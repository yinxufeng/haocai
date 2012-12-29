// suoshuiDlg.h : 头文件
//

#pragma once
#include <map>
#include <vector>
using namespace std;

// CsuoshuiDlg 对话框
class CsuoshuiDlg : public CDialog
{
// 构造
public:
	CsuoshuiDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SUOSHUI_DIALOG };

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
public:
	afx_msg void OnBnClickedOk();

	//解析数据
	void ParseData(CString& StrData,map<CString,vector<int>>& MapData);

	//获取数据
	vector<int> GetDataList(CString& StrData);

	//组合数据
	void Combine(map<CString,vector<int>> MapData);

	//组合数据
	void Combine3D(map<CString,vector<int>> MapData);

	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedOk5();
};
