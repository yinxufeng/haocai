
// ShuangSeQiuDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "RedBallDlg.h"
#include "DlgLianHaoHongQiu.h"
#include "DlgLianHaoLanQiu.h"
#include "DlgHengXiangChaZhi.h"
#include "DlgZongXiangChaZhi.h"
#include "DlgTongJiJieGuo.h"
#include "DlgFourEqual.h"
#include "ThreeEqualDlg.h"
#include "DlgShiFaDingHong.h"
#include "DlgZiDongFenXi.h"
#include "DlgTeZongHeFenXi.h"
#include "DlgDingHongWei.h"
#include "DlgNetDataParse.h"
#include "DlgJiXianWeiLan.h"
#include "afxwin.h"


struct sShuangSeQiuInfo
{
	CString m_QiHao;
	CString m_KaiJiangHao;
	CString m_ChuQiuShuanXu;
	CString m_BenQiXiaoLiang;
	CString m_JiangChiGunCun;
	CString m_OtherInfo;
};


//显示杀号类型
enum eShowShaType
{
	TYPE_SHA_BAI_WEI,       //杀百位图
	TYPE_SHA_SHI_WEI,       //杀十位图
	TYPE_SHA_GE_WEI,        //杀个位图
	TYPE_SHA_HE_WEI,        //杀和尾图
	TYPE_SHA_KUA_WEI,       //杀跨位图
};


class CShuangSeQiuDlg : public CDialog
{
// 构造
public:
	CShuangSeQiuDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SHUANGSEQIU_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedLoadDataBtn();
	afx_msg void OnBnClickedRedBallBtn();
	afx_msg void OnBnClickedSearchBtn();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedBlueBallBtn2();
	afx_msg void OnBnClickedBlueBallBtn4();
	afx_msg void OnBnClickedBlueBallBtn3();
	afx_msg void OnBnClickedBlueBallBtn6();
	afx_msg void OnBnClickedSearchBtn2();
	afx_msg void OnBnClickedSearchBtn3();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton12();
		
	afx_msg void OnCbnSelchangeCombo1();

	//插入和设置文本
	void InsertAndSetText(int Row,sShuangSeQiu& ShuangSeQiu);

	//插入和设置文本
	void InsertAndSetText2(int Row,sShuangSeQiu& ShuangSeQiu,int* pCount=NULL);
	
	//插入和设置文本
	void InsertAndSetText3(int Row,sShuangSeQiu& ShuangSeQiu,int* pCount=NULL);


	//填充数据
	void FillShowData(eShowShaType Type);


	afx_msg void OnBnClickedButton11();

private:

	//初始化列表头
	void InitListHeader();

	//初始化杀类型
	void InitShaMap();

	//导入网络分析数据
	void LoadNetData();

	//显示列表
	void ShowListCtrl(int ShowIndex);

private:

	CListCtrlEx m_ListCtrl;
	CListCtrlEx m_ListCtrl2;
	CListCtrlEx m_ListCtrl3;
	CRedBallDlg m_RedBallDlg;

	CDlgLianHaoHongQiu   m_DlgLianHaoHongQiu;
	CDlgLianHaoLanQiu    m_DlgLianHaoLanQiu;
	CDlgDingHongWei      m_DlgDingHongWei;
	
	CDlgHengXiangChaZhi  m_DlgHengXiangChaZhi;
	CDlgZongXiangChaZhi  m_DlgZongXiangChaZhi;

	CDlgTongJiJieGuo     m_DlgTongJiJieGuo;

	CDlgFourEqual        m_DlgFourEqual;
	CThreeEqualDlg       m_DlgThreeEqual;
	CDlgShiFaDingHong    m_DlgShiFaDingHong;
	CDlgZiDongFenXi      m_DlgZiDongFenXi;
	CDlgTeZongHeFenXi    m_DlgTeZongHeFenXi;
	CDlgNetDataParse     m_DlgNetDataParse;
	CDlgJiXianWeiLan     m_DlgJiXianWeiLan;

	vector<sShuangSeQiu> m_ResultDataList;

	CButton m_CheckBtn;
	CComboBox m_ComboBox;
	bool      m_IsShowByChuQiu;
	CComboBox m_ShaComboBox;
	map<CString,int> m_MapList;


public:
	afx_msg void OnBnClickedBlueBallBtn();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedBlueBallBtn5();
	afx_msg void OnBnClickedLoadDataBtn2();

	static DWORD WINAPI RequestDataInfoThread(LPVOID lpVoid);

    //爬取网易数据
	static DWORD WINAPI RequestDataWangYiThread(LPVOID lpVoid);

	 //爬取中彩擂台数据
	static DWORD WINAPI RequestDataZhongCaiThread(LPVOID lpVoid);

	//爬取澳客数据
	static DWORD WINAPI RequestDataAoKeThread(LPVOID lpVoid);
	
	//爬取360数据
	static DWORD WINAPI RequestData360Thread(LPVOID lpVoid);


	//获取HTTP数据
	static CString GetHttpData(CString Url);

	static DWORD WINAPI CombineDataThread(LPVOID lpVoid);


	//解析数据
	static bool PaseInfo(CString& Txt,sShuangSeQiuInfo& Info);

	//解析网页数据
	static bool PaseWangYiInfo(CString& Txt,sWangYiDataInfo& Info);
	static bool PaseWangYiInfo(CString& Txt,sWangYiDataInfo& Info,CString ParseFlag);

	//解析中彩擂台数据
	static bool PaseZhongCaiInfo(CString& Txt,vector<sZhongCaiDataInfo>& Info,int QiShuInt);
	static bool PaseZhongCaiInfo(CString& Txt,sZhongCaiDataInfo& Info,CString ParseFlag);

	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton16();


	//解析数据
	static void ParseData(CString& StrData,map<CString,vector<int>>& MapData);

	//获取数据
	static vector<int> GetDataList(CString& StrData);

	//组合数据
	static void Combine(map<CString,vector<int>> MapData);
	
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnBnClickedButton17();
	afx_msg void OnBnClickedButton18();
};
