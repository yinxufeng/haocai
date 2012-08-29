#pragma once
#include "afxwin.h"


// CDlgWeiHong 对话框

class CDlgWeiHong : public CDialog
{
	DECLARE_DYNAMIC(CDlgWeiHong)

public:
	CDlgWeiHong(CWnd* pParent = NULL);   // 标准构造函数

	virtual ~CDlgWeiHong();

// 对话框数据
	enum { IDD = IDD_WEIHONG_DLG };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	//初始化列表头
	void InitListHeader();

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg void OnClose();
	
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();

	afx_msg void OnCbnSelchangeCombo1();

private:
	CListCtrlEx m_ListCtrl;
	BOOL      m_IsInitData;
	CComboBox m_ComboBox;
	vector<sData29> m_Result;

public:
	afx_msg void OnBnClickedButton1();

	void InsertTextToList(int InsertIndex,sData29& Data);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton2();
};
