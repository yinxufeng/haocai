#pragma once


// CDlgDrawTiaoXing 对话框

class CDlgDrawTiaoXing : public CDialog
{
	DECLARE_DYNAMIC(CDlgDrawTiaoXing)

public:
	CDlgDrawTiaoXing(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgDrawTiaoXing();

// 对话框数据
	enum { IDD = IDD_DRAW_TIAO_XING_DLG };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
