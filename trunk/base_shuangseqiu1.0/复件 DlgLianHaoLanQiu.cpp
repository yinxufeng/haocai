// DlgLianHaoLanQiu.cpp : 实现文件
//

#include "stdafx.h"
#include "ShuangSeQiu.h"
#include "DlgLianHaoLanQiu.h"


// CDlgLianHaoLanQiu 对话框


IMPLEMENT_DYNAMIC(CDlgLianHaoLanQiu, CDialog)

CDlgLianHaoLanQiu::CDlgLianHaoLanQiu(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLianHaoLanQiu::IDD, pParent)
{
	m_IsInitData = false;
}

CDlgLianHaoLanQiu::~CDlgLianHaoLanQiu()
{
}

void CDlgLianHaoLanQiu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CDlgLianHaoLanQiu, CDialog)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_SEARCH_BTN, &CDlgLianHaoLanQiu::OnBnClickedSearchBtn)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CDlgLianHaoLanQiu 消息处理程序

//初始化列表头
void CDlgLianHaoLanQiu::InitListHeader()
{
	CRect Rect;
	//初始化应用程序列表控件
	m_ListCtrl.GetWindowRect(&Rect);
	int nWidth = Rect.Width()/10;
	m_ListCtrl.InsertColumn(0,_TEXT("期数"),    LVCFMT_CENTER,	2*nWidth);
	m_ListCtrl.InsertColumn(1,_TEXT("均值"),	LVCFMT_CENTER,	2*nWidth);
	m_ListCtrl.InsertColumn(2,_TEXT("杀红"),	LVCFMT_CENTER,	6*nWidth);
/*	m_ListCtrl.InsertColumn(2,_TEXT("杀红1"),	LVCFMT_CENTER,	nWidth); 
	m_ListCtrl.InsertColumn(3,_TEXT("杀红2"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(4,_TEXT("杀红3"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(5,_TEXT("杀红4"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(6,_TEXT("杀红5"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(7,_TEXT("杀红6"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(8,_TEXT("杀红7"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(9,_TEXT("杀红8"),	LVCFMT_CENTER,	nWidth);
	*/
}

void CDlgLianHaoLanQiu::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	CDialog::OnShowWindow(bShow, nStatus);
	if(!m_IsInitData)
	{
		m_ListCtrl.DeleteAllItems();
		m_ListCtrl.InsertItem(0,"");
		vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
		int Sum[6];
		memset(Sum,0,sizeof(int)*6);

		for(int Index = 1; Index < (int)DataList->size()+1; Index++)
		{
			m_ListCtrl.InsertItem(Index,"");
			if(Index == DataList->size())
			{
				m_ListCtrl.SetItemText(Index,0,"预测");
			}
			else
			{
				CString Str;
				Str.Format("%s ",(*DataList)[Index].m_QiShu);
				for(int i =0; i < 6; i++)
				{
					CString Temp;
					Temp.Format("%02d ",(*DataList)[Index].m_HongQiu[i]);
					Str+=Temp;
				}

				CString TempLan;
				TempLan.Format("+%02d",(*DataList)[Index].m_LanQiu);
				Str+=TempLan;
				m_ListCtrl.SetItemText(Index,0,Str);

			}

			CString JunZhi;

			for(int i = 0; i < 6; i++)
			{
				Sum[i]+=(*DataList)[Index-1].m_HongQiu[i];
				CString Temp;
				Temp.Format("%02d ",Sum[i]/Index);
				JunZhi+=Temp;
			}

			m_ListCtrl.SetItemText(Index,1,JunZhi);

			CString ShaHongList;
			int TempData = (*DataList)[Index-1].m_HongQiu[5]-(*DataList)[Index-1].m_HongQiu[0];
			CString ShaHong;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();

			TempData = (*DataList)[Index-1].m_HongQiu[2]-(*DataList)[Index-1].m_HongQiu[1];
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();

			TempData = (*DataList)[Index-1].m_HongQiu[5]-(*DataList)[Index-1].m_HongQiu[1];
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();

			TempData = (*DataList)[Index-1].m_HongQiu[0]*4-2;
			if(TempData > 33)
				TempData = TempData%33;

			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);

			ShaHongList += ShaHong;
			ShaHong.Empty();

			TempData = ((*DataList)[Index-1].m_HongQiu[0]+(*DataList)[Index-1].m_LanQiu)*3;
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();


            TempData = (*DataList)[Index-1].m_LanQiu;
			if(TempData /2 == 0)
				TempData=TempData*2+2;
			else
				TempData=TempData*5+2;

			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();

		

		

		
		

			TempData = (*DataList)[Index-1].m_HongQiu[0]+9;
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);

			ShaHongList += ShaHong;
			ShaHong.Empty();

			TempData = (*DataList)[Index-1].m_HongQiu[1]+5;
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();

			TempData = (*DataList)[Index-1].m_HongQiu[2]+4;
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();

			TempData = (*DataList)[Index-1].m_HongQiu[2]+7;
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();

			TempData = (*DataList)[Index-1].m_HongQiu[5]+4;
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			
			TempData = (*DataList)[Index-1].m_HongQiu[4]-(*DataList)[Index-1].m_HongQiu[3]+(*DataList)[Index-1].m_LanQiu+1;
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();

			TempData = (*DataList)[Index-1].m_LanQiu+(*DataList)[Index-1].m_HongQiu[0];
			if(Index >= 2)
			{
				if((*DataList)[Index-1].m_LanQiu == ((*DataList)[Index-2].m_LanQiu))
					TempData-=1;
			}
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();

			TempData = abs((*DataList)[Index-1].m_LanQiu-(*DataList)[Index-1].m_HongQiu[5]);
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();

			TempData = abs((*DataList)[Index-1].m_LanQiu*(*DataList)[Index-1].m_HongQiu[0]);
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();

			TempData = (*DataList)[Index-1].m_LanQiu+7;
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();

			TempData = (*DataList)[Index-1].m_LanQiu+9;
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();

			TempData = (*DataList)[Index-1].m_LanQiu*5+2;
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();

			TempData = (*DataList)[Index-1].m_HongQiu[2]+(*DataList)[Index-1].m_HongQiu[5]/33 + 14;
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();

			TempData = ((*DataList)[Index-1].m_HongQiu[0]+(*DataList)[Index-1].m_HongQiu[2]+(*DataList)[Index-1].m_HongQiu[4])/2;
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsHongQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();



			m_ListCtrl.SetItemText(Index,2,ShaHongList);


		}
	}
}

// 生成的消息映射函数
BOOL CDlgLianHaoLanQiu::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitListHeader();
	return true;
}

void CDlgLianHaoLanQiu::OnClose()
{
	ShowWindow(SW_HIDE);
}

void CDlgLianHaoLanQiu::OnBnClickedSearchBtn()
{
	
}

BOOL CDlgLianHaoLanQiu::OnEraseBkgnd(CDC* pDC)
{
	/*CRect Rect;
	GetClientRect(Rect);
	pDC->FillSolidRect(Rect,RGB(222,222,222));

	vector<sShuangSeQiu>* pData=CDataManageCenter::GetInstance()->GetDataList();
	
	if(pData->size() == 0)
		return true;


	int Len = pData->size();
	Rect.top +=5;
	Rect.bottom-=5;
	int Height = Rect.Height()/Len;
	int Width  = Rect.Width()/33;


	for(int Index = 0; Index < Len; Index++)
	{
		for(int i = 0; i < 33; i++)
		{
			CRect Temp = Rect;
		    Temp.left = Rect.left + i*Width;
			Temp.right = Temp.left + Width;
			Temp.top = Rect.top + Index*Height;
			Temp.bottom = Temp.top + Height;

			bool IsWant = false;
			for(int j = 0; j < 6; j++)
			{
				if( (*pData)[Index].m_HongQiu[j] == i+1)
				{
					IsWant = true;
					break;
				}

			}

			if(IsWant)
				pDC->FillSolidRect(Temp,RGB(255,0,0));
			else
			{
				if( i % 2 == 0)
					pDC->FillSolidRect(Temp,RGB(0,0,0));
				else
					pDC->FillSolidRect(Temp,RGB(25,25,255));

			}
		}
	}

	return true;
	*/
	return CDialog::OnEraseBkgnd(pDC);
}
