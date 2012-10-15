#pragma once


// CThreeEqualDlg 对话框

class CThreeEqualDlg : public CDialog
{
	DECLARE_DYNAMIC(CThreeEqualDlg)

public:
	CThreeEqualDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CThreeEqualDlg();

// 对话框数据
	enum { IDD = IDD_SHUANGSEQIU_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg void OnClose();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();


	//初始化列表头
	void InitListHeader();

private:
	CListCtrlEx m_ListCtrl;
	BOOL      m_IsInitData;
};
