#pragma once


// CDlgFourEqual 对话框

class CDlgFourEqual : public CDialog
{
	DECLARE_DYNAMIC(CDlgFourEqual)

public:
	CDlgFourEqual(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgFourEqual();

// 对话框数据
	enum { IDD = IDD_SHUANGSEQIU_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg void OnClose();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();


	//初始化列表头
	void InitListHeader();

	//获取相等的平码
	vector<int> GetEqualData(vector<sShuangSeQiu>& DataList);

private:
	CListCtrlEx m_ListCtrl;
	BOOL      m_IsInitData;
};
