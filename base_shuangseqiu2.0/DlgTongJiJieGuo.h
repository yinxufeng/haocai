#pragma once

class CDlgTongJiJieGuo : public CDialog
{
	DECLARE_DYNAMIC(CDlgTongJiJieGuo)

public:
	CDlgTongJiJieGuo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTongJiJieGuo();

	virtual BOOL OnInitDialog();

	afx_msg void OnClose();

	void SetTongJieData(vector<sShuangSeQiu>& DataList);

	//统计
	void TongJi();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()

private:
	vector<sShuangSeQiu> m_TongJiDataList;
	int                  m_JiShuQi[QIU_COUNT];
	bool                 m_IsInitData;
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	
};
