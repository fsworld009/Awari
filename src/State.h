#pragma once


class AwariGame;

class State
{

public:
	/*typedef struct road{
		int m_value;
		int m_child_id;
	};*/
	State(void);
	State(AwariGame& game);
	void GetParameter(int disk[12],int player_score[2],bool& turn);
	State& State::operator=(AwariGame& rhs);
	State& State::operator=(State& rhs);
	int GetNextMove(int search_depth);		//header of the min_max search
public:
	virtual ~State(void);
private:
	int m_disk[12];
	int m_score[2];
	bool m_is_leaf;
	bool m_is_max;	//false=player(min) ,true=cpu(max);
	State* m_child[6];
	void GenerateChild(int depth_bound ,int max_depth_bound);
	bool DeleteChild(void);
	int Alpha_Beta(int &child_id, int a,int b);
	int Max(int a,int b);
	int Min(int a,int b);
	int evaluation();
	bool IsGoal();
};
