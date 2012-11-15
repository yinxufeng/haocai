#include "stdafx.h"
#include "HtmlCtrl.h"

CString     CHtmlCtrl::m_HomeUrl;
CString     CHtmlCtrl::m_LastUrl;

vector<CString>      CHtmlCtrl::m_FilterList;


char* UnicodeToUTF8(wchar_t* unicode)
{
	 int len = WideCharToMultiByte(CP_UTF8, 0, unicode, -1, 0, 0, 0, 0 );
	 char* buffer = new char[len+1];
	 WideCharToMultiByte(CP_UTF8, 0, unicode, -1, buffer,len, 0, 0 );
	 buffer[len] = '\0';
	 return buffer;
}



IMPLEMENT_DYNCREATE(CHtmlCtrl, CDHtmlDialog)

CHtmlCtrl::CHtmlCtrl(CString URL,CString PostData,CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(CHtmlCtrl::IDD, CHtmlCtrl::IDH, pParent)
{
	m_StrURL = URL;
	m_PostData=PostData;
	m_AddSession=false;
	m_ProgressHwnd = NULL;
}

CHtmlCtrl::CHtmlCtrl(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(CHtmlCtrl::IDD, CHtmlCtrl::IDH, pParent)
{
	m_IsRecordSession = false;
	m_ProgressHwnd = NULL;
}

CHtmlCtrl::~CHtmlCtrl()
{
}


void CHtmlCtrl::SetHtmlAndCom(CString StrURL, CString StrProg)
{
	HRESULT		hr		= NOERROR;
	m_StrURL = StrURL;
	hr = m_ComDisp.CoCreateInstance(StrProg);
	if(FAILED(hr))
	{
		TRACE(_T("Some error when create com object...\n"));
	}
	SetExternalDispatch(m_ComDisp);
}

void CHtmlCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
}

BOOL CHtmlCtrl::OnInitDialog()
{
	AfxEnableControlContainer();

	CDialog::OnInitDialog();

	RECT rectClient;
	GetClientRect(&rectClient);

	if(!m_lpszTemplateName)
		SetWindowText(m_strDlgCaption);

	CWnd *pCtrl = GetDlgItem(AFX_IDC_BROWSER);
	LPUNKNOWN lpUnk;
	if(pCtrl)
	{
		lpUnk = pCtrl->GetControlUnknown();
		if (lpUnk && SUCCEEDED(lpUnk->QueryInterface(IID_IWebBrowser2, (void **) &m_pBrowserApp)))
		{
			m_wndBrowser.Attach(pCtrl->m_hWnd);
			m_bAttachedControl = TRUE;
		}
	}
	if(m_pBrowserApp == NULL)
	{
		m_wndBrowser.CreateControl(CLSID_WebBrowser, NULL,
			WS_VISIBLE | WS_CHILD, rectClient, this, AFX_IDC_BROWSER);
		lpUnk = m_wndBrowser.GetControlUnknown();
		if(FAILED(lpUnk->QueryInterface(IID_IWebBrowser2, (void**) &m_pBrowserApp)))
		{
			m_wndBrowser.DestroyWindow();
			DestroyWindow();
			return TRUE;
		}
		//m_pBrowserApp->put_Silent(VARIANT_TRUE);
	}
	

	if(m_pBrowserApp)
	{
		////屏蔽掉大部分错误对话框
		////屏蔽掉含有错误Javascript代码的弹出对话框
		m_pBrowserApp->put_Silent(VARIANT_TRUE);
	}

	if(!m_PostData.IsEmpty())
	{
		/*int Len= WideCharToMultiByte( CP_UTF8, 0, (wchar_t *)(LPCTSTR)m_PostData, -1, 0, 0, 0, 0 );
		char* pData = new char[Len+1];
		memset(pData,0,Len+1);
		WideCharToMultiByte( CP_UTF8, 0, (wchar_t *)(LPCTSTR)m_PostData, -1, pData,Len, 0, 0 );
		pData[Len]='\0';*/
	/*	LPCTSTR PostData = m_PostData;
        UINT Len = lstrlen(PostData);
		char* Buffer = new char[Len];
		memcpy(Buffer,PostData,Len);*/
	/*	char Buffer[1024*10]={0};
		sprintf(Buffer,"%S",m_PostData.GetBuffer(0));
		int Len=strlen(Buffer);*/
	//	CString Head=_T("Content-Type: application/x-www-form-urlencoded\r\n");
	
		//CString Head=_T("Content-Type: text/*; charset=UTF-8\r\n");

	//	Navigate(m_StrURL,0,_T("_self"),NULL,(LPVOID)pData,Len-1);
		//delete []Buffer;




		/*char Buffer[1024*10]={0};
		sprintf(Buffer,"%S",m_PostData.GetBuffer(0));
		int Len=strlen(Buffer);*/
		char* Buffer=UnicodeToUTF8(m_PostData.GetBuffer());
		int Len=strlen(Buffer);
		CString Head=_T("Content-Type: application/x-www-form-urlencoded\r\n");
		Navigate(m_StrURL,0,_T("_self"),Head,(LPVOID)Buffer,Len);
	}
	else
		Navigate(m_StrURL,0,_T("_self"));

	return TRUE; 
}


BEGIN_MESSAGE_MAP(CHtmlCtrl, CDHtmlDialog)
END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(CHtmlCtrl)
	DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
	DHTML_EVENT_ONCLICK(_T("href"),OnDownFileUrl)
	//DHTML_EVENT(DISPID_NEWWINDOW3,VTS_PDISPATCH VTS_PBOOL VTS_I4 VTS_BSTR VTS_BSTR,OnNewWindow3)
END_DHTML_EVENT_MAP()

BEGIN_EVENTSINK_MAP(CHtmlCtrl,CDHtmlDialog)
ON_EVENT(CHtmlCtrl,AFX_IDC_BROWSER, 250 /* BeforeNavigate2 */, MyOnBeforeNavigate2, VTS_DISPATCH VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PBOOL) 
//ON_EVENT(CHtmlCtrl,AFX_IDC_BROWSER, DISPID_NEWWINDOW2, OnNewWindow2, VTS_PDISPATCH VTS_PBOOL) 
ON_EVENT(CHtmlCtrl,AFX_IDC_BROWSER,273,OnNewWindow3,VTS_PDISPATCH VTS_PBOOL VTS_I4 VTS_BSTR VTS_BSTR)
//ON_EVENT(CTestDhtmlDlgDlg, AFX_IDC_BROWSER, 251, OnNewWindow2, VTS_PDISPATCH VTS_PBOOL)
END_EVENTSINK_MAP()

HRESULT CHtmlCtrl::OnButtonOK(IHTMLElement* /*pElement*/)
{
	OnOK();
	return S_OK;
}

HRESULT CHtmlCtrl::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	OnCancel();
	return S_OK;
}

//下载URL
HRESULT CHtmlCtrl::OnDownFileUrl(IHTMLElement *pElement)
{
	CString Str;
	GetCurrentUrl(Str);
	AfxMessageBox(Str);
	return S_FALSE;
}


void CHtmlCtrl::OnDocumentComplete(LPDISPATCH pDisp, LPCTSTR szUrl)
{
	
	CDHtmlDialog::OnDocumentComplete(pDisp, szUrl);
	CString mainUrl;
	GetCurrentUrl(mainUrl);

	if(m_IsRecordSession)
	{
		m_Session=GetSession();
		::SendMessage(GetParent()->GetSafeHwnd(),WM_ADD_URL_MSG,(WPARAM)szUrl,(LPARAM)(LPCTSTR)m_Session);
	}
	else
		::SendMessage(GetParent()->GetSafeHwnd(),WM_ADD_URL_MSG,(WPARAM)szUrl,0);
//	::CloseProgressBar(m_ProgressHwnd);
	
	
}

void CHtmlCtrl::OnNavigateComplete(LPDISPATCH pDisp, LPCTSTR szUrl)
{
}

STDMETHODIMP CHtmlCtrl::GetHostInfo(DOCHOSTUIINFO* pInfo)
{
	pInfo->dwFlags = DOCHOSTUIFLAG_THEME;
	return S_OK;
}

BOOL CHtmlCtrl::CanAccessExternal()
{
	return TRUE;
}

void CHtmlCtrl::OnBeforeNavigate(LPDISPATCH pDisp, LPCTSTR szUrl)
{
	/*if(m_IsSaveCooike )
	{
		CComPtr < IDispatch > spDispDoc;
		m_pBrowserApp->get_Document(&spDispDoc);
		m_spHtmlDoc=spDispDoc;
		if(m_spHtmlDoc != NULL )
			m_spHtmlDoc->put_cookie(m_StrCookie);
	}*/
	//CString StrUrl=szUrl;
	//if(m_AddSession)
	//{
	//	StrUrl+=_T("&")+m_Session;
	//}
	//::OpenProgressBar(&m_ProgressHwnd,_T("正在加载网页"));
	CDHtmlDialog::OnBeforeNavigate(pDisp, szUrl);
}

//是否为下载文件URL
BOOL CHtmlCtrl::IsDownLoadFileUrl(CString Url)
{
	if(Url.Find(_T("downloadAppForPC")) != -1 || Url.Find(_T(".zip"))  != -1 || Url.Find(_T(".rar")) != -1 || Url.Find(_T(".exe")) != -1 || Url.Find(_T("downloadAppForWWW")) != -1 || Url.Find(_T(".iso")) != -1)
		return true;
	return false;
}

void CHtmlCtrl::MyOnBeforeNavigate2(LPDISPATCH pDisp,VARIANT FAR* URL,VARIANT FAR* Flags,VARIANT FAR* TargetFrameName,VARIANT FAR* PostData,VARIANT FAR* Headers,BOOL FAR* Cancel)
{
	static CString LastUrl;

	CString StrURL = CString(URL->bstrVal);

	CString KeyStr=_T("failure.html?ret=-3");
	if(StrURL.Find(KeyStr) != -1)
	{
		::PostMessage(GetParent()->GetSafeHwnd(),WM_HTML_ERROR_MSG,1,0);
		*Cancel=true;
		m_LastUrl=LastUrl;
		return;
	}

	if(StrURL.Find(_T("orderDownloadAction.do")) == -1 && StrURL.Find(_T("javascript")) == -1 && StrURL.Find(_T("about:blank")) == -1)
	{
		CString Temp = m_HomeUrl.Left(m_HomeUrl.ReverseFind(':'));
	    CString TempUrl;
		if(StrURL.Find('?') != -1)
			TempUrl=StrURL.Left(StrURL.Find('?'));
		else
			TempUrl=StrURL;

		if(TempUrl.Find(Temp) != -1)
			LastUrl=TempUrl;
	}

}

void CHtmlCtrl::OnNewWindow3(LPDISPATCH* ppDisp,BOOL* Cancel, unsigned long dwFlags, LPCTSTR bstrUrlContext, LPCTSTR bstrUrl)
{
	*Cancel=TRUE;
	CString StrURL=bstrUrl;
    if(IsDownLoadFileUrl(StrURL))
	{

		CComPtr < IDispatch > spDispDoc;
		m_pBrowserApp->get_Document(&spDispDoc);
		m_spHtmlDoc=spDispDoc;
		
		VARIANT Temp2;
		BSTR Cokie;
		BSTR Temp;
		if(m_spHtmlDoc != NULL )
		{
			IHTMLElement* Body=NULL;
			m_spHtmlDoc->get_cookie(&Cokie);
			m_spHtmlDoc->get_body(&Body);
			
			IDispatch* TempDis=NULL;
			Body->get_outerHTML(&Temp);
			Body->get_onclick(&Temp2);
	
		}
		char*pCokie=_com_util::ConvertBSTRToString(Cokie);
		::SendMessage(GetParent()->GetSafeHwnd(),WM_DOWNLOAD_FILE_MSG,(WPARAM)(LPCTSTR)StrURL,(LPARAM)pCokie);
		
	}
	else if( IsSelfUrl(StrURL))
		Navigate(bstrUrl,0,_T("_self"));
	else if(StrURL == _T("about:blank"))
		*Cancel=TRUE;
	else
		*Cancel=FALSE;

}

//保存Cookie
void CHtmlCtrl::SaveCookie(BOOL SaveCooike)
{
	m_IsSaveCooike = SaveCooike;
	if(SaveCooike)
	{
		CComPtr < IDispatch > spDispDoc;
		m_pBrowserApp->get_Document(&spDispDoc);
		m_spHtmlDoc=spDispDoc;
		if(m_spHtmlDoc != NULL )
			m_spHtmlDoc->get_cookie(&m_StrCookie);
		else
			m_IsSaveCooike = FALSE;
	}
}

CString CHtmlCtrl::GetSession()
{
	BSTR Cookie;
	CComPtr < IDispatch > spDispDoc;
	m_pBrowserApp->get_Document(&spDispDoc);
	m_spHtmlDoc=spDispDoc;
	CString Session;
	if(m_spHtmlDoc != NULL )
	{
		m_spHtmlDoc->get_cookie(&Cookie);
		char*pCookie=_com_util::ConvertBSTRToString(Cookie);
		 if(pCookie )
		 {
			 int   Len   =   strlen(pCookie)   +   1; 
			 int   nwLen =  MultiByteToWideChar(CP_ACP,   0,  pCookie,   Len,   NULL,   0); 
			 TCHAR* Temp= new TCHAR[nwLen];
			 MultiByteToWideChar(CP_ACP,   0,   pCookie,   Len,   Temp,   nwLen); 
			 Session=Temp;
			 delete []Temp; Temp = NULL;

			 ////ConvertBSTRToString allocates a string you must delete.
			 delete[]  pCookie; pCookie = NULL;
		 }
	}

	FilterSession(Session);
	return Session;
}

//过滤Session
void CHtmlCtrl::FilterSession(CString& Session)
{
	CString Temp=Session;
	CString FindStr=_T("JSESSIONID=");
	//msisdnCookie=13713716044; WT_FPC=id=2ee8c5fd2cde321d2741309859612562:lv=1309937596078:ss=1309937465796; UT=6A2C8A6DF022C715A693C3B0A22C7CF47688558A5255A456062F8F1460AB145FCF34C2174EC3B6DF; dCookie=924f88a7b76912351666122e56d2dfbb; MMnickname=""; servattr=L; f13713716044=true; lastLoginMsisdn=13713716044; pcppsURL=235e99cdf488bb14f02cba14; JSESSIONID=DBB235FEFC7235E23C338E8F254BCDB7
	int Pos=Temp.Find(FindStr);
	if(Pos != -1)
	{
		int TempPos=Temp.Find(_T(";"),Pos);
		Session=Temp.Mid(Pos+FindStr.GetLength(),TempPos-Pos-FindStr.GetLength());
	}
}

void CHtmlCtrl::GoHome()
{
	m_strCurrentUrl=m_StrURL;
	m_AddSession=TRUE;
	if(m_pBrowserApp)
		m_pBrowserApp->Refresh();
}

void CHtmlCtrl::GoBack()
{
	m_AddSession=TRUE;
	if(m_pBrowserApp)
		m_pBrowserApp->GoBack();
}

void CHtmlCtrl::GoForward()
{
	m_AddSession=TRUE;
	if(m_pBrowserApp)
		m_pBrowserApp->GoForward();
}

void CHtmlCtrl::Reflesh()
{
	m_AddSession=TRUE;
	if(m_pBrowserApp)
		m_pBrowserApp->Refresh();
}

//是否是自己的URL
bool CHtmlCtrl::IsSelfUrl(CString Url)
{
	//return true;
	if(Url.IsEmpty() || m_HomeUrl.IsEmpty())
		return true;

	CString Temp = m_HomeUrl.Left(m_HomeUrl.ReverseFind(':'));
	CString TempUrl = Url.Left(Url.Find('?'));

	for(int Index = 0; Index < m_FilterList.size(); Index++)
	{

		if(m_FilterList[Index].Find(Url) != -1)
			return true;
	}
	CString SpeacilStr=_T("web/sync139Login.do");
	if( TempUrl.Find(Temp) != -1 && Url.Find(SpeacilStr) == -1)
		return true;
	else
		return false;
}

BOOL CHtmlCtrl::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (VK_RETURN == pMsg->wParam || VK_ESCAPE == pMsg->wParam)
			return FALSE;
	}

	return CDHtmlDialog::PreTranslateMessage(pMsg);
}


//跳转到指定URL
void CHtmlCtrl::GoToUrl(CString Url,CString PostData)
{
	if(Url.IsEmpty())
		return;
	if(m_pBrowserApp)
	{
		char* TempPostData=UnicodeToUTF8(PostData.GetBuffer());
		PostData.ReleaseBuffer();
		char* TempUrl=UnicodeToUTF8(Url.GetBuffer());
		//char* TempUrl=::ConvertFromUnicodeToUtf8(Url.GetBuffer());
		BSTR bstrUrl = _com_util::ConvertStringToBSTR(TempUrl);
		DWORD Flag = 0;
		_variant_t   postData(TempPostData);
		_variant_t   tagNameData("self");
		_variant_t   flag(Flag);
		m_pBrowserApp->Navigate(bstrUrl,flag.GetAddress(),tagNameData.GetAddress(),postData.GetAddress(),NULL);
		delete []TempUrl;
		delete []TempPostData;
	}
	

}

//获取当前最后跳转的URL
CString CHtmlCtrl::GetLastUrl()
{
	if(m_LastUrl.IsEmpty())
		return m_HomeUrl;
	return m_LastUrl;
}