// MainFrm.h : CMainFrame ���O������
//


#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // �ȱq�ǦC�ƫإ�
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// �ݩ�
public:

// �@�~
public:

// �мg
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// �{���X��@
public:
	void UpdateView();
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // ����C���O������
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// ���ͪ��T�������禡
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
};


