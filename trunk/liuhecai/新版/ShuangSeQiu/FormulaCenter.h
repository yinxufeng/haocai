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

	//特码相关类型
	FORMULA_SHA_LAN             ,     //杀特码
	FORMULA_SHA_LAN_WEI         ,     //杀蓝尾
	FORMULA_SHA_LAN_LUSHU       ,     //杀特码路数
	FORMULA_SHA_LAN_FANWEI      ,     //杀特码范围 

	FORMULA_DING_LAN            ,     //定特码
	FORMULA_DING_LAN_WEI        ,     //定特码尾
	FORMULA_DING_LAN_FANWEI     ,     //定特码范围
	FORMULA_DING_LAN_LUSHU      ,     //定特码路数

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

	//平码相关类型
	FORMULA_SHA_HONG            ,    //杀平码
	FORMULA_SHA_HONG_WEI        ,    //杀平码V

	FORMULA_DING_HONG_DIAN      ,    //平码点位
	FORMULA_DING_HONG_WEI       ,    //定平码V
};

//公式描述数据
struct sFormulaData
{
	CString m_Data;            //描述数据
	bool    m_IsTrue;          //是否正确
	CString m_QiShu;           //期数

	sFormulaData()
	{
		m_IsTrue = true;
	}
};

//公式数据描述
struct sFormulaInfo
{
	CString                m_FormulaName;          //公式名字
	CString                m_QiShu;                //期数
	eFormulaType           m_FormulaType;          //公式类型
	vector<sFormulaData>   m_DataList;             //数据
	int                    m_MaxLianCuoCount;      //最大连错次数
	int                    m_MaxLianDuiCount;      //最大连对次数
	int                    m_MinLianCuoCount;      //最小连错次数
	int                    m_MinLianDuiCount;      //最小连对次数 
	int                    m_ErrorCount;           //错误次数
	int                    m_TrueCount;            //正确次数
	map<CString,int>       m_MapErrorInfo;         //错误信息
	bool                   m_LastStatus;           //最后一次公式状态

	sFormulaInfo()
	{
		 m_MaxLianCuoCount = 0;
		 m_MaxLianDuiCount = 0;
		 m_MinLianCuoCount = 0;
		 m_MinLianDuiCount = 0;

		 m_ErrorCount      = 0;
		 m_TrueCount       = 0;
		 m_LastStatus      = true;
		 m_FormulaType     = FORMULA_NULL;
	}
};

//m_ComboBox.InsertString(0,"正确率大于");
//	m_ComboBox.InsertString(1,"正确率等于");
//	m_ComboBox.InsertString(2,"正确率小于");
//	m_ComboBox.InsertString(3,"正确率区间");
//	m_ComboBox.InsertString(4,"正确率等于");
//	m_ComboBox.InsertString(5,"特码尾小于");
//	m_ComboBox.InsertString(6,"特码尾等于");
//	m_ComboBox.InsertString(7,"特码尾大于");
//	m_ComboBox.InsertString(8,"特码尾区间");
//	m_ComboBox.InsertString(9,"最后一次错");


enum eSearchVType
{
	TYPE_DA_YU,
	TYPE_DENG_YU,
	TYPE_XIAO_YU,
	TYPE_QU_JIAN,
	TYPE_V_DA_YU,
	TYPE_V_DENG_YU,
	TYPE_V_XIAO_YU,
	TYPE_V_QU_JIAN,
	TYPE_LAST_ERROR,
	TYPE_TE_DA_YU,
	TYPE_TE_DENG_YU,
	TYPE_TE_XIAO_YU,
	TYPE_TE_QU_JIAN,
};


class CFormulaCenter
{

public:

	//获取数据管理实例
	static  CFormulaCenter* GetInstance();

	//获取公式信息
	vector<sFormulaInfo> GetFormulaInfoByType(eFormulaType Type);

	//搜索公式信息
	vector<sFormulaInfo> SearchFormulaInfoByType(eFormulaType Type,eSearchVType SearchType,int Data,int Data2);

	//通过算法获取公式信息
	vector<sFormulaInfo> GetFormulaInfoByName(eFormulaType Type,vector<CString>& NameList);
	
	//获取算法个数
	int GetFormulaCount(eFormulaType Type);

	

private:

	//运行杀红公式
	void ExecShaHongFormula();

	//运行杀蓝公式
	void ExecShaLanFormula();

	//运行杀蓝V公式
	void ExecShaLanVFormula();

private:

	//整形转化到字符串
	CString DataToStr(int Data);

	//字符串转化到整形
	int StrToData(CString DataStr);

	//统计公式信息
	void ToJiFormulaInfo(sFormulaInfo& Formula);


	CFormulaCenter(void);

	~CFormulaCenter(void);

	//公式运算
	void RunFormula();


private:

	map<eFormulaType,vector<sFormulaInfo>> m_MapFormulaInfo;   //公式数据缓存
};
