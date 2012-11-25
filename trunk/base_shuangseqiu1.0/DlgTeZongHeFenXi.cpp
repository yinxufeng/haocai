// DlgTeZongHeFenXi.cpp : 实现文件
//

#include "stdafx.h"
#include "ShuangSeQiu.h"
#include "DlgTeZongHeFenXi.h"
#include "FormulaCenter.h"

// CDlgTeZongHeFenXi 对话框

IMPLEMENT_DYNAMIC(CDlgTeZongHeFenXi, CDialog)

CDlgTeZongHeFenXi::CDlgTeZongHeFenXi(CWnd* pParent /*=NULL*/)
: CDialog(CDlgTeZongHeFenXi::IDD, pParent)
{
	m_IsInitData=false;
}

CDlgTeZongHeFenXi::~CDlgTeZongHeFenXi()
{
}

void CDlgTeZongHeFenXi::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CDlgTeZongHeFenXi, CDialog)
	ON_WM_CLOSE()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()





// 生成的消息映射函数
BOOL CDlgTeZongHeFenXi::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitListHeader();
	this->CenterWindow();
	return true;
}

void CDlgTeZongHeFenXi::OnClose()
{
	ShowWindow(SW_HIDE);
}

void CDlgTeZongHeFenXi::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	if(!m_IsInitData)
	{

		int OffsetCount = 1;
		bool IsLast=false;
		m_IsInitData = true;

		vector<sShuangSeQiu>*DataList =CDataManageCenter::GetInstance()->GetDataList();

		
		for(int Index =0; Index <= DataList->size(); Index++)
		{
			m_ListCtrl.InsertItem(Index,_T(""));
			
			if(Index < DataList->size())
				m_ListCtrl.SetItemText(Index,0,(*DataList)[Index].m_QiShu);
			else
				m_ListCtrl.SetItemText(Index,0,"下期预测");

			sItemStyle Style;
			Style.m_ItemType = TEXT_TYPE;
			Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);
			Style.m_DrawData.m_TextData.m_TextFont = NULL;
			Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;

			map<int,vector<int>> TempMapList;
			int DataArray[33][33]={0};
			for(int i=0; i < 33; i++)
			{
				for(int j = 0 ; j < (int)Index; j++)
				{
					bool IsWant=false;
					for(int k = 0; k < 6; k++)
					{
						if((*DataList)[j].m_HongQiu[k] == i+1)
							IsWant=true;
					}
					
					if(!IsWant)
						continue;

					int Max=0;
					for(int k = 0; k < 6; k++)
					{
						int TempData = (*DataList)[j].m_HongQiu[k]-1;
						if(TempData != -1)
							DataArray[i][TempData]++;
					}

				}
			}

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

			for(int i = 0; i < 33; i++)
			{
				int TempData = DataArray[i][i];
				TempMapList[TempData].push_back(i+1);
			}
		
			
			map<int,vector<int>>::iterator it=TempMapList.begin();
			int Start = it->first;
			int LemitData=16;
			int LemitDataCount=0;
			int LemitCount=0;

			for(it; it != TempMapList.end(); it++)
			{
				int Count=it->first-Start+1;
				int OutCount=0;
				for(int i=0; i < it->second.size(); i++)
				{
					if(Index < DataList->size())
					{
						if(CDataManageCenter::IsHongQiuInData((*DataList)[Index],it->second[i]))
							OutCount++;
					}
					else
						OutCount=0;
				}

				int DataCount=it->second.size();
				if(Count >= 16)
				{
					LemitDataCount+=OutCount;
					OutCount=LemitDataCount;
					DataCount+=LemitCount;
					LemitCount=DataCount;
				}
				CString Str;
				Str.Format("%02d:%02d",DataCount,OutCount);
				m_ListCtrl.SetItemText(Index,Count,Str);
				Style.m_DrawData.m_TextData.m_BGColor = GetColor(OutCount);
				m_ListCtrl.SetItemSpecialStyle(Index,Count,Style);
			}
		}
	}
}



//初始化列表头
void CDlgTeZongHeFenXi::InitListHeader()
{
	CRect Rect;
	//初始化应用程序列表控件
	m_ListCtrl.GetWindowRect(&Rect);
	int nWidth = Rect.Width()/18;

	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_LEFT |DT_WORDBREAK|DT_EDITCONTROL|DT_EDITCONTROL|DT_CENTER;;

	m_ListCtrl.InsertColumn(0,_TEXT("期号"),    LVCFMT_CENTER,	2*nWidth);
	m_ListCtrl.SetColumStyle(0,Style);

	int QingCount=16;

	for(int Index = 1; Index <= QingCount; Index++)
	{
		CString Text;
		Text.Format("遗漏%2d层",Index);
		m_ListCtrl.SetColumStyle(Index,Style);
		m_ListCtrl.InsertColumn(Index,Text,    LVCFMT_CENTER,	nWidth);
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

//获取颜色值
COLORREF CDlgTeZongHeFenXi::GetColor(int Data)
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