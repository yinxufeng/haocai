// DlgTongJiJieGuo.cpp : 实现文件
//

#include "stdafx.h"
#include "ShuangSeQiu.h"
#include "DlgTongJiJieGuo.h"

extern CString GetAppCurrentPath();

// CDlgTongJiJieGuo 对话框

IMPLEMENT_DYNAMIC(CDlgTongJiJieGuo, CDialog)

CDlgTongJiJieGuo::CDlgTongJiJieGuo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTongJiJieGuo::IDD, pParent)
{
	m_IsInitData = false;
}

CDlgTongJiJieGuo::~CDlgTongJiJieGuo()
{
}

void CDlgTongJiJieGuo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgTongJiJieGuo, CDialog)
	ON_WM_CLOSE()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CDlgTongJiJieGuo 消息处理程序

BOOL CDlgTongJiJieGuo::OnInitDialog()
{
	CDialog::OnInitDialog();

	/*for(int Index=0; Index < QIU_COUNT; Index++)
	{
		GetDlgItem(IDC_STATIC1+Index)->SetWindowText(_T(""));
	}*/
	CenterWindow();
	return TRUE;  
}

void CDlgTongJiJieGuo::OnClose()
{
	ShowWindow(SW_HIDE);
}

void CDlgTongJiJieGuo::SetTongJieData(vector<sShuangSeQiu>& DataList)
{
	m_TongJiDataList.clear();
	m_TongJiDataList = DataList;
	m_IsInitData=false;
}
void CDlgTongJiJieGuo::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	if(bShow)
	{
		if(!m_IsInitData)
		{
			if(!m_TongJiDataList.empty())
				m_IsInitData=true;
			TongJi();
			for(int Index=0; Index < QIU_COUNT; Index++)
			{
				CString DataStr;
				DataStr.Format(_T("%d"),m_JiShuQi[Index]);
				if(m_JiShuQi[Index] == 0)
					DataStr.Empty();

				GetDlgItem(IDC_STATIC1+Index)->SetWindowText(DataStr);
			}
		}
	}
}

//统计
void CDlgTongJiJieGuo::TongJi()
{
	memset(m_JiShuQi,0,QIU_COUNT*sizeof(int));
	for(int Index=0; Index < m_TongJiDataList.size(); Index++)
	{
		for(int i=0; i < QIU_XUN;i++)
		{
			int Data=m_TongJiDataList[Index].m_HongQiu[i];
			Data--;
			m_JiShuQi[Data]++;
		}
	}

	CString FilePath=GetAppCurrentPath()+_T("tongji.txt");
	DWORD Flag = CREATE_ALWAYS;
	HANDLE FileHandle=CreateFile(FilePath,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL,Flag,FILE_ATTRIBUTE_NORMAL,NULL);
	if(FileHandle == INVALID_HANDLE_VALUE)
		return;


	CString HasData=_T("出号：\r\n");
	CString NotHasData=_T(_T("杀号：\r\n"));

	for(int Index = 0; Index < QIU_COUNT; Index++)
	{
		CString TempData;
		TempData.Format(_T("%02d"),Index+1);

		if(m_JiShuQi[Index])
			HasData+=_T(" ")+TempData;
		else
			NotHasData+=_T(" ")+TempData;
		
	}

	CString DataStr=HasData+_T("\r\n\r\n\r\n")+NotHasData;
	
	DWORD WriteBytes=0;
	::WriteFile(FileHandle,DataStr.GetBuffer(),DataStr.GetLength(),&WriteBytes,NULL);
	CloseHandle(FileHandle);
	ShellExecute(NULL, "open",FilePath, NULL, NULL, SW_SHOWNORMAL);
}
