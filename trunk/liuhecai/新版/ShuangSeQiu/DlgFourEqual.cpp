// DlgFourEqual.cpp : 实现文件
//

#include "stdafx.h"
#include "ShuangSeQiu.h"
#include "DlgFourEqual.h"


// CDlgFourEqual 对话框

IMPLEMENT_DYNAMIC(CDlgFourEqual, CDialog)

CDlgFourEqual::CDlgFourEqual(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFourEqual::IDD, pParent)
{
	m_IsInitData = false;
}

CDlgFourEqual::~CDlgFourEqual()
{
}

void CDlgFourEqual::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CDlgFourEqual, CDialog)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgFourEqual 消息处理程序
// 生成的消息映射函数
BOOL CDlgFourEqual::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitListHeader();
	return true;
}

void CDlgFourEqual::InitListHeader()
{
	CRect Rect;
	//初始化应用程序列表控件
	m_ListCtrl.GetWindowRect(&Rect);
	int nWidth = Rect.Width()/9;
	m_ListCtrl.InsertColumn(0,_TEXT("期数"),    LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(1,_TEXT("平码1"),	LVCFMT_CENTER,	nWidth); 
	m_ListCtrl.InsertColumn(2,_TEXT("平码2"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(3,_TEXT("平码3"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(4,_TEXT("平码4"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(5,_TEXT("平码5"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(6,_TEXT("平码6"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(7,_TEXT("平码之和"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(8,_TEXT("特码"),	LVCFMT_CENTER,	nWidth);

	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(222,0,0);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;
	m_ListCtrl.SetColumStyle(0,Style);
	m_ListCtrl.SetColumStyle(1,Style);
	m_ListCtrl.SetColumStyle(2,Style);
	m_ListCtrl.SetColumStyle(3,Style);
	m_ListCtrl.SetColumStyle(4,Style);
	m_ListCtrl.SetColumStyle(5,Style);
	m_ListCtrl.SetColumStyle(6,Style);
	m_ListCtrl.SetColumStyle(7,Style);
	Style.m_DrawData.m_TextData.m_TextColor=RGB(120,195,230);
	m_ListCtrl.SetColumStyle(8,Style);
	m_ListCtrl.SetRowHeight(30);

	sItemBkData ItemBkData;
	ItemBkData.m_BkFillMode = MODE_FILL_RGB;
	ItemBkData.m_HeightColor = RGB(222,22,100);
	ItemBkData.m_HeightFillMode = MODE_FILL_RGB;
	ItemBkData.m_HeightColor = RGB(100,100,100);
	ItemBkData.m_BkColor = RGB(222,222,222);

	m_ListCtrl.SetItemBkData(ItemBkData);
	
}
void CDlgFourEqual::OnClose()
{
	ShowWindow(SW_HIDE);
}

void CDlgFourEqual::OnShowWindow(BOOL bShow, UINT nStatus)
{
	if(!m_IsInitData)
	{
		map<CString,sEqualShuangSeQiu> Temp;
		Temp=CDataManageCenter::GetInstance()->GetFourDataEqualList();

		map<CString,sEqualShuangSeQiu>::iterator it=Temp.begin();
		if(it == Temp.end())
			return;

		sItemStyle Style;
		Style.m_ItemType = TEXT_TYPE;
		Style.m_DrawData.m_TextData.m_TextColor=RGB(22,22,33);
		Style.m_DrawData.m_TextData.m_TextFont = NULL;
		Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;

		
		int RowCount=0;
		for(; it != Temp.end();it++)
		{
			vector<sShuangSeQiu>* DataList=&it->second.m_ShuangSeQiuList;
		
			int Index=0;
			for(; Index < (int)DataList->size(); Index++)
			{
				m_ListCtrl.InsertItem(RowCount+Index,"");
				m_ListCtrl.SetItemText(RowCount+Index,0,(*DataList)[Index].m_QiShu);
				for(int HongQiu=0; HongQiu < 6; HongQiu++)
				{
					CString Temp;
					Temp.Format("%d",(*DataList)[Index].m_HongQiu[HongQiu]);
					m_ListCtrl.SetItemText(RowCount+Index,HongQiu+1,Temp);

					for(int j=0; j < (int)it->second.m_EqualData.size(); j++)
					{
						if(it->second.m_EqualData[j] == (*DataList)[Index].m_HongQiu[HongQiu])
						{
							m_ListCtrl.SetItemSpecialStyle(RowCount+Index,HongQiu+1,Style);
							break;
						}
					}
				}

				
				CString HongQiuSum;
				HongQiuSum.Format("%d",(*DataList)[Index].m_HongQiuSum);
				m_ListCtrl.SetItemText(RowCount+Index,7,HongQiuSum);

				CString LanQiu;
				LanQiu.Format("%d",(*DataList)[Index].m_LanQiu);
				m_ListCtrl.SetItemText(RowCount+Index,8,LanQiu);
			}

			m_ListCtrl.InsertItem(RowCount+Index,"");
			RowCount+=Index+1;
		
		}
		
		
		m_IsInitData=true;
	}
}
