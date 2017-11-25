#include "AwariGame.h"

#pragma once


// CAwariDebugDialog ��ܤ��

class CAwariDebugDialog : public CDialog
{
	DECLARE_DYNAMIC(CAwariDebugDialog)

public:
	CAwariDebugDialog(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CAwariDebugDialog();
	void SetParameter(AwariGame* game,int search_depth);

// ��ܤ�����
	enum { IDD = IDD_DEBUG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	DECLARE_MESSAGE_MAP()

public:
	int m_disk[12];
	int m_score[2];
	bool m_turn;
public:
	int m_turn_radio;
public:
	int m_search_depth;
};
