// Awari.h : Awari ���ε{�����D���Y��
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"       // �D�n�Ÿ�


// CAwariApp:
// �аѾ\��@�����O�� Awari.cpp
//

class CAwariApp : public CWinApp
{
public:
	CAwariApp();


// �мg
public:
	virtual BOOL InitInstance();

// �{���X��@
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CAwariApp theApp;