// DlgLianHaoLanQiu.cpp : 实现文件
//

#include "stdafx.h"
#include "ShuangSeQiu.h"
#include "DlgLianHaoLanQiu.h"
#include "FormulaCenter.h"

// CDlgLianHaoLanQiu 对话框

#define FORMULA_COUNT 24

//获取模块路径
CString GetAppCurrentPath3()
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



IMPLEMENT_DYNAMIC(CDlgLianHaoLanQiu, CDialog)

CDlgLianHaoLanQiu::CDlgLianHaoLanQiu(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLianHaoLanQiu::IDD, pParent)
{
	m_IsInitData = false;
}

CDlgLianHaoLanQiu::~CDlgLianHaoLanQiu()
{
}

void CDlgLianHaoLanQiu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CDlgLianHaoLanQiu, CDialog)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_SEARCH_BTN, &CDlgLianHaoLanQiu::OnBnClickedSearchBtn)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CDlgLianHaoLanQiu 消息处理程序

//初始化列表头
void CDlgLianHaoLanQiu::InitListHeader()
{
	CRect Rect;
	//初始化应用程序列表控件
	m_ListCtrl.GetWindowRect(&Rect);
	int nWidth = Rect.Width()/(FORMULA_COUNT+2);

	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(222,0,0);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;

	m_ListCtrl.InsertColumn(0,_TEXT("杀红"),    LVCFMT_CENTER,	2*nWidth);
	m_ListCtrl.SetColumStyle(0,Style);

	for(int Index = 1; Index < FORMULA_COUNT+1; Index++)
	{
		m_ListCtrl.InsertColumn(Index,_TEXT("杀红"),    LVCFMT_CENTER,	nWidth);
		m_ListCtrl.SetColumStyle(Index,Style);
	}


	
	m_ListCtrl.SetRowHeight(30);
	m_ListCtrl.ShowHeader(false);

	sItemBkData ItemBkData;
	ItemBkData.m_BkFillMode = MODE_FILL_RGB;
	ItemBkData.m_HeightColor = RGB(222,22,100);
	ItemBkData.m_HeightFillMode = MODE_FILL_RGB;
	ItemBkData.m_HeightColor = RGB(100,100,100);
	ItemBkData.m_BkColor = RGB(222,222,222);
	m_ListCtrl.SetItemBkData(ItemBkData);

}

void CDlgLianHaoLanQiu::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	CDialog::OnShowWindow(bShow, nStatus);
	if(!m_IsInitData)
	{
		m_IsInitData = true;
		sItemStyle Style;
		Style.m_ItemType = TEXT_TYPE;
		Style.m_DrawData.m_TextData.m_TextColor=RGB(222,0,0);
		Style.m_DrawData.m_TextData.m_TextFont = NULL;
		Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;

		m_ListCtrl.DeleteAllItems();
		vector<sFormulaInfo> FormulList=CFormulaCenter::GetInstance()->GetFormulaInfoByType(FORMULA_SHA_HONG);
		int DataSize = CDataManageCenter::GetInstance()->GetDataList()->size();
		for(int Index = 0; Index < DataSize; Index++)
		{
			m_ListCtrl.InsertItem(Index,_T(""));	
		}

		for(int Index = 0; Index < FORMULA_COUNT; Index++)
		{
			for(int i = 0; i < FormulList[Index].m_DataList.size(); i++)
			{
				if(Index ==0)
				{
					m_ListCtrl.SetItemText(i,0,FormulList[Index].m_DataList[i].m_QiShu);
				}
				m_ListCtrl.SetItemText(i,Index+1,FormulList[Index].m_DataList[i].m_Data);
				if(FormulList[Index].m_DataList[i].m_IsTrue)
				{
					Style.m_DrawData.m_TextData.m_TextColor=RGB(22,22,22);
					m_ListCtrl.SetItemSpecialStyle(i,Index+1,Style);
				}
				else
				{
				
					Style.m_DrawData.m_TextData.m_TextColor=RGB(222,0,0);
					m_ListCtrl.SetItemSpecialStyle(i,Index+1,Style);
				}
			}
		}

		m_ListCtrl.InsertItem(DataSize+1,_T(""));
		m_ListCtrl.SetItemText(DataSize,0,_T("正确率"));
		for(int Index = 0; Index < FORMULA_COUNT; Index++)
		{
			CString Str;
			Str.Format(_T("%d%%"),FormulList[Index].m_TrueCount*100/(FormulList[Index].m_ErrorCount+FormulList[Index].m_TrueCount));
			m_ListCtrl.SetItemText(DataSize,Index+1,Str);
			Style.m_DrawData.m_TextData.m_TextColor=RGB(222,0,0);
			m_ListCtrl.SetItemSpecialStyle(DataSize,Index+1,Style);
		}
	}
//	if(!m_IsInitData)
//	{
	/*	m_IsInitData = true;
		m_ListCtrl.DeleteAllItems();
		m_ListCtrl.InsertItem(0,"");
		vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
		vector<sShuangSeQiu>* ShunXuDataList = CDataManageCenter::GetInstance()->GetDataListByChuHao();
		int Sum[6];
		memset(Sum,0,sizeof(int)*6);*/

		
	/*	CString FilePath = GetAppCurrentPath3()+_T("\\shahao.txt");
		HANDLE FileHandle=CreateFile(FilePath,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

		for(int Index = 1; Index < (int)DataList->size()+1; Index++)
		{
			int ShaArray[34];
	    	memset(ShaArray,0,sizeof(int)*34);
			m_ListCtrl.InsertItem(Index,"");
			if(Index == DataList->size())
			{
				m_ListCtrl.SetItemText(Index,0,"预测");
			}
			else
			{
				CString Str;
				Str.Format("%s ",(*DataList)[Index].m_QiShu);
				for(int i =0; i < 6; i++)
				{
					CString Temp;
					Temp.Format("%02d ",(*DataList)[Index].m_HongQiu[i]);
					Str+=Temp;
				}

				CString TempLan;
				TempLan.Format("+%02d",(*DataList)[Index].m_LanQiu);
				Str+=TempLan;
				m_ListCtrl.SetItemText(Index,0,Str);

			}

			CString JunZhi;

			for(int i = 0; i < 6; i++)
			{
				Sum[i]+=(*DataList)[Index-1].m_HongQiu[i];
				CString Temp;
				Temp.Format("%02d ",Sum[i]/Index);
				JunZhi+=Temp;
			}

			m_ListCtrl.SetItemText(Index,1,JunZhi);

			CString ShaHongList;
			int TempData = (*DataList)[Index-1].m_HongQiu[5]-(*DataList)[Index-1].m_HongQiu[0];
			CString ShaHong;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_HongQiu[2]-(*DataList)[Index-1].m_HongQiu[1];
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_HongQiu[5]-(*DataList)[Index-1].m_HongQiu[1];
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_HongQiu[0]*4-2;
			if(TempData > 33)
				TempData = TempData%33;

			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);

			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = ((*DataList)[Index-1].m_HongQiu[0]+(*DataList)[Index-1].m_LanQiu)*3;
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_HongQiu[0]+9;
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);

			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;


			TempData = (*DataList)[Index-1].m_HongQiu[1]+5;
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_HongQiu[2]+4;
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_HongQiu[2]+7;
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_HongQiu[5]+4;
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_HongQiu[4]-(*DataList)[Index-1].m_HongQiu[3]+(*DataList)[Index-1].m_LanQiu+1;
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_LanQiu+(*DataList)[Index-1].m_HongQiu[0];
			if(Index >= 2)
			{
				if((*DataList)[Index-1].m_LanQiu == ((*DataList)[Index-2].m_LanQiu))
					TempData-=1;
			}
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_LanQiu+(*DataList)[Index-1].m_HongQiu[1]-1;
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;


			TempData = (*DataList)[Index-1].m_LanQiu-(*DataList)[Index-1].m_HongQiu[3]+1+33;
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_LanQiu-(*DataList)[Index-1].m_HongQiu[4]+33;
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = abs((*DataList)[Index-1].m_LanQiu*(*DataList)[Index-1].m_HongQiu[0]);
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_LanQiu+7;
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_LanQiu+9;
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

            TempData = (*DataList)[Index-1].m_LanQiu;
			if(TempData /2 == 0)
				TempData=TempData*2+2;
			else
				TempData=TempData*5+2;

			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;


			TempData = abs((*DataList)[Index-1].m_LanQiu-(*DataList)[Index-1].m_HongQiu[5]);
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_HongQiu[2]+(*DataList)[Index-1].m_HongQiu[5]/33 + 14;
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = ((*DataList)[Index-1].m_HongQiu[0]+(*DataList)[Index-1].m_HongQiu[2]+(*DataList)[Index-1].m_HongQiu[4])/2;
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = abs((*DataList)[Index-1].m_LanQiu+16-(*DataList)[Index-1].m_HongQiu[0]);
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_HongQiu[0]+(*DataList)[Index-1].m_HongQiu[1]+(*DataList)[Index-1].m_LanQiu;
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_HongQiu[5]-(*DataList)[Index-1].m_HongQiu[0]+(*DataList)[Index-1].m_HongQiu[2];
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;*/

		
			//按出球顺序杀号法
		//	if( ShunXuDataList->size() == DataList->size())
	//		{
			/*	TempData = (*ShunXuDataList)[Index-1].m_HongQiu[0]+(*ShunXuDataList)[Index-1].m_HongQiu[1];
				if(TempData > 33)
					TempData = TempData%33;
				if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
					ShaHong.Format("%02dF ",TempData);
				else
					ShaHong.Format("%02dS ",TempData);
				ShaHongList += ShaHong;
				ShaHong.Empty();
*/
			/*
				TempData = abs((*ShunXuDataList)[Index-1].m_HongQiu[1]-(*ShunXuDataList)[Index-1].m_HongQiu[2]);
				if(TempData > 33)
					TempData = TempData%33;
				if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
					ShaHong.Format("%02dF ",TempData);
				else
					ShaHong.Format("%02dS ",TempData);
				ShaHongList += ShaHong;
				ShaHong.Empty();
				ShaArray[TempData]++;

				TempData = abs((*ShunXuDataList)[Index-1].m_HongQiu[2]-(*ShunXuDataList)[Index-1].m_HongQiu[4]);
				if(TempData > 33)
					TempData = TempData%33;
				if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
					ShaHong.Format("%02dF ",TempData);
				else
					ShaHong.Format("%02dS ",TempData);
				ShaHongList += ShaHong;
				ShaHong.Empty();
				ShaArray[TempData]++;


				TempData = abs((*ShunXuDataList)[Index-1].m_HongQiu[0]-(*ShunXuDataList)[Index-1].m_HongQiu[5]) +(*ShunXuDataList)[Index-1].m_LanQiu-3;
				if(TempData > 33)
					TempData = TempData%33;
				if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
					ShaHong.Format("%02dF ",TempData);
				else
					ShaHong.Format("%02dS ",TempData);
				ShaHongList += ShaHong;
				ShaHong.Empty();
				ShaArray[TempData]++;

				TempData = abs((*ShunXuDataList)[Index-1].m_HongQiu[0]-(*ShunXuDataList)[Index-1].m_HongQiu[2]) +(*ShunXuDataList)[Index-1].m_LanQiu+2;
				if(TempData > 33)
					TempData = TempData%33;
				if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
					ShaHong.Format("%02dF ",TempData);
				else
					ShaHong.Format("%02dS ",TempData);
				ShaHongList += ShaHong;
				ShaHong.Empty();
				ShaArray[TempData]++;

				
				TempData = (*ShunXuDataList)[Index-1].m_HongQiu[0]+(*ShunXuDataList)[Index-1].m_HongQiu[1]+(*ShunXuDataList)[Index-1].m_HongQiu[2] +(*ShunXuDataList)[Index-1].m_LanQiu-1;
				if(TempData > 33)
					TempData = TempData%33;
				if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
					ShaHong.Format("%02dF ",TempData);
				else
					ShaHong.Format("%02dS ",TempData);
				ShaHongList += ShaHong;
				ShaHong.Empty();
				ShaArray[TempData]++;


			}

			//按AC值杀号
			TempData = CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_LanQiu;
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_LanQiu+ CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			
			TempData =0;
			for(int i=0; i < 6; i++)
				TempData+=(*DataList)[Index-1].m_HongQiu[i]%10;
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData =CDataManageCenter::GetZhiShuCount((*DataList)[Index-1]);
			TempData += (*DataList)[Index-1].m_LanQiu;
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData =CDataManageCenter::GetZhiShuCount((*DataList)[Index-1]);
			TempData =TempData*CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData =CDataManageCenter::GetZhiShuCount((*DataList)[Index-1]);
			TempData =TempData+CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData =CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
			TempData =abs(TempData - (*DataList)[Index-1].m_HongQiu[5]);
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData =CDataManageCenter::GetZhiShuCount((*DataList)[Index-1])+CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
			TempData =TempData + (*DataList)[Index-1].m_LanQiu;
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;


			for(int i=0; i < 6; i++)
			{
				float TempF = (float)(*DataList)[Index-1].m_HongQiu[i];
				TempF=TempF*0.88;
				TempData =(int)TempF;
				if(TempData > 33)
					TempData = TempData%33;
				if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
					ShaHong.Format("%02dF ",TempData);
				else
					ShaHong.Format("%02dS ",TempData);
				ShaHongList += ShaHong;
				ShaHong.Empty();
				ShaArray[TempData]++;
			}
//*/
//			m_ListCtrl.SetItemText(Index,2,ShaHongList);
//
//
//		
//			if(FileHandle!= INVALID_HANDLE_VALUE)
//			{
//				int ShaCount=0;
//				int ErrorCount=0;
//				CString TempStr;
//				for(int i=1; i < 34;i++)
//				{
//					if(ShaArray[i])
//					{
//						CString Temp;
//						Temp.Format("%02d ",i);
//						TempStr+=Temp;
//						ShaCount++;
//						if(Index != DataList->size())
//						{
//							for(int j=0; j < 6; j++)
//							{
//								if((*DataList)[Index].m_HongQiu[j] == i)
//								{
//									ErrorCount++;
//									break;
//								}
//							}
//						}
//					}
//
//				}
//
//				if(Index != DataList->size())
//				{
//					CString Temp;
//					Temp.Format("  杀号个数:%02d,错误个数:%02d\r\n",ShaCount,ErrorCount);
//					TempStr=(*DataList)[Index].m_QiShu+Temp+TempStr+"\r\n";
//				}
//				else
//				{
//					CString Temp;
//					Temp.Format("  杀号个数:%02d\r\n",ShaCount);
//					TempStr="下期杀号"+Temp+TempStr+"\r\n";
//				}
//
//				DWORD WriteBytes=0;
//				::WriteFile(FileHandle,TempStr.GetBuffer(),TempStr.GetLength(),&WriteBytes,NULL);
//				
//			}
//		}
//
//		if(FileHandle != INVALID_HANDLE_VALUE)
//		{
//			CloseHandle(FileHandle);
//			//ShellExecute(NULL, "open",FilePath, NULL, NULL, SW_SHOWNORMAL);
//		}

//	}
}

// 生成的消息映射函数
BOOL CDlgLianHaoLanQiu::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitListHeader();
	return true;
}

void CDlgLianHaoLanQiu::OnClose()
{
	ShowWindow(SW_HIDE);
}

void CDlgLianHaoLanQiu::OnBnClickedSearchBtn()
{
	
}

BOOL CDlgLianHaoLanQiu::OnEraseBkgnd(CDC* pDC)
{
	/*CRect Rect;
	GetClientRect(Rect);
	pDC->FillSolidRect(Rect,RGB(222,222,222));

	vector<sShuangSeQiu>* pData=CDataManageCenter::GetInstance()->GetDataList();
	
	if(pData->size() == 0)
		return true;


	int Len = pData->size();
	Rect.top +=5;
	Rect.bottom-=5;
	int Height = Rect.Height()/Len;
	int Width  = Rect.Width()/33;


	for(int Index = 0; Index < Len; Index++)
	{
		for(int i = 0; i < 33; i++)
		{
			CRect Temp = Rect;
		    Temp.left = Rect.left + i*Width;
			Temp.right = Temp.left + Width;
			Temp.top = Rect.top + Index*Height;
			Temp.bottom = Temp.top + Height;

			bool IsWant = false;
			for(int j = 0; j < 6; j++)
			{
				if( (*pData)[Index].m_HongQiu[j] == i+1)
				{
					IsWant = true;
					break;
				}

			}

			if(IsWant)
				pDC->FillSolidRect(Temp,RGB(255,0,0));
			else
			{
				if( i % 2 == 0)
					pDC->FillSolidRect(Temp,RGB(0,0,0));
				else
					pDC->FillSolidRect(Temp,RGB(25,25,255));

			}
		}
	}

	return true;
	*/
	return CDialog::OnEraseBkgnd(pDC);
}
