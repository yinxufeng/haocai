
// GetMailDataDlg.h : 头文件
//

#pragma once

#include "HtmlCtrl.h"
#include <map>
using std::map;

// CGetMailDataDlg 对话框
class CGetMailDataDlg : public CDialog
{
// 构造
public:
	CGetMailDataDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GETMAILDATA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	//创建新HTML控件
	void CreateNewHtmlCtrl(CString URL,CString PostData);

	//请求数据线程
	static DWORD WINAPI RequestDataInfoThread(LPVOID lpVoid);

	//解析数据
	static void PaseText(CString Text, vector<CString>& List);

	//解析email 
	static void PaseEmail(CString Text,map<CString,int>& EmailMap);

	//解析文件
	static void PaseEmailTxt(CString Text,map<CString,int>& EmailMap);

	LRESULT OnParseOverMsg(WPARAM wParam,LPARAM lParam);

public:
	afx_msg void OnBnClickedSearchBtn();


private:
	CHtmlCtrl* m_HtmlCtrl;
};
