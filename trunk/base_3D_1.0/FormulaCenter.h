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

	FORMULA_DING_LAN            ,     //定篮球
	FORMULA_DING_LAN_WEI        ,     //定篮球尾
	FORMULA_DING_LAN_FANWEI     ,     //定篮球范围
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

	FORMULA_WEI_BU_TONG_CHU     ,    //尾不同出

	FORMUAL_SHA_NEW_DI_YI_HONG,      //杀第一位红        
	FORMUAL_SHA_NEW_DI_ER_HONG,      //杀第二位红
	FORMUAL_SHA_NEW_DI_SAN_HONG,     //杀第三位红
	FORMUAL_SHA_NEW_DI_SI_HONG,      //杀第四位红
	FORMUAL_SHA_NEW_DI_WU_HONG,      //杀第五位红
	FORMUAL_SHA_NEW_DI_LIU_HONG,     //杀第六位红

	FORMUAL_SHA_JI_JU,               //杀极距
	FORMUAL_SHA_DI_YI_HONG,          //杀第一位红
	FORMUAL_SHA_DI_ER_HONG,          //杀第二位红
	FORMUAL_SHA_DI_SAN_HONG,         //杀第三位红
	FORMUAL_SHA_DI_SI_HONG,          //杀第四位红
	FORMUAL_SHA_DI_WU_HONG,          //杀第五位红
	FORMUAL_SHA_DI_LIU_HONG,         //杀第六位红

	FORMUAL_SHA_DI_YI_HONG_V,        //杀第一位红尾
	FORMUAL_SHA_DI_ER_HONG_V,        //杀第二位红尾
	FORMUAL_SHA_DI_SAN_HONG_V,       //杀第三位红尾
	FORMUAL_SHA_DI_SI_HONG_V,        //杀第四位红尾
	FORMUAL_SHA_DI_WU_HONG_V,        //杀第五位红尾
	FORMUAL_SHA_DI_LIU_HONG_V,       //杀第六位红尾

	FORMUAL_SHA_DI_YI_HONG_HE,        //杀第一位红和
	FORMUAL_SHA_DI_ER_HONG_HE,        //杀第二位红和
	FORMUAL_SHA_DI_SAN_HONG_HE,       //杀第三位红和
	FORMUAL_SHA_DI_SI_HONG_HE,        //杀第四位红和
	FORMUAL_SHA_DI_WU_HONG_HE,        //杀第五位红和
	FORMUAL_SHA_DI_LIU_HONG_HE,       //杀第六位红和

	FORMUAL_SHA_DI_YI_HONG_CHA,        //杀第一位红差
	FORMUAL_SHA_DI_ER_HONG_CHA,        //杀第二位红差
	FORMUAL_SHA_DI_SAN_HONG_CHA,       //杀第三位红差
	FORMUAL_SHA_DI_SI_HONG_CHA,        //杀第四位红差
	FORMUAL_SHA_DI_WU_HONG_CHA,        //杀第五位红差
	FORMUAL_SHA_DI_LIU_HONG_CHA,       //杀第六位红差

	FORMUAL_SHA_NEW_LAN_V,             //杀蓝尾

	FORMUAL_SHA_QUAN_HONG,
	FORMUAL_SHA_NEW_JIXIAN_LAN,          //新极限杀蓝

	
	FORMUAL_DI_YI_HONG_QU_JIAN,         //第一红波动区间
	FORMUAL_DI_ER_HONG_QU_JIAN,         //第二红波动区间
	FORMUAL_DI_SAN_HONG_QU_JIAN,        //第三红波动区间
	FORMUAL_DI_SI_HONG_QU_JIAN,         //第四红波动区间
	FORMUAL_DI_WU_HONG_QU_JIAN,         //第五红波动区间
	FORMUAL_DI_LIU_HONG_QU_JIAN,        //第六红波动区间

};

//公式描述数据
struct sFormulaData
{
	CString m_Data;            //描述数据
	bool    m_IsTrue;          //是否正确
	CString m_QiShu;           //期数
	CString m_TrueBaiFenBi;    //正确百分比

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
//	m_ComboBox.InsertString(5,"篮球尾小于");
//	m_ComboBox.InsertString(6,"篮球尾等于");
//	m_ComboBox.InsertString(7,"篮球尾大于");
//	m_ComboBox.InsertString(8,"篮球尾区间");
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

	//运行定红公式
	void ExecDingHongFormula();

	//运行定红V公式
	void ExecDingHongVFormula();

	//运行杀蓝公式
	void ExecShaLanFormula();

	//运行杀蓝V公式
	void ExecShaLanVFormula();

	//运行杀龙头公式
	void ExecShaLongTouFormula();

	//运行杀凤尾公式
	void ExecShaFengWeiFormula();

	//运行尾不同出公式
	void ExecWeiBuTongChuFormula();

 //   FORMUAL_SHA_JI_JU,               //杀极距
	//FORMUAL_SHA_DI_ER_HONG,          //杀第二位红
	//FORMUAL_SHA_DI_SAN_HONG,         //杀第三位红
	//FORMUAL_SHA_DI_SI_HONG,          //杀第四位红
	//FORMUAL_SHA_DI_WU_WHONG,         //杀第五位红

	//杀极距
	void ExecShaJiJu();

	//定位杀尾
	void ExecShaWeiV(int Wei);

	//杀蓝尾
	void ExeShaLanV();

	//定位杀合
	void ExecShaWeiHe(int Wei);

	//定位杀差
	void ExecShaWeiCha(int Wei);

	//杀第一位
	void ExecShaDiYiWei();

	//杀第二位
	void ExecShaDiErWei();

	//杀第三位
	void ExecShaDiSanWei();

	//杀第四位
	void ExecShaDiSiWei();

	//杀第五位
	void ExecShaDiWuWei();

	//杀第六位
	void ExecShaDiLiuWei();

	//杀全位
	void ExecShaQuanWei();


	//新极限杀蓝
	void ExecNewShaLan();


	//第一位波动区间
	void ExecDiYiBoDongQuJian();

	//第二位波动区间
	void ExecDiErBoDongQuJian();

	//第三位波动区间
	void ExecDiSanBoDongQuJian();

	//第四位波动区间
	void ExecDiSiBoDongQuJian();

	//第五位波动区间
	void ExecDiWuBoDongQuJian();

	//第六位波动区间
	void ExecDiLiuBoDongQuJian();



private:

	//整形转化到字符串
	CString DataToStr(int Data);

	//整形转化到字符串
	CString DataToStr(vector<int> Data);

	//字符串转化到整形
	int StrToData(CString DataStr);

	//统计公式信息
	void ToJiFormulaInfo(sFormulaInfo& Formula);

	//获取尾值和
	int GetWeiZhiCount(int DataList[],int Count);

	//运行区间公式
	void RunQuJianFormula(eFormulaType FormulaType);

	//记录数据
	void RecordDataToFile();

	CFormulaCenter(void);

	~CFormulaCenter(void);

	//公式运算
	void RunFormula();

private:

	map<eFormulaType,vector<sFormulaInfo>> m_MapFormulaInfo;   //公式数据缓存
};
