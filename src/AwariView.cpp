// AwariView.cpp : CAwariView ���O����@
//

#include "stdafx.h"
#include "Awari.h"

#include "AwariDoc.h"
#include "AwariView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAwariView

IMPLEMENT_DYNCREATE(CAwariView, CFormView)

BEGIN_MESSAGE_MAP(CAwariView, CFormView)
	ON_BN_CLICKED(IDC_CLICK0, &CAwariView::OnBnClickedClick0)
	ON_BN_CLICKED(IDC_CLICK1, &CAwariView::OnBnClickedClick1)
	ON_BN_CLICKED(IDC_CLICK2, &CAwariView::OnBnClickedClick2)
	ON_BN_CLICKED(IDC_CLICK3, &CAwariView::OnBnClickedClick3)
	ON_BN_CLICKED(IDC_CLICK4, &CAwariView::OnBnClickedClick4)
	ON_BN_CLICKED(IDC_CLICK5, &CAwariView::OnBnClickedClick5)
	ON_BN_CLICKED(IDC_FIRST, &CAwariView::OnBnClickedFirst)

	ON_BN_CLICKED(IDC_SECOND, &CAwariView::OnBnClickedSecond)
END_MESSAGE_MAP()

// CAwariView �غc/�Ѻc

CAwariView::CAwariView()
	: CFormView(CAwariView::IDD), m_search_depth(5)
{
	// TODO: �b���[�J�غc�{���X
	int i;
	for(i=0;i<12;i++){
		m_disk_view[i] = 4;
	}
	for(i=0;i<2;i++){
		m_player_view[i] = 0;
	}
}

CAwariView::~CAwariView()
{
}

void CAwariView::SetSearchDepth(int search_depth)
{
	m_search_depth = search_depth;
}

void CAwariView::DoDataExchange(CDataExchange* pDX)
{
	//int test=100;
	DDX_Text(pDX,IDC_SCORE0,m_disk_view[0]);
	DDX_Text(pDX,IDC_SCORE1,m_disk_view[1]);
	DDX_Text(pDX,IDC_SCORE2,m_disk_view[2]);
	DDX_Text(pDX,IDC_SCORE3,m_disk_view[3]);
	DDX_Text(pDX,IDC_SCORE4,m_disk_view[4]);
	DDX_Text(pDX,IDC_SCORE5,m_disk_view[5]);
	DDX_Text(pDX,IDC_SCORE6,m_disk_view[6]);
	DDX_Text(pDX,IDC_SCORE7,m_disk_view[7]);
	DDX_Text(pDX,IDC_SCORE8,m_disk_view[8]);
	DDX_Text(pDX,IDC_SCORE9,m_disk_view[9]);
	DDX_Text(pDX,IDC_SCORE10,m_disk_view[10]);
	DDX_Text(pDX,IDC_SCORE11,m_disk_view[11]);
	DDX_Text(pDX,IDC_PLAYER0_SCORE,m_player_view[0]);
	DDX_Text(pDX,IDC_PLAYER1_SCORE,m_player_view[1]);
	//Sleep(1000);
	CFormView::DoDataExchange(pDX);
	//UpdateData(false);
}

BOOL CAwariView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �b���g�ѭק� CREATESTRUCT cs 
	// �F��ק�������O�μ˦����ت�

	return CFormView::PreCreateWindow(cs);
}

void CAwariView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CAwariView �E�_

#ifdef _DEBUG
void CAwariView::AssertValid() const
{
	CFormView::AssertValid();
}

void CAwariView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CAwariDoc* CAwariView::GetDocument() const // ���O�D��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAwariDoc)));
	return (CAwariDoc*)m_pDocument;
}
#endif //_DEBUG


// CAwariView �T���B�z�`��

void CAwariView::OnBnClickedClick0()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	Move(0);
}

void CAwariView::OnBnClickedClick1()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	Move(1);
}

void CAwariView::OnBnClickedClick2()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	Move(2);
}

void CAwariView::OnBnClickedClick3()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	Move(3);
}

void CAwariView::OnBnClickedClick4()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	Move(4);
}

void CAwariView::OnBnClickedClick5()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	Move(5);

}

void CAwariView::Move(int disk_num)
{
	CAwariDoc* pDoc = (CAwariDoc*) GetDocument();
	AwariGame* pGame = pDoc->GetAwariGame();
	SetButtonStatus(false,false);
	if(pGame->PlayerMove(disk_num,true)){
		UpdateDataAndShow();
		if(CheckGoal()){					//player alreay win
			return;							//cpu do not move
		}
		Sleep(600);
		pGame->ComputerMove(m_search_depth);
		UpdateDataAndShow();
		if(CheckGoal()){					//cpu alreay win
			return;							//do not change button status(remain disable)
		}
		SetButtonStatus(true,false);
	}else{
		MessageBox(_T("���B�ǳW"),_T("���~"));
		SetButtonStatus(true,false);
	}
}

void CAwariView::UpdateDataAndShow()
{
	CAwariDoc* pDoc = (CAwariDoc*) GetDocument();
	AwariGame* pGame = pDoc->GetAwariGame();
	pGame->GetParameter(m_disk_view,m_player_view,m_turn);
	this->UpdateData(false);
}

void CAwariView::SetButtonStatus(bool click_enable,bool set_enable)
{
	this->GetDlgItem(IDC_CLICK0)->EnableWindow(click_enable);
	this->GetDlgItem(IDC_CLICK1)->EnableWindow(click_enable);
	this->GetDlgItem(IDC_CLICK2)->EnableWindow(click_enable);
	this->GetDlgItem(IDC_CLICK3)->EnableWindow(click_enable);
	this->GetDlgItem(IDC_CLICK4)->EnableWindow(click_enable);
	this->GetDlgItem(IDC_CLICK5)->EnableWindow(click_enable);
	this->GetDlgItem(IDC_FIRST)->EnableWindow(set_enable);
	this->GetDlgItem(IDC_SECOND)->EnableWindow(set_enable);
}

bool CAwariView::CheckGoal()
{
	CAwariDoc* pDoc = (CAwariDoc*) GetDocument();
	AwariGame* pGame = pDoc->GetAwariGame();
	switch(pGame->IsGoal()){
	case 1:
		MessageBox(_T("�C������"),_T("�A��F"));
		SetButtonStatus(false,false);
		return true;
		break;
	case -1:
		MessageBox(_T("�C������"),_T("�AĹ�F"));
		SetButtonStatus(false,false);
		return true;
		break;
	case 2:
		MessageBox(_T("�C������"),_T("����"));
		SetButtonStatus(false,false);
		return true;
		break;
	default:
		return false;
		break;
	}
}

void CAwariView::OnBnClickedFirst()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	CAwariDoc* pDoc = (CAwariDoc*) GetDocument();
	pDoc->NewGame(false);
	SetButtonStatus(true,false);
}

void CAwariView::OnBnClickedSecond()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	CAwariDoc* pDoc = (CAwariDoc*) GetDocument();
	pDoc->NewGame(true);
	AwariGame* pGame = pDoc->GetAwariGame();
	SetButtonStatus(false,false);
	pGame->ComputerMove(m_search_depth);
	CheckGoal();
	SetButtonStatus(true,false);

}

void CAwariView::ResetView()
{
	int i;
	for(i=0;i<12;i++)
		m_disk_view[i]=4;
	for(i=0;i<2;i++)
		m_player_view[i]=0;
	UpdateData(false);
}
