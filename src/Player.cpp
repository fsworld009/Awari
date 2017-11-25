#include "StdAfx.h"
#include "Player.h"

Player::Player(void):m_score(0)
{
}

Player::~Player(void)
{
}

int Player::AddScore(int score)
{
	m_score += score;
	return m_score;
}

int Player::GetScore(void)
{
	return m_score;
}

void Player::Reset(int num)
{
	m_score = num;
}
