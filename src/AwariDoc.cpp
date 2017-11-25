// AwariDoc.cpp : CAwariDoc 類別的實作
//

#include "stdafx.h"
#include "Awari.h"

#include "AwariDoc.h"
#include "AwariView.h"
#include "MainFrm.h"
#include "AwariDebugDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAwariDoc

IMPLEMENT_DYNCREATE(CAwariDoc, CDocument)

BEGIN_MESSAGE_MAP(CAwariDoc, CDocument)
	
	ON_COMMAND(ID_FILE_NEW, &CAwariDoc::OnFileNew)
	ON_COMMAND(ID_DEBUG, &CAwariDoc::OnDebug)
END_MESSAGE_MAP()


// CAwariDoc 建構/解構

CAwariDoc::CAwariDoc():m_search_depth(5)
{
	// TODO: 在此加入一次建構程式碼
	m_game = 0;

}

CAwariDoc::~CAwariDoc()
{
}

BOOL CAwariDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此加入重新初始化程式碼
	// (SDI 文件會重用此文件)
	

	return TRUE;
}




// CAwariDoc 序列化

void CAwariDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此加入儲存程式碼
	}
	else
	{
		// TODO: 在此加入載入程式碼
	}
}


// CAwariDoc 診斷

#ifdef _DEBUG
void CAwariDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAwariDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CAwariDoc 命令

AwariGame* CAwariDoc::GetAwariGame(void)
{
	return m_game;
}

bool CAwariDoc::NewGame(bool cpu_first)
{
	if(m_game==NULL){
		m_game = new AwariGame(cpu_first);
		return true;
	}
	return false;
}


void CAwariDoc::OnFileNew()
{
	// TODO: 在此加入您的命令處理常式程式碼
	if(m_game){
		delete m_game;
		m_game=0;
		CMainFrame* pMain = (CMainFrame*) AfxGetMainWnd();
		CAwariView* pView = (CAwariView*) pMain->GetActiveView();
		pView->ResetView();
		pView->SetButtonStatus(false,true);
	}
}

void CAwariDoc::OnDebug()
{
	// TODO: 在此加入您的命令處理常式程式碼
	if(m_game){
		CAwariDebugDialog dl;
		dl.SetParameter(m_game,m_search_depth);
		if(dl.DoModal() == IDOK){
			int turn_radio_value = dl.m_turn_radio;
			bool turn;
			if(turn_radio_value==0){
				turn=false;
			}else{
				turn=true;
			}
			m_game->Debug(dl.m_disk,dl.m_score,turn);
			m_search_depth = dl.m_search_depth;

			CMainFrame* pMain = (CMainFrame*) AfxGetMainWnd();
			CAwariView* pView = (CAwariView*) pMain->GetActiveView();
			pView->UpdateDataAndShow();
			pView->SetSearchDepth(m_search_depth);
			if(turn==true){	//cpu
				pView->SetButtonStatus(false,false);
				m_game->ComputerMove(m_search_depth);
				pView->CheckGoal();
				pView->SetButtonStatus(true,false);
			}
		}
	}
}
