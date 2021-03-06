// DlgLianHaoHongQiu.cpp : 实现文件
//

#include "stdafx.h"
#include "ShuangSeQiu.h"
#include "DlgLianHaoHongQiu.h"


extern CString GetAppCurrentPath();
// CDlgLianHaoHongQiu 对话框

IMPLEMENT_DYNAMIC(CDlgLianHaoHongQiu, CDialog)

CDlgLianHaoHongQiu::CDlgLianHaoHongQiu(CWnd* pParent /*=NULL*/)
: CDialog(CDlgLianHaoHongQiu::IDD, pParent)
{
	m_IsInitData = false;
	m_CompareShuangDanType=0;
	 m_ParamData=314;
	 m_Flag=false;
}

CDlgLianHaoHongQiu::~CDlgLianHaoHongQiu()
{
}

void CDlgLianHaoHongQiu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
	DDX_Control(pDX, IDC_LIST2, m_ListCtrl2);
	DDX_Control(pDX, IDC_LIST4,m_ListCtrl3);
	DDX_Control(pDX, IDC_COMBO1, m_ComboBox);
}


BEGIN_MESSAGE_MAP(CDlgLianHaoHongQiu, CDialog)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()

	ON_BN_CLICKED(IDC_BUTTON1, &CDlgLianHaoHongQiu::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgLianHaoHongQiu::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_WEI_FEN_BTN, &CDlgLianHaoHongQiu::OnBnClickedWeiFenBtn)
	ON_BN_CLICKED(IDC_HE_FEN_BTN, &CDlgLianHaoHongQiu::OnBnClickedHeFenBtn)
	ON_BN_CLICKED(IDC_WEISHU_SHUANGDAN_BTN, &CDlgLianHaoHongQiu::OnBnClickedWeishuShuangdanBtn)
	ON_BN_CLICKED(IDC_HESHU_SHUANGDAN_BTN, &CDlgLianHaoHongQiu::OnBnClickedHeshuShuangdanBtn)
	ON_BN_CLICKED(IDC_CHASHU_SHUANGDAN_BTN, &CDlgLianHaoHongQiu::OnBnClickedChashuShuangdanBtn)
	ON_BN_CLICKED(IDC_QIAN_SAN_WEI_BTN, &CDlgLianHaoHongQiu::OnBnClickedQianSanWeiBtn)
	ON_BN_CLICKED(IDC_HOU_SAN_WEI_BTN, &CDlgLianHaoHongQiu::OnBnClickedHouSanWeiBtn)
	ON_BN_CLICKED(IDC_QIAN_SAN_HE_BTN, &CDlgLianHaoHongQiu::OnBnClickedQianSanHeBtn)
	ON_BN_CLICKED(IDC_HOU_SAN_HE_BTN, &CDlgLianHaoHongQiu::OnBnClickedHouSanHeBtn)
	ON_BN_CLICKED(IDC_HOU_SAN_HE_BTN2, &CDlgLianHaoHongQiu::OnBnClickedHouSanHeBtn2)
	ON_BN_CLICKED(IDC_EXEC_BTN, &CDlgLianHaoHongQiu::OnBnClickedExecBtn)
	ON_BN_CLICKED(IDC_JIXIAN_BTN, &CDlgLianHaoHongQiu::OnBnClickedJixianBtn)
	ON_BN_CLICKED(IDC_WEISHU_SHUANGDAN_BTN6, &CDlgLianHaoHongQiu::OnBnClickedWeishuShuangdanBtn2)
	ON_BN_CLICKED(IDC_HESHU_SHUANGDAN_BTN6, &CDlgLianHaoHongQiu::OnBnClickedHeshuShuangdanBtn2)
	ON_BN_CLICKED(IDC_CHASHU_SHUANGDAN_BTN6, &CDlgLianHaoHongQiu::OnBnClickedChashuShuangdanBtn2)
END_MESSAGE_MAP()


// CDlgLianHaoHongQiu 消息处理程序

//初始化列表头
void CDlgLianHaoHongQiu::InitListHeader()
{
    CRect Rect;
	//初始化应用程序列表控件
	m_ListCtrl.GetWindowRect(&Rect);
	int ColoCount=10;
	int nWidth = Rect.Width()/(ColoCount+2);

	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;

	m_ListCtrl.InsertColumn(0,_TEXT("期数"),    LVCFMT_CENTER,	2*nWidth);
	m_ListCtrl.SetColumStyle(0,Style);
	m_ListCtrl2.SetColumStyle(0,Style);
	m_ListCtrl2.InsertColumn(0,_TEXT("期数"),    LVCFMT_CENTER,	nWidth);
    
	m_ListCtrl3.SetColumStyle(0,Style);
	m_ListCtrl3.InsertColumn(0,_TEXT("期数"),    LVCFMT_CENTER,	nWidth);

	for(int Index = 1; Index <= ColoCount; Index++)
	{
		CString Str;
		Str.Format("%02d",Index);
		m_ListCtrl.InsertColumn(Index,Str,    LVCFMT_CENTER,	nWidth);
		m_ListCtrl.SetColumStyle(Index,Style);
	}

	m_ListCtrl.InsertColumn(ColoCount+1,"统计",    LVCFMT_CENTER,	nWidth);
	m_ListCtrl.SetColumStyle(ColoCount+1,Style);
	m_ListCtrl.InsertColumn(ColoCount+2,"对错",    LVCFMT_CENTER,	nWidth);
	m_ListCtrl.SetColumStyle(ColoCount+2,Style);


	m_ListCtrl.InsertColumn(0,_TEXT("期数"),    LVCFMT_CENTER,	2*nWidth);
	m_ListCtrl.SetColumStyle(0,Style);

	int TempCount=70;
	nWidth=21;
	for(int Index = 1; Index <=TempCount; Index++)
	{
		CString Str;
		Str.Format("%02d",Index);
		m_ListCtrl2.InsertColumn(Index,Str,    LVCFMT_CENTER,	nWidth);
		m_ListCtrl2.SetColumStyle(Index,Style);
	}

	TempCount=60;
	nWidth=30;
	for(int Index = 1; Index <=TempCount; Index++)
	{
		CString Str;
		Str.Format("%02d",Index);
		m_ListCtrl3.InsertColumn(Index,Str,    LVCFMT_CENTER,	nWidth);
		m_ListCtrl3.SetColumStyle(Index,Style);
	}


	m_ListCtrl.SetRowHeight(30);
	m_ListCtrl.ShowHeader(true);

	m_ListCtrl2.SetRowHeight(21);
	m_ListCtrl2.ShowHeader(true);

	m_ListCtrl3.SetRowHeight(30);
	m_ListCtrl3.ShowHeader(true);

	sItemBkData ItemBkData;
	ItemBkData.m_BkFillMode = MODE_FILL_RGB;
	ItemBkData.m_HeightColor = RGB(222,22,100);
	ItemBkData.m_HeightFillMode = MODE_FILL_RGB;
	ItemBkData.m_HeightColor = RGB(100,100,100);
	ItemBkData.m_BkColor = RGB(222,222,222);
	m_ListCtrl.SetItemBkData(ItemBkData);
	m_ListCtrl2.SetItemBkData(ItemBkData);

	ItemBkData.m_BkColor = RGB(205,250,213);
	m_ListCtrl3.SetItemBkData(ItemBkData);

	m_ListCtrl2.SetShowHScrollBar(false);


}


//初始化Combox
void CDlgLianHaoHongQiu::InitCombox()
{
	m_ComboBox.InsertString(0,"314尾前后三走势");
	m_ComboBox.InsertString(1,"618尾前后三走势");
	m_ComboBox.InsertString(2,"314合前后三走势");
	m_ComboBox.InsertString(3,"618合前后三走势");
	m_ComboBox.InsertString(4,"314差前后三走势");
	m_ComboBox.InsertString(5,"618差前后三走势");
	m_ComboBox.InsertString(6,"双胆尾走势");
	m_ComboBox.InsertString(7,"双胆合走势");
	m_ComboBox.InsertString(8,"双胆差走势");

	m_ComboBox.InsertString(9,"可变尾前后三走势");
	m_ComboBox.InsertString(10,"可变合前后三走势");
	m_ComboBox.InsertString(11,"可变差前后三走势");
	m_ComboBox.InsertString(12,"可变双胆尾走势");
	m_ComboBox.InsertString(13,"可变双胆合走势");
	m_ComboBox.InsertString(14,"可变双胆差走势");


	m_ComboBox.InsertString(15,"自动尾前后三极限");
	m_ComboBox.InsertString(16,"自动合前后三极限");
	m_ComboBox.InsertString(17,"自动差前后三极限");
	m_ComboBox.InsertString(18,"自动双胆尾极限");
	m_ComboBox.InsertString(19,"自动双胆合极限");
	m_ComboBox.InsertString(20,"自动双胆差极限");

	


}

void CDlgLianHaoHongQiu::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	if(!m_IsInitData)
	{
		m_IsInitData = true;
		OnBnClickedButton1();
		
	}
}

// 生成的消息映射函数
BOOL CDlgLianHaoHongQiu::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitListHeader();
	InitCombox();
	CenterWindow();
	return true;
}

void CDlgLianHaoHongQiu::OnClose()
{
	ShowWindow(SW_HIDE);
}

void CDlgLianHaoHongQiu::OnBnClickedSearchBtn()
{
	CString Text;
	GetDlgItem(IDC_EDIT1)->GetWindowText(Text);
	DWORD Data=::atoi(Text.GetBuffer());
	m_ListCtrl.DeleteAllItems();
	vector<sShuangSeQiu>* DataList = NULL;
	vector<sShuangSeQiu> Temp;
	if(Data == 0)
	{
		DataList=CDataManageCenter::GetInstance()->GetLianHaoHongQiu();
	}
	else
	{
		Temp=CDataManageCenter::GetInstance()->SearchLianHaoHongQiu(Data);
		DataList=&Temp;
	}

	for(int Index = 0; Index < (int)DataList->size(); Index++)
	{
		m_ListCtrl.InsertItem(Index,"");
		m_ListCtrl.SetItemText(Index,0,(*DataList)[Index].m_QiShu);
		for(int HongQiu=0; HongQiu < 6; HongQiu++)
		{
			CString Temp;
			Temp.Format("%d",(*DataList)[Index].m_HongQiu[HongQiu]);
			m_ListCtrl.SetItemText(Index,HongQiu+1,Temp);
		}

		CString HongQiuSum;
		HongQiuSum.Format("%d",(*DataList)[Index].m_HongQiuSum);
		m_ListCtrl.SetItemText(Index,7,HongQiuSum);

		CString LanQiu;
		LanQiu.Format("%d",(*DataList)[Index].m_LanQiu);
		m_ListCtrl.SetItemText(Index,8,LanQiu);
	}
}

void CDlgLianHaoHongQiu::AddFlag(CString& Str,bool IsTrue)
{
	if(IsTrue)
		Str+="S";
	else
		Str+="F";
}

//三胆V换算
int CDlgLianHaoHongQiu::TransDataByInt(CString DataStr,int Data2 )
{
	int TempData = atoi(DataStr.GetBuffer());
	DataStr.ReleaseBuffer();
	int Temp=TempData*Data2;
	return Temp%1000;
}

//三胆尾换算
int CDlgLianHaoHongQiu::TransDataByInt(CString DataStr)
{
    int TempData = atoi(DataStr.GetBuffer());
	DataStr.ReleaseBuffer();
	int Temp=TempData;
	return Temp%1000;
}

//双胆尾换算
int CDlgLianHaoHongQiu::TransDataByInt(CString DataStr,int Data2 ,int Data3)
{
	int TempData = atoi(DataStr.GetBuffer());
	DataStr.ReleaseBuffer();
	int Temp=TempData*Data2;
	if(Data3 != 0)
		Temp=Temp*Data3;

	return Temp%100;
}


CString CDlgLianHaoHongQiu::TransData(CString DataStr,float Data)
{
	int TempData = atoi(DataStr.GetBuffer());
	if(TempData == 0)
		return "";

	CString RetStr;

	float TempData2=(float)TempData*Data;
	RetStr.Format("%f",TempData2);
	RetStr=RetStr.Mid(RetStr.Find(".")+1,3);
	return RetStr;
}

void CDlgLianHaoHongQiu::OnBnClickedButton1()
{
	m_ListCtrl.ShowWindow(SW_SHOW);
	m_ListCtrl2.ShowWindow(SW_HIDE);
	m_ListCtrl3.ShowWindow(SW_HIDE);

	    m_ListCtrl.DeleteAllItems();
		m_ListCtrl.InsertItem(0,"");
		vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
		vector<sShuangSeQiu>* QiuShun=CDataManageCenter::GetInstance()->GetDataListByChuHao();


		m_ListCtrl.SetItemText(0,0,"期数");
		m_ListCtrl.SetItemText(0,1,"球顺前三V");
		m_ListCtrl.SetItemText(0,2,"球顺后三V");
		m_ListCtrl.SetItemText(0,3,"球前三V");
		m_ListCtrl.SetItemText(0,4,"球后三V");
		m_ListCtrl.SetItemText(0,5,"跨度");
		m_ListCtrl.SetItemText(0,6,"和尾");

		CString FilePath = GetAppCurrentPath()+_T("\\yaner.csv");
		HANDLE FileHandle=CreateFile(FilePath,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
		if(FileHandle == INVALID_HANDLE_VALUE)
		{
			AfxMessageBox(_T("打开文件失败！"));
			return;
		}

		CString WriteCSV="期数,球顺前三V, , ,球顺后三V, , ,球前三V, , ,球后三V, , ,跨度,和尾,球顺前三*3.14,球顺前三*6.18,球顺后三V*3.14,球顺后三V*6.18,球前三V*3.14,球前三V*6.18,球后三V*3.14,球后三V*6.18\n";
		for(int Index = 0; Index < (int)DataList->size(); Index++)
		{
			int InsertItemPos=Index+1;
			m_ListCtrl.InsertItem(InsertItemPos,"");

			CString ShunV;
			CString HouV;
			CString QiuV;
			CString QiuHouV;
			CString KuaDu;
			CString HeV;

			int VCount=0;

			CString ShunVCSV;
			CString HouVCSV;
			CString QiuVCSV;
			CString QiuHouVCSV;
			
			int TempArray[10];
			memset(TempArray,0,10*sizeof(int));

			for(int i=0; i < 6; i++)
			{
				int V=(*DataList)[Index].m_HongQiu[i]%10;
				int V2=(*QiuShun)[Index].m_HongQiu[i]%10;
				VCount+=V;
				TempArray[V]++;

				CString StrV;
				StrV.Format("%d",V);
				CString StrV2;
				StrV2.Format("%d",V2);
			
				if(i < 3)
				{
					QiuV+=StrV;
					ShunV+=StrV2;
					if(QiuVCSV.IsEmpty())
						QiuVCSV+=StrV;
					else 
						QiuVCSV+=","+StrV;
					if(ShunVCSV.IsEmpty())
						ShunVCSV+=StrV2;
					else
						ShunVCSV+=","+StrV2;
				}
				else
				{
					QiuHouV+=StrV;
					HouV+=StrV2;

					if(QiuHouVCSV.IsEmpty())
						QiuHouVCSV+=StrV;
					else 
						QiuHouVCSV+=","+StrV;
					if(HouVCSV.IsEmpty())
						HouVCSV+=StrV2;
					else
						HouVCSV+=","+StrV2;

				}
			}

			CString AllV;
			for(int j=0; j < 10; j++)
			{
				if(TempArray[j])
				{
					CString Temp;
					Temp.Format("%d",j);
					AllV+=Temp;
				}
			}
			HeV.Format("%d",VCount);
			KuaDu.Format("%d",(*DataList)[Index].m_HongQiu[5]-(*DataList)[Index].m_HongQiu[0]);

			CString TempCSV;
			CString QiShu=(*DataList)[Index].m_QiShu;
			if(QiShu.Find("\n")!=-1)
				QiShu=QiShu.Left(QiShu.Find("\n")-1);
			TempCSV=QiShu+","+ShunVCSV+","+HouVCSV+","+QiuVCSV+","+QiuHouVCSV+","+KuaDu+","+HeV;


			CString Temp=TransData(ShunV,3.14);
			TempCSV+=","+Temp;
			Temp=TransData(ShunV,6.18);
			TempCSV+=","+Temp;

			Temp=TransData(HouV,3.14);
			TempCSV+=","+Temp;

			Temp=TransData(HouV,6.18);
			TempCSV+=","+Temp;

			Temp=TransData(QiuV,3.14);
			TempCSV+=","+Temp;
			
			Temp=TransData(QiuV,6.18);
			TempCSV+=","+Temp;

			
			Temp=TransData(QiuHouV,3.14);
			TempCSV+=","+Temp;
			
			Temp=TransData(QiuHouV,6.18);
			TempCSV+=","+Temp;
			TempCSV+="\n";


			WriteCSV+=TempCSV;
			m_ListCtrl.SetItemText(InsertItemPos,0,(*DataList)[Index].m_QiShu);
			m_ListCtrl.SetItemText(InsertItemPos,1,ShunV);
			m_ListCtrl.SetItemText(InsertItemPos,2,HouV);
			m_ListCtrl.SetItemText(InsertItemPos,3,QiuV);
			m_ListCtrl.SetItemText(InsertItemPos,4,QiuHouV);
			m_ListCtrl.SetItemText(InsertItemPos,5,KuaDu);
			m_ListCtrl.SetItemText(InsertItemPos,6,HeV);
			m_ListCtrl.SetItemText(InsertItemPos,7,AllV);
		
		}

		
		DWORD WriteBytes=0;
		::WriteFile(FileHandle,WriteCSV.GetBuffer(),WriteCSV.GetLength(),&WriteBytes,NULL);
		WriteCSV.ReleaseBuffer();
		CloseHandle(FileHandle);
}

void CDlgLianHaoHongQiu::OnBnClickedButton2()
{
	m_ListCtrl.ShowWindow(SW_SHOW);
	m_ListCtrl2.ShowWindow(SW_HIDE);
	m_ListCtrl3.ShowWindow(SW_HIDE);

m_ListCtrl.DeleteAllItems();
		m_ListCtrl.InsertItem(0,"");
		vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
		vector<sShuangSeQiu>* QiuShun=CDataManageCenter::GetInstance()->GetDataListByChuHao();


		m_ListCtrl.SetItemText(0,0,"期数");
		m_ListCtrl.SetItemText(0,1,"球顺前三合");
		m_ListCtrl.SetItemText(0,2,"球顺后三合");
		m_ListCtrl.SetItemText(0,3,"球前三合");
		m_ListCtrl.SetItemText(0,4,"球后三合");
		m_ListCtrl.SetItemText(0,5,"跨度");
		m_ListCtrl.SetItemText(0,6,"和合");

		CString FilePath = GetAppCurrentPath()+_T("\\yaner_he.csv");
		HANDLE FileHandle=CreateFile(FilePath,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
		if(FileHandle == INVALID_HANDLE_VALUE)
		{
			AfxMessageBox(_T("打开文件失败！"));
			return;
		}

		CString WriteCSV="期数,球顺前三合, , ,球顺后三合, , ,球前三合, , ,球后三合, , ,跨度,和尾,球顺前三*3.14,球顺前三*6.18,球顺后三合*3.14,球顺后三合*6.18,球前三合*3.14,球前三合*6.18,球后三合*3.14,球后三合*6.18\n";
		for(int Index = 0; Index < (int)DataList->size(); Index++)
		{
			int InsertItemPos=Index+1;
			m_ListCtrl.InsertItem(InsertItemPos,"");

			CString ShunV;
			CString HouV;
			CString QiuV;
			CString QiuHouV;
			CString KuaDu;
			CString HeV;

			int VCount=0;

			CString ShunVCSV;
			CString HouVCSV;
			CString QiuVCSV;
			CString QiuHouVCSV;

			for(int i=0; i < 6; i++)
			{
				int V=(*DataList)[Index].m_HongQiu[i]%10+(*DataList)[Index].m_HongQiu[i]/10;
				V=V%10;
				int V2=(*QiuShun)[Index].m_HongQiu[i]%10+(*QiuShun)[Index].m_HongQiu[i]/10;
				V2=V2%10;
				VCount+=V;

				CString StrV;
				StrV.Format("%d",V);
				CString StrV2;
				StrV2.Format("%d",V2);
				if(i < 3)
				{
					QiuV+=StrV;
					ShunV+=StrV2;
					if(QiuVCSV.IsEmpty())
						QiuVCSV+=StrV;
					else 
						QiuVCSV+=","+StrV;
					if(ShunVCSV.IsEmpty())
						ShunVCSV+=StrV2;
					else
						ShunVCSV+=","+StrV2;
				}
				else
				{
					QiuHouV+=StrV;
					HouV+=StrV2;

					if(QiuHouVCSV.IsEmpty())
						QiuHouVCSV+=StrV;
					else 
						QiuHouVCSV+=","+StrV;
					if(HouVCSV.IsEmpty())
						HouVCSV+=StrV2;
					else
						HouVCSV+=","+StrV2;

				}
			}

			HeV.Format("%d",VCount);
			KuaDu.Format("%d",(*DataList)[Index].m_HongQiu[5]-(*DataList)[Index].m_HongQiu[0]);

			CString TempCSV;
			CString QiShu=(*DataList)[Index].m_QiShu;
			if(QiShu.Find("\n")!=-1)
				QiShu=QiShu.Left(QiShu.Find("\n")-1);
			TempCSV=QiShu+","+ShunVCSV+","+HouVCSV+","+QiuVCSV+","+QiuHouVCSV+","+KuaDu+","+HeV;

			CString Temp=TransData(ShunV,3.14);
			TempCSV+=","+Temp;
			Temp=TransData(ShunV,6.18);
			TempCSV+=","+Temp;

			Temp=TransData(HouV,3.14);
			TempCSV+=","+Temp;

			Temp=TransData(HouV,6.18);
			TempCSV+=","+Temp;

			Temp=TransData(QiuV,3.14);
			TempCSV+=","+Temp;
			
			Temp=TransData(QiuV,6.18);
			TempCSV+=","+Temp;

			
			Temp=TransData(QiuHouV,3.14);
			TempCSV+=","+Temp;
			
			Temp=TransData(QiuHouV,6.18);
			TempCSV+=","+Temp;
			TempCSV+="\n";



			WriteCSV+=TempCSV;
			m_ListCtrl.SetItemText(InsertItemPos,0,(*DataList)[Index].m_QiShu);
			m_ListCtrl.SetItemText(InsertItemPos,1,ShunV);
			m_ListCtrl.SetItemText(InsertItemPos,2,HouV);
			m_ListCtrl.SetItemText(InsertItemPos,3,QiuV);
			m_ListCtrl.SetItemText(InsertItemPos,4,QiuHouV);
			m_ListCtrl.SetItemText(InsertItemPos,5,KuaDu);
			m_ListCtrl.SetItemText(InsertItemPos,6,HeV);
		
		}

		
		DWORD WriteBytes=0;
		::WriteFile(FileHandle,WriteCSV.GetBuffer(),WriteCSV.GetLength(),&WriteBytes,NULL);
		WriteCSV.ReleaseBuffer();
		CloseHandle(FileHandle);
}

void CDlgLianHaoHongQiu::OnBnClickedWeiFenBtn()
{
	m_ListCtrl.ShowWindow(SW_HIDE);
	m_ListCtrl2.ShowWindow(SW_SHOW);
	m_ListCtrl3.ShowWindow(SW_HIDE);

	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;
	Style.m_DrawData.m_TextData.m_IsFillBG=true;

	COLORREF Yelow=RGB(255,192,0);
	COLORREF ZiSe=RGB(112,48,160);
	COLORREF Write=RGB(255,255,255);
	COLORREF Red=RGB(255,0,0);

	    m_ListCtrl2.DeleteAllItems();
		m_ListCtrl2.InsertItem(0,"");
		vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
		vector<sShuangSeQiu>* QiuShun=CDataManageCenter::GetInstance()->GetDataListByChuHao();

		
		CString WriteCSV="期数,球顺前三V, , ,球顺后三V, , ,球前三V, , ,球后三V, , ,跨度,和尾,球顺前三*3.14,球顺前三*6.18,球顺后三V*3.14,球顺后三V*6.18,球前三V*3.14,球前三V*6.18,球后三V*3.14,球后三V*6.18\n";
		for(int Index = 0; Index < (int)DataList->size(); Index++)
		{
			
			m_ListCtrl2.InsertItem(Index,"");

			CString ShunV;
			CString HouV;
			CString QiuV;
			CString QiuHouV;
			CString KuaDu;
			CString HeV;

			int VCount=0;

			CString ShunVCSV;
			CString HouVCSV;
			CString QiuVCSV;
			CString QiuHouVCSV;

			vector<int> ShunVInt;
			vector<int> HouVInt;
			vector<int> QiuVInt;
			vector<int> QiuHouVInt;
			
			int TempArray[10];
			memset(TempArray,0,10*sizeof(int));

			for(int i=0; i < 6; i++)
			{
				int V=(*DataList)[Index].m_HongQiu[i]%10;
				int V2=(*QiuShun)[Index].m_HongQiu[i]%10;
				VCount+=V;
				TempArray[V]++;

				CString StrV;
				StrV.Format("%d",V);
				CString StrV2;
				StrV2.Format("%d",V2);
			
				if(i < 3)
				{
					QiuV+=StrV;
					ShunV+=StrV2;

					ShunVInt.push_back(V2);
					QiuVInt.push_back(V);

					if(QiuVCSV.IsEmpty())
						QiuVCSV+=StrV;
					else 
						QiuVCSV+=","+StrV;
					if(ShunVCSV.IsEmpty())
						ShunVCSV+=StrV2;
					else
						ShunVCSV+=","+StrV2;
				}
				else
				{
					QiuHouV+=StrV;
					HouV+=StrV2;

					HouVInt.push_back(V2);
					QiuHouVInt.push_back(V);

					if(QiuHouVCSV.IsEmpty())
						QiuHouVCSV+=StrV;
					else 
						QiuHouVCSV+=","+StrV;
					if(HouVCSV.IsEmpty())
						HouVCSV+=StrV2;
					else
						HouVCSV+=","+StrV2;

				}
			}

			CString AllV;
			for(int j=0; j < 10; j++)
			{
				if(TempArray[j])
				{
					CString Temp;
					Temp.Format("%d",j);
					AllV+=Temp;
				}
			}

			
			
			int List2Index=0;

			m_ListCtrl2.SetItemText(Index,List2Index,(*DataList)[Index].m_QiShu+" "+AllV);
			List2Index++;
			bool IsWrite=false;

			int HeCount=0;
			int KuaDuCount=0;
			int MaxData=0;
			int MinData=100;

			for(int j=0; j < ShunVInt.size(); j++)
			{
				CString Str;
				Str.Format("%d",ShunVInt[j]);
				m_ListCtrl2.SetItemText(Index,List2Index,Str);
				IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],ShunVInt[j],true);
				if(IsWrite)
					Style.m_DrawData.m_TextData.m_BGColor = Write;
				else
					Style.m_DrawData.m_TextData.m_BGColor = ZiSe;

				m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);

				HeCount+=ShunVInt[j];
				if(MaxData < ShunVInt[j])
					MaxData=ShunVInt[j];
				
				if(MinData > ShunVInt[j])
					MinData=ShunVInt[j];

				List2Index++;
			}

			KuaDuCount=MaxData-MinData;
			CString TempHe;
			CString TempKuai;
			TempHe.Format("%d",HeCount);
			TempKuai.Format("%d",KuaDuCount);

			m_ListCtrl2.SetItemText(Index,List2Index,TempKuai);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],KuaDuCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;

			m_ListCtrl2.SetItemText(Index,List2Index,TempHe);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
			{

				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;

				bool IsWrite1 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount/10,true);
				bool IsWrite2 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount%10,true);

				if(!IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Yelow;

				if(!IsWrite1 &&  IsWrite2 || IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Red;

					
			}
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;

			HeCount=0;
			KuaDuCount=0;
			MaxData=0;
			MinData=100;
			TempHe.Empty();
			TempKuai.Empty();

			for(int j=0; j < HouVInt.size(); j++)
			{
				CString Str;
				Str.Format("%d",HouVInt[j]);
				m_ListCtrl2.SetItemText(Index,List2Index,Str);

				IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HouVInt[j],true);
				if(IsWrite)
					Style.m_DrawData.m_TextData.m_BGColor = Write;
				else
					Style.m_DrawData.m_TextData.m_BGColor = ZiSe;

				m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);

				HeCount+=HouVInt[j];
				if(MaxData < HouVInt[j])
					MaxData=HouVInt[j];
				
				if(MinData > HouVInt[j])
					MinData=HouVInt[j];

				List2Index++;
			}

			KuaDuCount=MaxData-MinData;
			TempHe.Format("%d",HeCount);
			TempKuai.Format("%d",KuaDuCount);

			m_ListCtrl2.SetItemText(Index,List2Index,TempKuai);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],KuaDuCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;
			m_ListCtrl2.SetItemText(Index,List2Index,TempHe);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
			{

				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;

				bool IsWrite1 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount/10,true);
				bool IsWrite2 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount%10,true);

				if(!IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Yelow;

				if(!IsWrite1 &&  IsWrite2 || IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Red;

					
			}
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;

			HeCount=0;
			KuaDuCount=0;
			MaxData=0;
			MinData=100;
			TempHe.Empty();
			TempKuai.Empty();
			for(int j=0; j < QiuVInt.size(); j++)
			{
				CString Str;
				Str.Format("%d",QiuVInt[j]);
				m_ListCtrl2.SetItemText(Index,List2Index,Str);

				IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],QiuVInt[j],true);
				if(IsWrite)
					Style.m_DrawData.m_TextData.m_BGColor = Write;
				else
					Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
				m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);

				HeCount+= QiuVInt[j];
				if(MaxData <  QiuVInt[j])
					MaxData= QiuVInt[j];
				
				if(MinData >  QiuVInt[j])
					MinData= QiuVInt[j];
				List2Index++;
			}

			KuaDuCount=MaxData-MinData;
			TempHe.Format("%d",HeCount);
			TempKuai.Format("%d",KuaDuCount);

			m_ListCtrl2.SetItemText(Index,List2Index,TempKuai);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],KuaDuCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
		
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;

			m_ListCtrl2.SetItemText(Index,List2Index,TempHe);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
			{

				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;

				bool IsWrite1 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount/10,true);
				bool IsWrite2 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount%10,true);

				if(!IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Yelow;

				if(!IsWrite1 &&  IsWrite2 || IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Red;

					
			}

			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;


			HeCount=0;
			KuaDuCount=0;
			MaxData=0;
			MinData=100;
			TempHe.Empty();
			TempKuai.Empty();
			for(int j=0; j < QiuHouVInt.size(); j++)
			{
				CString Str;
				Str.Format("%d",QiuHouVInt[j]);
				m_ListCtrl2.SetItemText(Index,List2Index,Str);

				IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],QiuHouVInt[j],true);
				if(IsWrite)
					Style.m_DrawData.m_TextData.m_BGColor = Write;
				else
					Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
				m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);

				HeCount+=QiuHouVInt[j];
				if(MaxData < QiuHouVInt[j])
					MaxData=QiuHouVInt[j];
				
				if(MinData > QiuHouVInt[j])
					MinData=QiuHouVInt[j];

				List2Index++;
			}

			KuaDuCount=MaxData-MinData;
			TempHe.Format("%d",HeCount);
			TempKuai.Format("%d",KuaDuCount);

			m_ListCtrl2.SetItemText(Index,List2Index,TempKuai);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],KuaDuCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
		
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;

			m_ListCtrl2.SetItemText(Index,List2Index,TempHe);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
			{

				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;

				bool IsWrite1 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount/10,true);
				bool IsWrite2 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount%10,true);

				if(!IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Yelow;

				if(!IsWrite1 &&  IsWrite2 || IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Red;

					
			}

			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;

			HeCount=0;
			KuaDuCount=0;
			MaxData=0;
			MinData=100;
			TempHe.Empty();
			TempKuai.Empty();


			int TempData=TransDataByInt(ShunV,314);
			int TempData2=TempData/100;

			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;

			CString Str;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			Str.Empty();
			List2Index++;

			
			TempData2=TempData/10%10;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;

			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			Str.Empty();
			List2Index++;

			TempData2=TempData%10;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;

			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			Str.Empty();
			List2Index++;

			KuaDuCount=MaxData-MinData;
			TempHe.Format("%d",HeCount);
			TempKuai.Format("%d",KuaDuCount);

			m_ListCtrl2.SetItemText(Index,List2Index,TempKuai);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],KuaDuCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
		
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;

			m_ListCtrl2.SetItemText(Index,List2Index,TempHe);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
			{

				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;

				bool IsWrite1 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount/10,true);
				bool IsWrite2 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount%10,true);

				if(!IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Yelow;

				if(!IsWrite1 &&  IsWrite2 || IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Red;

					
			}

			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;

			
			HeCount=0;
			KuaDuCount=0;
			MaxData=0;
			MinData=100;
			TempHe.Empty();
			TempKuai.Empty();


			TempData=TransDataByInt(ShunV,618);
			TempData2=TempData/100;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			Str.Empty();
			List2Index++;

			
			TempData2=TempData/10%10;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			Str.Empty();
			List2Index++;

			TempData2=TempData%10;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);

			List2Index++;
			Str.Empty();

			KuaDuCount=MaxData-MinData;
			TempHe.Format("%d",HeCount);
			TempKuai.Format("%d",KuaDuCount);

			m_ListCtrl2.SetItemText(Index,List2Index,TempKuai);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],KuaDuCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
		
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;

			m_ListCtrl2.SetItemText(Index,List2Index,TempHe);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
			{

				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;

				bool IsWrite1 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount/10,true);
				bool IsWrite2 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount%10,true);

				if(!IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Yelow;

				if(!IsWrite1 &&  IsWrite2 || IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Red;

					
			}

			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;
			Str.Empty();




			//
			HeCount=0;
			KuaDuCount=0;
			MaxData=0;
			MinData=100;
			TempHe.Empty();
			TempKuai.Empty();


			TempData=TransDataByInt(HouV,314);
			TempData2=TempData/100;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			Str.Empty();
			List2Index++;

			
			TempData2=TempData/10%10;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			Str.Empty();
			List2Index++;

			TempData2=TempData%10;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);

			List2Index++;
			Str.Empty();

			KuaDuCount=MaxData-MinData;
			TempHe.Format("%d",HeCount);
			TempKuai.Format("%d",KuaDuCount);

			m_ListCtrl2.SetItemText(Index,List2Index,TempKuai);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],KuaDuCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
		
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;

			m_ListCtrl2.SetItemText(Index,List2Index,TempHe);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
			{

				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;

				bool IsWrite1 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount/10,true);
				bool IsWrite2 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount%10,true);

				if(!IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Yelow;

				if(!IsWrite1 &&  IsWrite2 || IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Red;

					
			}

			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;
			Str.Empty();
		


			//
			HeCount=0;
			KuaDuCount=0;
			MaxData=0;
			MinData=100;
			TempHe.Empty();
			TempKuai.Empty();


			TempData=TransDataByInt(HouV,618);
			TempData2=TempData/100;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			Str.Empty();
			List2Index++;

			
			TempData2=TempData/10%10;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			Str.Empty();
			List2Index++;

			TempData2=TempData%10;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);

			List2Index++;
			Str.Empty();

			KuaDuCount=MaxData-MinData;
			TempHe.Format("%d",HeCount);
			TempKuai.Format("%d",KuaDuCount);

			m_ListCtrl2.SetItemText(Index,List2Index,TempKuai);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],KuaDuCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
		
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;

			m_ListCtrl2.SetItemText(Index,List2Index,TempHe);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
			{

				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;

				bool IsWrite1 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount/10,true);
				bool IsWrite2 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount%10,true);

				if(!IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Yelow;

				if(!IsWrite1 &&  IsWrite2 || IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Red;

					
			}

			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;
			Str.Empty();


			//
			HeCount=0;
			KuaDuCount=0;
			MaxData=0;
			MinData=100;
			TempHe.Empty();
			TempKuai.Empty();


			TempData=TransDataByInt(QiuV,314);
			TempData2=TempData/100;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			Str.Empty();
			List2Index++;

			
			TempData2=TempData/10%10;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			Str.Empty();
			List2Index++;

			TempData2=TempData%10;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);

			List2Index++;
			Str.Empty();

			KuaDuCount=MaxData-MinData;
			TempHe.Format("%d",HeCount);
			TempKuai.Format("%d",KuaDuCount);

			m_ListCtrl2.SetItemText(Index,List2Index,TempKuai);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],KuaDuCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
		
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;

			m_ListCtrl2.SetItemText(Index,List2Index,TempHe);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
			{

				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;

				bool IsWrite1 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount/10,true);
				bool IsWrite2 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount%10,true);

				if(!IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Yelow;

				if(!IsWrite1 &&  IsWrite2 || IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Red;

					
			}

			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;
			Str.Empty();


			HeCount=0;
			KuaDuCount=0;
			MaxData=0;
			MinData=100;
			TempHe.Empty();
			TempKuai.Empty();


			TempData=TransDataByInt(QiuV,618);
			TempData2=TempData/100;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			Str.Empty();
			List2Index++;

			
			TempData2=TempData/10%10;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			Str.Empty();
			List2Index++;

			TempData2=TempData%10;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);

			List2Index++;
			Str.Empty();

			KuaDuCount=MaxData-MinData;
			TempHe.Format("%d",HeCount);
			TempKuai.Format("%d",KuaDuCount);

			m_ListCtrl2.SetItemText(Index,List2Index,TempKuai);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],KuaDuCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
		
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;

			m_ListCtrl2.SetItemText(Index,List2Index,TempHe);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
			{

				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;

				bool IsWrite1 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount/10,true);
				bool IsWrite2 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount%10,true);

				if(!IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Yelow;

				if(!IsWrite1 &&  IsWrite2 || IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Red;

					
			}

			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;
			Str.Empty();


			//
			
			HeCount=0;
			KuaDuCount=0;
			MaxData=0;
			MinData=100;
			TempHe.Empty();
			TempKuai.Empty();


			TempData=TransDataByInt(QiuHouV,314);
			TempData2=TempData/100;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			Str.Empty();
			List2Index++;

			
			TempData2=TempData/10%10;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			Str.Empty();
			List2Index++;

			TempData2=TempData%10;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);

			List2Index++;
			Str.Empty();

			KuaDuCount=MaxData-MinData;
			TempHe.Format("%d",HeCount);
			TempKuai.Format("%d",KuaDuCount);

			m_ListCtrl2.SetItemText(Index,List2Index,TempKuai);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],KuaDuCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
		
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;

			m_ListCtrl2.SetItemText(Index,List2Index,TempHe);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
			{

				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;

				bool IsWrite1 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount/10,true);
				bool IsWrite2 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount%10,true);

				if(!IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Yelow;

				if(!IsWrite1 &&  IsWrite2 || IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Red;

					
			}

			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;
			Str.Empty();

			//
			HeCount=0;
			KuaDuCount=0;
			MaxData=0;
			MinData=100;
			TempHe.Empty();
			TempKuai.Empty();


			TempData=TransDataByInt(QiuHouV,618);
			TempData2=TempData/100;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			Str.Empty();
			List2Index++;

			
			TempData2=TempData/10%10;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			Str.Empty();
			List2Index++;

			TempData2=TempData%10;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);

			List2Index++;
			Str.Empty();

			KuaDuCount=MaxData-MinData;
			TempHe.Format("%d",HeCount);
			TempKuai.Format("%d",KuaDuCount);

			m_ListCtrl2.SetItemText(Index,List2Index,TempKuai);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],KuaDuCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
		
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;

			m_ListCtrl2.SetItemText(Index,List2Index,TempHe);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
			{

				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;

				bool IsWrite1 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount/10,true);
				bool IsWrite2 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],HeCount%10,true);

				if(!IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Yelow;

				if(!IsWrite1 &&  IsWrite2 || IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Red;

					
			}

			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;
			Str.Empty();
		
		}

}

void CDlgLianHaoHongQiu::OnBnClickedHeFenBtn()
{
	m_ListCtrl.ShowWindow(SW_HIDE);
	m_ListCtrl2.ShowWindow(SW_SHOW);
	m_ListCtrl3.ShowWindow(SW_HIDE);

	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;
	Style.m_DrawData.m_TextData.m_IsFillBG=true;

	COLORREF Yelow=RGB(255,192,0);
	COLORREF ZiSe=RGB(112,48,160);
	COLORREF Write=RGB(255,255,255);
	COLORREF Red=RGB(255,0,0);

	    m_ListCtrl2.DeleteAllItems();
		m_ListCtrl2.InsertItem(0,"");
		vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
		vector<sShuangSeQiu>* QiuShun=CDataManageCenter::GetInstance()->GetDataListByChuHao();

		
		CString WriteCSV="期数,球顺前三V, , ,球顺后三V, , ,球前三V, , ,球后三V, , ,跨度,和尾,球顺前三*3.14,球顺前三*6.18,球顺后三V*3.14,球顺后三V*6.18,球前三V*3.14,球前三V*6.18,球后三V*3.14,球后三V*6.18\n";
		for(int Index = 0; Index < (int)DataList->size(); Index++)
		{
			
			m_ListCtrl2.InsertItem(Index,"");

			CString ShunV;
			CString HouV;
			CString QiuV;
			CString QiuHouV;
			CString KuaDu;
			CString HeV;

			int VCount=0;

			CString ShunVCSV;
			CString HouVCSV;
			CString QiuVCSV;
			CString QiuHouVCSV;

			vector<int> ShunVInt;
			vector<int> HouVInt;
			vector<int> QiuVInt;
			vector<int> QiuHouVInt;
			
			int TempArray[10];
			memset(TempArray,0,10*sizeof(int));

			for(int i=0; i < 6; i++)
			{
				int V=(*DataList)[Index].m_HongQiu[i]%10+(*DataList)[Index].m_HongQiu[i]/10;
				V=V%10;
				int V2=(*QiuShun)[Index].m_HongQiu[i]%10+(*QiuShun)[Index].m_HongQiu[i]/10;
				V2=V2%10;
				VCount+=V;
				TempArray[V]++;

				CString StrV;
				StrV.Format("%d",V);
				CString StrV2;
				StrV2.Format("%d",V2);
			
				if(i < 3)
				{
					QiuV+=StrV;
					ShunV+=StrV2;

					ShunVInt.push_back(V2);
					QiuVInt.push_back(V);

					if(QiuVCSV.IsEmpty())
						QiuVCSV+=StrV;
					else 
						QiuVCSV+=","+StrV;
					if(ShunVCSV.IsEmpty())
						ShunVCSV+=StrV2;
					else
						ShunVCSV+=","+StrV2;
				}
				else
				{
					QiuHouV+=StrV;
					HouV+=StrV2;

					HouVInt.push_back(V2);
					QiuHouVInt.push_back(V);

					if(QiuHouVCSV.IsEmpty())
						QiuHouVCSV+=StrV;
					else 
						QiuHouVCSV+=","+StrV;
					if(HouVCSV.IsEmpty())
						HouVCSV+=StrV2;
					else
						HouVCSV+=","+StrV2;

				}
			}

			CString AllV;
			for(int j=0; j < 10; j++)
			{
				if(TempArray[j])
				{
					CString Temp;
					Temp.Format("%d",j);
					AllV+=Temp;
				}
			}

			
			
			int List2Index=0;

			m_ListCtrl2.SetItemText(Index,List2Index,(*DataList)[Index].m_QiShu+" "+AllV);
			List2Index++;
			bool IsWrite=false;

			int HeCount=0;
			int KuaDuCount=0;
			int MaxData=0;
			int MinData=100;

			for(int j=0; j < ShunVInt.size(); j++)
			{
				CString Str;
				Str.Format("%d",ShunVInt[j]);
				m_ListCtrl2.SetItemText(Index,List2Index,Str);
				IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],ShunVInt[j],true);
				if(IsWrite)
					Style.m_DrawData.m_TextData.m_BGColor = Write;
				else
					Style.m_DrawData.m_TextData.m_BGColor = ZiSe;

				m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);

				HeCount+=ShunVInt[j];
				if(MaxData < ShunVInt[j])
					MaxData=ShunVInt[j];
				
				if(MinData > ShunVInt[j])
					MinData=ShunVInt[j];

				List2Index++;
			}

			KuaDuCount=MaxData-MinData;
			CString TempHe;
			CString TempKuai;
			TempHe.Format("%d",HeCount);
			TempKuai.Format("%d",KuaDuCount);

			m_ListCtrl2.SetItemText(Index,List2Index,TempKuai);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],KuaDuCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;

			m_ListCtrl2.SetItemText(Index,List2Index,TempHe);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
			{

				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;

				bool IsWrite1 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount/10,true);
				bool IsWrite2 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount%10,true);

				if(!IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Yelow;

				if(!IsWrite1 &&  IsWrite2 || IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Red;

					
			}
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;

			HeCount=0;
			KuaDuCount=0;
			MaxData=0;
			MinData=100;
			TempHe.Empty();
			TempKuai.Empty();

			for(int j=0; j < HouVInt.size(); j++)
			{
				CString Str;
				Str.Format("%d",HouVInt[j]);
				m_ListCtrl2.SetItemText(Index,List2Index,Str);

				IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HouVInt[j],true);
				if(IsWrite)
					Style.m_DrawData.m_TextData.m_BGColor = Write;
				else
					Style.m_DrawData.m_TextData.m_BGColor = ZiSe;

				m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);

				HeCount+=HouVInt[j];
				if(MaxData < HouVInt[j])
					MaxData=HouVInt[j];
				
				if(MinData > HouVInt[j])
					MinData=HouVInt[j];

				List2Index++;
			}

			KuaDuCount=MaxData-MinData;
			TempHe.Format("%d",HeCount);
			TempKuai.Format("%d",KuaDuCount);

			m_ListCtrl2.SetItemText(Index,List2Index,TempKuai);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],KuaDuCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;
			m_ListCtrl2.SetItemText(Index,List2Index,TempHe);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
			{

				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;

				bool IsWrite1 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount/10,true);
				bool IsWrite2 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount%10,true);

				if(!IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Yelow;

				if(!IsWrite1 &&  IsWrite2 || IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Red;

					
			}
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;

			HeCount=0;
			KuaDuCount=0;
			MaxData=0;
			MinData=100;
			TempHe.Empty();
			TempKuai.Empty();
			for(int j=0; j < QiuVInt.size(); j++)
			{
				CString Str;
				Str.Format("%d",QiuVInt[j]);
				m_ListCtrl2.SetItemText(Index,List2Index,Str);

				IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],QiuVInt[j],true);
				if(IsWrite)
					Style.m_DrawData.m_TextData.m_BGColor = Write;
				else
					Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
				m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);

				HeCount+= QiuVInt[j];
				if(MaxData <  QiuVInt[j])
					MaxData= QiuVInt[j];
				
				if(MinData >  QiuVInt[j])
					MinData= QiuVInt[j];
				List2Index++;
			}

			KuaDuCount=MaxData-MinData;
			TempHe.Format("%d",HeCount);
			TempKuai.Format("%d",KuaDuCount);

			m_ListCtrl2.SetItemText(Index,List2Index,TempKuai);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],KuaDuCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
		
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;

			m_ListCtrl2.SetItemText(Index,List2Index,TempHe);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
			{

				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;

				bool IsWrite1 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount/10,true);
				bool IsWrite2 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount%10,true);

				if(!IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Yelow;

				if(!IsWrite1 &&  IsWrite2 || IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Red;

					
			}

			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;


			HeCount=0;
			KuaDuCount=0;
			MaxData=0;
			MinData=100;
			TempHe.Empty();
			TempKuai.Empty();
			for(int j=0; j < QiuHouVInt.size(); j++)
			{
				CString Str;
				Str.Format("%d",QiuHouVInt[j]);
				m_ListCtrl2.SetItemText(Index,List2Index,Str);

				IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],QiuHouVInt[j],true);
				if(IsWrite)
					Style.m_DrawData.m_TextData.m_BGColor = Write;
				else
					Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
				m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);

				HeCount+=QiuHouVInt[j];
				if(MaxData < QiuHouVInt[j])
					MaxData=QiuHouVInt[j];
				
				if(MinData > QiuHouVInt[j])
					MinData=QiuHouVInt[j];

				List2Index++;
			}

			KuaDuCount=MaxData-MinData;
			TempHe.Format("%d",HeCount);
			TempKuai.Format("%d",KuaDuCount);

			m_ListCtrl2.SetItemText(Index,List2Index,TempKuai);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],KuaDuCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
		
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;

			m_ListCtrl2.SetItemText(Index,List2Index,TempHe);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
			{

				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;

				bool IsWrite1 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount/10,true);
				bool IsWrite2 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount%10,true);

				if(!IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Yelow;

				if(!IsWrite1 &&  IsWrite2 || IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Red;

					
			}

			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;

			HeCount=0;
			KuaDuCount=0;
			MaxData=0;
			MinData=100;
			TempHe.Empty();
			TempKuai.Empty();


			int TempData=TransDataByInt(ShunV,314);
			int TempData2=TempData/100;

			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;

			CString Str;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			Str.Empty();
			List2Index++;

			
			TempData2=TempData/10%10;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;

			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			Str.Empty();
			List2Index++;

			TempData2=TempData%10;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;

			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			Str.Empty();
			List2Index++;

			KuaDuCount=MaxData-MinData;
			TempHe.Format("%d",HeCount);
			TempKuai.Format("%d",KuaDuCount);

			m_ListCtrl2.SetItemText(Index,List2Index,TempKuai);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],KuaDuCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
		
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;

			m_ListCtrl2.SetItemText(Index,List2Index,TempHe);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
			{

				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;

				bool IsWrite1 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount/10,true);
				bool IsWrite2 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount%10,true);

				if(!IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Yelow;

				if(!IsWrite1 &&  IsWrite2 || IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Red;

					
			}

			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;

			
			HeCount=0;
			KuaDuCount=0;
			MaxData=0;
			MinData=100;
			TempHe.Empty();
			TempKuai.Empty();


			TempData=TransDataByInt(ShunV,618);
			TempData2=TempData/100;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			Str.Empty();
			List2Index++;

			
			TempData2=TempData/10%10;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			Str.Empty();
			List2Index++;

			TempData2=TempData%10;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);

			List2Index++;
			Str.Empty();

			KuaDuCount=MaxData-MinData;
			TempHe.Format("%d",HeCount);
			TempKuai.Format("%d",KuaDuCount);

			m_ListCtrl2.SetItemText(Index,List2Index,TempKuai);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],KuaDuCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
		
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;

			m_ListCtrl2.SetItemText(Index,List2Index,TempHe);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
			{

				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;

				bool IsWrite1 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount/10,true);
				bool IsWrite2 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount%10,true);

				if(!IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Yelow;

				if(!IsWrite1 &&  IsWrite2 || IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Red;

					
			}

			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;
			Str.Empty();




			//
			HeCount=0;
			KuaDuCount=0;
			MaxData=0;
			MinData=100;
			TempHe.Empty();
			TempKuai.Empty();


			TempData=TransDataByInt(HouV,314);
			TempData2=TempData/100;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			Str.Empty();
			List2Index++;

			
			TempData2=TempData/10%10;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			Str.Empty();
			List2Index++;

			TempData2=TempData%10;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);

			List2Index++;
			Str.Empty();

			KuaDuCount=MaxData-MinData;
			TempHe.Format("%d",HeCount);
			TempKuai.Format("%d",KuaDuCount);

			m_ListCtrl2.SetItemText(Index,List2Index,TempKuai);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],KuaDuCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
		
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;

			m_ListCtrl2.SetItemText(Index,List2Index,TempHe);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
			{

				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;

				bool IsWrite1 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount/10,true);
				bool IsWrite2 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount%10,true);

				if(!IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Yelow;

				if(!IsWrite1 &&  IsWrite2 || IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Red;

					
			}

			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;
			Str.Empty();
		


			//
			HeCount=0;
			KuaDuCount=0;
			MaxData=0;
			MinData=100;
			TempHe.Empty();
			TempKuai.Empty();


			TempData=TransDataByInt(HouV,618);
			TempData2=TempData/100;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			Str.Empty();
			List2Index++;

			
			TempData2=TempData/10%10;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			Str.Empty();
			List2Index++;

			TempData2=TempData%10;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);

			List2Index++;
			Str.Empty();

			KuaDuCount=MaxData-MinData;
			TempHe.Format("%d",HeCount);
			TempKuai.Format("%d",KuaDuCount);

			m_ListCtrl2.SetItemText(Index,List2Index,TempKuai);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],KuaDuCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
		
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;

			m_ListCtrl2.SetItemText(Index,List2Index,TempHe);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
			{

				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;

				bool IsWrite1 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount/10,true);
				bool IsWrite2 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount%10,true);

				if(!IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Yelow;

				if(!IsWrite1 &&  IsWrite2 || IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Red;

					
			}

			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;
			Str.Empty();


			//
			HeCount=0;
			KuaDuCount=0;
			MaxData=0;
			MinData=100;
			TempHe.Empty();
			TempKuai.Empty();


			TempData=TransDataByInt(QiuV,314);
			TempData2=TempData/100;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			Str.Empty();
			List2Index++;

			
			TempData2=TempData/10%10;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			Str.Empty();
			List2Index++;

			TempData2=TempData%10;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);

			List2Index++;
			Str.Empty();

			KuaDuCount=MaxData-MinData;
			TempHe.Format("%d",HeCount);
			TempKuai.Format("%d",KuaDuCount);

			m_ListCtrl2.SetItemText(Index,List2Index,TempKuai);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],KuaDuCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
		
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;

			m_ListCtrl2.SetItemText(Index,List2Index,TempHe);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
			{

				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;

				bool IsWrite1 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount/10,true);
				bool IsWrite2 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount%10,true);

				if(!IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Yelow;

				if(!IsWrite1 &&  IsWrite2 || IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Red;

					
			}

			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;
			Str.Empty();


			HeCount=0;
			KuaDuCount=0;
			MaxData=0;
			MinData=100;
			TempHe.Empty();
			TempKuai.Empty();


			TempData=TransDataByInt(QiuV,618);
			TempData2=TempData/100;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			Str.Empty();
			List2Index++;

			
			TempData2=TempData/10%10;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			Str.Empty();
			List2Index++;

			TempData2=TempData%10;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);

			List2Index++;
			Str.Empty();

			KuaDuCount=MaxData-MinData;
			TempHe.Format("%d",HeCount);
			TempKuai.Format("%d",KuaDuCount);

			m_ListCtrl2.SetItemText(Index,List2Index,TempKuai);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],KuaDuCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
		
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;

			m_ListCtrl2.SetItemText(Index,List2Index,TempHe);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
			{

				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;

				bool IsWrite1 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount/10,true);
				bool IsWrite2 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount%10,true);

				if(!IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Yelow;

				if(!IsWrite1 &&  IsWrite2 || IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Red;

					
			}

			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;
			Str.Empty();


			//
			
			HeCount=0;
			KuaDuCount=0;
			MaxData=0;
			MinData=100;
			TempHe.Empty();
			TempKuai.Empty();


			TempData=TransDataByInt(QiuHouV,314);
			TempData2=TempData/100;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			Str.Empty();
			List2Index++;

			
			TempData2=TempData/10%10;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			Str.Empty();
			List2Index++;

			TempData2=TempData%10;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);

			List2Index++;
			Str.Empty();

			KuaDuCount=MaxData-MinData;
			TempHe.Format("%d",HeCount);
			TempKuai.Format("%d",KuaDuCount);

			m_ListCtrl2.SetItemText(Index,List2Index,TempKuai);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],KuaDuCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
		
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;

			m_ListCtrl2.SetItemText(Index,List2Index,TempHe);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
			{

				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;

				bool IsWrite1 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount/10,true);
				bool IsWrite2 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount%10,true);

				if(!IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Yelow;

				if(!IsWrite1 &&  IsWrite2 || IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Red;

					
			}

			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;
			Str.Empty();

			//
			HeCount=0;
			KuaDuCount=0;
			MaxData=0;
			MinData=100;
			TempHe.Empty();
			TempKuai.Empty();


			TempData=TransDataByInt(QiuHouV,618);
			TempData2=TempData/100;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			Str.Empty();
			List2Index++;

			
			TempData2=TempData/10%10;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			Str.Empty();
			List2Index++;

			TempData2=TempData%10;
			HeCount+=TempData2;
			if(MaxData < TempData2)
				MaxData=TempData2;
				
			if(MinData > TempData2)
				MinData=TempData2;
			Str.Format("%d",TempData2);
			m_ListCtrl2.SetItemText(Index,List2Index,Str);

			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],TempData2,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);

			List2Index++;
			Str.Empty();

			KuaDuCount=MaxData-MinData;
			TempHe.Format("%d",HeCount);
			TempKuai.Format("%d",KuaDuCount);

			m_ListCtrl2.SetItemText(Index,List2Index,TempKuai);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],KuaDuCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
		
			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;

			m_ListCtrl2.SetItemText(Index,List2Index,TempHe);
			IsWrite = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount,true);
			if(IsWrite)
				Style.m_DrawData.m_TextData.m_BGColor = Write;
			else
			{

				Style.m_DrawData.m_TextData.m_BGColor = ZiSe;

				bool IsWrite1 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount/10,true);
				bool IsWrite2 = Index+1 >= DataList->size() ? true:!CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],HeCount%10,true);

				if(!IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Yelow;

				if(!IsWrite1 &&  IsWrite2 || IsWrite1 &&  !IsWrite2)
					Style.m_DrawData.m_TextData.m_BGColor = Red;

					
			}

			m_ListCtrl2.SetItemSpecialStyle(Index,List2Index,Style);
			List2Index++;
			Str.Empty();
		
		



		}
}

//尾数双胆
void CDlgLianHaoHongQiu::OnBnClickedWeishuShuangdanBtn()
{
	FillShuangDanList(0);
}

//合数双胆
void CDlgLianHaoHongQiu::OnBnClickedHeshuShuangdanBtn()
{
	FillShuangDanList(1);
}

//差数双胆
void CDlgLianHaoHongQiu::OnBnClickedChashuShuangdanBtn()
{
	FillShuangDanList(2);
}


//填充颜色
void CDlgLianHaoHongQiu::FillItemStyleColor(sItemStyle& Style,bool IsTrue1,bool IsTrue2)
{
	COLORREF Yelow=RGB(255,192,0);
	COLORREF ZiSe=RGB(112,48,160);
	COLORREF Write=RGB(255,255,255);
	//COLORREF Red=RGB(255,0,0);

	if(IsTrue1 && IsTrue2)
	{
		Style.m_DrawData.m_TextData.m_BGColor = ZiSe;
		return;
	}

	if((!IsTrue1 && IsTrue2) || (IsTrue1 && !IsTrue2))
	{
		Style.m_DrawData.m_TextData.m_BGColor =Yelow;
		return;
	}

	if(!IsTrue1 && !IsTrue2)
	{
		Style.m_DrawData.m_TextData.m_BGColor =Write;
		return;
	}


}

//填充数据
void CDlgLianHaoHongQiu::FillShuangDanListData(CListCtrlEx& ListCtrl,vector<sShuangSeQiu>* DataList,int Data,int Index, int& CololIndex)
{
	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;
	Style.m_DrawData.m_TextData.m_IsFillBG=true;

	COLORREF Yelow=RGB(255,192,0);
	COLORREF ZiSe=RGB(112,48,160);
	COLORREF Write=RGB(255,255,255);
	COLORREF Red=RGB(255,0,0);

	int TempData=Data;
	int TempData2=TempData/10;
	int TempData3=TempData%10;
	bool IsTrue1=false;
	bool IsTrue2=false;

	if(m_CompareShuangDanType < 10 || m_CompareShuangDanType>= 30)
	{
		CString Str;
		Str.Format("%d%d",TempData2,TempData3);
		ListCtrl.SetItemText(Index,CololIndex,Str);
		/*Str.Empty();
		Str.Format("%d",TempData3);
		ListCtrl.SetItemText(Index,CololIndex+1,Str);*/

		if(m_CompareShuangDanType == 0 || m_CompareShuangDanType== 5 || m_CompareShuangDanType== 30)
		{
			IsTrue1 = Index+1 >= DataList->size() ? false:CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],TempData2,true);
			IsTrue2 = Index+1 >= DataList->size() ? false:CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],TempData3,true);
		}
		else if(m_CompareShuangDanType  == 1|| m_CompareShuangDanType== 6|| m_CompareShuangDanType== 31)
		{
			IsTrue1 = Index+1 >= DataList->size() ? false:CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],TempData2,true);
			IsTrue2 = Index+1 >= DataList->size() ? false:CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],TempData3,true);
		}
		else if(m_CompareShuangDanType ==2 ||  m_CompareShuangDanType== 7 || m_CompareShuangDanType== 32)
		{
			IsTrue1 = Index+1 >= DataList->size() ? false:CDataManageCenter::IsHongQiuInChaData((*DataList)[Index+1],TempData2,true);
			IsTrue2 = Index+1 >= DataList->size() ? false:CDataManageCenter::IsHongQiuInChaData((*DataList)[Index+1],TempData3,true);
		}

		if(!IsTrue1)
		{
			Style.m_DrawData.m_TextData.m_BGColor = Write;
		}
		else
		{
			FillItemStyleColor(Style,IsTrue1,IsTrue2);
		}
		ListCtrl.SetItemSpecialStyle(Index,CololIndex,Style);
		CololIndex++;
	}
	else
	{
		CString Str;
		Str.Format("%d",TempData2);
		ListCtrl.SetItemText(Index,CololIndex,Str);
		int Data=TempData2;
		if(m_CompareShuangDanType == 10 || m_CompareShuangDanType== 11|| m_CompareShuangDanType== 20)
		{
			//前三后三胆V
			IsTrue1 = Index+1 >= DataList->size() ? false:CDataManageCenter::IsHongQiuInQianSanData((*DataList)[Index+1],Data,true);
			IsTrue2 = Index+1 >= DataList->size() ? false:CDataManageCenter::IsHongQiuInHouSanData((*DataList)[Index+1],Data,true);
		}
		else if(m_CompareShuangDanType == 12 || m_CompareShuangDanType== 13|| m_CompareShuangDanType== 21)
		{
			//前三后三胆合
			IsTrue1 = Index+1 >= DataList->size() ? false:CDataManageCenter::IsHongQiuInHeQianSanData((*DataList)[Index+1],Data,true);
			IsTrue2 = Index+1 >= DataList->size() ? false:CDataManageCenter::IsHongQiuInHeHouSanData((*DataList)[Index+1],Data,true);

		}
		else if(m_CompareShuangDanType == 14 || m_CompareShuangDanType== 15|| m_CompareShuangDanType== 22)
		{
			//前三后三胆差
			IsTrue1 = Index+1 >= DataList->size() ? false:CDataManageCenter::IsHongQiuInChaQianSanData((*DataList)[Index+1],Data,true);
			IsTrue2 = Index+1 >= DataList->size() ? false:CDataManageCenter::IsHongQiuInChaHouSanData((*DataList)[Index+1],Data,true);
		}

		if(IsTrue1 && IsTrue2)
			Style.m_DrawData.m_TextData.m_BGColor=Red;
		else if(!IsTrue1&&!IsTrue2)
			Style.m_DrawData.m_TextData.m_BGColor=Write;
		else if(IsTrue1&&!IsTrue2)
			Style.m_DrawData.m_TextData.m_BGColor=Yelow;
		else
			Style.m_DrawData.m_TextData.m_BGColor=ZiSe;

		
		ListCtrl.SetItemSpecialStyle(Index,CololIndex,Style);
		CololIndex++;

		Str.Empty();
		Str.Format("%d",TempData3);
		ListCtrl.SetItemText(Index,CololIndex,Str);
		Data=TempData3;
		if(m_CompareShuangDanType == 10 || m_CompareShuangDanType== 11)
		{
			//前三后三胆V
			IsTrue1 = Index+1 >= DataList->size() ? false:CDataManageCenter::IsHongQiuInQianSanData((*DataList)[Index+1],Data,true);
			IsTrue2 = Index+1 >= DataList->size() ? false:CDataManageCenter::IsHongQiuInHouSanData((*DataList)[Index+1],Data,true);
		}
		else if(m_CompareShuangDanType == 12 || m_CompareShuangDanType== 13)
		{
			//前三后三胆合
			IsTrue1 = Index+1 >= DataList->size() ? false:CDataManageCenter::IsHongQiuInHeQianSanData((*DataList)[Index+1],Data,true);
			IsTrue2 = Index+1 >= DataList->size() ? false:CDataManageCenter::IsHongQiuInHeHouSanData((*DataList)[Index+1],Data,true);

		}
		else if(m_CompareShuangDanType == 14 || m_CompareShuangDanType== 15)
		{
			//前三后三胆差
			IsTrue1 = Index+1 >= DataList->size() ? false:CDataManageCenter::IsHongQiuInChaQianSanData((*DataList)[Index+1],Data,true);
			IsTrue2 = Index+1 >= DataList->size() ? false:CDataManageCenter::IsHongQiuInChaHouSanData((*DataList)[Index+1],Data,true);
		}

		if(IsTrue1 && IsTrue2)
			Style.m_DrawData.m_TextData.m_BGColor=Red;
		else if(!IsTrue1&&!IsTrue2)
			Style.m_DrawData.m_TextData.m_BGColor=Write;
		else if(IsTrue1&&!IsTrue2)
			Style.m_DrawData.m_TextData.m_BGColor=Yelow;
		else
			Style.m_DrawData.m_TextData.m_BGColor=ZiSe;

		ListCtrl.SetItemSpecialStyle(Index,CololIndex,Style);
		CololIndex++;
	}

	return;
}

//填充数据
void CDlgLianHaoHongQiu::FillSanDanListData(CListCtrlEx& ListCtrl,vector<sShuangSeQiu>* DataList,int Data,int Index, int& CololIndex)
{
	int TempData=Data;
	int TempData1=TempData/100;
	int TempData2=TempData/10%10;
	int TempData3=TempData%10;
	bool IsTrue1=false;
	bool IsTrue2=false;
	bool IsTrue3=false;

	CString Str;
	Str.Format("%d",TempData1);
	ListCtrl.SetItemText(Index,CololIndex,Str);
	sItemStyle Style=GetSanDanItemStyle(m_CompareSanDanType,DataList,Index,TempData1);
	ListCtrl.SetItemSpecialStyle(Index,CololIndex,Style);
	Str.Empty();
	CololIndex++;

	Str.Format("%d",TempData2);
	ListCtrl.SetItemText(Index,CololIndex,Str);
	Style=GetSanDanItemStyle(m_CompareSanDanType,DataList,Index,TempData2);
	ListCtrl.SetItemSpecialStyle(Index,CololIndex,Style);
	Str.Empty();
	CololIndex++;

	Str.Format("%d",TempData3);
	ListCtrl.SetItemText(Index,CololIndex,Str);
	Style=GetSanDanItemStyle(m_CompareSanDanType,DataList,Index,TempData3);
	ListCtrl.SetItemSpecialStyle(Index,CololIndex,Style);
	Str.Empty();
	CololIndex++;

	int max=((TempData1+TempData2)+abs(TempData1-TempData2))/2;
	if(max < TempData3)
		max=TempData3;

	int min=((TempData1+TempData2)-abs(TempData1-TempData2))/2;
	if(min > TempData3)
		min=TempData3;

	Str.Format("%d",max-min);
	ListCtrl.SetItemText(Index,CololIndex,Str);
	Style=GetSanDanItemStyle(m_CompareSanDanType,DataList,Index,max-min);
	Style.m_DrawData.m_TextData.m_IsFillBG=false;
	ListCtrl.SetItemSpecialStyle(Index,CololIndex,Style);
	Str.Empty();
	CololIndex++;

	int He=TempData1+TempData2+TempData3;
	Str.Format("%d",He);
	ListCtrl.SetItemText(Index,CololIndex,Str);
	Style=GetSanDanItemStyle(m_CompareSanDanType,DataList,Index,He);
	Style.m_DrawData.m_TextData.m_IsFillBG=false;
	ListCtrl.SetItemSpecialStyle(Index,CololIndex,Style);
	Str.Empty();
	CololIndex++;

	return;
}

//填充数据
void CDlgLianHaoHongQiu::FillSingleDanListData(CListCtrlEx& ListCtrl,vector<sShuangSeQiu>* DataList,int Data,int Index, int& CololIndex,eYanType FillType)
{
	CString Str;
	Str.Format("%d",Data);
	ListCtrl.SetItemText(Index,CololIndex,Str);
	sItemStyle Style=GetSingleDanItemStyle(FillType,DataList,Index,Data);
	ListCtrl.SetItemSpecialStyle(Index,CololIndex,Style);
	Str.Empty();
	CololIndex++;
}

//获取三胆填充风格
sItemStyle CDlgLianHaoHongQiu::GetSanDanItemStyle(int FillType,vector<sShuangSeQiu>* DataList,int Index,int Data)
{
	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;
	Style.m_DrawData.m_TextData.m_IsFillBG=true;

	COLORREF Yelow=RGB(255,192,0);
	COLORREF ZiSe=RGB(112,48,160);
	COLORREF Write=RGB(255,255,255);
	COLORREF Red=RGB(255,0,0);

	bool IsTrue1=false;
	bool IsTrue2=false;

	if(FillType == 0)
	{
		IsTrue1 = Index+1 >= DataList->size() ? false:CDataManageCenter::IsHongQiuInQianSanData((*DataList)[Index+1],Data,true);
		IsTrue2 = Index+1 >= DataList->size() ? false:CDataManageCenter::IsHongQiuInHouSanData((*DataList)[Index+1],Data,true);
	}
	else if(FillType == 1)
	{
		IsTrue1 = Index+1 >= DataList->size() ? false:CDataManageCenter::IsHongQiuInHeQianSanData((*DataList)[Index+1],Data,true);
		IsTrue2 = Index+1 >= DataList->size() ? false:CDataManageCenter::IsHongQiuInHeHouSanData((*DataList)[Index+1],Data,true);
	}
	else
	{
		IsTrue1 = Index+1 >= DataList->size() ? false:CDataManageCenter::IsHongQiuInChaQianSanData((*DataList)[Index+1],Data,true);
		IsTrue2 = Index+1 >= DataList->size() ? false:CDataManageCenter::IsHongQiuInChaHouSanData((*DataList)[Index+1],Data,true);
	}

	if(IsTrue1 && IsTrue2)
		Style.m_DrawData.m_TextData.m_BGColor=Red;
	else if(!IsTrue1&&!IsTrue2)
		Style.m_DrawData.m_TextData.m_BGColor=Write;
	else if(IsTrue1&&!IsTrue2)
		Style.m_DrawData.m_TextData.m_BGColor=Yelow;
	else
		Style.m_DrawData.m_TextData.m_BGColor=ZiSe;

	return Style;
}

//获取单胆填充风格
sItemStyle CDlgLianHaoHongQiu::GetSingleDanItemStyle(eYanType FillType,vector<sShuangSeQiu>* DataList,int Index,int Data)
{
	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;
	Style.m_DrawData.m_TextData.m_IsFillBG=true;

	bool IsTrue1=false;
	if(FillType == TYPE_WEI)
	{
		IsTrue1 = Index+1 >= DataList->size() ? false:CDataManageCenter::IsHongQiuInData((*DataList)[Index+1],Data,true);
	}
	else if(FillType == TYPE_HE)
	{
		IsTrue1 = Index+1 >= DataList->size() ? false:CDataManageCenter::IsHongQiuInHeData((*DataList)[Index+1],Data,true);
	}
	else
	{
		IsTrue1 = Index+1 >= DataList->size() ? false:CDataManageCenter::IsHongQiuInChaData((*DataList)[Index+1],Data,true);
		
	}

	if(IsTrue1)
		Style.m_DrawData.m_TextData.m_BGColor=WRITE;
	else 
		Style.m_DrawData.m_TextData.m_BGColor=ZISE;


	return Style;

}


//填充双胆尾数据
void CDlgLianHaoHongQiu::FillShuangDanList(int FillType)
{
	
	m_ListCtrl.ShowWindow(SW_HIDE);
	m_ListCtrl2.ShowWindow(SW_HIDE);
	m_ListCtrl3.ShowWindow(SW_SHOW);

	m_CompareShuangDanType=FillType;
	

	
	m_ListCtrl3.DeleteAllItems();
	m_ListCtrl3.InsertItem(0,"");
	vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
	vector<sShuangSeQiu>* QiuShun=CDataManageCenter::GetInstance()->GetDataListByChuHao();
	
	for(int Index = 0; Index < (int)DataList->size(); Index++)
	{
		m_ListCtrl3.InsertItem(Index,"");
	}

	int ListInsertPos=0;
	FillDataByType(0,true,ListInsertPos);
	FillDataByType(1,false,ListInsertPos);
	FillDataByType(2,false,ListInsertPos);
}

//填充三胆尾数据
void CDlgLianHaoHongQiu::FillSanDanList(int FillType)
{
	m_CompareSanDanType=FillType;
	m_ListCtrl.ShowWindow(SW_HIDE);
	m_ListCtrl2.ShowWindow(SW_SHOW);
	m_ListCtrl3.ShowWindow(SW_HIDE);

	m_ListCtrl2.DeleteAllItems();
	m_ListCtrl2.InsertItem(0,"");
	vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
	vector<sShuangSeQiu>* QiuShun=CDataManageCenter::GetInstance()->GetDataListByChuHao();
	
	for(int Index = 0; Index < (int)DataList->size(); Index++)
	{
		m_ListCtrl2.InsertItem(Index,"");
	}

	int ListInsertPos=0;
	FillSanDanDataByType(FillType,true,ListInsertPos);
}


//填充数据
void CDlgLianHaoHongQiu::FillDataByType(int FillType,bool FillWay,int& ColoumnIndex)
{
	vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
	vector<sShuangSeQiu>* QiuShun=CDataManageCenter::GetInstance()->GetDataListByChuHao();
	
	int TempColoumnIndex=ColoumnIndex;

	for(int Index = 0; Index < (int)DataList->size(); Index++)
	{
			CString ShunV;
			CString HouV;
			CString QiuV;
			CString QiuHouV;
			CString KuaDu;
			CString HeV;

			int VCount=0;

			CString ShunVCSV;
			CString HouVCSV;
			CString QiuVCSV;
			CString QiuHouVCSV;

			vector<int> ShunVInt;
			vector<int> HouVInt;
			vector<int> QiuVInt;
			vector<int> QiuHouVInt;
			
			int TempArray[10];
			memset(TempArray,0,10*sizeof(int));

			for(int i=0; i < 6; i++)
			{
				int V=0;
				int V2=0;
				
				
				if(FillType == 0)
				{
					V=(*DataList)[Index].m_HongQiu[i]%10;
					V2=(*QiuShun)[Index].m_HongQiu[i]%10;

				}
				else if(FillType == 1)
				{
					V=(*DataList)[Index].m_HongQiu[i]%10+(*DataList)[Index].m_HongQiu[i]/10;
					V2=(*QiuShun)[Index].m_HongQiu[i]%10+(*QiuShun)[Index].m_HongQiu[i]/10;
				}
				else
				{
					V=abs((*DataList)[Index].m_HongQiu[i]%10-(*DataList)[Index].m_HongQiu[i]/10);
					V2=abs((*QiuShun)[Index].m_HongQiu[i]%10-(*QiuShun)[Index].m_HongQiu[i]/10);
				}

				if(m_CompareShuangDanType == 0 || m_CompareShuangDanType == 5|| m_CompareShuangDanType== 10 || m_CompareShuangDanType== 11 || m_CompareShuangDanType== 20 || m_CompareShuangDanType== 30)
				{
					int TempV=(*DataList)[Index].m_HongQiu[i]%10;
					TempArray[TempV]++;
				}
				else if(m_CompareShuangDanType == 1||m_CompareShuangDanType == 6|| m_CompareShuangDanType== 12 || m_CompareShuangDanType== 13 ||m_CompareShuangDanType== 21 || m_CompareShuangDanType== 31 )
				{
					int TempV=(*DataList)[Index].m_HongQiu[i]%10+(*DataList)[Index].m_HongQiu[i]/10;
					TempV=TempV%10;
					TempArray[TempV]++;
				}
				else
				{
					int TempV=abs((*DataList)[Index].m_HongQiu[i]%10-(*DataList)[Index].m_HongQiu[i]/10);
					TempV=TempV%10;
					TempArray[TempV]++;
				}


				V=V%10; 
				V2=V2%10;
				VCount+=V;

				

				CString StrV;
				StrV.Format("%d",V);
				CString StrV2;
				StrV2.Format("%d",V2);
			
				if(i < 3)
				{
					QiuV+=StrV;
					ShunV+=StrV2;

					ShunVInt.push_back(V2);
					QiuVInt.push_back(V);

					if(QiuVCSV.IsEmpty())
						QiuVCSV+=StrV;
					else 
						QiuVCSV+=","+StrV;
					if(ShunVCSV.IsEmpty())
						ShunVCSV+=StrV2;
					else
						ShunVCSV+=","+StrV2;
				}
				else
				{
					QiuHouV+=StrV;
					HouV+=StrV2;

					HouVInt.push_back(V2);
					QiuHouVInt.push_back(V);

					if(QiuHouVCSV.IsEmpty())
						QiuHouVCSV+=StrV;
					else 
						QiuHouVCSV+=","+StrV;
					if(HouVCSV.IsEmpty())
						HouVCSV+=StrV2;
					else
						HouVCSV+=","+StrV2;

				}
			}


			int InsertPos=Index;

			int List2Index=TempColoumnIndex;
			if(FillWay)
			{
				CString AllV;
				for(int j=0; j < 10; j++)
				{
					if(TempArray[j])
					{
						CString Temp;
						Temp.Format("%d",j);
						AllV+=Temp;
					}
				}

				
				CString Text;
				Text=(*DataList)[Index].m_QiShu+" "+AllV;
				m_ListCtrl3.SetItemText(InsertPos,List2Index,Text);
				List2Index++;
				List2Index++;
			}

			if(m_CompareShuangDanType < 10)
			{
				if(m_CompareShuangDanType < 4)
				{
					int TempData=TransDataByInt(ShunV,314,8);
					FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);

					TempData=TransDataByInt(ShunV,618,8);
					FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);

					TempData=TransDataByInt(HouV,314,8);
					FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);

					TempData=TransDataByInt(HouV,618,8);
					FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);

					TempData=TransDataByInt(QiuV,314,8);
					FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);

					TempData=TransDataByInt(QiuV,618,8);
					FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);

					TempData=TransDataByInt(QiuHouV,314,8);
					FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);

					TempData=TransDataByInt(QiuHouV,618,8);
					FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);


					//只乘0.8
					TempData=TransDataByInt(ShunV,8,0);
					FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);

					TempData=TransDataByInt(HouV,8,0);
					FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);

					TempData=TransDataByInt(QiuV,8,0);
					FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);

					TempData=TransDataByInt(QiuHouV,8,0);
					FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);
				}

				if(m_CompareShuangDanType > 4)
				{
					int TempData=0;

					//只乘314
					TempData=TransDataByInt(ShunV,314,0);
					FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);

					TempData=TransDataByInt(HouV,314,0);
					FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);

					TempData=TransDataByInt(QiuV,314,0);
					FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);

					TempData=TransDataByInt(QiuHouV,314,0);
					FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);

					//只乘618
					TempData=TransDataByInt(ShunV,618,0);
					FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);

					TempData=TransDataByInt(HouV,618,0);
					FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);

					TempData=TransDataByInt(QiuV,618,0);
					FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);

					TempData=TransDataByInt(QiuHouV,618,0);
					FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);
				}
			}
			else if(m_CompareShuangDanType < 20)
			{
				if(m_CompareShuangDanType %2 == 0 )
				{
					/*int TempData=TransDataByInt(ShunV,314,1);
					FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);

					TempData=TransDataByInt(HouV,314,1);
					FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);

					TempData=TransDataByInt(QiuV,314,1);
					FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);

					TempData=TransDataByInt(QiuHouV,314,1);
		
		            FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);*/

					int Param=314;

					int TempData=TransDataByInt(ShunV,Param,1);
					FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);

					TempData=TransDataByInt(HouV,Param,1);
					FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);

					TempData=TransDataByInt(QiuV,Param,1);
					FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);

					TempData=TransDataByInt(QiuHouV,Param,1);
					FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);


				}
				else
				{
					
					int TempData=TransDataByInt(ShunV,618,1);
					FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);

					TempData=TransDataByInt(HouV,618,1);
					FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);

					TempData=TransDataByInt(QiuV,618,1);
					FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);

					TempData=TransDataByInt(QiuHouV,618,1);
					FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);
					

				}
			}
			else
			{
				    int Param=m_ParamData;

					int TempData=TransDataByInt(ShunV,Param,1);
					FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);

					TempData=TransDataByInt(HouV,Param,1);
					FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);

					TempData=TransDataByInt(QiuV,Param,1);
					FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);

					TempData=TransDataByInt(QiuHouV,Param,1);
					FillShuangDanListData(m_ListCtrl3,DataList,TempData,InsertPos,List2Index);
			}
			

			if(Index == 0)
				ColoumnIndex=List2Index;
		}
}

//填充三胆尾数据
void CDlgLianHaoHongQiu::FillSanDanDataByType(int FillType,bool FillWay,int& ColoumnIndex)
{
	vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
	vector<sShuangSeQiu>* QiuShun=CDataManageCenter::GetInstance()->GetDataListByChuHao();
	
	int TempColoumnIndex=ColoumnIndex;
	for(int Index = 0; Index < (int)DataList->size(); Index++)
	{
			CString ShunV;
			CString HouV;
			CString QiuV;
			CString QiuHouV;
			CString KuaDu;
			CString HeV;

			int VCount=0;

			CString ShunVCSV;
			CString HouVCSV;
			CString QiuVCSV;
			CString QiuHouVCSV;

			vector<int> ShunVInt;
			vector<int> HouVInt;
			vector<int> QiuVInt;
			vector<int> QiuHouVInt;
			
			int TempArray[10];
			memset(TempArray,0,10*sizeof(int));

			for(int i=0; i < 6; i++)
			{
				int V=0;
				int V2=0;
				
				
				if(FillType == 0)
				{
					V=(*DataList)[Index].m_HongQiu[i]%10;
					V2=(*QiuShun)[Index].m_HongQiu[i]%10;
					

				}
				else if(FillType == 1)
				{
					V=(*DataList)[Index].m_HongQiu[i]%10+(*DataList)[Index].m_HongQiu[i]/10;
					V2=(*QiuShun)[Index].m_HongQiu[i]%10+(*QiuShun)[Index].m_HongQiu[i]/10;
				}
				else
				{
					V=abs((*DataList)[Index].m_HongQiu[i]%10-(*DataList)[Index].m_HongQiu[i]/10);
					V2=abs((*QiuShun)[Index].m_HongQiu[i]%10-(*QiuShun)[Index].m_HongQiu[i]/10);
				}

				V=V%10;
				V2=V2%10;
				TempArray[V]++;
				CString StrV;
				StrV.Format("%d",V);
				CString StrV2;
				StrV2.Format("%d",V2);
			
				if(i < 3)
				{
					QiuV+=StrV;
					ShunV+=StrV2;

					ShunVInt.push_back(V2);
					QiuVInt.push_back(V);

					if(QiuVCSV.IsEmpty())
						QiuVCSV+=StrV;
					else 
						QiuVCSV+=","+StrV;
					if(ShunVCSV.IsEmpty())
						ShunVCSV+=StrV2;
					else
						ShunVCSV+=","+StrV2;
				}
				else
				{
					QiuHouV+=StrV;
					HouV+=StrV2;

					HouVInt.push_back(V2);
					QiuHouVInt.push_back(V);

					if(QiuHouVCSV.IsEmpty())
						QiuHouVCSV+=StrV;
					else 
						QiuHouVCSV+=","+StrV;
					if(HouVCSV.IsEmpty())
						HouVCSV+=StrV2;
					else
						HouVCSV+=","+StrV2;

				}
			}


			int InsertPos=Index;

			int List2Index=TempColoumnIndex;
			if(FillWay)
			{
				CString AllV;
				int Min=10;
				int Max=0;
				for(int j=0; j < 10; j++)
				{
					if(TempArray[j])
					{
						CString Temp;
						Temp.Format("%d",j);
						AllV+=Temp;

						if(Max < j)
							Max=j;
						
						if(Min > j)
							Min=j;
					}
				}

				
				CString Text;
				Text=(*DataList)[Index].m_QiShu+" "+AllV;
				m_ListCtrl2.SetItemText(InsertPos,List2Index,Text);
				List2Index++;

				Text.Empty();
				Text.Format("%d",Max-Min);
				m_ListCtrl2.SetItemText(InsertPos,List2Index,Text);

				sItemStyle Style;
				Style.m_ItemType = TEXT_TYPE;
				Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);
				Style.m_DrawData.m_TextData.m_TextFont = NULL;
				Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;
				Style.m_DrawData.m_TextData.m_IsFillBG=false;
				m_ListCtrl2.SetItemSpecialStyle(InsertPos,List2Index,Style);
				List2Index++;

			}

			

			int TempData=TransDataByInt(ShunV);
			FillSanDanListData(m_ListCtrl2,DataList,TempData,InsertPos,List2Index);

			TempData=TransDataByInt(HouV);
			FillSanDanListData(m_ListCtrl2,DataList,TempData,InsertPos,List2Index);

			TempData=TransDataByInt(QiuV);
			FillSanDanListData(m_ListCtrl2,DataList,TempData,InsertPos,List2Index);

			TempData=TransDataByInt(QiuHouV);
			FillSanDanListData(m_ListCtrl2,DataList,TempData,InsertPos,List2Index);


			TempData=TransDataByInt(ShunV,314);
			FillSanDanListData(m_ListCtrl2,DataList,TempData,InsertPos,List2Index);

			TempData=TransDataByInt(ShunV,618);
			FillSanDanListData(m_ListCtrl2,DataList,TempData,InsertPos,List2Index);

			TempData=TransDataByInt(HouV,314);
			FillSanDanListData(m_ListCtrl2,DataList,TempData,InsertPos,List2Index);

			TempData=TransDataByInt(HouV,618);
			FillSanDanListData(m_ListCtrl2,DataList,TempData,InsertPos,List2Index);

			TempData=TransDataByInt(QiuV,314);
			FillSanDanListData(m_ListCtrl2,DataList,TempData,InsertPos,List2Index);

			TempData=TransDataByInt(QiuV,618);
			FillSanDanListData(m_ListCtrl2,DataList,TempData,InsertPos,List2Index);

			TempData=TransDataByInt(QiuHouV,314);
			FillSanDanListData(m_ListCtrl2,DataList,TempData,InsertPos,List2Index);

			TempData=TransDataByInt(QiuHouV,618);
			FillSanDanListData(m_ListCtrl2,DataList,TempData,InsertPos,List2Index);

			if(Index == 0)
				ColoumnIndex=List2Index;
		}
}

void CDlgLianHaoHongQiu::OnBnClickedQianSanWeiBtn()
{
	OnBnClickedButton1();
}

void CDlgLianHaoHongQiu::OnBnClickedHouSanWeiBtn()
{
	OnBnClickedButton2();
}

void CDlgLianHaoHongQiu::OnBnClickedQianSanHeBtn()
{
	FillSanDanList(0);
}

void CDlgLianHaoHongQiu::OnBnClickedHouSanHeBtn()
{
	FillSanDanList(1);
}
void CDlgLianHaoHongQiu::OnBnClickedHouSanHeBtn2()
{
	FillSanDanList(2);
	
}

void CDlgLianHaoHongQiu::OnBnClickedExecBtn()
{
	/*m_ComboBox.InsertString(0,"314尾走势");
	m_ComboBox.InsertString(1,"618尾走势");
	m_ComboBox.InsertString(2,"314合走势");
	m_ComboBox.InsertString(3,"618合走势");
	m_ComboBox.InsertString(4,"314差走势");
	m_ComboBox.InsertString(5,"618差走势");*/
	//m_ComboBox.InsertString(0,"314尾前后三走势");
	//m_ComboBox.InsertString(1,"618尾前后三走势");
	//m_ComboBox.InsertString(2,"314合前后三走势");
	//m_ComboBox.InsertString(3,"618合前后三走势");
	//m_ComboBox.InsertString(4,"314差前后三走势");
	//m_ComboBox.InsertString(5,"618差前后三走势");

	//m_ComboBox.InsertString(9,"可变尾前后三走势");
	//m_ComboBox.InsertString(10,"可变合前后三走势");
	//m_ComboBox.InsertString(11,"可变差前后三走势");
	//m_ComboBox.InsertString(12,"可变双胆尾走势");
	//m_ComboBox.InsertString(13,"可变双胆合走势");
	//m_ComboBox.InsertString(14,"可变双胆差走势");

	/*m_ComboBox.InsertString(15,"自动尾前后三极限");
	m_ComboBox.InsertString(16,"自动合前后三极限");
	m_ComboBox.InsertString(17,"自动差前后三极限");
	m_ComboBox.InsertString(18,"自动双胆尾极限");
	m_ComboBox.InsertString(19,"自动双胆合极限");
	m_ComboBox.InsertString(20,"自动双胆差极限");*/


	CString Text;
	GetDlgItem(IDC_COMBO1)->GetWindowText(Text);
	if(Text == _T("314尾前后三走势"))
	{
		m_CompareShuangDanType = 10;
	}
	else if(Text==_T("618尾前后三走势"))
	{
		m_CompareShuangDanType = 11;
	}
	else if(Text == _T("314合前后三走势"))
	{
		m_CompareShuangDanType = 12;
	}
	else if(Text == _T("618合前后三走势"))
	{
		m_CompareShuangDanType = 13;
	}
	else if(Text == _T("314差前后三走势"))
	{
		m_CompareShuangDanType = 14;
	}
	else if(Text == _T("618差前后三走势"))
	{
		m_CompareShuangDanType = 15;

	}
	else if(Text == _T("双胆尾走势"))
	{
		m_CompareShuangDanType=5;
	}
	else if(Text == _T("双胆合走势"))
	{
		m_CompareShuangDanType=6;
	}
	else if(Text == _T("双胆差走势"))
	{
		m_CompareShuangDanType=7;
	}
	else if(Text == _T("可变尾前后三走势"))
	{
		m_CompareShuangDanType=20;
	}
	else if(Text == _T("可变合前后三走势"))
	{
		m_CompareShuangDanType=21;
	}
	else if(Text == _T("可变差前后三走势"))
	{
		m_CompareShuangDanType=22;
	}
	else if(Text==_T("可变双胆尾走势"))
	{
		m_CompareShuangDanType=30;

	}
	else if(Text==_T("可变双胆合走势"))
	{
		m_CompareShuangDanType=31;
	}
	else if(Text==_T("可变双胆差走势"))
	{
		m_CompareShuangDanType=32;
	}
	else
	{
		if(m_Flag)
		{
			AfxMessageBox("正在计算极限");
			return;
		}
		
		eYanDataType DataType=TYPE_WEI_QIANSAN_HOUSAN;		
		if(Text==_T("自动尾前后三极限"))
		{
			DataType=TYPE_WEI_QIANSAN_HOUSAN;          //前三后三尾
		}
		else if(Text==_T("自动合前后三极限"))
		{
			DataType=TYPE_HE_QIANSAN_HOUSAN;          //前三后三合
		}
		else if(Text==_T("自动差前后三极限"))
		{
			DataType=TYPE_CHA_QIANSAN_HOUSAN;          //前三后三差
		}
		else if(Text==_T("自动双胆尾极限"))
		{
			DataType =TYPE_WEI_SHUANG_DAN;
		}
		else if(Text==_T("自动双胆合极限"))
		{
			DataType =TYPE_HE_SHUANG_DAN;
		}
		else if(Text==_T("自动双胆差极限"))
		{
			DataType =TYPE_CHA_SHUANG_DAN;
		}
		else
		{
			m_CompareShuangDanType =10;
		}

		FillJiXianDataList(DataType);
		return;
	}



	/*m_ComboBox.InsertString(15,"自动尾前后三极限");
	m_ComboBox.InsertString(16,"自动合前后三极限");
	m_ComboBox.InsertString(17,"自动差前后三极限");
	m_ComboBox.InsertString(18,"自动双胆尾极限");
	m_ComboBox.InsertString(19,"自动双胆合极限");
	m_ComboBox.InsertString(20,"自动双胆差极限");*/

	CString EditText;
	GetDlgItem(IDC_EDIT1)->GetWindowText(EditText);
	m_ParamData=atoi(EditText.GetBuffer());
	EditText.ReleaseBuffer();

	FillShuangDanList(m_CompareShuangDanType);
	
}

void CDlgLianHaoHongQiu::OnBnClickedJixianBtn()
{
	CString EditText;
	GetDlgItem(IDC_EDIT1)->GetWindowText(EditText);
	m_ParamData=atoi(EditText.GetBuffer());
	EditText.ReleaseBuffer();

	::CreateThread(NULL,0,LookJiXianThread,this,0,NULL);
}

//计算数据
void CDlgLianHaoHongQiu::FillMapData(map<int,vector<sDataInfo>>& MapData,int StartPos,int OffsetPos,eYanType YanType,eYanDataType DataType,int Param)
{
	vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
	vector<sShuangSeQiu>* QiuShun=CDataManageCenter::GetInstance()->GetDataListByChuHao();
	for(int Index =0; Index < DataList->size(); Index++)
	{
			CString ShunV;
			CString HouV;
			CString QiuV;
			CString QiuHouV;
			CString KuaDu;
			CString HeV;

			int VCount=0;

			CString ShunVCSV;
			CString HouVCSV;
			CString QiuVCSV;
			CString QiuHouVCSV;

			vector<int> ShunVInt;
			vector<int> HouVInt;
			vector<int> QiuVInt;
			vector<int> QiuHouVInt;
			
			int TempArray[10];
			memset(TempArray,0,10*sizeof(int));

			for(int i=0; i < 6; i++)
			{
				int V=0;
				int V2=0;
				
				
				if(YanType == TYPE_WEI)
				{
					V=(*DataList)[Index].m_HongQiu[i]%10;
					V2=(*QiuShun)[Index].m_HongQiu[i]%10;

				}
				else if(YanType == TYPE_HE)
				{
					V=(*DataList)[Index].m_HongQiu[i]%10+(*DataList)[Index].m_HongQiu[i]/10;
					V2=(*QiuShun)[Index].m_HongQiu[i]%10+(*QiuShun)[Index].m_HongQiu[i]/10;
				}
				else
				{
					V=abs((*DataList)[Index].m_HongQiu[i]%10-(*DataList)[Index].m_HongQiu[i]/10);
					V2=abs((*QiuShun)[Index].m_HongQiu[i]%10-(*QiuShun)[Index].m_HongQiu[i]/10);
				}

				
				V=V%10; 
				V2=V2%10;
				VCount+=V;

				CString StrV;
				StrV.Format("%d",V);
				CString StrV2;
				StrV2.Format("%d",V2);

				if(i < 3)
				{
					QiuV+=StrV;
					ShunV+=StrV2;

					ShunVInt.push_back(V2);
					QiuVInt.push_back(V);

					if(QiuVCSV.IsEmpty())
						QiuVCSV+=StrV;
					else 
						QiuVCSV+=","+StrV;
					if(ShunVCSV.IsEmpty())
						ShunVCSV+=StrV2;
					else
						ShunVCSV+=","+StrV2;
				}
				else
				{
					QiuHouV+=StrV;
					HouV+=StrV2;

					HouVInt.push_back(V2);
					QiuHouVInt.push_back(V);

					if(QiuHouVCSV.IsEmpty())
						QiuHouVCSV+=StrV;
					else 
						QiuHouVCSV+=","+StrV;
					if(HouVCSV.IsEmpty())
						HouVCSV+=StrV2;
					else
						HouVCSV+=","+StrV2;

				}
			}

			sDataInfo Info;
			Info.m_QiShu = (*DataList)[Index].m_QiShu;
			if(DataType <= TYPE_CHA_QIANSAN_HOUSAN)
			{
				int TempData=TransDataByInt(ShunV,Param,1);
				int TempOffsetPos=StartPos+OffsetPos+1;
				Info.m_Data = TempData/10;
				Info.m_Color = Index+1 >= DataList->size() ? WRITE:GetDataColor(DataType,(*DataList)[Index+1],Info.m_Data,true);
				MapData[TempOffsetPos].push_back(Info);
				TempOffsetPos++;

				Info.m_Data = TempData%10;
				Info.m_Color = Index+1 >= DataList->size() ? WRITE:GetDataColor(DataType,(*DataList)[Index+1],Info.m_Data,true);
				MapData[TempOffsetPos].push_back(Info);
				TempOffsetPos++;

				TempData=TransDataByInt(ShunV,Param,1);
				Info.m_Data = TempData/10;
				Info.m_Color = Index+1 >= DataList->size() ? WRITE:GetDataColor(DataType,(*DataList)[Index+1],Info.m_Data,true);
				MapData[TempOffsetPos].push_back(Info);
				TempOffsetPos++;

				Info.m_Data = TempData%10;
				Info.m_Color = Index+1 >= DataList->size() ? WRITE:GetDataColor(DataType,(*DataList)[Index+1],Info.m_Data,true);
				MapData[TempOffsetPos].push_back(Info);
				TempOffsetPos++;

				TempData=TransDataByInt(QiuV,Param,1);
				Info.m_Data = TempData/10;
				Info.m_Color = Index+1 >= DataList->size() ? WRITE:GetDataColor(DataType,(*DataList)[Index+1],Info.m_Data,true);
				MapData[TempOffsetPos].push_back(Info);
				TempOffsetPos++;

				Info.m_Data = TempData%10;
				Info.m_Color = Index+1 >= DataList->size() ? WRITE:GetDataColor(DataType,(*DataList)[Index+1],Info.m_Data,true);
				MapData[TempOffsetPos].push_back(Info);
				TempOffsetPos++;

				TempData=TransDataByInt(QiuHouV,Param,1);
				Info.m_Data = TempData/10;
				Info.m_Color = Index+1 >= DataList->size() ? WRITE:GetDataColor(DataType,(*DataList)[Index+1],Info.m_Data,true);
				MapData[TempOffsetPos].push_back(Info);
				TempOffsetPos++;

				Info.m_Data = TempData%10;
				Info.m_Color = Index+1 >= DataList->size() ? WRITE:GetDataColor(DataType,(*DataList)[Index+1],Info.m_Data,true);
				MapData[TempOffsetPos].push_back(Info);
				TempOffsetPos++;
			}
			else
			{
				int TempData=TransDataByInt(ShunV,Param,1);
				int TempOffsetPos=StartPos+OffsetPos+1;
				Info.m_Data = TempData;
				Info.m_Color = Index+1 >= DataList->size() ? WRITE:GetDataColor(DataType,(*DataList)[Index+1],Info.m_Data,true);
				MapData[TempOffsetPos].push_back(Info);
				TempOffsetPos++;

				TempData=TransDataByInt(ShunV,Param,1);
				Info.m_Data = TempData/10;
				Info.m_Color = Index+1 >= DataList->size() ? WRITE:GetDataColor(DataType,(*DataList)[Index+1],Info.m_Data,true);
				MapData[TempOffsetPos].push_back(Info);
				TempOffsetPos++;

				TempData=TransDataByInt(QiuV,Param,1);
				Info.m_Data = TempData;
				Info.m_Color = Index+1 >= DataList->size() ? WRITE:GetDataColor(DataType,(*DataList)[Index+1],Info.m_Data,true);
				MapData[TempOffsetPos].push_back(Info);
				TempOffsetPos++;

				TempData=TransDataByInt(QiuHouV,Param,1);
				Info.m_Data = TempData;
				Info.m_Color = Index+1 >= DataList->size() ? WRITE:GetDataColor(DataType,(*DataList)[Index+1],Info.m_Data,true);
				MapData[TempOffsetPos].push_back(Info);
				TempOffsetPos++;

			}
	}
}

//是否是需要的数据类型
bool CDlgLianHaoHongQiu::IsWantData(vector<sDataInfo>& VecData,eYanDataType DataType)
{
	if(VecData.size() < 10)
		return false;

	int JiXianCount= m_ParamData-1 >= 0 ? m_ParamData-1:3;
	int Start = VecData.size()-2;
	COLORREF Color=VecData[Start].m_Color;
	if(Color != WRITE)
	{
			switch(DataType)
			{
				case TYPE_WEI_QIANSAN_HOUSAN:          //前三后三尾
				case TYPE_HE_QIANSAN_HOUSAN:            //前三后三合 
				case TYPE_CHA_QIANSAN_HOUSAN:          //前三后三差	
					{
						for(int i=Start; i >=Start-JiXianCount; i--)
						{
							if(Color == RED)
							{
								Color = VecData[i].m_Color;
							}
							else if(Color != WRITE)
							{
								if(Color != VecData[i].m_Color)
									return false;
							}
							else
								return false;
						}
					}
					break;
				case TYPE_WEI_SHUANG_DAN:              //双胆尾
				case TYPE_HE_SHUANG_DAN:               //双胆合
				case TYPE_CHA_SHUANG_DAN:              //双胆差
					{
						JiXianCount= m_ParamData-1 >= 0 ? m_ParamData-1:4;
						for(int i=Start; i >=Start-JiXianCount; i--)
						{
							if(Color == ZISE)
							{
								Color = VecData[i].m_Color;
							}
							else
								return false;
						}

						
					}
					break;

				default:
					return false;
					break;
			}
	}
	else
	{
		    JiXianCount= m_ParamData-1 >= 0 ? m_ParamData-1+6:10;
			switch(DataType)
			{
				case TYPE_WEI_QIANSAN_HOUSAN:          //前三后三尾
				case TYPE_HE_QIANSAN_HOUSAN:            //前三后三合 
				case TYPE_CHA_QIANSAN_HOUSAN:          //前三后三差	
					{
						for(int i=Start; i >=Start-JiXianCount; i--)
						{
							if(Color == WRITE)
							{
								Color = VecData[i].m_Color;
							}
							else
								return false;
						}
					}
					break;
				case TYPE_WEI_SHUANG_DAN:              //双胆尾
				case TYPE_HE_SHUANG_DAN:               //双胆合
				case TYPE_CHA_SHUANG_DAN:              //双胆差
					{
						 JiXianCount= m_ParamData-1 >= 0 ? m_ParamData-1+4:5;
						for(int i=Start; i >=Start-JiXianCount; i--)
						{
							if(Color == WRITE)
							{
								Color = VecData[i].m_Color;
							}
			
							else
								return false;
						}

						
					}
					break;

				default:
					return false;
					break;
			}
	}


	return true;
}
	
//获取数据颜色值
COLORREF CDlgLianHaoHongQiu::GetDataColor(eYanDataType Type,sShuangSeQiu QiuData,int Data,bool IsV)
{
	bool IsTrue1=false;
	bool IsTrue2=false;
	int TempData2=Data/10;
	int TempData3=Data%10;

	switch(Type)
	{
		case TYPE_WEI_QIANSAN_HOUSAN:          //前三后三尾
			//前三后三胆V
			IsTrue1 =CDataManageCenter::IsHongQiuInQianSanData(QiuData,Data,IsV);
			IsTrue2 =CDataManageCenter::IsHongQiuInHouSanData(QiuData,Data,IsV);
			break;
		case TYPE_HE_QIANSAN_HOUSAN:           //前三后三合 
			//前三后三胆合
			IsTrue1 = CDataManageCenter::IsHongQiuInHeQianSanData(QiuData,Data,IsV);
			IsTrue2 = CDataManageCenter::IsHongQiuInHeHouSanData(QiuData,Data,IsV);
			break;
		case TYPE_CHA_QIANSAN_HOUSAN:         //前三后三差
			IsTrue1 = CDataManageCenter::IsHongQiuInChaQianSanData(QiuData,Data,IsV);
			IsTrue2 = CDataManageCenter::IsHongQiuInChaHouSanData(QiuData,Data,IsV);
			break;

		case TYPE_WEI_SHUANG_DAN:              //双胆尾
			IsTrue1 = CDataManageCenter::IsHongQiuInData(QiuData,TempData2,IsV);
			IsTrue2 = CDataManageCenter::IsHongQiuInData(QiuData,TempData3,IsV);
			break;
		case TYPE_HE_SHUANG_DAN:               //双胆合
			IsTrue1 = CDataManageCenter::IsHongQiuInHeData(QiuData,TempData2,IsV);
			IsTrue2 = CDataManageCenter::IsHongQiuInHeData(QiuData,TempData3,IsV);
			break;
		case TYPE_CHA_SHUANG_DAN:           //双胆差
			IsTrue1 = CDataManageCenter::IsHongQiuInChaData(QiuData,TempData2,IsV);
			IsTrue2 = CDataManageCenter::IsHongQiuInChaData(QiuData,TempData3,IsV);
			break;
		default:
			break;
	}

	 


	COLORREF Color=WRITE;
	//颜色比较方式
	switch(Type)
	{
		case TYPE_WEI_QIANSAN_HOUSAN:          //前三后三尾
		case TYPE_HE_QIANSAN_HOUSAN:           //前三后三合 
		case TYPE_CHA_QIANSAN_HOUSAN:         //前三后三差	
			{
				if(IsTrue1 && IsTrue2)
					Color=RED;
				else if(!IsTrue1&&!IsTrue2)
					Color=WRITE;
				else if(IsTrue1&&!IsTrue2)
					Color=YELOW;
				else
					Color=ZISE;
			}
			break;
		case TYPE_WEI_SHUANG_DAN:              //双胆尾
		case TYPE_HE_SHUANG_DAN:               //双胆合
		case TYPE_CHA_SHUANG_DAN:           //双胆差
			{
				if(IsTrue1 && IsTrue2)
					Color=ZISE;
				else if((!IsTrue1 && IsTrue2) || (IsTrue1 && !IsTrue2))
					Color=YELOW;
				else
					Color=WRITE;
			}
			break;
		default:
			break;
	}

	return Color;
}

//寻找极限基数线程
DWORD CDlgLianHaoHongQiu::LookJiXianThread(LPVOID lpVoid)
{
	CDlgLianHaoHongQiu* Self=(CDlgLianHaoHongQiu*)lpVoid;
	Self->m_Flag=true;
	Self->m_AllData.clear();

	Self->GetDlgItem(IDC_JIXIAN_BTN)->EnableWindow(false);

	map<int,map<int,vector<sDataInfo>>> AllData;

	for(int DataType=TYPE_WEI_QIANSAN_HOUSAN; DataType <=TYPE_CHA_SHUANG_DAN; DataType++)
	{
		
		map<int,vector<sDataInfo>> WantMapData;
		int WantPos=0;
		for(int Param=1; Param < 100; Param++)
		{
			map<int,vector<sDataInfo>> MapData;
			int StartPos =0;
			int OffsetPos=0;
			int FillType =0;
			eYanType     YanType  = TYPE_WEI;
			Self->FillMapData(MapData,StartPos,OffsetPos,YanType,(eYanDataType)DataType,Param);

			OffsetPos+=20;
			YanType=TYPE_HE;
			Self->FillMapData(MapData,StartPos,OffsetPos,YanType,(eYanDataType)DataType,Param);

			OffsetPos+=20;
			YanType=TYPE_CHA;
			Self->FillMapData(MapData,StartPos,OffsetPos,YanType,(eYanDataType)DataType,Param);

			
			map<int,vector<sDataInfo>>::iterator it=MapData.begin();
			for(; it != MapData.end(); it++)
			{
				bool IsWant=Self->IsWantData(it->second,(eYanDataType)DataType);
				if(IsWant)
				{
					
					WantMapData[WantPos].insert(WantMapData[WantPos].begin(),it->second.begin(),it->second.end());
					WantPos++;
				}
			}

		}

		AllData[DataType]=WantMapData;
		
	}


	Self->FilterMapData(AllData);
	Self->m_AllData=AllData;
	
	Self->m_Flag=false;
	Self->GetDlgItem(IDC_JIXIAN_BTN)->EnableWindow(true);

	return 0;
}

//过滤重复数据
void CDlgLianHaoHongQiu::FilterMapData(map<int,map<int,vector<sDataInfo>>>& MapData)
{
	map<int,map<int,vector<sDataInfo>>> AllData;
	map<int,map<int,vector<sDataInfo>>>::iterator itAll = MapData.begin();
	for(; itAll != MapData.end(); itAll++)
	{

		map<int,vector<sDataInfo>>::iterator it=itAll->second.begin();
		map<int,vector<sDataInfo>> TempData;

		for(;it != itAll->second.end(); it++)
		{
			map<int,vector<sDataInfo>>::iterator it2=TempData.begin();
			if(it2 == TempData.end())
			{
				TempData[it->first]=it->second;
				continue;
			}

			bool IsWant=true;
			for(;it2 != TempData.end(); it2++)
			{
				if(IsEqualVector(it2->second,it->second))
				{
					IsWant=false;
					break;
				}
			}

			if(IsWant)
				TempData[it->first]=it->second;
		}

		AllData[itAll->first]=TempData;
	}

	MapData.clear();
	MapData=AllData;

	
	
}

//判断两个vector数据相等
bool CDlgLianHaoHongQiu::IsEqualVector(vector<sDataInfo>& Vec1,vector<sDataInfo>& Vec2)
{
	if(Vec1.size() != Vec2.size())
		return false;

	int CompareCount=Vec1.size() > 10 ? 10:Vec1.size();
	int EqualCount=0;
	for(int Index=0; Index < CompareCount; Index++)
	{
		if(Vec1[Index].m_Data == Vec2[Index].m_Data)
			EqualCount++;
	}

	if(CompareCount == EqualCount)
		return true;

	return false;
}


//填充极限数据
void CDlgLianHaoHongQiu::FillJiXianDataList(eYanDataType DataType)
{
	m_ListCtrl.ShowWindow(SW_HIDE);
	m_ListCtrl2.ShowWindow(SW_HIDE);
	m_ListCtrl3.ShowWindow(SW_SHOW);
	m_ListCtrl3.DeleteAllItems();
	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;
	Style.m_DrawData.m_TextData.m_IsFillBG=true;
	vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();

	for(int Index = 0; Index < (int)DataList->size(); Index++)
	{
		m_ListCtrl3.InsertItem(Index,"");
		int TempArray[10];
		memset(TempArray,0,10*sizeof(int));
		for(int i=0; i < 6; i++)
		{
			int V=0;
			if(DataType == TYPE_WEI_QIANSAN_HOUSAN || DataType == TYPE_WEI_SHUANG_DAN)
			{
				V=(*DataList)[Index].m_HongQiu[i]%10;
			
			}
			else if(DataType == TYPE_HE_QIANSAN_HOUSAN || DataType == TYPE_HE_SHUANG_DAN)
			{
				V=(*DataList)[Index].m_HongQiu[i]%10+(*DataList)[Index].m_HongQiu[i]/10;
			}
			else 
			{
				V=abs((*DataList)[Index].m_HongQiu[i]%10-(*DataList)[Index].m_HongQiu[i]/10);
			}
			
			V=V%10;
			TempArray[V]++;
		}

		CString Text=" ";
		for(int i=0; i < 10; i++)
		{
			if(TempArray[i])
			{
				CString Temp;
				Temp.Format("%d",i);
				Text+=Temp;
			}
		}

		Text=(*DataList)[Index].m_QiShu+Text;
		m_ListCtrl3.SetItemText(Index,0,Text);
	}


	int ListInsertPos=0;
	map<int,map<int,vector<sDataInfo>>>::iterator it=m_AllData.find(DataType);
	if(it != m_AllData.end())
	{
		map<int,vector<sDataInfo>>::iterator it2=it->second.begin();
		
		int ListIndex=1;
		while(it2 != it->second.end())
		{
			int InsertPos=0;
			for(int Index = 0; Index < it2->second.size(); Index++)
			{
				CString Text;
				Text.Format("%d",it2->second[Index].m_Data);
				Style.m_DrawData.m_TextData.m_BGColor = it2->second[Index].m_Color;
				m_ListCtrl3.SetItemText(InsertPos,ListIndex,Text);
				m_ListCtrl3.SetItemSpecialStyle(InsertPos,ListIndex,Style);
				InsertPos++;
				
			}

			ListIndex++;
			it2++;
		}
	}
}
void CDlgLianHaoHongQiu::OnBnClickedWeishuShuangdanBtn2()
{
	m_YanType     = TYPE_WEI;
	m_YanDataType = TYPE_WEI_SINGLE;
	FillSingleDanDataByType(TYPE_WEI,TYPE_WEI_SINGLE);
}

void CDlgLianHaoHongQiu::OnBnClickedHeshuShuangdanBtn2()
{
	m_YanType     = TYPE_HE;
	m_YanDataType = TYPE_HE_SINGLE;
	FillSingleDanDataByType(TYPE_HE,TYPE_HE_SINGLE);
}

void CDlgLianHaoHongQiu::OnBnClickedChashuShuangdanBtn2()
{
	m_YanType     = TYPE_CHA;
	m_YanDataType = TYPE_CHA_SINGLE;
	FillSingleDanDataByType(TYPE_CHA,TYPE_CHA_SINGLE);
}



//填充单胆尾
void CDlgLianHaoHongQiu::FillSingleDanDataByType(eYanType YanType,eYanDataType DataType)
{
	/*m_ListCtrl.ShowWindow(SW_HIDE);
	m_ListCtrl2.ShowWindow(SW_HIDE);
	m_ListCtrl3.ShowWindow(SW_SHOW);
	m_ListCtrl3.DeleteAllItems();
	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;
	Style.m_DrawData.m_TextData.m_IsFillBG=true;

	vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
	vector<sShuangSeQiu>* QiuShun=CDataManageCenter::GetInstance()->GetDataListByChuHao();

	for(int Index = 0; Index < (int)DataList->size(); Index++)
	{
		m_ListCtrl3.InsertItem(Index,"");
		int TempArray[10];
		memset(TempArray,0,10*sizeof(int));
		int ListColIndex=1;

		int TempData1=0;

		for(int i=0; i < QIU_XUN-1; i++)
		{
			int TempData=0;

			TempData= (*DataList)[Index].m_HongQiu[i]%10+(*DataList)[Index].m_HongQiu[i+1]%10;
			TempData=TempData%10;
			FillSingleDanListData(m_ListCtrl3,DataList,TempData,Index,ListColIndex,YanType);

			TempData=abs((*DataList)[Index].m_HongQiu[i]%10-(*DataList)[Index].m_HongQiu[i+1]%10);
			TempData=TempData%10;
			FillSingleDanListData(m_ListCtrl3,DataList,TempData,Index,ListColIndex,YanType);

			TempData=((*DataList)[Index].m_HongQiu[i]%10)*((*DataList)[Index].m_HongQiu[i+1]%10);
			TempData=TempData%10;
			FillSingleDanListData(m_ListCtrl3,DataList,TempData,Index,ListColIndex,YanType);

		}
	}*/
}