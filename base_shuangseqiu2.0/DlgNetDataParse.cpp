// DlgNetDataParse.cpp : 实现文件
//

#include "stdafx.h"
#include "ShuangSeQiu.h"
#include "DlgNetDataParse.h"


// CDlgNetDataParse 对话框

IMPLEMENT_DYNAMIC(CDlgNetDataParse, CDialog)

CDlgNetDataParse::CDlgNetDataParse(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNetDataParse::IDD, pParent)
{
	m_IsInitData=false;
}

CDlgNetDataParse::~CDlgNetDataParse()
{
}

void CDlgNetDataParse::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CDlgNetDataParse, CDialog)
	ON_BN_CLICKED(IDC_ZHONGCAI_HONG_BTN, &CDlgNetDataParse::OnBnClickedZhongcaiHongBtn)
	ON_BN_CLICKED(IDC_ZHONGCAILAN_BTN, &CDlgNetDataParse::OnBnClickedZhongcailanBtn)
	ON_BN_CLICKED(IDC_AOKE360_BTN, &CDlgNetDataParse::OnBnClickedAoke360Btn)
	ON_BN_CLICKED(IDC_WANGYI_BTN, &CDlgNetDataParse::OnBnClickedWangyiBtn)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
END_MESSAGE_MAP()



//初始化列表头
void CDlgNetDataParse::InitListHeader()
{
	CRect Rect;
	//初始化应用程序列表控件
	int PAGE_COUNT=36;

	m_ListCtrl.GetWindowRect(&Rect);
	int nWidth = Rect.Width()/(PAGE_COUNT);

	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;

	m_ListCtrl.InsertColumn(0,_TEXT("期数"),    LVCFMT_CENTER,	3*nWidth);
	m_ListCtrl.SetColumStyle(0,Style);

	for(int Index = 1; Index <= 34; Index++)
	{
		CString Str;
		Str.Format("%02d",Index);
		m_ListCtrl.InsertColumn(Index,Str,    LVCFMT_CENTER,	nWidth);
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

void CDlgNetDataParse::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	if(!m_IsInitData)
	{
		m_IsInitData = true;

		m_ListCtrl.DeleteAllItems();
		OnBnClickedZhongcaiHongBtn();
	
	}
			
}

// 生成的消息映射函数
BOOL CDlgNetDataParse::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitListHeader();

	CenterWindow();
	return true;
}

void CDlgNetDataParse::OnClose()
{
	ShowWindow(SW_HIDE);
}


//中彩红球分析
void CDlgNetDataParse::OnBnClickedZhongcaiHongBtn()
{
	m_ListCtrl.DeleteAllItems();

	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;
	Style.m_DrawData.m_TextData.m_IsFillBG = true;
	

	vector<sZhongCaiDataInfo>* DataList=CDataManageCenter::GetInstance()->GetZhongCaiDataInfo();
	int InsetIndex=0;
	for(int Index=0; Index < DataList->size(); Index++)
	{
		if((*DataList)[Index].m_Type == TYPE_ZHONGCAI_HONG)
		{
			int ListIndex=0;
			m_ListCtrl.InsertItem(InsetIndex,_T(""));
			m_ListCtrl.SetItemText(InsetIndex,ListIndex,(*DataList)[Index].m_QiShu);
			ListIndex++;
			for(int i=0; i < (*DataList)[Index].m_DataList.size(); i++)
			{
			
				CString Text;
				Text.Format("%d",(*DataList)[Index].m_DataList[i].m_DataCount);
				m_ListCtrl.SetItemText(InsetIndex,ListIndex,Text);
				sShuangSeQiu Data;
				bool IsDefualt=CDataManageCenter::GetInstance()->GetShuangSeQiuData((*DataList)[Index].m_QiShu,Data);
				if(IsDefualt)
				{
					IsDefualt =CDataManageCenter::IsHongQiuInData(Data,(*DataList)[Index].m_DataList[i].m_Data);
				}

			
				Style.m_DrawData.m_TextData.m_BGColor=GetColor((*DataList)[Index].m_DataList[i].m_DataCount,IsDefualt);
				m_ListCtrl.SetItemSpecialStyle(InsetIndex,ListIndex,Style);
				ListIndex++;
			}

			InsetIndex++;
		}
	}
}

//中彩篮球分析
void CDlgNetDataParse::OnBnClickedZhongcailanBtn()
{
	m_ListCtrl.DeleteAllItems();

	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;
	Style.m_DrawData.m_TextData.m_IsFillBG = true;
	

	vector<sZhongCaiDataInfo>* DataList=CDataManageCenter::GetInstance()->GetZhongCaiDataInfo();
	int InsetIndex=0;
	for(int Index=0; Index < DataList->size(); Index++)
	{
		if((*DataList)[Index].m_Type == TYPE_ZHONGCAI_LAN)
		{
			int ListIndex=0;
			m_ListCtrl.InsertItem(InsetIndex,_T(""));
			m_ListCtrl.SetItemText(InsetIndex,ListIndex,(*DataList)[Index].m_QiShu);
			ListIndex++;
			for(int i=0; i < (*DataList)[Index].m_DataList.size(); i++)
			{
			
				CString Text;
				Text.Format("%d",(*DataList)[Index].m_DataList[i].m_DataCount);
				m_ListCtrl.SetItemText(InsetIndex,ListIndex,Text);
				sShuangSeQiu Data;
				bool IsDefualt=CDataManageCenter::GetInstance()->GetShuangSeQiuData((*DataList)[Index].m_QiShu,Data);
				if(IsDefualt)
				{
					IsDefualt =CDataManageCenter::IsLanQiuInData(Data,(*DataList)[Index].m_DataList[i].m_Data);
				}

			
				Style.m_DrawData.m_TextData.m_BGColor=GetColor((*DataList)[Index].m_DataList[i].m_DataCount,IsDefualt);
				m_ListCtrl.SetItemSpecialStyle(InsetIndex,ListIndex,Style);
				ListIndex++;
			}

			InsetIndex++;
		}
	}
}

//澳客360分析
void CDlgNetDataParse::OnBnClickedAoke360Btn()
{
	
}

//网易数据分析
void CDlgNetDataParse::OnBnClickedWangyiBtn()
{
	
}

//获取颜色值
COLORREF CDlgNetDataParse::GetColor(int Data,bool IsDefault)
{
	COLORREF Yelow=RGB(255,192,0);
	COLORREF ZiSe=RGB(112,48,160);
	COLORREF Write=RGB(255,255,255);
	COLORREF Red=RGB(255,0,0);

	if(IsDefault)
		return Red;

	if(Data < 5)
	{
		return ZiSe;
	}

	if(Data >= 5 && Data < 10)
	{
		return  RGB(205,250,213);
	}

	
	if(Data >= 10)
		return Yelow;

}