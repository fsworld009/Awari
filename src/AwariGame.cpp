#include "StdAfx.h"
#include "AwariGame.h"
#include "AwariView.h"
#include "MainFrm.h"

//add operator =

AwariGame::AwariGame(bool cpu_first):m_turn(cpu_first)
{
}

AwariGame::AwariGame(State &src)
{
	int disk[12], score[2];
	bool turn;
	src.GetParameter(disk,score,turn);
	int i;
	for(i=0;i<12;i++){
		m_disk[i].Reset(disk[i]);
	}
	for(i=0;i<2;i++){
		m_player[i].Reset(score[i]);
	}
	m_turn = turn;
	m_current = src;
}

AwariGame &AwariGame::operator=(State &rhs)
{
	int disk[12], score[2];
	bool turn;
	rhs.GetParameter(disk,score,turn);
	int i;
	for(i=0;i<12;i++){
		m_disk[i].Reset(disk[i]);
	}
	for(i=0;i<2;i++){
		m_player[i].Reset(score[i]);
	}
	m_turn = turn;
	m_current = rhs;
	return *this;
}

AwariGame::~AwariGame()
{
}

void AwariGame::UpdateCurrentMove(int time)
{
	CMainFrame* pMain = (CMainFrame*) AfxGetMainWnd();
	CAwariView* pView = (CAwariView*) pMain->GetActiveView();
	pView->UpdateDataAndShow();
	Sleep(time);
}

bool AwariGame::Move(int disk_num, bool step_play)
{
	if(!(disk_num >= 0 && disk_num <12))
		return false;
	if(m_turn == false){	//player
		if(disk_num >5 && disk_num <12)
			return false;
	}else{			//cpu
		if(disk_num >=0 && disk_num <6)
			return false;
	}
	if(m_disk[disk_num].GetNumOfChesses() == 0)
		return false;

	int total_chess = m_disk[disk_num].TakeUpAllChesses();
	if(step_play)
		UpdateCurrentMove(400);

	int i=disk_num,count=0;
	i = NextDisk(i);
	for(count=0; count < total_chess ; ){
		if(i != disk_num){
			m_disk[i].PutAChess();
			count++;			//if turn a round, ignore the [disk_num] position
			if(step_play)
				UpdateCurrentMove(200);
		}
		i = NextDisk(i);
	}
	i= PreviousDisk(i);
	//Check Get Score
	int lower_bound, upper_bound, player_id;

	if(m_turn == false){				//player's
		lower_bound=6, upper_bound=11, player_id=0;
	}else{		//cpu
		lower_bound=0, upper_bound=5, player_id=1;
	}

	if(m_disk[i].CanGetPoints() && step_play)
		UpdateCurrentMove(400);

	while(m_disk[i].CanGetPoints() && i>=lower_bound && i<=upper_bound){
		m_player[player_id].AddScore(m_disk[i].TakeUpAllChesses());
		i= PreviousDisk(i);
		if(step_play)
			UpdateCurrentMove(200);
	}

	//Rival's disk are All 0 's situation
	if(m_disk[lower_bound].GetNumOfChesses()==0 && m_disk[lower_bound+1].GetNumOfChesses()==0 && m_disk[lower_bound+2].GetNumOfChesses()==0 && m_disk[lower_bound+3].GetNumOfChesses()==0 && m_disk[lower_bound+4].GetNumOfChesses()==0 && m_disk[lower_bound+5].GetNumOfChesses()==0){
		//if(判斷是否所有移動後對方都為0){
			//return true;
		//}else{
			*this = m_current;	//回碩
			return false;		//犯規
		//}
	}
	

	PlayerChange();
	return true;
}

bool AwariGame::PlayerMove(int disk_num,bool step_play)
{
	if(step_play){
		if(!Move(disk_num))			//先看看有沒有犯規
			return false;			//直接回傳false;
		*this = m_current;			//回碩
		Move(disk_num,true);		//有動畫的再移一次
		m_current = *this;			//更新目前狀態
		return true;
	}
	else{
		return Move(disk_num);
	}
	

	
}

bool AwariGame::ComputerMove(int search_depth)
{
	//m_current.GenerateChild(0,5);
	/*int a;
	do{
		a = rand()%6+6;
	}while(!Move(a));*/
	int a = m_current.GetNextMove(search_depth);
	Move(a,true);		//this Move always true
	m_current = *this;
	return true;
}

void AwariGame::GetParameter(int disk[12],int player_score[2], bool& turn)
{
	int i;
	for(i=0;i<12;i++){
		disk[i] = m_disk[i].GetNumOfChesses();
	}
	for(i=0;i<2;i++){
		player_score[i] = m_player[i].GetScore();
	}
	turn = m_turn;
}

void AwariGame::PlayerChange()
{
	m_turn = !m_turn;
}

int AwariGame::NextDisk(int current_disk_num)
{
	return (current_disk_num+1)%12;
}



int AwariGame::PreviousDisk(int current_disk_num)
{
	if(current_disk_num == 0){
		return 11;
	}else{
		return (--current_disk_num);
	}
}

int AwariGame::IsGoal()
{
	//-1 = player win, 0 =false, 1 = cpu win, 2 =draw
	if(m_player[0].GetScore() >24){
		return -1;
	}
	if(m_player[1].GetScore() > 24){
		return 1;
	}
	if(m_player[0].GetScore() ==24 && m_player[1].GetScore()==24)
		return 2;

	bool zero0 = (m_disk[0].GetNumOfChesses()==0)&&(m_disk[1].GetNumOfChesses()==0)&&(m_disk[2].GetNumOfChesses()==0)&&(m_disk[3].GetNumOfChesses()==0)&&(m_disk[4].GetNumOfChesses()==0)&&(m_disk[5].GetNumOfChesses()==0 && (m_turn==false));
	bool zero1 = (m_disk[6].GetNumOfChesses()==0)&&(m_disk[7].GetNumOfChesses()==0)&&(m_disk[8].GetNumOfChesses()==0)&&(m_disk[9].GetNumOfChesses()==0)&&(m_disk[10].GetNumOfChesses()==0)&&(m_disk[11].GetNumOfChesses()==0 && (m_turn==true));
	if(zero0 || zero1){
		if(m_player[0].GetScore() > m_player[1].GetScore())
			return -1;
		else if(m_player[1].GetScore() > m_player[0].GetScore())
			return 1;
		else
			return 2;
	}
	return 0;

}

void AwariGame::Debug(int disk[], int player_score[], bool turn)
{
	int i;
	for(i=0;i<12;i++){
		m_disk[i].Reset(disk[i]);
	}
	for(i=0;i<2;i++){
		m_player[i].Reset(player_score[i]);
	}
	m_turn = turn;
	m_current = *this;
}