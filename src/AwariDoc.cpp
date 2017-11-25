// AwariDoc.cpp : CAwariDoc ���O����@
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


// CAwariDoc �غc/�Ѻc

CAwariDoc::CAwariDoc():m_search_depth(5)
{
	// TODO: �b���[�J�@���غc�{���X
	m_game = 0;

}

CAwariDoc::~CAwariDoc()
{
}

BOOL CAwariDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �b���[�J���s��l�Ƶ{���X
	// (SDI ���|���Φ����)
	

	return TRUE;
}




// CAwariDoc �ǦC��

void CAwariDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �b���[�J�x�s�{���X
	}
	else
	{
		// TODO: �b���[�J���J�{���X
	}
}


// CAwariDoc �E�_

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


// CAwariDoc �R�O

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
	// TODO: �b���[�J�z���R�O�B�z�`���{���X
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
	// TODO: �b���[�J�z���R�O�B�z�`���{���X
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
