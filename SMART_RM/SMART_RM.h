
// SMART_RM.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CSMART_RMApp:
// See SMART_RM.cpp for the implementation of this class
//

class CSMART_RMApp : public CWinApp
{
public:
	CSMART_RMApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CSMART_RMApp theApp;