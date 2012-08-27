// DlgWeiHong.cpp : 实现文件
//

#include "stdafx.h"
#include "ShuangSeQiu.h"
#include "DlgWeiHong.h"

extern CString GetAppCurrentPath();

// CDlgWeiHong 对话框

IMPLEMENT_DYNAMIC(CDlgWeiHong, CDialog)

CDlgWeiHong::CDlgWeiHong(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWeiHong::IDD, pParent)
{
	m_IsInitData=false;
}

CDlgWeiHong::~CDlgWeiHong()
{
}

void CDlgWeiHong::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
	DDX_Control(pDX, IDC_COMBO1, m_ComboBox);
}


BEGIN_MESSAGE_MAP(CDlgWeiHong, CDialog)
	
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDlgWeiHong::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgWeiHong::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CDlgWeiHong::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgWeiHong::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDlgWeiHong 消息处理程序


//初始化列表头
void CDlgWeiHong::InitListHeader()
{
	CRect Rect;
	//初始化应用程序列表控件
	m_ListCtrl.GetWindowRect(&Rect);
	int nWidth = Rect.Width()/10;
	m_ListCtrl.InsertColumn(0,_TEXT("29组号"),    LVCFMT_CENTER,5*nWidth);
	m_ListCtrl.InsertColumn(1,_TEXT("绝杀号"),	LVCFMT_CENTER,	4*nWidth); 
	m_ListCtrl.InsertColumn(2,_TEXT("关联号"),	LVCFMT_CENTER,	nWidth);
	
	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(222,0,0);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;
	m_ListCtrl.SetColumStyle(0,Style);
	m_ListCtrl.SetColumStyle(1,Style);
	m_ListCtrl.SetColumStyle(2,Style);

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

void CDlgWeiHong::OnShowWindow(BOOL bShow, UINT nStatus)
{
}

void CDlgWeiHong::OnClose()
{
	ShowWindow(SW_HIDE);
}
	
// 生成的消息映射函数
BOOL CDlgWeiHong::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitListHeader();

	/*
	SEARCH_JUESHA_QIE_JUESHA,      //按绝杀且绝杀搜索方式
	SEARCH_JUESHA_HUO_JUESHA,      //按绝杀或绝杀搜索方式
	SEARCH_DINGDAN_QIE_DINGDAN,    //按定胆且定胆搜索方式
	SEARCH_DINGDAN_HUO_DINGDAN,    //按定胆或定胆搜索方式     
	SEARCH_JUESHA_QIE_DINGDAN,     //按绝杀与定胆方式搜索
	SEARCH_JUESHA_HUO_DINGDAN      //按绝杀或定胆方式搜索
	*/
	m_ComboBox.InsertString(0,"绝杀且");
	m_ComboBox.InsertString(1,"绝杀或");
	m_ComboBox.InsertString(2,"定胆且");
	m_ComboBox.InsertString(3,"定胆或");
	m_ComboBox.InsertString(4,"绝或定");
	m_ComboBox.InsertString(5,"绝与定");
	m_ComboBox.SetCurSel(0);

	vector<sData29>* DataList=CDataManageCenter::GetInstance()->GetData29List();
	for(int Index=0; Index < DataList->size(); Index++)
	{
		InsertTextToList(Index,(*DataList)[Index]);
		
	}

	m_Result=*DataList;
//	sData29* DataList=CDataCenter::
	return true;
}

void CDlgWeiHong::OnCbnSelchangeCombo1()
{
	OnBnClickedButton1();
}

void CDlgWeiHong::OnBnClickedButton1()
{
	m_ListCtrl.DeleteAllItems();
	int CurSel = m_ComboBox.GetCurSel();
	int EData[7];
	memset(EData,0,sizeof(int)*7);

	CString Edit1;
	GetDlgItem(IDC_EDIT20)->GetWindowText(Edit1);
	if(!Edit1.IsEmpty())
	{
		EData[0] = atoi(Edit1.GetBuffer());
		Edit1.ReleaseBuffer();
	}

	GetDlgItem(IDC_EDIT21)->GetWindowText(Edit1);
	if(!Edit1.IsEmpty())
	{
		EData[1] = atoi(Edit1.GetBuffer());
		Edit1.ReleaseBuffer();
	}

	GetDlgItem(IDC_EDIT22)->GetWindowText(Edit1);
	if(!Edit1.IsEmpty())
	{
		EData[2] = atoi(Edit1.GetBuffer());
		Edit1.ReleaseBuffer();
	}

	GetDlgItem(IDC_EDIT23)->GetWindowText(Edit1);
	if(!Edit1.IsEmpty())
	{
		EData[3] = atoi(Edit1.GetBuffer());
		Edit1.ReleaseBuffer();
	}

	GetDlgItem(IDC_EDIT24)->GetWindowText(Edit1);
	if(!Edit1.IsEmpty())
	{
		EData[4] = atoi(Edit1.GetBuffer());
		Edit1.ReleaseBuffer();
	}

	GetDlgItem(IDC_EDIT25)->GetWindowText(Edit1);
	if(!Edit1.IsEmpty())
	{
		EData[5]= atoi(Edit1.GetBuffer());
		Edit1.ReleaseBuffer();
	}

	GetDlgItem(IDC_EDIT26)->GetWindowText(Edit1);
	if(!Edit1.IsEmpty())
	{
		EData[6] = atoi(Edit1.GetBuffer());
		Edit1.ReleaseBuffer();
	}

	
	sData29 Data;

	vector<sData29> DataList;

	/*
		SEARCH_JUESHA_QIE_JUESHA,      //按绝杀且绝杀搜索方式
	SEARCH_JUESHA_HUO_JUESHA,      //按绝杀或绝杀搜索方式
	SEARCH_DINGDAN_QIE_DINGDAN,    //按定胆且定胆搜索方式
	SEARCH_DINGDAN_HUO_DINGDAN,    //按定胆或定胆搜索方式     
	SEARCH_JUESHA_QIE_DINGDAN,     //按绝杀与定胆方式搜索
	SEARCH_JUESHA_HUO_DINGDAN      //按绝杀或定胆方式搜索
	*/

	switch(CurSel)
	{
	case 0:
		{
			for(int Index=0; Index < 7; Index++)
			{
				if(EData[Index] > 0)
					Data.m_JueSha.push_back(EData[Index]);
			}

			DataList=CDataManageCenter::GetInstance()->SeartData29(m_Result,Data,SEARCH_JUESHA_QIE_JUESHA);
		}
		break;
	case 1:
		{
			for(int Index=0; Index < 7; Index++)
			{
				if(EData[Index] > 0)
					Data.m_JueSha.push_back(EData[Index]);
			}

			DataList=CDataManageCenter::GetInstance()->SeartData29(m_Result,Data,SEARCH_JUESHA_HUO_JUESHA);
		}
		break;
	case 2:
		{
			for(int Index=0; Index < 7; Index++)
			{
				if(EData[Index] > 0)
					Data.m_WeiHong.push_back(EData[Index]);
			}

			DataList=CDataManageCenter::GetInstance()->SeartData29(m_Result,Data,SEARCH_DINGDAN_QIE_DINGDAN);
		}
		break;
	case 3:
		{
			for(int Index=0; Index < 7; Index++)
			{
				if(EData[Index] > 0)
					Data.m_WeiHong.push_back(EData[Index]);
			}

			DataList=CDataManageCenter::GetInstance()->SeartData29(m_Result,Data,SEARCH_DINGDAN_HUO_DINGDAN);
		}
		break;
	case 4:
		{
			for(int Index=0; Index < 4; Index++)
			{
				if(EData[Index] > 0)
					Data.m_JueSha.push_back(EData[Index]);
			}

			for(int Index=4; Index < 7; Index++)
			{
				if(EData[Index] > 0)
					Data.m_WeiHong.push_back(EData[Index]);
			}

			DataList=CDataManageCenter::GetInstance()->SeartData29(m_Result,Data,SEARCH_JUESHA_QIE_DINGDAN);
		}
		break;
	case 5:
		{
			for(int Index=0; Index < 4; Index++)
			{
				if(EData[Index] > 0)
					Data.m_JueSha.push_back(EData[Index]);
			}

			for(int Index=4; Index < 7; Index++)
			{
				if(EData[Index] > 0)
					Data.m_WeiHong.push_back(EData[Index]);
			}

			DataList=CDataManageCenter::GetInstance()->SeartData29(m_Result,Data,SEARCH_JUESHA_HUO_DINGDAN);
		}
		break;
	}

	for(int i=0; i < DataList.size(); i++)
	{
		InsertTextToList(i,DataList[i]);
	}

	m_Result.clear();
	m_Result =DataList;
}

void CDlgWeiHong::InsertTextToList(int InsertIndex,sData29& Data)
{	
	static bool IsFenGe=false;

	//InsertIndex=m_ListCtrl.GetItemCount();
	InsertIndex=m_ListCtrl.GetRowCount();
	if(InsertIndex == -1)
		IsFenGe=false;

	if(Data.m_WeiHong.size() == 1)
	{
		if(!IsFenGe)
		{
			m_ListCtrl.InsertItem(InsertIndex,"");
			InsertIndex++;
			IsFenGe=true;
		}
		CString Temp;
		if(Data.m_WeiHong[0] != 0)
		{
			Temp.Format("搜索号：%02d",Data.m_WeiHong[0]);
			m_ListCtrl.InsertItem(InsertIndex,"");
		    m_ListCtrl.SetItemText(InsertIndex,0,Temp);
			InsertIndex++;
		}
		return ;
		
	}

	m_ListCtrl.InsertItem(InsertIndex,"");
	InsertIndex++;

	CString StrData=Data.m_BianHao+"  ";
	for(int i=0; i < Data.m_WeiHong.size(); i++)
	{
		CString Temp;
		Temp.Format("%02d ",Data.m_WeiHong[i]);
		StrData+=Temp;
	}

	m_ListCtrl.SetItemText(InsertIndex-1,0,StrData);
	StrData.Empty();

	for(int i=0; i < Data.m_JueSha.size(); i++)
	{
		CString Temp;
		Temp.Format("%02d ",Data.m_JueSha[i]);
		StrData+=Temp;
	}
	m_ListCtrl.SetItemText(InsertIndex-1,1,StrData);
	StrData.Empty();


	for(int i=0; i < Data.m_GuanLian.size(); i++)
	{
		CString Temp;
		Temp.Format("%02d ",Data.m_GuanLian[i]);
		StrData+=Temp;
	}
	m_ListCtrl.SetItemText(InsertIndex-1,2,StrData);
	StrData.Empty();


}
void CDlgWeiHong::OnBnClickedOk()
{
	m_Result.clear();
	vector<sData29>* DataList=CDataManageCenter::GetInstance()->GetData29List();
	m_Result=*DataList;

	OnBnClickedButton1();
}

void CDlgWeiHong::OnBnClickedButton2()
{
	int ArrayData[33];
	memset(ArrayData,0,33*sizeof(int));
	int DataCount=0;

	for(int Index=0; Index < m_Result.size(); Index++)
	{
		if(m_Result[Index].m_WeiHong.size() == 1)
		{
			continue;
		}

		for(int i=0; i < m_Result[Index].m_WeiHong.size(); i++)
		{
			int Data =  m_Result[Index].m_WeiHong[i]-1;
			ArrayData[Data]++;
		}

		DataCount++;
	}

	int JueArrayData[33];
	memset(JueArrayData,0,33*sizeof(int));
	int JueDataCount=0;

	for(int Index=0; Index < m_Result.size(); Index++)
	{
		if(m_Result[Index].m_WeiHong.size() == 1)
		{
			continue;
		}

		for(int i=0; i < m_Result[Index].m_JueSha.size(); i++)
		{
			int Data =  m_Result[Index].m_JueSha[i]-1;
			JueArrayData[Data]++;
		}

		JueDataCount++;
	}



	CString FilePath=GetAppCurrentPath()+_T("29searchtongji.txt");
	DWORD Flag = CREATE_ALWAYS;
	HANDLE FileHandle=CreateFile(FilePath,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL,Flag,FILE_ATTRIBUTE_NORMAL,NULL);
	if(FileHandle == INVALID_HANDLE_VALUE)
		return;


	CString HasData=_T("围红交集：\r\n");
	CString NotHasData=_T(_T("绝杀交集：\r\n"));

	for(int Index = 0; Index < 33; Index++)
	{
		if( ArrayData[Index] == DataCount)
		{
			CString TempStr;
			TempStr.Format("%02d ",Index+1);
			HasData+=TempStr;
		}

		if(JueArrayData[Index] == JueDataCount)
		{
			CString TempStr;
			TempStr.Format("%02d ",Index+1);
			NotHasData+=TempStr;
		}
		
	}

	CString DataStr=HasData+_T("\r\n\r\n\r\n")+NotHasData;
	
	DWORD WriteBytes=0;
	::WriteFile(FileHandle,DataStr.GetBuffer(),DataStr.GetLength(),&WriteBytes,NULL);
	CloseHandle(FileHandle);
	ShellExecute(NULL, "open",FilePath, NULL, NULL, SW_SHOWNORMAL);
}
