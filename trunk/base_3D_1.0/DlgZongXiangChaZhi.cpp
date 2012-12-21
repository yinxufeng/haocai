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

const int ARRAY_COUNT=18;

// CDlgZongXiangChaZhi 对话框

IMPLEMENT_DYNAMIC(CDlgZongXiangChaZhi, CDialog)

CDlgZongXiangChaZhi::CDlgZongXiangChaZhi(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgZongXiangChaZhi::IDD, pParent)
{
	m_IsInitData = false;
	 m_IsLiShan=true;
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

	ON_BN_CLICKED(IDC_BUTTON1, &CDlgZongXiangChaZhi::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CDlgZongXiangChaZhi::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CDlgZongXiangChaZhi::OnBnClickedButton3)
END_MESSAGE_MAP()


// CDlgZongXiangChaZhi 消息处理程序
//初始化列表头
void CDlgZongXiangChaZhi::InitListHeader()
{
	
	CRect Rect;
	//初始化应用程序列表控件
	m_ListCtrl.GetWindowRect(&Rect);
	int FormulCount = ARRAY_COUNT;
	int nWidth = Rect.Width()/(FormulCount+2);

	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(222,0,0);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;

	m_ListCtrl.InsertColumn(0,_TEXT("期号"),    LVCFMT_CENTER,	2*nWidth);
	m_ListCtrl.SetColumStyle(0,Style);

	for(int Index = 1; Index < FormulCount+1; Index++)
	{
		CString Text;
		Text.Format("%02d区",Index);
		m_ListCtrl.InsertColumn(Index,Text,    LVCFMT_CENTER,	nWidth);
		m_ListCtrl.SetColumStyle(Index,Style);
	}

	m_ListCtrl.SetRowHeight(30);
	m_ListCtrl.ShowHeader(true);

	sItemBkData ItemBkData;
	ItemBkData.m_BkFillMode = MODE_FILL_RGB;
	ItemBkData.m_HeightColor = RGB(222,22,100);
	ItemBkData.m_HeightFillMode = MODE_FILL_RGB;
	ItemBkData.m_HeightColor = RGB(100,100,100);
	ItemBkData.m_BkColor = RGB(222,222,222);
	m_ListCtrl.SetItemBkData(ItemBkData);

}

//填充区域数据
void CDlgZongXiangChaZhi::FillQuData(sShuangSeQiu Data,int* DataArray,int DataCount)
{
	
	CString QuArray[18];
	QuArray[0]="01 02 03 04 05 06";
	QuArray[1]="07 08 09 10 11 12";
	QuArray[2]="13 14 15 16 17 18";
	QuArray[3]="19 20 21 22 23 24";
	QuArray[4]="25 26 27 28 29 30";
	QuArray[5]="31 32 33";

	QuArray[6] ="01 07 13 19 25 31";
	QuArray[7] ="02 08 14 20 26 32";
	QuArray[8] ="03 09 15 21 27 33";
	QuArray[9] ="04 10 16 22 28";
	QuArray[10]="05 11 17 23 29";
	QuArray[11]="06 12 18 24 30";

	QuArray[12]="01 08 15 22 29";
	QuArray[13]="06 11 16 21 26 31";

	QuArray[14]="07 13 14 19 20 25";
	QuArray[15]="02 03 04 05 09 10";
	QuArray[16]="12 17 18 23 24 30";
	QuArray[17]="27 28 32 33";



	memset(DataArray,0,sizeof(int)*DataCount);
	for(int Index=0; Index < QIU_XUN; Index++)
	{
		CString Temp;
		Temp.Format("%02d",Data.m_HongQiu[Index]);
		for(int i=0; i < ARRAY_COUNT; i++)
		{
			if(QuArray[i].Find(Temp) != -1)
			{
				DataArray[i]++;
			}
		}
	}
}

//填充区域数据
void CDlgZongXiangChaZhi::FillQuData(sShuangSeQiu Data,map<int,CString> MapData,int* DataArray,int DataCount)
{
	memset(DataArray,0,sizeof(int)*DataCount);
	for(int Index=0; Index < QIU_XUN; Index++)
	{
		CString Temp;
		Temp.Format("%02d",Data.m_HongQiu[Index]);
		map<int,CString>::iterator it=MapData.begin();
		for(; it != MapData.end(); it++)
		{
			if(it->second.Find(Temp) != -1)
			{
				int Count=it->first;
				DataArray[Count]++;
			}
		}
	}
}


//获取区号数据
CString CDlgZongXiangChaZhi::GetQuDataStr(int QuHao)
{
	if( m_IsLiShan)
	{
		CString QuArray[18];
		QuArray[0]="01 02 03 04 05 06";
		QuArray[1]="07 08 09 10 11 12";
		QuArray[2]="13 14 15 16 17 18";
		QuArray[3]="19 20 21 22 23 24";
		QuArray[4]="25 26 27 28 29 30";
		QuArray[5]="31 32 33";

		QuArray[6] ="01 07 13 19 25 31";
		QuArray[7] ="02 08 14 20 26 32";
		QuArray[8] ="03 09 15 21 27 33";
		QuArray[9] ="04 10 16 22 28";
		QuArray[10]="05 11 17 23 29";
		QuArray[11]="06 12 18 24 30";

		QuArray[12]="01 08 15 22 29";
		QuArray[13]="06 11 16 21 26 31";

		QuArray[14]="07 13 14 19 20 25";
		QuArray[15]="02 03 04 05 09 10";
		QuArray[16]="12 17 18 23 24 30";
		QuArray[17]="27 28 32 33";

		return QuArray[QuHao];
	}
	else
	{

		vector<map<int,CString>>* DanZuList=CDataManageCenter::GetInstance()->GetDanZuDataList();
	    int DataSize = DanZuList->size();
		map<int,CString>::iterator it=(*DanZuList)[DataSize-1].begin();

		for(it ; it != (*DanZuList)[DataSize-1].end(); it++)
		{
			if(it->first == QuHao)
				return it->second;
		}
	}

	return "";
}

void CDlgZongXiangChaZhi::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	if(!m_IsInitData)
	{
		m_IsInitData = true;
		OnBnClickedButton4();
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


	//		//上期开球顺序h2+上上期大小红球H3-2
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


	//		//上期开球顺序h2+上上期大小红球H2-2
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

void CDlgZongXiangChaZhi::OnBnClickedButton1()
{
	CString Text;
	GetDlgItem(IDC_EDIT1)->GetWindowText(Text);
	if(Text.IsEmpty())
	{
		GetDlgItem(IDC_EDIT2)->SetWindowText("区号为空");
		return;
	}

	int Data=atoi(Text.GetBuffer());
	Text.ReleaseBuffer();
	if(Data < 1 || Data > 18)
	{
		GetDlgItem(IDC_EDIT2)->SetWindowText("区号暂不支持");
		return;
	}


	CString StrData=GetQuDataStr(Data-1);
	GetDlgItem(IDC_EDIT2)->SetWindowText(StrData);
}

void CDlgZongXiangChaZhi::OnBnClickedButton4()
{
	 m_IsLiShan=true;
	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_IsFillBG=true;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;

	m_ListCtrl.DeleteAllItems();
	
	vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
	
	int DataSize = DataList->size();
	for(int Index = 0; Index < DataSize; Index++)
	{
		m_ListCtrl.InsertItem(Index,_T(""));	
		m_ListCtrl.SetItemText(Index,0,(*DataList)[Index].m_QiShu);
		int DataArray[ARRAY_COUNT]={0};
		FillQuData((*DataList)[Index],DataArray,ARRAY_COUNT);
		for(int i=0; i < ARRAY_COUNT; i++)
		{
			CString Text;
			if(DataArray[i])
			{
				Text.Format("%02d",DataArray[i]);
				m_ListCtrl.SetItemText(Index,i+1,Text);
				Style.m_DrawData.m_TextData.m_BGColor = RGB(205,250,213);
				m_ListCtrl.SetItemSpecialStyle(Index,i+1,Style);
			}
			else
			{
				m_ListCtrl.SetItemText(Index,i+1,Text);
				Style.m_DrawData.m_TextData.m_BGColor =RGB(248,183,173);
				m_ListCtrl.SetItemSpecialStyle(Index,i+1,Style);
			}
		}
	}
}

void CDlgZongXiangChaZhi::OnBnClickedButton3()
{
	 m_IsLiShan=false;
	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_IsFillBG=true;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;

	m_ListCtrl.DeleteAllItems();

	vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
	vector<map<int,CString>>* DanZuList=CDataManageCenter::GetInstance()->GetDanZuDataList();
	int DataSize = DataList->size();
	for(int Index = 0; Index < DataSize; Index++)
	{
		m_ListCtrl.InsertItem(Index,_T(""));	
		m_ListCtrl.SetItemText(Index,0,(*DataList)[Index].m_QiShu);
		int DataArray[ARRAY_COUNT]={0};
		FillQuData((*DataList)[Index],(*DanZuList)[Index],DataArray,ARRAY_COUNT);
		for(int i=0; i < ARRAY_COUNT; i++)
		{
			CString Text;
			if(DataArray[i])
			{
				Text.Format("%02d",DataArray[i]);
				m_ListCtrl.SetItemText(Index,i+1,Text);
				Style.m_DrawData.m_TextData.m_BGColor = RGB(205,250,213);
				m_ListCtrl.SetItemSpecialStyle(Index,i+1,Style);
			}
			else
			{
				m_ListCtrl.SetItemText(Index,i+1,Text);
				Style.m_DrawData.m_TextData.m_BGColor =RGB(248,183,173);
				m_ListCtrl.SetItemSpecialStyle(Index,i+1,Style);
			}
		}
	}
}
