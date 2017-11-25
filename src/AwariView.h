// AwariView.h : CAwariView 類別的介面
//

//Use for AwariGame Class??
#include "Awari.h"
#include "AwariDoc.h"
//

#pragma once


class CAwariView : public CFormView
{
protected: // 僅從序列化建立
	CAwariView();
	DECLARE_DYNCREATE(CAwariView)

public:
	enum{ IDD = IDD_AWARI_FORM };

// 屬性
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

// 作業
public:

// 覆寫
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援
	virtual void OnInitialUpdate(); // 建構後第一次呼叫

// 程式碼實作
public:
	virtual ~CAwariView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 產生的訊息對應函式
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

#ifndef _DEBUG  // AwariView.cpp 中的偵錯版本
inline CAwariDoc* CAwariView::GetDocument() const
   { return reinterpret_cast<CAwariDoc*>(m_pDocument); }
#endif

