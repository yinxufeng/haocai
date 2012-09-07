// MainUI.h : main header file for the PROJECT_NAME application
//

// #pragma once
// 
// #ifndef __AFXWIN_H__
// 	#error "include 'stdafx.h' before including this file for PCH"
// #endif
// 
// #include "resource.h"		// main symbols


// CMainUIApp:
// See MainUI.cpp for the implementation of this class
///////////////////////////////////////////////
#if !defined(AFX_MFCHTML_H__B1788361_D0EF_46A7_96FF_0FB656587334__INCLUDED_)
#define AFX_MFCHTML_H__B1788361_D0EF_46A7_96FF_0FB656587334__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////
class CImpIDispatch;
class CMainUIApp : public CWinApp
{
public:
	CMainUIApp();

	CImpIDispatch*		m_pCustDisp;

// Overrides
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMainUIApp theApp;

#endif