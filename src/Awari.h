// Awari.h : Awari 應用程式的主標頭檔
//
#pragma once

#ifndef __AFXWIN_H__
	#error "對 PCH 包含此檔案前先包含 'stdafx.h'"
#endif

#include "resource.h"       // 主要符號


// CAwariApp:
// 請參閱實作此類別的 Awari.cpp
//

class CAwariApp : public CWinApp
{
public:
	CAwariApp();


// 覆寫
public:
	virtual BOOL InitInstance();

// 程式碼實作
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CAwariApp theApp;