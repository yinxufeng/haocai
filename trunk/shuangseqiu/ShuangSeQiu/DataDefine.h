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
#define QIU_XUAN  6

enum eSuanFaType                 //预测算法类型
{
	SUANFA_WEIZHI_YUCE,          //尾值预测
	SUANFA_LANJI_YUCE,           //篮球为基准预测
	SUANFA_ACZHI_YUCE,           //AC值预测
	SUANFA_HEZHI_YUCE2,          //和值预测2
	SUANFA_HEZHI_YUCE,           //和值预测
	SUANFA_YIDONG_JUN,           //移动平均值
	


};

struct sShuangSeQiu
{
	DWORD   m_QiShuID;            //期数ID程序自动分配 
	CString m_QiShu;              //期数
	int   m_HongQiu[6];         //红球
	int   m_LanQiu;             //篮球
	int   m_HongQiuSum;         //红球之和
	int   m_QuJian[3];          //区间
	sShuangSeQiu()
	{
		m_QiShuID=0;
		m_QiShu=_T("未知");
		m_LanQiu = 0;
		m_HongQiuSum=0;
		memset(m_HongQiu,0,sizeof(DWORD)*6);
		memset(m_QuJian,0,sizeof(DWORD)*3);
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
	DWORD m_HongQiuChaZhi[6];    //红球差值
	DWORD m_LanQiuChaZhi;        //篮球差值
};

struct sHengXiangChaZhi          //横向差值
{
	CString m_QiShu;             //期数
	DWORD m_HongQiuChaZhi[6];    //红球差值
	DWORD m_LanQiuChaZhi;        //篮球差值
};

//29组数据
struct sData29
{
	CString     m_BianHao;       //编号
	vector<int> m_WeiHong;       //围红号
	vector<int> m_JueSha;        //绝杀号
	vector<int> m_GuanLian;      //关联号
};

//搜索29组数据类型
enum eSearch29Type
{
	SEARCH_JUESHA_QIE_JUESHA,      //按绝杀且绝杀搜索方式
	SEARCH_JUESHA_HUO_JUESHA,      //按绝杀或绝杀搜索方式
	SEARCH_DINGDAN_QIE_DINGDAN,    //按定胆且定胆搜索方式
	SEARCH_DINGDAN_HUO_DINGDAN,    //按定胆或定胆搜索方式     
	SEARCH_JUESHA_QIE_DINGDAN,     //按绝杀与定胆方式搜索
	SEARCH_JUESHA_HUO_DINGDAN      //按绝杀或定胆方式搜索
};

//搜索29组数据
struct sSearchData29
{
	sData29           m_Data29;            //搜索29组数据
	int               m_GroupID;           //组号
};

