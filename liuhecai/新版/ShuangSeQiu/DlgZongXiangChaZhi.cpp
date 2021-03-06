// DlgZongXiangChaZhi.cpp : 实现文件
//

#include "stdafx.h"
#include "ShuangSeQiu.h"
#include "DlgZongXiangChaZhi.h"
#include "FormulaCenter.h"

CString GetAppCurrentPath4()
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

#define BEGIN_FORMULA 24
#define END_FORMULA   48

// CDlgZongXiangChaZhi 对话框

IMPLEMENT_DYNAMIC(CDlgZongXiangChaZhi, CDialog)

CDlgZongXiangChaZhi::CDlgZongXiangChaZhi(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgZongXiangChaZhi::IDD, pParent)
{
	m_IsInitData = false;
}

CDlgZongXiangChaZhi::~CDlgZongXiangChaZhi()
{
}

void CDlgZongXiangChaZhi::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CDlgZongXiangChaZhi, CDialog)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()

END_MESSAGE_MAP()


// CDlgZongXiangChaZhi 消息处理程序
//初始化列表头
void CDlgZongXiangChaZhi::InitListHeader()
{
	//CRect Rect;
	////初始化应用程序列表控件
	//
	//m_ListCtrl.GetWindowRect(&Rect);
	//int nWidth = Rect.Width()/10;
	//m_ListCtrl.InsertColumn(0,_TEXT("期数"),    LVCFMT_CENTER,	2*nWidth);
	//m_ListCtrl.InsertColumn(2,_TEXT("杀红"),	LVCFMT_CENTER,	8*nWidth);

	CRect Rect;
	//初始化应用程序列表控件
	m_ListCtrl.GetWindowRect(&Rect);
	int FormulCount = END_FORMULA-BEGIN_FORMULA;
	int nWidth = Rect.Width()/(FormulCount+2);

	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(222,0,0);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;

	m_ListCtrl.InsertColumn(0,_TEXT("杀红"),    LVCFMT_CENTER,	2*nWidth);
	m_ListCtrl.SetColumStyle(0,Style);

	for(int Index = 1; Index < FormulCount+1; Index++)
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

void CDlgZongXiangChaZhi::OnShowWindow(BOOL bShow, UINT nStatus)
{
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
		vector<sFormulaInfo> FormulList=CFormulaCenter::GetInstance()->GetFormulaInfoByType(FORMULA_SHA_LAN);
		int DataSize = CDataManageCenter::GetInstance()->GetDataList()->size();
		for(int Index = 0; Index < DataSize; Index++)
		{
			m_ListCtrl.InsertItem(Index,_T(""));	
		}

	
		for(int Index = BEGIN_FORMULA; Index < END_FORMULA; Index++)
		{
			for(int i = 0; i < FormulList[Index].m_DataList.size(); i++)
			{
				int TempIndex = Index -BEGIN_FORMULA;
				if(TempIndex ==0)
				{
					m_ListCtrl.SetItemText(i,0,FormulList[Index].m_DataList[i].m_QiShu);
				}
				m_ListCtrl.SetItemText(i,TempIndex+1,FormulList[Index].m_DataList[i].m_Data);

				if(FormulList[Index].m_DataList[i].m_IsTrue)
				{
					if(Index %2 == 0)
						Style.m_DrawData.m_TextData.m_TextColor=RGB(22,22,22);
					else
						Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);

					Style.m_DrawData.m_TextData.m_BGColor =RGB(205,250,213);
					m_ListCtrl.SetItemSpecialStyle(i+1,TempIndex+1,Style);
				}
				else
				{

					Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);
					Style.m_DrawData.m_TextData.m_BGColor = RGB(248,183,173);
					m_ListCtrl.SetItemSpecialStyle(i+1,TempIndex+1,Style);
				}
				/*if(FormulList[Index].m_DataList[i].m_IsTrue)
				{
					if(Index %2 == 0)
						Style.m_DrawData.m_TextData.m_TextColor=RGB(22,22,22);
					else
						Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);

					m_ListCtrl.SetItemSpecialStyle(i,TempIndex+1,Style);
				}
				else
				{
				
					Style.m_DrawData.m_TextData.m_TextColor=RGB(222,0,0);
					m_ListCtrl.SetItemSpecialStyle(i,TempIndex+1,Style);
				}*/
			}
		}

		m_ListCtrl.InsertItem(DataSize+1,_T(""));
		m_ListCtrl.SetItemText(DataSize,0,_T("正确率"));
		for(int Index = BEGIN_FORMULA; Index < END_FORMULA; Index++)
		{
			int TempIndex = Index - BEGIN_FORMULA;
			CString Str;
			Str.Format(_T("%d%%"),FormulList[Index].m_TrueCount*100/(FormulList[Index].m_ErrorCount+FormulList[Index].m_TrueCount));
			m_ListCtrl.SetItemText(DataSize,TempIndex+1,Str);
			Style.m_DrawData.m_TextData.m_TextColor=RGB(222,0,0);
			m_ListCtrl.SetItemSpecialStyle(DataSize,TempIndex+1,Style);
		}
	}

	//if(!m_IsInitData)
	//{
	//	m_IsInitData = true;
	//    m_ListCtrl.DeleteAllItems();
	//	m_ListCtrl.InsertItem(0,"");
	//	vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
	//	vector<sShuangSeQiu>* ShunXuDataList = CDataManageCenter::GetInstance()->GetDataListByChuHao();
	//	int Sum[6];
	//	memset(Sum,0,sizeof(int)*6);

	//	
	//	CString FilePath = GetAppCurrentPath4()+_T("\\shahao2.txt");
	//	HANDLE FileHandle=CreateFile(FilePath,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

	//	for(int Index = 1; Index < (int)DataList->size()+1; Index++)
	//	{
	//		int ShaArray[34];
	//    	memset(ShaArray,0,sizeof(int)*34);
	//		m_ListCtrl.InsertItem(Index,"");
	//		if(Index == DataList->size())
	//		{
	//			m_ListCtrl.SetItemText(Index,0,"预测");
	//		}
	//		else
	//		{
	//			CString Str;
	//			Str.Format("%s ",(*DataList)[Index].m_QiShu);
	//			for(int i =0; i < 6; i++)
	//			{
	//				CString Temp;
	//				Temp.Format("%02d ",(*DataList)[Index].m_HongQiu[i]);
	//				Str+=Temp;
	//			}

	//			CString TempLan;
	//			TempLan.Format("+%02d",(*DataList)[Index].m_LanQiu);
	//			Str+=TempLan;
	//			m_ListCtrl.SetItemText(Index,0,Str);

	//		}

	//
	//		CString ShaHongList;
	//		int TempData =0;
	//		CString ShaHong;

	//		
	//		//按出球顺序杀号法
	//	//	if( ShunXuDataList->size() == DataList->size())
	//	{
	//			TempData = abs((*ShunXuDataList)[Index-1].m_HongQiu[1]-(*ShunXuDataList)[Index-1].m_HongQiu[2]);
	//			if(TempData > 33)
	//				TempData = TempData%33;
	//			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
	//				ShaHong.Format("%02dF ",TempData);
	//			else
	//				ShaHong.Format("%02dS ",TempData);
	//			ShaHongList += ShaHong;
	//			ShaHong.Empty();
	//			ShaArray[TempData]++;

	//			TempData = abs((*ShunXuDataList)[Index-1].m_HongQiu[2]-(*ShunXuDataList)[Index-1].m_HongQiu[4]);
	//			if(TempData > 33)
	//				TempData = TempData%33;
	//			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
	//				ShaHong.Format("%02dF ",TempData);
	//			else
	//				ShaHong.Format("%02dS ",TempData);
	//			ShaHongList += ShaHong;
	//			ShaHong.Empty();
	//			ShaArray[TempData]++;


	//			TempData = abs((*ShunXuDataList)[Index-1].m_HongQiu[0]-(*ShunXuDataList)[Index-1].m_HongQiu[5]) +(*ShunXuDataList)[Index-1].m_LanQiu-3;
	//			if(TempData > 33)
	//				TempData = TempData%33;
	//			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
	//				ShaHong.Format("%02dF ",TempData);
	//			else
	//				ShaHong.Format("%02dS ",TempData);
	//			ShaHongList += ShaHong;
	//			ShaHong.Empty();
	//			ShaArray[TempData]++;

	//			TempData = abs((*ShunXuDataList)[Index-1].m_HongQiu[0]-(*ShunXuDataList)[Index-1].m_HongQiu[2]) +(*ShunXuDataList)[Index-1].m_LanQiu+2;
	//			if(TempData > 33)
	//				TempData = TempData%33;
	//			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
	//				ShaHong.Format("%02dF ",TempData);
	//			else
	//				ShaHong.Format("%02dS ",TempData);
	//			ShaHongList += ShaHong;
	//			ShaHong.Empty();
	//			ShaArray[TempData]++;

	//			
	//			TempData = (*ShunXuDataList)[Index-1].m_HongQiu[0]+(*ShunXuDataList)[Index-1].m_HongQiu[1]+(*ShunXuDataList)[Index-1].m_HongQiu[2] +(*ShunXuDataList)[Index-1].m_LanQiu-1;
	//			if(TempData > 33)
	//				TempData = TempData%33;
	//			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
	//				ShaHong.Format("%02dF ",TempData);
	//			else
	//				ShaHong.Format("%02dS ",TempData);
	//			ShaHongList += ShaHong;
	//			ShaHong.Empty();
	//			ShaArray[TempData]++;


	//		}

	//		//按AC值杀号
	//		TempData = CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
	//		if(TempData > 33)
	//			TempData = TempData%33;
	//		if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
	//			ShaHong.Format("%02dF ",TempData);
	//		else
	//			ShaHong.Format("%02dS ",TempData);
	//		ShaHongList += ShaHong;
	//		ShaHong.Empty();
	//		ShaArray[TempData]++;

	//		TempData = (*DataList)[Index-1].m_LanQiu;
	//		if(TempData > 33)
	//			TempData = TempData%33;
	//		if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
	//			ShaHong.Format("%02dF ",TempData);
	//		else
	//			ShaHong.Format("%02dS ",TempData);
	//		ShaHongList += ShaHong;
	//		ShaHong.Empty();
	//		ShaArray[TempData]++;

	//		TempData = (*DataList)[Index-1].m_LanQiu+ CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
	//		if(TempData > 33)
	//			TempData = TempData%33;
	//		if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
	//			ShaHong.Format("%02dF ",TempData);
	//		else
	//			ShaHong.Format("%02dS ",TempData);
	//		ShaHongList += ShaHong;
	//		ShaHong.Empty();
	//		ShaArray[TempData]++;

	//		
	//		TempData =0;
	//		for(int i=0; i < 6; i++)
	//			TempData+=(*DataList)[Index-1].m_HongQiu[i]%10;
	//		if(TempData > 33)
	//			TempData = TempData%33;
	//		if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
	//			ShaHong.Format("%02dF ",TempData);
	//		else
	//			ShaHong.Format("%02dS ",TempData);
	//		ShaHongList += ShaHong;
	//		ShaHong.Empty();
	//		ShaArray[TempData]++;

	//		TempData =CDataManageCenter::GetZhiShuCount((*DataList)[Index-1]);
	//		TempData += (*DataList)[Index-1].m_LanQiu;
	//		if(TempData > 33)
	//			TempData = TempData%33;
	//		if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
	//			ShaHong.Format("%02dF ",TempData);
	//		else
	//			ShaHong.Format("%02dS ",TempData);
	//		ShaHongList += ShaHong;
	//		ShaHong.Empty();
	//		ShaArray[TempData]++;

	//		TempData =CDataManageCenter::GetZhiShuCount((*DataList)[Index-1]);
	//		TempData =TempData*CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
	//		if(TempData > 33)
	//			TempData = TempData%33;
	//		if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
	//			ShaHong.Format("%02dF ",TempData);
	//		else
	//			ShaHong.Format("%02dS ",TempData);
	//		ShaHongList += ShaHong;
	//		ShaHong.Empty();
	//		ShaArray[TempData]++;

	//		TempData =CDataManageCenter::GetZhiShuCount((*DataList)[Index-1]);
	//		TempData =TempData+CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
	//		if(TempData > 33)
	//			TempData = TempData%33;
	//		if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
	//			ShaHong.Format("%02dF ",TempData);
	//		else
	//			ShaHong.Format("%02dS ",TempData);
	//		ShaHongList += ShaHong;
	//		ShaHong.Empty();
	//		ShaArray[TempData]++;

	//		TempData =CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
	//		TempData =abs(TempData - (*DataList)[Index-1].m_HongQiu[5]);
	//		if(TempData > 33)
	//			TempData = TempData%33;
	//		if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
	//			ShaHong.Format("%02dF ",TempData);
	//		else
	//			ShaHong.Format("%02dS ",TempData);
	//		ShaHongList += ShaHong;
	//		ShaHong.Empty();
	//		ShaArray[TempData]++;

	//		TempData =CDataManageCenter::GetZhiShuCount((*DataList)[Index-1])+CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
	//		TempData =TempData + (*DataList)[Index-1].m_LanQiu;
	//		if(TempData > 33)
	//			TempData = TempData%33;
	//		if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
	//			ShaHong.Format("%02dF ",TempData);
	//		else
	//			ShaHong.Format("%02dS ",TempData);
	//		ShaHongList += ShaHong;
	//		ShaHong.Empty();
	//		ShaArray[TempData]++;

	//	

	//		for(int i=0; i < 6; i++)
	//		{
	//			float TempF = (float)(*DataList)[Index-1].m_HongQiu[i];
	//			TempF=TempF*0.88;
	//			TempData =(int)TempF;
	//			if(TempData > 33)
	//				TempData = TempData%33;
	//			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
	//				ShaHong.Format("%02dF ",TempData);
	//			else
	//				ShaHong.Format("%02dS ",TempData);
	//			ShaHongList += ShaHong;
	//			ShaHong.Empty();
	//			ShaArray[TempData]++;
	//		}


		/*	if(Index > 2)
			{
				TempData = 33-(*DataList)[Index-2].m_LanQiu;
				if(TempData > 33)
					TempData = TempData%33;
				if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
					ShaHong.Format("%02dF ",TempData);
				else
					ShaHong.Format("%02dS ",TempData);
				ShaHongList += ShaHong;
				ShaHong.Empty();
				ShaArray[TempData]++;
			}*/

		/*	TempData =(*DataList)[Index-1].m_HongQiu[4]-(*DataList)[Index-1].m_HongQiu[1];
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;*/

	//		TempData =abs((*DataList)[Index-1].m_LanQiu+16-(*DataList)[Index-1].m_HongQiu[0]);
	//		if(TempData > 33)
	//			TempData = TempData%33;
	//		if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
	//			ShaHong.Format("%02dF ",TempData);
	//		else
	//			ShaHong.Format("%02dS ",TempData);
	//		ShaHongList += ShaHong;
	//		ShaHong.Empty();
	//		ShaArray[TempData]++;


	//		//上期开球顺序h2+上上期大小平码H3-2
	//		TempData =(*DataList)[Index-1].m_HongQiu[1]+(*ShunXuDataList)[Index-1].m_HongQiu[2] -2;
	//		if(TempData > 33)
	//			TempData = TempData%33;
	//		if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
	//			ShaHong.Format("%02dF ",TempData);
	//		else
	//			ShaHong.Format("%02dS ",TempData);
	//		ShaHongList += ShaHong;
	//		ShaHong.Empty();
	//		ShaArray[TempData]++;


	//		//上期开球顺序h2+上上期大小平码H2-2
	//		if(Index > 1)
	//		{
	//		TempData =(*DataList)[Index-1].m_HongQiu[1]+(*ShunXuDataList)[Index-2].m_HongQiu[1] -2;
	//		if(TempData > 33)
	//			TempData = TempData%33;
	//		if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
	//			ShaHong.Format("%02dF ",TempData);
	//		else
	//			ShaHong.Format("%02dS ",TempData);
	//		ShaHongList += ShaHong;
	//		ShaHong.Empty();
	//		ShaArray[TempData]++;
	//		}
	//	/*	TempData =(*DataList)[Index-1].m_HongQiu[0]*4-2;
	//		if(TempData > 33)
	//			TempData = TempData%33;
	//		if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
	//			ShaHong.Format("%02dF ",TempData);
	//		else
	//			ShaHong.Format("%02dS ",TempData);
	//		ShaHongList += ShaHong;
	//		ShaHong.Empty();
	//		ShaArray[TempData]++;*/

	//	/*	TempData = (*DataList)[Index-1].m_LanQiu+7;
	//		if(TempData > 33)
	//			TempData = TempData%33;
	//		if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
	//			ShaHong.Format("%02dF ",TempData);
	//		else
	//			ShaHong.Format("%02dS ",TempData);
	//		ShaHongList += ShaHong;
	//		ShaHong.Empty();
	//		ShaArray[TempData]++;*/



	//		m_ListCtrl.SetItemText(Index,1,ShaHongList);


	//	
	//		if(FileHandle!= INVALID_HANDLE_VALUE)
	//		{
	//			int ShaCount=0;
	//			int ErrorCount=0;
	//			CString TempStr;
	//			for(int i=1; i < 34;i++)
	//			{
	//				if(ShaArray[i])
	//				{
	//					CString Temp;
	//					Temp.Format("%02d ",i);
	//					TempStr+=Temp;
	//					ShaCount++;
	//					if(Index != DataList->size())
	//					{
	//						for(int j=0; j < 6; j++)
	//						{
	//							if((*DataList)[Index].m_HongQiu[j] == i)
	//							{
	//								ErrorCount++;
	//								break;
	//							}
	//						}
	//					}
	//				}

	//			}

	//			if(Index != DataList->size())
	//			{
	//				CString Temp;
	//				Temp.Format("  杀号个数:%02d,错误个数:%02d\r\n",ShaCount,ErrorCount);
	//				TempStr=(*DataList)[Index].m_QiShu+Temp+TempStr+"\r\n";
	//			}
	//			else
	//			{
	//				CString Temp;
	//				Temp.Format("  杀号个数:%02d\r\n",ShaCount);
	//				TempStr="下期杀号"+Temp+TempStr+"\r\n";
	//			}

	//			DWORD WriteBytes=0;
	//			::WriteFile(FileHandle,TempStr.GetBuffer(),TempStr.GetLength(),&WriteBytes,NULL);
	//			
	//		}
	//	}

	//	if(FileHandle != INVALID_HANDLE_VALUE)
	//	{
	//		CloseHandle(FileHandle);
	//		//ShellExecute(NULL, "open",FilePath, NULL, NULL, SW_SHOWNORMAL);
	//	}

	//}
	//

}

// 生成的消息映射函数
BOOL CDlgZongXiangChaZhi::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitListHeader();
	return true;
}

void CDlgZongXiangChaZhi::OnClose()
{
	ShowWindow(SW_HIDE);
}

void CDlgZongXiangChaZhi::OnBnClickedSearchBtn()
{
	/*CString Text;
	GetDlgItem(IDC_EDIT1)->GetWindowText(Text);
	DWORD Data=::atoi(Text.GetBuffer());
	m_ListCtrl.DeleteAllItems();
	vector<sZongXiangChaZhi>* DataList = NULL;
	vector<sZongXiangChaZhi> Temp;
	if(Data == 0)
	{
		DataList=CDataManageCenter::GetInstance()->GetZongXiangChaZhi();
	}
	else
	{
		Temp=CDataManageCenter::GetInstance()->SearchZongXiangChaZhi(Data);
		DataList=&Temp;
	}

	for(int Index = 0; Index < (int)DataList->size(); Index++)
	{
		m_ListCtrl.InsertItem(Index,"");
		m_ListCtrl.SetItemText(Index,0,(*DataList)[Index].m_QiShu);
		for(int HongQiu=0; HongQiu < 6; HongQiu++)
		{
			CString Temp;
			Temp.Format("%d",(*DataList)[Index].m_HongQiuChaZhi[HongQiu]);
			m_ListCtrl.SetItemText(Index,HongQiu+1,Temp);
		}

		CString LanQiu;
		LanQiu.Format("%d",(*DataList)[Index].m_LanQiuChaZhi);
		m_ListCtrl.SetItemText(Index,7,LanQiu);
	}*/
}
