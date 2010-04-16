
// mfctest.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTempApp:
// See Temp.cpp for the implementation of this class
//

class CmfctestApp : public CWinAppEx
{
public:
	CmfctestApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CmfctestApp theApp;