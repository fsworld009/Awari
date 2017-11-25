#pragma once

class Disk
{
public:
	Disk(void);
	virtual ~Disk(void);
	int PutAChess();
	int TakeUpAllChesses();
	bool CanGetPoints();
	bool IsEmpty();
	int GetNumOfChesses(void);
	void Reset(int num);
private:
	int m_chesses;
	
};
