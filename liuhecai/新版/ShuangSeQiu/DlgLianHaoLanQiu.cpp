// DlgLianHaoLanQiu.cpp : 实现文件
//

#include "stdafx.h"
#include "ShuangSeQiu.h"
#include "DlgLianHaoLanQiu.h"


// CDlgLianHaoLanQiu 对话框


//获取模块路径
CString GetAppCurrentPath3()
{
	CString server_ip;
	CString StrDes=_T("");
	::GetModuleFileName(NULL,StrDes.GetBuffer(MAX_PATH),MAX_PATH); 
	//::GetCurrentDirectory(MAX_PATH,StrDes.GetBuffer(MAX_PATH));
	StrDes.ReleaseBuffer();
	StrDes=StrDes.Left(StrDes.ReverseFind('\\'));
	if(StrDes.Right(1)!='\\')
		StrDes+="\\";

	return StrDes;
}



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
	m_ListCtrl.InsertColumn(0,_TEXT("期数"),    LVCFMT_CENTER,	1*nWidth);
	//m_ListCtrl.InsertColumn(1,_TEXT("均值"),	LVCFMT_CENTER,	0.5*nWidth);
	m_ListCtrl.InsertColumn(1,_TEXT("绝杀特码"),	LVCFMT_CENTER,	7*nWidth);
	m_ListCtrl.InsertColumn(2,_TEXT("绝杀统计"),	LVCFMT_CENTER,	2*nWidth);
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
		m_IsInitData = true;
		m_ListCtrl.DeleteAllItems();
		m_ListCtrl.InsertItem(0,"");
		vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
		vector<sShuangSeQiu>* ShunXuDataList = CDataManageCenter::GetInstance()->GetDataListByChuHao();
		int Sum[6];
		memset(Sum,0,sizeof(int)*6);

		
		CString FilePath = GetAppCurrentPath3()+_T("\\shahao.txt");
		HANDLE FileHandle=CreateFile(FilePath,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

		for(int Index = 1; Index < (int)DataList->size()+1; Index++)
		{
			int ShaArray[QIU_COUNT+1];
	    	memset(ShaArray,0,sizeof(int)*(QIU_COUNT+1));
			m_ListCtrl.InsertItem(Index,"");
			if(Index == DataList->size())
			{
				m_ListCtrl.SetItemText(Index,0,"预测");
			}
			else
			{
				CString Str;
				Str.Format("%s 特码=%02d",(*DataList)[Index].m_QiShu,(*DataList)[Index].m_LanQiu);
				/*for(int i =0; i < 6; i++)
				{
					CString Temp;
					Temp.Format("%02d ",(*DataList)[Index].m_HongQiu[i]);
					Str+=Temp;
				}

				CString TempLan;
				TempLan.Format("+%02d",(*DataList)[Index].m_LanQiu);
				Str+=TempLan;*/
				m_ListCtrl.SetItemText(Index,0,Str);

			}

			/*CString JunZhi;

			for(int i = 0; i < 6; i++)
			{
				Sum[i]+=(*DataList)[Index-1].m_HongQiu[i];
				CString Temp;
				Temp.Format("%02d ",Sum[i]/Index);
				JunZhi+=Temp;
			}

			m_ListCtrl.SetItemText(Index,1,JunZhi);*/

			CString ShaHongList;
			int TempData = (*DataList)[Index-1].m_HongQiu[5]-(*DataList)[Index-1].m_HongQiu[0];
			CString ShaHong;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_HongQiu[2]-(*DataList)[Index-1].m_HongQiu[1];
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_HongQiu[5]-(*DataList)[Index-1].m_HongQiu[1];
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_HongQiu[0]*4-2;
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;

			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);

			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = ((*DataList)[Index-1].m_HongQiu[0]+(*DataList)[Index-1].m_LanQiu)*3;
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_HongQiu[0]+9;
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);

			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;


			TempData = (*DataList)[Index-1].m_HongQiu[1]+5;
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_HongQiu[2]+4;
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_HongQiu[2]+7;
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_HongQiu[5]+4;
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_HongQiu[4]-(*DataList)[Index-1].m_HongQiu[3]+(*DataList)[Index-1].m_LanQiu+1;
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_LanQiu+(*DataList)[Index-1].m_HongQiu[0];
			if(Index >= 2)
			{
				if((*DataList)[Index-1].m_LanQiu == ((*DataList)[Index-2].m_LanQiu))
					TempData-=1;
			}
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_LanQiu+(*DataList)[Index-1].m_HongQiu[1]-1;
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;


			TempData = (*DataList)[Index-1].m_LanQiu-(*DataList)[Index-1].m_HongQiu[3]+1+QIU_COUNT;
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_LanQiu-(*DataList)[Index-1].m_HongQiu[4]+QIU_COUNT;
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = abs((*DataList)[Index-1].m_LanQiu*(*DataList)[Index-1].m_HongQiu[0]);
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_LanQiu+7;
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_LanQiu+9;
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

		/*	TempData = (*DataList)[Index-1].m_LanQiu*5+2;
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			*/


			
            TempData = (*DataList)[Index-1].m_LanQiu;
			if(TempData /2 == 0)
				TempData=TempData*2+2;
			else
				TempData=TempData*5+2;

			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;


			TempData = abs((*DataList)[Index-1].m_LanQiu-(*DataList)[Index-1].m_HongQiu[5]);
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_HongQiu[2]+(*DataList)[Index-1].m_HongQiu[5]/QIU_COUNT + 14;
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = ((*DataList)[Index-1].m_HongQiu[0]+(*DataList)[Index-1].m_HongQiu[2]+(*DataList)[Index-1].m_HongQiu[4])/2;
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = abs((*DataList)[Index-1].m_LanQiu+16-(*DataList)[Index-1].m_HongQiu[0]);
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_HongQiu[0]+(*DataList)[Index-1].m_HongQiu[1]+(*DataList)[Index-1].m_LanQiu;
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_HongQiu[5]-(*DataList)[Index-1].m_HongQiu[0]+(*DataList)[Index-1].m_HongQiu[2];
			if(TempData > QIU_COUNT)
				TempData = TempData%QIU_COUNT;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

		
			
			//按出球顺序杀号法
		/*if( ShunXuDataList->size() == DataList->size())
			{
			/*	TempData = (*ShunXuDataList)[Index-1].m_HongQiu[0]+(*ShunXuDataList)[Index-1].m_HongQiu[1];
				if(TempData > 33)
					TempData = TempData%33;
				if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
					ShaHong.Format("%02dF ",TempData);
				else
					ShaHong.Format("%02dS ",TempData);
				ShaHongList += ShaHong;
				ShaHong.Empty();
*/
		/*	
				TempData = abs((*ShunXuDataList)[Index-1].m_HongQiu[1]-(*ShunXuDataList)[Index-1].m_HongQiu[2]);
				if(TempData > 33)
					TempData = TempData%33;
				if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
					ShaHong.Format("%02dF ",TempData);
				else
					ShaHong.Format("%02dS ",TempData);
				ShaHongList += ShaHong;
				ShaHong.Empty();
				ShaArray[TempData]++;

				TempData = abs((*ShunXuDataList)[Index-1].m_HongQiu[2]-(*ShunXuDataList)[Index-1].m_HongQiu[4]);
				if(TempData > 33)
					TempData = TempData%33;
				if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
					ShaHong.Format("%02dF ",TempData);
				else
					ShaHong.Format("%02dS ",TempData);
				ShaHongList += ShaHong;
				ShaHong.Empty();
				ShaArray[TempData]++;


				TempData = abs((*ShunXuDataList)[Index-1].m_HongQiu[0]-(*ShunXuDataList)[Index-1].m_HongQiu[5]) +(*ShunXuDataList)[Index-1].m_LanQiu-3;
				if(TempData > 33)
					TempData = TempData%33;
				if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
					ShaHong.Format("%02dF ",TempData);
				else
					ShaHong.Format("%02dS ",TempData);
				ShaHongList += ShaHong;
				ShaHong.Empty();
				ShaArray[TempData]++;

				TempData = abs((*ShunXuDataList)[Index-1].m_HongQiu[0]-(*ShunXuDataList)[Index-1].m_HongQiu[2]) +(*ShunXuDataList)[Index-1].m_LanQiu+2;
				if(TempData > 33)
					TempData = TempData%33;
				if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
					ShaHong.Format("%02dF ",TempData);
				else
					ShaHong.Format("%02dS ",TempData);
				ShaHongList += ShaHong;
				ShaHong.Empty();
				ShaArray[TempData]++;

				
				TempData = (*ShunXuDataList)[Index-1].m_HongQiu[0]+(*ShunXuDataList)[Index-1].m_HongQiu[1]+(*ShunXuDataList)[Index-1].m_HongQiu[2] +(*ShunXuDataList)[Index-1].m_LanQiu-1;
				if(TempData > 33)
					TempData = TempData%33;
				if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
					ShaHong.Format("%02dF ",TempData);
				else
					ShaHong.Format("%02dS ",TempData);
				ShaHongList += ShaHong;
				ShaHong.Empty();
				ShaArray[TempData]++;


			}

			//按AC值杀号
			TempData = CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_LanQiu;
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData = (*DataList)[Index-1].m_LanQiu+ CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			
			TempData =0;
			for(int i=0; i < 6; i++)
				TempData+=(*DataList)[Index-1].m_HongQiu[i]%10;
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData =CDataManageCenter::GetZhiShuCount((*DataList)[Index-1]);
			TempData += (*DataList)[Index-1].m_LanQiu;
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData =CDataManageCenter::GetZhiShuCount((*DataList)[Index-1]);
			TempData =TempData*CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData =CDataManageCenter::GetZhiShuCount((*DataList)[Index-1]);
			TempData =TempData+CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData =CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
			TempData =abs(TempData - (*DataList)[Index-1].m_HongQiu[5]);
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;

			TempData =CDataManageCenter::GetZhiShuCount((*DataList)[Index-1])+CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
			TempData =TempData + (*DataList)[Index-1].m_LanQiu;
			if(TempData > 33)
				TempData = TempData%33;
			if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
				ShaHong.Format("%02dF ",TempData);
			else
				ShaHong.Format("%02dS ",TempData);
			ShaHongList += ShaHong;
			ShaHong.Empty();
			ShaArray[TempData]++;


			for(int i=0; i < 6; i++)
			{
				float TempF = (float)(*DataList)[Index-1].m_HongQiu[i];
				TempF=TempF*0.88;
				TempData =(int)TempF;
				if(TempData > 33)
					TempData = TempData%33;
				if(Index < DataList->size() && CDataManageCenter::IsLanQiuInData((*DataList)[Index],TempData))
					ShaHong.Format("%02dF ",TempData);
				else
					ShaHong.Format("%02dS ",TempData);
				ShaHongList += ShaHong;
				ShaHong.Empty();
				ShaArray[TempData]++;
			}
			*/

			m_ListCtrl.SetItemText(Index,1,ShaHongList);

			
			CString ErrorStr;

	

			if(FileHandle!= INVALID_HANDLE_VALUE)
			{
				
				CString LuShuStr0 ="路数0：\r\n";
				CString LuShuStr1 ="路数1：\r\n";
				CString LuShuStr2 ="路数2：\r\n";

				int ShaCount=0;
				int ErrorCount=0;
				CString TempStr;
				for(int i=1; i < QIU_COUNT+1;i++)
				{
					if(ShaArray[i])
					{
						CString Temp;
						Temp.Format("%02d ",i);
						TempStr+=Temp;
						ShaCount++;

						switch(i%3)
						{
						case 0:
							LuShuStr0 +=Temp;
							break;
						case 1:
							LuShuStr1 +=Temp;
							break;
						case 2:
							LuShuStr2 +=Temp;
							break;
						}
						
						if(Index != DataList->size())
						{
							if((*DataList)[Index].m_LanQiu == i)
							{
								ErrorCount=ShaArray[i];
							}
						}
					}

				}

				if(Index != DataList->size())
				{
					CString Temp;
					Temp.Format("  杀号个数:%02d,错误个数:%02d\r\n",ShaCount,ErrorCount);
					ErrorStr.Format("杀:%02d,错:%02d",ShaCount,ErrorCount);
					TempStr=(*DataList)[Index].m_QiShu+Temp+TempStr+"\r\n";
				}
				else
				{
					CString Temp;
					Temp.Format("  杀号个数:%02d\r\n",ShaCount);
					TempStr="下期杀号"+Temp+TempStr+"\r\n";

					ErrorStr.Format("杀:%02d",ShaCount);
				}

				m_ListCtrl.SetItemText(Index,2,ErrorStr);

				LuShuStr0 +="\r\n";
				LuShuStr1 +="\r\n";
				LuShuStr2 +="\r\n";

				DWORD WriteBytes=0;
				::WriteFile(FileHandle,TempStr.GetBuffer(),TempStr.GetLength(),&WriteBytes,NULL);
				::WriteFile(FileHandle,LuShuStr0.GetBuffer(),LuShuStr0.GetLength(),&WriteBytes,NULL);
				::WriteFile(FileHandle,LuShuStr1.GetBuffer(),LuShuStr1.GetLength(),&WriteBytes,NULL);
				::WriteFile(FileHandle,LuShuStr2.GetBuffer(),LuShuStr2.GetLength(),&WriteBytes,NULL);
				
			}
		}

		if(FileHandle != INVALID_HANDLE_VALUE)
		{
			CloseHandle(FileHandle);
			//ShellExecute(NULL, "open",FilePath, NULL, NULL, SW_SHOWNORMAL);
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
