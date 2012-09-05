#pragma once


// CDlgZongXiangChaZhi 对话框

class CDlgZongXiangChaZhi : public CDialog
{
	DECLARE_DYNAMIC(CDlgZongXiangChaZhi)

public:
	CDlgZongXiangChaZhi(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgZongXiangChaZhi();

// 对话框数据
	enum { IDD = IDD_SHUANGSEQIU_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	
	afx_msg void OnClose();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();

	//初始化列表头
	void InitListHeader();


	DECLARE_MESSAGE_MAP()



private:
	CListCtrlEx m_ListCtrl;
	BOOL      m_IsInitData;
	
public:
	afx_msg void OnBnClickedSearchBtn();
};
