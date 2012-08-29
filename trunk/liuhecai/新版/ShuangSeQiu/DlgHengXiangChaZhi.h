#pragma once


// CDlgHengXiangChaZhi 对话框

class CDlgHengXiangChaZhi : public CDialog
{
	DECLARE_DYNAMIC(CDlgHengXiangChaZhi)

public:
	CDlgHengXiangChaZhi(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgHengXiangChaZhi();

// 对话框数据
	enum { IDD = IDD_SHUANGSEQIU_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg void OnClose();
	
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();

	//初始化列表头
	void InitListHeader();

	//获取路数
	int GetLuShu(int Data);

	CString GetDataStr(int LuShu);

private:
	CListCtrl m_ListCtrl;
	BOOL      m_IsInitData;
public:
	afx_msg void OnBnClickedSearchBtn();
};
