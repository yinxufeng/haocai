#pragma once

//极限围栏

class CDlgJiXianWeiLan : public CDialog
{
	DECLARE_DYNAMIC(CDlgJiXianWeiLan)

public:
	CDlgJiXianWeiLan(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgJiXianWeiLan();

// 对话框数据
	enum { IDD = IDD_DLG_WEI_LAN };


	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg void OnClose();
	
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();

	//初始化列表头
	void InitListHeader();


	//获取颜色值
	COLORREF GetColor(int Data);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


private:
	CListCtrlEx m_ListCtrl;
	BOOL        m_IsInitData;
};
