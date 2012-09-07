
// MainUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MainUI.h"
#include "MainUIDlg.h"
#include "ImpIDispatch.h"
#include <TlHelp32.h>
#include <atlbase.h>
#include <cfgmgr32.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern CString GetAppCurrentPath();

CMainUIDlg::CMainUIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainUIDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pIHTMLDoc		= NULL;
	
}

void CMainUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EXPLORER_MAIN, m_wndWeb);
}

BEGIN_MESSAGE_MAP(CMainUIDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CMainUIDlg, CDialog)
	ON_EVENT(CMainUIDlg, IDC_EXPLORER_MAIN, 259, OnDocumentCompleteExplorerMain, VTS_DISPATCH VTS_PVARIANT)
END_EVENTSINK_MAP()

void CMainUIDlg::OnDocumentCompleteExplorerMain(LPDISPATCH pDisp, VARIANT FAR* URL) 
{
	IDispatch*				pIDisp			= NULL;
	pIDisp = m_wndWeb.GetDocument();
	if(pIDisp)
	{
		theApp.m_pCustDisp->m_InterfaceToJs->SetDisPath(pIDisp);
	}
}

BOOL CMainUIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	

     CString StrDes=_T("");
     ::GetModuleFileName(NULL,StrDes.GetBuffer(MAX_PATH),MAX_PATH); 
     StrDes.ReleaseBuffer();
     StrDes=StrDes.Left(StrDes.ReverseFind('\\'));
     if(StrDes.Right(1)!='\\')
         StrDes+="\\";
	 StrDes +=_T("Custom.html");


	CRect Rect;
	GetWindowRect(Rect);
	int Width   = 910;
	int Height  = 683;
	Rect.right  = Rect.left + Width;
	Rect.bottom = Rect.top + Height;
	MoveWindow(Rect);                    //设置对话框大小
	this->CenterWindow(NULL);            //居中
	SetRoundWindows(Width,Height,4);     //设置圆角的对话框
	m_wndWeb.Navigate(StrDes, NULL, NULL, NULL, NULL);

	m_wndWeb.SetWidth(Width);
	m_wndWeb.SetHeight(Height);


	CString FilePath=GetAppCurrentPath()+_T("Data.txt");
	CDataManageCenter::GetInstance()->LoadDataFromFile(FilePath,false);
	FilePath=GetAppCurrentPath()+_T("Data2.txt");
	CDataManageCenter::GetInstance()->LoadDataFromFile(FilePath,true);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMainUIDlg::SetRoundWindows(int Width, int Height, int round)  //设置弧度 对话框 宽 高 弧度
{
	CRgn m_frmRgn;
	POINT PointArray[7];
	PointArray[0].x=4;
	PointArray[0].y=0;
	PointArray[1].x=Width-4;
	PointArray[1].y=0;
	PointArray[2].x=Width;
	PointArray[2].y=4;
	PointArray[3].x=Width;
	PointArray[3].y=Height;
	PointArray[4].x=0;
	PointArray[4].y=Height;
	PointArray[5].x=0;
	PointArray[5].y=4;
	PointArray[6].x=4;
	PointArray[6].y=0;
	m_frmRgn.CreatePolygonRgn(PointArray,7,ALTERNATE);
	SetWindowRgn(m_frmRgn,TRUE);
	m_frmRgn.DeleteObject();
}

void CMainUIDlg::MoveMainDlg(int iArg1 , int iArg2)
{
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(iArg1,iArg2));
	return;
}

BOOL CMainUIDlg::IsAppRun(CString AppName) 
{ 
	char   pPath[_MAX_PATH]; 
	pPath[0]=0; 
	const char *cExeName = CStrToChar(AppName);
	_searchenv(cExeName, "PATH ",pPath); 
	VERIFY(pPath);
	DWORD id=GetProcessIdFromName(AppName);//这样查杀AppName 
	if(id!=NULL) 
	{ 
		HANDLE   myhandle=OpenProcess(PROCESS_ALL_ACCESS,TRUE,id); 
		DWORD   exitcode=0; 
		TerminateProcess(myhandle,exitcode); 
		return   TRUE; 
	} 
	return   FALSE; 
}

DWORD  CMainUIDlg::GetProcessIdFromName(LPCTSTR   name) 
{ 

	PROCESSENTRY32   pe; 
	DWORD   id   =   0; 
	HANDLE   hSnapshot   =   CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0); 
	pe.dwSize   =   sizeof(PROCESSENTRY32); 
	if(   !Process32First(hSnapshot,&pe)   ) 
		return   0; 
	CString   name1,name2; 
	do 
	{ 
		pe.dwSize   =   sizeof(PROCESSENTRY32); 
		if(   Process32Next(hSnapshot,&pe)==FALSE   ) 
			break; 
		name1=pe.szExeFile; 
		name2=name; 
		name1.MakeUpper(); 
		name2.MakeUpper(); 
		if(name1 == name2) 
		{ 
			id   =   pe.th32ProcessID; 
			break; 
		} 
	}   while(1); 
	CloseHandle(hSnapshot); 
	return   id; 
}

const char* CMainUIDlg::CStrToChar(CString strSrc)
{
#ifdef UNICODE
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, strSrc.GetBuffer(0), -1, NULL, 0, NULL, FALSE);
	char *psText;
	psText = new char[dwNum];
	if (!psText)
		delete []psText;
	WideCharToMultiByte(CP_OEMCP, NULL, strSrc.GetBuffer(0), -1, psText, dwNum, NULL, FALSE);
	return (const char*)psText;
#else
	return (LPCTSTR)strSrc;
#endif
}




void CMainUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CMainUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMainUIDlg::OnDestroy()
{

	__super::OnDestroy();
}
