// suoshuiDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "suoshui.h"
#include "suoshuiDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//获取模块路径
CString GetAppCurrentPath()
{
	CString server_ip;
	CString StrDes=_T("");
	::GetModuleFileName(NULL,StrDes.GetBuffer(MAX_PATH),MAX_PATH); 
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


// CsuoshuiDlg 对话框




CsuoshuiDlg::CsuoshuiDlg(CWnd* pParent /*=NULL*/)
: CDialog(CsuoshuiDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CsuoshuiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CsuoshuiDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK8, &CsuoshuiDlg::OnBnClickedOk)
	//ON_BN_CLICKED(IDOK2, &CsuoshuiDlg::OnBnClickedOk2)
	ON_BN_CLICKED(IDOK5, &CsuoshuiDlg::OnBnClickedOk5)
END_MESSAGE_MAP()


// CsuoshuiDlg 消息处理程序

BOOL CsuoshuiDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CsuoshuiDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CsuoshuiDlg::OnPaint()
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
HCURSOR CsuoshuiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CsuoshuiDlg::OnBnClickedOk()
{
	CString FilePath=GetAppCurrentPath()+"tiaojian.txt";
	DWORD Flag = OPEN_EXISTING;
	HANDLE FileHandle=CreateFile(FilePath,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL,Flag,FILE_ATTRIBUTE_NORMAL,NULL);
	if(FileHandle == INVALID_HANDLE_VALUE)
		return ;
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

}


//解析数据
void CsuoshuiDlg::ParseData(CString& StrData,map<CString,vector<int>>& MapData)
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
		if(!Temp.IsEmpty() && Temp.Find("#") == -1)
		{
			vector<int> Data=this->GetDataList(Temp);
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
void CsuoshuiDlg::Combine(map<CString,vector<int>> MapData)
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

				if(it->first.Find("胆V或") != -1)
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

				if(it->first.Find("定胆或") != -1)
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

					if(QieCount > 0 )
						RealWantCount++;
					continue;
				}

				if(it->first.Find("杀胆V") != -1)
				{
					WantCount++;
					int QieCount=0;
					for(int i=1; i<=m; i++)      
					{
						int TempData=MapData["球数"][order[i]]%10;
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


				if(it->first.Find("红一杀") != -1)
				{
					WantCount++;
					bool IsWant=true;
					int TempData=MapData["球数"][order[1]];

					for(int j=0; j < it->second.size();j++)
					{
						if(TempData == it->second[j])
						{
							IsWant=false;
							break;
						}

					}

					if(IsWant)
						RealWantCount++;

					continue;
				}

				if(it->first.Find("红一") != -1)
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

				if(it->first.Find("红二杀") != -1)
				{
					WantCount++;
					bool IsWant=true;
					int TempData=MapData["球数"][order[2]];

					for(int j=0; j < it->second.size();j++)
					{
						if(TempData == it->second[j])
						{
							IsWant=false;
							break;
						}

					}

					if(IsWant)
						RealWantCount++;

					continue;
				}

				if(it->first.Find("红二") != -1)
				{
					WantCount++;
					bool IsWant=false;
					int TempData=MapData["球数"][order[2]];

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

				if(it->first.Find("红三杀") != -1)
				{
					WantCount++;
					bool IsWant=true;
					int TempData=MapData["球数"][order[3]];

					for(int j=0; j < it->second.size();j++)
					{
						if(TempData == it->second[j])
						{
							IsWant=false;
							break;
						}

					}

					if(IsWant)
						RealWantCount++;

					continue;
				}

				if(it->first.Find("红三") != -1)
				{
					WantCount++;
					bool IsWant=false;
					int TempData=MapData["球数"][order[3]];

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

				if(it->first.Find("红四杀") != -1)
				{
					WantCount++;
					bool IsWant=true;
					int TempData=MapData["球数"][order[4]];

					for(int j=0; j < it->second.size();j++)
					{
						if(TempData == it->second[j])
						{
							IsWant=false;
							break;
						}

					}

					if(IsWant)
						RealWantCount++;

					continue;
				}

				if(it->first.Find("红四") != -1)
				{
					WantCount++;
					bool IsWant=false;
					int TempData=MapData["球数"][order[4]];

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

				if(it->first.Find("红五杀") != -1)
				{
					WantCount++;
					bool IsWant=true;
					int TempData=MapData["球数"][order[5]];

					for(int j=0; j < it->second.size();j++)
					{
						if(TempData == it->second[j])
						{
							IsWant=false;
							break;
						}

					}

					if(IsWant)
						RealWantCount++;

					continue;
				}


				if(it->first.Find("红五") != -1)
				{
					WantCount++;
					bool IsWant=false;
					int TempData=MapData["球数"][order[5]];

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

				if(it->first.Find("红六杀") != -1)
				{
					WantCount++;
					bool IsWant=true;
					int TempData=MapData["球数"][order[6]];

					for(int j=0; j < it->second.size();j++)
					{
						if(TempData == it->second[j])
						{
							IsWant=false;
							break;
						}

					}

					if(IsWant)
						RealWantCount++;

					continue;
				}

				if(it->first.Find("红六") != -1)
				{
					WantCount++;
					bool IsWant=false;
					int TempData=MapData["球数"][order[6]];

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

				if(it->first.Find("极距杀") != -1)
				{
					WantCount++;
					bool IsWant=true;
					int TempData=MapData["球数"][order[6]]-MapData["球数"][order[1]];

					for(int j=0; j < it->second.size();j++)
					{
						if(TempData == it->second[j])
						{
							IsWant=false;
							break;
						}

					}

					if(IsWant)
						RealWantCount++;

					continue;
				}


				if(it->first.Find("胆组") != -1)
				{
					int EqualCount=0;
					if(it->first.Find("胆组1") != -1)
						EqualCount=1;
					else if(it->first.Find("胆组2") != -1)
						EqualCount=2;
					else if(it->first.Find("胆组3") != -1)
						EqualCount=3;
					else if(it->first.Find("胆组4") != -1)
						EqualCount=4;
					else if(it->first.Find("胆组5") != -1)
						EqualCount=5;
					else
						EqualCount=6;

					int IsXiaoYu=1;
					if(it->first.Find("-0") != -1)
					{
						IsXiaoYu=2;
					}
					else if(it->first.Find("-") != -1)
						IsXiaoYu=1;
					else
						IsXiaoYu=0;

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

					if(IsXiaoYu)
					{
						if(IsXiaoYu == 1)
						{
							if(QieCount <= EqualCount && QieCount > 0)
								RealWantCount++;
						}
						else
						{
							if(QieCount <= EqualCount)
								RealWantCount++;
						}
					}else
					{
						if(QieCount == EqualCount )
							RealWantCount++;
					}


					continue;
				}



				if(it->first.Find("前三尾杀") != -1)
				{

					WantCount++;
					bool IsWant=true;
					int QieCount=0;
					for(int i=1; i<=3; i++)      
					{
						int TempData=MapData["球数"][order[i]]%10;
						for(int j=0; j < it->second.size();j++)
						{
							if(TempData == it->second[j])
							{
								IsWant=false;
								break;
							}
						}
					}

					if(IsWant)
						RealWantCount++;

					continue;
				}

				if(it->first.Find("前三尾") != -1)
				{
					WantCount++;
					bool IsWant=false;
					int QieCount=0;
					for(int i=1; i<=3; i++)      
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
					}

					if(IsWant)
						RealWantCount++;

					continue;
				}


				if(it->first.Find("前三合杀") != -1)
				{
					WantCount++;
					bool IsWant=true;
					for(int i=1; i<=3; i++)      
					{
						int TempData=MapData["球数"][order[i]]%10+MapData["球数"][order[i]]/10;
						for(int j=0; j < it->second.size();j++)
						{
							if(TempData == it->second[j])
							{
								IsWant=false;
								break;
							}
						}
					}

					if(IsWant)
						RealWantCount++;

					continue;
				}

				if(it->first.Find("前三合") != -1)
				{
					WantCount++;
					bool IsWant=false;
					for(int i=1; i<=3; i++)      
					{
						int TempData=MapData["球数"][order[i]]%10+MapData["球数"][order[i]]/10;
						for(int j=0; j < it->second.size();j++)
						{
							if(TempData == it->second[j])
							{
								IsWant=true;
								break;
							}
						}
					}

					if(IsWant)
						RealWantCount++;

					continue;
				}

				if(it->first.Find("前三差杀") != -1)
				{
					WantCount++;
					bool IsWant=true;
					for(int i=1; i<=3; i++)      
					{
						int TempData=abs(MapData["球数"][order[i]]%10-MapData["球数"][order[i]]/10);
						for(int j=0; j < it->second.size();j++)
						{
							if(TempData == it->second[j])
							{
								IsWant=false;
								break;
							}
						}
					}

					if(IsWant)
						RealWantCount++;

					continue;
				}

				if(it->first.Find("前三差") != -1)
				{

					WantCount++;
					bool IsWant=false;
					for(int i=1; i<=3; i++)      
					{
						int TempData=MapData["球数"][order[i]]%10-MapData["球数"][order[i]]/10;
						for(int j=0; j < it->second.size();j++)
						{
							if(TempData == it->second[j])
							{
								IsWant=true;
								break;
							}
						}
					}

					if(IsWant)
						RealWantCount++;

					continue;
				}


				if(it->first.Find("后三尾杀") != -1)
				{

					WantCount++;
					bool IsWant=true;
					int QieCount=0;
					for(int i=4; i<=m; i++)      
					{
						int TempData=MapData["球数"][order[i]]%10;
						for(int j=0; j < it->second.size();j++)
						{
							if(TempData == it->second[j])
							{
								IsWant=false;
								break;
							}
						}
					}

					if(IsWant)
						RealWantCount++;

					continue;
				}

				if(it->first.Find("后三尾") != -1)
				{

					WantCount++;
					bool IsWant=false;
					int QieCount=0;
					for(int i=4; i<=m; i++)      
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
					}

					if(IsWant)
						RealWantCount++;

					continue;
				}


				if(it->first.Find("后三合杀") != -1)
				{
					WantCount++;
					bool IsWant=true;
					for(int i=4; i<=m; i++)      
					{
						int TempData=MapData["球数"][order[i]]%10+MapData["球数"][order[i]]/10;
						for(int j=0; j < it->second.size();j++)
						{
							if(TempData == it->second[j])
							{
								IsWant=false;
								break;
							}
						}
					}

					if(IsWant)
						RealWantCount++;

					continue;
				}

				if(it->first.Find("后三合") != -1)
				{
					WantCount++;
					bool IsWant=false;
					for(int i=4; i<=m; i++)      
					{
						int TempData=MapData["球数"][order[i]]%10+MapData["球数"][order[i]]/10;
						for(int j=0; j < it->second.size();j++)
						{
							if(TempData == it->second[j])
							{
								IsWant=true;
								break;
							}
						}
					}

					if(IsWant)
						RealWantCount++;

					continue;
				}

				if(it->first.Find("后三差杀") != -1)
				{
					WantCount++;
					bool IsWant=true;
					for(int i=4; i<=m; i++)      
					{
						int TempData=abs(MapData["球数"][order[i]]%10-MapData["球数"][order[i]]/10);
						for(int j=0; j < it->second.size();j++)
						{
							if(TempData == it->second[j])
							{
								IsWant=false;
								break;
							}
						}
					}

					if(IsWant)
						RealWantCount++;

					continue;
				}

				if(it->first.Find("后三差") != -1)
				{
					WantCount++;
					bool IsWant=false;
					for(int i=4; i<=m; i++)      
					{
						int TempData=MapData["球数"][order[i]]%10-MapData["球数"][order[i]]/10;
						for(int j=0; j < it->second.size();j++)
						{
							if(TempData == it->second[j])
							{
								IsWant=true;
								break;
							}
						}
					}

					if(IsWant)
						RealWantCount++;

					continue;
				}


				if(it->first.Find("尾不同出") != -1)
				{
					WantCount++;
					bool IsWant=false;
					int TempArray[10];
					memset(TempArray,0,10*sizeof(int));
					for(int i=1; i<=m; i++)      
					{
						int TempData=MapData["球数"][order[i]]%10;
						for(int j=0; j < it->second.size();j++)
						{
							if(TempData == it->second[j])
							{
								TempArray[TempData]++;
								IsWant=true;
								break;
							}
						}
					}

					int QieCount=0;
					for(int i=0; i < 10; i++)
					{
						if(TempArray[i])
							QieCount++;
					}

					if(it->second.size() != QieCount || QieCount == 0)
						RealWantCount++;
					continue;
				}


				if(it->first.Find("合不同出") != -1)
				{
					WantCount++;
					bool IsWant=false;
					int TempArray[10];
					memset(TempArray,0,10*sizeof(int));
					for(int i=1; i<=m; i++)      
					{
						int TempData=MapData["球数"][order[i]]%10+MapData["球数"][order[i]]/10;
						for(int j=0; j < it->second.size();j++)
						{
							if(TempData == it->second[j])
							{
								TempArray[TempData]++;
								IsWant=true;
								break;
							}
						}
					}

					int QieCount=0;
					for(int i=0; i < 10; i++)
					{
						if(TempArray[i])
							QieCount++;
					}

					if(it->second.size() != QieCount || QieCount == 0)
						RealWantCount++;
					continue;
				}

				if(it->first.Find("差不同出") != -1)
				{
					WantCount++;
					bool IsWant=false;
					int TempArray[10];
					memset(TempArray,0,10*sizeof(int));
					for(int i=1; i<=m; i++)      
					{
						int TempData=abs(MapData["球数"][order[i]]%10-MapData["球数"][order[i]]/10);
						for(int j=0; j < it->second.size();j++)
						{
							if(TempData == it->second[j])
							{
								TempArray[TempData]++;
								IsWant=true;
								break;
							}
						}
					}

					int QieCount=0;
					for(int i=0; i < 10; i++)
					{
						if(TempArray[i])
							QieCount++;
					}

					if(it->second.size() != QieCount || QieCount == 0)
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
					if(i == 1)
						Temp.Format("%02d",TempData);
					else
						Temp.Format(" %02d",TempData);
					OutStr+=Temp;
				}


				CString LanQiu;
				LanQiu.Format(":%02d",MapData["篮球"][0]);
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
vector<int> CsuoshuiDlg::GetDataList(CString& StrData)
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
		DataList.push_back(TempData);
		StartPos = EndPos+1;
	}

	return DataList;
}


void CsuoshuiDlg::OnBnClickedOk2()
{
	/*CString FilePath=GetAppCurrentPath()+"zuxuan_tiaojian.txt";
	DWORD Flag = OPEN_EXISTING;
	HANDLE FileHandle=CreateFile(FilePath,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL,Flag,FILE_ATTRIBUTE_NORMAL,NULL);
	if(FileHandle == INVALID_HANDLE_VALUE)
	return ;
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
	CloseHandle(FileHandle);*/
}

void CsuoshuiDlg::OnBnClickedOk5()
{
	CString FilePath=GetAppCurrentPath()+"3d_tiaojian.txt";
	DWORD Flag = OPEN_EXISTING;
	HANDLE FileHandle=CreateFile(FilePath,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL,Flag,FILE_ATTRIBUTE_NORMAL,NULL);
	if(FileHandle == INVALID_HANDLE_VALUE)
		return ;
	DWORD Size = ::GetFileSize(FileHandle,NULL);
	char* Buffer = new char[Size+1];
	memset(Buffer,'\0',Size+1);
	DWORD ReadBytes=0;
	::ReadFile(FileHandle,Buffer,Size,&ReadBytes,NULL);
	CString StrData=CString(Buffer);
	map<CString,vector<int>> MapData;
	ParseData(StrData,MapData);
	Combine3D(MapData);
	delete []Buffer;
	CloseHandle(FileHandle);
}

//组合数据
void CsuoshuiDlg::Combine3D(map<CString,vector<int>> MapData)
{
	const int DATA=9;

	CString WriteStr;
	int count = 0;   
	int AllCount=0;

	for(int a=0; a <= DATA; a++)
	{
		for(int b=0; b <= DATA; b++)
		{
			for(int c=0; c<= DATA; c++)
			{
				int Array[3];
				Array[0]=a;
				Array[1]=b;
				Array[2]=c;

				int DaXiaoArray[3];
				DaXiaoArray[0]=a;
				DaXiaoArray[1]=b;
				DaXiaoArray[2]=c;

				if(a== 5 && b==4 && c== 2)
				{
					int test=0;
					test++;

				}
				for(int f=0; f < 3; f++)
				{
					for(int k=f+1; k < 3; k++)
					{
						if(DaXiaoArray[k] < DaXiaoArray[f])
						{
							int Temp=DaXiaoArray[k];
							DaXiaoArray[k]=DaXiaoArray[f];
							DaXiaoArray[f]=Temp;
						}
					}
				}

				CString OutStr;

				map<CString,vector<int>>::iterator it=MapData.begin();

				int WantCount=0;
				int RealWantCount=0;
				for(; it != MapData.end(); it++)
				{

					if(it->first.Find("跨值杀") != -1)
					{
						WantCount++;
						int Sum=0;
						bool IsWant=true;
						int Max=0;
						int Min=100;
						for(int i=0; i<=2; i++)      
						{
							if(Min > Array[i])
								Min = Array[i];

							if(Max < Array[i])
								Max=Array[i];
						}

						int  TempData=abs(Max-Min);
						for(int j=0; j < it->second.size();j++)
						{
							if(TempData == it->second[j])
							{
								IsWant=false;
								break;
							}
						}

						if(IsWant)
							RealWantCount++;
						continue;
					}


					if(it->first.Find("和尾杀") != -1)
					{
						WantCount++;
						int Sum=0;
						bool IsWant=true;
						for(int i=0; i<=2; i++)      
						{
							Sum+=Array[i];

						}

						int TempData=Sum%10;
						for(int j=0; j < it->second.size();j++)
						{
							if(TempData == it->second[j])
							{
								IsWant=false;
								break;
							}
						}

						if(IsWant)
							RealWantCount++;
						continue;
					}



					if(it->first.Find("百位杀") != -1)
					{
						WantCount++;
						bool IsWant=true;
						int TempData=Array[0];

						for(int j=0; j < it->second.size();j++)
						{
							if(TempData == it->second[j])
							{
								IsWant=false;
								break;
							}

						}

						if(IsWant)
							RealWantCount++;

						continue;
					}



					if(it->first.Find("十位杀") != -1)
					{
						WantCount++;
						bool IsWant=true;
						int TempData=Array[1];

						for(int j=0; j < it->second.size();j++)
						{
							if(TempData == it->second[j])
							{
								IsWant=false;
								break;
							}

						}

						if(IsWant)
							RealWantCount++;

						continue;
					}


					if(it->first.Find("个位杀") != -1)
					{
						WantCount++;
						bool IsWant=true;
						int TempData=Array[2];

						for(int j=0; j < it->second.size();j++)
						{
							if(TempData == it->second[j])
							{
								IsWant=false;
								break;
							}

						}

						if(IsWant)
							RealWantCount++;

						continue;
					}



					if(it->first.Find("一位杀") != -1)
					{
						WantCount++;
						bool IsWant=true;

						int TempData=DaXiaoArray[0];

						for(int j=0; j < it->second.size();j++)
						{
							if(TempData == it->second[j])
							{
								IsWant=false;
								break;
							}

						}

						if(IsWant)
							RealWantCount++;

						continue;
					}


					if(it->first.Find("二位杀") != -1)
					{
						WantCount++;
						bool IsWant=true;
						int TempData=DaXiaoArray[1];

						for(int j=0; j < it->second.size();j++)
						{
							if(TempData == it->second[j])
							{
								IsWant=false;
								break;
							}

						}

						if(IsWant)
							RealWantCount++;

						continue;
					}


					if(it->first.Find("三位杀") != -1)
					{
						WantCount++;
						bool IsWant=true;
						int TempData=DaXiaoArray[2];

						for(int j=0; j < it->second.size();j++)
						{
							if(TempData == it->second[j])
							{
								IsWant=false;
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
					for(int i=0; i<=2; i++)      
					{
						int TempData=Array[i];	
						CString Temp;
						if(i == 0)
							Temp.Format("%d",TempData);
						else
							Temp.Format(" %d",TempData);
						OutStr+=Temp;
					}


					OutStr+="\r\n";
					WriteStr+=OutStr;
					count++;
				}

				AllCount++;
			}

		}
	}



	CString FilePath2 = GetAppCurrentPath()+_T("\\3D_goumai.txt");
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


	CString FilePath = GetAppCurrentPath()+_T("\\3D_suoshui.txt");
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