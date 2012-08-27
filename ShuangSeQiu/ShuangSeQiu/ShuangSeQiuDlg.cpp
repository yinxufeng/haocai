
// ShuangSeQiuDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ShuangSeQiu.h"
#include "ShuangSeQiuDlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//获取模块路径
CString GetAppCurrentPath()
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

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CShuangSeQiuDlg 对话框




CShuangSeQiuDlg::CShuangSeQiuDlg(CWnd* pParent /*=NULL*/)
: CDialog(CShuangSeQiuDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShuangSeQiuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
	DDX_Control(pDX, IDC_CHECK1, m_CheckBtn);
	DDX_Control(pDX, IDC_COMBO1, m_ComboBox);
}

BEGIN_MESSAGE_MAP(CShuangSeQiuDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_LOAD_DATA_BTN, &CShuangSeQiuDlg::OnBnClickedLoadDataBtn)
	ON_BN_CLICKED(IDC_RED_BALL_BTN, &CShuangSeQiuDlg::OnBnClickedRedBallBtn)
	ON_BN_CLICKED(IDC_SEARCH_BTN, &CShuangSeQiuDlg::OnBnClickedSearchBtn)
	ON_BN_CLICKED(IDC_BLUE_BALL_BTN2, &CShuangSeQiuDlg::OnBnClickedBlueBallBtn2)
	ON_BN_CLICKED(IDC_BLUE_BALL_BTN4, &CShuangSeQiuDlg::OnBnClickedBlueBallBtn4)
	ON_BN_CLICKED(IDC_BLUE_BALL_BTN3, &CShuangSeQiuDlg::OnBnClickedBlueBallBtn3)
	ON_BN_CLICKED(IDC_BLUE_BALL_BTN6, &CShuangSeQiuDlg::OnBnClickedBlueBallBtn6)
	ON_BN_CLICKED(IDC_SEARCH_BTN2, &CShuangSeQiuDlg::OnBnClickedSearchBtn2)
	ON_BN_CLICKED(IDC_SEARCH_BTN3, &CShuangSeQiuDlg::OnBnClickedSearchBtn3)
	ON_BN_CLICKED(IDC_BUTTON9, &CShuangSeQiuDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON6, &CShuangSeQiuDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON10, &CShuangSeQiuDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON8, &CShuangSeQiuDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON12, &CShuangSeQiuDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON11, &CShuangSeQiuDlg::OnBnClickedButton11)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CShuangSeQiuDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BLUE_BALL_BTN, &CShuangSeQiuDlg::OnBnClickedBlueBallBtn)
	ON_BN_CLICKED(IDC_BUTTON13, &CShuangSeQiuDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BLUE_BALL_BTN5, &CShuangSeQiuDlg::OnBnClickedBlueBallBtn5)
END_MESSAGE_MAP()


// CShuangSeQiuDlg 消息处理程序

BOOL CShuangSeQiuDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	InitListHeader();
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_RedBallDlg.Create(CRedBallDlg::IDD,this);
	m_RedBallDlg.ShowWindow(SW_HIDE);

	m_DlgLianHaoHongQiu.Create(CDlgLianHaoHongQiu::IDD,this);
	m_DlgLianHaoHongQiu.ShowWindow(SW_HIDE);

	m_DlgLianHaoLanQiu.Create(CDlgLianHaoLanQiu::IDD,this);
	m_DlgLianHaoLanQiu.ShowWindow(SW_HIDE);
	m_DlgHengXiangChaZhi.Create(CDlgHengXiangChaZhi::IDD,this);
	m_DlgHengXiangChaZhi.ShowWindow(SW_HIDE);

	m_DlgZongXiangChaZhi.Create(CDlgZongXiangChaZhi::IDD,this);
	m_DlgZongXiangChaZhi.ShowWindow(SW_HIDE);

	m_DlgTongJiJieGuo.Create(CDlgTongJiJieGuo::IDD,this);
	m_DlgTongJiJieGuo.ShowWindow(SW_HIDE);

	m_DlgFourEqual.Create(CDlgFourEqual::IDD,this);
	m_DlgFourEqual.ShowWindow(SW_HIDE);

	m_DlgThreeEqual.Create(CThreeEqualDlg::IDD,this);
	m_DlgThreeEqual.ShowWindow(SW_HIDE);

	m_DlgShiFaDingHong.Create(CDlgShiFaDingHong::IDD,this);
	m_DlgShiFaDingHong.ShowWindow(SW_HIDE);

	m_DlgWeiHong.Create(CDlgWeiHong::IDD,this);
	m_DlgWeiHong.ShowWindow(SW_HIDE);

	m_ComboBox.InsertString(0,_T("搜索红球"));
	m_ComboBox.InsertString(1,_T("搜索篮球"));
	m_ComboBox.InsertString(2,_T("搜索龙头"));
	m_ComboBox.InsertString(3,_T("搜索尾值"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CShuangSeQiuDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CShuangSeQiuDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CShuangSeQiuDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CShuangSeQiuDlg::OnBnClickedLoadDataBtn()
{
	CString FilePath=GetAppCurrentPath()+_T("Data.txt");
	CDataManageCenter::GetInstance()->LoadDataFromFile(FilePath,false);
	FilePath=GetAppCurrentPath()+_T("Data2.txt");
	CDataManageCenter::GetInstance()->LoadDataFromFile(FilePath,true);

	m_ListCtrl.DeleteAllItems();

	vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
	for(int Index = 0; Index < (int)DataList->size(); Index++)
	{
		InsertAndSetText(Index,(*DataList)[Index]);
	}
}

//初始化列表头
void CShuangSeQiuDlg::InitListHeader()
{
	CRect Rect;
	//初始化应用程序列表控件
	m_ListCtrl.GetWindowRect(&Rect);
	int nWidth = Rect.Width()/10;
	m_ListCtrl.InsertColumn(0,_TEXT("期数"),    LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(1,_TEXT("红球1"),	LVCFMT_CENTER,	nWidth); 
	m_ListCtrl.InsertColumn(2,_TEXT("红球2"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(3,_TEXT("红球3"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(4,_TEXT("红球4"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(5,_TEXT("红球5"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(6,_TEXT("红球6"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(7,_TEXT("红球之和"),LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(8,_TEXT("篮球"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(9,_TEXT("区间比"),	LVCFMT_CENTER,	nWidth);
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
	m_ListCtrl.SetColumStyle(9,Style);
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


void CShuangSeQiuDlg::OnBnClickedRedBallBtn()
{

	if(!m_ResultDataList.empty())
		m_RedBallDlg.SetDataList(m_ResultDataList);
	else
		m_RedBallDlg.SetDataList(*CDataManageCenter::GetInstance()->GetDataList());
	m_RedBallDlg.ShowWindow(SW_SHOW);
}

void CShuangSeQiuDlg::OnBnClickedSearchBtn()
{
	CString Text;
	GetDlgItem(IDC_EDIT1)->GetWindowText(Text);
	DWORD Data=::atoi(Text.GetBuffer());
	m_ListCtrl.DeleteAllItems();
	vector<sShuangSeQiu>* DataList = NULL;
	vector<sShuangSeQiu> Temp;
	if(Data == 0)
	{
		DataList=CDataManageCenter::GetInstance()->GetDataList();
	}
	else
	{
		Temp=CDataManageCenter::GetInstance()->SearchHongQiu(Data);
		DataList=&Temp;
	}

	m_ResultDataList.clear();
	m_ResultDataList=*DataList;

	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(22,22,33);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;

	for(int Index = 0; Index < (int)DataList->size(); Index++)
	{
		InsertAndSetText(Index,(*DataList)[Index]);
	}

}

void CShuangSeQiuDlg::OnBnClickedSearchBtn2()
{
	CString Text;
	GetDlgItem(IDC_EDIT2)->GetWindowText(Text);
	DWORD Data=::atoi(Text.GetBuffer());
	DWORD Data1=0;
	GetDlgItem(IDC_EDIT1)->GetWindowText(Text);
	Data1=::atoi(Text.GetBuffer());

	m_ListCtrl.DeleteAllItems();
	vector<sShuangSeQiu>* DataList = NULL;
	vector<sShuangSeQiu> Temp;
	if(Data == 0)
	{

		if(Data1== 0)
		{
			DataList=CDataManageCenter::GetInstance()->GetDataList();
		}
		else
		{
			Temp=CDataManageCenter::GetInstance()->SearchHongQiu(Data);
			DataList=&Temp;
		}
	}
	else
	{
		Temp=CDataManageCenter::GetInstance()->SearchHongQiu(m_ResultDataList,Data);
		DataList=&Temp;
	}

	m_ResultDataList.clear();
	m_ResultDataList=*DataList;

	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(22,22,33);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;


	for(int Index = 0; Index < (int)DataList->size(); Index++)
	{
		InsertAndSetText(Index,(*DataList)[Index]);
	}

}

void CShuangSeQiuDlg::OnBnClickedBlueBallBtn2()
{
	m_DlgLianHaoLanQiu.ShowWindow(SW_SHOW);
}

void CShuangSeQiuDlg::OnBnClickedBlueBallBtn4()
{
	m_DlgLianHaoHongQiu.ShowWindow(SW_SHOW);
}

void CShuangSeQiuDlg::OnBnClickedBlueBallBtn3()
{
	m_DlgHengXiangChaZhi.ShowWindow(SW_SHOW);
}

void CShuangSeQiuDlg::OnBnClickedBlueBallBtn6()
{
	m_DlgZongXiangChaZhi.ShowWindow(SW_SHOW);
}



void CShuangSeQiuDlg::OnBnClickedSearchBtn3()
{
	m_DlgTongJiJieGuo.SetTongJieData(m_ResultDataList);
	m_DlgTongJiJieGuo.ShowWindow(SW_SHOW);
}

void CShuangSeQiuDlg::OnBnClickedButton9()
{
	CDataManageCenter::GetInstance()->SetSearchFlag(m_CheckBtn.GetCheck());
	CString Text3;
	GetDlgItem(IDC_EDIT3)->GetWindowText(Text3);
	CString Text4;
	GetDlgItem(IDC_EDIT4)->GetWindowText(Text4);
	CString Text5;
	GetDlgItem(IDC_EDIT5)->GetWindowText(Text5);
	CString Text7;
	GetDlgItem(IDC_EDIT7)->GetWindowText(Text7);

	DWORD Data1=0,Data2=0,Data3=0,Data4=0;
	CString Str;
	if(Text3.Find(":") != -1)
		Str=Text3;
	else
		Data1=atoi(Text3.GetBuffer());

	if(Text4.Find(":") != -1)
		Str=Text4;
	else
		Data2=atoi(Text4.GetBuffer());
	
	if(Text5.Find(":") != -1)
		Str=Text5;
	else
		Data3=atoi(Text5.GetBuffer());

	if(Text7.Find(":") != -1)
		Str=Text7;
	else
		Data4=atoi(Text7.GetBuffer());
	m_ListCtrl.DeleteAllItems();


	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(22,22,33);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;


	vector<sShuangSeQiu> TempList;
	int CurSel=m_ComboBox.GetCurSel();
	switch(CurSel)
	{
	case 1:
		TempList=CDataManageCenter::GetInstance()->SearchDataLanQiu(Data1,Data2,Data3,Data4,Str);
		break;

	case 2:
		TempList=CDataManageCenter::GetInstance()->SearchDataLongTou(Data1,Data2,Data3,Data4,Str);
		break;

	case 3:
		TempList=CDataManageCenter::GetInstance()->SearchDataWeiZhi(Data1,Data2,Data3,Data4,Str);
		break;

	default:
		TempList=CDataManageCenter::GetInstance()->GetSpecialDataList(Data1,Data2,Data3,Data4,Str);
		break;
	}
	vector<sShuangSeQiu>* DataList=&TempList;
	m_ResultDataList.clear();
	m_ResultDataList=*DataList;


	for(int Index = 0; Index < (int)DataList->size(); Index++)
	{
		InsertAndSetText(Index,(*DataList)[Index]);
	}
}

void CShuangSeQiuDlg::OnBnClickedButton6()
{
	m_DlgFourEqual.ShowWindow(SW_SHOW);
}

void CShuangSeQiuDlg::OnBnClickedButton10()
{
	m_DlgThreeEqual.ShowWindow(SW_SHOW);
}

void CShuangSeQiuDlg::OnBnClickedButton8()
{

}

void CShuangSeQiuDlg::OnBnClickedButton12()
{
	m_ListCtrl.DeleteAllItems();
	map<CString,sYuCeShuangSeQiu> Temp;
	Temp=CDataManageCenter::GetInstance()->GetDataBySuanFa();

	map<CString,sYuCeShuangSeQiu>::iterator it=Temp.begin();
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
		map<eSuanFaType,sShuangSeQiu>::iterator TempIt=it->second.m_YuCeQiuMap.begin();
		int Index=0;
		for(;TempIt != it->second.m_YuCeQiuMap.end();TempIt++)
		{
			InsertAndSetText(RowCount+Index,TempIt->second);
			Index++;
			switch(TempIt->first)
			{
			case SUANFA_LANJI_YUCE:
				Style.m_DrawData.m_TextData.m_TextColor=RGB(22,222,222);
				break;
			case 	SUANFA_ACZHI_YUCE:        
				Style.m_DrawData.m_TextData.m_TextColor=RGB(222,22,222);
				break;
			case SUANFA_WEIZHI_YUCE:
				Style.m_DrawData.m_TextData.m_TextColor=RGB(22,22,222);
				break;
			case SUANFA_HEZHI_YUCE:
				Style.m_DrawData.m_TextData.m_TextColor=RGB(22,22,33);

			}

			for(int HongQiu=0; HongQiu < 6; HongQiu++)
			{
				int TempData = (int)TempIt->second.m_HongQiu[HongQiu]%10;
				for(int j=0; j < 6; j++)
				{
					int TempData2=(int)it->second.m_ShuangSeQiu.m_HongQiu[j]%10;
					if(TempData2 == TempData)
					{
						if( TempIt->second.m_HongQiu[HongQiu] == it->second.m_ShuangSeQiu.m_HongQiu[j])
						{
							sItemStyle Style2;
							Style2.m_ItemType = TEXT_TYPE;
							Style2.m_DrawData.m_TextData.m_TextColor=RGB(111,111,111);
							Style2.m_DrawData.m_TextData.m_TextFont = NULL;
							Style2.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;
							m_ListCtrl.SetItemSpecialStyle(RowCount+Index-1,HongQiu+1,Style2);
						}
						else
							m_ListCtrl.SetItemSpecialStyle(RowCount+Index-1,HongQiu+1,Style);
						break;
					}
				}
			}


		}

		InsertAndSetText(RowCount+Index,it->second.m_ShuangSeQiu);
		Index++;

		m_ListCtrl.InsertItem(RowCount+Index,"");
		RowCount+=Index+1;

	}
}

//插入和设置文本
void CShuangSeQiuDlg::InsertAndSetText(int Row,sShuangSeQiu& ShuangSeQiu)
{
	//sItemStyle Style;
	//Style.m_ItemType = TEXT_TYPE;
	//Style.m_DrawData.m_TextData.m_TextColor=RGB(222,0,0);
	//Style.m_DrawData.m_TextData.m_TextFont = NULL;
	//Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;

	m_ListCtrl.InsertItem(Row,"");
	if(ShuangSeQiu.m_QiShu == _T("分割"))
		return ;

	m_ListCtrl.SetItemText(Row,0,ShuangSeQiu.m_QiShu);
	for(int HongQiu=0; HongQiu < 6; HongQiu++)
	{
		CString Temp;
		Temp.Format("%d",ShuangSeQiu.m_HongQiu[HongQiu]);
		m_ListCtrl.SetItemText(Row,HongQiu+1,Temp);
	//	m_ListCtrl.SetItemSpecialStyle(Row,HongQiu+1,Style);
	}

	CString HongQiuSum;
	HongQiuSum.Format("%d",ShuangSeQiu.m_HongQiuSum);
	m_ListCtrl.SetItemText(Row,7,HongQiuSum);

	CString LanQiu;
	LanQiu.Format("%d",ShuangSeQiu.m_LanQiu);
	m_ListCtrl.SetItemText(Row,8,LanQiu);

	CString QuJianBi;
	QuJianBi.Format("%d:%d:%d",ShuangSeQiu.m_QuJian[0],ShuangSeQiu.m_QuJian[1],ShuangSeQiu.m_QuJian[2]);
	m_ListCtrl.SetItemText(Row,9,QuJianBi);
}

void CShuangSeQiuDlg::OnBnClickedButton11()
{
	CString Text3;
	GetDlgItem(IDC_EDIT3)->GetWindowText(Text3);
	CString Text4;
	GetDlgItem(IDC_EDIT4)->GetWindowText(Text4);
	CString Text5;
	GetDlgItem(IDC_EDIT5)->GetWindowText(Text5);
	CString Text7;
	GetDlgItem(IDC_EDIT7)->GetWindowText(Text7);

	DWORD Data1=0,Data2=0,Data3=0,Data4=0;
	Data1=atoi(Text3.GetBuffer());
	Data2=atoi(Text4.GetBuffer());
	Data3=atoi(Text5.GetBuffer());
	Data4=atoi(Text7.GetBuffer());
	CString QiShu;
	if(Data1 == 0 && !Text3.IsEmpty())
		QiShu=Text3;
	if(Data2 == 0 && !Text4.IsEmpty())
		QiShu=Text4;

	if(Data3 == 0 && !Text5.IsEmpty())
		QiShu=Text5;
	if(Data4 == 0 && !Text7.IsEmpty())
		QiShu=Text7;

	


	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(22,22,33);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;

	m_ListCtrl.DeleteAllItems();
	map<CString,sYuCeShuangSeQiu> Temp;
	Temp=CDataManageCenter::GetInstance()->SearchDataBySuanFa(Data1,Data2,Data3,Data4,QiShu);

	map<CString,sYuCeShuangSeQiu>::iterator it=Temp.begin();
	if(it == Temp.end())
		return;


	int RowCount=0;
	for(; it != Temp.end();it++)
	{
		map<eSuanFaType,sShuangSeQiu>::iterator TempIt=it->second.m_YuCeQiuMap.begin();
		int Index=0;
		for(;TempIt != it->second.m_YuCeQiuMap.end();TempIt++)
		{
			InsertAndSetText(RowCount+Index,TempIt->second);
			Index++;
			
			for(int HongQiu=0; HongQiu < 6; HongQiu++)
			{
				int TempData = TempIt->second.m_HongQiu[HongQiu];
				for(int j=0; j < 6; j++)
				{
					if(TempData == Data1 || TempData == Data2 || TempData == Data3 || TempData == Data4)
					{
						m_ListCtrl.SetItemSpecialStyle(RowCount+Index-1,HongQiu+1,Style);
						break;
					}
				}
			}


		}

		InsertAndSetText(RowCount+Index,it->second.m_ShuangSeQiu);
		for(int HongQiu=0; HongQiu < 6; HongQiu++)
		{
			int TempData = it->second.m_ShuangSeQiu.m_HongQiu[HongQiu];
			for(int j=0; j < 6; j++)
			{
				if(TempData == Data1 || TempData == Data2 || TempData == Data3 || TempData == Data4)
				{
					m_ListCtrl.SetItemSpecialStyle(RowCount+Index,HongQiu+1,Style);
					break;
				}
			}
		}


		Index++;

		m_ListCtrl.InsertItem(RowCount+Index,"");
		RowCount+=Index+1;

	}
}

void CShuangSeQiuDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedButton9();
}

void CShuangSeQiuDlg::OnBnClickedBlueBallBtn()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CShuangSeQiuDlg::OnBnClickedButton13()
{
	this->m_DlgShiFaDingHong.ShowWindow(SW_SHOW);
}

void CShuangSeQiuDlg::OnBnClickedBlueBallBtn5()
{
	m_DlgWeiHong.ShowWindow(SW_SHOW);
}
