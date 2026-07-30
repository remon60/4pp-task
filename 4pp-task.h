
// 4pp-task.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMy4pptaskApp:
// See 4pp-task.cpp for the implementation of this class
//

class CMy4pptaskApp : public CWinApp
{
public:
	CMy4pptaskApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMy4pptaskApp theApp;
