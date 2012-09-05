#pragma once


// CDlgLianHaoLanQiu 对话框

class CDlgLianHaoLanQiu : public CDialog
{
	DECLARE_DYNAMIC(CDlgLianHaoLanQiu)

public:
	CDlgLianHaoLanQiu(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgLianHaoLanQiu();

// 对话框数据
	enum { IDD = IDD_SHUANGSEQIU_DIALOG2 };

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

public:
	afx_msg void OnBnClickedSearchBtn();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);


};
