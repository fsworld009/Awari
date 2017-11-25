#include "Disk.h"
#include "Player.h"
#include "State.h"

#pragma once

class AwariGame
{
public:
	AwariGame(bool cpu_first);
	AwariGame(State &src);
	virtual ~AwariGame();
	bool PlayerMove(int Disk_num,bool step_play=false);
	bool ComputerMove(int search_depth);
	void GetParameter(int disk[12],int player_score[2],bool& turn);
	void Debug(int disk[12],int player_score[2],bool turn);
	int IsGoal();	//StateªºIsGoal¾aAwariGame§¹¦¨
	AwariGame &AwariGame::operator =(State &rhs);
private:
	Disk m_disk[12];
	Player m_player[2];
	State m_current;
	bool m_turn;	//flase=player,true=cpu;
	bool Move(int disk_num,bool step_play=false);
	int NextDisk(int current_disk_num);
	int PreviousDisk(int current_disk_num);
	void UpdateCurrentMove(int time);		//Show Move Step
	void PlayerChange();
};

