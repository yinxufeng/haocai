#pragma once

#include <vector>
#include <map>
using std::vector;
using std::map;

//公式管理中心

//公式类型
enum eFormulaType
{
	FORMULA_NULL                ,     //空类型

	//篮球相关类型
	FORMULA_SHA_LAN             ,     //杀篮球
	FORMULA_SHA_LAN_WEI         ,     //杀蓝尾
	FORMULA_SHA_LAN_LUSHU       ,     //杀篮球路数
	FORMULA_SHA_LAN_FANWEI      ,     //杀篮球范围 

	FORMULA_DING_LAN            ,     //定蓝球
	FORMULA_DING_LAN_WEI        ,     //定篮球尾
	FORMULA_DING_LAN_FANWEI     ,     //定蓝球范围
	FORMULA_DING_LAN_LUSHU      ,     //定篮球路数

	//龙头相关类型
	FORMULA_SHA_LONG_TOU        ,     //杀龙头
	FORMULA_SHA_LONG_TOU_WEI    ,     //杀龙头V
	FORMULA_SHA_LONG_TOU_LUSHU  ,     //杀龙头路数

	FORMULA_DING_LONG_TOU       ,     //定龙头范围

	//凤尾相关类型
	FORMULA_SHA_FENG_WEI        ,     //杀凤尾
	FORMULA_SHA_FENG_WEI_WEI    ,     //杀凤尾V
	FORMULA_SHA_FENG_WEI_LUSHU  ,     //杀凤尾路数

	FORMULA_DING_FENG_WEI       ,     //定凤尾范围

	//红球相关类型
	FORMULA_SHA_HONG            ,    //杀红球
	FORMULA_SHA_HONG_WEI        ,    //杀红球V

	FORMULA_DING_HONG_DIAN      ,    //红球点位
	FORMULA_DING_HONG_WEI       ,    //定红球V
};

//公式描述数据
struct sFormulaData
{
	CString m_Data;            //描述数据
	bool    m_IsTrue;          //是否正确
};

//公式数据描述
struct sFormulaInfo
{
	CString                m_FormulaName;          //公式名字
	eFormulaType           m_FormulaType;          //公式类型
	vector<sFormulaData>   m_DataList;             //数据
	int                    m_MaxLianCuoCount;      //最大连错次数
	int                    m_MaxLianDuiCount;      //最大连对次数
	int                    m_MinLianCuoCount;      //最小连错次数
	int                    m_MinLianDuiCount;      //最小连对次数 
	int                    m_ErrorCount;           //错误次数
	map<CString,int>       m_MapErrorInfo;         //错误信息
	bool                   m_LastStatus;           //最后一次公式状态

	sFormulaInfo()
	{
		 m_MaxLianCuoCount = 0;
		 m_MaxLianDuiCount = 0;
		 m_MinLianCuoCount = 0;
		 m_MinLianDuiCount = 0;

		 m_ErrorCount      = 0;
		 m_LastStatus      = true;
		 m_FormulaType     = FORMULA_NULL;
	}
};


class CFormulaCenter
{

public:

	CFormulaCenter(void);

	~CFormulaCenter(void);

	//获取公式信息
	vector<sFormulaInfo> GetFormulaInfoByType(eFormulaType Type);

	//公式运算
	void RunFormula();

private:

	//运行杀红公式
	void ExecShaHongFormula();

private:

	map<CString,vector<sFormulaInfo>> m_MapFormulaInfo;   //公式数据缓存
};
