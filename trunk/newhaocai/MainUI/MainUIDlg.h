

#pragma once

#include "webbrowser2.h"
#include "Markup.h"
#include <vdmdbg.h>
#include <Dbt.h>
#include <SetupAPI.h>

#include <MSHTML.H>

class CMainUIDlg : public CDialog
{
public:

	CMainUIDlg(CWnd* pParent = NULL);							// standard constructor
	enum { IDD = IDD_PCSUITE_DIALOG };
protected:

	virtual void DoDataExchange(CDataExchange* pDX);			// DDX/DDV support

public:

	void	SetRoundWindows(int Width, int Height, int round);  //设置对话框圆角
	void	MoveMainDlg(int iArg1 , int iArg2);					//移动主对话框
	BOOL	IsAppRun(CString   AppName);						//结束进程
	DWORD   GetProcessIdFromName(LPCTSTR   name);				//获得进程中的ID通过进程名
	const char* CStrToChar(CString strSrc);						//将Cstring 转换成 const char *

protected:

	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDocumentCompleteExplorerMain(LPDISPATCH pDisp, VARIANT FAR* URL);

	DECLARE_EVENTSINK_MAP()
	DECLARE_MESSAGE_MAP()	

private:

	IHTMLDocument2*  m_pIHTMLDoc;            //HTML指针
	CWebBrowser2	 m_wndWeb;               //Web内核
	
public:
	afx_msg void OnDestroy();
};