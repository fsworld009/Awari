// AwariDoc.h : CAwariDoc 類別的介面
//
#include "AwariGame.h"

#pragma once


class CAwariDoc : public CDocument
{
protected: // 僅從序列化建立
	CAwariDoc();
	DECLARE_DYNCREATE(CAwariDoc)

// 屬性
public:
	bool NewGame(bool cpu_first);
private:
	AwariGame *m_game;
	int m_search_depth;
// 作業
public:

// 覆寫
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 程式碼實作
public:
	virtual ~CAwariDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 產生的訊息對應函式
protected:
	DECLARE_MESSAGE_MAP()
public:
	AwariGame* GetAwariGame(void);

public:
	afx_msg void OnFileNew();
public:
	afx_msg void OnDebug();
};


