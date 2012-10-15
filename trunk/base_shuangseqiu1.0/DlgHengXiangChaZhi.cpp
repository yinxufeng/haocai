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
	int AllCount = 6;
	m_ListCtrl.GetWindowRect(&Rect);
	int nWidth = Rect.Width()/(AllCount+2);

	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(222,0,0);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;

	m_ListCtrl.InsertColumn(0,_TEXT("期号"),    LVCFMT_CENTER,	2*nWidth);
	m_ListCtrl.SetColumStyle(0,Style);
	
	for(int Index = 1; Index < 6; Index++)
	{
		CString Text;
		Text.Format("%02d",Index);
		m_ListCtrl.InsertColumn(Index,Text,    LVCFMT_CENTER,	nWidth);
		m_ListCtrl.SetColumStyle(Index,Style);
	}


	m_ListCtrl.InsertColumn(7,"7",    LVCFMT_CENTER,	3*nWidth);
	m_ListCtrl.SetColumStyle(7,Style);
	m_ListCtrl.InsertColumn(8,"8",    LVCFMT_CENTER,	nWidth);
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
		Style.m_DrawData.m_TextData.m_TextColor=RGB(222,0,0);
		Style.m_DrawData.m_TextData.m_TextFont = NULL;
		Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;

		m_ListCtrl.InsertItem(0,"");

		vector<sShuangSeQiu>*DataList =CDataManageCenter::GetInstance()->GetDataListByChuHao();
		for(int Index = 1; Index <= DataList->size(); Index++)
		{
			m_ListCtrl.InsertItem(Index,"");
		
			int LuShuArray[3];
			memset(LuShuArray,0,sizeof(int)*3);
			int ErrorCount=0;
			
			if(Index !=  DataList->size())
			{
				CString Str;
				Str.Format("%s 篮球=%02d 路数=%02d ",(*DataList)[Index].m_QiShu,(*DataList)[Index].m_LanQiu,(*DataList)[Index].m_LanQiu%3);
				m_ListCtrl.SetItemText(Index,0,Str);
			}


			if(Index >= 2)
			{
				int Lu=0;
				/*int Lu1 = (*DataList)[Index-1].m_LanQiu%3;
				int Lu2 = (*DataList)[Index-2].m_LanQiu%3;
				if(Lu1 == Lu2)
				{
					Lu = Lu1+Lu2 + 1;
				}
				else
					Lu = Lu1+Lu2;

				Lu=Lu%3;*/
				Lu = ((*DataList)[Index-1].m_HongQiu[2]+(*DataList)[Index-1].m_HongQiu[3])%3;

				bool IsTrue=false;
				if(Index != DataList->size() && (*DataList)[Index].m_LanQiu%3 == Lu)
				{
					IsTrue = true;
				}

				if(!IsTrue)
				{
					if(Index %2 == 0)
						Style.m_DrawData.m_TextData.m_TextColor=RGB(22,22,22);
					else
						Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);

					m_ListCtrl.SetItemSpecialStyle(Index,1,Style);
				}
				else
				{

					Style.m_DrawData.m_TextData.m_TextColor=RGB(222,0,0);
					m_ListCtrl.SetItemSpecialStyle(Index,1,Style);
				}
				
				CString Str;
				Str.Format("%d",Lu);
				m_ListCtrl.SetItemText(Index,1,Str);
			}
		}
		//CString FilePath = GetAppCurrentPath3()+_T("\\LuShu.txt");
		//HANDLE FileHandle=CreateFile(FilePath,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

		//m_ListCtrl.InsertItem(0,"");
		//vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
		//vector<sShuangSeQiu>* ShunXu = CDataManageCenter::GetInstance()->GetDataListByChuHao();
		//for(int Index = 1; Index <= DataList->size(); Index++)
		//{
		//	m_ListCtrl.InsertItem(Index,"");
		//
		//	int LuShuArray[3];
		//	memset(LuShuArray,0,sizeof(int)*3);
		//	int ErrorCount=0;
		//	
		//	if(Index !=  DataList->size())
		//	{
		//		CString Str;
		//		Str.Format("%s 篮球=%02d 路数=%02d ",(*DataList)[Index].m_QiShu,(*DataList)[Index].m_LanQiu,(*DataList)[Index].m_LanQiu%3);
		//		if((*DataList)[Index].m_LanQiu%2)
		//			Str+="奇偶=奇";
		//		else
		//			Str+="奇偶=偶";
		//		m_ListCtrl.SetItemText(Index,0,Str);
		//	}

		//	int QiShu=atoi((*DataList)[Index-1].m_QiShu.GetBuffer());
		//	int Jio = (*DataList)[Index-1].m_HongQiu[0]+QiShu;
		//	CString StrJio;
		//	if(Jio%2 == 0)
		//	{
		//		StrJio="偶数";
		//		if(Index != DataList->size())
		//		{
		//			if((*DataList)[Index].m_LanQiu %2)
		//				StrJio+="F";
		//			else
		//				StrJio+="S";
		//		}
		//		else
		//			StrJio+="S";
		//	}
		//	else
		//	{
		//		StrJio="奇数";
		//		if(Index != DataList->size())
		//		{
		//			if((*DataList)[Index].m_LanQiu %2)
		//				StrJio+="S";
		//			else
		//				StrJio+="F";
		//		}
		//		else
		//			StrJio+="S";
		//	}

		////	int Temp1=(*DataList)[Index-1].m_HongQiu[0]/10+(*DataList)[Index-1].m_HongQiu[0]%10 +(*DataList)[Index-1].m_HongQiu[1]/10+(*DataList)[Index-1].m_HongQiu[1]%10;
		//	//int Temp1=(*DataList)[Index-1].m_HongQiu[1]/10+(*DataList)[Index-1].m_HongQiu[1]%10 +(*DataList)[Index-1].m_HongQiu[2]/10+(*DataList)[Index-1].m_HongQiu[2]%10;
		//	//int Temp1=(*DataList)[Index-1].m_HongQiu[1]%3+(*DataList)[Index-1].m_HongQiu[3]%3 +(*DataList)[Index-1].m_HongQiu[5]%3;
		//	int Temp1=(*DataList)[Index-1].m_HongQiu[3]%3;
		////	int Temp1=(*DataList)[Index-1].m_HongQiu[1]%10 +(*DataList)[Index-1].m_HongQiu[2]%10;
		////	Temp1=Temp1%10;
		//	int LuShu =Temp1%3;//GetLuShu(Temp1);
		//	CString LongTou;
		//	CString JiaoJi;

		//	LuShuArray[LuShu]++;
		//	LongTou.Empty();
		//	LongTou.Format("%02d",LuShu);
		//	LongTou=""+LongTou;

		//	if(Index != DataList->size())
		//	{
		//		CString TempData;
		//		TempData.Format("%02d",(*DataList)[Index].m_LanQiu%3);
		//		if(LongTou.Find(TempData) == -1)
		//			LongTou+="S";
		//		else
		//		{
		//			LongTou+="F";
		//			ErrorCount++;
		//		}
		//	}
		//	else
		//		LongTou+="S";


		//	if(Index != DataList->size())
		//	{
		//		CString TempData;
		//		TempData.Format("%02d",(*DataList)[Index].m_LanQiu);
		//		if(JiaoJi.Find(TempData) != -1)
		//			JiaoJi+="S";
		//		else
		//			JiaoJi+="F";
		//	}
		//	else
		//		JiaoJi+="S";



		//	m_ListCtrl.SetItemText(Index,1,LongTou);
		//	m_ListCtrl.SetItemText(Index,2,JiaoJi);

	


		//	Temp1=0;
		//	QiShu = atoi((*DataList)[Index-1].m_QiShu.GetBuffer());

		//

		//	Temp1=abs((*ShunXu)[Index-1].m_HongQiu[1]+(*ShunXu)[Index-1].m_HongQiu[5]-(*ShunXu)[Index-1].m_HongQiu[0]);
		//	LuShu=Temp1%3;


		//	LuShuArray[LuShu]++;
		//    LongTou.Empty();
		//	LongTou.Format("%02d",LuShu);

		//	LongTou="杀"+LongTou;

		//	if(Index != DataList->size())
		//	{
		//		CString TempData;
		//		TempData.Format("%02d",(*DataList)[Index].m_LanQiu%3);
		//		if(LongTou.Find(TempData) == -1)
		//			LongTou+="S";
		//		else
		//		{
		//			LongTou+="F";
		//			ErrorCount++;
		//		}
		//	}
		//	else
		//		LongTou+="S";

		//	m_ListCtrl.SetItemText(Index,2,LongTou);





		//	m_ListCtrl.SetItemText(Index,3,StrJio);

		//	CString ShaHao   ="  杀号:      ";
		//	CString WeiShaHao="未杀号:      ";

		//	for(int i=0; i < 3; i++)
		//	{
		//		if(LuShuArray[i])
		//		{
		//			ShaHao+=GetDataStr(i);
		//		}
		//		else
		//			WeiShaHao+=GetDataStr(i);
		//	}

		//	ShaHao   +="\r\n";
		//	WeiShaHao+="\r\n";

		//	CString WriteStr;
		//	if(Index !=  DataList->size())
		//	{
		//		WriteStr.Format("%s 篮球=%02d 错误个数: %02d:\r\n",(*DataList)[Index].m_QiShu,(*DataList)[Index].m_LanQiu,ErrorCount);
		//	}
		//	else
		//	{
		//		WriteStr="下期预测:\r\n";
		//	}

		//	WriteStr +=ShaHao+WeiShaHao;
		//	DWORD WriteBytes=0;
		//	::WriteFile(FileHandle,WriteStr.GetBuffer(),WriteStr.GetLength(),&WriteBytes,NULL);

			/*if(Index != DataList->size())
			{
				LongTou.Empty();
				LongTou.Format("%02d",(*DataList)[Index].m_LanQiu%3);
				m_ListCtrl.SetItemText(Index,4,LongTou);

				LongTou.Empty();
				if((*DataList)[Index].m_LanQiu%2)
					LongTou="奇数";
				else
					LongTou="偶数";

				m_ListCtrl.SetItemText(Index,5,LongTou);
			}*/

		

		//}
		
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

	/*	if(!DataList->empty())
			m_IsInitData = true;

		if(FileHandle != INVALID_HANDLE_VALUE)
			CloseHandle(FileHandle);*/
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
	//CString Text;
	//GetDlgItem(IDC_EDIT1)->GetWindowText(Text);
	//DWORD Data=::atoi(Text.GetBuffer());
	//m_ListCtrl.DeleteAllItems();
	//vector<sHengXiangChaZhi>* DataList = NULL;
	//vector<sHengXiangChaZhi> Temp;
	//if(Data == 0)
	//{
	//	DataList=CDataManageCenter::GetInstance()->GetHengXiangChaZhi();
	//}
	//else
	//{
	//	Temp=CDataManageCenter::GetInstance()->SearchHengXiangChaZhi(Data);
	//	DataList=&Temp;
	//}

	//for(int Index = 0; Index < (int)DataList->size(); Index++)
	//{
	//	m_ListCtrl.InsertItem(Index,"");
	//	m_ListCtrl.SetItemText(Index,0,(*DataList)[Index].m_QiShu);
	//	for(int HongQiu=0; HongQiu < 6; HongQiu++)
	//	{
	//		CString Temp;
	//		Temp.Format("%d",(*DataList)[Index].m_HongQiuChaZhi[HongQiu]);
	//		m_ListCtrl.SetItemText(Index,HongQiu+1,Temp);
	//	}

	//	CString LanQiu;
	//	LanQiu.Format("%d",(*DataList)[Index].m_LanQiuChaZhi);
	//	m_ListCtrl.SetItemText(Index,7,LanQiu);
//	}
	CString FilePath = GetAppCurrentPath3()+_T("\\LuShu.txt");
	ShellExecute(NULL, "open",FilePath, NULL, NULL, SW_SHOWNORMAL);
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
