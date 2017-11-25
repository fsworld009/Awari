#include "StdAfx.h"
#include "Disk.h"

Disk::Disk(void):m_chesses(4)
{
}

Disk::~Disk(void)
{
}

int Disk::PutAChess()
{
	m_chesses++;
	return m_chesses;
}

int Disk::TakeUpAllChesses()
{
	int total = m_chesses;
	m_chesses=0;	//Take Up All
	return total;	//return how many you takes up
}

bool Disk::CanGetPoints()
{
	if(m_chesses==2 || m_chesses==3)
		return true;
	else
		return false;
}

bool Disk::IsEmpty()
{
	if(m_chesses==0)
		return true;
	else
		return false;
}

int Disk::GetNumOfChesses(void)
{
	return m_chesses;
}

void Disk::Reset(int num)
{
	m_chesses = num;
}