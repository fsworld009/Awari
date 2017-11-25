#pragma once

class Player
{
public:
	Player(void);
	virtual ~Player(void);
	int AddScore(int points);
	int GetScore(void);
	bool IsWinner();
	void Reset(int num);
private:
	int m_score;
};
