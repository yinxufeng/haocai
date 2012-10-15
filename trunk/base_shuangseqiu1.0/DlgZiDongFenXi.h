#pragma once


// CDlgZiDongFenXi 对话框

class CDlgZiDongFenXi : public CDialog
{
	DECLARE_DYNAMIC(CDlgZiDongFenXi)

public:
	CDlgZiDongFenXi(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgZiDongFenXi();

// 对话框数据
	enum { IDD = IDD_SHUANGSEQIU_DIALOG8 };

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();

	//初始化列表头
	void InitListHeader();

	void OnClose();

	void OnShowWindow(BOOL bShow, UINT nStatus);


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private :

	CListCtrlEx m_ListCtrl;
	BOOL      m_IsInitData;
};
