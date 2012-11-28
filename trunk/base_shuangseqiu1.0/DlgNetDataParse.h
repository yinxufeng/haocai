#pragma once


// CDlgNetDataParse 对话框

//网络数据分析

class CDlgNetDataParse : public CDialog
{
	DECLARE_DYNAMIC(CDlgNetDataParse)

public:
	CDlgNetDataParse(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgNetDataParse();

// 对话框数据
	enum { IDD = IDD_SHUANGSEQIU_NET_PARSE };

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg void OnClose();
	
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();

	

	//初始化列表头
	void InitListHeader();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedZhongcaiHongBtn();
	afx_msg void OnBnClickedZhongcailanBtn();
	afx_msg void OnBnClickedAoke360Btn();
	afx_msg void OnBnClickedWangyiBtn();


private:

	//获取颜色值
	COLORREF GetColor(int Data,bool IsDefault=false);

private:

	CListCtrlEx m_ListCtrl;
	BOOL      m_IsInitData;
};
