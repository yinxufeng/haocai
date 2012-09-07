#include "StdAfx.h"
#include "FormulaCenter.h"
#include "DataManageCenter.h"
#include <algorithm>   
using namespace std; 


bool SortByErrorCount(sFormulaInfo tp1, sFormulaInfo tp2)
{ 
	if(tp1.m_TrueCount > tp2.m_TrueCount)
		return false;
	else
		return true;

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

//公式运算
void CFormulaCenter::RunFormula()
{
	ExecShaHongFormula();
}


//运行杀红公式

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
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = (*DataList)[Index-1].m_HongQiu[2]-(*DataList)[Index-1].m_HongQiu[1];
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
		    FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;


			TempData = (*DataList)[Index-1].m_HongQiu[5]-(*DataList)[Index-1].m_HongQiu[1];
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = (*DataList)[Index-1].m_HongQiu[0]*4-2;
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;



			TempData = ((*DataList)[Index-1].m_HongQiu[0]+(*DataList)[Index-1].m_LanQiu)*3;
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;


			TempData = (*DataList)[Index-1].m_HongQiu[0]+9;
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = (*DataList)[Index-1].m_HongQiu[1]+5;
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = (*DataList)[Index-1].m_HongQiu[2]+4;
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = (*DataList)[Index-1].m_HongQiu[2]+7;
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = (*DataList)[Index-1].m_HongQiu[5]+4;
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = (*DataList)[Index-1].m_HongQiu[4]-(*DataList)[Index-1].m_HongQiu[3]+(*DataList)[Index-1].m_LanQiu+1;
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = (*DataList)[Index-1].m_LanQiu+(*DataList)[Index-1].m_HongQiu[0];
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = (*DataList)[Index-1].m_LanQiu+(*DataList)[Index-1].m_HongQiu[1]-1;
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;


			TempData = (*DataList)[Index-1].m_LanQiu-(*DataList)[Index-1].m_HongQiu[3]+1+33;
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = (*DataList)[Index-1].m_LanQiu-(*DataList)[Index-1].m_HongQiu[4]+33;
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = abs((*DataList)[Index-1].m_LanQiu*(*DataList)[Index-1].m_HongQiu[0]);
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = (*DataList)[Index-1].m_LanQiu+7;
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = (*DataList)[Index-1].m_LanQiu+9;
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

            TempData = (*DataList)[Index-1].m_LanQiu;
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;


			TempData = abs((*DataList)[Index-1].m_LanQiu-(*DataList)[Index-1].m_HongQiu[5]);
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = (*DataList)[Index-1].m_HongQiu[2]+(*DataList)[Index-1].m_HongQiu[5]/33 + 14;
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = ((*DataList)[Index-1].m_HongQiu[0]+(*DataList)[Index-1].m_HongQiu[2]+(*DataList)[Index-1].m_HongQiu[4])/2;
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = abs((*DataList)[Index-1].m_LanQiu+16-(*DataList)[Index-1].m_HongQiu[0]);
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = (*DataList)[Index-1].m_HongQiu[0]+(*DataList)[Index-1].m_HongQiu[1]+(*DataList)[Index-1].m_LanQiu;
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = (*DataList)[Index-1].m_HongQiu[5]-(*DataList)[Index-1].m_HongQiu[0]+(*DataList)[Index-1].m_HongQiu[2];
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;


			TempData = abs((*ShunXuDataList)[Index-1].m_HongQiu[1]-(*ShunXuDataList)[Index-1].m_HongQiu[2]);
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;
			

			TempData = abs((*ShunXuDataList)[Index-1].m_HongQiu[2]-(*ShunXuDataList)[Index-1].m_HongQiu[4]);
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;
				

			TempData = abs((*ShunXuDataList)[Index-1].m_HongQiu[0]-(*ShunXuDataList)[Index-1].m_HongQiu[5]) +(*ShunXuDataList)[Index-1].m_LanQiu-3;
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = abs((*ShunXuDataList)[Index-1].m_HongQiu[0]-(*ShunXuDataList)[Index-1].m_HongQiu[2]) +(*ShunXuDataList)[Index-1].m_LanQiu+2;
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

				
			TempData = (*ShunXuDataList)[Index-1].m_HongQiu[0]+(*ShunXuDataList)[Index-1].m_HongQiu[1]+(*ShunXuDataList)[Index-1].m_HongQiu[2] +(*ShunXuDataList)[Index-1].m_LanQiu-1;
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;


			//按AC值杀号
			TempData = CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = (*DataList)[Index-1].m_LanQiu;
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData = (*DataList)[Index-1].m_LanQiu+ CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;
			
			TempData =0;
			for(int i=0; i < 6; i++)
				TempData+=(*DataList)[Index-1].m_HongQiu[i]%10;
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;


			TempData =CDataManageCenter::GetZhiShuCount((*DataList)[Index-1]);
			TempData += (*DataList)[Index-1].m_LanQiu;
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData =CDataManageCenter::GetZhiShuCount((*DataList)[Index-1]);
			TempData =TempData*CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
	    	TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData =CDataManageCenter::GetZhiShuCount((*DataList)[Index-1]);
			TempData =TempData+CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData =CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
			TempData =abs(TempData - (*DataList)[Index-1].m_HongQiu[5]);
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

			TempData =CDataManageCenter::GetZhiShuCount((*DataList)[Index-1])+CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
			TempData =TempData + (*DataList)[Index-1].m_LanQiu;
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;

		

			for(int i=0; i < QIU_XUAN; i++)
			{
				float TempF = (float)(*DataList)[Index-1].m_HongQiu[i];
				TempF=TempF*0.88;
				TempData =(int)TempF;
				TempData = TempData%QIU_COUNT;
				IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
				FormulaData.m_Data   = DataToStr(TempData);
				FormulaData.m_IsTrue = IsTrue;
				FormualList[FormualIndex].m_DataList.push_back(FormulaData);
				FormualIndex++;
			}


			TempData =abs((*DataList)[Index-1].m_LanQiu+16-(*DataList)[Index-1].m_HongQiu[0]);
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;


			//上期开球顺序h2+上上期大小红球H3-2
			TempData =(*DataList)[Index-1].m_HongQiu[1]+(*ShunXuDataList)[Index-1].m_HongQiu[2] -2;
			TempData = TempData%QIU_COUNT;
			IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
			FormulaData.m_Data   = DataToStr(TempData);
			FormulaData.m_IsTrue = IsTrue;
			FormualList[FormualIndex].m_DataList.push_back(FormulaData);
			FormualIndex++;


			//上期开球顺序h2+上上期大小红球H2-2
			if(Index > 1)
			{
				TempData =(*DataList)[Index-1].m_HongQiu[1]+(*ShunXuDataList)[Index-2].m_HongQiu[1] -2;
				TempData = TempData%QIU_COUNT;
				IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
				FormulaData.m_Data   = DataToStr(TempData);
				FormulaData.m_IsTrue = IsTrue;
				FormualList[FormualIndex].m_DataList.push_back(FormulaData);
				FormualIndex++;
			}
			else
			{
				TempData =0;
				IsTrue = Index < DataList->size() ? CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData):true;
				FormulaData.m_Data   = DataToStr(TempData);
				FormulaData.m_IsTrue = IsTrue;
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

//字符串转化到整形
int CFormulaCenter::StrToData(CString DataStr)
{
	int Data=_wtoi(DataStr.GetBuffer());
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
