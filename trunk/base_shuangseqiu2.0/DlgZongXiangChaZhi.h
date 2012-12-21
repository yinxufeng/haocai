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


	//填充区域数据
	void FillQuData(sShuangSeQiu Data,int* DataArray,int DataCount);

	//填充区域数据
	void FillQuData(sShuangSeQiu Data,map<int,CString> MapData,int* DataArray,int DataCount);

	DECLARE_MESSAGE_MAP()

	//获取区号数据
	CString GetQuDataStr(int QuHao);


private:
	CListCtrlEx m_ListCtrl;
	BOOL      m_IsInitData;
	BOOL      m_IsLiShan;
	
public:
	afx_msg void OnBnClickedSearchBtn();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
};
