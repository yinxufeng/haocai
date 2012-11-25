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

