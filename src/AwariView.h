// AwariView.h : CAwariView ���O������
//

//Use for AwariGame Class??
#include "Awari.h"
#include "AwariDoc.h"
//

#pragma once


class CAwariView : public CFormView
{
protected: // �ȱq�ǦC�ƫإ�
	CAwariView();
	DECLARE_DYNCREATE(CAwariView)

public:
	enum{ IDD = IDD_AWARI_FORM };

// �ݩ�
public:
	CAwariDoc* GetDocument() const;
	void UpdateDataAndShow();	//GetParameter from AwariGame, then UpdateData
	void SetButtonStatus(bool click_enable,bool set_enable);
	bool CheckGoal();
	void ResetView();
	void SetSearchDepth(int search_depth);
private:
	int m_disk_view[12];
	int m_player_view[2];
	bool m_turn;
	int m_search_depth;

// �@�~
public:

// �мg
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩
	virtual void OnInitialUpdate(); // �غc��Ĥ@���I�s

// �{���X��@
public:
	virtual ~CAwariView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ͪ��T�������禡
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedClick0();
public:
	afx_msg void OnBnClickedClick1();
public:
	afx_msg void OnBnClickedClick2();
public:
	afx_msg void OnBnClickedClick3();
public:
	afx_msg void OnBnClickedClick4();
public:
	afx_msg void OnBnClickedClick5();
public:
	void Move(int disk_num);
public:
	afx_msg void OnBnClickedFirst();
public:
	afx_msg void OnBnClickedSecond();
};

#ifndef _DEBUG  // AwariView.cpp ������������
inline CAwariDoc* CAwariView::GetDocument() const
   { return reinterpret_cast<CAwariDoc*>(m_pDocument); }
#endif

