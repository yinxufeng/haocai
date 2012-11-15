// ceshiDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ceshi.h"
#include "ceshiDlg.h"
#include <atlrx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CceshiDlg 对话框




CceshiDlg::CceshiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CceshiDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CceshiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CceshiDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CceshiDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CceshiDlg 消息处理程序

BOOL CceshiDlg::OnInitDialog()
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

void CceshiDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CceshiDlg::OnPaint()
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
HCURSOR CceshiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CceshiDlg::OnBnClickedOk()
{
// TODO: 在此添加控件通知处理程序代码
//	OnOK();

	 CString strRegex=L"({[a-zA-Z0-9_]+@[a-zA-Z0-9]+[.][a-zA-Z0-9]+[.]?[a-zA-Z0-9]+})";

     CString strInput;

     strInput=L"bae123@domain.com";

 

     CAtlRegExp<CAtlRECharTraitsW> reRule;

     wchar_t *wt = (wchar_t *)(LPCTSTR)strRegex;

     REParseError status = reRule.Parse((const ATL::CAtlRegExp<CAtlRECharTraitsW>::RECHAR *)wt);

 

     if (REPARSE_ERROR_OK != status)

     {

        // return 0;

     }

     CAtlREMatchContext<CAtlRECharTraitsW> mcRule;

     wt = (wchar_t *)(LPCTSTR)strInput;

     if (!reRule.Match((const ATL::CAtlRegExp<CAtlRECharTraitsW>::RECHAR *)wt,&mcRule))

     {

         AfxMessageBox(L"您输入的邮件地址不合法！");

     }

     else
     {

         for (UINT nGroupIndex = 0; nGroupIndex < mcRule.m_uNumGroups; ++nGroupIndex)

         {

              const CAtlREMatchContext<>::RECHAR* szStart = 0;

              const CAtlREMatchContext<>::RECHAR* szEnd = 0;

              mcRule.GetMatch(nGroupIndex, &szStart, &szEnd);

              ptrdiff_t nLength = szEnd - szStart;

              CString strEmailAddress(szStart,  static_cast<int>(nLength));

 

              if(strEmailAddress.Compare(strInput)!=0)

              {

              CString strPrompt;

              strPrompt.Format(L"您输入的邮件地址不合法，您要输入%s 吗！",strEmailAddress);

              AfxMessageBox(strPrompt);

              }

              else

              {

                   AfxMessageBox(L"输入的邮件地址正确！");

              }

 

         }

     }



}
