#pragma once


// CDlgLianHaoHongQiu 对话框

class CDlgLianHaoHongQiu : public CDialog
{
	DECLARE_DYNAMIC(CDlgLianHaoHongQiu)

public:
	CDlgLianHaoHongQiu(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgLianHaoHongQiu();

// 对话框数据
	enum { IDD = IDD_SHUANGSEQIU_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg void OnClose();
	
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();

	//初始化列表头
	void InitListHeader();

	//三胆尾换算
	int TransDataByInt(CString DataStr,int Data2 );

	//双胆尾换算
	int TransDataByInt(CString DataStr,int Data2 ,int Data3);

	CString TransData(CString DataStr,float Data);

	//填充颜色
	void FillItemStyleColor(sItemStyle& Style,bool IsTrue1,bool IsTrue2);

private:

	//填充双胆尾数据
	void FillShuangDanList(int FillType);

	//填充数据
	void FillDataByType(int FillType,bool FillWay,int& List2Index);

	//填充数据
	void FillShuangDanListData(CListCtrlEx& ListCtrl,vector<sShuangSeQiu>* DataList,int Data,int Index, int& CololIndex);

private:
	CListCtrlEx m_ListCtrl;         //显示前三后三
	CListCtrlEx m_ListCtrl2;        //显示尾三 合三 走势
	CListCtrlEx m_ListCtrl3;        //显示双胆
	BOOL      m_IsInitData;
	int       m_CompareShuangDanType; //双胆比较方式
public:
	afx_msg void OnBnClickedSearchBtn();

	void AddFlag(CString& Str,bool IsTrue);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedWeiFenBtn();
	afx_msg void OnBnClickedHeFenBtn();


	
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedWeishuShuangdanBtn();
	afx_msg void OnBnClickedHeshuShuangdanBtn();
	afx_msg void OnBnClickedChashuShuangdanBtn();
};
