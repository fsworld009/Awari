// AwariDoc.h : CAwariDoc ���O������
//
#include "AwariGame.h"

#pragma once


class CAwariDoc : public CDocument
{
protected: // �ȱq�ǦC�ƫإ�
	CAwariDoc();
	DECLARE_DYNCREATE(CAwariDoc)

// �ݩ�
public:
	bool NewGame(bool cpu_first);
private:
	AwariGame *m_game;
	int m_search_depth;
// �@�~
public:

// �мg
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// �{���X��@
public:
	virtual ~CAwariDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ͪ��T�������禡
protected:
	DECLARE_MESSAGE_MAP()
public:
	AwariGame* GetAwariGame(void);

public:
	afx_msg void OnFileNew();
public:
	afx_msg void OnDebug();
};


