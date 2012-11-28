
// ShuangSeQiuDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ShuangSeQiu.h"
#include "ShuangSeQiuDlg.h"

#include <afxinet.h>
#include <afxwin.h>

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
	DDX_Control(pDX, IDC_LIST2, m_ListCtrl2);
	DDX_Control(pDX, IDC_LIST3, m_ListCtrl3);
	DDX_Control(pDX, IDC_CHECK1, m_CheckBtn);
	DDX_Control(pDX, IDC_COMBO1, m_ComboBox);
	DDX_Control(pDX, IDC_COMBO2, m_ShaComboBox);
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
	ON_BN_CLICKED(IDC_LOAD_DATA_BTN2, &CShuangSeQiuDlg::OnBnClickedLoadDataBtn2)
	ON_BN_CLICKED(IDC_BUTTON14, &CShuangSeQiuDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, &CShuangSeQiuDlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON16, &CShuangSeQiuDlg::OnBnClickedButton16)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CShuangSeQiuDlg::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON17, &CShuangSeQiuDlg::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON18, &CShuangSeQiuDlg::OnBnClickedButton18)
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

	m_IsShowByChuQiu = false;

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

	m_DlgZiDongFenXi.Create(CDlgZiDongFenXi::IDD,this);
	m_DlgZiDongFenXi.ShowWindow(SW_HIDE);

	m_DlgTeZongHeFenXi.Create(CDlgTeZongHeFenXi::IDD,this);
	m_DlgTeZongHeFenXi.ShowWindow(SW_HIDE);

	m_DlgDingHongWei.Create(CDlgDingHongWei::IDD,this);
	m_DlgDingHongWei.ShowWindow(SW_HIDE);

	m_DlgNetDataParse.Create(CDlgNetDataParse::IDD,this);
	m_DlgNetDataParse.ShowWindow(SW_HIDE);

	m_ListCtrl.ShowWindow(SW_SHOW);
	m_ListCtrl2.ShowWindow(SW_HIDE);
	m_ListCtrl3.ShowWindow(SW_HIDE);

	m_ComboBox.InsertString(0,_T("搜索红球"));
	m_ComboBox.InsertString(1,_T("搜索篮球"));
	m_ComboBox.InsertString(2,_T("搜索龙头"));
	m_ComboBox.InsertString(3,_T("搜索尾值"));

	InitShaMap();
	map<CString,int>::iterator it=this->m_MapList.begin();
	int Count=0;
	while(it != m_MapList.end())
	{
		m_ShaComboBox.InsertString(Count,it->first);
		Count++;
		it++;
	}
	m_ShaComboBox.SetCurSel(0);
	CenterWindow();

	OnBnClickedLoadDataBtn();
	OnBnClickedLoadDataBtn2();
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
	
	m_ListCtrl.ShowWindow(SW_SHOW);
	m_ListCtrl2.ShowWindow(SW_HIDE);
	m_ListCtrl3.ShowWindow(SW_HIDE);

	m_ListCtrl.DeleteAllItems();

	vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
	for(int Index = 0; Index < (int)DataList->size(); Index++)
	{
		InsertAndSetText(Index,(*DataList)[Index]);
	}
}

//初始化杀类型
void CShuangSeQiuDlg::InitShaMap()
{
		//篮球相关类型
	//FORMULA_SHA_LAN             ,     //杀篮球
	//FORMULA_SHA_LAN_WEI         ,     //杀蓝尾
	//FORMULA_SHA_LAN_LUSHU       ,     //杀篮球路数
	//FORMULA_SHA_LAN_FANWEI      ,     //杀篮球范围 

	//FORMULA_DING_LAN            ,     //定篮球
	//FORMULA_DING_LAN_WEI        ,     //定篮球尾
	//FORMULA_DING_LAN_FANWEI     ,     //定篮球范围
	//FORMULA_DING_LAN_LUSHU      ,     //定篮球路数

	////龙头相关类型
	//FORMULA_SHA_LONG_TOU        ,     //杀龙头
	//FORMULA_SHA_LONG_TOU_WEI    ,     //杀龙头V
	//FORMULA_SHA_LONG_TOU_LUSHU  ,     //杀龙头路数

	//FORMULA_DING_LONG_TOU       ,     //定龙头范围

	////凤尾相关类型
	//FORMULA_SHA_FENG_WEI        ,     //杀凤尾
	//FORMULA_SHA_FENG_WEI_WEI    ,     //杀凤尾V
	//FORMULA_SHA_FENG_WEI_LUSHU  ,     //杀凤尾路数

	//FORMULA_DING_FENG_WEI       ,     //定凤尾范围

	////红球相关类型
	//FORMULA_SHA_HONG            ,    //杀红球
	//FORMULA_SHA_HONG_WEI        ,    //杀红球V

	//FORMULA_DING_HONG_DIAN      ,    //红球点位
	//FORMULA_DING_HONG_WEI       ,    //定红球V
	m_MapList["狂杀红球"]=FORMULA_SHA_HONG;
	m_MapList["狂杀篮球"]=FORMULA_SHA_LAN ;
	m_MapList["狂杀龙头"]=FORMULA_SHA_LONG_TOU;
	m_MapList["狂杀凤尾"]=FORMULA_SHA_FENG_WEI;
	m_MapList["尾不同出"]=FORMULA_WEI_BU_TONG_CHU;
	m_MapList["定红V"]=FORMULA_DING_HONG_WEI;
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
	m_ListCtrl.InsertColumn(9,_TEXT("篮球路数"),	LVCFMT_CENTER,	nWidth);


	nWidth = Rect.Width()/17;
	m_ListCtrl2.InsertColumn(0,_TEXT("期数"),    LVCFMT_CENTER,	nWidth);
	m_ListCtrl2.InsertColumn(1,_TEXT("0V"),	LVCFMT_CENTER,	nWidth); 
	m_ListCtrl2.InsertColumn(2,_TEXT("1V"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl2.InsertColumn(3,_TEXT("2V"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl2.InsertColumn(4,_TEXT("3V"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl2.InsertColumn(5,_TEXT("4V"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl2.InsertColumn(6,_TEXT("5V"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl2.InsertColumn(7,_TEXT("6V"),LVCFMT_CENTER,	nWidth);
	m_ListCtrl2.InsertColumn(8,_TEXT("7V"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl2.InsertColumn(9,_TEXT("8V"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl2.InsertColumn(10,_TEXT("9V"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl2.InsertColumn(11,_TEXT("妍儿定V"),	LVCFMT_CENTER,	2*nWidth);
	m_ListCtrl2.InsertColumn(12,_TEXT("统计出V"),	LVCFMT_CENTER,	2*nWidth);
	m_ListCtrl2.InsertColumn(13,_TEXT("统计未出V"),	LVCFMT_CENTER,	2*nWidth);


	nWidth = Rect.Width()/19;
	m_ListCtrl3.InsertColumn(0,_TEXT("期数"),    LVCFMT_CENTER,	nWidth);
	m_ListCtrl3.InsertColumn(1,_TEXT("0合"),	LVCFMT_CENTER,	nWidth); 
	m_ListCtrl3.InsertColumn(2,_TEXT("1合"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl3.InsertColumn(3,_TEXT("2合"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl3.InsertColumn(4,_TEXT("3合"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl3.InsertColumn(5,_TEXT("4合"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl3.InsertColumn(6,_TEXT("5合"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl3.InsertColumn(7,_TEXT("6合"),LVCFMT_CENTER,	nWidth);
	m_ListCtrl3.InsertColumn(8,_TEXT("7合"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl3.InsertColumn(9,_TEXT("8合"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl3.InsertColumn(10,_TEXT("9合"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl3.InsertColumn(11,_TEXT("妍儿合和"),	LVCFMT_CENTER,	2*nWidth);
	m_ListCtrl3.InsertColumn(12,_TEXT("妍儿合差"),	LVCFMT_CENTER,	2*nWidth);
	m_ListCtrl3.InsertColumn(13,_TEXT("统计出合"),	LVCFMT_CENTER,	2*nWidth);
	m_ListCtrl3.InsertColumn(14,_TEXT("统计未出合"),	LVCFMT_CENTER,	2*nWidth);



	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);
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


	for(int i=0; i < 14; i++)
		m_ListCtrl2.SetColumStyle(i,Style);

	for(int i=0; i < 15; i++)
		m_ListCtrl3.SetColumStyle(i,Style);

	Style.m_DrawData.m_TextData.m_TextColor=RGB(120,195,230);
	m_ListCtrl.SetColumStyle(8,Style);
	
	m_ListCtrl.SetRowHeight(30);
	m_ListCtrl2.SetRowHeight(30);
	m_ListCtrl3.SetRowHeight(30);

	sItemBkData ItemBkData;
	ItemBkData.m_BkFillMode = MODE_FILL_RGB;
	ItemBkData.m_HeightColor = RGB(222,22,100);
	ItemBkData.m_HeightFillMode = MODE_FILL_RGB;
	ItemBkData.m_HeightColor = RGB(100,100,100);
	ItemBkData.m_BkColor = RGB(222,222,222);




	m_ListCtrl.SetItemBkData(ItemBkData);
	m_ListCtrl2.SetItemBkData(ItemBkData);
	m_ListCtrl3.SetItemBkData(ItemBkData);

}


void CShuangSeQiuDlg::OnBnClickedRedBallBtn()
{

	//if(!m_ResultDataList.empty())
	//	m_RedBallDlg.SetDataList(m_ResultDataList);
	//else
		m_RedBallDlg.SetDataList(*CDataManageCenter::GetInstance()->GetDataList());
	m_RedBallDlg.ShowWindow(SW_SHOW);
}

void CShuangSeQiuDlg::OnBnClickedSearchBtn()
{
	m_ListCtrl.ShowWindow(SW_SHOW);
	m_ListCtrl2.ShowWindow(SW_HIDE);
	m_ListCtrl3.ShowWindow(SW_HIDE);

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
	m_ListCtrl.ShowWindow(SW_SHOW);
	m_ListCtrl2.ShowWindow(SW_HIDE);
	m_ListCtrl3.ShowWindow(SW_HIDE);

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
	/*m_DlgLianHaoLanQiu.SetWondowsTitle("狂杀篮球",FORMULA_SHA_LAN);
	m_DlgLianHaoLanQiu.ShowWindow(SW_SHOW);*/
	this->m_DlgDingHongWei.ShowWindow(SW_SHOW);
}

void CShuangSeQiuDlg::OnBnClickedBlueBallBtn4()
{
	m_DlgLianHaoHongQiu.ShowWindow(SW_SHOW);
}

void CShuangSeQiuDlg::OnBnClickedBlueBallBtn3()
{
	ShellExecute(NULL, "open","http://www.haocai188.com", NULL, NULL, SW_SHOWNORMAL);
//	m_DlgHengXiangChaZhi.ShowWindow(SW_SHOW);
}

void CShuangSeQiuDlg::OnBnClickedBlueBallBtn6()
{
	m_ListCtrl.ShowWindow(SW_SHOW);
	m_ListCtrl2.ShowWindow(SW_HIDE);
	m_ListCtrl3.ShowWindow(SW_HIDE);
	m_IsShowByChuQiu= false;
	m_ListCtrl.DeleteAllItems();
	vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
	for(int Index = 0; Index < (int)DataList->size(); Index++)
	{
		InsertAndSetText(Index,(*DataList)[Index]);
	}

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
	m_ListCtrl.ShowWindow(SW_SHOW);
	m_ListCtrl2.ShowWindow(SW_HIDE);
	m_ListCtrl3.ShowWindow(SW_HIDE);
	m_IsShowByChuQiu = true;
	m_ListCtrl.DeleteAllItems();
	vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataListByChuHao();
	for(int Index = 0; Index < (int)DataList->size(); Index++)
	{
		InsertAndSetText(Index,(*DataList)[Index]);
	}
}

void CShuangSeQiuDlg::OnBnClickedButton12()
{
	m_ListCtrl.ShowWindow(SW_SHOW);
	m_ListCtrl2.ShowWindow(SW_HIDE);
	m_ListCtrl3.ShowWindow(SW_HIDE);

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

			for(int HongQiu=0; HongQiu < QIU_XUN; HongQiu++)
			{
				int TempData = (int)TempIt->second.m_HongQiu[HongQiu]%10;
				for(int j=0; j < QIU_XUN; j++)
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
	m_ListCtrl.InsertItem(Row,"");
	if(ShuangSeQiu.m_QiShu == _T("分割"))
		return ;

	m_ListCtrl.SetItemText(Row,0,ShuangSeQiu.m_QiShu);
	for(int HongQiu=0; HongQiu < QIU_XUN; HongQiu++)
	{
		CString Temp;
		Temp.Format("%02d",ShuangSeQiu.m_HongQiu[HongQiu]);
		m_ListCtrl.SetItemText(Row,HongQiu+1,Temp);
	}

	CString HongQiuSum;
	HongQiuSum.Format("%d",ShuangSeQiu.m_HongQiuSum);
	m_ListCtrl.SetItemText(Row,7,HongQiuSum);

	CString LanQiu;
	LanQiu.Format("%d",ShuangSeQiu.m_LanQiu);

	CString Str;
	LanQiu.Format("%02d",ShuangSeQiu.m_LanQiu);

	m_ListCtrl.SetItemText(Row,8,LanQiu);

	CString QuJianBi;
	QuJianBi.Format("%d",ShuangSeQiu.m_LanQiu%3);
	m_ListCtrl.SetItemText(Row,9,QuJianBi);
}

//插入和设置文本
void CShuangSeQiuDlg::InsertAndSetText2(int Row,sShuangSeQiu& ShuangSeQiu,int* pCount)
{
	m_ListCtrl2.InsertItem(Row,"");
	m_ListCtrl2.SetItemText(Row,0,ShuangSeQiu.m_QiShu);
	int DataArray[10];
	memset(DataArray,0,10*sizeof(int));

	for(int HongQiu=0; HongQiu < QIU_XUN; HongQiu++)
	{
		int Data=ShuangSeQiu.m_HongQiu[HongQiu]%10;
		DataArray[Data]++;
		if(pCount != NULL)
		{
			pCount[Data]++;
		}
	}

	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;
	
	CString Chu;
	CString WeiChu;
	CString YanEr;
	for(int i=0; i < 10; i++)
	{
		CString QuJianBi;
		QuJianBi.Format("%d",i);
		if(DataArray[i])
		{

			m_ListCtrl2.SetItemText(Row,i+1,QuJianBi);
			Style.m_DrawData.m_TextData.m_BGColor =RGB(205,250,213);
			Chu+= QuJianBi;
			m_ListCtrl2.SetItemSpecialStyle(Row,i+1,Style);

		}
		else
		{
			WeiChu+= QuJianBi;
			Style.m_DrawData.m_TextData.m_BGColor = RGB(248,183,173);
			m_ListCtrl2.SetItemSpecialStyle(Row,i+1,Style);
		}

	}


	int Array[5]={1,3,5,6,8};
	int DataArray2[10];
	memset(DataArray2,0,10*sizeof(int));


	for(int i=0; i < 10; i++)
	{
		for(int j=0; j < 10; j++)
		{
			if( i != j)
			{
				/*int a=Array[i];
				int b=Array[j];*/
				int a=i;
				int b=j;
				if(DataArray[a]&& DataArray[b])
				{
				int TempData=a+b;
				TempData=TempData%10;
				DataArray2[TempData]++;
				}
			}
		}
	}
	
	
	for(int i=0; i < 10; i++)
	{
		CString QuJianBi;
		QuJianBi.Format("%d",i);
		if(!DataArray2[i])
			YanEr+= QuJianBi;
	}

	Style.m_DrawData.m_TextData.m_BGColor =RGB(205,250,213);
	m_ListCtrl2.SetItemText(Row,11,YanEr);
	m_ListCtrl2.SetItemText(Row,12,Chu);
	m_ListCtrl2.SetItemText(Row,13,WeiChu);
	m_ListCtrl2.SetItemSpecialStyle(Row,11,Style);
	m_ListCtrl2.SetItemSpecialStyle(Row,12,Style);
	m_ListCtrl2.SetItemSpecialStyle(Row,13,Style);


}


//插入和设置文本
void CShuangSeQiuDlg::InsertAndSetText3(int Row,sShuangSeQiu& ShuangSeQiu,int* pCount)
{
	m_ListCtrl3.InsertItem(Row,"");
	m_ListCtrl3.SetItemText(Row,0,ShuangSeQiu.m_QiShu);
	int DataArray[10];
	memset(DataArray,0,10*sizeof(int));

	for(int HongQiu=0; HongQiu < QIU_XUN; HongQiu++)
	{
		int Data=ShuangSeQiu.m_HongQiu[HongQiu]%10+ShuangSeQiu.m_HongQiu[HongQiu]/10;
		Data=Data%10;
		DataArray[Data]++;
		if(pCount != NULL)
		{
			pCount[Data]++;
		}
	}

	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;
	
	CString Chu;
	CString WeiChu;
	CString YanEr;
	CString YanErHeCha;

	for(int i=0; i < 10; i++)
	{
		CString QuJianBi;
		QuJianBi.Format("%d",i);
		if(DataArray[i])
		{

			m_ListCtrl3.SetItemText(Row,i+1,QuJianBi);
			Style.m_DrawData.m_TextData.m_BGColor =RGB(205,250,213);
			Chu+= QuJianBi;
			m_ListCtrl3.SetItemSpecialStyle(Row,i+1,Style);

		}
		else
		{
			WeiChu+= QuJianBi;
			Style.m_DrawData.m_TextData.m_BGColor = RGB(248,183,173);
			m_ListCtrl3.SetItemSpecialStyle(Row,i+1,Style);
		}

	}


	
	int DataArray2[10];
	int DataArray3[10];
	memset(DataArray2,0,10*sizeof(int));
	memset(DataArray3,0,10*sizeof(int));


	for(int i=0; i < 10; i++)
	{
		for(int j=0; j < 10; j++)
		{
			if( i != j)
			{

				int a=i;
				int b=j;
				if(DataArray[a]&& DataArray[b])
				{
					int TempData=a+b;
					TempData=TempData%10;
					DataArray2[TempData]++;

					int TempData3=abs(a-b);
					TempData3=TempData3%10;
					DataArray3[TempData3]++;

				}
			}
		}
	}
	
	
	for(int i=0; i < 10; i++)
	{
		CString QuJianBi;
		QuJianBi.Format("%d",i);
		if(!DataArray2[i])
			YanEr+= QuJianBi;
		
		QuJianBi.Empty();
		QuJianBi.Format("%d",i);
		if(!DataArray3[i])
			YanErHeCha+=QuJianBi;
	}

	Style.m_DrawData.m_TextData.m_BGColor =RGB(205,250,213);
	m_ListCtrl3.SetItemText(Row,11,YanEr);
	m_ListCtrl3.SetItemText(Row,12,YanErHeCha);
	m_ListCtrl3.SetItemText(Row,13,Chu);
	m_ListCtrl3.SetItemText(Row,14,WeiChu);
	m_ListCtrl3.SetItemSpecialStyle(Row,11,Style);
	m_ListCtrl3.SetItemSpecialStyle(Row,12,Style);
	m_ListCtrl3.SetItemSpecialStyle(Row,13,Style);
	m_ListCtrl3.SetItemSpecialStyle(Row,14,Style);


}

void CShuangSeQiuDlg::OnBnClickedButton11()
{
	CFormulaCenter::GetInstance();
	m_DlgLianHaoLanQiu.SetWondowsTitle("红球点位",FORMULA_DING_HONG_DIAN );
	m_DlgLianHaoLanQiu.ShowWindow(SW_SHOW);
}
//void CShuangSeQiuDlg::OnBnClickedButton11()
//{
//	CString Text3;
//	GetDlgItem(IDC_EDIT3)->GetWindowText(Text3);
//	CString Text4;
//	GetDlgItem(IDC_EDIT4)->GetWindowText(Text4);
//	CString Text5;
//	GetDlgItem(IDC_EDIT5)->GetWindowText(Text5);
//	CString Text7;
//	GetDlgItem(IDC_EDIT7)->GetWindowText(Text7);
//
//	DWORD Data1=0,Data2=0,Data3=0,Data4=0;
//	Data1=atoi(Text3.GetBuffer());
//	Data2=atoi(Text4.GetBuffer());
//	Data3=atoi(Text5.GetBuffer());
//	Data4=atoi(Text7.GetBuffer());
//	CString QiShu;
//	if(Data1 == 0 && !Text3.IsEmpty())
//		QiShu=Text3;
//	if(Data2 == 0 && !Text4.IsEmpty())
//		QiShu=Text4;
//
//	if(Data3 == 0 && !Text5.IsEmpty())
//		QiShu=Text5;
//	if(Data4 == 0 && !Text7.IsEmpty())
//		QiShu=Text7;
//
//	
//
//
//	sItemStyle Style;
//	Style.m_ItemType = TEXT_TYPE;
//	Style.m_DrawData.m_TextData.m_TextColor=RGB(22,22,33);
//	Style.m_DrawData.m_TextData.m_TextFont = NULL;
//	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;
//
//	m_ListCtrl.DeleteAllItems();
//	map<CString,sYuCeShuangSeQiu> Temp;
//	Temp=CDataManageCenter::GetInstance()->SearchDataBySuanFa(Data1,Data2,Data3,Data4,QiShu);
//
//	map<CString,sYuCeShuangSeQiu>::iterator it=Temp.begin();
//	if(it == Temp.end())
//		return;
//
//
//	int RowCount=0;
//	for(; it != Temp.end();it++)
//	{
//		map<eSuanFaType,sShuangSeQiu>::iterator TempIt=it->second.m_YuCeQiuMap.begin();
//		int Index=0;
//		for(;TempIt != it->second.m_YuCeQiuMap.end();TempIt++)
//		{
//			InsertAndSetText(RowCount+Index,TempIt->second);
//			Index++;
//			
//			for(int HongQiu=0; HongQiu < QIU_XUN; HongQiu++)
//			{
//				int TempData = TempIt->second.m_HongQiu[HongQiu];
//				for(int j=0; j < QIU_XUN; j++)
//				{
//					if(TempData == Data1 || TempData == Data2 || TempData == Data3 || TempData == Data4)
//					{
//						m_ListCtrl.SetItemSpecialStyle(RowCount+Index-1,HongQiu+1,Style);
//						break;
//					}
//				}
//			}
//
//
//		}
//
//		InsertAndSetText(RowCount+Index,it->second.m_ShuangSeQiu);
//		for(int HongQiu=0; HongQiu < QIU_XUN; HongQiu++)
//		{
//			int TempData = it->second.m_ShuangSeQiu.m_HongQiu[HongQiu];
//			for(int j=0; j < QIU_XUN; j++)
//			{
//				if(TempData == Data1 || TempData == Data2 || TempData == Data3 || TempData == Data4)
//				{
//					m_ListCtrl.SetItemSpecialStyle(RowCount+Index,HongQiu+1,Style);
//					break;
//				}
//			}
//		}
//
//
//		Index++;
//
//		m_ListCtrl.InsertItem(RowCount+Index,"");
//		RowCount+=Index+1;
//
//	}
//}

void CShuangSeQiuDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedButton9();
}

void CShuangSeQiuDlg::OnBnClickedBlueBallBtn()
{
	m_ListCtrl.ShowWindow(SW_HIDE);
	m_ListCtrl2.ShowWindow(SW_HIDE);
	m_ListCtrl3.ShowWindow(SW_SHOW);
	
	m_ListCtrl3.DeleteAllItems();

	vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
	if(DataList->empty())
		return;

	int CountArray[10];
	memset(CountArray,0,sizeof(int)*10);

	for(int Index = 0; Index < (int)DataList->size(); Index++)
	{
		InsertAndSetText3(Index,(*DataList)[Index],CountArray);
	}

	m_ListCtrl3.InsertItem(DataList->size(),"");
	m_ListCtrl3.SetItemText(DataList->size(),0,"合数统计");

	for(int i=0; i < 10; i++)
	{
		CString Text;
		Text.Format(_T("%d"),CountArray[i]);
		m_ListCtrl3.SetItemText(DataList->size(),i+1,Text);
	}
}

void CShuangSeQiuDlg::OnBnClickedButton13()
{
	//m_ShaComboBox.InsertString(0,"狂杀红球");
	//m_ShaComboBox.InsertString(1,"狂杀篮球");
	//m_ShaCmoboBox.InsertString(2,"狂杀龙头");
	//m_ShaCmoboBox.InsertString(3,"狂杀凤尾");
	//m_ShaCmoboBox.InsertString(4,"尾不同出");

	CString Text;
	m_ShaComboBox.GetWindowText(Text);
	map<CString,int>::iterator it= this->m_MapList.begin();
	for(it ; it != m_MapList.end(); it++)
	{
		if(it->first == Text)
		{
			m_DlgLianHaoLanQiu.SetWondowsTitle(Text,(eFormulaType)it->second);
			m_DlgLianHaoLanQiu.ShowWindow(SW_SHOW);
			break;
		}
	}

	
	//this->m_DlgShiFaDingHong.ShowWindow(SW_SHOW);
}

void CShuangSeQiuDlg::OnBnClickedBlueBallBtn5()
{
	m_ListCtrl.ShowWindow(SW_HIDE);
	m_ListCtrl3.ShowWindow(SW_HIDE);
	m_ListCtrl2.ShowWindow(SW_SHOW);
	
	m_ListCtrl2.DeleteAllItems();

	vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
	if(DataList->empty())
		return;

	int CountArray[10];
	memset(CountArray,0,sizeof(int)*10);

	for(int Index = 0; Index < (int)DataList->size(); Index++)
	{
		InsertAndSetText2(Index,(*DataList)[Index],CountArray);
	}

	m_ListCtrl2.InsertItem(DataList->size(),"");
	m_ListCtrl2.SetItemText(DataList->size(),0,"V数统计");

	for(int i=0; i < 10; i++)
	{
		CString Text;
		Text.Format(_T("%d"),CountArray[i]);
		m_ListCtrl2.SetItemText(DataList->size(),i+1,Text);
	}
}

void CShuangSeQiuDlg::OnBnClickedLoadDataBtn2()
{
	::CreateThread(NULL,0,RequestDataInfoThread,this,0,0);
}


DWORD CShuangSeQiuDlg::RequestDataInfoThread(LPVOID lpVoid)
{
    CShuangSeQiuDlg* Self=(CShuangSeQiuDlg*)lpVoid;

	Self->GetDlgItem(IDC_LOAD_DATA_BTN2)->EnableWindow(false);

	vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
	int StartQiShu=0;
	if(DataList->empty())
	{
		__time32_t aa=time(NULL);
		COleDateTime TempTime(aa);
		StartQiShu=TempTime.GetYear();
		StartQiShu=StartQiShu*1000;
		StartQiShu++;
	}
	else
	{
		int TempIndex=DataList->size()-1;
		CString QiShu=(*DataList)[TempIndex].m_QiShu;
		StartQiShu=atoi(QiShu.GetBuffer());
		QiShu.ReleaseBuffer();
		StartQiShu++;
	}

	vector<sShuangSeQiuInfo> InfoList;
	while(true)
	{
		CString Url;
		CString QiHao;
		QiHao.Format(_T("%d"),StartQiShu);
		Url.Format(_T("http://kaijiang.cjcp.com.cn/ssq/%d.html"),StartQiShu);
		CHttpFile* File= NULL;
		try
		{
			//获取服务器列表文件
			CInternetSession Session;
			File=(CHttpFile*)Session.OpenURL(Url);
			if(NULL == File) 
				return -1;

			DWORD Len=0;
			DWORD   Status; 
			DWORD   StatusSize   =   sizeof(Status); 
			DWORD   ContentLen=0,   ContentLenSize   =   sizeof(ContentLenSize); 
			if(File->QueryInfo(HTTP_QUERY_FLAG_NUMBER   |   HTTP_QUERY_STATUS_CODE,  &Status,   &StatusSize,   NULL) &&   Status   ==   HTTP_STATUS_OK) 
				File-> QueryInfo(HTTP_QUERY_FLAG_NUMBER   |   HTTP_QUERY_CONTENT_LENGTH,   &Len,   &ContentLenSize);	

			char Buffer[10*1024+1];
			memset(Buffer,0,10*1024+1);
			DWORD AllLen = 0;
			CString Txt;
			while(true)
			{
				char Buffer[1024*10+1]={0};
				memset(Buffer,0,1024*10+1);
				DWORD ReadLen= Len - AllLen > 10*1024 ? 10*1024 : Len - AllLen;
				DWORD ReadBytes=File->Read(Buffer,ReadLen);
				if(ReadBytes == -1)
					break;
				AllLen += ReadBytes;
				CString TempTxt=CString(Buffer);
				Txt+=TempTxt;

				if(AllLen == Len )
					break;
				

			}

			if(Txt.Find("对不起没有找到该页面") !=-1)
			{
				File->Close();
				delete File; File = NULL;
				break;
			}
			sShuangSeQiuInfo Info;
			Info.m_QiHao = QiHao;
			PaseInfo(Txt,Info);
			InfoList.push_back(Info);
			File->Close();
			delete File; File = NULL;
		}catch(...)
		{
			if(File)
			{
				File->Close();
				delete File; File = NULL;
			}

			break;
		
		}

		StartQiShu++;
	}

	CString FileName=GetAppCurrentPath()+_T("Data.txt");
	HANDLE FileHandle=::CreateFile(FileName,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(FileHandle == INVALID_HANDLE_VALUE)
	{
		FileHandle=::CreateFile(FileName,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	}
	::SetFilePointer(FileHandle,0,0,FILE_END);
	for(int i = 0; i < InfoList.size(); i++)
	{
		DWORD WriteByte=0;
		::WriteFile(FileHandle,InfoList[i].m_ChuQiuShuanXu.GetBuffer(),InfoList[i].m_ChuQiuShuanXu.GetLength(),&WriteByte,NULL);
	}
	CloseHandle(FileHandle);

	Self->GetDlgItem(IDC_LOAD_DATA_BTN2)->EnableWindow(true);

	if(!InfoList.empty())
		Self->OnBnClickedLoadDataBtn();
	return 0;
}


//DWORD CShuangSeQiuDlg::RequestDataInfoThread(LPVOID lpVoid)
//{
//   /* CShuangSeQiuDlg* Self=(CShuangSeQiuDlg*)lpVoid;
//
//	Self->GetDlgItem(IDC_LOAD_DATA_BTN2)->EnableWindow(false);
//
//	vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
//	int StartQiShu=0;
//	if(DataList->empty())
//	{
//		__time32_t aa=time(NULL);
//		COleDateTime TempTime(aa);
//		StartQiShu=TempTime.GetYear();
//		StartQiShu=StartQiShu*1000;
//		StartQiShu++;
//	}
//	else
//	{
//		int TempIndex=DataList->size()-1;
//		CString QiShu=(*DataList)[TempIndex].m_QiShu;
//		StartQiShu=atoi(QiShu.GetBuffer());
//		QiShu.ReleaseBuffer();
//		StartQiShu++;
//	}
//
//	vector<sShuangSeQiuInfo> InfoList;
//	while(true)
//	{*/
//		CString Url;
//		CString QiHao;
//	//	QiHao.Format(_T("%d"),StartQiShu);
//		Url=_T("http://www.google.com.hk");//,StartQiShu;
//		CHttpFile* File= NULL;
//		try
//		{
//			//获取服务器列表文件
//			CInternetSession Session;
//			File=(CHttpFile*)Session.OpenURL(Url);
//			if(NULL == File) 
//				return -1;
//
//			DWORD Len=0;
//			DWORD   Status; 
//			DWORD   StatusSize   =   sizeof(Status); 
//			DWORD   ContentLen=0,   ContentLenSize   =   sizeof(ContentLenSize); 
//			if(File->QueryInfo(HTTP_QUERY_FLAG_NUMBER   |   HTTP_QUERY_STATUS_CODE,  &Status,   &StatusSize,   NULL) &&   Status   ==   HTTP_STATUS_OK) 
//				File-> QueryInfo(HTTP_QUERY_FLAG_NUMBER   |   HTTP_QUERY_CONTENT_LENGTH,   &Len,   &ContentLenSize);	
//
//			char Buffer[10*1024+1];
//			memset(Buffer,0,10*1024+1);
//			DWORD AllLen = 0;
//			CString Txt;
//			while(true)
//			{
//				char Buffer[1024*10+1]={0};
//				memset(Buffer,0,1024*10+1);
//				DWORD ReadLen= Len - AllLen > 10*1024 ? 10*1024 : Len - AllLen;
//				DWORD ReadBytes=File->Read(Buffer,ReadLen);
//				if(ReadBytes == -1)
//					break;
//				AllLen += ReadBytes;
//				CString TempTxt=CString(Buffer);
//				Txt+=TempTxt;
//
//				if(AllLen == Len )
//					break;
//				
//
//			}
//
//			if(Txt.Find("对不起没有找到该页面") !=-1)
//			{
//				File->Close();
//				delete File; File = NULL;
//			//	break;
//			}
//			sShuangSeQiuInfo Info;
//			Info.m_QiHao = QiHao;
//			PaseInfo(Txt,Info);
////			InfoList.push_back(Info);
//			File->Close();
//			delete File; File = NULL;
//		}catch(...)
//		{
//			if(File)
//			{
//				File->Close();
//				delete File; File = NULL;
//			}
//
//			//break;
//		
//		}
//
//	//	StartQiShu++;
//	//}
//
//	CString FileName=GetAppCurrentPath()+_T("Data.txt");
//	HANDLE FileHandle=::CreateFile(FileName,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
//	if(FileHandle == INVALID_HANDLE_VALUE)
//	{
//		FileHandle=::CreateFile(FileName,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
//	}
//	::SetFilePointer(FileHandle,0,0,FILE_END);
//	/*for(int i = 0; i < InfoList.size(); i++)
//	{
//		DWORD WriteByte=0;
//		::WriteFile(FileHandle,InfoList[i].m_ChuQiuShuanXu.GetBuffer(),InfoList[i].m_ChuQiuShuanXu.GetLength(),&WriteByte,NULL);
//	}*/
//	CloseHandle(FileHandle);
//
////	Self->GetDlgItem(IDC_LOAD_DATA_BTN2)->EnableWindow(true);
//
//	//if(!InfoList.empty())
//	//	Self->OnBnClickedLoadDataBtn();
//	return 0;
//}

//解析数据
bool CShuangSeQiuDlg::PaseInfo(CString& Txt,sShuangSeQiuInfo& Info)
{
	int StartPos=0;
	int EndPos=0;
	CString TempStr;
	CString FindStr=_T("<input type=\"button\" value=\"");
	CString LanQiu;
	for(int Index = 0; Index < 7; Index++)
	{
	
		StartPos=Txt.Find(FindStr,StartPos);
		if(StartPos != -1)
		{
			EndPos=Txt.Find(_T("\""),StartPos+FindStr.GetLength()+1);
			if(EndPos != -1)
			{
				CString Value=Txt.Mid(StartPos+FindStr.GetLength(),EndPos-StartPos-FindStr.GetLength());
				TempStr+=_T(" ")+Value;
				if(Index == 6)
					LanQiu=Value;

			}
		}
		StartPos = EndPos+1;
	}
	if(!TempStr.IsEmpty())
	{
		TempStr.TrimLeft();
		TempStr.TrimRight();
		TempStr=TempStr+_T(" ;\r\n");
		Info.m_KaiJiangHao = Info.m_QiHao +_T(" ")+TempStr;
	}

	FindStr=_T("<td class=\"kjhm\"><strong>");
	StartPos=Txt.Find(FindStr,StartPos);
	if(StartPos != -1)
	{
		EndPos = Txt.Find(_T("</strong>"),StartPos+FindStr.GetLength()+1);
		if(EndPos != -1)
		{
			CString Value = Txt.Mid(StartPos+FindStr.GetLength(),EndPos-StartPos-FindStr.GetLength());
			if(!Value.IsEmpty())
			{
				Value.TrimLeft();
				Value.TrimRight();
				Value=Value+_T(" ")+LanQiu+_T(" ;\r\n");
				Info.m_ChuQiuShuanXu = Info.m_QiHao +_T(" ")+Value;
			}
		}
	}

	return true;
}

bool CShuangSeQiuDlg::PaseWangYiInfo(CString& Txt,sWangYiDataInfo& Info,CString ParseFlag)
{
    int StartPos=0;
	int EndPos=0;
	CString TempStr;

	//获取高人气号
	CString FindStr=ParseFlag;
	StartPos=Txt.Find(FindStr,0);
	FindStr=_T("<td><span class=\"red_ball\">");

	CString LanQiu;
	for(int Index = 0; Index < 7; Index++)
	{
		if(Index == 6)
			FindStr=_T("<td><span class=\"blue_ball\">");

		StartPos=Txt.Find(FindStr,StartPos);
		if(StartPos != -1)
		{
			EndPos=Txt.Find(_T("</"),StartPos+FindStr.GetLength()+1);
			if(EndPos != -1)
			{
				CString Value=Txt.Mid(StartPos+FindStr.GetLength(),EndPos-StartPos-FindStr.GetLength());
				sWangYiData TempData;
				TempData.m_Count= 0;
				TempData.m_Data = atoi(Value.GetBuffer());
				Value.ReleaseBuffer();

				CString Value2;
				int TempPos=Txt.Find(_T("<td><em"),EndPos);
				if(TempPos != -1)
				{
					int TempStartPos=Txt.Find(_T("<td>"),TempPos+7);
					int TempEndPos =Txt.Find(_T("</td>"),TempStartPos+4);
					CString TempDataStr = Txt.Mid(TempStartPos+4,TempEndPos-TempStartPos-4);
					TempData.m_Count= atoi(TempDataStr.GetBuffer());
					TempDataStr.ReleaseBuffer();
					
				}

				Info.m_WangYiData.push_back(TempData);
			}
		}
		StartPos = EndPos+1;
	}

	return true;
}

bool CShuangSeQiuDlg::PaseWangYiInfo(CString& Txt,sWangYiDataInfo& Info)
{
	int StartPos=0;
	int EndPos=0;
	CString TempStr;

	//获取期号
	CString FindStr=_T("&nbsp; <b class=\"c_ba2636\">");
	CString EndStr=_T("/b>");
	StartPos=Txt.Find(FindStr,0);
	EndPos = Txt.Find(EndStr,StartPos+FindStr.GetLength());
	CString Value = Txt.Mid(StartPos+FindStr.GetLength()+7,EndPos-StartPos+FindStr.GetLength());
	int QiShu=atoi(Value.GetBuffer());
	Value.ReleaseBuffer();
	QiShu+=1;

	__time32_t aa=time(NULL);
	COleDateTime TempTime(aa);
	CString QiShuStr;
	QiShuStr.Format(_T("%d%d"),TempTime.GetYear(),QiShu);


	//获取高人气号
	sWangYiDataInfo Info1;
	Info1.m_QiShu = QiShuStr;
	Info1.m_GetTime=aa;
	Info1.m_Type = TYPE_GAO_REN_QI;
	PaseWangYiInfo(Txt,Info1,_T("<div class=\"num_detail\" id=\"hotCoolCon1\">"));

	//获取低人气号
	sWangYiDataInfo Info2;
	Info2.m_QiShu = QiShuStr;
	Info2.m_GetTime=aa;
	Info2.m_Type = TYPE_DI_REN_QI;
	PaseWangYiInfo(Txt,Info2,_T("<div class=\"num_detail\" id=\"hotCoolCon2\" style=\"display:none\">"));

	//获取热号
	sWangYiDataInfo Info3;
	Info3.m_QiShu = QiShuStr;
	Info3.m_GetTime=aa;
	Info3.m_Type = TYPE_RE_HAO;
	PaseWangYiInfo(Txt,Info3,_T("<div class=\"num_detail\" id=\"hotCoolCon3\" style=\"display:none\">"));

	//获取冷号
	sWangYiDataInfo Info4;
	Info4.m_QiShu = QiShuStr;
	Info4.m_GetTime=aa;
	Info4.m_Type = TYPE_LENG_HAO;
	PaseWangYiInfo(Txt,Info4,_T("<div class=\"num_detail\" id=\"hotCoolCon4\" style=\"display:none\">"));


	CString FilePath2 = GetAppCurrentPath()+_T("\\net.txt");
	HANDLE FileHandle2=CreateFile(FilePath2,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL,  OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(FileHandle2 == INVALID_HANDLE_VALUE)
		FileHandle2=CreateFile(FilePath2,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL,  	CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

	::SetFilePointer(FileHandle2,0,0,FILE_END);
	CString WriteStr;
	WriteStr=Info1.ToString()+_T("\r\n")+Info2.ToString()+_T("\r\n")+Info3.ToString()+_T("\r\n")+Info4.ToString()+_T("\r\n");
	DWORD WriteBytes=0;
	::WriteFile(FileHandle2,WriteStr.GetBuffer(),WriteStr.GetLength(),&WriteBytes,NULL);
	CloseHandle(FileHandle2);
	return true;
}

//解析中彩擂台数据
bool CShuangSeQiuDlg::PaseZhongCaiInfo(CString& Txt,vector<sZhongCaiDataInfo>& InfoList,int QiShuInt)
{
	
	if(Txt.IsEmpty())
		return false;

	int StartPos=0;
	int EndPos=0;
	CString TempStr;

	//获取期号
	CString FindStr=_T("<h3 class=\"h3t\"><span>");
	CString EndStr=_T("/span>");
	StartPos=Txt.Find(FindStr,0);
	EndPos = Txt.Find(EndStr,StartPos+FindStr.GetLength());
	CString Value = Txt.Mid(StartPos+FindStr.GetLength()+16,EndPos-StartPos+FindStr.GetLength());
	int QiShu=atoi(Value.GetBuffer());
	Value.ReleaseBuffer();

	__time32_t aa=time(NULL);
	COleDateTime TempTime(aa);
	CString QiShuStr;
	QiShuStr.Format("%d%03d",TempTime.GetYear(),QiShu);


	//获取红球统计数
	sZhongCaiDataInfo Info1;
	Info1.m_Type =TYPE_ZHONGCAI_HONG; 
	Info1.m_QiShu=QiShuStr;
	Info1.m_QiShuInt = QiShuInt;

	FindStr=_T("<table class=\"qtab02\"  border=\"0\" cellspacing=\"0\" cellpadding=\"0\">");
	EndStr=_T("</table>");
	StartPos=Txt.Find(FindStr,0);
	EndPos = Txt.Find(EndStr,StartPos+FindStr.GetLength());
	Value = Txt.Mid(StartPos+FindStr.GetLength(),EndPos-StartPos+FindStr.GetLength());
	PaseZhongCaiInfo(Value,Info1,_T("<div class=\"hbg_red\" style"));
	

	//获取篮球统计数
	sZhongCaiDataInfo Info2;
	Info2.m_Type = TYPE_ZHONGCAI_LAN;
	Info2.m_QiShu=QiShuStr;
	Info2.m_QiShuInt = QiShuInt;
	StartPos=Txt.Find(FindStr,EndPos+1);
	EndPos = Txt.Find(EndStr,StartPos+FindStr.GetLength());
	Value = Txt.Mid(StartPos+FindStr.GetLength(),EndPos-StartPos+FindStr.GetLength());
	PaseZhongCaiInfo(Value,Info2,_T("<div class=\"hbg_blue\" style"));


	InfoList.push_back(Info1);
	InfoList.push_back(Info2);

	
	

	return true;
}

bool CShuangSeQiuDlg::PaseZhongCaiInfo(CString& Txt,sZhongCaiDataInfo& Info,CString ParseFlag)
{
	int StartPos=0;
	int EndPos=0;
	CString TempStr;

	CString FindStr=ParseFlag;
	StartPos=Txt.Find(FindStr,0);
	EndPos=Txt.Find(_T("</div>"),StartPos+1);
	int Data=0;
	while(StartPos != -1 && EndPos != -1)
	{
		CString Temp=Txt.Mid(StartPos+FindStr.GetLength(),EndPos-StartPos-FindStr.GetLength());
		CString TempFindStr=_T("<span>");
		int TempStartPos=Temp.Find(TempFindStr);
		int TempEndPos=Temp.Find("</span>");
		CString WantStr=Temp.Mid(TempStartPos+TempFindStr.GetLength(),TempEndPos-TempStartPos-TempFindStr.GetLength());
		Data++;
		int TempData = atoi(WantStr.GetBuffer());
		WantStr.ReleaseBuffer();

		sZhongCaiData ZhongCaiData;
		ZhongCaiData.m_Data = Data;
		ZhongCaiData.m_DataCount = TempData;
		Info.m_DataList.push_back(ZhongCaiData);

		StartPos=Txt.Find(FindStr,EndPos+1);
		EndPos=Txt.Find(_T("</div>"),StartPos+1);
		
	}


	return true;
}

void CShuangSeQiuDlg::OnBnClickedButton14()
{
	m_DlgZongXiangChaZhi.CenterWindow();
	m_DlgZongXiangChaZhi.ShowWindow(SW_SHOW);
}

void CShuangSeQiuDlg::OnBnClickedButton15()
{
	//m_DlgLianHaoLanQiu.SetWondowsTitle("狂杀龙凤",FORMULA_SHA_LONG_TOU);
	//m_DlgLianHaoLanQiu.ShowWindow(SW_SHOW);
	m_DlgHengXiangChaZhi.ShowWindow(SW_SHOW);

}

void CShuangSeQiuDlg::OnBnClickedButton16()
{
	m_DlgTeZongHeFenXi.ShowWindow(SW_SHOW);
}

 DWORD CShuangSeQiuDlg::CombineDataThread(LPVOID lpVoid)
{
	CShuangSeQiuDlg* Self=(CShuangSeQiuDlg*)lpVoid;

	CString FilePath=GetAppCurrentPath()+"tiaojian.txt";
	DWORD Flag = OPEN_EXISTING;
	HANDLE FileHandle=CreateFile(FilePath,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL,Flag,FILE_ATTRIBUTE_NORMAL,NULL);
	if(FileHandle == INVALID_HANDLE_VALUE)
		return 0;

	Self->GetDlgItem(IDC_BUTTON16)->EnableWindow(false);
	DWORD Size = ::GetFileSize(FileHandle,NULL);
	char* Buffer = new char[Size+1];
	memset(Buffer,'\0',Size+1);
	DWORD ReadBytes=0;
	::ReadFile(FileHandle,Buffer,Size,&ReadBytes,NULL);
	CString StrData=CString(Buffer);
	map<CString,vector<int>> MapData;
	ParseData(StrData,MapData);
	Combine(MapData);
	delete []Buffer;
	CloseHandle(FileHandle);
	Self->GetDlgItem(IDC_BUTTON16)->EnableWindow(true);
	return 0;
}


//解析数据
void CShuangSeQiuDlg::ParseData(CString& StrData,map<CString,vector<int>>& MapData)
{
	int StartPos=0;
	int EndPos=0;
	while(EndPos != -1)
	{
		EndPos=StrData.Find(";",StartPos);
		if(EndPos == -1)
			break;

		CString Temp=StrData.Mid(StartPos,EndPos-StartPos);
		StartPos = EndPos+1;
		
		int Pos=Temp.Find("=");
		if(Pos == -1)
			continue;

		CString Name = Temp.Left(Pos);
		if(Name.Find("\r\n") != -1)
			Name=Name.Mid(Name.Find("\r\n")+2);
		Name=Name.Trim();
		Temp=Temp.Mid(Pos+1);
		if(!Temp.IsEmpty())
		{
			vector<int> Data=GetDataList(Temp);
			MapData[Name]=Data;
		}
		
	}

	for(int i = 0; i < MapData["球数"].size(); i++)
	{
		for(int Index = 0 ; Index < MapData["球数"].size(); Index++)
		{
			if(MapData["球数"][i] < MapData["球数"][Index])
			{
				int Temp1 = MapData["球数"][Index];
				MapData["球数"][Index]=MapData["球数"][i];
				MapData["球数"][i] = Temp1;
			}	
		}
	}
}

//组合数据
void CShuangSeQiuDlg::Combine(map<CString,vector<int>> MapData)
{
	int n=0,m=0;

	n=MapData["球数"].size();
	m=MapData["球选"][0];
	m = m > n ? n : m;

	int* order = new int[m+1];    
	for(int i=0; i<=m; i++)
	  order[i] = i-1;            // 注意这里order[0]=-1用来作为循环判断标识
	 

	 CString WriteStr;
	 int count = 0;   
	 int AllCount=0;
	 int k = m;
	 bool flag = true;           // 标志找到一个有效组合
	 while(order[0] == -1)
	 {
		  if(flag)                   // 输出符合要求的组合
		  {   
			  flag = false;
			  CString OutStr;

			  map<CString,vector<int>>::iterator it=MapData.begin();

			  int WantCount=0;
			  int RealWantCount=0;
			  for(; it != MapData.end(); it++)
			  {
				  if(it->first == "龙头")
				  {
					  WantCount++;
					  bool IsWant=false;
					  int TempData=MapData["球数"][order[1]];
					  for(int j=0; j < it->second.size();j++)
					  {
						  if(TempData == it->second[j])
						  {
							  IsWant=true;
							  break;
						  }

					  }

					  if(IsWant)
						RealWantCount++;

					   continue;
				  }

				  if(it->first == "凤尾")
				  {
					  WantCount++;
					  bool IsWant=false;
					  int TempData=MapData["球数"][order[m]];
					  for(int j=0; j < it->second.size();j++)
					  {
						  if(TempData == it->second[j])
						  {
							  IsWant=true;
							  break;
						  }

					  }

					  if(IsWant)
						RealWantCount++;
					  continue;
				  }

				  if(it->first == "胆V或")
				  {
					  WantCount++;
					  bool IsWant=false;
					  for(int i=1; i<=m; i++)      
					  {
						  int TempData=MapData["球数"][order[i]]%10;
						  for(int j=0; j < it->second.size();j++)
						  {
							  if(TempData == it->second[j])
							  {
								  IsWant=true;
								  break;
							  }
						  }

						  if(IsWant)
							  break;
					  }

					  if(IsWant)
						RealWantCount++;
					  continue;
				  }

				  if(it->first == "胆V且")
				  {
					  WantCount++;
					  int Array[10];
					  memset(Array,0,sizeof(int)*10);
					  for(int i=1; i<=m; i++)      
					  {
						  int TempData=MapData["球数"][order[i]]%10;
						  for(int j=0; j < it->second.size();j++)
						  {
							  if(TempData == it->second[j])
							  {
								  Array[TempData]++;
								 break;
							  }
						  }
					  }

					  int QieCount=0;
					  for(int f=0; f < 10; f++)
					  {
						  if(Array[f])
							  QieCount++;
					  }
					  if(QieCount >= it->second.size() )
						RealWantCount++;
					  continue;
				  }


				  if(it->first == "定胆")
				  {
					  WantCount++;
					  int QieCount=0;
					  for(int i=1; i<=m; i++)      
					  {
						  int TempData=MapData["球数"][order[i]];
						  for(int j=0; j < it->second.size();j++)
						  {
							  if(TempData == it->second[j])
							  {
								 QieCount++;
								 break;
							  }
						  }
					  }

					  if(QieCount >= it->second.size() )
						RealWantCount++;
					  continue;
				  }
				  
				  if(it->first.Find("杀号") != -1)
				  {
					  WantCount++;
					  int QieCount=0;
					  for(int i=1; i<=m; i++)      
					  {
						  int TempData=MapData["球数"][order[i]];
						  for(int j=0; j < it->second.size();j++)
						  {
							  if(TempData == it->second[j])
							  {
								 QieCount++;
								 break;
							  }
						  }
					  }

					  if(QieCount < it->second.size() )
						RealWantCount++;
					  continue;
				  }


				  if(it->first.Find("红一大于") != -1)
				  {
					  WantCount++;
					  bool IsWant=false;
					  int TempData=MapData["球数"][order[1]];
				
					  for(int j=0; j < it->second.size();j++)
					  {
						  if(TempData > it->second[j])
						  {
							  IsWant=true;
							  break;
						  }

					  }

					  if(IsWant)
						RealWantCount++;

					   continue;
				  }

				  if(it->first.Find("红一小于") != -1)
				  {
					  WantCount++;
					  bool IsWant=false;
					  int TempData=MapData["球数"][order[1]];
				
					  for(int j=0; j < it->second.size();j++)
					  {
						  if(TempData < it->second[j])
						  {
							  IsWant=true;
							  break;
						  }

					  }

					  if(IsWant)
						RealWantCount++;

					   continue;
				  }

				    if(it->first.Find("红二大于") != -1)
				  {
					  WantCount++;
					  bool IsWant=false;
					  int TempData=MapData["球数"][order[2]];
				
					  for(int j=0; j < it->second.size();j++)
					  {
						  if(TempData > it->second[j])
						  {
							  IsWant=true;
							  break;
						  }

					  }

					  if(IsWant)
						RealWantCount++;

					   continue;
				  }

				  if(it->first.Find("红二小于") != -1)
				  {
					  WantCount++;
					  bool IsWant=false;
					  int TempData=MapData["球数"][order[2]];
				
					  for(int j=0; j < it->second.size();j++)
					  {
						  if(TempData < it->second[j])
						  {
							  IsWant=true;
							  break;
						  }

					  }

					  if(IsWant)
						RealWantCount++;

					   continue;
				  }



				    if(it->first.Find("红三大于") != -1)
				  {
					  WantCount++;
					  bool IsWant=false;
					  int TempData=MapData["球数"][order[3]];
				
					  for(int j=0; j < it->second.size();j++)
					  {
						  if(TempData > it->second[j])
						  {
							  IsWant=true;
							  break;
						  }

					  }

					  if(IsWant)
						RealWantCount++;

					   continue;
				  }

				  if(it->first.Find("红三小于") != -1)
				  {
					  WantCount++;
					  bool IsWant=false;
					  int TempData=MapData["球数"][order[3]];
				
					  for(int j=0; j < it->second.size();j++)
					  {
						  if(TempData < it->second[j])
						  {
							  IsWant=true;
							  break;
						  }

					  }

					  if(IsWant)
						RealWantCount++;

					   continue;
				  }



				    if(it->first.Find("红四大于") != -1)
				  {
					  WantCount++;
					  bool IsWant=false;
					  int TempData=MapData["球数"][order[4]];
				
					  for(int j=0; j < it->second.size();j++)
					  {
						  if(TempData > it->second[j])
						  {
							  IsWant=true;
							  break;
						  }

					  }

					  if(IsWant)
						RealWantCount++;

					   continue;
				  }

				  if(it->first.Find("红四小于") != -1)
				  {
					  WantCount++;
					  bool IsWant=false;
					  int TempData=MapData["球数"][order[4]];
				
					  for(int j=0; j < it->second.size();j++)
					  {
						  if(TempData < it->second[j])
						  {
							  IsWant=true;
							  break;
						  }

					  }

					  if(IsWant)
						RealWantCount++;

					   continue;
				  }



				    if(it->first.Find("红五大于") != -1)
				  {
					  WantCount++;
					  bool IsWant=false;
					  int TempData=MapData["球数"][order[5]];
				
					  for(int j=0; j < it->second.size();j++)
					  {
						  if(TempData > it->second[j])
						  {
							  IsWant=true;
							  break;
						  }

					  }

					  if(IsWant)
						RealWantCount++;

					   continue;
				  }

				  if(it->first.Find("红五小于") != -1)
				  {
					  WantCount++;
					  bool IsWant=false;
					  int TempData=MapData["球数"][order[5]];
				
					  for(int j=0; j < it->second.size();j++)
					  {
						  if(TempData < it->second[j])
						  {
							  IsWant=true;
							  break;
						  }

					  }

					  if(IsWant)
						RealWantCount++;

					   continue;
				  }



				    if(it->first.Find("红六大于") != -1)
				  {
					  WantCount++;
					  bool IsWant=false;
					  int TempData=MapData["球数"][order[6]];
				
					  for(int j=0; j < it->second.size();j++)
					  {
						  if(TempData > it->second[j])
						  {
							  IsWant=true;
							  break;
						  }

					  }

					  if(IsWant)
						RealWantCount++;

					   continue;
				  }

				  if(it->first.Find("红六小于") != -1)
				  {
					  WantCount++;
					  bool IsWant=false;
					  int TempData=MapData["球数"][order[6]];
				
					  for(int j=0; j < it->second.size();j++)
					  {
						  if(TempData < it->second[j])
						  {
							  IsWant=true;
							  break;
						  }

					  }

					  if(IsWant)
						RealWantCount++;

					   continue;
				  }






			  }

			  if(RealWantCount == WantCount)
			  {
					for(int i=1; i<=m; i++)      
					{
						int TempData=MapData["球数"][order[i]];	
						CString Temp;
						Temp.Format("%02d ",TempData);
						OutStr+=Temp;
					}

				   CString LanQiu;
				   LanQiu.Format("%02d",MapData["蓝球"][0]);
				   OutStr+=LanQiu;
				   OutStr+="\r\n";
				   WriteStr+=OutStr;
				   count++;
			  }

			  AllCount++;
			 
		  }

		  order[k]++;                // 在当前位置选择新的数字
		  if(order[k] == n)          // 当前位置已无数字可选，回溯
		  {
		   order[k--] = 0;
		   continue;
		  }     
		  
		  if(k < m)                  // 更新当前位置的下一位置的数字          
		  {
		   order[++k] = order[k-1];
		   continue;
		  }
		  
		  if(k == m)
		   flag = true;
	 }

	 delete[] order;

    CString FilePath2 = GetAppCurrentPath()+_T("\\goumai.txt");
	HANDLE FileHandle2=CreateFile(FilePath2,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(FileHandle2 == INVALID_HANDLE_VALUE)
	{
		AfxMessageBox(_T("打开文件失败！"));
		return;
	}

	DWORD WriteBytes=0;
	::WriteFile(FileHandle2,WriteStr.GetBuffer(),WriteStr.GetLength(),&WriteBytes,NULL);
	WriteStr.ReleaseBuffer();
	CloseHandle(FileHandle2);

	 CString Header;
	 Header.Format("总注数：%02d 缩水后：%02d\r\n",AllCount,count);
	 WriteStr=Header+WriteStr;


    CString FilePath = GetAppCurrentPath()+_T("\\suoshui.txt");
	HANDLE FileHandle=CreateFile(FilePath,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(FileHandle == INVALID_HANDLE_VALUE)
	{
		AfxMessageBox(_T("打开文件失败！"));
		return;
	}
		
	WriteBytes=0;
	::WriteFile(FileHandle,WriteStr.GetBuffer(),WriteStr.GetLength(),&WriteBytes,NULL);
	WriteStr.ReleaseBuffer();
	CloseHandle(FileHandle);
	ShellExecute(NULL, "open",FilePath, NULL, NULL, SW_SHOWNORMAL);

}

//获取数据
vector<int> CShuangSeQiuDlg::GetDataList(CString& StrData)
{
	int StartPos = 0;
	int EndPos   = 0;
	int Index = 0;
	int Count=0;
	vector<int> DataList;

	while(EndPos != -1)
	{
		EndPos=StrData.Find(_T(" "),StartPos);
		if(EndPos == -1)
			break;

		CString Temp = StrData.Mid(StartPos,EndPos-StartPos);
		int TempData = atoi(Temp.GetBuffer());
		Temp.ReleaseBuffer();
		if(TempData != 0)
			DataList.push_back(TempData);
		StartPos = EndPos+1;
	}

	return DataList;
}

void CShuangSeQiuDlg::OnCbnSelchangeCombo2()
{
	
}

void CShuangSeQiuDlg::OnBnClickedButton17()
{
	//::CreateThread(NULL,0,RequestDataWangYiThread,this,0,0);

	m_DlgNetDataParse.ShowWindow(SW_SHOW);
}


//爬取网易数据
DWORD CShuangSeQiuDlg::RequestDataWangYiThread(LPVOID lpVoid)
{
	
		CString Url;
		Url="http://caipiao.163.com/order/preBet_ssq.html";
		CHttpFile* File= NULL;
		try
		{
			//获取服务器列表文件
			CInternetSession Session;
			File=(CHttpFile*)Session.OpenURL(Url);
			if(NULL == File) 
				return -1;

			DWORD Len=0;
			DWORD   Status; 
			DWORD   StatusSize   =   sizeof(Status); 
			DWORD   ContentLen=0,   ContentLenSize   =   sizeof(ContentLenSize); 
			if(File->QueryInfo(HTTP_QUERY_FLAG_NUMBER   |   HTTP_QUERY_STATUS_CODE,  &Status,   &StatusSize,   NULL) &&   Status   ==   HTTP_STATUS_OK) 
				File-> QueryInfo(HTTP_QUERY_FLAG_NUMBER   |   HTTP_QUERY_CONTENT_LENGTH,   &Len,   &ContentLenSize);	

			char Buffer[10*1024+1];
			memset(Buffer,0,10*1024+1);
			DWORD AllLen = 0;
			CString Txt;
			while(true)
			{
				char Buffer[1024*10+1]={0};
				memset(Buffer,0,1024*10+1);
				//DWORD ReadLen= Len - AllLen > 10*1024 ? 10*1024 : Len - AllLen;
				DWORD ReadLen=10*1024;
				DWORD ReadBytes=File->Read(Buffer,ReadLen);
				if(ReadBytes == -1)
					break;
				AllLen += ReadBytes;
				CString TempTxt=CString(Buffer);
				Txt+=TempTxt;

				if(TempTxt.Find("</body>") != -1 || TempTxt.Find("</BODY>") != -1)
					break;
			}

			if(Txt.IsEmpty())
			{
				File->Close();
				delete File; File = NULL;
			}
			
			sWangYiDataInfo Info;
			PaseWangYiInfo(Txt,Info);
			File->Close();
			delete File; File = NULL;
		}catch(...)
		{
			if(File)
			{
				File->Close();
				delete File; File = NULL;
			}
		
		}

	return 0;
}

 //爬取中彩擂台数据
DWORD CShuangSeQiuDlg::RequestDataZhongCaiThread(LPVOID lpVoid)
{
	
	CShuangSeQiuDlg* Self=(CShuangSeQiuDlg*)lpVoid;
	Self->GetDlgItem(IDC_BUTTON18)->EnableWindow(false);
	Self->GetDlgItem(IDC_BUTTON17)->EnableWindow(false);

	vector<sZhongCaiDataInfo>* DataList=CDataManageCenter::GetInstance()->GetZhongCaiDataInfo();
	int StartQiShu=0;
	if(DataList->empty())
	{
		//从2012年爬取开始
		StartQiShu=150;
	}
	else
	{
		int TempIndex=DataList->size()-1;
		StartQiShu=(*DataList)[TempIndex].m_QiShuInt;
		StartQiShu++;
	}

	
	int MaxErrorCount=2;
	if(StartQiShu == 150)
		MaxErrorCount=6;

	vector<sZhongCaiDataInfo> InfoList;
	int ErrorCount=0;
	while(true)
	{

		CString Url;
		Url.Format("http://app.zhcw.com/wwwroot/zhcw/jsp/MediaArena2/leitai.jsp?issueId=%d&utilType=1",StartQiShu);
		CString Txt=GetHttpData(Url);
		if(Txt.IsEmpty() || Txt.Find("<title>HTTP Status 500 - Error report</title>") != -1)
		{
			ErrorCount++;
			StartQiShu++;
			
			if(ErrorCount >= MaxErrorCount)
				break;

			continue;
		}

		ErrorCount=0;
		PaseZhongCaiInfo(Txt,InfoList,StartQiShu);
		StartQiShu++;
	}

	

	CString FilePath2 = GetAppCurrentPath()+ZHONG_CAI_FILE_NAME;
	HANDLE FileHandle2=CreateFile(FilePath2,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL,  OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(FileHandle2 == INVALID_HANDLE_VALUE)
		FileHandle2=CreateFile(FilePath2,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL,  	CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

	::SetFilePointer(FileHandle2,0,0,FILE_END);
	CString WriteStr;
	for(int i=0; i < InfoList.size(); i++)
		WriteStr+=InfoList[i].ToString()+_T("\r\n");

	DWORD WriteBytes=0;
	::WriteFile(FileHandle2,WriteStr.GetBuffer(),WriteStr.GetLength(),&WriteBytes,NULL);
	CloseHandle(FileHandle2);

	if(!InfoList.empty())
		Self->LoadNetData();

	Self->GetDlgItem(IDC_BUTTON17)->EnableWindow(true);
	Self->GetDlgItem(IDC_BUTTON18)->EnableWindow(true);

	return 0;
}

//获取HTTP数据
CString CShuangSeQiuDlg::GetHttpData(CString Url)
{
	CString RetStr;

	CHttpFile* File= NULL;
	try
	{
		//获取服务器列表文件
		CInternetSession Session;
		File=(CHttpFile*)Session.OpenURL(Url);
		if(NULL == File) 
			return RetStr;

		DWORD Len=0;
		DWORD   Status; 
		DWORD   StatusSize   =   sizeof(Status); 
		DWORD   ContentLen=0,   ContentLenSize   =   sizeof(ContentLenSize); 
		if(File->QueryInfo(HTTP_QUERY_FLAG_NUMBER   |   HTTP_QUERY_STATUS_CODE,  &Status,   &StatusSize,   NULL) &&   Status   ==   HTTP_STATUS_OK) 
			File-> QueryInfo(HTTP_QUERY_FLAG_NUMBER   |   HTTP_QUERY_CONTENT_LENGTH,   &Len,   &ContentLenSize);	

		char Buffer[10*1024+1];
		memset(Buffer,0,10*1024+1);
		DWORD AllLen = 0;
		CString Txt;
		while(true)
		{
			char Buffer[1024*10+1]={0};
			memset(Buffer,0,1024*10+1);
			//DWORD ReadLen= Len - AllLen > 10*1024 ? 10*1024 : Len - AllLen;
			DWORD ReadLen=10*1024;
			DWORD ReadBytes=File->Read(Buffer,ReadLen);
			if(ReadBytes == -1)
				break;
			AllLen += ReadBytes;
			CString TempTxt=CString(Buffer);
			Txt+=TempTxt;

			if(TempTxt.Find("</body>") != -1 || TempTxt.Find("</BODY>") != -1)
				break;
		}

		if(Txt.IsEmpty())
		{
			File->Close();
			delete File; File = NULL;
		}

		RetStr=Txt;
		
		File->Close();
		delete File; File = NULL;
	}catch(...)
	{
		if(File)
		{
			File->Close();
			delete File; File = NULL;
		}
	
	}

	return RetStr;

}

void CShuangSeQiuDlg::OnBnClickedButton18()
{
	//http://www.okooo.com/shuangseqiu/ssqsh/en/100/                                      //澳客杀蓝数据
	//http://cp.360.cn/shdd/sha/?ItemID=20344&TopCount=100                                //360杀蓝数据
	//http://app.zhcw.com/wwwroot/zhcw/jsp/MediaArena2/leitai.jsp?issueId=290&utilType=1  //擂台网络数据

	::CreateThread(NULL,0,RequestDataZhongCaiThread,this,0,0);
}

//导入网络分析数据
void CShuangSeQiuDlg::LoadNetData()
{
	CDataManageCenter::GetInstance()->LoadNetData();
}