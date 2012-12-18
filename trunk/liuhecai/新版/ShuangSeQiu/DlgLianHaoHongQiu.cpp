// DlgLianHaoHongQiu.cpp : 实现文件
//

#include "stdafx.h"
#include "ShuangSeQiu.h"
#include "DlgLianHaoHongQiu.h"


// CDlgLianHaoHongQiu 对话框

IMPLEMENT_DYNAMIC(CDlgLianHaoHongQiu, CDialog)

CDlgLianHaoHongQiu::CDlgLianHaoHongQiu(CWnd* pParent /*=NULL*/)
: CDialog(CDlgLianHaoHongQiu::IDD, pParent)
{
	m_IsInitData = false;
}

CDlgLianHaoHongQiu::~CDlgLianHaoHongQiu()
{
}

void CDlgLianHaoHongQiu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CDlgLianHaoHongQiu, CDialog)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()

END_MESSAGE_MAP()


// CDlgLianHaoHongQiu 消息处理程序

//初始化列表头
void CDlgLianHaoHongQiu::InitListHeader()
{
	const int PAGE_COUNT= 10;

	CRect Rect;
	//初始化应用程序列表控件
	m_ListCtrl.GetWindowRect(&Rect);
	int nWidth = Rect.Width()/(PAGE_COUNT+2);

	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;

	m_ListCtrl.InsertColumn(0,_TEXT("期数"),    LVCFMT_CENTER,	2*nWidth);
	m_ListCtrl.SetColumStyle(0,Style);

	CString Array[PAGE_COUNT]={"尾值走势","合值走势","路数走势","大小走势","奇偶走势","横七走势","纵七走势"};
	for(int Index = 1; Index <PAGE_COUNT; Index++)
	{
		CString Str;
		Str=Array[Index-1];
		m_ListCtrl.InsertColumn(Index,Str,    LVCFMT_CENTER,	nWidth);
		m_ListCtrl.SetColumStyle(Index,Style);
	}

	m_ListCtrl.InsertColumn(PAGE_COUNT+1,"统计",    LVCFMT_CENTER,	nWidth);
	m_ListCtrl.SetColumStyle(PAGE_COUNT+1,Style);
	m_ListCtrl.InsertColumn(PAGE_COUNT+2,"对错",    LVCFMT_CENTER,	nWidth);
	m_ListCtrl.SetColumStyle(PAGE_COUNT+2,Style);

	
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

void CDlgLianHaoHongQiu::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	if(!m_IsInitData)
	{
		m_IsInitData = true;

		m_ListCtrl.DeleteAllItems();
	
		sItemStyle Style;
		Style.m_ItemType = TEXT_TYPE;
		Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);
		Style.m_DrawData.m_TextData.m_TextFont = NULL;
		Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;
		Style.m_DrawData.m_TextData.m_IsFillBG=true;
		Style.m_DrawData.m_TextData.m_BGColor =RGB(205,250,213);
		//Style.m_DrawData.m_TextData.m_BGColor = RGB(248,183,173);

		vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
		vector<sShuangSeQiu>* QiuShun=CDataManageCenter::GetInstance()->GetDataListByChuHao();
		for(int i=0; i < DataList->size(); i++)
		{
			int TempData=0;
			int TempIndex=0;
			CString TempStr;
			m_ListCtrl.InsertItem(i,"");
			TempStr.Format("%s %02d",(*DataList)[i].m_QiShu,(*DataList)[i].m_LanQiu);
			m_ListCtrl.SetItemText(i,TempIndex,TempStr);
			TempStr.Empty();
			TempIndex++;

			//尾值
			TempData=(*DataList)[i].m_LanQiu%10;
			TempStr.Format("%d",TempData);
			m_ListCtrl.SetItemText(i,TempIndex,TempStr);
			if(TempData < 5)
				Style.m_DrawData.m_TextData.m_BGColor =RGB(205,250,213);
			else
				Style.m_DrawData.m_TextData.m_BGColor = RGB(248,183,173);
				
		
			m_ListCtrl.SetItemSpecialStyle(i,TempIndex+1,Style);
			TempStr.Empty();
			TempIndex++;
		

			//合值
			TempData=(*DataList)[i].m_LanQiu%10+(*DataList)[i].m_LanQiu/10;
			TempData=TempData%10;
			TempStr.Format("%d",TempData);
			m_ListCtrl.SetItemText(i,TempIndex,TempStr);
			if(TempData < 5)
				Style.m_DrawData.m_TextData.m_BGColor =RGB(205,250,213);
			else
				Style.m_DrawData.m_TextData.m_BGColor = RGB(248,183,173);

			m_ListCtrl.SetItemSpecialStyle(i,TempIndex+1,Style);
			TempStr.Empty();
			TempIndex++;

			//路数
			TempData=(*DataList)[i].m_LanQiu%3;
			TempData=TempData%10;
			TempStr.Format("%d",TempData);
			m_ListCtrl.SetItemText(i,TempIndex,TempStr);
			TempStr.Empty();
			TempIndex++;

			//大小
			TempData=(*DataList)[i].m_LanQiu;
			if(TempData > QIU_COUNT/2)
			{
				TempStr="大";
				Style.m_DrawData.m_TextData.m_BGColor =RGB(205,250,213);
			}
			else
			{
				TempStr="小";
			    Style.m_DrawData.m_TextData.m_BGColor = RGB(248,183,173);
			}
			m_ListCtrl.SetItemText(i,TempIndex+1,TempStr);
			TempStr.Empty();
			TempIndex++;

			//奇偶
			TempData=(*DataList)[i].m_LanQiu%2;
			if(TempData > 0)
			{
				TempStr="奇";
				Style.m_DrawData.m_TextData.m_BGColor =RGB(205,250,213);
			}
			else
			{
				TempStr="偶";
				Style.m_DrawData.m_TextData.m_BGColor =RGB(205,250,213);
			}
			m_ListCtrl.SetItemText(i,TempIndex+1,TempStr);
			m_ListCtrl.SetItemText(i,TempIndex,TempStr);
			TempStr.Empty();
			TempIndex++;


			//横七
			TempData=(*DataList)[i].m_LanQiu/7;
			TempStr.Format("%d",TempData);
			m_ListCtrl.SetItemText(i,TempIndex,TempStr);
			TempStr.Empty();
			TempIndex++;

			//纵七
			TempData=(*DataList)[i].m_LanQiu%7;
			TempStr.Format("%d",TempData);
			m_ListCtrl.SetItemText(i,TempIndex,TempStr);
			TempStr.Empty();
			TempIndex++;



		}

	}
}


	//	int LanQiuSum = 0;

	//	for(int Index = 1; Index < (int)DataList->size()+1; Index++)
	//	{
	//		int InsertItemPos=0;
	//		m_ListCtrl.InsertItem(Index,"");
	//		if(Index == DataList->size())
	//		{
	//			m_ListCtrl.SetItemText(Index,InsertItemPos,"预测");
	//		}
	//		else
	//		{
	//			CString LanQiu;
	//			LanQiu.Format("%d",(*DataList)[Index].m_LanQiu);
	//			m_ListCtrl.SetItemText(Index,InsertItemPos,LanQiu);
	//		}

	//		InsertItemPos++;
	//		bool IsAddS = false;
	//		int TempLanQiu = (*DataList)[Index-1].m_LanQiu;
	//		int Temp = (TempLanQiu%10)*2;
	//		if(Temp >= 10)
	//			Temp = Temp%10;

	//		if(Index >=2)
	//		{
	//			int TempLanCha = abs((*DataList)[Index-1].m_LanQiu%10 - (*DataList)[Index-2].m_LanQiu%10);
	//			int TempLanHe  = abs((*DataList)[Index-1].m_LanQiu%10 + (*DataList)[Index-2].m_LanQiu%10);
	//			int TempLanHeArray[7];
	//			int TempLanChaArray[7];

	//			for(int i = 0; i < 7; i++)
	//			{
	//				if(i < 3)
	//				{
	//					TempLanHeArray[i]=TempLanHe-(i+1);
	//					if(TempLanHeArray[i] > 9)
	//						TempLanHeArray[i] =TempLanHeArray[i]-10;
	//					if(TempLanHeArray[i] < 0)
	//						TempLanHeArray[i] =TempLanHeArray[i]+10;


	//					TempLanChaArray[i]=TempLanCha-(i+1);
	//					if(TempLanChaArray[i] > 9)
	//						TempLanChaArray[i] = TempLanChaArray[i]-10;
	//					if(TempLanChaArray[i] < 0)
	//						TempLanChaArray[i] = TempLanChaArray[i]+10;

	//				}
	//				else if(i ==3)
	//				{
	//					TempLanHeArray[i]=TempLanHe;
	//					TempLanChaArray[i] = TempLanCha;
	//					if(TempLanHeArray[i] < 0)
	//						TempLanHeArray[i] =TempLanHeArray[i]+10;
	//					if(TempLanHeArray[i] > 9)
	//						TempLanHeArray[i] =TempLanHeArray[i]-10;

	//					if(TempLanChaArray[i] < 0)
	//						TempLanChaArray[i] = TempLanChaArray[i]+10;
	//					if(TempLanChaArray[i] > 9)
	//						TempLanChaArray[i] = TempLanChaArray[i]-10;
	//				}
	//				else
	//				{
	//					TempLanHeArray[i]=TempLanHe+i-3;
	//					if(TempLanHeArray[i] < 0)
	//						TempLanHeArray[i] =TempLanHeArray[i]+10;
	//					if(TempLanHeArray[i] > 9)
	//						TempLanHeArray[i] =TempLanHeArray[i]-10;

	//					TempLanChaArray[i]=TempLanCha+i-3;
	//					if(TempLanChaArray[i] < 0)
	//						TempLanChaArray[i] = TempLanChaArray[i]+10;
	//					if(TempLanChaArray[i] > 9)
	//						TempLanChaArray[i] = TempLanChaArray[i]-10;
	//				}


	//			}


	//			int Array[100];
	//			memset(Array,0,sizeof(int)*10);

	//			bool IsSu=false;

	//			for(int i = 0; i < 7; i++)
	//			{
	//				int Data = TempLanChaArray[i];
	//				int Data2= TempLanHeArray[i];
	//				Array[Data]++;
	//				Array[Data2]++;
	//			}

	//			CString LanStr2;
	//			for(int j =0; j < 10; j++)
	//			{
	//				if(Array[j] == 1)
	//				{
	//					CString TempStr;
	//					TempStr.Format("%02d",j);
	//					LanStr2+=TempStr;

	//					if(!IsSu)
	//					{
	//						if(Index == DataList->size())
	//						{
	//							IsSu=true;
	//							continue;
	//						}

	//						if(CDataManageCenter::IsLanQiuInData((*DataList)[Index],j,true))
	//							IsSu = true;
	//					}
	//				}
	//			}

	//			LanStr2+="V";

	//			AddFlag(LanStr2,IsSu);
	//			m_ListCtrl.SetItemText(Index,1,LanStr2);
	//		}

	//		/*CString LanQiu10;
	//		Temp = (*DataList)[Index-1].m_LanQiu;
	//		switch(Temp)
	//		{
	//		case 1:
	//			LanQiu10="06 08 09 11 12 13 14 15 16";
	//			break;
	//		case 2:
	//			LanQiu10="03 05 07 11 12 13 14 15 16";
	//			break;
	//		case 3:
	//			LanQiu10="02 06 08 09 10 13 14 15 16";
	//			break;
	//		case 4:
	//			LanQiu10="01 05 06 07 09 10 13 14 15 16";
	//			break;

	//		case 5:
	//			LanQiu10="02 06 08 09 10 13 14 15 16";
	//			break;

	//		case 6:
	//			LanQiu10="01 03 07 09 10 11 12 15 16";
	//			break;

	//		case 7:
	//			LanQiu10="02 04 06 09 10 11 12 13 14";
	//			break;

	//		case 8:
	//			LanQiu10="01 02 05 06 07 08 09 13 15";
	//			break;
	//		case 9:
	//			LanQiu10="03 04 05 06 07 08 13 14 16";
	//			break;
	//		case 10:
	//			LanQiu10="03 04 05 06 07 08 11 13 15";
	//			break;
	//		case 11:
	//			LanQiu10="01 02 05 06 07 08 10 14 16";
	//			break;
	//		case 12:
	//			LanQiu10="01 02 05 06 07 08 09 13 15";
	//			break;
	//		case 13:
	//			LanQiu10="01 02 03 04 07 08 10 12 16";
	//			break;
	//		case 14:
	//			LanQiu10="01 02 03 04 07 08 09 11 15";
	//			break;
	//		case 15:
	//			LanQiu10="01 02 03 04 05 06 10 12 14";
	//			break;
	//		case 16:
	//			LanQiu10="01 02 03 04 05 06 09 11 13";
	//			break;

	//		}


	//		if(Index == DataList->size())
	//		{
	//			IsAddS = true;
	//		}
	//		else
	//		{
	//			CString TempStr;
	//			TempStr.Format("%02d",(*DataList)[Index].m_LanQiu);
	//			if(LanQiu10.Find(TempStr) != -1)
	//				IsAddS = true;
	//			else
	//				IsAddS = false;
	//		}
	//		AddFlag(LanQiu10,IsAddS);
	//		m_ListCtrl.SetItemText(Index,2,LanQiu10);*/

	//		CString TempStr;

	//		/*int TempData = (*DataList)[Index-1].m_HongQiu[5]-(*DataList)[Index-1].m_HongQiu[0]-(*DataList)[Index-1].m_HongQiu[2];
	//		int TempData1 = (*DataList)[Index-1].m_HongQiu[5]-(*DataList)[Index-1].m_HongQiu[0]+(*DataList)[Index-1].m_HongQiu[2];
	//		if(TempData1 > 49)
	//			TempData1=49;*/
	//		int TempData=0;
	//		int TempData1=0;

	//		if(Index > 2)
	//		{
	//			LanQiuSum+=(*DataList)[Index-1].m_LanQiu;
	//			TempData = LanQiuSum/(Index-1) - 5;
	//			TempData1= LanQiuSum/(Index-1) +5;
	//		}

	//		
	//		if(Index == DataList->size())
	//		{
	//			IsAddS = true;
	//		}else
	//		{
	//			if((*DataList)[Index].m_LanQiu < TempData || (*DataList)[Index].m_LanQiu > TempData1)
	//				IsAddS = true;
	//			else
	//				IsAddS = false;
	//		}
	//		
	//		TempStr.Format("[%02d %02d]",TempData,TempData1);
	//		AddFlag(TempStr,IsAddS);
	//		m_ListCtrl.SetItemText(Index,2,TempStr);
	//		TempStr.Empty();

	//	

	//	//	Temp =(*QiuShun)[Index-1].m_HongQiu[2]%10 + (*QiuShun)[Index-1].m_LanQiu%10;
	//		Temp = (*DataList)[Index-1].m_HongQiu[3]-(*DataList)[Index-1].m_HongQiu[1];
	//		Temp=Temp%10;
	//		CString FormatStr;
	//
	//		FormatStr.Format("杀%02dV",Temp);
	//		if(Index == DataList->size())
	//		{
	//			IsAddS = true;
	//		}
	//		else
	//		{
	//			CString TempStr;
	//			TempStr.Format("%02d",(*DataList)[Index].m_LanQiu%10);
	//			if(FormatStr.Find(TempStr) != -1)
	//				IsAddS = false;
	//			else
	//				IsAddS = true;
	//		}
	//		AddFlag(FormatStr,IsAddS);
	//		m_ListCtrl.SetItemText(Index,3,FormatStr);

	//	
	//		CString LanQiu9;
	//		Temp=(*DataList)[Index-1].m_HongQiu[5]%10+1;
	//		CString TempLanQiu9;
	//		TempLanQiu9.Format("%02d",Temp);
	//		LanQiu9 += TempLanQiu9;
	//		TempLanQiu9.Empty();
	//		if(Index == DataList->size())
	//		{
	//			IsAddS = true;
	//		}
	//		else
	//			IsAddS=!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,true);
	//		AddFlag(LanQiu9,IsAddS);


	//		Temp=(*DataList)[Index-1].m_HongQiu[0]+3;
	//		if(Temp> QIU_COUNT)
	//			Temp -=QIU_COUNT;

	//		TempLanQiu9.Format("%02d",Temp);
	//		LanQiu9 += TempLanQiu9;
	//		TempLanQiu9.Empty();
	//		if(Index == DataList->size())
	//		{
	//			IsAddS = true;
	//		}
	//		else
	//			IsAddS=!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,true);
	//		AddFlag(LanQiu9,IsAddS);


	//		Temp=(*DataList)[Index-1].m_HongQiu[0]*2;
	//		if(Temp> QIU_COUNT)
	//			Temp -=QIU_COUNT;
	//		TempLanQiu9.Format("%02d",Temp);
	//		LanQiu9 += TempLanQiu9;
	//		TempLanQiu9.Empty();
	//		if(Index == DataList->size())
	//		{
	//			IsAddS = true;
	//		}
	//		else
	//			IsAddS=!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,true);
	//		AddFlag(LanQiu9,IsAddS);


	//		Temp=CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1])*2-6;
	//		if(Temp> QIU_COUNT)
	//			Temp -=QIU_COUNT;
	//		TempLanQiu9.Format("%02d",Temp);
	//		LanQiu9 += TempLanQiu9;
	//		TempLanQiu9.Empty();
	//		if(Index == DataList->size())
	//		{
	//			IsAddS = true;
	//		}
	//		else
	//			IsAddS=!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,true);
	//		AddFlag(LanQiu9,IsAddS);

	//		if(Index >= 3)
	//		{
	//			Temp=(*DataList)[Index-1].m_LanQiu%10+(*DataList)[Index-2].m_LanQiu%10+(*DataList)[Index-3].m_LanQiu%10;
	//			if(Temp> QIU_COUNT)
	//				Temp -=QIU_COUNT;
	//			TempLanQiu9.Format("%02d",Temp);
	//			LanQiu9 += TempLanQiu9;
	//			TempLanQiu9.Empty();
	//			if(Index == DataList->size())
	//			{
	//				IsAddS = true;
	//			}
	//			else
	//				IsAddS=!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,true);
	//			AddFlag(LanQiu9,IsAddS);

	//		}


	//		if( Index>=2)
	//		{
	//			Temp=((*DataList)[Index-1].m_LanQiu%10)*((*DataList)[Index-2].m_LanQiu%10)+5;
	//			if(Temp > QIU_COUNT)
	//				Temp-=QIU_COUNT;
	//			TempLanQiu9.Format("%02d",Temp);
	//			LanQiu9 += TempLanQiu9;
	//			TempLanQiu9.Empty();
	//			if(Index == DataList->size())
	//			{
	//				IsAddS = true;
	//			}
	//			else
	//				IsAddS=!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,true);
	//			AddFlag(LanQiu9,IsAddS);

	//		}

	//		Temp=(*DataList)[Index-1].m_HongQiu[3]%10 + (*DataList)[Index-1].m_LanQiu%10;
	//		if(Temp> QIU_COUNT)
	//			Temp -=QIU_COUNT;
	//		TempLanQiu9.Format("%02d",Temp);
	//		LanQiu9 += TempLanQiu9;
	//		TempLanQiu9.Empty();
	//		if(Index == DataList->size())
	//		{
	//			IsAddS = true;
	//		}
	//		else
	//			IsAddS=!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,true);
	//		AddFlag(LanQiu9,IsAddS);
	//		m_ListCtrl.SetItemText(Index,4,LanQiu9);


	//		if( Index >= 2)
	//		{
	//			Temp = 	abs((*DataList)[Index-1].m_LanQiu - (*DataList)[Index-2].m_LanQiu);
	//			Temp = Temp%10;
	//			CString LanQiu2;
	//			LanQiu2.Format("杀%02dV",Temp);
	//			if(Index == DataList->size())
	//			{
	//				IsAddS = true;
	//			}
	//			else
	//				IsAddS=!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,true);
	//			AddFlag(LanQiu2,IsAddS);
	//			m_ListCtrl.SetItemText(Index,5,LanQiu2);
	//		}

	//		if( Index >= 2)
	//		{
	//			Temp = 	(*DataList)[Index-1].m_LanQiu + (*DataList)[Index-2].m_LanQiu;
	//			if(Temp > QIU_COUNT)
	//				Temp-=QIU_COUNT;

	//			CString LanQiu3;
	//			LanQiu3.Format("杀%02d",Temp);
	//			if(Index == DataList->size())
	//			{
	//				IsAddS = true;
	//			}
	//			else
	//				IsAddS=!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,false);
	//			AddFlag(LanQiu3,IsAddS);
	//			m_ListCtrl.SetItemText(Index,6,LanQiu3);
	//		}


	//		CString LanQiu4;
	//		int Temp1=(*DataList)[Index-1].m_LanQiu+2;
	//		int Temp2=(*DataList)[Index-1].m_LanQiu-2;
	//		if(Temp1 < 0)
	//			Temp1 +=QIU_COUNT;
	//		if(Temp2 < 0)
	//			Temp2 +=QIU_COUNT;

	//		if(Temp1 > QIU_COUNT)
	//			Temp1 -=QIU_COUNT;
	//		if(Temp2 > QIU_COUNT)
	//			Temp2 -=QIU_COUNT;
	//		LanQiu4.Format("杀%02d %02d",Temp1,Temp2);
	//		if(Index == DataList->size())
	//		{
	//			IsAddS = true;
	//		}
	//		else
	//			IsAddS=CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp1,false);

	//		bool IsAddS2=false;
	//		if(Index == DataList->size())
	//		{
	//			IsAddS2 = true;
	//		}
	//		else
	//			IsAddS2=CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp2,false);

	//		if(IsAddS || IsAddS2)
	//			IsAddS=false;
	//		else
	//			IsAddS=true;
	//		AddFlag(LanQiu4,IsAddS);
	//		m_ListCtrl.SetItemText(Index,7,LanQiu4);

	//		CString LanQiu5;
	//		Temp =(*DataList)[Index-1].m_LanQiu +(*DataList)[Index-1].m_HongQiu[0];
	//		if(Temp > QIU_COUNT)
	//			Temp -=QIU_COUNT;
	//		LanQiu5.Format("杀%02d",Temp);
	//		if(Index == DataList->size())
	//		{
	//			IsAddS = true;
	//		}
	//		else
	//			IsAddS=!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,false);
	//		AddFlag(LanQiu5,IsAddS);
	//		m_ListCtrl.SetItemText(Index,8,LanQiu5);

	//		CString LanQiu6;
	//		int QiShu = atoi((*DataList)[Index-1].m_QiShu.GetBuffer())%100+(*DataList)[Index-1].m_LanQiu;
	//		QiShu=QiShu%10;
	//		LanQiu6.Format("杀%02d",QiShu);
	//		if(Index == DataList->size())
	//		{
	//			IsAddS = true;
	//		}
	//		else
	//			IsAddS=!CDataManageCenter::IsLanQiuInData((*DataList)[Index],QiShu,false);
	//		AddFlag(LanQiu6,IsAddS);
	//		m_ListCtrl.SetItemText(Index,9,LanQiu6);

	//		CString LanQiu7;
	//		Temp = (*DataList)[Index-1].m_HongQiu[1]%10+1;
	//		LanQiu7.Format("杀%02dV",Temp);
	//		if(Index == DataList->size())
	//		{
	//			IsAddS = true;
	//		}
	//		else
	//			IsAddS=!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,true);
	//		AddFlag(LanQiu7,IsAddS);
	//		m_ListCtrl.SetItemText(Index,10,LanQiu7);



	//		Temp =(*QiuShun)[Index-1].m_HongQiu[5]%10 + (*QiuShun)[Index-1].m_LanQiu%10;
	//		Temp=Temp%10;
	//		CString LanQiu8;
	//		LanQiu8.Format("杀%02dV",Temp);
	//		if(Index == DataList->size())
	//		{
	//			IsAddS = true;
	//		}
	//		else
	//		{
	//			CString TempStr;
	//			TempStr.Format("%02d",(*DataList)[Index].m_LanQiu%10);
	//			if(LanQiu8.Find(TempStr) != -1)
	//				IsAddS = false;
	//			else
	//				IsAddS = true;
	//		}
	//		AddFlag(LanQiu8,IsAddS);
	//		m_ListCtrl.SetItemText(Index,11,LanQiu8);


	//		CString LanQiu1;
	//		Temp = (*DataList)[Index-1].m_LanQiu%10*2;
	//		Temp =Temp%10;
	//		LanQiu1.Format("杀%02dV",Temp);
	//		if(Index == DataList->size())
	//		{
	//			IsAddS = true;
	//		}
	//		else
	//			IsAddS=!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,true);
	//		AddFlag(LanQiu1,IsAddS);
	//		m_ListCtrl.SetItemText(Index,12,LanQiu1);

	//	}

	//	if(!DataList->empty())
	//		m_IsInitData = true;
	//}

//}

// 生成的消息映射函数
BOOL CDlgLianHaoHongQiu::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitListHeader();
	return true;
}

void CDlgLianHaoHongQiu::OnClose()
{
	ShowWindow(SW_HIDE);
}

void CDlgLianHaoHongQiu::OnBnClickedSearchBtn()
{
	CString Text;
	GetDlgItem(IDC_EDIT1)->GetWindowText(Text);
	DWORD Data=::atoi(Text.GetBuffer());
	m_ListCtrl.DeleteAllItems();
	vector<sShuangSeQiu>* DataList = NULL;
	vector<sShuangSeQiu> Temp;
	if(Data == 0)
	{
		DataList=CDataManageCenter::GetInstance()->GetLianHaoHongQiu();
	}
	else
	{
		Temp=CDataManageCenter::GetInstance()->SearchLianHaoHongQiu(Data);
		DataList=&Temp;
	}

	for(int Index = 0; Index < (int)DataList->size(); Index++)
	{
		m_ListCtrl.InsertItem(Index,"");
		m_ListCtrl.SetItemText(Index,0,(*DataList)[Index].m_QiShu);
		for(int HongQiu=0; HongQiu < 6; HongQiu++)
		{
			CString Temp;
			Temp.Format("%d",(*DataList)[Index].m_HongQiu[HongQiu]);
			m_ListCtrl.SetItemText(Index,HongQiu+1,Temp);
		}

		CString HongQiuSum;
		HongQiuSum.Format("%d",(*DataList)[Index].m_HongQiuSum);
		m_ListCtrl.SetItemText(Index,7,HongQiuSum);

		CString LanQiu;
		LanQiu.Format("%d",(*DataList)[Index].m_LanQiu);
		m_ListCtrl.SetItemText(Index,8,LanQiu);
	}
}

void CDlgLianHaoHongQiu::AddFlag(CString& Str,bool IsTrue)
{
	if(IsTrue)
		Str+="S";
	else
		Str+="F";
}