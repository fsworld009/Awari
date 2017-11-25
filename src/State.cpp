#include "StdAfx.h"
#include "State.h"
#include "AwariGame.h"

#define STATE_INFINITE 999
#define STATE_MINUS_INFINITE -9999

State::State(void):m_is_leaf(false),m_is_max(false)
{
	int i;
	for(i=0;i<12;i++)
		m_disk[i] = 4;
	for(i=0;i<2;i++)
		m_score[i] = 0;
	for(i=0;i<6;i++)
		m_child[i] = 0;
}

State::State(AwariGame& game): m_is_leaf(false)
{
	game.GetParameter(m_disk,m_score,m_is_max);	
	int i;
	for(i=0;i<6;i++)
		m_child[i] = 0;
}

State& State::operator=(State& rhs)
{
	int i;
	for(i=0;i<6;i++){
		m_child[i] = rhs.m_child[i];
	}
	for(i=0;i<12;i++){
		m_disk[i] = rhs.m_disk[i];
	}
	for(i=0;i<2;i++){
		m_score[i] = rhs.m_score[i];
	}
	//ignore bool flag
	return *this;
}


State& State::operator=(AwariGame& rhs)
{
	rhs.GetParameter(m_disk,m_score,m_is_max);
	//don't care about child
	return *this;
}

void State::GetParameter(int disk[12],int player_score[2],bool& turn)
{
	int i;
	for(i=0;i<12;i++){
		disk[i] = m_disk[i];
	}
	for(i=0;i<2;i++){
		player_score[i] = m_score[i];
	}
	turn = m_is_max;
}

int State::GetNextMove(int search_depth)
{
	GenerateChild(1,search_depth);
	int next;
	Alpha_Beta(next,-99999,99999);
	DeleteChild();
	return next+6;
}

void State::GenerateChild(int depth_bound ,int max_depth_bound)
{
	//set goal flag at here?


	if(depth_bound==max_depth_bound){
		m_is_leaf = true;
		return;
	}
	AwariGame game_temp(*this);
	if(game_temp.IsGoal() != 0){
		m_is_leaf = true;		//Goal, is leaf
		return;
	}


	int i,move_id;
	for(i=0;i<6;i++){
		if(m_is_max == false)	//player
			move_id = i;
		else
			move_id = i+6;
		if(game_temp.PlayerMove(move_id,false)){
			m_child[i] = new State(game_temp);
			m_child[i]->GenerateChild(depth_bound+1,max_depth_bound);
		}else{
			m_child[i]=0;
		}
		game_temp = *this;
	}
}

State::~State(void)
{
}

bool State::DeleteChild(void)
{
	int i;
	if(m_is_leaf)	//no child
		return true;
	for(i=0;i<6;i++){
		if(m_child[i] != NULL){
			m_child[i]->DeleteChild();
			delete m_child[i];
		}
	}
	return true;
}

int State::Max(int a,int b)
{
	if(a>=b)
		return a;
	else
		return b;
}

int State::Min(int a,int b)
{
	if(a<=b)
		return a;
	else
		return b;
}

int State::evaluation()
{
	int self_id, rival_id, self_disk, rival_disk, min_max;
	if(m_is_max){	//cpu
		self_id=1;
		rival_id=0;
		self_disk=6;
		rival_disk=0;
		min_max=1;
	}else{			//player
		self_id=0;
		rival_id=1;
		self_disk=0;
		rival_disk=6;
		min_max=-1;
	}

	//isGoal
	if(m_score[self_id] > 25){
		return 99999*(min_max);
	}
	if(m_score[rival_id] > 25){
		return -99999*(min_max);
	}




	int total=0,current_max=0,get_score=0;
	int i,j;
	int mux1, mux2;
	
	for(i=5;i>=0;i--){
		if(m_disk[self_disk+i]==0 || m_disk[self_disk+i]==1 || m_disk[self_disk+i]==2){
			switch(m_disk[self_disk+i]){
			case 0:
				mux1=11; mux2=22;	break;
			case 1:
				mux1=0; mux2=11;	break;
			case 2:
				mux1=999; mux2=0;	break;//mux2 impossible
			}
			for(j=5;j>=0;j--){
				if(m_disk[rival_disk+j]==((6-(5-i))+(5-j))+mux1){
					get_score+=2;
				}else if(m_disk[rival_disk+j]==((6-(5-i))+(5-j))+mux2){
					get_score+=3;
					break;		//3 is the max, don't need to search other state
				}
			}
			if(get_score == 0){
				total=Max(total,current_max);
				current_max=0;	//restart count
			}else{
				current_max+=get_score;
			}
		}
	}

	total=Max(total,current_max);
	return (m_score[self_id]-m_score[rival_id]-total)*(min_max);
}

int State::Alpha_Beta(int &child_id, int a,int b)
{
	//a = alpha, b = beta;
	child_id=0;
	int new_child_id=0;
	int i;
	if(m_is_leaf){
		child_id = -1;	//child_id is meaningless
		return evaluation();
	}
	if(m_is_max){
		//max
		int max_v = -99999, old_max_v;
		for(i=0;i<6;i++){
			if(m_child[i] != NULL){
				old_max_v = max_v;
				max_v = Max(max_v, m_child[i]->Alpha_Beta(new_child_id,a,b));
				if(max_v > old_max_v)	//refresh
					child_id = i;
				a = Max(max_v,a);
				if(a >= b)
					return a;
			}
		}
		return max_v;
	}

	if(!m_is_max){
		//min
		int min_v = 99999, old_min_v;
		for(i=0;i<6;i++){
			if(m_child[i] != NULL){
				old_min_v = min_v;
				min_v = Min(min_v, m_child[i]->Alpha_Beta(child_id,a,b));
				if(min_v < old_min_v)	//refresh
					child_id = i;
				b = Min(min_v,b);
				if(b <= a)
					return b;
			}
		}
		return min_v;
	}
	return -1;
}