
// MainUI.cpp : Defines the class behaviors for the application.
//
#include "stdafx.h"
#include "MainUI.h"
#include "MainUIDlg.h"
#include "ImpIDispatch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



BEGIN_MESSAGE_MAP(CMainUIApp, CWinApp)
	//{{AFX_MSG_MAP(CMFCHtmlApp)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCHtmlApp construction

CMainUIApp::CMainUIApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMFCHtmlApp object

CMainUIApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMFCHtmlApp initialization

BOOL CMainUIApp::InitInstance()
{
	AfxEnableControlContainer();
	CoInitialize(NULL);

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested=MAKEWORD(1,1);  // for mobile it 1.1 C Sock
	err=WSAStartup(wVersionRequested,&wsaData);
	if (LOBYTE(wsaData.wVersion)!=1||HIBYTE(wsaData.wVersion)!=1)
	{
		WSACleanup();
	}

	m_pCustDisp = new CImpIDispatch;

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	CMainUIDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CMainUIApp::ExitInstance() 
{
	WSACleanup();
	// TODO: Add your specialized code here and/or call the base class
	if(m_pCustDisp)
	{
		delete m_pCustDisp;
		m_pCustDisp = NULL;
	}
	CoUninitialize();
	return CWinApp::ExitInstance();
}
/////////////////////////////////////////////////////////////




// CMainUIApp
// 
// BEGIN_MESSAGE_MAP(CMainUIApp, CWinAppEx)
// 	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
// END_MESSAGE_MAP()
// 
// 
// CMainUIApp construction
// 
// CMainUIApp::CMainUIApp()
// {
// 	// TODO: add construction code here,
// 	// Place all significant initialization in InitInstance
// }
// 
// 
// The one and only CMainUIApp object
// 
// CMainUIApp theApp;
// 
// 
// CMainUIApp initialization
// 
// BOOL CMainUIApp::InitInstance()
// {
// 	// InitCommonControlsEx() is required on Windows XP if an application
// 	// manifest specifies use of ComCtl32.dll version 6 or later to enable
// 	// visual styles.  Otherwise, any window creation will fail.
// 	INITCOMMONCONTROLSEX InitCtrls;
// 	InitCtrls.dwSize = sizeof(InitCtrls);
// 	// Set this to include all the common control classes you want to use
// 	// in your application.
// 	InitCtrls.dwICC = ICC_WIN95_CLASSES;
// 	InitCommonControlsEx(&InitCtrls);
// 
// 	CWinAppEx::InitInstance();
// 
// 	AfxEnableControlContainer();
// 
// 	// Standard initialization
// 	// If you are not using these features and wish to reduce the size
// 	// of your final executable, you should remove from the following
// 	// the specific initialization routines you do not need
// 	// Change the registry key under which our settings are stored
// 	// TODO: You should modify this string to be something appropriate
// 	// such as the name of your company or organization
// 	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
// 
// 	CMainUIDlg dlg;
// 	m_pMainWnd = &dlg;
// 	INT_PTR nResponse = dlg.DoModal();
// 	if (nResponse == IDOK)
// 	{
// 		// TODO: Place code here to handle when the dialog is
// 		//  dismissed with OK
// 	}
// 	else if (nResponse == IDCANCEL)
// 	{
// 		// TODO: Place code here to handle when the dialog is
// 		//  dismissed with Cancel
// 	}
// 
// 	// Since the dialog has been closed, return FALSE so that we exit the
// 	//  application, rather than start the application's message pump.
// 	return FALSE;
// }
