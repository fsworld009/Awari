// AwariDebugDialog.cpp : 實作檔
//

#include "stdafx.h"
#include "Awari.h"
#include "AwariDebugDialog.h"


// CAwariDebugDialog 對話方塊

IMPLEMENT_DYNAMIC(CAwariDebugDialog, CDialog)

CAwariDebugDialog::CAwariDebugDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CAwariDebugDialog::IDD, pParent)
	, m_turn_radio(0)
	, m_search_depth(5)
{

}

CAwariDebugDialog::~CAwariDebugDialog()
{
}

void CAwariDebugDialog::DoDataExchange(CDataExchange* pDX)
{
	DDX_Text(pDX,IDC_DISK0,m_disk[0]);
	DDX_Text(pDX,IDC_DISK1,m_disk[1]);
	DDX_Text(pDX,IDC_DISK2,m_disk[2]);
	DDX_Text(pDX,IDC_DISK3,m_disk[3]);
	DDX_Text(pDX,IDC_DISK4,m_disk[4]);
	DDX_Text(pDX,IDC_DISK5,m_disk[5]);
	DDX_Text(pDX,IDC_DISK6,m_disk[6]);
	DDX_Text(pDX,IDC_DISK7,m_disk[7]);
	DDX_Text(pDX,IDC_DISK8,m_disk[8]);
	DDX_Text(pDX,IDC_DISK9,m_disk[9]);
	DDX_Text(pDX,IDC_DISK10,m_disk[10]);
	DDX_Text(pDX,IDC_DISK11,m_disk[11]);
	DDX_Text(pDX,IDC_PLAYER_SCORE,m_score[0]);
	DDX_Text(pDX,IDC_CPU_SCORE,m_score[1]);
	DDX_Text(pDX,IDC_S_DEPTH,m_search_depth);
	DDX_Radio(pDX,IDC_R_PLAYER,m_turn_radio);
	CDialog::DoDataExchange(pDX);
}

void CAwariDebugDialog::SetParameter(AwariGame* game,int search_depth)
{
	game->GetParameter(m_disk,m_score,m_turn);
	if(m_turn==false)
		m_turn_radio=0;
	else
		m_turn_radio=1;
	m_search_depth=search_depth;
	//this->GetDlgItem(IDC_R_PLAYER)->CheckRadioButton(IDC_R_PLAYER,IDC_R_CPU,IDC_R_PLAYER);
}


BEGIN_MESSAGE_MAP(CAwariDebugDialog, CDialog)
END_MESSAGE_MAP()


// CAwariDebugDialog 訊息處理常式
