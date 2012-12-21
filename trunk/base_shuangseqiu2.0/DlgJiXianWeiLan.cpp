// DlgJiXianWeiLan.cpp : 实现文件
//

#include "stdafx.h"
#include "ShuangSeQiu.h"
#include "DlgJiXianWeiLan.h"


// CDlgJiXianWeiLan 对话框

IMPLEMENT_DYNAMIC(CDlgJiXianWeiLan, CDialog)

CDlgJiXianWeiLan::CDlgJiXianWeiLan(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgJiXianWeiLan::IDD, pParent)
{
	m_IsInitData=false;
}

CDlgJiXianWeiLan::~CDlgJiXianWeiLan()
{
}

void CDlgJiXianWeiLan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST4, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CDlgJiXianWeiLan, CDialog)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


//初始化列表头
void CDlgJiXianWeiLan::InitListHeader()
{
	CRect Rect;
	//初始化应用程序列表控件
	int AllCount = 40;
	m_ListCtrl.GetWindowRect(&Rect);
	int nWidth = Rect.Width()/(AllCount+2);

	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;

	m_ListCtrl.InsertColumn(0,_TEXT("期号"),    LVCFMT_CENTER,	3*nWidth);
	m_ListCtrl.SetColumStyle(0,Style);

	for(int Index = 1; Index < 39; Index++)
	{
		CString Text;
		Text.Format("%02d",Index%17);
		m_ListCtrl.InsertColumn(Index,Text,    LVCFMT_CENTER,	nWidth);
		m_ListCtrl.SetColumStyle(Index,Style);
	}

	m_ListCtrl.SetRowHeight(30);
	sItemBkData ItemBkData;
	ItemBkData.m_BkFillMode = MODE_FILL_RGB;
	ItemBkData.m_HeightColor = RGB(222,22,100);
	ItemBkData.m_HeightFillMode = MODE_FILL_RGB;
	ItemBkData.m_HeightColor = RGB(100,100,100);
	ItemBkData.m_BkColor = RGB(222,222,222);
	m_ListCtrl.SetItemBkData(ItemBkData);
	
}


void CDlgJiXianWeiLan::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	if(!m_IsInitData)
	{
		m_IsInitData=true;
		sItemStyle Style;
		Style.m_ItemType = TEXT_TYPE;
		Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);
		Style.m_DrawData.m_TextData.m_TextFont = NULL;
		Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;

		vector<sShuangSeQiu>*DataList = CDataManageCenter::GetInstance()->GetDataList();
		m_ListCtrl.InsertItem(0,_T(""));
		for(int Index=1; Index < DataList->size(); Index++)
		{
			m_ListCtrl.InsertItem(Index,_T(""));
			int ListIndex=0;
			m_ListCtrl.SetItemText(Index,ListIndex,(*DataList)[Index].ToLanString());
			ListIndex++;

			int SucessIndex1=0;
			int SucessIndex2=0;
	
			for(int i=0; i < 16; i++)
			{
			
				int LanQiu=abs((*DataList)[Index].m_LanQiu-(*DataList)[Index-1].m_LanQiu);
			//	int LanQiu=(*DataList)[Index].m_LanQiu;

				int Temp=(LanQiu+i);
				CString TempStr;
				bool IsTrue=false;
				int TempData=0;

				if(Temp > 16)
					TempData=Temp%16;
				else
					TempData=Temp;

				if(TempData == 0)
					TempData=16;

				TempStr.Format("%02d",TempData);
				m_ListCtrl.SetItemText(Index,ListIndex,TempStr);
				IsTrue=Index+1 < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index+1],TempData,false):false;
				if( IsTrue)
				{
					SucessIndex1=i;
				
				}

				Style.m_DrawData.m_TextData.m_BGColor=GetColor(IsTrue);
				m_ListCtrl.SetItemSpecialStyle(Index,ListIndex,Style);
				TempStr.Empty();
				ListIndex++;
			
			}

			ListIndex++;
			for(int i=0; i < 16; i++)
			{
			
				int LanQiu=abs((*DataList)[Index].m_LanQiu-(*DataList)[Index-1].m_LanQiu);
				//int LanQiu=(*DataList)[Index].m_LanQiu;

				int Temp=LanQiu-i;

				CString TempStr;
				bool IsTrue=false;
				int TempData=0;

				if(Temp < 0)
					TempData=Temp+16;
				else
					TempData=Temp;

				if(TempData == 0)
					TempData=16;

				TempStr.Format("%02d",TempData);
				m_ListCtrl.SetItemText(Index,ListIndex,TempStr);
				IsTrue=Index+1 < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index+1],TempData,false):false;
				if( IsTrue)
				{
					SucessIndex1=i;
				
				}

				Style.m_DrawData.m_TextData.m_BGColor=GetColor(IsTrue);
				m_ListCtrl.SetItemSpecialStyle(Index,ListIndex,Style);
				TempStr.Empty();
				ListIndex++;
			
			}
		}


			//ListIndex++;

			//for(int i=0; i < 16; i++)
			//{
			//	int LanQiu=(*DataList)[Index].m_LanQiu+(*DataList)[Index-1].m_LanQiu;
			//	int Temp=(LanQiu+i);
			//	CString TempStr;
			//	bool IsTrue=false;
			//	int TempData=0;

	
			//	if(Temp > 16)
			//		TempData=Temp%16;
			//	else
			//		TempData=Temp;
			//	if(TempData == 0)
			//		TempData=16;

			//	TempStr.Format("%02d",TempData);
			//	m_ListCtrl.SetItemText(Index,ListIndex,TempStr);
			//	IsTrue=Index+1 < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index+1],TempData,false):false;
			//    if(IsTrue)
			//	{
			//		SucessIndex2=i;
			//		
			//	}
			//	Style.m_DrawData.m_TextData.m_BGColor=GetColor(IsTrue);
			//	m_ListCtrl.SetItemSpecialStyle(Index,ListIndex,Style);
			//	TempStr.Empty();
			//	ListIndex++;
			//	
			//}

	
			//int Offset=abs(SucessIndex2-SucessIndex1);

			//for(int i=0; i < 16; i++)
			//{
			//	int MaxData=SucessIndex1+Offset > 16 ? 16:SucessIndex1+Offset;
			//	int TempOffset=0;
			//	for(int j=SucessIndex1+1; j < MaxData; j++)
			//	{
			//		if(j > 16)
			//			break;


			//		Style.m_DrawData.m_TextData.m_BGColor=YELOW;
			//		TempOffset++;
			//		int TempData=(*DataList)[Index].m_LanQiu+TempOffset;
			//		
			//		if(TempData > 16)
			//		TempData=TempData%16;
			//		bool IsTrue=Index+1 < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index+1],TempData,false):false;
			//		m_ListCtrl.SetItemSpecialStyle(Index,j+1,Style);
			//		if(IsTrue)
			//		{
			//			Style.m_DrawData.m_TextData.m_BGColor=RED;
			//			m_ListCtrl.SetItemSpecialStyle(Index,j,Style);
			//		}
			//		
			//	}

			//	MaxData=SucessIndex2+Offset > 16 ? 16:SucessIndex2+Offset;
			//	TempOffset=0;
			//	for(int j=SucessIndex2+1; j < MaxData; j++)
			//	{
			//		if(j > 16)
			//			break;

			//		
			//		Style.m_DrawData.m_TextData.m_BGColor=YELOW;

			//		
			//		TempOffset++;
			//		int TempData=(*DataList)[Index].m_LanQiu+TempOffset;
			//		TempData=TempData%16;
			//		bool IsTrue=Index+1 < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index+1],TempData,false):false;

			//		if(IsTrue)
			//			Style.m_DrawData.m_TextData.m_BGColor=RED;

			//		m_ListCtrl.SetItemSpecialStyle(Index,18+j,Style);
			//	}


			//
			//	TempOffset=0;
			//	MaxData=SucessIndex1-Offset < 0 ? 1:SucessIndex1-Offset;
			//	for(int j=SucessIndex1; j > MaxData; j--)
			//	{
			//		if(j < 0)
			//			break;

			//		Style.m_DrawData.m_TextData.m_BGColor=YELOW;

			//		TempOffset++;
			//		int TempData=(*DataList)[Index].m_LanQiu-TempOffset;
			//		bool IsTrue=Index+1 < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index+1],TempData,false):false;
			//		m_ListCtrl.SetItemSpecialStyle(Index,j,Style);
			//		if(IsTrue)
			//		{
			//			Style.m_DrawData.m_TextData.m_BGColor=RED;
			//			m_ListCtrl.SetItemSpecialStyle(Index,j,Style);
			//		}
			//	
			//				

			//	
			//	}

				/*TempOffset=0;
		    	MaxData=SucessIndex2-Offset < 0 ? 1:SucessIndex2-Offset;
				for(int j=SucessIndex2-1; j > MaxData; j--)
				{
					if(j < 0)
						break;

					Style.m_DrawData.m_TextData.m_BGColor=YELOW;
					m_ListCtrl.SetItemSpecialStyle(Index,18+j,Style);
					
					TempOffset++;
					int TempData=abs((*DataList)[Index].m_LanQiu-TempOffset);
					TempData=TempData%16;
					bool IsTrue=Index+1 < DataList->size() ? CDataManageCenter::IsLanQiuInData((*DataList)[Index+1],TempData,false):false;
					m_ListCtrl.SetItemSpecialStyle(Index,18+j,Style);
					if(IsTrue)
					{
						Style.m_DrawData.m_TextData.m_BGColor=RED;
						m_ListCtrl.SetItemSpecialStyle(Index,18+j-1,Style);
					}
				}*/

		//	}
    //    }

	}



}

// 生成的消息映射函数
BOOL CDlgJiXianWeiLan::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitListHeader();
	CenterWindow();
	return true;
}

void CDlgJiXianWeiLan::OnClose()
{
	ShowWindow(SW_HIDE);
}

//获取颜色值
COLORREF CDlgJiXianWeiLan::GetColor(int Data)
{
	switch(Data)
	{
	case 0:
		return WRITE;
//return RGB(112,48,160);
	case 1:
		return ZISE;
		//return RGB(255,0,0);
	case 2:
		return RGB(198,198,200);
	case 3:
		return RGB(255,192,0);
	case 4:
		return RGB(128,128,128);
	default:
		return RGB(248,183,173);
	}
}
