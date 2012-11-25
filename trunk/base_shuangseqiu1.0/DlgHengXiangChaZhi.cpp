// DlgHengXiangChaZhi.cpp : 实现文件
//

#include "stdafx.h"
#include "ShuangSeQiu.h"
#include "DlgHengXiangChaZhi.h"
#include <vector>
using std::vector;


extern CString GetAppCurrentPath3();
// CDlgHengXiangChaZhi 对话框

IMPLEMENT_DYNAMIC(CDlgHengXiangChaZhi, CDialog)

CDlgHengXiangChaZhi::CDlgHengXiangChaZhi(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHengXiangChaZhi::IDD, pParent)
{
	m_IsInitData = false;

}

CDlgHengXiangChaZhi::~CDlgHengXiangChaZhi()
{
}

void CDlgHengXiangChaZhi::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CDlgHengXiangChaZhi, CDialog)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_SEARCH_BTN, &CDlgHengXiangChaZhi::OnBnClickedSearchBtn)
END_MESSAGE_MAP()

//初始化列表头
void CDlgHengXiangChaZhi::InitListHeader()
{
		CRect Rect;
	//初始化应用程序列表控件
	int AllCount = 10;
	m_ListCtrl.GetWindowRect(&Rect);
	int nWidth = Rect.Width()/(AllCount+2);

	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;

	m_ListCtrl.InsertColumn(0,_TEXT("期号"),    LVCFMT_CENTER,	3*nWidth);
	m_ListCtrl.SetColumStyle(0,Style);
	
	CString Array[9]={"遗漏0层","遗漏1层","遗漏2层","遗漏3层","遗漏4层","遗漏5层以上","内外比值","五期以内个数","五期以外个数"};
	for(int Index = 1; Index < 10; Index++)
	{
		CString Text;
		Text=Array[Index-1];
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


//获取路数
int CDlgHengXiangChaZhi::GetLuShu(int Data)
{
	/*
0路3：03 12 21 30
0路6：06 15 24 33
0路9：09 18 27

1路1：01 10 19 28
1路4：04 13 22 31
1路7：07 16 25

2路2：02 11 20 29
2路5：05 14 23 32
2路8：08 17 26
*/

	int Lu0[11]={3,12,21,30,06,15,24,33,9,18,27};
	int Lu1[11]={1,10,19,28,4,13,22,31,7,16,25};
	int Lu2[11]={2,11,20,29,5,14,23,32,8,17,26};

	bool IsWant=false;
	for(int Index = 0; Index < 11; Index++)
	{
		if(Lu0[Index] == Data)
		{
			IsWant = true;
			break;
		}
	}

	if(IsWant)
		return 0;

	for(int Index = 0; Index < 11; Index++)
	{
		if(Lu1[Index] == Data)
		{
			IsWant = true;
			break;
		}
	}

	if(IsWant)
		return 1;

	for(int Index = 0; Index < 11; Index++)
	{
		if(Lu2[Index] == Data)
		{
			IsWant = true;
			break;
		}
	}

	if(IsWant)
		return 2;

	return 0;
}

void CDlgHengXiangChaZhi::OnShowWindow(BOOL bShow, UINT nStatus)
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

		m_ListCtrl.InsertItem(0,"");
		m_ListCtrl.InsertItem(1,"");
		m_ListCtrl.InsertItem(2,"");
		m_ListCtrl.InsertItem(3,"");

		CString FilePath2 = GetAppCurrentPath3()+_T("\\wuqiyilou.txt");
		HANDLE FileHandle2=CreateFile(FilePath2,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

		vector<sShuangSeQiu>*DataList =CDataManageCenter::GetInstance()->GetDataList();
		for(int Index =4; Index < DataList->size(); Index++)
		{
			
			m_ListCtrl.InsertItem(Index,"");
			int Data[QIU_COUNT]={0};
			int DataArray[QIU_COUNT][5];
			int YiLouDataArray[5][QIU_COUNT];
			memset(DataArray,0,QIU_COUNT*5*sizeof(int));
			memset(YiLouDataArray,0,QIU_COUNT*5*sizeof(int));

			for(int i=4; i >= 0; i--)
			{
				for(int j=0; j < 6; j++)
				{
					int TempData =(*DataList)[Index-i].m_HongQiu[j]-1;
					bool IsWant=true;
					for(int k=i-1; k >= 0; k--)
					{
						for(int f=0; f < 6; f++)
						{
							int TempData2 =(*DataList)[Index-k].m_HongQiu[f]-1;
							if(TempData2 == TempData)
							{
								IsWant=false;
								break;
							}
						}

						if(!IsWant)
							break;
					}

					if(IsWant)
						YiLouDataArray[i][TempData]=1;

					Data[TempData]++;
				}
			}
			
			int ListIndex=0;
			CString ShowText=Index+1 >= DataList->size() ? "下期预测":(*DataList)[Index+1].m_QiShu+" ";
			if(Index+1 < DataList->size())
			{
				for(int g=0; g < 6; g++)
				{
					CString Temp;
					Temp.Format("%02d ",(*DataList)[Index+1].m_HongQiu[g]);
					ShowText+=Temp;
				}

				CString Temp;
				Temp.Format("+%02d",(*DataList)[Index+1].m_LanQiu);
				ShowText+=Temp;

			}
			m_ListCtrl.SetItemText(Index,ListIndex,ShowText);

			ListIndex++;

			int WuQiCount=0;
			int WuQiWaiCount=0;
			int WuQiShuCount=0;
			int WuQiWaiShuCount=0;

			if(Index == 134)
				WuQiCount=0;


			CString WriteTextStr="下期：\r\n";
			if(Index+1 < DataList->size())
			{
				WriteTextStr=(*DataList)[Index+1].m_QiShu;

			}

			for(int k=0; k <= 4 ; k++)
			{
				int TempCount=0;
				int AllCount=0;
				CString TempText;
				TempText.Format("%02d层:   ",k);
				CString OutText;

				for(int j=0; j < QIU_COUNT; j++)
				{
					if(YiLouDataArray[k][j])
					{
						CString Temp;
						Temp.Format("%02d ",j+1);
						TempText+=Temp;

						bool Want=Index+1 >= DataList->size() ? false:CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],j+1);
						if(Want)
						{
							TempCount++;
							WuQiCount++;
							OutText+=Temp;
							
							
						}
						AllCount++;
						WuQiShuCount++;
					}
				}

				CString Text;
				Text.Format("%d:%d",AllCount,TempCount);
				
				m_ListCtrl.SetItemText(Index,ListIndex,Text);
				Style.m_DrawData.m_TextData.m_BGColor=GetColor(TempCount);
				m_ListCtrl.SetItemSpecialStyle(Index,ListIndex,Style);
				ListIndex++;

				for(int i=TempText.GetLength(); i < 50; i++)
					TempText+=" ";
				WriteTextStr+=TempText+"==》"+OutText+"\r\n";
			}

			WriteTextStr+="\r\n";
			DWORD WriteBytes=0;
			::WriteFile(FileHandle2,WriteTextStr.GetBuffer(),WriteTextStr.GetLength(),&WriteBytes,0);
			ShowText.Empty();
			ShowText.Format("%d:%d",QIU_COUNT-WuQiShuCount,6-WuQiCount);
			m_ListCtrl.SetItemText(Index,ListIndex,ShowText);
			Style.m_DrawData.m_TextData.m_BGColor=GetColor(6-WuQiCount);
			m_ListCtrl.SetItemSpecialStyle(Index,ListIndex,Style);
			ListIndex++;

			ShowText.Empty();
			ShowText.Format("%d:%d",WuQiCount,6-WuQiCount);
			m_ListCtrl.SetItemText(Index,ListIndex,ShowText);
			Style.m_DrawData.m_TextData.m_BGColor=GetColor(WuQiCount);
			m_ListCtrl.SetItemSpecialStyle(Index,ListIndex,Style);
			ListIndex++;

			ShowText.Empty();
			ShowText.Format("%d",WuQiShuCount);
			m_ListCtrl.SetItemText(Index,ListIndex,ShowText);
			Style.m_DrawData.m_TextData.m_BGColor=GetColor(WuQiShuCount);
			m_ListCtrl.SetItemSpecialStyle(Index,ListIndex,Style);
			ListIndex++;

			ShowText.Empty();
			ShowText.Format("%d",QIU_COUNT-WuQiShuCount);
			m_ListCtrl.SetItemText(Index,ListIndex,ShowText);
			Style.m_DrawData.m_TextData.m_BGColor=GetColor(QIU_COUNT-WuQiShuCount);
			m_ListCtrl.SetItemSpecialStyle(Index,ListIndex,Style);

			ListIndex++;
		}
		

		CloseHandle(FileHandle2);
	}



}

// 生成的消息映射函数
BOOL CDlgHengXiangChaZhi::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitListHeader();
	this->CenterWindow();
	return true;
}

void CDlgHengXiangChaZhi::OnClose()
{
	ShowWindow(SW_HIDE);
}


void CDlgHengXiangChaZhi::OnBnClickedSearchBtn()
{
	
}

CString CDlgHengXiangChaZhi::GetDataStr(int LuShu)
{
	CString RetStr;
	for(int Index=1; Index <= QIU_COUNT; Index++)
	{
		if(Index %3 == LuShu)
		{
			CString Temp;
			Temp.Format("%02d ",Index);
			RetStr+=Temp;
		}
	}

	return RetStr;
}

//获取颜色值
COLORREF CDlgHengXiangChaZhi::GetColor(int Data)
{
	switch(Data)
	{
	case 0:
		return RGB(112,48,160);
	case 1:
		return RGB(255,0,0);
	case 2:
		return RGB(255,255,255);
	case 3:
		return RGB(255,192,0);
	case 4:
		return RGB(128,128,128);
	default:
		return RGB(248,183,173);
	}
}
