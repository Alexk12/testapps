
// DecodeBase64.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CDecodeBase64App:
// See DecodeBase64.cpp for the implementation of this class
//

class CDecodeBase64App : public CWinApp
{
public:
	CDecodeBase64App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CDecodeBase64App theApp;
