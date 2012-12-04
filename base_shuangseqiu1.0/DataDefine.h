/************************************************************
*                                                           *
*此文件用于数据的定义 2012年02月22日         谭军红         *
*                                                           *
*                                                           *
*************************************************************/
#include <vector>
#include <map>
using std::vector;
using std::map;

#define QIU_COUNT 33
#define QIU_XUN   6

enum eSuanFaType                 //预测算法类型
{
	SUANFA_WEIZHI_YUCE,          //尾值预测
	SUANFA_LANJI_YUCE,           //篮球为基准预测
	SUANFA_ACZHI_YUCE,           //AC值预测
	SUANFA_HEZHI_YUCE2,          //和值预测2
	SUANFA_HEZHI_YUCE,           //和值预测
	SUANFA_YIDONG_JUN,           //移动平均值
	


};

//29组数据
struct sData29
{
	CString     m_BianHao;       //编号
	vector<int> m_WeiHong;       //围红号
	vector<int> m_JueSha;        //绝杀号
	vector<int> m_GuanLian;      //关联号
};

struct sShuangSeQiu
{
	DWORD   m_QiShuID;            //期数ID程序自动分配 
	CString m_QiShu;              //期数
	int   m_HongQiu[QIU_XUN];         //红球
	int   m_LanQiu;             //篮球
	int   m_HongQiuSum;         //红球之和
	int   m_QuJian[3];          //区间
	sShuangSeQiu()
	{
		m_QiShuID=0;
		m_QiShu=_T("未知");
		m_LanQiu = 0;
		m_HongQiuSum=0;
		memset(m_HongQiu,0,sizeof(DWORD)*QIU_XUN);
		memset(m_QuJian,0,sizeof(DWORD)*3);
	}

public:

	CString ToString()
	{
		int QiShu=atoi(m_QiShu.GetBuffer());
		m_QiShu.ReleaseBuffer();
		
		CString RetStr;
		RetStr.Format("%d",QiShu);
		for(int i=0; i < QIU_XUN; i++)
		{
			CString Str;
			Str.Format(" %02d",m_HongQiu[i]);
			RetStr+=Str;
		}

		CString Lan;
		Lan.Format("+%02d",m_LanQiu);
		RetStr=RetStr+Lan;
		return RetStr;
		
	}
};

struct sEqualShuangSeQiu          //相等红球数结构体定义
{
	vector<sShuangSeQiu>     m_ShuangSeQiuList;  //双色球列表
	vector<DWORD>            m_EqualData;        //双色球相等个数列表
};

//预测球结构体
struct sYuCeShuangSeQiu
{
	sShuangSeQiu                      m_ShuangSeQiu;      //实际双色球
	map<eSuanFaType,sShuangSeQiu>     m_YuCeQiuMap;      //预测球列表
};
//
struct sZongXiangChaZhi          //纵向差值
{
	CString m_QiShu;              //期数
	DWORD m_HongQiuChaZhi[QIU_XUN];    //红球差值
	DWORD m_LanQiuChaZhi;        //篮球差值
};

struct sHengXiangChaZhi          //横向差值
{
	CString m_QiShu;             //期数
	DWORD m_HongQiuChaZhi[QIU_XUN];    //红球差值
	DWORD m_LanQiuChaZhi;        //篮球差值
};


//网易数据描述
struct sWangYiData
{
	int  m_Data;          //数据
	long m_Count;         //出球次数
};

/*********************网络数据描述************************/
enum eLoadDataType
{
	LOAD_ALL_DATA,        //导入所有数据
	LOAD_WANGYI_DATA,     //导入网易数据
	LOAD_ZHONGCAI_DATA,   //导入中彩数据
	LOAD_AOKE_DATA,       //导入澳客数据
	LOAD_360_DATA,        //导入360数据
};

/*********************网易数据描述************************/
#define WANG_YI_FILE_NAME  "net_wangyi.txt"

enum eWangYiType
{
	TYPE_GAO_REN_QI,      //高人气号
	TYPE_DI_REN_QI,       //低人气号
	TYPE_RE_HAO,          //热号
	TYPE_LENG_HAO,        //冷号
};

//网易数据描述
struct sWangYiDataInfo
{
	__time32_t           m_GetTime;       //获取时间
	CString              m_QiShu;         //期数
	eWangYiType          m_Type;          //类型
	vector<sWangYiData>  m_WangYiData;    //网易数据

	//转化成字符串
public:
	CString ToString()
	{
		CString Temp;
		Temp.Format("#%d#%s#%d#",m_GetTime,m_QiShu,m_Type);
		for(int i=0; i < m_WangYiData.size(); i++)
		{
			CString Temp2;
			Temp2.Format("%02d#",m_WangYiData[i]);
			Temp+=Temp2;
		}
		return Temp;
	}
};


/*********************中彩数据描述************************/
#define ZHONG_CAI_FILE_NAME  "net_zhongcai.txt"
//中彩数据类型
enum eZhongCaiType
{
	TYPE_ZHONGCAI_HONG,
	TYPE_ZHONGCAI_LAN,
};

//中彩擂台数据描述
struct sZhongCaiData
{
	int m_Data;            //球数据
	int m_DataCount;       //球数据计数
};

struct sZhongCaiDataInfo
{
	CString               m_QiShu;        //期数
	int                   m_QiShuInt;     //期数整形描述
	eZhongCaiType         m_Type;         //数据类型
	vector<sZhongCaiData> m_DataList;     //中彩数据列表
	
	//转化成字符串
public:
	CString ToString()
	{
		CString Temp;
		Temp.Format("#%s#%d#%d#",m_QiShu,m_QiShuInt,m_Type);
		for(int i=0; i < m_DataList.size(); i++)
		{
			CString Temp2;
			Temp2.Format("%02d#",m_DataList[i].m_DataCount);
			Temp+=Temp2;
		}
		return Temp;
	}

};


/*********************网络数据描述************************/


/************************颜色值定义*********************/

#define YELOW   RGB(255,192,0)                 //黄色
#define ZISE    RGB(112,48,160)                //紫色
#define WRITE   RGB(255,255,255)               //白色
#define RED     RGB(255,0,0)                   //红色
