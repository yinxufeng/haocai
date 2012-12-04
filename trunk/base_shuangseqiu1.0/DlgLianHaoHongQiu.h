#pragma once
#include "afxwin.h"


//极限数据描述
struct sDataInfo
{
	int          m_Data;      //数据
	CString      m_QiShu;     //期数
	COLORREF     m_Color;     //颜色值
};

//定义数据类型
enum eYanDataType
{
	TYPE_WEI_QIANSAN_HOUSAN,          //前三后三尾
	TYPE_HE_QIANSAN_HOUSAN,            //前三后三合 
	TYPE_CHA_QIANSAN_HOUSAN,          //前三后三差
	TYPE_WEI_SHUANG_DAN,              //双胆尾
	TYPE_HE_SHUANG_DAN,               //双胆合
	TYPE_CHA_SHUANG_DAN,              //双胆差
};

//定义数据总类型
enum eYanType
{
	TYPE_WEI,         //尾
	TYPE_HE,          //合
	TYPE_CHA,         //差
};

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

	//初始化Combox
	void InitCombox();

	//三胆尾换算
	int TransDataByInt(CString DataStr,int Data2 );

	//三胆尾换算
	int TransDataByInt(CString DataStr);

	//双胆尾换算
	int TransDataByInt(CString DataStr,int Data2 ,int Data3);

	CString TransData(CString DataStr,float Data);

	//填充颜色
	void FillItemStyleColor(sItemStyle& Style,bool IsTrue1,bool IsTrue2);

private:

	//填充双胆尾数据
	void FillShuangDanList(int FillType);

	//填充三胆尾数据
	void FillSanDanList(int FillType);

	//填充数据
	void FillDataByType(int FillType,bool FillWay,int& List2Index);

	//填充三胆尾数据
	void FillSanDanDataByType(int FillType,bool FillWay,int& List2Index);

	//填充数据
	void FillShuangDanListData(CListCtrlEx& ListCtrl,vector<sShuangSeQiu>* DataList,int Data,int Index, int& CololIndex);

	//填充数据
	void FillSanDanListData(CListCtrlEx& ListCtrl,vector<sShuangSeQiu>* DataList,int Data,int Index, int& CololIndex);

	//获取三胆填充风格
	sItemStyle GetSanDanItemStyle(int FillType,vector<sShuangSeQiu>* DataList,int Index,int Data);

private:
	CListCtrlEx m_ListCtrl;         //显示前三后三
	CListCtrlEx m_ListCtrl2;        //显示尾三 合三 走势
	CListCtrlEx m_ListCtrl3;        //显示双胆
	BOOL      m_IsInitData;
	int       m_CompareShuangDanType; //双胆比较方式
	int       m_CompareSanDanType;    //三胆尾比较方式
	int       m_ParamData;            //参数
	CComboBox m_ComboBox;

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
	afx_msg void OnBnClickedQianSanWeiBtn();
	afx_msg void OnBnClickedHouSanWeiBtn();
	afx_msg void OnBnClickedQianSanHeBtn();
	afx_msg void OnBnClickedHouSanHeBtn();
	afx_msg void OnBnClickedHouSanHeBtn2();
	afx_msg void OnBnClickedExecBtn();
	afx_msg void OnBnClickedJixianBtn();

public:
	
	//寻找极限基数线程
	static DWORD WINAPI LookJiXianThread(LPVOID lpVoid);

	//计算数据
	void FillMapData(map<int,vector<sDataInfo>>& MapData,int StartPos,int OffsetPos,eYanType YanType,eYanDataType DataType,int Param);

	//是否是需要的数据类型
	bool IsWantData(vector<sDataInfo>& VecData,eYanDataType DataType);

	//填充极限数据
	void FillJiXianDataList(eYanDataType DataType);

	//获取数据颜色值
	COLORREF GetDataColor(eYanDataType Type,sShuangSeQiu QiuData,int Data,bool IsV=false);

	//过滤重复数据
	void FilterMapData(map<int,map<int,vector<sDataInfo>>>& MapData);

	//判断两个vector数据相等
	bool IsEqualVector(vector<sDataInfo>& Vec1,vector<sDataInfo>& Vec2);



private:
	map<int,map<int,vector<sDataInfo>>>  m_AllData;       //自动搜索极限数据
	int                                  m_Flag;            
};
