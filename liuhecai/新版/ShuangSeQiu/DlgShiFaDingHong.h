#pragma once
#include "afxwin.h"
#include "FormulaCenter.h"

// CShiFaDingHong 对话框

class CDlgShiFaDingHong : public CDialog
{
	DECLARE_DYNAMIC(CDlgShiFaDingHong)

public:
	CDlgShiFaDingHong(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgShiFaDingHong();

// 对话框数据
	enum { IDD = IDD_SHUANGSEQIU_DIALOG7 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg void OnBnClickedSearchBtn();

	afx_msg void OnClose();
	
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();

	//初始化列表头
	void InitListHeader();

	void FillData(vector<sFormulaInfo>& FormulList);

private:
	CListCtrlEx m_ListCtrl;
	BOOL      m_IsInitData;
	CComboBox m_ComboBox;
	int       m_CurrentIndex;
	vector<sFormulaInfo> m_FormulaInfoList;
	
public:
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedPrevBtn();
	afx_msg void OnBnClickedNextBtn();

	void UpdateBtnStatus();
};
