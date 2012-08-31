// DlgHengXiangChaZhi.cpp : 实现文件
//

#include "stdafx.h"
#include "ShuangSeQiu.h"
#include "DlgHengXiangChaZhi.h"
#include <vector>
using std::vector;



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
	m_ListCtrl.GetWindowRect(&Rect);
	int nWidth = Rect.Width()/8;
	m_ListCtrl.InsertColumn(0,_TEXT("期数"),    LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(1,_TEXT("绝杀龙头"),	LVCFMT_CENTER,	nWidth); 
	m_ListCtrl.InsertColumn(2,_TEXT("龙头单双"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(3,_TEXT("绝杀凤尾"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(4,_TEXT("绝杀龙头2"),	LVCFMT_CENTER,	nWidth);
	
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

		m_ListCtrl.InsertItem(0,"");
		vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
		for(int Index = 1; Index <= DataList->size(); Index++)
		{
			m_ListCtrl.InsertItem(Index,"");
			
			if(Index !=  DataList->size())
			{
				CString Str;
				Str.Format("%s 龙头=%02d 凤尾=%02d",(*DataList)[Index].m_QiShu,(*DataList)[Index].m_HongQiu[0],(*DataList)[Index].m_HongQiu[5]);
				m_ListCtrl.SetItemText(Index,0,Str);
			}

			int Jio = (*DataList)[Index-1].m_HongQiu[0]+(*DataList)[Index-1].m_HongQiu[1];
			CString StrJio;
			if(Jio%2 == 0)
			{
				StrJio="偶数";
				if(Index != DataList->size())
				{
					if((*DataList)[Index].m_HongQiu[0] %2)
						StrJio+="F";
					else
						StrJio+="S";
				}
				else
					StrJio+="S";
			}
			else
			{
				StrJio="奇数";
				if(Index != DataList->size())
				{
					if((*DataList)[Index].m_HongQiu[0] %2)
						StrJio+="S";
					else
						StrJio+="F";
				}
				else
					StrJio+="S";
			}

			int Temp1=(*DataList)[Index-1].m_HongQiu[0]/10+(*DataList)[Index-1].m_HongQiu[0]%10 +(*DataList)[Index-1].m_HongQiu[1]/10+(*DataList)[Index-1].m_HongQiu[1]%10;
		//	Temp1=Temp1%10;
			int LuShu =GetLuShu(Temp1);
			CString LongTou;
			CString JiaoJi;

			switch(LuShu)
			{
			case 0:
				LongTou = "369V";
			/*	if(Jio%2 != 0)
					JiaoJi ="03 09 15";
				else
					JiaoJi ="06 12";*/
				break;

			case 1:
				LongTou = "147V";
			/*	if(Jio%2 != 0)
					JiaoJi ="01 07 13";
				else
					JiaoJi ="04 10";*/
				break;

			case 2:
				LongTou = "258V";
			/*	if(Jio%2 != 0)
					JiaoJi ="02 08 14";
				else
					JiaoJi ="05 11";*/
				break;
			}

			LongTou="杀"+LongTou;

			if(Index != DataList->size())
			{
				CString TempData;
				TempData.Format("%d",(*DataList)[Index].m_HongQiu[0]%10);
				if(LongTou.Find(TempData) == -1)
					LongTou+="S";
				else
					LongTou+="F";
			}
			else
				LongTou+="S";


			if(Index != DataList->size())
			{
				CString TempData;
				TempData.Format("%02d",(*DataList)[Index].m_HongQiu[0]);
				if(JiaoJi.Find(TempData) != -1)
					JiaoJi+="S";
				else
					JiaoJi+="F";
			}
			else
				JiaoJi+="S";



			m_ListCtrl.SetItemText(Index,1,LongTou);
			m_ListCtrl.SetItemText(Index,2,StrJio);
			m_ListCtrl.SetItemText(Index,3,JiaoJi);

		    //Temp1=(*DataList)[Index-1].m_HongQiu[0]/10+(*DataList)[Index-1].m_HongQiu[0]%10 +(*DataList)[Index-1].m_HongQiu[5]/10+(*DataList)[Index-1].m_HongQiu[5]%10;
			Temp1=(*DataList)[Index-1].m_HongQiu[0]+(*DataList)[Index-1].m_HongQiu[5];
		    Temp1=Temp1%10+Temp1/10;
		   // LuShu =GetLuShu(Temp1);
			LuShu=Temp1%3;
		

			switch(LuShu) 
			{
			case 0:
				LongTou = "0369V";
			/*	if(Jio%2 != 0)
					JiaoJi ="03 09 15";
				else
					JiaoJi ="06 12";*/
				break;

			case 1:
				LongTou = "147V";
			/*	if(Jio%2 != 0)
					JiaoJi ="01 07 13";
				else
					JiaoJi ="04 10";*/
				break;

			case 2:
				LongTou = "258V";
			/*	if(Jio%2 != 0)
					JiaoJi ="02 08 14";
				else
					JiaoJi ="05 11";*/
				break;
			}

			LongTou="杀"+LongTou;

			if(Index != DataList->size())
			{
				CString TempData;
				TempData.Format("%d",(*DataList)[Index].m_HongQiu[5]%10);
				if(LongTou.Find(TempData) == -1)
					LongTou+="S";
				else
					LongTou+="F";
			}
			else
				LongTou+="S";
			m_ListCtrl.SetItemText(Index,3,LongTou);


			LongTou.Empty();
			Temp1=(*DataList)[Index-1].m_HongQiu[1]%10 -1;
			LongTou.Format("%02d",Temp1);
			if(Index != DataList->size())
			{
				CString TempData;
				TempData.Format("%d",(*DataList)[Index].m_HongQiu[0]);
				if(LongTou.Find(TempData) == -1)
					LongTou+="S";
				else
					LongTou+="F";
			}
			else
				LongTou+="S";

			m_ListCtrl.SetItemText(Index,4,LongTou);

		}
		
	/*	vector<sHengXiangChaZhi>* DataList=CDataManageCenter::GetInstance()->GetHengXiangChaZhi();

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

		if(!DataList->empty())
			m_IsInitData = true;
	}

}

// 生成的消息映射函数
BOOL CDlgHengXiangChaZhi::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitListHeader();
	return true;
}

void CDlgHengXiangChaZhi::OnClose()
{
	ShowWindow(SW_HIDE);
}


void CDlgHengXiangChaZhi::OnBnClickedSearchBtn()
{
	CString Text;
	GetDlgItem(IDC_EDIT1)->GetWindowText(Text);
	DWORD Data=::atoi(Text.GetBuffer());
	m_ListCtrl.DeleteAllItems();
	vector<sHengXiangChaZhi>* DataList = NULL;
	vector<sHengXiangChaZhi> Temp;
	if(Data == 0)
	{
		DataList=CDataManageCenter::GetInstance()->GetHengXiangChaZhi();
	}
	else
	{
		Temp=CDataManageCenter::GetInstance()->SearchHengXiangChaZhi(Data);
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
	}
}
