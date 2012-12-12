#include "StdAfx.h"
#include "DataManageCenter.h"



//获取模块路径
CString GetAppCurrentPath2()
{
	CString server_ip;
	CString StrDes=_T("");
	::GetModuleFileName(NULL,StrDes.GetBuffer(MAX_PATH),MAX_PATH); 
	//::GetCurrentDirectory(MAX_PATH,StrDes.GetBuffer(MAX_PATH));
	StrDes.ReleaseBuffer();
	StrDes=StrDes.Left(StrDes.ReverseFind('\\'));
	if(StrDes.Right(1)!='\\')
		StrDes+="\\";

	return StrDes;
}



CDataManageCenter::CDataManageCenter(void)
{
	m_SearchFlag = false;

	LoadNetData();
}

CDataManageCenter::~CDataManageCenter(void)
{
}

//获取数据管理实例
CDataManageCenter* CDataManageCenter::GetInstance()
{
	static CDataManageCenter Self;
	return &Self;
}

//获取双色球列表
vector<sShuangSeQiu>* CDataManageCenter::GetDataList()
{
	//初始化横向差值
	InitHengXiangChaZhi(m_ShuangSeQiuList);

	//初始化纵向差值
	InitZongXiangChaZhi(m_ShuangSeQiuList);

	//初始化连号红球
	InitLianHaoHongQiu(m_ShuangSeQiuList);

	//初始化连号篮球
	InitLianHaoLanQiu(m_ShuangSeQiuList);

	return &m_ShuangSeQiuList;
}

//获取按出号顺序双色球列表 
vector<sShuangSeQiu>* CDataManageCenter::GetDataListByChuHao()
{
	return &m_ShuangSeQiuChuHaoList;
}

//获取双色球列表
vector<sShuangSeQiu> CDataManageCenter::GetSpecialDataList(DWORD Data1,DWORD Data2,DWORD Data3,DWORD Data4,CString Str)
{
	DWORD Data[4];
	Data[0]=Data1;
	Data[1]=Data2;
	Data[2]=Data3;
	Data[3]=Data4;

	vector<sShuangSeQiu> WantList;

	for(int i=0; i < m_ShuangSeQiuList.size(); i++)
	{
		bool IsWant=false;
		int DataNotZoreCount=0;
		int DataEqualCount=0;
		for(int Index= 0 ; Index < 4; Index++)
		{
			if(Data[Index] != 0)
			{
				DataNotZoreCount++;
				for(int j=0; j < QIU_XUN; j++)
				{
					if( m_ShuangSeQiuList[i].m_HongQiu[j] == Data[Index])
					{
						DataEqualCount++;
						break;
					}
				}
			}
		}

		if(DataNotZoreCount != 0 && DataNotZoreCount == DataEqualCount)
		{
			if(Str.IsEmpty())
			{
				WantList.push_back(m_ShuangSeQiuList[i]);
				if(m_SearchFlag && i+1 < m_ShuangSeQiuList.size())
				{
					WantList.push_back(m_ShuangSeQiuList[i+1]);
					sShuangSeQiu Temp;
					Temp.m_QiShu = _T("分割");
					WantList.push_back(Temp);
				}
			}

			else
			{
				CString Temp;
				Temp.Format("%d:%d:%d",m_ShuangSeQiuList[i].m_QuJian[0],m_ShuangSeQiuList[i].m_QuJian[1],m_ShuangSeQiuList[i].m_QuJian[2]);
				if(Temp == Str)
				{
					WantList.push_back(m_ShuangSeQiuList[i]);
					if(i+1 < m_ShuangSeQiuList.size())
					{
						WantList.push_back(m_ShuangSeQiuList[i+1]);
						if(m_SearchFlag)
						{
							sShuangSeQiu Temp;
							Temp.m_QiShu = _T("分割");
							WantList.push_back(Temp);
						}
					}

				}
			}
		}
		else if(!Str.IsEmpty())
		{
		
			CString Temp;
			Temp.Format("%d:%d:%d",m_ShuangSeQiuList[i].m_QuJian[0],m_ShuangSeQiuList[i].m_QuJian[1],m_ShuangSeQiuList[i].m_QuJian[2]);
			if(Temp == Str)
			{
				WantList.push_back(m_ShuangSeQiuList[i]);
				if(i+1 < m_ShuangSeQiuList.size())
					WantList.push_back(m_ShuangSeQiuList[i+1]);

			}
		}
	}
	return WantList;
}

//获取4个双色球相同的列表
map<CString,sEqualShuangSeQiu> CDataManageCenter::GetFourDataEqualList()
{
	map<CString,sEqualShuangSeQiu> TempData;

	for(int i=0; i < m_ShuangSeQiuList.size(); i++)
	{
		for(int j=i+1; j < m_ShuangSeQiuList.size(); j++)
		{
			sEqualShuangSeQiu TempEqual;
			int EqualCount=0;
			for (int g=0; g < QIU_XUN; g++)
			{
				for(int k=0; k < QIU_XUN; k++)
				{
					if(m_ShuangSeQiuList[j].m_HongQiu[k] == m_ShuangSeQiuList[i].m_HongQiu[g])
					{
						TempEqual.m_EqualData.push_back(m_ShuangSeQiuList[j].m_HongQiu[k]);
						EqualCount++;
						break;
					}
				}
			}

			if(EqualCount == 4)
			{
				TempEqual.m_ShuangSeQiuList.push_back(m_ShuangSeQiuList[i]);
				TempEqual.m_ShuangSeQiuList.push_back(m_ShuangSeQiuList[j]);
				TempData[m_ShuangSeQiuList[i].m_QiShu]=TempEqual;
				
			}
		}
	}

	return TempData;
}

//获取3个双色球相同的列表
map<CString,sEqualShuangSeQiu> CDataManageCenter::GetThreeDataList()
{
	map<CString,sEqualShuangSeQiu> TempData;

	for(int i=0; i < m_ShuangSeQiuList.size(); i++)
	{
		for(int j=i+1; j < m_ShuangSeQiuList.size(); j++)
		{
			sEqualShuangSeQiu TempEqual;
			int EqualCount=0;
			for (int g=0; g < QIU_XUN; g++)
			{
				for(int k=0; k < QIU_XUN; k++)
				{
					if(m_ShuangSeQiuList[j].m_HongQiu[k] == m_ShuangSeQiuList[i].m_HongQiu[g])
					{
						TempEqual.m_EqualData.push_back(m_ShuangSeQiuList[j].m_HongQiu[k]);
						EqualCount++;
						break;
					}
				}
			}

			if(EqualCount == 3)
			{
				TempEqual.m_ShuangSeQiuList.push_back(m_ShuangSeQiuList[i]);
				TempEqual.m_ShuangSeQiuList.push_back(m_ShuangSeQiuList[j]);
				TempData[m_ShuangSeQiuList[i].m_QiShu]=TempEqual;
			}
		}
	}

	return TempData;
}


//预测计算方法
map<CString,sYuCeShuangSeQiu>CDataManageCenter::GetDataBySuanFa()
{

	map<CString,sYuCeShuangSeQiu>  TempData;
	int ListCount = m_ShuangSeQiuList.size();
	for(int i=0; i < ListCount; i++)
	{
		DWORD Sum=m_ShuangSeQiuList[i].m_HongQiuSum;
		sShuangSeQiu TempQiuData;
		TempQiuData.m_LanQiu = 0;
		TempQiuData.m_QiShu = _T("和值预测");
		TempQiuData.m_HongQiuSum = 0;

		sShuangSeQiu TempQiuData2;
		TempQiuData2.m_LanQiu = 0;
		TempQiuData2.m_QiShu = _T("和值预测2");
		TempQiuData2.m_HongQiuSum = 0;


		sShuangSeQiu TempLanQiuData;
		TempLanQiuData.m_LanQiu = 0;
		TempLanQiuData.m_QiShu = _T("蓝基预测");
		TempLanQiuData.m_HongQiuSum = 0;

		sShuangSeQiu TempACQiuData;
		TempACQiuData.m_LanQiu = 0;
		TempACQiuData.m_QiShu = _T("AC预测");
		TempACQiuData.m_HongQiuSum = 0;

		sShuangSeQiu TempWeiQiuData;
		TempWeiQiuData.m_LanQiu = 0;
		TempWeiQiuData.m_QiShu = _T("尾值预测");
		TempWeiQiuData.m_HongQiuSum = 0;

		sYuCeShuangSeQiu TempEqual;

		int ACCount=GetACCount(m_ShuangSeQiuList[i]);
		int WeiZhiCount=GetWeiZhiParam(m_ShuangSeQiuList[i]);

		////预测篮球
		//int TempLanQiu  = m_ShuangSeQiuList[i].m_LanQiu % 5;
		//int TempLanQiu2 = m_ShuangSeQiuList[i].m_LanQiu % 3;

		//vector<DWORD> LanQiu1;
		//vector<DWORD> LanQiu2;
		//for(int l=1; l <= 16; l++)
		//{
		//	if( l%3 == TempLanQiu)
		//		LanQiu1.push_back(l);
		//	if(l%5 == TempLanQiu2)
		//		LanQiu2.push_back(l);
		//}

		//DWORD LanQiuYuCe=0;
		//for(int a=0; a < LanQiu1.size(); a++)
		//{
		//	for(int b=0; b < LanQiu2.size(); b++)
		//	{
		//		if(LanQiu1[a] == LanQiu2[b])
		//			LanQiuYuCe=LanQiu1[a];
		//	}
		//}

		//TempQiuData.m_LanQiu = LanQiuYuCe;




		for(int j=0; j < QIU_XUN; j++)
		{
			int Data = Sum/m_ShuangSeQiuList[i].m_HongQiu[j];
			//int Data=(Sum-m_ShuangSeQiuList[i].m_HongQiu[j])/m_ShuangSeQiuList[i].m_HongQiu[j];
			TempQiuData.m_HongQiu[j]= Data;
			TempQiuData2.m_HongQiu[j]=(Sum-m_ShuangSeQiuList[i].m_HongQiu[j])/m_ShuangSeQiuList[i].m_HongQiu[j];
			

			//篮球选号
			if(i-1>=0)
			{
				TempLanQiuData.m_HongQiu[j]=abs(m_ShuangSeQiuList[i-1].m_HongQiu[j]-m_ShuangSeQiuList[i].m_LanQiu);
				TempWeiQiuData.m_HongQiu[j]=abs(m_ShuangSeQiuList[i-1].m_HongQiu[j]-WeiZhiCount);
			}
			else
			{
				TempLanQiuData.m_HongQiu[j]=0;
				TempWeiQiuData.m_HongQiu[j]=0;
			}

			//AC差值
			TempACQiuData.m_HongQiu[j]=abs(m_ShuangSeQiuList[i].m_HongQiu[j]-ACCount);

		}

		if(i+1 < ListCount)
		{

			TempEqual.m_ShuangSeQiu = m_ShuangSeQiuList[i+1];
			TempEqual.m_YuCeQiuMap[SUANFA_HEZHI_YUCE]=TempQiuData;
			TempEqual.m_YuCeQiuMap[SUANFA_HEZHI_YUCE2]=TempQiuData2;
			TempEqual.m_YuCeQiuMap[SUANFA_ACZHI_YUCE]=TempACQiuData;
			TempEqual.m_YuCeQiuMap[SUANFA_WEIZHI_YUCE]=TempWeiQiuData;
			TempEqual.m_YuCeQiuMap[SUANFA_LANJI_YUCE]=TempLanQiuData;			
			TempData[m_ShuangSeQiuList[i+1].m_QiShu]=TempEqual;
		}
		else
		{
			TempEqual.m_ShuangSeQiu.m_QiShu=_T("最新预测");
			TempEqual.m_ShuangSeQiu.m_HongQiuSum = 0;
			TempEqual.m_ShuangSeQiu.m_LanQiu  = 0;
			for(int Index = 0; Index < QIU_XUN; Index++)
			{
				TempEqual.m_ShuangSeQiu.m_HongQiu[Index]=0;
			}
			TempEqual.m_YuCeQiuMap[SUANFA_HEZHI_YUCE]=TempQiuData;
			TempEqual.m_YuCeQiuMap[SUANFA_HEZHI_YUCE2]=TempQiuData2;
			TempEqual.m_YuCeQiuMap[SUANFA_ACZHI_YUCE]=TempACQiuData;
			TempEqual.m_YuCeQiuMap[SUANFA_WEIZHI_YUCE]=TempWeiQiuData;
			TempEqual.m_YuCeQiuMap[SUANFA_LANJI_YUCE]=TempLanQiuData;
			TempData["算法预测"]=TempEqual;

			SaveDataToFile(TempEqual);
		}


	}

	return TempData;
}

//通过篮球搜索数据
vector<sShuangSeQiu> CDataManageCenter::SearchDataLanQiu(DWORD Data1,DWORD Data2,DWORD Data3,DWORD Data4,CString Str)
{
	DWORD Data[4];
	Data[0]=Data1;
	Data[1]=Data2;
	Data[2]=Data3;
	Data[3]=Data4;

	vector<sShuangSeQiu> WantList;

	for(int i=0; i < m_ShuangSeQiuList.size(); i++)
	{
		bool IsWant=false;
		int DataNotZoreCount=0;
		int DataEqualCount=0;
		for(int Index= 0 ; Index < 4; Index++)
		{
			if(Data[Index] != 0)
			{
				DataNotZoreCount++;
			
				if( m_ShuangSeQiuList[i].m_LanQiu == Data[Index])
				{
					DataEqualCount++;
					break;
				}
			}
		}

		if(DataNotZoreCount != 0 && DataEqualCount > 0)
		{
			if(Str.IsEmpty())
			{
				WantList.push_back(m_ShuangSeQiuList[i]);
				if(m_SearchFlag && i+1 < m_ShuangSeQiuList.size())
				{
					WantList.push_back(m_ShuangSeQiuList[i+1]);
					sShuangSeQiu Temp;
					Temp.m_QiShu = _T("分割");
					WantList.push_back(Temp);
				}
			}

			else
			{
				CString Temp;
				Temp.Format("%d:%d:%d",m_ShuangSeQiuList[i].m_QuJian[0],m_ShuangSeQiuList[i].m_QuJian[1],m_ShuangSeQiuList[i].m_QuJian[2]);
				if(Temp == Str)
				{
					WantList.push_back(m_ShuangSeQiuList[i]);
					if(i+1 < m_ShuangSeQiuList.size())
					{
						WantList.push_back(m_ShuangSeQiuList[i+1]);
						if(m_SearchFlag)
						{
							sShuangSeQiu Temp;
							Temp.m_QiShu = _T("分割");
							WantList.push_back(Temp);
						}
					}

				}
			}
		}
		else if(!Str.IsEmpty())
		{
		
			CString Temp;
			Temp.Format("%d:%d:%d",m_ShuangSeQiuList[i].m_QuJian[0],m_ShuangSeQiuList[i].m_QuJian[1],m_ShuangSeQiuList[i].m_QuJian[2]);
			if(Temp == Str)
			{
				WantList.push_back(m_ShuangSeQiuList[i]);
				if(i+1 < m_ShuangSeQiuList.size())
					WantList.push_back(m_ShuangSeQiuList[i+1]);

			}
		}
	}
	return WantList;
}

//通过龙头搜索数据
vector<sShuangSeQiu> CDataManageCenter::SearchDataLongTou(DWORD Data1,DWORD Data2,DWORD Data3,DWORD Data4,CString Str)
{
	DWORD Data[4];
	Data[0]=Data1;
	Data[1]=Data2;
	Data[2]=Data3;
	Data[3]=Data4;

	vector<sShuangSeQiu> WantList;

	for(int i=0; i < m_ShuangSeQiuList.size(); i++)
	{
		bool IsWant=false;
		int DataNotZoreCount=0;
		int DataEqualCount=0;
		for(int Index= 0 ; Index < 4; Index++)
		{
			if(Data[Index] != 0)
			{
				DataNotZoreCount++;
			    //for(int j=0; j < 6; j++)
				{
					if( m_ShuangSeQiuList[i].m_HongQiu[0] == Data[Index])
					{
						DataEqualCount++;
						break;
					}
				}//
			}
		}

		if(DataNotZoreCount != 0 && DataEqualCount > 0)
		{
			if(Str.IsEmpty())
			{
				WantList.push_back(m_ShuangSeQiuList[i]);
				if(m_SearchFlag && i+1 < m_ShuangSeQiuList.size())
				{
					WantList.push_back(m_ShuangSeQiuList[i+1]);
					sShuangSeQiu Temp;
					Temp.m_QiShu = _T("分割");
					WantList.push_back(Temp);
				}
			}

			else
			{
				CString Temp;
				Temp.Format("%d:%d:%d",m_ShuangSeQiuList[i].m_QuJian[0],m_ShuangSeQiuList[i].m_QuJian[1],m_ShuangSeQiuList[i].m_QuJian[2]);
				if(Temp == Str)
				{
					WantList.push_back(m_ShuangSeQiuList[i]);
					if(i+1 < m_ShuangSeQiuList.size())
					{
						WantList.push_back(m_ShuangSeQiuList[i+1]);
						if(m_SearchFlag)
						{
							sShuangSeQiu Temp;
							Temp.m_QiShu = _T("分割");
							WantList.push_back(Temp);
						}
					}

				}
			}
		}
		else if(!Str.IsEmpty())
		{
		
			CString Temp;
			Temp.Format("%d:%d:%d",m_ShuangSeQiuList[i].m_QuJian[0],m_ShuangSeQiuList[i].m_QuJian[1],m_ShuangSeQiuList[i].m_QuJian[2]);
			if(Temp == Str)
			{
				WantList.push_back(m_ShuangSeQiuList[i]);
				if(i+1 < m_ShuangSeQiuList.size())
					WantList.push_back(m_ShuangSeQiuList[i+1]);

			}
		}
	}
	return WantList;
}

//通过尾值搜索数据
vector<sShuangSeQiu> CDataManageCenter::SearchDataWeiZhi(DWORD Data1,DWORD Data2,DWORD Data3,DWORD Data4,CString Str)
{
	DWORD Data[4];
	Data[0]=Data1;
	Data[1]=Data2;
	Data[2]=Data3;
	Data[3]=Data4;

	vector<sShuangSeQiu> WantList;

	for(int i=0; i < m_ShuangSeQiuList.size(); i++)
	{
		bool IsWant=false;
		int DataNotZoreCount=0;
		int DataEqualCount=0;
		for(int Index= 0 ; Index < 4; Index++)
		{
			if(Data[Index] != 0)
			{
				DataNotZoreCount++;
				for(int j=0; j < QIU_XUN; j++)
				{
					int WeiZhi=m_ShuangSeQiuList[i].m_HongQiu[j]%10;
					if( WeiZhi == Data[Index])
					{
						DataEqualCount++;
						break;
					}
				}
			}
		}

		if(DataNotZoreCount != 0 && DataNotZoreCount == DataEqualCount)
		{
			if(Str.IsEmpty())
			{
				WantList.push_back(m_ShuangSeQiuList[i]);
				if(m_SearchFlag && i+1 < m_ShuangSeQiuList.size())
				{
					WantList.push_back(m_ShuangSeQiuList[i+1]);
					sShuangSeQiu Temp;
					Temp.m_QiShu = _T("分割");
					WantList.push_back(Temp);
				}
			}

			else
			{
				CString Temp;
				Temp.Format("%d:%d:%d",m_ShuangSeQiuList[i].m_QuJian[0],m_ShuangSeQiuList[i].m_QuJian[1],m_ShuangSeQiuList[i].m_QuJian[2]);
				if(Temp == Str)
				{
					WantList.push_back(m_ShuangSeQiuList[i]);
					if(i+1 < m_ShuangSeQiuList.size())
					{
						WantList.push_back(m_ShuangSeQiuList[i+1]);
						if(m_SearchFlag)
						{
							sShuangSeQiu Temp;
							Temp.m_QiShu = _T("分割");
							WantList.push_back(Temp);
						}
					}

				}
			}
		}
		else if(!Str.IsEmpty())
		{
		
			CString Temp;
			Temp.Format("%d:%d:%d",m_ShuangSeQiuList[i].m_QuJian[0],m_ShuangSeQiuList[i].m_QuJian[1],m_ShuangSeQiuList[i].m_QuJian[2]);
			if(Temp == Str)
			{
				WantList.push_back(m_ShuangSeQiuList[i]);
				if(i+1 < m_ShuangSeQiuList.size())
					WantList.push_back(m_ShuangSeQiuList[i+1]);

			}
		}
	}
	return WantList;
}

//搜索预测结果
map<CString,sYuCeShuangSeQiu> CDataManageCenter::SearchDataBySuanFa(DWORD Data1,DWORD Data2,DWORD Data3,DWORD Data4,CString QiShu)
{
	DWORD Data[4];
	Data[0]=Data1;
	Data[1]=Data2;
	Data[2]=Data3;
	Data[3]=Data4;

	map<CString,sYuCeShuangSeQiu> YuCeData=GetDataBySuanFa();
	map<CString,sYuCeShuangSeQiu> Ret;
	map<CString,sYuCeShuangSeQiu>::iterator it=YuCeData.begin();

	

	for(; it != YuCeData.end(); it++)
	{
		sYuCeShuangSeQiu TempYuCeShuangSeQiu;
		map<eSuanFaType,sShuangSeQiu> TempMap;

		bool IsWant=false;
		map<eSuanFaType,sShuangSeQiu>::iterator TempIt=it->second.m_YuCeQiuMap.begin();
		for(; TempIt != it->second.m_YuCeQiuMap.end(); TempIt++)
		{
		
			int DataNotZoreCount=0;
			int DataEqualCount=0;

			for(int Index= 0 ; Index < 4; Index++)
			{
				if(Data[Index] != 0)
				{
					DataNotZoreCount++;
					for(int j=0; j < QIU_XUN; j++)
					{
						if( TempIt->second.m_HongQiu[j] == Data[Index])
						{
							DataEqualCount++;
							break;
						}
					}
				}
			}

		//	if(DataNotZoreCount != 0 && DataEqualCount >= DataNotZoreCount)
			if(Data1 == 0 && !QiShu.IsEmpty())
			{
				if(DataNotZoreCount != 0 && DataEqualCount == DataNotZoreCount || DataNotZoreCount == 0&&!QiShu.IsEmpty())
				{
					if(!QiShu.IsEmpty()&& QiShu== TempIt->second.m_QiShu || QiShu.IsEmpty())
					{
						IsWant=true;
						TempMap[TempIt->first]=TempIt->second;
					}
				}
			}
			else
			{
				
				if(DataNotZoreCount != 0 && DataEqualCount >0  || DataNotZoreCount == 0&&!QiShu.IsEmpty())
				{
					if(!QiShu.IsEmpty()&& QiShu== TempIt->second.m_QiShu || QiShu.IsEmpty())
					{
						IsWant=true;
						TempMap[TempIt->first]=TempIt->second;
					}
				}
			}
		}
		
		if(IsWant)
		{
			TempYuCeShuangSeQiu.m_ShuangSeQiu = it->second.m_ShuangSeQiu;
			TempYuCeShuangSeQiu.m_YuCeQiuMap = TempMap;
			//TempYuCeShuangSeQiu.m_YuCeQiuMap = it->second.m_YuCeQiuMap;
			Ret[it->first]=TempYuCeShuangSeQiu;
		}
	}

	return Ret;
}

//搜索红球
vector<sShuangSeQiu> CDataManageCenter::SearchHongQiu(DWORD HongQiu)
{
	/*vector<sShuangSeQiu> ShuangSeQiuList;
	for(int Index = 0; Index < (int)m_ShuangSeQiuList.size(); Index++)
	{
	bool IsWant=false;
	for(int i=0; i < QIU_XUN; i++)
	{
	if(m_ShuangSeQiuList[Index].m_HongQiu[i] == HongQiu)
	{
	IsWant=true;
	break;
	}
	}

	if(IsWant)
	ShuangSeQiuList.push_back(m_ShuangSeQiuList[Index]);
	}*/
	//return ShuangSeQiuList;
	return SearchHongQiu(m_ShuangSeQiuList,HongQiu);

}

//搜索红球
vector<sShuangSeQiu> CDataManageCenter::SearchHongQiu(vector<sShuangSeQiu>& DataList,DWORD HongQiu)
{
	vector<sShuangSeQiu> ShuangSeQiuList;
	for(int Index = 0; Index < (int)DataList.size(); Index++)
	{
		bool IsWant=false;
		for(int i=0; i < QIU_XUN; i++)
		{
			if(DataList[Index].m_HongQiu[i] == HongQiu)
			{
				IsWant=true;
				break;
			}
		}

		if(IsWant)
			ShuangSeQiuList.push_back(DataList[Index]);
	}

	//初始化横向差值
	InitHengXiangChaZhi(ShuangSeQiuList);

	//初始化纵向差值
	InitZongXiangChaZhi(ShuangSeQiuList);

	//初始化连号红球
	InitLianHaoHongQiu(ShuangSeQiuList);

	//初始化连号篮球
	InitLianHaoLanQiu(ShuangSeQiuList);

	return ShuangSeQiuList;
}

//搜索篮球
vector<sShuangSeQiu> CDataManageCenter::SearchLanQiu(DWORD LanQiu)
{
	vector<sShuangSeQiu> ShuangSeQiuList;
	for(int Index = 0; Index < (int)m_ShuangSeQiuList.size(); Index++)
	{
		if(m_ShuangSeQiuList[Index].m_LanQiu == LanQiu)
		{
			ShuangSeQiuList.push_back(m_ShuangSeQiuList[Index]);
		}
	}

	//初始化横向差值
	InitHengXiangChaZhi(ShuangSeQiuList);

	//初始化纵向差值
	InitZongXiangChaZhi(ShuangSeQiuList);

	//初始化连号红球
	InitLianHaoHongQiu(ShuangSeQiuList);

	//初始化连号篮球
	InitLianHaoLanQiu(ShuangSeQiuList);

	return ShuangSeQiuList;
}

//获取纵向差值
vector<sZongXiangChaZhi>* CDataManageCenter::GetZongXiangChaZhi()
{ 
	return &m_ZongXiangChaZhiList;
}

//获取横向差值
vector<sHengXiangChaZhi>* CDataManageCenter::GetHengXiangChaZhi()
{
	return &m_HengXiangChaZhiList;
}

//获取连号红球
vector<sShuangSeQiu>* CDataManageCenter::GetLianHaoHongQiu()
{
	return &m_LianHaoHongQiu;
}

//获取连号篮球
vector<sShuangSeQiu>* CDataManageCenter::GetLianHaoLanQiu()
{
	return &m_LianHaoLanQiu;
}

//搜索纵向差值
vector<sZongXiangChaZhi> CDataManageCenter::SearchZongXiangChaZhi(DWORD Value)
{
	vector<sZongXiangChaZhi> ChiZhiList;
	for(int Index=0; Index < m_ZongXiangChaZhiList.size(); Index++)
	{
		bool IsWant=false;
		for(int i =0; i < QIU_XUN; i++)
		{
			if(m_ZongXiangChaZhiList[Index].m_HongQiuChaZhi[i] == Value)
			{
				IsWant=true;
				break;
			}
		}

		if(m_ZongXiangChaZhiList[Index].m_LanQiuChaZhi == Value)
			IsWant=true;

		if(IsWant)
			ChiZhiList.push_back(m_ZongXiangChaZhiList[Index]);
	}

	return ChiZhiList;
}

//搜索横向差值
vector<sHengXiangChaZhi> CDataManageCenter::SearchHengXiangChaZhi(DWORD Value)
{
	vector<sHengXiangChaZhi> ChiZhiList;
	for(int Index=0; Index < m_HengXiangChaZhiList.size(); Index++)
	{
		bool IsWant=false;
		for(int i =0; i < QIU_XUN; i++)
		{
			if(m_HengXiangChaZhiList[Index].m_HongQiuChaZhi[i] == Value)
			{
				IsWant=true;
				break;
			}
		}

		if(m_HengXiangChaZhiList[Index].m_LanQiuChaZhi == Value)
			IsWant=true;

		if(IsWant)
			ChiZhiList.push_back(m_HengXiangChaZhiList[Index]);
	}


	return ChiZhiList;
}


//获取连号红球
vector<sShuangSeQiu> CDataManageCenter::SearchLianHaoHongQiu(DWORD Value)
{
	vector<sShuangSeQiu> QiuList;
	for(int Index = 0 ; Index < m_LianHaoHongQiu.size(); Index++)
	{
		bool IsWant=false;
		for(int i=0; i < QIU_XUN; i++)
		{
			if(m_LianHaoHongQiu[Index].m_HongQiu[i] == Value)
			{
				IsWant=true;
				break;
			}
		}

		if(IsWant )
			QiuList.push_back(m_LianHaoHongQiu[Index]);

	}


	//初始化横向差值
	InitHengXiangChaZhi(QiuList);

	//初始化纵向差值
	InitZongXiangChaZhi(QiuList);

	//初始化连号红球
	InitLianHaoHongQiu(QiuList);

	//初始化连号篮球
	InitLianHaoLanQiu(QiuList);

	return QiuList;
}

//获取连号篮球
vector<sShuangSeQiu> CDataManageCenter::SearchLianHaoLanQiu(DWORD Value)
{
	vector<sShuangSeQiu> QiuList;
	for(int Index = 0 ; Index < m_LianHaoLanQiu.size(); Index++)
	{
		if(m_LianHaoLanQiu[Index].m_LanQiu == Value)
			QiuList.push_back(m_LianHaoLanQiu[Index]);
	}

	//初始化横向差值
	InitHengXiangChaZhi(QiuList);

	//初始化纵向差值
	InitZongXiangChaZhi(QiuList);

	//初始化连号红球
	InitLianHaoHongQiu(QiuList);

	//初始化连号篮球
	InitLianHaoLanQiu(QiuList);

	return QiuList;
}


//初始化横向差值
void CDataManageCenter::InitHengXiangChaZhi(vector<sShuangSeQiu>& ShuangSeQiuList)
{  
	m_HengXiangChaZhiList.clear();
	if(ShuangSeQiuList.empty())
		return;
	for(int Index = 0 ; Index < ShuangSeQiuList.size(); Index++)
	{
		sHengXiangChaZhi ChaZhi;

		for(int i =0; i < 5; i++)
		{
			ChaZhi.m_HongQiuChaZhi[i] = ShuangSeQiuList[Index].m_HongQiu[i+1]-ShuangSeQiuList[Index].m_HongQiu[i];

		}

		ChaZhi.m_HongQiuChaZhi[5] = ShuangSeQiuList[Index].m_LanQiu - ShuangSeQiuList[Index].m_HongQiu[5];
		ChaZhi.m_QiShu = ShuangSeQiuList[Index].m_QiShu;
		ChaZhi.m_LanQiuChaZhi = ShuangSeQiuList[Index].m_LanQiu;
		m_HengXiangChaZhiList.push_back(ChaZhi);
	}
}

//初始化纵向差值
void CDataManageCenter::InitZongXiangChaZhi(vector<sShuangSeQiu>& ShuangSeQiuList)
{
	m_ZongXiangChaZhiList.clear();
	if(ShuangSeQiuList.empty())
		return;

	DWORD Size=ShuangSeQiuList.size();
	if(Size > 1)
	{
		for(int Index = 0; Index < Size-1; Index++)
		{
			sZongXiangChaZhi ChaZhi;
			for(int i= 0; i < QIU_XUN; i++)
			{
				DWORD Value=ShuangSeQiuList[Index+1].m_HongQiu[i] - ShuangSeQiuList[Index].m_HongQiu[i];
				ChaZhi.m_HongQiuChaZhi[i] = Value;
			}
			ChaZhi.m_LanQiuChaZhi = ShuangSeQiuList[Index+1].m_LanQiu - ShuangSeQiuList[Index].m_LanQiu;
			ChaZhi.m_QiShu = ShuangSeQiuList[Index].m_QiShu;
			m_ZongXiangChaZhiList.push_back(ChaZhi);
		}
	}
}

//初始化连号红球
void CDataManageCenter::InitLianHaoHongQiu(vector<sShuangSeQiu>& ShuangSeQiuList)
{
	m_LianHaoHongQiu.clear();
	if(ShuangSeQiuList.empty())
		return;

	for(int Index = 0 ; Index < ShuangSeQiuList.size(); Index++)
	{
		bool IsWant = false;
		for(int i =0; i < 4; i++)
		{
			if(ShuangSeQiuList[Index].m_HongQiu[i] +1 == ShuangSeQiuList[Index].m_HongQiu[i+1])
			{
				IsWant=true;
				break;
			}
		}

		if(IsWant)
			m_LianHaoHongQiu.push_back(ShuangSeQiuList[Index]);
	}
}

//初始化连号篮球
void CDataManageCenter::InitLianHaoLanQiu(vector<sShuangSeQiu>& ShuangSeQiuList)
{
	m_LianHaoLanQiu.clear();
	if(ShuangSeQiuList.empty())
		return;

	for(int Index = 0 ; Index < ShuangSeQiuList.size()-1; Index++)
	{

		if(ShuangSeQiuList[Index].m_LanQiu +1 == ShuangSeQiuList[Index].m_LanQiu)
			m_LianHaoLanQiu.push_back(ShuangSeQiuList[Index]);
	}
}

//从文件加载数据
bool  CDataManageCenter::LoadDataFromFile(CString FilePath,bool IsChuHaoXunXu,bool IsClean)
{
	if(!IsChuHaoXunXu)
	{
		if(IsClean)
			m_ShuangSeQiuList.clear();

		LoadDataFromFile(FilePath,m_ShuangSeQiuList);

		//保存统计数据到csv文件中
		SaveDataToCSVFile();

		//保存统计五期以内和五期以外数据到txt文件中
		SaveFiveDataToTxtFile();
	}
	else
	{
		if(IsClean)
			m_ShuangSeQiuChuHaoList.clear();

		LoadDataFromFile(FilePath,m_ShuangSeQiuChuHaoList);

	}
	return true;
}

//从文件加载数据
bool CDataManageCenter::LoadDataFromFile(CString FilePath,vector<sShuangSeQiu>& QiuList)
{
	DWORD Flag = OPEN_EXISTING;
	HANDLE FileHandle=CreateFile(FilePath,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL,Flag,FILE_ATTRIBUTE_NORMAL,NULL);
	if(FileHandle == INVALID_HANDLE_VALUE)
		return false;
	DWORD Size = ::GetFileSize(FileHandle,NULL);
	char* Buffer = new char[Size+1];
	memset(Buffer,'\0',Size+1);
	DWORD ReadBytes=0;
	::ReadFile(FileHandle,Buffer,Size,&ReadBytes,NULL);
	CString StrData=CString(Buffer);
	ParseData(StrData,QiuList);
	delete []Buffer;

	CloseHandle(FileHandle);

	//初始化横向差值
/*	InitHengXiangChaZhi(m_ShuangSeQiuList);

	//初始化纵向差值
	InitZongXiangChaZhi(m_ShuangSeQiuList);

	//初始化连号红球
	InitLianHaoHongQiu(m_ShuangSeQiuList);

	//初始化连号篮球
	InitLianHaoLanQiu(m_ShuangSeQiuList);
	*/



	return true;
}

//解析外部数据
void CDataManageCenter::ParseWaiBuData(CString& StrData,vector<sShuangSeQiu>& VectorData)
{
	int StartPos = StrData.ReverseFind('[');
	int EndPos = StrData.ReverseFind(']');
	CString QiShu=StrData.Mid(StartPos,EndPos-StartPos+1);
	CString Data = StrData.Mid(StartPos);
	Data.Replace(" + "," ");


	StartPos = 0;
	while(StartPos != -1)
	{
		StartPos = Data.Find("=",StartPos);
		if(StartPos == -1)
			break;

		EndPos =Data.Find(_T("\n"),StartPos);
		CString TempData=Data.Mid(StartPos+1,EndPos-StartPos-1);
		TempData+=_T(" ");
		TempData=QiShu+_T(" ")+TempData;
		sShuangSeQiu ShuangSeQiu = GetShuangSeQiuByStr(TempData);
		VectorData.push_back(ShuangSeQiu);
		StartPos=EndPos+1;
	}
}


//保存预测数据到文件中
void CDataManageCenter::SaveDataToFile(sYuCeShuangSeQiu& Data)
{
	//static int DiaoYongCount=0;
	//if(DiaoYongCount > 0)
	//	return;

	//DiaoYongCount++;
	//CString FilePath=GetAppCurrentPath2()+_T("yuce.txt");
	//
	//DWORD Flag = CREATE_ALWAYS;
	//HANDLE FileHandle=CreateFile(FilePath,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL,Flag,FILE_ATTRIBUTE_NORMAL,NULL);
	//if(FileHandle == INVALID_HANDLE_VALUE)
	//	return;

	//DWORD Flag2 = OPEN_EXISTING;
	//CString FilePath2 =_T("C:\\双色球预测大师\\预测结果.txt");
	//HANDLE FileHandle2=CreateFile(FilePath2,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL,Flag2,FILE_ATTRIBUTE_NORMAL,NULL);
	//if(FileHandle2 == INVALID_HANDLE_VALUE)
	//	return;

	//DWORD Size = ::GetFileSize(FileHandle2,NULL);
	//char* Buffer = new char[Size+1];
	//memset(Buffer,0,Size+1);
	//DWORD ReadBytes=0;
	//::ReadFile(FileHandle2,Buffer,Size,&ReadBytes,NULL);
	//CString StrData=CString(Buffer);
	//delete []Buffer;

	//vector<sShuangSeQiu> ShuangSeQiuList;
	//ParseWaiBuData(StrData,ShuangSeQiuList);

	//int HongCount[33];
	//memset(HongCount,0,33*sizeof(int));

	//CString DataStr=_T("自身预测值：\r\n");
	//map<eSuanFaType,sShuangSeQiu>::iterator it=Data.m_YuCeQiuMap.begin();
	//for(;it != Data.m_YuCeQiuMap.end();it++)
	//{
	//	
	//	for(int Index =0; Index < QIU_XUN; Index++)
	//	{
	//		CString HongQiuStr;
	//		HongQiuStr.Format(_T("%02d "),it->second.m_HongQiu[Index]);
	//		int TempData=it->second.m_HongQiu[Index];
	//		if( TempData> 0 && TempData <=QIU_COUNT)
	//			HongCount[TempData-1]++;
	//		DataStr+=HongQiuStr;

	//	}

	//	DataStr+=_T(";\r\n");
	//	
	//}

	//DataStr+=_T("\r\n\r\n\r\n");
	//CString NotEqualData=_T("自身过滤值：\r\n");
	//int Count=0;
	//for(int Index = 0; Index < QIU_COUNT; Index++)
	//{
	//	if(HongCount[Index])
	//	{
	//		CString TempData;
	//		TempData.Format("%02d ",Index+1);
	//		NotEqualData+=TempData;
	//		Count++;
	//	}
	//}
	//
	//CString CountStr;
	//CountStr.Format(_T("总个数：%d\r\n"),Count);
	//NotEqualData+=_T("\r\n\r\n");
	//NotEqualData+=CountStr;


	//CString YuCeStr=_T("神经网络预测：\r\n");
	//int HongCount2[QIU_COUNT];
	//memset(HongCount2,0,QIU_COUNT*sizeof(int));

	//for(int i=0; i < (int) ShuangSeQiuList.size();i++)
	//{
	//	for(int j = 0; j < QIU_XUN; j++)
	//	{
	//		CString HongQiuStr;
	//		HongQiuStr.Format(_T("%02d "),ShuangSeQiuList[i].m_HongQiu[j]);
	//		int TempData=ShuangSeQiuList[i].m_HongQiu[j];
	//		if( TempData> 0 && TempData <=QIU_COUNT)
	//			HongCount2[TempData-1]++;

	//		YuCeStr+=HongQiuStr;
	//	}

	//	YuCeStr+=_T(";\r\n");
	//}

	//YuCeStr+=_T("\r\n\r\n\r\n");
	//CString NotEqualData2=_T("神经网络过滤值：\r\n");
	//int Count2=0;
	//for(int Index = 0; Index < QIU_COUNT; Index++)
	//{
	//	if(HongCount2[Index])
	//	{
	//		CString TempData;
	//		TempData.Format("%02d ",Index+1);
	//		NotEqualData2+=TempData;
	//		Count2++;
	//	}
	//}

	//CString CountStr2;
	//CountStr2.Format(_T("总个数：%d\r\n"),Count2);
	//NotEqualData2+=_T("\r\n\r\n");
	//NotEqualData2+=CountStr2;

	//CString JiaoJi=_T("算法交集：\r\n");
	//int JiaoJiCount=0;
	//for(int Index = 0; Index < QIU_COUNT; Index++)
	//{
	//	if(HongCount2[Index] && HongCount[Index])
	//	{
	//		CString TempData;
	//		TempData.Format("%02d ",Index+1);
	//		JiaoJi+=TempData;
	//		JiaoJiCount++;
	//	}
	//}

	//JiaoJi+=_T("\r\n\r\n\r\n");
	//CString CountStr3;
	//CountStr3.Format(_T("交集总个数：%d\r\n"),JiaoJiCount);
	//JiaoJi+=_T("\r\n\r\n");
	//JiaoJi+=CountStr3;



	//DWORD WriteBytes=0;
	//::WriteFile(FileHandle,DataStr.GetBuffer(),DataStr.GetLength(),&WriteBytes,NULL);
	//::WriteFile(FileHandle,YuCeStr.GetBuffer(),YuCeStr.GetLength(),&WriteBytes,NULL);
	//::WriteFile(FileHandle,NotEqualData.GetBuffer(),NotEqualData.GetLength(),&WriteBytes,NULL);
	//::WriteFile(FileHandle,NotEqualData2.GetBuffer(),NotEqualData2.GetLength(),&WriteBytes,NULL);
	//::WriteFile(FileHandle,JiaoJi.GetBuffer(),JiaoJi.GetLength(),&WriteBytes,NULL);
	//CloseHandle(FileHandle);
	//CloseHandle(FileHandle2);


	//ShellExecute(NULL, "open",FilePath, NULL, NULL, SW_SHOWNORMAL);
}

//解析数据
void CDataManageCenter::ParseData(CString& StrData,vector<sShuangSeQiu>& VectorData)
{
	int StartPos=0;
	int EndPos=0;
	while(EndPos != -1)
	{
		EndPos=StrData.Find(";",StartPos);
		if(EndPos == -1)
			break;

		CString Temp=StrData.Mid(StartPos,EndPos-StartPos);
		if(Temp.Find("\n"))
			Temp=Temp.Mid(Temp.Find("\n")+1);
		if(!Temp.IsEmpty())
		{
			sShuangSeQiu ShuangSeQiu = GetShuangSeQiuByStr(Temp);
			VectorData.push_back(ShuangSeQiu);
		}
		StartPos = EndPos+1;
	}

}

//通过字符串获取双色球
sShuangSeQiu CDataManageCenter::GetShuangSeQiuByStr(CString& StrData)
{
	sShuangSeQiu ShuangSeQiu;

	int StartPos = 0;
	int EndPos   = 0;
	int Index = 0;
	int Count=0;
	while(EndPos != -1)
	{
		EndPos=StrData.Find(_T(" "),StartPos);
		if(EndPos == -1)
			break;

		if(Index == 0)
		{
			ShuangSeQiu.m_QiShu = StrData.Mid(StartPos,EndPos-StartPos);
		}
		else if(Index == 7)
		{
			CString Temp = StrData.Mid(StartPos,EndPos-StartPos);
			ShuangSeQiu.m_LanQiu = atoi(Temp.GetBuffer());
			Temp.ReleaseBuffer();
		}
		else
		{
			if(Index > QIU_XUN)
				continue;
			CString Temp = StrData.Mid(StartPos,EndPos-StartPos);
			ShuangSeQiu.m_HongQiu[Index-1]= atoi(Temp.GetBuffer());
			Temp.ReleaseBuffer();
			Count+=ShuangSeQiu.m_HongQiu[Index-1];
			if( ShuangSeQiu.m_HongQiu[Index-1] <= 11)
				ShuangSeQiu.m_QuJian[0]++;
			else if(ShuangSeQiu.m_HongQiu[Index-1] > 11 && ShuangSeQiu.m_HongQiu[Index-1] <= 22)
				ShuangSeQiu.m_QuJian[1]++;
			else
				ShuangSeQiu.m_QuJian[2]++;
		}

		Index++;
		StartPos = EndPos+1;
	}

	ShuangSeQiu.m_HongQiuSum = Count;
	m_ShuangSeQiuChuHaoList.push_back(ShuangSeQiu);
	for(int i = 0; i < QIU_XUN; i++)
	{
		for(int Index = 0 ; Index < QIU_XUN; Index++)
		{
			if(ShuangSeQiu.m_HongQiu[i] < ShuangSeQiu.m_HongQiu[Index])
			{
				int Temp1 = ShuangSeQiu.m_HongQiu[Index];
				ShuangSeQiu.m_HongQiu[Index]=ShuangSeQiu.m_HongQiu[i];
				ShuangSeQiu.m_HongQiu[i] = Temp1;
			}	
		}
	}

	return ShuangSeQiu;
}

//获取AC差值
int CDataManageCenter::GetACCount(sShuangSeQiu& ShuangSeQiu)
{
	int DataCount[QIU_COUNT];
	memset(DataCount,0,sizeof(int)*QIU_COUNT);

	for(int i=0; i < QIU_XUN; i++)
	{
		for(int g=i+1; g < QIU_XUN; g++)
		{
			int TempData=abs(ShuangSeQiu.m_HongQiu[i]-ShuangSeQiu.m_HongQiu[g]);
			DataCount[TempData]++;
		}
	}

	int Count=0;
	for(int Index=0; Index < QIU_COUNT; Index++)
	{
		if(DataCount[Index] > 0)
			Count++;
	}

	return Count-5;
}

//获取胆组数据
vector<map<int,CString>>* CDataManageCenter::GetDanZuDataList()
{
	return &m_DanZu;
}

//获取尾数预测参数
int CDataManageCenter::GetWeiZhiParam(sShuangSeQiu& ShuangSeQiu)
{
	int Data=0;
	for(int i=0; i < QIU_XUN; i++)
	{
		Data+=ShuangSeQiu.m_HongQiu[i] % 10;
	}

	int Data1 = Data / 10;
	int Data2 = Data % 10;
	return Data1+Data2;
}


//保存统计数据到csv文件中
void CDataManageCenter::SaveDataToCSVFile()
{


	 CString FilePath = GetAppCurrentPath2()+_T("\\chuqiushu.csv");

	HANDLE FileHandle=CreateFile(FilePath,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(FileHandle == INVALID_HANDLE_VALUE)
	{
		AfxMessageBox(_T("打开文件失败！"));
		return;
	}

	CString FilePath2 = GetAppCurrentPath2()+_T("\\zuihouchuqiushu.txt");

	HANDLE FileHandle2=CreateFile(FilePath2,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(FileHandle2 == INVALID_HANDLE_VALUE)
	{
		AfxMessageBox(_T("打开文件失败！"));
		return;
	}

	m_DanZu.clear();

	CString StrCSV;
	CString StrCSV2;
	CString StrText2=_T("球\t次数\r\n");

	for(int i = 0; i <= 33; i++)
	{
		CString Temp;
		Temp.Format(_T("%02d"),i);
		if( i != 33)
			Temp+=_T(",");
		else
			Temp+=_T("\n");

		StrCSV+=Temp;
	}


	int OffsetCount = 1;
	bool IsLast=false;

	map<int,vector<int>> TempMapList;

	for(int Index =0; Index < m_ShuangSeQiuList.size(); )
	{
		if(Index + OffsetCount < m_ShuangSeQiuList.size())
			Index+=OffsetCount;
		else
		{
			Index = m_ShuangSeQiuList.size();
			IsLast = true;
			
		}

		int DataArray[33][33]={0};
		for(int i=0; i < 33; i++)
		{
			for(int j = 0 ; j < (int)Index; j++)
			{
				bool IsWant=false;
				for(int k = 0; k < 6; k++)
				{
					if(m_ShuangSeQiuList[j].m_HongQiu[k] == i+1)
						IsWant=true;
				}
				
				if(!IsWant)
					continue;

				int Max=0;
				for(int k = 0; k < 6; k++)
				{
				/*	if(m_ShuangSeQiuList[j].m_HongQiu[k] == i+1)
						continue;*/

					int TempData = m_ShuangSeQiuList[j].m_HongQiu[k]-1;
					if(TempData != -1)
						DataArray[i][TempData]++;
				}

			}
		}


		

	

		

		/*for(int i = 0; i < 33; i++)
		{
			CString Temp;
			Temp.Format(_T("%02d,"),i+1);
			for(int j =0; j < 33; j++)
			{
				CString Temp2;
				Temp2.Format(_T("%02d"),DataArray[i][j]);
				Temp+=Temp2;
				if(j != 32)
					Temp+=_T(",");	
			}

			Temp+=_T("\n");

			StrCSV+=Temp;
		}*/

		int MaxData[33]={0};
		for(int i = 0; i < 33; i++)
		{
			int TempMax=0;
			for(int j =0; j < 33; j++)
			{
				if(TempMax < DataArray[i][j] && i != j)
				{
					TempMax=DataArray[i][j];
					MaxData[i]=j+1;
				}
			}
		}

		//StrCSV =_T("球,出球次数最多的球,出球次数,统计期数\n");
		CString Temp;
		CString Temp2;

		for(int i = 0; i < 33; i++)
		{
			/*CString Temp;
			Temp.Format(_T("%02d,%02d,%02d,%02d\n"),i+1,MaxData[i],DataArray[i][i],Index);
			StrCSV+=Temp;*/
		
			

			Temp2.Format(_T("%02d"),MaxData[i]);

			if( i != 32)
				Temp2+=_T(",");
			else
				Temp2+=_T("\n");

			Temp +=Temp2;

			
		}

		StrCSV+=_T("最大值,")+Temp;

		Temp2.Empty();
		Temp.Empty();
		


		for(int i = 0; i < 33; i++)
		{
			
			Temp2.Format(_T("%02d"),DataArray[i][i]);

			if( i != 32)
				Temp2+=_T(",");
			else
				Temp2+=_T("\n");

			Temp += Temp2;

		//	if(IsLast)
			{
				int TempData = DataArray[i][i];
				TempMapList[TempData].push_back(i+1);
			}
			
		}
		StrCSV2+=_T("出球次数,")+Temp;

		if(Index !=  m_ShuangSeQiuList.size())
			StrText2+=m_ShuangSeQiuList[Index].m_QiShu+=":\r\n";

		
		map<int,vector<int>>::iterator it=TempMapList.begin();

		
		int QuCount=0;
		map<int,CString> TempMap;

		for(it; it != TempMapList.end(); it++)
		{
			CString FormatStr;
			FormatStr.Format("%02d: ",it->first);
			CString MapStr;

			vector<int> TempData;
			for(int i=0; i < it->second.size(); i++)
			{
				CString TempStr;
				TempStr.Format(_T("%02d "),it->second[i]);
				FormatStr+=TempStr;
				MapStr+=TempStr;

				for(int j=0; j < 6; j++)
				{
					if( Index !=  m_ShuangSeQiuList.size() && m_ShuangSeQiuList[Index].m_HongQiu[j] == it->second[i])
						TempData.push_back(it->second[i]);
				}
			}


			TempMap[QuCount]=MapStr;
			QuCount++;



			for(int i = FormatStr.GetLength(); i < 50;i++)
				FormatStr+=" ";

			StrText2 +=FormatStr+"==》";
			for(int i = 0; i < TempData.size(); i++)
			{
				CString TempDataStr;
				if( TempData[i]!=0)
					TempDataStr.Format("%02d ",TempData[i]);
				StrText2+=TempDataStr;
			}

			StrText2 +="\r\n";
		}

		m_DanZu.push_back(TempMap);
		StrText2+="\r\n\r\n";
		TempMapList.clear();
		
	}

	

	/*map<int,vector<int>>::iterator it=TempMapList.begin();
	for(it; it != TempMapList.end(); it++)
	{
		for(int Index=0; Index < it->second.size(); Index++)
		{
			CString TempStr;
			TempStr.Format(_T("%02d\t%02d\r\n"),it->second[Index],it->first);
			StrText2+=TempStr;
		}
	}*/

	StrCSV +=_T("\n\n\n")+StrCSV2;
	DWORD WriteBytes=0;
	::WriteFile(FileHandle,StrCSV.GetBuffer(),StrCSV.GetLength(),&WriteBytes,NULL);
	
	WriteBytes=0;
	::WriteFile(FileHandle2,StrText2.GetBuffer(),StrText2.GetLength(),&WriteBytes,NULL);

	CloseHandle(FileHandle);
	CloseHandle(FileHandle2);

	//ShellExecute(NULL, "open",FilePath, NULL, NULL, SW_SHOWNORMAL);
	//ShellExecute(NULL, "open",FilePath2, NULL, NULL, SW_SHOWNORMAL);
}


//保存统计五期以内和五期以外数据到txt文件中
void CDataManageCenter::SaveFiveDataToTxtFile()
{
	CString  WriteStr;
	CString  WriteStr2=_T("\r\n\r\n\r\n");
	CString WuQiStr;
	for(int Index =4; Index < m_ShuangSeQiuList.size(); Index++)
	{
		

		int Data[33]={0};
		int DataArray[33][5];
		memset(DataArray,0,33*5*sizeof(int));

		for(int i=4; i >= 0; i--)
		{
			for(int j=0; j < 6; j++)
			{
				int TempData = m_ShuangSeQiuList[Index-i].m_HongQiu[j]-1;
				DataArray[TempData][i]=1;
				if(TempData >= 0)
					Data[TempData]++;
			}
		}

		int Count=0;
		CString WuQiYiWai;
	    CString WuQiYiNei;
		
		CString TempWuQi=m_ShuangSeQiuList[Index].m_QiShu+"：\r\n";;
		for(int i=0; i < 5; i++)
		{
			for(int j=1; j < 5; j++)
			{

			}

			CString TempStr;
			TempStr.Format("%02d： ",i);
			CString TempStr2;
			for(int k=0; k < 33; k++)
			{
				if(DataArray[k][i])
				{
					CString TempStr3;
					TempStr3.Format("%02d ",k+1);
					TempStr2+=TempStr3;

				}
			}
			TempStr2+="\r\n";
			TempStr+=TempStr2;
			TempWuQi+=TempStr;
		}

		WuQiStr+=TempWuQi+"\r\n\r\n";
		for(int k=0; k < 33; k++)
		{
			CString TempStr;
			TempStr.Format(_T("%02d "),k+1);

			if(Data[k])
			{	
				Count++;
				WuQiYiNei+=TempStr;
			}
			else
			{
				WuQiYiWai+=TempStr;
			}
		}

		CString ChuQiu;
		if(Index+1 != m_ShuangSeQiuList.size())
		{
			int Count=0;
			for(int i=0; i < 6; i++)
			{
				int TempData = m_ShuangSeQiuList[Index+1].m_HongQiu[i];
				CString TempStr;
				TempStr.Format(_T("%02d "),TempData);
				if(Data[TempData-1])
					Count++;
				ChuQiu += TempStr;
			}

			ChuQiu= m_ShuangSeQiuList[Index+1].m_QiShu+_T(" ")+ChuQiu;
			CString Temp;
			Temp.Format(_T("     五期以内出球个数：%02d    五期以外出球个数：%02d\r\n"),Count,6-Count);
			ChuQiu+=Temp;
			WriteStr2+=ChuQiu;
		}

		CString Temp;
		Temp.Format(_T("    个数%02d\r\n"),Count);
		WuQiYiNei+=Temp;
		Temp.Empty();
		Temp.Format(_T("    个数%02d\r\n"),33-Count);
		WuQiYiWai+=Temp;

		 WriteStr+=WuQiYiNei+WuQiYiWai;
		 if(!ChuQiu.IsEmpty())
			  WriteStr+=ChuQiu;
			
		 if((Index) % 4)
		 {
			 WriteStr+=_T("\r\n");
		//	 WriteStr2+=_T("\r\n");
			 
		 }
		 else
		 {
			 WriteStr+=_T("\r\n\r\n\r\n");
			// WriteStr2+=_T("\r\n\r\n\r\n");
		 }
	}

	CString FilePath2 = GetAppCurrentPath2()+_T("\\wuqitongji.txt");

	HANDLE FileHandle2=CreateFile(FilePath2,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(FileHandle2 == INVALID_HANDLE_VALUE)
	{
		AfxMessageBox(_T("打开文件失败！"));
		return;
	}
	CString FilePath3=GetAppCurrentPath2()+_T("\\wuqixiangqing.txt");
	HANDLE FileHandle3=CreateFile(FilePath3,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(FileHandle3 == INVALID_HANDLE_VALUE)
	{
		AfxMessageBox(_T("打开文件失败！"));
		return;
	}
		
	DWORD WriteBytes=0;
	::WriteFile(FileHandle2,WriteStr.GetBuffer(),WriteStr.GetLength(),&WriteBytes,NULL);
	::WriteFile(FileHandle2,WriteStr2.GetBuffer(),WriteStr2.GetLength(),&WriteBytes,NULL);
	::WriteFile(FileHandle3,WuQiStr.GetBuffer(), WuQiStr.GetLength(),&WriteBytes,NULL);
	CloseHandle(FileHandle2);
	CloseHandle(FileHandle3);
//	ShellExecute(NULL, "open",FilePath2, NULL, NULL, SW_SHOWNORMAL);
}

//保存29组统计数据到txt文件中
void CDataManageCenter::Save29DataToTxtFile()
{
	CString  WriteStr;
	CString FilePath2 = GetAppCurrentPath2()+_T("\\tongji29zu.txt");

	HANDLE FileHandle2=CreateFile(FilePath2,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(FileHandle2 == INVALID_HANDLE_VALUE)
	{
		AfxMessageBox(_T("打开文件失败！"));
		return;
	}

	
	for(int Index = 0; Index < this->m_ShuangSeQiuList.size(); Index++)
	{
		vector<int> VecIndex;
		for(int i=0; i< m_Data29.size(); i++)
		{
			int Count=0;
			for(int j =0; j < m_Data29[i].m_WeiHong.size(); j++)
			{
				bool IsWant=false;
				for(int k=0; k < 6; k++)
				{
					if(m_ShuangSeQiuList[Index].m_HongQiu[k] == m_Data29[i].m_WeiHong[j])
					{
						IsWant=true;
						break;
					}
				}

				if(IsWant)
				{
					Count++;
					//break;
				}
			}
			
			if(Count == 6)
			{
				VecIndex.push_back(i);

			}
		}

		int ArrayData[33];
		memset(ArrayData,0,sizeof(int)*33);

		CString IndexStr;
		for(int f =0; f < VecIndex.size(); f++)
		{
			CString TempStr;
			TempStr.Format("%02d ",VecIndex[f]+1);
			IndexStr +=TempStr;
			for(int j=0; j <  m_Data29[VecIndex[f]].m_WeiHong.size(); j++)
			{
				int TempData= m_Data29[VecIndex[f]].m_WeiHong[j]-1;
				ArrayData[TempData]++;
			}
		}

		int DataCount=0;
		CString Str;
		for(int g=0; g < 33;g++)
		{
			if(ArrayData[g] == VecIndex.size())
			{
				CString TempStr;
				TempStr.Format("%02d ",g+1);
				Str+=TempStr;
				DataCount++;
			}
		}

		for(int h=Str.GetLength(); h < 80; h++)
			Str+=" ";
		CString DataStr;
		DataStr.Format("个数：%02d",DataCount);
		Str+=DataStr;

		CString QiuStr=m_ShuangSeQiuList[Index].m_QiShu;
		if(Index==0)
			QiuStr+="\r\n";
		QiuStr+=" ";
		for(int k=0; k < 6; k++)
		{
			CString TempStr;
			TempStr.Format("%02d ",m_ShuangSeQiuList[Index].m_HongQiu[k]);
			QiuStr+=TempStr;
		}

		for(int f=IndexStr.GetLength(); f < 36; f++)
			IndexStr+=" ";
		WriteStr+=QiuStr+"  所属组："+IndexStr+" 交集："+Str+"\r\n";
	}

	DWORD WriteBytes=0;
	::WriteFile(FileHandle2,WriteStr.GetBuffer(),WriteStr.GetLength(),&WriteBytes,NULL);
	CloseHandle(FileHandle2);
}

//球是否在红球中
bool CDataManageCenter::IsHongQiuInData(sShuangSeQiu QiuData,int Data,bool IsV)
{
	bool Ret=false;
	for(int Index = 0; Index < QIU_XUN; Index++)
	{
		if(!IsV)
		{
			if(QiuData.m_HongQiu[Index] == Data)
			{
				Ret = true;
				break;
			}
		}
		else
		{
			if(QiuData.m_HongQiu[Index]%10 == Data%10)
			{
				Ret = true;
				break;
			}

		}
	}

	return Ret;
}



//球是否在红球前三中
bool CDataManageCenter::IsHongQiuInQianSanData(sShuangSeQiu QiuData,int Data,bool IsV)
{
	bool Ret=false;
	for(int Index = 0; Index < 3; Index++)
	{
		if(!IsV)
		{
			if(QiuData.m_HongQiu[Index] == Data)
			{
				Ret = true;
				break;
			}
		}
		else
		{
			if(QiuData.m_HongQiu[Index]%10 == Data%10)
			{
				Ret = true;
				break;
			}

		}
	}

	return Ret;
}

//球是否在红球后三中
bool CDataManageCenter::IsHongQiuInHouSanData(sShuangSeQiu QiuData,int Data,bool IsV)
{
	bool Ret=false;
	for(int Index = 3; Index < QIU_XUN; Index++)
	{
		if(!IsV)
		{
			if(QiuData.m_HongQiu[Index] == Data)
			{
				Ret = true;
				break;
			}
		}
		else
		{
			if(QiuData.m_HongQiu[Index]%10 == Data%10)
			{
				Ret = true;
				break;
			}

		}
	}

	return Ret;
}


//球是否在红球合中
bool CDataManageCenter::IsHongQiuInHeData(sShuangSeQiu QiuData,int Data,bool IsV)
{
	bool Ret=false;
	for(int Index = 0; Index < QIU_XUN; Index++)
	{
		if(!IsV)
		{
			if((QiuData.m_HongQiu[Index]%10+ QiuData.m_HongQiu[Index]/10)== (Data%10+Data/10))
			{
				Ret = true;
				break;
			}
		}
		else
		{
			if((QiuData.m_HongQiu[Index]%10+ QiuData.m_HongQiu[Index]/10)%10== (Data%10+Data/10)%10)
			{
				Ret = true;
				break;
			}

		}
	}

	return Ret;
}

//球是否在红球合前三中
bool CDataManageCenter::IsHongQiuInHeQianSanData(sShuangSeQiu QiuData,int Data,bool IsV)
{
	bool Ret=false;
	for(int Index = 0; Index < 3; Index++)
	{
		if(!IsV)
		{
			if((QiuData.m_HongQiu[Index]%10+ QiuData.m_HongQiu[Index]/10)== (Data%10+Data/10))
			{
				Ret = true;
				break;
			}
		}
		else
		{
			if((QiuData.m_HongQiu[Index]%10+ QiuData.m_HongQiu[Index]/10)%10== (Data%10+Data/10)%10)
			{
				Ret = true;
				break;
			}

		}
	}

	return Ret;
}

//球是否在红球合后三中
bool CDataManageCenter::IsHongQiuInHeHouSanData(sShuangSeQiu QiuData,int Data,bool IsV)
{
	bool Ret=false;
	for(int Index = 3; Index < QIU_XUN; Index++)
	{
		if(!IsV)
		{
			if((QiuData.m_HongQiu[Index]%10+ QiuData.m_HongQiu[Index]/10)== (Data%10+Data/10))
			{
				Ret = true;
				break;
			}
		}
		else
		{
			if((QiuData.m_HongQiu[Index]%10+ QiuData.m_HongQiu[Index]/10)%10== (Data%10+Data/10)%10)
			{
				Ret = true;
				break;
			}

		}
	}

	return Ret;
}


//球是否在红球差中
bool CDataManageCenter::IsHongQiuInChaData(sShuangSeQiu QiuData,int Data,bool IsV)
{
	bool Ret=false;
	for(int Index = 0; Index < QIU_XUN; Index++)
	{
		if(!IsV)
		{
			if(abs(QiuData.m_HongQiu[Index]%10- QiuData.m_HongQiu[Index]/10)== abs(Data%10-Data/10))
			{
				Ret = true;
				break;
			}
		}
		else
		{
			if(abs(QiuData.m_HongQiu[Index]%10- QiuData.m_HongQiu[Index]/10)%10== abs(Data%10-Data/10)%10)
			{
				Ret = true;
				break;
			}

		}
	}

	return Ret;
}

//球是否在红球差中
bool CDataManageCenter::IsHongQiuInChaQianSanData(sShuangSeQiu QiuData,int Data,bool IsV)
{
	bool Ret=false;
	for(int Index = 0; Index < 3; Index++)
	{
		if(!IsV)
		{
			if(abs(QiuData.m_HongQiu[Index]%10- QiuData.m_HongQiu[Index]/10)== abs(Data%10-Data/10))
			{
				Ret = true;
				break;
			}
		}
		else
		{
			if(abs(QiuData.m_HongQiu[Index]%10- QiuData.m_HongQiu[Index]/10)%10== abs(Data%10-Data/10)%10)
			{
				Ret = true;
				break;
			}

		}
	}

	return Ret;
}

//球是否在红球差中
bool CDataManageCenter::IsHongQiuInChaHouSanData(sShuangSeQiu QiuData,int Data,bool IsV)
{
	bool Ret=false;
	for(int Index = 3; Index < QIU_XUN; Index++)
	{
		if(!IsV)
		{
			if(abs(QiuData.m_HongQiu[Index]%10- QiuData.m_HongQiu[Index]/10)== abs(Data%10-Data/10))
			{
				Ret = true;
				break;
			}
		}
		else
		{
			if(abs(QiuData.m_HongQiu[Index]%10- QiuData.m_HongQiu[Index]/10)%10== abs(Data%10-Data/10)%10)
			{
				Ret = true;
				break;
			}

		}
	}

	return Ret;
}

//球是否在位数中
bool CDataManageCenter::IsHongQiuWeiData(sShuangSeQiu QiuData,int Data,int WeiShu,bool IsV)
{
	bool Ret=false;
	for(int Index = 0; Index < QIU_XUN; Index++)
	{
		if(!IsV)
		{
			if(QiuData.m_HongQiu[Index] == Data && Index == WeiShu)
			{
				Ret = true;
				break;
			}
		}
		else
		{
			if(QiuData.m_HongQiu[Index]%10 == Data%10 && Index ==WeiShu)
			{
				Ret = true;
				break;
			}

		}
	}

	return Ret;
}

//球是否在红球区间中
bool CDataManageCenter::IsHongQiuQuJianInData(sShuangSeQiu QiuData,int BeginData,int EndData,int WeiShu,bool IsV)
{
	bool Ret=false;
	for(int Index = 0; Index < QIU_XUN; Index++)
	{
		if(!IsV)
		{
			if( Index == WeiShu && QiuData.m_HongQiu[Index] >=BeginData &&QiuData.m_HongQiu[Index] <= EndData)
			{
				Ret = true;
				break;
			}
		}
		else
		{
			if(Index ==WeiShu && QiuData.m_HongQiu[Index]%10 >= BeginData%10 && QiuData.m_HongQiu[Index]%10 <= EndData%10 )
			{
				Ret = true;
				break;
			}

		}
	}

	return Ret;
}

//球是否等于极距中
bool CDataManageCenter::IsHongJiJuInData(sShuangSeQiu QiuData,int Data)
{
	int TempData = abs(QiuData.m_HongQiu[5] - QiuData.m_HongQiu[0]) ;
	if(Data == TempData)
		return true;

	return false;
}

//球是否在篮球中
bool CDataManageCenter::IsLanQiuInData(sShuangSeQiu QiuData,int Data,bool IsV)
{

	if(!IsV&&QiuData.m_LanQiu == Data)
		return true;

	if(IsV)
	{
		if(QiuData.m_LanQiu == Data || QiuData.m_LanQiu%10 == Data)
			return true;
		return false;
	}

	return false;
}

//判断数据是否为合数
bool CDataManageCenter::IsHeShuData(int Data)
{
	if(Data == 1 || Data == 2)
		return false;

	if(Data % 2 == 0)
		return true;

	if(Data % 3 == 0)
		return true;

	return false;
}

//获取质数个数
int CDataManageCenter::GetZhiShuCount(sShuangSeQiu QiuData)
{
	int Count=0;
	for(int Index = 0; Index < 6; Index++)
	{
		if(QiuData.m_HongQiu[Index] == 1 || QiuData.m_HongQiu[Index] == 2 || QiuData.m_HongQiu[Index]== 3)
		{
			Count++;
			continue;
		}
		if(QiuData.m_HongQiu[Index] %2 != 0 && QiuData.m_HongQiu[Index] %3 != 0)
			Count++;
	}

	return Count;
}


CString CDataManageCenter::GetDataStr(int Data,bool IsTrue,bool IsV)
{
	CString TempStr;
	TempStr.Format("%02d",Data);
	if(IsV)
		TempStr+="V";

	/*if(IsTrue)
		TempStr+="S";
	else
		TempStr+="F";*/

	return TempStr;

}

//初始化29组数据
void CDataManageCenter::Init29Data()
{
	sData29 Data;

	//04 06 08 13 18 19 27 29 31
	Data.m_JueSha.push_back(4);
	Data.m_JueSha.push_back(6);
	Data.m_JueSha.push_back(8);
	Data.m_JueSha.push_back(13);
	Data.m_JueSha.push_back(18);
	Data.m_JueSha.push_back(19);
	Data.m_JueSha.push_back(27);
	Data.m_JueSha.push_back(29);
	Data.m_JueSha.push_back(31);
	Data.m_BianHao="一";
	InitOneData(Data);
	m_Data29.push_back(Data);
	Data.m_JueSha.clear();
	Data.m_WeiHong.clear();

    //03 06 11 19 20 21 24 31 33
	Data.m_BianHao="  二";
	Data.m_JueSha.push_back(3);
	Data.m_JueSha.push_back(6);
	Data.m_JueSha.push_back(11);
	Data.m_JueSha.push_back(19);
	Data.m_JueSha.push_back(20);
	Data.m_JueSha.push_back(21);
	Data.m_JueSha.push_back(24);
	Data.m_JueSha.push_back(31);
	Data.m_JueSha.push_back(33);
	InitOneData(Data);
	m_Data29.push_back(Data);
	Data.m_JueSha.clear();
	Data.m_WeiHong.clear();

	//03 06 07 17 19 20 31 32 33
	Data.m_BianHao="  三";
	Data.m_JueSha.push_back(3);
	Data.m_JueSha.push_back(6);
	Data.m_JueSha.push_back(7);
	Data.m_JueSha.push_back(17);
	Data.m_JueSha.push_back(19);
	Data.m_JueSha.push_back(20);
	Data.m_JueSha.push_back(31);
	Data.m_JueSha.push_back(32);
	Data.m_JueSha.push_back(33);
	InitOneData(Data);
	m_Data29.push_back(Data);
	Data.m_JueSha.clear();
	Data.m_WeiHong.clear();

	//01 02 06 14 16 19 25 28 31
	Data.m_BianHao="  四";
	Data.m_JueSha.push_back(1);
	Data.m_JueSha.push_back(2);
	Data.m_JueSha.push_back(6);
	Data.m_JueSha.push_back(14);
	Data.m_JueSha.push_back(16);
	Data.m_JueSha.push_back(19);
	Data.m_JueSha.push_back(25);
	Data.m_JueSha.push_back(28);
	Data.m_JueSha.push_back(31);
	InitOneData(Data);
	m_Data29.push_back(Data);
	Data.m_JueSha.clear();
	Data.m_WeiHong.clear();

	//02 05 10 12 15 16 25 26 30
	Data.m_BianHao="  五";
	Data.m_JueSha.push_back(2);
	Data.m_JueSha.push_back(5);
	Data.m_JueSha.push_back(10);
	Data.m_JueSha.push_back(12);
	Data.m_JueSha.push_back(15);
	Data.m_JueSha.push_back(16);
	Data.m_JueSha.push_back(25);
	Data.m_JueSha.push_back(26);
	Data.m_JueSha.push_back(30);
	InitOneData(Data);
	m_Data29.push_back(Data);
	Data.m_JueSha.clear();
	Data.m_WeiHong.clear();


	//06 07 11 17 19 21 24 31 32
	Data.m_BianHao="  六";
	Data.m_JueSha.push_back(6);
	Data.m_JueSha.push_back(7);
	Data.m_JueSha.push_back(11);
	Data.m_JueSha.push_back(17);
	Data.m_JueSha.push_back(19);
	Data.m_JueSha.push_back(21);
	Data.m_JueSha.push_back(24);
	Data.m_JueSha.push_back(31);
	Data.m_JueSha.push_back(32);
	InitOneData(Data);
	m_Data29.push_back(Data);
	Data.m_JueSha.clear();
	Data.m_WeiHong.clear();

	//05 06 08 15 18 19 29 30 31
	Data.m_BianHao="  七";
	Data.m_JueSha.push_back(5);
	Data.m_JueSha.push_back(6);
	Data.m_JueSha.push_back(8);
	Data.m_JueSha.push_back(15);
	Data.m_JueSha.push_back(18);
	Data.m_JueSha.push_back(19);
	Data.m_JueSha.push_back(29);
	Data.m_JueSha.push_back(30);
	Data.m_JueSha.push_back(31);
	InitOneData(Data);
	m_Data29.push_back(Data);
	Data.m_JueSha.clear();
	Data.m_WeiHong.clear();

	//06 09 10 12 19 22 23 26 31
	Data.m_BianHao="  八";
	Data.m_JueSha.push_back(6);
	Data.m_JueSha.push_back(9);
	Data.m_JueSha.push_back(10);
	Data.m_JueSha.push_back(12);
	Data.m_JueSha.push_back(19);
	Data.m_JueSha.push_back(22);
	Data.m_JueSha.push_back(23);
	Data.m_JueSha.push_back(26);
	Data.m_JueSha.push_back(31);
	InitOneData(Data);
	m_Data29.push_back(Data);
	Data.m_JueSha.clear();
	Data.m_WeiHong.clear();

	//05 07 09 15 17 22 23 30 32
	Data.m_BianHao="  九";
	Data.m_JueSha.push_back(5);
	Data.m_JueSha.push_back(7);
	Data.m_JueSha.push_back(9);
	Data.m_JueSha.push_back(15);
	Data.m_JueSha.push_back(17);
	Data.m_JueSha.push_back(22);
	Data.m_JueSha.push_back(23);
	Data.m_JueSha.push_back(30);
	Data.m_JueSha.push_back(32);
	InitOneData(Data);
	m_Data29.push_back(Data);
	Data.m_JueSha.clear();
	Data.m_WeiHong.clear();

	// 01 03 04 13 14 20 27 28 33
	Data.m_BianHao="  十";
	Data.m_JueSha.push_back(1);
	Data.m_JueSha.push_back(3);
	Data.m_JueSha.push_back(4);
	Data.m_JueSha.push_back(13);
	Data.m_JueSha.push_back(14);
	Data.m_JueSha.push_back(20);
	Data.m_JueSha.push_back(27);
	Data.m_JueSha.push_back(28);
	Data.m_JueSha.push_back(33);
	InitOneData(Data);
	m_Data29.push_back(Data);
	Data.m_JueSha.clear();
	Data.m_WeiHong.clear();

	//02 07 08 16 17 18 25 29 32
	Data.m_BianHao="十一";
	Data.m_JueSha.push_back(2);
	Data.m_JueSha.push_back(7);
	Data.m_JueSha.push_back(8);
	Data.m_JueSha.push_back(16);
	Data.m_JueSha.push_back(17);
	Data.m_JueSha.push_back(18);
	Data.m_JueSha.push_back(25);
	Data.m_JueSha.push_back(29);
	Data.m_JueSha.push_back(32);
	InitOneData(Data);
	m_Data29.push_back(Data);
	Data.m_JueSha.clear();
	Data.m_WeiHong.clear();

	//01 04 11 13 14 21 24 27 28
	Data.m_BianHao="十二";
	Data.m_JueSha.push_back(1);
	Data.m_JueSha.push_back(4);
	Data.m_JueSha.push_back(11);
	Data.m_JueSha.push_back(13);
	Data.m_JueSha.push_back(14);
	Data.m_JueSha.push_back(21);
	Data.m_JueSha.push_back(24);
	Data.m_JueSha.push_back(27);
	Data.m_JueSha.push_back(28);
	InitOneData(Data);
	m_Data29.push_back(Data);
	Data.m_JueSha.clear();
	Data.m_WeiHong.clear();

	//02 09 11 16 21 22 23 24 25
	Data.m_BianHao="十三";
	Data.m_JueSha.push_back(2);
	Data.m_JueSha.push_back(9);
	Data.m_JueSha.push_back(11);
	Data.m_JueSha.push_back(16);
	Data.m_JueSha.push_back(21);
	Data.m_JueSha.push_back(22);
	Data.m_JueSha.push_back(23);
	Data.m_JueSha.push_back(24);
	Data.m_JueSha.push_back(25);
	InitOneData(Data);
	m_Data29.push_back(Data);
	Data.m_JueSha.clear();
	Data.m_WeiHong.clear();

	//04 05 09 13 15 22 23 27 30
	Data.m_BianHao="十四";
	Data.m_JueSha.push_back(4);
	Data.m_JueSha.push_back(5);
	Data.m_JueSha.push_back(9);
	Data.m_JueSha.push_back(13);
	Data.m_JueSha.push_back(15);
	Data.m_JueSha.push_back(22);
	Data.m_JueSha.push_back(23);
	Data.m_JueSha.push_back(27);
	Data.m_JueSha.push_back(30);
	InitOneData(Data);
	m_Data29.push_back(Data);
	Data.m_JueSha.clear();
	Data.m_WeiHong.clear();

	//04 07 09 13 17 22 23 27 32
	Data.m_BianHao="十五";
	Data.m_JueSha.push_back(4);
	Data.m_JueSha.push_back(7);
	Data.m_JueSha.push_back(9);
	Data.m_JueSha.push_back(13);
	Data.m_JueSha.push_back(17);
	Data.m_JueSha.push_back(22);
	Data.m_JueSha.push_back(23);
	Data.m_JueSha.push_back(27);
	Data.m_JueSha.push_back(32);
	InitOneData(Data);
	m_Data29.push_back(Data);
	Data.m_JueSha.clear();
	Data.m_WeiHong.clear();

	//04 05 10 12 13 16 25 26 27
	Data.m_BianHao="十六";
	Data.m_JueSha.push_back(4);
	Data.m_JueSha.push_back(5);
	Data.m_JueSha.push_back(10);
	Data.m_JueSha.push_back(12);
	Data.m_JueSha.push_back(13);
	Data.m_JueSha.push_back(16);
	Data.m_JueSha.push_back(25);
	Data.m_JueSha.push_back(26);
	Data.m_JueSha.push_back(27);
	InitOneData(Data);
	m_Data29.push_back(Data);
	Data.m_JueSha.clear();
	Data.m_WeiHong.clear();

	//02 04 10 12 13 16 25 26 27
	Data.m_BianHao="十七";
	Data.m_JueSha.push_back(2);
	Data.m_JueSha.push_back(4);
	Data.m_JueSha.push_back(10);
	Data.m_JueSha.push_back(12);
	Data.m_JueSha.push_back(13);
	Data.m_JueSha.push_back(16);
	Data.m_JueSha.push_back(25);
	Data.m_JueSha.push_back(26);
	Data.m_JueSha.push_back(27);
	InitOneData(Data);
	m_Data29.push_back(Data);
	Data.m_JueSha.clear();
	Data.m_WeiHong.clear();

	//02 04 05 13 15 16 25 27 30
	Data.m_BianHao="十八";
	Data.m_JueSha.push_back(2);
	Data.m_JueSha.push_back(4);
	Data.m_JueSha.push_back(5);
	Data.m_JueSha.push_back(13);
	Data.m_JueSha.push_back(15);
	Data.m_JueSha.push_back(16);
	Data.m_JueSha.push_back(25);
	Data.m_JueSha.push_back(27);
	Data.m_JueSha.push_back(30);
	InitOneData(Data);
	m_Data29.push_back(Data);
	Data.m_JueSha.clear();
	Data.m_WeiHong.clear();

	//04 05 07 13 15 17 27 30 32
	Data.m_BianHao="十九";
	Data.m_JueSha.push_back(4);
	Data.m_JueSha.push_back(5);
	Data.m_JueSha.push_back(7);
	Data.m_JueSha.push_back(13);
	Data.m_JueSha.push_back(15);
	Data.m_JueSha.push_back(17);
	Data.m_JueSha.push_back(27);
	Data.m_JueSha.push_back(30);
	Data.m_JueSha.push_back(32);
	InitOneData(Data);
	m_Data29.push_back(Data);
	Data.m_JueSha.clear();
	Data.m_WeiHong.clear();

	//01 03 05 14 15 20 28 30 33
	Data.m_BianHao="二十";
	Data.m_JueSha.push_back(1);
	Data.m_JueSha.push_back(3);
	Data.m_JueSha.push_back(5);
	Data.m_JueSha.push_back(14);
	Data.m_JueSha.push_back(15);
	Data.m_JueSha.push_back(20);
	Data.m_JueSha.push_back(28);
	Data.m_JueSha.push_back(30);
	Data.m_JueSha.push_back(33);
	InitOneData(Data);
	m_Data29.push_back(Data);
	Data.m_JueSha.clear();
	Data.m_WeiHong.clear();

	//03 08 11 18 20 21 24 29 33
	Data.m_BianHao="二一";
	Data.m_JueSha.push_back(3);
	Data.m_JueSha.push_back(8);
	Data.m_JueSha.push_back(11);
	Data.m_JueSha.push_back(18);
	Data.m_JueSha.push_back(20);
	Data.m_JueSha.push_back(21);
	Data.m_JueSha.push_back(24);
	Data.m_JueSha.push_back(29);
	Data.m_JueSha.push_back(33);
	InitOneData(Data);
	m_Data29.push_back(Data);
	Data.m_JueSha.clear();
	Data.m_WeiHong.clear();

	//03 10 11 12 20 21 24 26 33
	Data.m_BianHao="二二";
	Data.m_JueSha.push_back(3);
	Data.m_JueSha.push_back(10);
	Data.m_JueSha.push_back(11);
	Data.m_JueSha.push_back(12);
	Data.m_JueSha.push_back(20);
	Data.m_JueSha.push_back(21);
	Data.m_JueSha.push_back(24);
	Data.m_JueSha.push_back(26);
	Data.m_JueSha.push_back(33);
	InitOneData(Data);
	m_Data29.push_back(Data);
	Data.m_JueSha.clear();
	Data.m_WeiHong.clear();

	//03 07 11 17 20 21 24 32 33
	Data.m_BianHao="二三";
	Data.m_JueSha.push_back(3);
	Data.m_JueSha.push_back(7);
	Data.m_JueSha.push_back(11);
	Data.m_JueSha.push_back(17);
	Data.m_JueSha.push_back(20);
	Data.m_JueSha.push_back(21);
	Data.m_JueSha.push_back(24);
	Data.m_JueSha.push_back(32);
	Data.m_JueSha.push_back(33);
	InitOneData(Data);
	m_Data29.push_back(Data);
	Data.m_JueSha.clear();
	Data.m_WeiHong.clear();

	//03 08 10 12 18 20 26 29 33
	Data.m_BianHao="二四";
	Data.m_JueSha.push_back(3);
	Data.m_JueSha.push_back(8);
	Data.m_JueSha.push_back(10);
	Data.m_JueSha.push_back(12);
	Data.m_JueSha.push_back(18);
	Data.m_JueSha.push_back(20);
	Data.m_JueSha.push_back(26);
	Data.m_JueSha.push_back(29);
	Data.m_JueSha.push_back(33);
	InitOneData(Data);
	m_Data29.push_back(Data);
	Data.m_JueSha.clear();
	Data.m_WeiHong.clear();

	//02 03 09 16 20 22 23 25 33
	Data.m_BianHao="二五";
	Data.m_JueSha.push_back(2);
	Data.m_JueSha.push_back(3);
	Data.m_JueSha.push_back(9);
	Data.m_JueSha.push_back(16);
	Data.m_JueSha.push_back(20);
	Data.m_JueSha.push_back(22);
	Data.m_JueSha.push_back(23);
	Data.m_JueSha.push_back(25);
	Data.m_JueSha.push_back(33);
	InitOneData(Data);
	m_Data29.push_back(Data);
	Data.m_JueSha.clear();
	Data.m_WeiHong.clear();

	//08 10 11 12 18 21 24 26 29
	Data.m_BianHao="二六";
	Data.m_JueSha.push_back(8);
	Data.m_JueSha.push_back(10);
	Data.m_JueSha.push_back(11);
	Data.m_JueSha.push_back(12);
	Data.m_JueSha.push_back(18);
	Data.m_JueSha.push_back(21);
	Data.m_JueSha.push_back(24);
	Data.m_JueSha.push_back(26);
	Data.m_JueSha.push_back(29);
	InitOneData(Data);
	m_Data29.push_back(Data);
	Data.m_JueSha.clear();
	Data.m_WeiHong.clear();

	//01 05 11 14 15 21 24 28 30
	Data.m_BianHao="二七";
	Data.m_JueSha.push_back(1);
	Data.m_JueSha.push_back(5);
	Data.m_JueSha.push_back(11);
	Data.m_JueSha.push_back(14);
	Data.m_JueSha.push_back(15);
	Data.m_JueSha.push_back(21);
	Data.m_JueSha.push_back(24);
	Data.m_JueSha.push_back(28);
	Data.m_JueSha.push_back(30);
	InitOneData(Data);
	m_Data29.push_back(Data);
	Data.m_JueSha.clear();
	Data.m_WeiHong.clear();

	//01 08 09 14 18 22 23 28 29
	Data.m_BianHao="二八";
	Data.m_JueSha.push_back(1);
	Data.m_JueSha.push_back(8);
	Data.m_JueSha.push_back(9);
	Data.m_JueSha.push_back(14);
	Data.m_JueSha.push_back(18);
	Data.m_JueSha.push_back(22);
	Data.m_JueSha.push_back(23);
	Data.m_JueSha.push_back(28);
	Data.m_JueSha.push_back(29);
	InitOneData(Data);
	m_Data29.push_back(Data);
	Data.m_JueSha.clear();
	Data.m_WeiHong.clear();

	//01 07 10 12 14 17 26 28 32
	Data.m_BianHao="二九";
	Data.m_JueSha.push_back(1);
	Data.m_JueSha.push_back(7);
	Data.m_JueSha.push_back(10);
	Data.m_JueSha.push_back(12);
	Data.m_JueSha.push_back(14);
	Data.m_JueSha.push_back(17);
	Data.m_JueSha.push_back(26);
	Data.m_JueSha.push_back(28);
	Data.m_JueSha.push_back(32);
	InitOneData(Data);
	m_Data29.push_back(Data);
	Data.m_JueSha.clear();
	Data.m_WeiHong.clear();



}

//初始一组数据
void CDataManageCenter::InitOneData(sData29 &Data)
{
	for(int i=0; i< 33; i++)
	{
		bool IsWant=true;
		for(int j=0; j < Data.m_JueSha.size(); j++)
		{
			if(i+1 == Data.m_JueSha[j])
			{
				IsWant=false;
				break;
			}
		}

		if(IsWant)
			Data.m_WeiHong.push_back(i+1);

	}
}

//红球同出
bool CDataManageCenter::IsHongQiuTongChu(sShuangSeQiu QiuData,vector<int> Data,bool IsV)
{
	//for(int i=0; i < QIU_XUN;
	return true;
}

//获取网易数据信息
vector<sWangYiDataInfo>* CDataManageCenter::GetWangYiDataInfo()
{
	return &m_WangYiDataInfo;
}

//获取中彩数据信息
vector<sZhongCaiDataInfo>* CDataManageCenter::GetZhongCaiDataInfo()
{
	return &m_ZhongCaiDataInfo;
}

//导入网络分析数据
void CDataManageCenter::LoadNetData(eLoadDataType Type)
{
	switch(Type)
	{
	
	case LOAD_WANGYI_DATA:     //导入网易数据
		//导入网易数据
		LoadWangYiData();
		break;

	case LOAD_ZHONGCAI_DATA:   //导入中彩数据
		//导入中彩数据
		LoadZhongCaiData();
		break;

	case LOAD_AOKE_DATA:       //导入澳客数据
		//导入澳客数据
		LoadAoKeData();
		break;

	case LOAD_360_DATA:        //导入360数据
		//导入360数据
		Load360Data();
		break;

	default:
		//导入中彩数据
		LoadZhongCaiData();

		//导入网易数据
		LoadWangYiData();

		//导入360数据
		Load360Data();

		//导入澳客数据
		LoadAoKeData();
		break;
	}
	
}


//导入中彩数据
void CDataManageCenter::LoadZhongCaiData()
{
	CString FilePath=GetAppCurrentPath2()+ZHONG_CAI_FILE_NAME;
	CString StrData=GetFileStr(FilePath);

	int StartPos=0;
	int EndPos=0;
	while(EndPos != -1)
	{
		EndPos=StrData.Find("\r\n",StartPos);
		if(EndPos == -1)
			break;

		CString Temp=StrData.Mid(StartPos,EndPos-StartPos);
		
		vector<CString> DataList;
		PaseFileStr(Temp,DataList);

		sZhongCaiDataInfo Info;
		Info.m_QiShu = DataList[0];
		Info.m_QiShuInt=atoi(DataList[1].GetBuffer());
		DataList[1].ReleaseBuffer();

		Info.m_Type  = (eZhongCaiType)atoi(DataList[2].GetBuffer());
		DataList[2].ReleaseBuffer();

		for(int i=3; i < DataList.size();i++)
		{
			sZhongCaiData Data;
			Data.m_Data=i-2;
			Data.m_DataCount=atoi(DataList[i].GetBuffer());
			DataList[i].ReleaseBuffer();

			Info.m_DataList.push_back(Data);
		}

		m_ZhongCaiDataInfo.push_back(Info);
		StartPos = EndPos+1;
	}

}

//导入网易数据
void CDataManageCenter::LoadWangYiData()
{
	CString FilePath=GetAppCurrentPath2()+WANG_YI_FILE_NAME;
	CString StrData=GetFileStr(FilePath);

	int StartPos=0;
	int EndPos=0;
	while(EndPos != -1)
	{
		EndPos=StrData.Find("\r\n",StartPos);
		if(EndPos == -1)
			break;

		CString Temp=StrData.Mid(StartPos,EndPos-StartPos);
		
		vector<CString> DataList;
		PaseFileStr(Temp,DataList);


	/*	sWangYiDataInfo Info;
		Info.m_QiShu = DataList[0];
		Info.m_QiShuInt=DataList[1];
		Info.m_Type  = DataList[2];

		for(int i=3; i < DataList.size();i++)
		{
			sZhongCaiData Data;
			Data.m_Data=i-2;
			Data.m_DataCount=DataList[i];
			Info.m_DataList.push_back(Data);
		}*/

		StartPos = EndPos+1;
	}


}

//导入360数据
void CDataManageCenter::Load360Data()
{

}

//导入澳客数据
void CDataManageCenter::LoadAoKeData()
{

}

//获取文件字符串
CString CDataManageCenter::GetFileStr(CString FilePath)
{
	DWORD Flag = OPEN_EXISTING;
	HANDLE FileHandle=CreateFile(FilePath,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL,Flag,FILE_ATTRIBUTE_NORMAL,NULL);
	if(FileHandle == INVALID_HANDLE_VALUE)
		return "";
	DWORD Size = ::GetFileSize(FileHandle,NULL);
	char* Buffer = new char[Size+1];
	memset(Buffer,'\0',Size+1);
	DWORD ReadBytes=0;
	::ReadFile(FileHandle,Buffer,Size,&ReadBytes,NULL);
	CString StrData=CString(Buffer);
	delete []Buffer;
	CloseHandle(FileHandle);

	return StrData;
}

//解析文件字符串
void CDataManageCenter::PaseFileStr(CString StrData,vector<CString>& DataList)
{
	int StartPos=StrData.Find("#",0);
	int EndPos=StrData.Find("#",StartPos+1);
	while(EndPos != -1)
	{
		CString Temp=StrData.Mid(StartPos+1,EndPos-StartPos-1);
		if(!Temp.IsEmpty())
			DataList.push_back(Temp);
		StartPos = EndPos;
		EndPos=StrData.Find("#",StartPos+1);
	}

}

//通过期数获取双色球数据
bool  CDataManageCenter::GetShuangSeQiuData(CString QiShu,sShuangSeQiu& Data)
{
	for(int i=0; i < m_ShuangSeQiuList.size(); i++)
	{
		if(m_ShuangSeQiuList[i].m_QiShu.Find(QiShu) != -1)
		{
			Data=m_ShuangSeQiuList[i];
			return true;
		}
	}


	return false;
}