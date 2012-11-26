#pragma once


//定红V对话框

class CDlgDingHongWei : public CDialog
{
	DECLARE_DYNAMIC(CDlgDingHongWei)

public:
	CDlgDingHongWei(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgDingHongWei();

// 对话框数据
	enum { IDD = IDD_SHUANGSEQIU_DIALOG10 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnClose();
	
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();

	//初始化列表头
	void InitListHeader();

	//获取颜色值
	COLORREF GetColor(int Data);

private:
	CListCtrlEx m_ListCtrl;
	BOOL        m_IsInitData;
};
