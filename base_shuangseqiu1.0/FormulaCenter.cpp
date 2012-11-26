#include "StdAfx.h"
#include "FormulaCenter.h"
#include "DataManageCenter.h"
#include <algorithm> 
using namespace std; 


bool SortByErrorCount(sFormulaInfo tp1, sFormulaInfo tp2)
{ 
	if(tp1.m_TrueCount > tp2.m_TrueCount)
		return true;
	else
		return false;

}

CFormulaCenter::CFormulaCenter(void)
{
	RunFormula();
}

CFormulaCenter::~CFormulaCenter(void)
{
}


//获取公式信息
vector<sFormulaInfo> CFormulaCenter::GetFormulaInfoByType(eFormulaType Type)
{
	vector<sFormulaInfo> InfoList;
	map<eFormulaType,vector<sFormulaInfo>>::iterator it = m_MapFormulaInfo.find(Type);
	if(it != m_MapFormulaInfo.end())
		InfoList=it->second;
	return InfoList;
}

//搜索公式信息
vector<sFormulaInfo>  CFormulaCenter::SearchFormulaInfoByType(eFormulaType Type,eSearchVType SearchType,int Data,int Data2)
{
	vector<sFormulaInfo> InfoList;
	map<eFormulaType,vector<sFormulaInfo>>::iterator it = m_MapFormulaInfo.find(Type);
	if(it != m_MapFormulaInfo.end())
	{
		for(int Index = 0; Index < it->second.size(); Index++)
		{
			switch(SearchType)
			{
			case TYPE_DA_YU:
				{
					int AllCount = it->second[Index].m_ErrorCount+it->second[Index].m_TrueCount;
					if(AllCount != 0)
					{
						int TempData = it->second[Index].m_TrueCount*100/AllCount;
						if(TempData > Data && Data != -1)
						{
							InfoList.push_back(it->second[Index]);
							continue;
						}

						if(TempData >Data2 && Data2 != -1 )
						{
							
							InfoList.push_back(it->second[Index]);
							continue;
						}
					}

					break;
				}
			case TYPE_DENG_YU:
					{
					int AllCount = it->second[Index].m_ErrorCount+it->second[Index].m_TrueCount;
					if(AllCount != 0)
					{
						int TempData = it->second[Index].m_TrueCount*100/AllCount;
						if(Data == TempData)
						{
							InfoList.push_back(it->second[Index]);
							continue;
						}

						if(Data2 == TempData)
						{
							
							InfoList.push_back(it->second[Index]);
							continue;
						}
					}

					break;
				}

			case TYPE_XIAO_YU:
					{
					int AllCount = it->second[Index].m_ErrorCount+it->second[Index].m_TrueCount;
					if(AllCount != 0)
					{
						int TempData = it->second[Index].m_TrueCount*100/AllCount;
						if(Data != -1&&  Data >TempData )
						{
							InfoList.push_back(it->second[Index]);
							continue;
						}

						if(Data2 != -1 && Data2 >TempData)
						{
							
							InfoList.push_back(it->second[Index]);
							continue;
						}
					}

					break;
				}

			case TYPE_QU_JIAN:
				{
					int AllCount = it->second[Index].m_ErrorCount+it->second[Index].m_TrueCount;
					if(AllCount != 0)
					{
						int TempData = it->second[Index].m_TrueCount*100/AllCount;

						if(Data > Data2)
						{
							int Temp=Data;
							Data=Data2;
							Data2=Temp;
						}

						if(Data < TempData  && TempData < Data2)
						{
							InfoList.push_back(it->second[Index]);
							continue;
						}
					}

					break;
				}

			case TYPE_TE_DA_YU:
			case TYPE_V_DA_YU:
				{
					int SizeIndex=it->second[Index].m_DataList.size()-1;
					if(SizeIndex < 0)
						continue;

					int TempData = atoi(it->second[Index].m_DataList[SizeIndex].m_Data.GetBuffer());
					if(Data != -1 && Data <TempData)
					{ 
						InfoList.push_back(it->second[Index]);
						continue;
					}

					if(Data2 != -1 && Data2 <TempData)
					{
						
						InfoList.push_back(it->second[Index]);
						continue;
					}
					break;
				}
			case TYPE_TE_DENG_YU:
			case TYPE_V_DENG_YU:
				{
					int SizeIndex=it->second[Index].m_DataList.size()-1;
					if(SizeIndex < 0)
						continue;

					int TempData = atoi(it->second[Index].m_DataList[SizeIndex].m_Data.GetBuffer());
					if(TYPE_V_DENG_YU == SearchType)
						TempData=TempData%10;

					if(Data == TempData)
					{
						InfoList.push_back(it->second[Index]);
						continue;
					}

					if(Data2 == TempData)
					{
						
						InfoList.push_back(it->second[Index]);
						continue;
					}
					break;
				}

			case TYPE_TE_XIAO_YU:
			case TYPE_V_XIAO_YU:
				{
					int SizeIndex=it->second[Index].m_DataList.size()-1;
					if(SizeIndex < 0)
						continue;

					int TempData = atoi(it->second[Index].m_DataList[SizeIndex].m_Data.GetBuffer());
					if(Data!= -1 && Data > TempData)
					{
						InfoList.push_back(it->second[Index]);
						continue;
					}

					if(Data2 != -1 && Data2 > TempData)
					{
						
						InfoList.push_back(it->second[Index]);
						continue;
					}
					break;
				}

			case TYPE_TE_QU_JIAN:
			case TYPE_V_QU_JIAN:
				{
					int SizeIndex=it->second[Index].m_DataList.size()-1;
					if(SizeIndex < 0)
						continue;

					if(Data > Data2)
					{
						int Temp=Data;
						Data=Data2;
						Data2=Temp;
					}

					int TempData = atoi(it->second[Index].m_DataList[SizeIndex].m_Data.GetBuffer());
					if(Data < TempData  && TempData < Data2)
					{
						InfoList.push_back(it->second[Index]);
						continue;
					}
					break;
				}
				break;

			case TYPE_LAST_ERROR:
				{
					int SizeIndex=it->second[Index].m_DataList.size()-2;
					if(SizeIndex < 0)
						continue;

					if(!it->second[Index].m_DataList[SizeIndex].m_IsTrue)
					{
						InfoList.push_back(it->second[Index]);
						continue;
					}
					break;
				}
				break;

			}
		}
	}

	return InfoList;
	
}


//通过算法获取公式信息
vector<sFormulaInfo> CFormulaCenter::GetFormulaInfoByName(eFormulaType Type,vector<CString>& NameList)
{
	vector<sFormulaInfo> InfoList;
	map<eFormulaType,vector<sFormulaInfo>>::iterator it = m_MapFormulaInfo.find(Type);
	if(it != m_MapFormulaInfo.end())
	{
		for(int Index = 0; Index < it->second.size(); Index++)
		{
			for(int j=0; j < NameList.size(); j++)
			{
				if(it->second[Index].m_FormulaName == NameList[j])
				{
					InfoList.push_back(it->second[Index]);
					break;
				}
			}
		}
	}

	return InfoList;
}

//公式运算
void CFormulaCenter::RunFormula()
{
	ExecShaHongFormula();
	ExecShaLanFormula();
	ExecShaLanVFormula();
	ExecDingHongFormula();
	ExecShaLongTouFormula();
	ExecWeiBuTongChuFormula();

	//运行杀凤尾公式
	ExecShaFengWeiFormula();

	ExecDingHongVFormula();
}


//杀红公式
void CFormulaCenter::ExecShaHongFormula()
{

		vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
		vector<sShuangSeQiu>* ShunXuDataList = CDataManageCenter::GetInstance()->GetDataListByChuHao();

		const int  FormualCount = 48;   //定义公式个数
		sFormulaInfo FormualList[FormualCount];
		
		for(int Index = 1; Index < (int)DataList->size()+1; Index++)
		{

			int FormualIndex=0;
			sFormulaData FormulaData;
			int TempData = 0;
			bool IsTrue = false;

			TempData = (*DataList)[Index-1].m_HongQiu[5]-(*DataList)[Index-1].m_HongQiu[0];
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
		
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = (*DataList)[Index-1].m_HongQiu[2]-(*DataList)[Index-1].m_HongQiu[1];
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		    FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;


			TempData = (*DataList)[Index-1].m_HongQiu[5]-(*DataList)[Index-1].m_HongQiu[1];
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = (*DataList)[Index-1].m_HongQiu[0]*4-2;
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;



			TempData = ((*DataList)[Index-1].m_HongQiu[0]+(*DataList)[Index-1].m_LanQiu)*3;
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;


			TempData = (*DataList)[Index-1].m_HongQiu[0]+9;
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = (*DataList)[Index-1].m_HongQiu[1]+5;
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = (*DataList)[Index-1].m_HongQiu[2]+4;
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = (*DataList)[Index-1].m_HongQiu[2]+7;
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = (*DataList)[Index-1].m_HongQiu[5]+4;
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = (*DataList)[Index-1].m_HongQiu[4]-(*DataList)[Index-1].m_HongQiu[3]+(*DataList)[Index-1].m_LanQiu+1;
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = (*DataList)[Index-1].m_LanQiu+(*DataList)[Index-1].m_HongQiu[0];
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = (*DataList)[Index-1].m_LanQiu+(*DataList)[Index-1].m_HongQiu[1]-1;
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;


			TempData = (*DataList)[Index-1].m_LanQiu-(*DataList)[Index-1].m_HongQiu[3]+1+33;
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = (*DataList)[Index-1].m_LanQiu-(*DataList)[Index-1].m_HongQiu[4]+33;
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = abs((*DataList)[Index-1].m_LanQiu*(*DataList)[Index-1].m_HongQiu[0]);
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = (*DataList)[Index-1].m_LanQiu+7;
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = (*DataList)[Index-1].m_LanQiu+9;
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

            TempData = (*DataList)[Index-1].m_LanQiu;
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;


			TempData = abs((*DataList)[Index-1].m_LanQiu-(*DataList)[Index-1].m_HongQiu[5]);
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = (*DataList)[Index-1].m_HongQiu[2]+(*DataList)[Index-1].m_HongQiu[5]/33 + 14;
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = ((*DataList)[Index-1].m_HongQiu[0]+(*DataList)[Index-1].m_HongQiu[2]+(*DataList)[Index-1].m_HongQiu[4])/2;
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = abs((*DataList)[Index-1].m_LanQiu+16-(*DataList)[Index-1].m_HongQiu[0]);
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = (*DataList)[Index-1].m_HongQiu[0]+(*DataList)[Index-1].m_HongQiu[1]+(*DataList)[Index-1].m_LanQiu;
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = (*DataList)[Index-1].m_HongQiu[5]-(*DataList)[Index-1].m_HongQiu[0]+(*DataList)[Index-1].m_HongQiu[2];
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;


			TempData = abs((*ShunXuDataList)[Index-1].m_HongQiu[1]-(*ShunXuDataList)[Index-1].m_HongQiu[2]);
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;
			

			TempData = abs((*ShunXuDataList)[Index-1].m_HongQiu[2]-(*ShunXuDataList)[Index-1].m_HongQiu[4]);
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;
				

			TempData = abs((*ShunXuDataList)[Index-1].m_HongQiu[0]-(*ShunXuDataList)[Index-1].m_HongQiu[5]) +(*ShunXuDataList)[Index-1].m_LanQiu-3;
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = abs((*ShunXuDataList)[Index-1].m_HongQiu[0]-(*ShunXuDataList)[Index-1].m_HongQiu[2]) +(*ShunXuDataList)[Index-1].m_LanQiu+2;
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

				
			TempData = (*ShunXuDataList)[Index-1].m_HongQiu[0]+(*ShunXuDataList)[Index-1].m_HongQiu[1]+(*ShunXuDataList)[Index-1].m_HongQiu[2] +(*ShunXuDataList)[Index-1].m_LanQiu-1;
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;


			//按AC值杀号
			TempData = CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = (*DataList)[Index-1].m_LanQiu;
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = (*DataList)[Index-1].m_LanQiu+ CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;
			
			TempData =0;
			for(int i=0; i < 6; i++)
				TempData+=(*DataList)[Index-1].m_HongQiu[i]%10;
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;


			TempData =CDataManageCenter::GetZhiShuCount((*DataList)[Index-1]);
			TempData += (*DataList)[Index-1].m_LanQiu;
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData =CDataManageCenter::GetZhiShuCount((*DataList)[Index-1]);
			TempData =TempData*CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
	    	if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData =CDataManageCenter::GetZhiShuCount((*DataList)[Index-1]);
			TempData =TempData+CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData =CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
			TempData =abs(TempData - (*DataList)[Index-1].m_HongQiu[5]);
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData =CDataManageCenter::GetZhiShuCount((*DataList)[Index-1])+CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
			TempData =TempData + (*DataList)[Index-1].m_LanQiu;
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

		

			for(int i=0; i < QIU_XUN; i++)
			{
				float TempF = (float)(*DataList)[Index-1].m_HongQiu[i];
				TempF=TempF*0.88;
				TempData =(int)TempF;
				if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
				IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
				FormulaData.m_Data   = DataToStr(TempData);
				FormulaData.m_IsTrue = !IsTrue;
				FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
				FormualList[FormualIndex].m_DataList.push_back(FormulaData);
				FormualIndex++;
			}


			TempData =abs((*DataList)[Index-1].m_LanQiu+16-(*DataList)[Index-1].m_HongQiu[0]);
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;


			//上期开球顺序h2+上上期大小红球H3-2
			TempData =(*DataList)[Index-1].m_HongQiu[1]+(*ShunXuDataList)[Index-1].m_HongQiu[2] -2;
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;


			//上期开球顺序h2+上上期大小红球H2-2
			if(Index > 1)
			{
				TempData =(*DataList)[Index-1].m_HongQiu[1]+(*ShunXuDataList)[Index-2].m_HongQiu[1] -2;
				if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
				IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
				FormulaData.m_Data   = DataToStr(TempData);
				FormulaData.m_IsTrue = !IsTrue;
				FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
				FormualList[FormualIndex].m_DataList.push_back(FormulaData);
				FormualIndex++;
			}
			else
			{
				TempData =0;
				IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
				FormulaData.m_Data   = DataToStr(TempData);
				FormulaData.m_IsTrue = !IsTrue;
				FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
				FormualList[FormualIndex].m_DataList.push_back(FormulaData);
				FormualIndex++;
			}
     }

	 for(int i = 0; i < FormualCount; i++)
	 {
		 CString Name;
		 Name.Format(_T("杀红_%02d"),i);
		 FormualList[i].m_FormulaName = Name;
		 FormualList[i].m_FormulaType = FORMULA_SHA_HONG;
		 ToJiFormulaInfo(FormualList[i]);
		 m_MapFormulaInfo[FORMULA_SHA_HONG].push_back(FormualList[i]);
	 }

	 sort(m_MapFormulaInfo[FORMULA_SHA_HONG].begin(),m_MapFormulaInfo[FORMULA_SHA_HONG].end(), SortByErrorCount);
}





//整形转化到字符串
CString CFormulaCenter::DataToStr(int Data)
{
	CString TempStr;
	TempStr.Format(_T("%02d"),Data);
	return TempStr;
}

//整形转化到字符串
CString CFormulaCenter::DataToStr(vector<int> Data)
{
	CString RetStr;
	for(int i=0; i < Data.size(); i++)
	{
		CString Temp;
		Temp.Format("%d",Data[i]);
		RetStr+=Temp;
	}

	return RetStr;
}

//字符串转化到整形
int CFormulaCenter::StrToData(CString DataStr)
{
	int Data=atoi(DataStr.GetBuffer());
	DataStr.ReleaseBuffer();
	return Data;
}



//统计公式信息
void CFormulaCenter::ToJiFormulaInfo(sFormulaInfo& Formula)
{
	int                    MaxLianCuoCount=0;    
	int                    MaxLianDuiCount=0;      
	int                    MinLianCuoCount=0;      
	int                    MinLianDuiCount=0;    
	int                    ErrorCount=0;      
	int                    TrueCount = 0;
	bool                   LastStatus=false;  


	int                    TempLianCuoCount=0;    
	int                    TempLianDuiCount=0; 



	for(int Index = 0; Index < Formula.m_DataList.size(); Index++)
	{
		if(Formula.m_DataList[Index].m_IsTrue)
		{
			TrueCount++;
			if(MaxLianCuoCount < TempLianCuoCount)
				MaxLianCuoCount = TempLianCuoCount;
			else if(MinLianCuoCount > TempLianCuoCount)
				MinLianCuoCount = TempLianCuoCount;
			TempLianCuoCount=0;
			TempLianDuiCount++;
		}
		else
		{
			ErrorCount++;
			if(MaxLianDuiCount < TempLianDuiCount)
				MaxLianDuiCount = TempLianDuiCount;
			else if(MinLianDuiCount > TempLianDuiCount)
				MinLianDuiCount = TempLianDuiCount;
			TempLianDuiCount=0;

			TempLianDuiCount  = 0;
			TempLianCuoCount++;
		}

		if(Index == Formula.m_DataList.size()-1)
			LastStatus = Formula.m_DataList[Index].m_IsTrue;
	}

	Formula.m_ErrorCount      = ErrorCount;
	Formula.m_TrueCount       = TrueCount;
	Formula.m_MaxLianCuoCount = MaxLianCuoCount;
	Formula.m_MinLianCuoCount = MinLianCuoCount;
	Formula.m_MaxLianDuiCount = MaxLianDuiCount;
	Formula.m_MaxLianCuoCount = MaxLianCuoCount;
	Formula.m_LastStatus      = LastStatus;

}

//获取算法个数
int CFormulaCenter::GetFormulaCount(eFormulaType Type)
{
	map<eFormulaType,vector<sFormulaInfo>>::iterator it = m_MapFormulaInfo.find(Type);
	if(it != m_MapFormulaInfo.end())
		return it->second.size();
	return 0;
}

//获取公式管理实例
CFormulaCenter* CFormulaCenter::GetInstance()
{
	static CFormulaCenter Self;
	return &Self;
}

//运行杀蓝公式
void CFormulaCenter::ExecShaLanFormula()
{
	vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
	vector<sShuangSeQiu>* ShunXuDataList = CDataManageCenter::GetInstance()->GetDataListByChuHao();

	const int  FormualCount = 58;   //定义公式个数
	const int  MODE_COUNT=16;

	int RealCount=0;

	sFormulaInfo FormualList[FormualCount];

	for(int Index = 1; Index < (int)DataList->size()+1; Index++)
	{
		sFormulaData FormulaData;
		int FormualIndex=0;
		int TempData = 0;
		bool IsTrue = false;

		TempData = (*DataList)[Index-1].m_HongQiu[5]%10+1;
		if(TempData > MODE_COUNT) TempData = TempData%MODE_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;


		TempData = (*DataList)[Index-1].m_HongQiu[0]+3;
		if(TempData > MODE_COUNT) TempData = TempData%MODE_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;


		TempData = (*DataList)[Index-1].m_HongQiu[0]*2;
		if(TempData > MODE_COUNT) TempData = TempData%MODE_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		TempData = CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1])*2-6;
		if(TempData > MODE_COUNT) TempData = TempData%MODE_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;


		if(Index >= 3)
		{
			TempData = (*DataList)[Index-1].m_LanQiu%10+(*DataList)[Index-2].m_LanQiu%10+(*DataList)[Index-3].m_LanQiu%10;
			if(TempData > MODE_COUNT) TempData = TempData%MODE_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;
		}
		else
		{
			FormulaData.m_Data   = "";
			FormulaData.m_IsTrue = false;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;
		}

		if(Index >=2)
		{
			TempData = ((*DataList)[Index-1].m_LanQiu%10)*((*DataList)[Index-2].m_LanQiu%10)+5;
			if(TempData > MODE_COUNT) TempData = TempData%MODE_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = abs((*DataList)[Index-1].m_LanQiu - (*DataList)[Index-2].m_LanQiu);
			if(TempData > MODE_COUNT) TempData = TempData%MODE_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = (*DataList)[Index-1].m_LanQiu + (*DataList)[Index-2].m_LanQiu;
			if(TempData > MODE_COUNT) TempData = TempData%MODE_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

		}
		else
		{
			FormulaData.m_Data   = "";
			FormulaData.m_IsTrue = false;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			FormulaData.m_Data   = "";
			FormulaData.m_IsTrue = false;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			FormulaData.m_Data   = "";
			FormulaData.m_IsTrue = false;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;


		}

		TempData = (*DataList)[Index-1].m_HongQiu[3]%10 + (*DataList)[Index-1].m_LanQiu%10;
		if(TempData > MODE_COUNT) TempData = TempData%MODE_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		TempData = (*DataList)[Index-1].m_LanQiu+2;
		if(TempData > MODE_COUNT) TempData = TempData%MODE_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		TempData = (*DataList)[Index-1].m_LanQiu-2;
		if(TempData > MODE_COUNT) TempData = TempData%MODE_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		TempData = (*DataList)[Index-1].m_LanQiu +(*DataList)[Index-1].m_HongQiu[0];
		if(TempData > MODE_COUNT) TempData = TempData%MODE_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		TempData =atoi((*DataList)[Index-1].m_QiShu.GetBuffer())%100+(*DataList)[Index-1].m_LanQiu;
		if(TempData > MODE_COUNT) TempData = TempData%MODE_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		TempData =(*DataList)[Index-1].m_HongQiu[1]%10+1;
		if(TempData > 10) TempData =TempData%10;
		if(TempData > MODE_COUNT) TempData = TempData%MODE_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		TempData =(*DataList)[Index-1].m_HongQiu[1]%10+1;
		if(TempData > 10) TempData =TempData%10;
		if(TempData <= MODE_COUNT%10)
			TempData = TempData+10;
		if(TempData > MODE_COUNT) TempData = TempData%MODE_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		TempData =(*DataList)[Index-1].m_LanQiu+5;
		if(TempData > MODE_COUNT) TempData = TempData%MODE_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		TempData =(*DataList)[Index-1].m_LanQiu%10*2;
		if(TempData > 10) TempData =TempData%10;
		if(TempData > MODE_COUNT) TempData = TempData%MODE_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		TempData =(*DataList)[Index-1].m_LanQiu%10*2;
		if(TempData > 10) TempData =TempData%10;
		if(TempData <= MODE_COUNT%10)
			TempData = TempData+10;
		if(TempData > MODE_COUNT) TempData = TempData%MODE_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;


		TempData =(*DataList)[Index-1].m_LanQiu+8;
		if(TempData > MODE_COUNT) TempData = TempData%MODE_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		if(Index == 1)
			RealCount=FormualIndex;
	}

	for(int i = 0; i < RealCount; i++)
	{
		CString Name;
		Name.Format(_T("式_%02d"),i);
		FormualList[i].m_FormulaName = Name;
		FormualList[i].m_FormulaType = FORMULA_SHA_LAN ;
		ToJiFormulaInfo(FormualList[i]);
		m_MapFormulaInfo[FORMULA_SHA_LAN ].push_back(FormualList[i]);
	}

	sort(m_MapFormulaInfo[FORMULA_SHA_LAN ].begin(),m_MapFormulaInfo[FORMULA_SHA_LAN ].end(), SortByErrorCount);
}

//运行杀蓝V公式
void CFormulaCenter::ExecShaLanVFormula()
{
	vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
	vector<sShuangSeQiu>* ShunXuDataList = CDataManageCenter::GetInstance()->GetDataListByChuHao();

	const int  FormualCount = 56;   //定义公式个数
	sFormulaInfo FormualList[FormualCount];

	for(int Index = 1; Index < (int)DataList->size()+1; Index++)
	{
		int FormualIndex=0;
		sFormulaData FormulaData;
		int TempData = 0;
		bool IsTrue = false;

		TempData = Index < DataList->size() ? (*DataList)[Index].m_LanQiu:0;
		CString AddStr=_T("  ")+DataToStr(TempData);

		TempData = (*DataList)[Index-1].m_HongQiu[5]-(*DataList)[Index-1].m_HongQiu[0];
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;

		
		if(Index > 1)
		{
			int Data = atoi((*DataList)[Index-2].m_QiShu)-2012000;
			Data = abs(Data - (*DataList)[Index-1].m_LanQiu);
			TempData = Data/10;
			TempData = TempData%10;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData,true):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu+AddStr:_T("下期预测");
		
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = Data%10;
			TempData = TempData%10;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData,true):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu+AddStr:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

		}
		else
		{
			TempData =0;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData,true):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu+AddStr:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData =0;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData,true):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu+AddStr:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;
		}

		TempData = (*DataList)[Index-1].m_LanQiu%10 +(*DataList)[Index-1].m_HongQiu[2]%10;;
		TempData = TempData%10;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData,true):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu+AddStr:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;


		TempData =(*DataList)[Index-1].m_HongQiu[5] - (*DataList)[Index-1].m_HongQiu[4];
		TempData = TempData%10;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData,true):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu+AddStr:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;



		if( Index > 1)
		{
			TempData = 	abs((*DataList)[Index-1].m_LanQiu - (*DataList)[Index-2].m_LanQiu);
			TempData = TempData%10;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData,true):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu+AddStr:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;
		}
		else
		{

			TempData =0;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData,true):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu+AddStr:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

		}




		TempData = (*DataList)[Index-1].m_HongQiu[1]%10+1;
		TempData = TempData%10;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData,true):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu+AddStr:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;



		TempData = 	(*DataList)[Index-1].m_LanQiu%10*2;
		TempData = TempData%10;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData,true):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu+AddStr:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		int MinData = (*DataList)[Index-1].m_HongQiu[0];
		int MaxData = (*DataList)[Index-1].m_HongQiu[5];
		if(MinData > (*DataList)[Index-1].m_LanQiu)
			MinData = (*DataList)[Index-1].m_LanQiu;

		if(MaxData < (*DataList)[Index-1].m_LanQiu)
			MaxData = (*DataList)[Index-1].m_LanQiu;

		TempData = 	MaxData +(*DataList)[Index-1].m_HongQiu[4];
		TempData = TempData%10;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData,true):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu+AddStr:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;


		TempData = (*DataList)[Index-1].m_LanQiu + (*DataList)[Index-1].m_HongQiu[2];
		TempData = TempData%10;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData,true):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu+AddStr:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;






		TempData = (*DataList)[Index-1].m_HongQiu[5]/10+(*DataList)[Index-1].m_HongQiu[5]%10 +(*DataList)[Index-1].m_HongQiu[4]/10+(*DataList)[Index-1].m_HongQiu[4]%10;
		TempData = TempData%10;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData,true):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu+AddStr:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;


		TempData = (*DataList)[Index-1].m_HongQiu[0]/10+(*DataList)[Index-1].m_HongQiu[0]%10 +(*DataList)[Index-1].m_HongQiu[1]/10+(*DataList)[Index-1].m_HongQiu[1]%10;
		TempData = TempData%10;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData,true):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu+AddStr:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;


		TempData = atoi((*DataList)[Index-1].m_QiShu.GetBuffer());
		TempData = TempData%10;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData,true):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu+AddStr:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;


		TempData = atoi((*DataList)[Index-1].m_QiShu.GetBuffer());
		TempData =	TempData%100+	TempData%10;
		TempData = TempData%10;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData,true):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu+AddStr:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;


		TempData = abs((*DataList)[Index-1].m_LanQiu - (*DataList)[Index-1].m_HongQiu[5]);
		TempData +=1;
		TempData = TempData%10;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData,true):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu+AddStr:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		/////////////////////////////////////////////////
		////14


		//14+6+5+6+9

		
	
		//+3 +5 +7 +8 +9 +5

		int temp[5]={3,5,7,8 ,9};
		for(int k=0; k < 5; k++)
		{
			TempData = (*DataList)[Index-1].m_LanQiu/10;
			TempData =TempData+temp[k];
			if(TempData < 0)
				TempData+=10;
			TempData = TempData%10;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData,true):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu+AddStr:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;
		}

		//0+1+2+5+8+9
		int Array[6]={0,1,2,5,8,9};
		for(int k=0; k < 6; k++)
		{
			TempData = (*DataList)[Index-1].m_LanQiu/10 +(*DataList)[Index-1].m_HongQiu[5]%10;
			TempData =TempData+Array[k];
			if(TempData < 0)
				TempData+=10;
			TempData = TempData%10;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData,true):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu+AddStr:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;
		}

      
        //+3
        int Array4[4]={1,8,-2,-3};
		for(int k=0; k < 4; k++)
		{
			TempData = abs((*DataList)[Index-1].m_LanQiu - (*DataList)[Index-1].m_HongQiu[5]);
			TempData =TempData+Array4[k];
			if(TempData < 0)
				TempData+=10;
			TempData = TempData%10;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData,true):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu+AddStr:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;
		}

		int Array6[2]={-3,-6};
		for(int k=0; k < 2; k++)
		{
			TempData = (*DataList)[Index-1].m_LanQiu%10 +(*DataList)[Index-1].m_HongQiu[2]%10;
			TempData =TempData+Array6[k];
			if(TempData < 0)
				TempData+=10;
			TempData = TempData%10;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData,true):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu+AddStr:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;
		}


		//1,+4,7,8,9,-1,-2,-3,-9
		int Array5[9]={1,4,7,8,9,-1,-2,-3,-9};
		for(int k=0; k < 4; k++)
		{
			TempData = (*DataList)[Index-1].m_HongQiu[5] - (*DataList)[Index-1].m_HongQiu[4];
			TempData =TempData+Array5[k];
			if(TempData < 0)
				TempData+=10;
			TempData = TempData%10;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData,true):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu+AddStr:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;
		}

		//int Array2[6]={0,1,6,9,-4,-5};

		int Array2[6]={2,-2,5,-3,3,-4};
		for(int k=0; k< 6; k++)
		{
			TempData = (*DataList)[Index-1].m_LanQiu%10;
			TempData +=Array2[k];
			if(TempData < 10)
				TempData+=10;

			TempData = TempData%10;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData,true):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu+AddStr:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;
		}


		
	/*	TempData = (*DataList)[Index-1].m_HongQiu[5]%10;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData,true):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu+AddStr:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;*/

		for(int i=0; i < 6; i++)
		{
	//	TempData = (*ShunXuDataList)[Index-1].m_HongQiu[i]%10;
		TempData = (*DataList)[Index-1].m_HongQiu[i]%10;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData,true):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu+AddStr:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;
		}

		for(int i=0; i < 6;i++)
		{
			TempData = (*ShunXuDataList)[Index-1].m_HongQiu[i]%10;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData,true):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu+AddStr:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;
		}

	    	TempData = (*ShunXuDataList)[Index-1].m_HongQiu[3]%10+(*ShunXuDataList)[Index-1].m_HongQiu[3]/10;
			TempData=TempData%10;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData,true):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu+AddStr:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

		/*	TempData = (*ShunXuDataList)[Index-1].m_HongQiu[2]%10+(*ShunXuDataList)[Index-1].m_HongQiu[1]/10;
			TempData=TempData%10;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData,true):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu+AddStr:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;*/

			TempData = (*DataList)[Index-1].m_HongQiu[0]%10+(*DataList)[Index-1].m_HongQiu[5]%10+(*DataList)[Index-1].m_HongQiu[5]/10;
			TempData=TempData%10;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData,true):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu+AddStr:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;


			TempData = (*ShunXuDataList)[Index-1].m_HongQiu[4]%10+(*ShunXuDataList)[Index-1].m_HongQiu[4]/10;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData,true):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu+AddStr:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;




	}

	for(int i = 0; i < FormualCount; i++)
	{
		CString Name;
		Name.Format(_T("杀蓝_%02d"),i);
		FormualList[i].m_FormulaName = Name;
		FormualList[i].m_FormulaType = FORMULA_SHA_LAN_WEI;
		ToJiFormulaInfo(FormualList[i]);
		m_MapFormulaInfo[FORMULA_SHA_LAN_WEI].push_back(FormualList[i]);
	}

	sort(m_MapFormulaInfo[FORMULA_SHA_LAN_WEI].begin(),m_MapFormulaInfo[FORMULA_SHA_LAN_WEI ].end(), SortByErrorCount);

}


//运行定红公式
void CFormulaCenter::ExecDingHongFormula()
{
	vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
	vector<sShuangSeQiu>* ShunXuDataList = CDataManageCenter::GetInstance()->GetDataListByChuHao();

	const int  FormualCount = 58;   //定义公式个数
	const int  MODE_COUNT=16;

	int RealCount=0;

	sFormulaInfo FormualList[FormualCount];

	for(int Index = 1; Index < (int)DataList->size()+1; Index++)
	{
    	int FormualIndex=0;
		sFormulaData FormulaData;
		int TempData = 0;
		bool IsTrue = false;
		CString TempStr;

		CString StrQiShu=(*ShunXuDataList)[Index-1].m_QiShu.Right(3);
		int QiShu=atoi(StrQiShu.GetBuffer());
		StrQiShu.ReleaseBuffer();
		QiShu=QiShu/100+ (QiShu/10)%10 +QiShu%10;
		

		TempData = (*ShunXuDataList)[Index-1].m_HongQiu[0]+QiShu;
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = IsTrue;
		if(IsTrue)
			TempStr+=FormulaData.m_Data+" ";
	
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		TempData = abs((*ShunXuDataList)[Index-1].m_HongQiu[0]-QiShu);
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		if(TempData == 0) TempData=QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = IsTrue;
		if(IsTrue)
			TempStr+=FormulaData.m_Data+" ";
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		TempData = (*ShunXuDataList)[Index-1].m_HongQiu[5]+QiShu;
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = IsTrue;
		if(IsTrue)
			TempStr+=FormulaData.m_Data+" ";
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;


		TempData = abs((*ShunXuDataList)[Index-1].m_HongQiu[5]-QiShu);
		if(TempData == 0) TempData=QIU_COUNT;
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = IsTrue;
		if(IsTrue)
			TempStr+=FormulaData.m_Data+" ";
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		FormulaData.m_Data   = "";
		FormulaData.m_IsTrue = true;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;
		TempStr.Empty();


	    int QiuSum=(*DataList)[Index-1].m_HongQiuSum;
		int HeSum=0;
		int WeiSum=0;
		for(int i = 0; i < 6; i++)
		{
			WeiSum=HeSum+(*DataList)[Index-1].m_HongQiu[i]%10;
			if(CDataManageCenter::IsHeShuData((*DataList)[Index-1].m_HongQiu[i]))
				HeSum+=(*DataList)[Index-1].m_HongQiu[i];

		}

		
		QiuSum +=WeiSum;
		int QuYu = QiuSum%QIU_COUNT;
		int QuShang =QiuSum/QIU_COUNT;
		int Temp = abs(QuYu-QuShang);


		TempData = QuYu+QuShang;
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = IsTrue;
		if(IsTrue)
			TempStr+=FormulaData.m_Data+" ";
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;


		TempData = QuYu+QuShang+1;
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = IsTrue;
		if(IsTrue)
			TempStr+=FormulaData.m_Data+" ";
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		TempData = QuYu+QuShang+2;
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = IsTrue;
		if(IsTrue)
			TempStr+=FormulaData.m_Data+" ";
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		TempData = QuYu+QuShang-1;
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		if(TempData < 0 ) TempData+=QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = IsTrue;
		if(IsTrue)
			TempStr+=FormulaData.m_Data+" ";
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		TempData = QuYu+QuShang-2;
		if(TempData < 0 ) TempData+=QIU_COUNT;
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = IsTrue;
		if(IsTrue)
			TempStr+=FormulaData.m_Data+" ";
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		FormulaData.m_Data   = "";
		FormulaData.m_IsTrue = true;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;
		TempStr.Empty();

		TempData = abs(QuYu-QuShang);
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = IsTrue;
		if(IsTrue)
			TempStr+=FormulaData.m_Data+" ";
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;


		TempData =  abs(QuYu-QuShang)+1;
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = IsTrue;
		if(IsTrue)
			TempStr+=FormulaData.m_Data+" ";
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		TempData =  abs(QuYu-QuShang)+2;
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = IsTrue;
		if(IsTrue)
			TempStr+=FormulaData.m_Data+" ";
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		TempData =  abs(QuYu-QuShang)-1;
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		if(TempData < 0 ) TempData+=QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = IsTrue;
		if(IsTrue)
			TempStr+=FormulaData.m_Data+" ";
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		TempData =  abs(QuYu-QuShang)-2;
		if(TempData < 0 ) TempData+=QIU_COUNT;
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = IsTrue;
		if(IsTrue)
			TempStr+=FormulaData.m_Data+" ";
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		FormulaData.m_Data   = "";
		FormulaData.m_IsTrue = true;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;
		TempStr.Empty();


		QiuSum=(*DataList)[Index-1].m_HongQiuSum;
		QiuSum +=HeSum;
		QuYu = QiuSum%QIU_COUNT;
		QuShang =QiuSum/QIU_COUNT;
		Temp = abs(QuYu-QuShang);


		TempData = QuYu+QuShang;
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = IsTrue;
		if(IsTrue)
			TempStr+=FormulaData.m_Data+" ";
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;


		TempData = QuYu+QuShang+1;
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = IsTrue;
		if(IsTrue)
			TempStr+=FormulaData.m_Data+" ";
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		TempData = QuYu+QuShang+2;
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = IsTrue;
		if(IsTrue)
			TempStr+=FormulaData.m_Data+" ";
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		TempData = QuYu+QuShang-1;
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		if(TempData < 0 ) TempData+=QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = IsTrue;
		if(IsTrue)
			TempStr+=FormulaData.m_Data+" ";
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		TempData = QuYu+QuShang-2;
		if(TempData < 0 ) TempData+=QIU_COUNT;
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = IsTrue;
		if(IsTrue)
			TempStr+=FormulaData.m_Data+" ";
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		FormulaData.m_Data   = "";
		FormulaData.m_IsTrue = true;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;
		TempStr.Empty();

		TempData = abs(QuYu-QuShang);
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = IsTrue;
		if(IsTrue)
			TempStr+=FormulaData.m_Data+" ";
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;


		TempData =  abs(QuYu-QuShang)+1;
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = IsTrue;
		if(IsTrue)
			TempStr+=FormulaData.m_Data+" ";
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		TempData =  abs(QuYu-QuShang)+2;
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = IsTrue;
		if(IsTrue)
			TempStr+=FormulaData.m_Data+" ";
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		TempData =  abs(QuYu-QuShang)-1;
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		if(TempData < 0 ) TempData+=QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = IsTrue;
		if(IsTrue)
			TempStr+=FormulaData.m_Data+" ";
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		TempData =  abs(QuYu-QuShang)-2;
		if(TempData < 0 ) TempData+=QIU_COUNT;
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = IsTrue;
		if(IsTrue)
			TempStr+=FormulaData.m_Data+" ";
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		FormulaData.m_Data   = "";
		FormulaData.m_IsTrue = true;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;
		TempStr.Empty();


		

		FormulaData.m_Data   = "";
		FormulaData.m_IsTrue = true;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;
		TempStr.Empty();

		float Ag1 = float((*DataList)[Index-1].m_HongQiuSum)/6;
		for(int i = 0; i < 6; i++)
		{
			float Ag2=float((*DataList)[Index-1].m_HongQiu[i])/6;
			CString TempStr;
			TempStr.Format("%f ",Ag1+Ag2);

			TempStr=TempStr.Mid(TempStr.Find(".")+1,3);
			int Temp = atoi(TempStr.GetBuffer());
			if(Temp % 111 == 0)
			{
				TempData=Temp/111;
				IsTrue =  Index == DataList->size() ? true:CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData,true);
				FormulaData.m_Data   = CDataManageCenter::GetDataStr(TempData,IsTrue,true);
				FormulaData.m_IsTrue = IsTrue;
				FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
				FormualList[FormualIndex].m_DataList.push_back(FormulaData);
				FormualIndex++;

			}
			else
			{
				FormulaData.m_Data   = "";
				FormulaData.m_IsTrue = true;
				FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
				FormualList[FormualIndex].m_DataList.push_back(FormulaData);
				FormualIndex++;
			}
		}

		FormulaData.m_Data   = "";
		FormulaData.m_IsTrue = true;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;
		TempStr.Empty();


		if(Index > 1)
		{
			int Data = atoi((*DataList)[Index-2].m_QiShu);
			Data=Data%1000;
			Data = abs(Data - (*DataList)[Index-1].m_LanQiu);
			TempData = Data/10;
			TempData=TempData%10;

			IsTrue =  Index == DataList->size() ? true:CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData,true);
			FormulaData.m_Data   = CDataManageCenter::GetDataStr(TempData,IsTrue,true);
			FormulaData.m_IsTrue = IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = Data%10;
			IsTrue =  Index == DataList->size() ? true:CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData,true);
			FormulaData.m_Data   = CDataManageCenter::GetDataStr(TempData,IsTrue,true);
			FormulaData.m_IsTrue = IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;
		}
		else
		{
			FormulaData.m_Data   = "";
			FormulaData.m_IsTrue = false;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			FormulaData.m_Data   = "";
			FormulaData.m_IsTrue = false;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;
		}
		TempData = (*DataList)[Index-1].m_HongQiu[0] + (*DataList)[Index-1].m_HongQiu[5];
		TempData = TempData/10 + TempData%10;
		TempData = TempData%10;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData,true):true;
		FormulaData.m_Data   = CDataManageCenter::GetDataStr(TempData,IsTrue,true);
		FormulaData.m_IsTrue = IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		TempData = (*DataList)[Index-1].m_LanQiu%10 +(*DataList)[Index-1].m_HongQiu[2]%10;
		TempData = TempData%10;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData,true):true;
		FormulaData.m_Data   =  CDataManageCenter::GetDataStr(TempData,IsTrue,true);
		FormulaData.m_IsTrue = IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		FormulaData.m_Data   = "";
		FormulaData.m_IsTrue = true;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;


		if(Index == 1)
			RealCount+=FormualIndex;
	}

	for(int i = 0; i < RealCount; i++)
	{
		CString Name;
		Name.Format(_T("定_%02d"),i);
		FormualList[i].m_FormulaName = Name;
		FormualList[i].m_FormulaType = FORMULA_DING_HONG_DIAN;
		ToJiFormulaInfo(FormualList[i]);
		m_MapFormulaInfo[FORMULA_DING_HONG_DIAN].push_back(FormualList[i]);
	}

	//sort(m_MapFormulaInfo[FORMULA_SHA_LAN_WEI].begin(),m_MapFormulaInfo[FORMULA_SHA_LAN_WEI ].end(), SortByErrorCount);
}

//运行杀龙凤尾公式
void CFormulaCenter::ExecShaLongTouFormula()
{


    vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
	vector<sShuangSeQiu>* ShunXuDataList = CDataManageCenter::GetInstance()->GetDataListByChuHao();

	const int  FormualCount = 58;   //定义公式个数
	const int  MODE_COUNT=16;

	int RealCount=0;

	sFormulaInfo FormualList[FormualCount];

	for(int Index = 1; Index < (int)DataList->size()+1; Index++)
	{
    	int FormualIndex=0;
		sFormulaData FormulaData;
		int TempData = 0;
		bool IsTrue = false;
		CString TempStr;

	

		TempData = abs((*DataList)[Index-1].m_HongQiu[0]+(*DataList)[Index-1].m_HongQiu[1]);
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuWeiData((*DataList)[Index],TempData,0):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		TempData = abs((*DataList)[Index-1].m_HongQiu[4]%10+(*DataList)[Index-1].m_HongQiu[3]%10);
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuWeiData((*DataList)[Index],TempData,0):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;


		TempData = abs((*DataList)[Index-1].m_HongQiu[2]%10+(*DataList)[Index-1].m_HongQiu[5]%10);
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuWeiData((*DataList)[Index],TempData,0):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		TempData = abs((*DataList)[Index-1].m_HongQiu[2]%10+(*DataList)[Index-1].m_HongQiu[1]%10);
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuWeiData((*DataList)[Index],TempData,0):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;


		TempData = abs((*DataList)[Index-1].m_HongQiu[0]+(*DataList)[Index-1].m_HongQiu[3]%10);
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuWeiData((*DataList)[Index],TempData,0):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;


		TempData = abs((*ShunXuDataList)[Index-1].m_HongQiu[0]+(*ShunXuDataList)[Index-1].m_HongQiu[1]%10);
		TempData=TempData%10+TempData/10;
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuWeiData((*DataList)[Index],TempData,0):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		TempData = abs((*ShunXuDataList)[Index-1].m_HongQiu[0]%10);//+(*ShunXuDataList)[Index-1].m_HongQiu[4]%10);
		//TempData=TempData%10+TempData/10;
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuWeiData((*DataList)[Index],TempData,0):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		TempData = abs((*ShunXuDataList)[Index-1].m_HongQiu[4]%10);//+(*ShunXuDataList)[Index-1].m_HongQiu[4]%10);
		//TempData=TempData%10+TempData/10;
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuWeiData((*DataList)[Index],TempData,0):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		TempData = abs((*ShunXuDataList)[Index-1].m_HongQiu[0]%10)+(*DataList)[Index-1].m_HongQiu[0]%10;//+(*ShunXuDataList)[Index-1].m_HongQiu[4]%10);
		TempData=TempData%10+TempData/10;
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuWeiData((*DataList)[Index],TempData,0):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		FormulaData.m_Data   = "";
		FormulaData.m_IsTrue = true;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;



		//龙头胆组
		int TempData1=(*ShunXuDataList)[Index-1].m_HongQiu[5];
		while(true)
		{
			TempData1+=6;
			if(TempData1 > QIU_COUNT)
				break;
		}
		TempData=TempData1;
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuWeiData((*DataList)[Index],TempData,0):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;


		TempData = TempData1+1;
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuWeiData((*DataList)[Index],TempData,0):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;


		TempData = TempData1-1;
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuWeiData((*DataList)[Index],TempData,0):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;


		if(Index == 1)
			RealCount+=FormualIndex;
	}

	for(int i = 0; i < RealCount; i++)
	{
		CString Name;
		Name.Format(_T("杀头_%02d"),i);
		FormualList[i].m_FormulaName = Name;
		FormualList[i].m_FormulaType = FORMULA_SHA_LONG_TOU;
		ToJiFormulaInfo(FormualList[i]);
		m_MapFormulaInfo[FORMULA_SHA_LONG_TOU].push_back(FormualList[i]);
	}
}

//运行杀凤尾公式
void CFormulaCenter::ExecShaFengWeiFormula()
{
	vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
	vector<sShuangSeQiu>* ShunXuDataList = CDataManageCenter::GetInstance()->GetDataListByChuHao();

	const int  FormualCount = 58;   //定义公式个数
	const int  MODE_COUNT=16;

	int RealCount=0;

	sFormulaInfo FormualList[FormualCount];

	for(int Index = 1; Index < (int)DataList->size()+1; Index++)
	{
    	int FormualIndex=0;
		sFormulaData FormulaData;
		int TempData = 0;
		bool IsTrue = false;
		CString TempStr;

	

		TempData = (*DataList)[Index-1].m_HongQiu[3]+(*DataList)[Index-1].m_HongQiu[1];
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuWeiData((*DataList)[Index],TempData,5):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		TempData = (*DataList)[Index-1].m_HongQiu[3]%10+(*DataList)[Index-1].m_HongQiu[4];
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuWeiData((*DataList)[Index],TempData,5):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;


		TempData = (*DataList)[Index-1].m_HongQiu[4]%10+(*DataList)[Index-1].m_HongQiu[5];
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuWeiData((*DataList)[Index],TempData,5):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		TempData = (*DataList)[Index-1].m_HongQiu[2]%10+(*DataList)[Index-1].m_HongQiu[5];
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuWeiData((*DataList)[Index],TempData,5):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		TempData = (*DataList)[Index-1].m_HongQiu[2]%10+(*DataList)[Index-1].m_HongQiu[3]%10+(*DataList)[Index-1].m_HongQiu[4];
		if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuWeiData((*DataList)[Index],TempData,5):true;
		FormulaData.m_Data   = DataToStr(TempData);
		FormulaData.m_IsTrue = !IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		if(Index > 2)
		{
			TempData = (*DataList)[Index-2].m_HongQiu[1]+(*DataList)[Index-1].m_HongQiu[3];
			if(TempData > QIU_COUNT) TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuWeiData((*DataList)[Index],TempData,5):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = !IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;
		}
		else
		{
			FormulaData.m_Data   = "";
			FormulaData.m_IsTrue = true;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;
		}


		if(Index == 1)
			RealCount+=FormualIndex;
	}

	for(int i = 0; i < RealCount; i++)
	{
		CString Name;
		Name.Format(_T("杀尾_%02d"),i);
		FormualList[i].m_FormulaName = Name;
		FormualList[i].m_FormulaType = FORMULA_SHA_FENG_WEI;
		ToJiFormulaInfo(FormualList[i]);
		m_MapFormulaInfo[FORMULA_SHA_FENG_WEI].push_back(FormualList[i]);
	}
}
//运行尾不同出公式
void CFormulaCenter::ExecWeiBuTongChuFormula()
{
	vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
	vector<sShuangSeQiu>* ShunXuDataList = CDataManageCenter::GetInstance()->GetDataListByChuHao();

	const int  FormualCount = 58;   //定义公式个数
	const int  MODE_COUNT=16;

	int RealCount=0;

	sFormulaInfo FormualList[FormualCount];

	for(int Index = 1; Index < (int)DataList->size()+1; Index++)
	{
    	int FormualIndex=0;
		sFormulaData FormulaData;
		int TempData = 0;
		bool IsTrue = false;
		CString TempStr;

		vector<int> QianSan;
		vector<int> HouSan;
		vector<int> ShunQianSan;
		vector<int> ShunHouSan;

		int QianSanArray[10];
		int HouSanArray[10];
		int ShunQianSanArray[10];
		int ShunHouSanArray[10];

		memset(QianSanArray,0,sizeof(int)*10);
		memset(HouSanArray,0,sizeof(int)*10);
		memset(ShunQianSanArray,0,sizeof(int)*10);
		memset(ShunHouSanArray,0,sizeof(int)*10);

		
		for(int i=0; i < 6; i++)
		{
			int V=(*DataList)[Index-1].m_HongQiu[i]%10;
			int V2=(*ShunXuDataList)[Index-1].m_HongQiu[i]%10;
			if(i < 3)
			{
				QianSanArray[V]++;
				ShunQianSanArray[V2]++;

			}
			else
			{
				HouSanArray[V]++;
				ShunHouSanArray[V2]++;
			
			}
		}
		

		for(int i=0; i < 10; i++)
		{
			if(QianSanArray[i])
				QianSan.push_back(i);

			if(HouSanArray[i])
				HouSan.push_back(i);

			if(ShunQianSanArray[i])
				ShunQianSan.push_back(i);

			if(ShunHouSanArray[i])
				ShunHouSan.push_back(i);
		}

		if(QianSan.size()>2)
		{
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuTongChu((*DataList)[Index],QianSan,true):true;
			FormulaData.m_Data   = DataToStr(QianSan);
			FormulaData.m_IsTrue = IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;
		}
		else
		{
			IsTrue = false;
			FormulaData.m_Data   = "";
			FormulaData.m_IsTrue = false;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;
		}

		if(HouSan.size()>2)
		{
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuTongChu((*DataList)[Index],HouSan,true):true;
			FormulaData.m_Data   = DataToStr(HouSan);
			FormulaData.m_IsTrue = IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;
		}
		else
		{
			IsTrue = false;
			FormulaData.m_Data   = "";
			FormulaData.m_IsTrue = false;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;
		}


		if(ShunQianSan.size()>2)
		{
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuTongChu((*DataList)[Index],ShunQianSan,true):true;
			FormulaData.m_Data   = DataToStr(ShunQianSan);
			FormulaData.m_IsTrue = IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;
		}
		else
		{
			IsTrue = false;
			FormulaData.m_Data   = "";
			FormulaData.m_IsTrue = false;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;
		}


		if(ShunHouSan.size()>2)
		{
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuTongChu((*DataList)[Index],ShunHouSan,true):true;
			FormulaData.m_Data   = DataToStr(ShunHouSan);
			FormulaData.m_IsTrue = IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;
		}
		else
		{
			IsTrue = false;
			FormulaData.m_Data   = "";
			FormulaData.m_IsTrue = false;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;
		}
	
	
		if(Index == 1)
			RealCount+=FormualIndex;
	}

	for(int i = 0; i < RealCount; i++)
	{
		CString Name;
		Name.Format(_T("尾_%02d"),i);
		FormualList[i].m_FormulaName = Name;
		FormualList[i].m_FormulaType = FORMULA_WEI_BU_TONG_CHU;
		ToJiFormulaInfo(FormualList[i]);
		m_MapFormulaInfo[FORMULA_WEI_BU_TONG_CHU].push_back(FormualList[i]);
	}
}

//运行定红V公式
void CFormulaCenter::ExecDingHongVFormula()
{
	vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
	vector<sShuangSeQiu>* ShunXuDataList = CDataManageCenter::GetInstance()->GetDataListByChuHao();

	const int  FormualCount = 58;   //定义公式个数
	const int  MODE_COUNT=16;

	int RealCount=0;

	sFormulaInfo FormualList[FormualCount];

	for(int Index = 1; Index < (int)DataList->size()+1; Index++)
	{
    	int FormualIndex=0;
		sFormulaData FormulaData;
		int TempData = 0;
		bool IsTrue = false;

		if(Index > 1)
		{
			int Data = atoi((*DataList)[Index-2].m_QiShu);
			Data=Data%1000;
			Data = abs(Data - (*DataList)[Index-1].m_LanQiu);
			TempData = Data/10;
			TempData=TempData%10;

			IsTrue =  Index == DataList->size() ? true:CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData,true);
			FormulaData.m_Data   = CDataManageCenter::GetDataStr(TempData,IsTrue,true);
			FormulaData.m_IsTrue = IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = Data%10;
			IsTrue =  Index == DataList->size() ? true:CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData,true);
			FormulaData.m_Data   = CDataManageCenter::GetDataStr(TempData,IsTrue,true);
			FormulaData.m_IsTrue = IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;
		}
		else
		{
			FormulaData.m_Data   = "";
			FormulaData.m_IsTrue = false;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			FormulaData.m_Data   = "";
			FormulaData.m_IsTrue = false;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;
		}
		TempData = (*DataList)[Index-1].m_HongQiu[0] + (*DataList)[Index-1].m_HongQiu[5];
		TempData = TempData/10 + TempData%10;
		TempData = TempData%10;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData,true):true;
		FormulaData.m_Data   = CDataManageCenter::GetDataStr(TempData,IsTrue,true);
		FormulaData.m_IsTrue = IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		TempData = (*DataList)[Index-1].m_LanQiu%10 +(*DataList)[Index-1].m_HongQiu[2]%10;
		TempData = TempData%10;
		IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData,true):true;
		FormulaData.m_Data   =  CDataManageCenter::GetDataStr(TempData,IsTrue,true);
		FormulaData.m_IsTrue = IsTrue;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;

		/*FormulaData.m_Data   = "";
		FormulaData.m_IsTrue = true;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;*/


		int WeiZhiCount=GetWeiZhiCount((*DataList)[Index-1].m_HongQiu,QIU_XUN);
		for(int j=0; j < QIU_XUN; j++)
		{
			TempData = abs((*DataList)[Index-1].m_HongQiu[j]-WeiZhiCount);
			TempData = TempData%10;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData,true):true;
			FormulaData.m_Data   =  CDataManageCenter::GetDataStr(TempData,IsTrue,true);
			FormulaData.m_IsTrue = IsTrue;
			FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;
		}

		FormulaData.m_Data   = "";
		FormulaData.m_IsTrue = true;
		FormulaData.m_QiShu = Index < DataList->size() ? (*DataList)[Index].m_QiShu:_T("下期预测");
		FormualList[FormualIndex].m_DataList.push_back(FormulaData);
		FormualIndex++;


		if(Index == 1)
			RealCount+=FormualIndex;
	}

	for(int i = 0; i < RealCount; i++)
	{
		CString Name;
		Name.Format(_T("定尾_%02d"),i);
		FormualList[i].m_FormulaName = Name;
		FormualList[i].m_FormulaType = FORMULA_DING_HONG_WEI;
		ToJiFormulaInfo(FormualList[i]);
		m_MapFormulaInfo[FORMULA_DING_HONG_WEI].push_back(FormualList[i]);
	}
}

//获取尾值和
int CFormulaCenter::GetWeiZhiCount(int DataList[],int Count)
{
	int Data=0;
	for(int i=0; i < Count; i++)
	{
		Data+=DataList[i] % 10;
	}

	int Data1 = Data / 10;
	int Data2 = Data % 10;
	return Data1+Data2;
}