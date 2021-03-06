#pragma once
/************************************************************
*                                                           *
*此文件用于数据的管理 2012年02月22日         谭军红         *
*                                                           *
*                                                           *
*************************************************************/

#include "DataDefine.h"
#include <vector>
#include <map>
using std::map;
using std::vector;


class CDataManageCenter
{
public:

	//获取数据管理实例
	static CDataManageCenter* GetInstance();

	//获取双色球列表
	vector<sShuangSeQiu>* GetDataList();

	//获取按出号顺序双色球列表 
	vector<sShuangSeQiu>* GetDataListByChuHao();

	//获取双色球列表
	vector<sShuangSeQiu> GetSpecialDataList(DWORD Data1,DWORD Data2,DWORD Data3,DWORD Data4,CString Str=_T(""));

	//获取4个双色球相同的列表
	map<CString,sEqualShuangSeQiu> GetFourDataEqualList();

	//获取3个双色球相同的列表
	map<CString,sEqualShuangSeQiu> GetThreeDataList();

    //预测计算方法
	map<CString,sYuCeShuangSeQiu> GetDataBySuanFa();

	//通过篮球搜索数据
	vector<sShuangSeQiu> SearchDataLanQiu(DWORD Data1,DWORD Data2,DWORD Data3,DWORD Data4,CString Str=_T(""));

	//通过龙头搜索数据
	vector<sShuangSeQiu> SearchDataLongTou(DWORD Data1,DWORD Data2,DWORD Data3,DWORD Data4,CString Str=_T(""));

	//通过尾值搜索数据
	vector<sShuangSeQiu> SearchDataWeiZhi(DWORD Data1,DWORD Data2,DWORD Data3,DWORD Data4,CString Str=_T(""));

	//搜索预测结果
	map<CString,sYuCeShuangSeQiu> SearchDataBySuanFa(DWORD Data1,DWORD Data2,DWORD Data3,DWORD Data4,CString QiShu=_T(""));


	//搜索红球
	vector<sShuangSeQiu> SearchHongQiu(DWORD HongQiu);

	//搜索红球
	vector<sShuangSeQiu> SearchHongQiu(vector<sShuangSeQiu>& DataList,DWORD HongQiu);

	//搜索篮球
	vector<sShuangSeQiu> SearchLanQiu(DWORD LanQiu);
	
	//获取纵向差值
	vector<sZongXiangChaZhi>* GetZongXiangChaZhi();

	//获取横向差值
	vector<sHengXiangChaZhi>* GetHengXiangChaZhi();

	//获取连号红球
	vector<sShuangSeQiu>* GetLianHaoHongQiu();

	//获取连号篮球
	vector<sShuangSeQiu>* GetLianHaoLanQiu();

	//搜索纵向差值
	vector<sZongXiangChaZhi> SearchZongXiangChaZhi(DWORD Value);

	//搜索横向差值
	vector<sHengXiangChaZhi> SearchHengXiangChaZhi(DWORD Value);

	//获取连号红球
	vector<sShuangSeQiu> SearchLianHaoHongQiu(DWORD Value);

	//获取连号篮球
	vector<sShuangSeQiu> SearchLianHaoLanQiu(DWORD Value);

	//从文件加载数据
	bool LoadDataFromFile(CString FilePath,bool IsChuHaoXunXu=false,bool IsClean=true);

	//从文件加载数据
	bool LoadDataFromFile(CString FilePath,vector<sShuangSeQiu>& QiuList);

	//保存预测数据到文件中
	void SaveDataToFile(sYuCeShuangSeQiu& Data);

	//设置搜索标志
	void SetSearchFlag(BOOL Flag) { m_SearchFlag = Flag;}

	//保存统计数据到csv文件中
	void SaveDataToCSVFile();

	//保存统计五期以内和五期以外数据到txt文件中
	void SaveFiveDataToTxtFile();

	//保存29组统计数据到txt文件中
	void Save29DataToTxtFile();

	//获取AC差值
	int GetACCount(sShuangSeQiu& ShuangSeQiu);

	//获取胆组数据
	vector<map<int,CString>>* GetDanZuDataList();

public:
	
	//通过期数获取双色球数据
	bool GetShuangSeQiuData(CString QiShu,sShuangSeQiu& Data);

	//球是否在红球中
	static bool IsHongQiuInData(sShuangSeQiu QiuData,int Data,bool IsV=false);
	
	//球是否在红球前三中
	static bool IsHongQiuInQianSanData(sShuangSeQiu QiuData,int Data,bool IsV=false);

	//球是否在红球后三中
	static bool IsHongQiuInHouSanData(sShuangSeQiu QiuData,int Data,bool IsV=false);


	//球是否在红球合中
	static bool IsHongQiuInHeData(sShuangSeQiu QiuData,int Data,bool IsV=false);

	//球是否在红球合前三中
	static bool IsHongQiuInHeQianSanData(sShuangSeQiu QiuData,int Data,bool IsV=false);

	//球是否在红球合后三中
	static bool IsHongQiuInHeHouSanData(sShuangSeQiu QiuData,int Data,bool IsV=false);


	//球是否在红球差中
	static bool IsHongQiuInChaData(sShuangSeQiu QiuData,int Data,bool IsV=false);

	//球是否在红球差中
	static bool IsHongQiuInChaQianSanData(sShuangSeQiu QiuData,int Data,bool IsV=false);

	//球是否在红球差中
	static bool IsHongQiuInChaHouSanData(sShuangSeQiu QiuData,int Data,bool IsV=false);



	//球是否在位数中
	static bool IsHongQiuWeiData(sShuangSeQiu QiuData,int Data,int WeiShu,bool IsV=false);

	//球是否在位数和中
	static bool IsHongQiuWeiHeData(sShuangSeQiu QiuData,int Data,int WeiShu,bool IsV=false);

	//球是否在位数差中
	static bool IsHongQiuWeiChaData(sShuangSeQiu QiuData,int Data,int WeiShu,bool IsV=false);

	//球是否在红球区间中
	static bool IsHongQiuQuJianInData(sShuangSeQiu QiuData,int BeginData,int EndData,int WeiShu,bool IsV=false);

	//球是否等于极距中
	static bool IsHongJiJuInData(sShuangSeQiu QiuData,int Data);

	//红球同出
	static bool IsHongQiuTongChu(sShuangSeQiu QiuData,vector<int> Data,bool IsV=false);

	//球是否在篮球中
	static bool IsLanQiuInData(sShuangSeQiu QiuData,int Data,bool IsV=false);

	//判断数据是否为合数
	static bool IsHeShuData(int Data);

	//获取质数个数
	static int GetZhiShuCount(sShuangSeQiu QiuData);

	static CString GetDataStr(int Data,bool IsTrue=true,bool IsV=false);

	//// 判断点位是否在红球中
	//static bool IsDianHongQiuInData(sShuangSeQiu QiuData,int Data,int Offset=1);

	////获取点位字符串
	//static CString GetDianDataStr(int Data,bool IsTrue=true,int Offset=1);


//网络数据
public:

	//获取网易数据信息
	vector<sWangYiDataInfo>* GetWangYiDataInfo();

	//获取中彩数据信息
	vector<sZhongCaiDataInfo>* GetZhongCaiDataInfo();

	//导入网络分析数据
	void LoadNetData(eLoadDataType Type=LOAD_ALL_DATA);

private:

	//解析数据
	void ParseData(CString& StrData,vector<sShuangSeQiu>& VectorData);

	//解析外部数据
	void ParseWaiBuData(CString& StrData,vector<sShuangSeQiu>& VectorData);

	//通过字符串获取双色球
	sShuangSeQiu GetShuangSeQiuByStr(CString& StrData);

	//初始化横向差值
	void InitHengXiangChaZhi(vector<sShuangSeQiu>& ShuangSeQiuList);

	//初始化纵向差值
	void InitZongXiangChaZhi(vector<sShuangSeQiu>& ShuangSeQiuList);

	//初始化连号红球
	void InitLianHaoHongQiu(vector<sShuangSeQiu>& ShuangSeQiuList);

	//初始化连号篮球
	void InitLianHaoLanQiu(vector<sShuangSeQiu>& ShuangSeQiuList);


	
	//获取尾数预测参数
	int GetWeiZhiParam(sShuangSeQiu& ShuangSeQiu);


	/////初始29组数/////////////

	//初始化29组数据
	void Init29Data();

	//初始一组数据
	void InitOneData(sData29 &Data);

	CDataManageCenter(void);

	~CDataManageCenter(void);

private:

	//导入中彩数据
	void LoadZhongCaiData();

	//导入网易数据
	void LoadWangYiData();

	//导入360数据
	void Load360Data();

	//导入澳客数据
	void LoadAoKeData();

	//获取文件字符串
	CString GetFileStr(CString FilePath);

	//解析文件字符串
	void PaseFileStr(CString Str,vector<CString>& DataList);
	
private:
	vector<sShuangSeQiu>        m_ShuangSeQiuList;        //双色球值列表
	vector<sShuangSeQiu>        m_ShuangSeQiuChuHaoList;  //双色球球出号顺序列表
	vector<sHengXiangChaZhi>    m_HengXiangChaZhiList;    //双色球横向差值列表
	vector<sZongXiangChaZhi>    m_ZongXiangChaZhiList;    //双色球纵向差值列表
	vector<sShuangSeQiu>        m_LianHaoHongQiu;         //双色球连号红球数值
	vector<sShuangSeQiu>        m_LianHaoLanQiu;          //双色球连号篮球数值
	vector<sData29>             m_Data29;                 //29组数据
	BOOL                        m_SearchFlag;             //搜索标志
	vector<map<int,CString>>    m_DanZu;                  //胆组数据


	//网络数据
	vector<sWangYiDataInfo>     m_WangYiDataInfo;         //网易数据
	vector<sZhongCaiDataInfo>   m_ZhongCaiDataInfo;       //中彩数据描述
};
