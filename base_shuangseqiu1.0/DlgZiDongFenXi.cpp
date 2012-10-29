// DlgZiDongFenXi.cpp : 实现文件
//

#include "stdafx.h"
#include "ShuangSeQiu.h"
#include "DlgZiDongFenXi.h"
#include "FormulaCenter.h"


// CDlgZiDongFenXi 对话框

IMPLEMENT_DYNAMIC(CDlgZiDongFenXi, CDialog)

CDlgZiDongFenXi::CDlgZiDongFenXi(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgZiDongFenXi::IDD, pParent)
{
	m_IsInitData = false;
}

CDlgZiDongFenXi::~CDlgZiDongFenXi()
{
}

void CDlgZiDongFenXi::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CDlgZiDongFenXi, CDialog)
	ON_WM_CLOSE()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_SEARCH_BTN, &CDlgZiDongFenXi::OnBnClickedSearchBtn)
END_MESSAGE_MAP()


// 生成的消息映射函数
BOOL CDlgZiDongFenXi::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitListHeader();
	return true;
}

void CDlgZiDongFenXi::OnClose()
{
	ShowWindow(SW_HIDE);
}

void CDlgZiDongFenXi::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	if(!m_IsInitData)
	{
		m_IsInitData=true;

		vector<sFormulaInfo> InfoList=CFormulaCenter::GetInstance()->GetFormulaInfoByType(FORMULA_SHA_LAN_WEI);
		m_ListCtrl.DeleteAllItems();
		vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
    	int DataSize = DataList->size();


		for(int Index = 0; Index < DataSize; Index++)
		{
			m_ListCtrl.InsertItem(Index,_T(""));	
			int JueShaV[10];
			int WeiV[10];
			memset(JueShaV,0,sizeof(int)*10);
			memset(WeiV,0,sizeof(int)*10);

			for(int i = 0; i < InfoList.size(); i++)
			{
				int ErrorCount=0;
				int TrueCount=0;

				/*if(Index >=8)
				{
					for(int j=Index-1; j > Index-8;j--)
					{
						if( InfoList[i].m_DataList[j].m_IsTrue)
							TrueCount++;
						else
							ErrorCount++;

					}

					if(!ErrorCount)
					{
						int TempV=atoi(InfoList[i].m_DataList[Index].m_Data.GetBuffer());
						JueShaV[TempV]++;
					}

				}*/
			//	int Count=10;

				ErrorCount=0;
				TrueCount=0;

				for(int j=0; j < Index;j++)
				{
					if( InfoList[i].m_DataList[j].m_IsTrue)
						TrueCount++;
					else
						ErrorCount++;

				}

				if(TrueCount+ErrorCount)
				{
					int TempData=(TrueCount*100)/(TrueCount+ErrorCount);
					if(TempData >92 && i <= 9)
					{
						int TempV=atoi(InfoList[i].m_DataList[Index].m_Data.GetBuffer());
						JueShaV[TempV]++;
					}

					if(TempData <90)
					{
						int TempV=atoi(InfoList[i].m_DataList[Index].m_Data.GetBuffer());
						WeiV[TempV]++;
					}

					if(!InfoList[i].m_DataList[Index-1].m_IsTrue)
					{
						int TempV=atoi(InfoList[i].m_DataList[Index].m_Data.GetBuffer());
						JueShaV[TempV]++;
					}
				}
			}

			CString JueShaVStr;
			CString WeiVStr;
			CString ZongHeStr;

			for(int i=0; i < 10; i++)
			{
				if(JueShaV[i]>=3)
				{
					CString Temp;
					Temp.Format("%2d",i);
					 JueShaVStr+=Temp;
				}

			/*	if(WeiV[i])
				{
					CString Temp;
					Temp.Format("%2d",i);
					WeiVStr+=Temp;
					
				}*/

				//if(WeiV[i] && !JueShaV[i]) /*|| !WeiV[i] && JueShaV[i])*/
				if(JueShaV[i]<=2)
				{
					CString Temp;
					Temp.Format("%2d",i);
					ZongHeStr+=Temp;
				}
			}

			CString JieGuo="对";
			CString QiHao;
			if(Index+1 == DataSize)
			{
				QiHao="下期预测";
				
			}
			else
			{
				CString TempData;
				TempData.Format("%2d",(*DataList)[Index+1].m_LanQiu%10);
				CString TempData2;
				TempData2.Format(" %02d",(*DataList)[Index+1].m_LanQiu);
				

				if(ZongHeStr.Find(TempData) == -1)
				{
					JieGuo="错";
					sItemStyle Style;
					Style.m_ItemType = TEXT_TYPE;
					Style.m_DrawData.m_TextData.m_TextColor=RGB(222,0,0);
					Style.m_DrawData.m_TextData.m_TextFont = NULL;
					Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;
					m_ListCtrl.SetItemSpecialStyle(Index,4,Style);

				}

				QiHao=(*DataList)[Index+1].m_QiShu+TempData2;
			}

			

			m_ListCtrl.SetItemText(Index,0,QiHao);	
			m_ListCtrl.SetItemText(Index,1,WeiVStr);
			m_ListCtrl.SetItemText(Index,2,JueShaVStr);
			m_ListCtrl.SetItemText(Index,3,ZongHeStr);
			m_ListCtrl.SetItemText(Index,4,JieGuo);
		}

    
	}

}


//初始化列表头
void CDlgZiDongFenXi::InitListHeader()
{
	CRect Rect;
	//初始化应用程序列表控件
	m_ListCtrl.GetWindowRect(&Rect);
	int nWidth = Rect.Width()/10;

	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(22,22,22);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;

	m_ListCtrl.InsertColumn(0,_TEXT("期号"),    LVCFMT_CENTER,	2*nWidth);
	m_ListCtrl.SetColumStyle(0,Style);

	m_ListCtrl.InsertColumn(1,"围篮球尾",    LVCFMT_CENTER,	3*nWidth);
	m_ListCtrl.InsertColumn(2,"绝杀篮球尾",    LVCFMT_CENTER,3*nWidth);
	m_ListCtrl.InsertColumn(3,"分析结果",    LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(4,"对错",    LVCFMT_CENTER,	nWidth);

	m_ListCtrl.SetColumStyle(1,Style);
	m_ListCtrl.SetColumStyle(2,Style);
	m_ListCtrl.SetColumStyle(3,Style);
	m_ListCtrl.SetColumStyle(4,Style);



	m_ListCtrl.SetRowHeight(30);
	//m_ListCtrl.ShowHeader(false);

	sItemBkData ItemBkData;
	ItemBkData.m_BkFillMode = MODE_FILL_RGB;
	ItemBkData.m_HeightColor = RGB(222,22,100);
	ItemBkData.m_HeightFillMode = MODE_FILL_RGB;
	ItemBkData.m_HeightColor = RGB(100,100,100);
	ItemBkData.m_BkColor = RGB(222,222,222);
	m_ListCtrl.SetItemBkData(ItemBkData);
}
void CDlgZiDongFenXi::OnBnClickedSearchBtn()
{
	// TODO: 在此添加控件通知处理程序代码
}
