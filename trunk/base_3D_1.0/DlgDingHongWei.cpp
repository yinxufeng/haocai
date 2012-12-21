// DlgDingHongWei.cpp : 实现文件
//

#include "stdafx.h"
#include "ShuangSeQiu.h"
#include "DlgDingHongWei.h"
#include "FormulaCenter.h"

// CDlgDingHongWei 对话框

IMPLEMENT_DYNAMIC(CDlgDingHongWei, CDialog)

CDlgDingHongWei::CDlgDingHongWei(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDingHongWei::IDD, pParent)
{
		m_IsInitData = false;
}

CDlgDingHongWei::~CDlgDingHongWei()
{
}

void CDlgDingHongWei::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CDlgDingHongWei, CDialog)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

















// 生成的消息映射函数
BOOL CDlgDingHongWei::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitListHeader();
	this->CenterWindow();
	return true;
}


//初始化列表头
void CDlgDingHongWei::InitListHeader()
{
	CRect Rect;
	//初始化应用程序列表控件
	int AllCount = 12;
	m_ListCtrl.GetWindowRect(&Rect);
	int nWidth = Rect.Width()/(AllCount+2);

	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;

	m_ListCtrl.InsertColumn(0,_TEXT("期号"),    LVCFMT_CENTER,	3*nWidth);
	m_ListCtrl.SetColumStyle(0,Style);
	
	//CString Array[9]={"定红尾1","定红尾2","定红尾3","定红尾4","定红尾5","定红尾6","内外比值","五期以内个数","五期以外个数"};
	for(int Index = 1; Index < 12; Index++)
	{
		CString Text;
		//Text=Array[Index-1];
		Text.Format("定红V%d",Index);
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



//获取颜色值
COLORREF CDlgDingHongWei::GetColor(int Data)
{
	switch(Data)
	{
	case 0:
		return RGB(112,48,160);
	case 1:
		return RGB(255,0,0);
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


void CDlgDingHongWei::OnShowWindow(BOOL bShow, UINT nStatus)
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

		vector<sShuangSeQiu>*DataList =CDataManageCenter::GetInstance()->GetDataList();
		vector<sFormulaInfo>FormulaList=CFormulaCenter::GetInstance()->GetFormulaInfoByType(FORMULA_DING_HONG_WEI);
		m_ListCtrl.InsertItem(0,"");
	
		for(int Index =1; Index < DataList->size(); Index++)
		{
		
			m_ListCtrl.InsertItem(Index,"");
			int ListIndex=0;
			int ListIndex2=0;
			if(Index < DataList->size())
				m_ListCtrl.SetItemText(Index,ListIndex,(*DataList)[Index].ToString());
			else
				m_ListCtrl.SetItemText(Index,ListIndex,"下期预测");

			ListIndex++;
			ListIndex2++;

			int TempArray[10];
			memset(TempArray,0,sizeof(int)*10);

			for(int i = 0; i < FormulaList.size(); i++)
			{
				int Data=atoi(FormulaList[i].m_DataList[Index-1].m_Data.GetBuffer());
				FormulaList[i].m_DataList[Index-1].m_Data.ReleaseBuffer();
				m_ListCtrl.SetItemText(Index,ListIndex,FormulaList[i].m_DataList[Index-1].m_Data);
				ListIndex++;
				if(Data >=0 && Data < 10 && FormulaList[i].m_DataList[Index-1].m_IsTrue)
					TempArray[Data]++;

			}

			sItemStyle Style;
			Style.m_ItemType = TEXT_TYPE;
			Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);
			Style.m_DrawData.m_TextData.m_TextFont = NULL;
			Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;

			for(int i = 0; i < FormulaList.size(); i++)
			{
				if(FormulaList[i].m_DataList[Index-1].m_IsTrue)
				{
					int Data=atoi(FormulaList[i].m_DataList[Index].m_Data.GetBuffer());
					FormulaList[i].m_DataList[Index].m_Data.ReleaseBuffer();
					Style.m_DrawData.m_TextData.m_BGColor = GetColor(TempArray[Data]);
					m_ListCtrl.SetItemSpecialStyle(Index,ListIndex2,Style);
					ListIndex2++;
				}
				
			}
		}

	}
}

void CDlgDingHongWei::OnClose()
{
	ShowWindow(SW_HIDE);
}
