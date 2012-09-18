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

#define QIU_COUNT 49
#define QIU_XUN   6

enum eSuanFaType                 //预测算法类型
{
	SUANFA_WEIZHI_YUCE,          //尾值预测
	SUANFA_LANJI_YUCE,           //特码为基准预测
	SUANFA_ACZHI_YUCE,           //AC值预测
	SUANFA_HEZHI_YUCE2,          //和值预测2
	SUANFA_HEZHI_YUCE,           //和值预测
	SUANFA_YIDONG_JUN,           //移动平均值
	


};

struct sShuangSeQiu
{
	DWORD   m_QiShuID;            //期数ID程序自动分配 
	CString m_QiShu;              //期数
	int   m_HongQiu[QIU_XUN];         //平码
	int   m_LanQiu;             //特码
	int   m_HongQiuSum;         //平码之和
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
};

struct sEqualShuangSeQiu          //相等平码数结构体定义
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
	DWORD m_HongQiuChaZhi[QIU_XUN];    //平码差值
	DWORD m_LanQiuChaZhi;        //特码差值
};

struct sHengXiangChaZhi          //横向差值
{
	CString m_QiShu;             //期数
	DWORD m_HongQiuChaZhi[QIU_XUN];    //平码差值
	DWORD m_LanQiuChaZhi;        //特码差值
};

