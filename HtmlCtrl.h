#pragma once

#ifdef _WIN32_WCE
#error "Windows CE 不支持 CDHtmlDialog。"
#endif 

/****************************************************************************
*  描述：　浏览器控件                                                       *
*　创建：　2011.6.15                                                        *
*  作者：  谭军红                                                           *
*                                                                           *
****************************************************************************/

#include "Resource.h"
//#define INITGUID
//#include <initguid.h>
//#include <exdisp.h>
#include <afxdhtml.h>
#include <vector>
using std::vector;


#define WM_ADD_URL_MSG            WM_USER+3000        //新增URL消息
#define WM_DOWNLOAD_FILE_MSG      WM_USER+3001        //文件下载消息
#define WM_HTML_ERROR_MSG         WM_USER+3002        //HTML错误消息

class CHtmlCtrl : public CDHtmlDialog
{
	DECLARE_DYNCREATE(CHtmlCtrl)

public:
	CHtmlCtrl(CString URL,CString PostData=_T(""),CWnd* pParent = NULL);   
	CHtmlCtrl(CWnd* pParent = NULL); 
	virtual ~CHtmlCtrl();
	enum { IDD = IDD_DLG_HTML, IDH = 0 };

	void  SetDefaultURL(CString Url) { m_StrURL = Url;}
	void	SetHtmlAndCom(CString StrURL, CString StrProg=_T(""));

	virtual void OnBeforeNavigate(LPDISPATCH pDisp, LPCTSTR szUrl);

	HRESULT OnButtonOK(IHTMLElement *pElement);

	HRESULT OnButtonCancel(IHTMLElement *pElement);

	//下载URL
	HRESULT OnDownFileUrl(IHTMLElement *pElement);
	
	//是否为下载文件URL
	BOOL IsDownLoadFileUrl(CString Url);

	//设置主页URL，用于外部URL过滤
	static void SetHomeUrl(CString Url){ m_HomeUrl = Url;}

	static void SetFilterUrl(vector<CString> FilterList){ m_FilterList = FilterList;}

	void IsRecordSession(BOOL Session){ m_IsRecordSession = Session; }

	//跳转到指定URL
	void GoToUrl(CString Url,CString PostData=_T(""));
	void GoHome();
	void GoBack();
	void GoForward();
	void Reflesh();

	//获取当前最后跳转的URL
	static CString GetLastUrl();
	
	//保存Cookie
	void SaveCookie(BOOL  SaveCooike = TRUE);

	CString GetSessionInfo(){ return m_Session;}

	STDMETHOD(GetHostInfo)(DOCHOSTUIINFO* pInfo);
	
	virtual BOOL IsExternalDispatchSafe(){ return true;}
	virtual	BOOL CanAccessExternal();
	
	virtual void OnDocumentComplete(LPDISPATCH pDisp, LPCTSTR szUrl);
	virtual void OnNavigateComplete(LPDISPATCH pDisp, LPCTSTR szUrl);

	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);  

	virtual BOOL OnInitDialog();

	//在弹出新窗口前拦截URL
	virtual void OnNewWindow3(LPDISPATCH* ppDisp,BOOL* Cancel, unsigned long dwFlags, LPCTSTR bstrUrlContext, LPCTSTR bstrUrl);

	//在跳转前截获URL
	virtual void MyOnBeforeNavigate2(LPDISPATCH pDisp,VARIANT FAR* URL,VARIANT FAR* Flags,VARIANT FAR* TargetFrameName,VARIANT FAR* PostData,VARIANT FAR* Headers,BOOL FAR* Cancel);
	
	//过滤Session
	void FilterSession(CString& Session);

	//是否是自己的URL
	virtual bool IsSelfUrl(CString Url);

	CString GetSession();

	HRESULT GetPostData(LPVARIANT pPostData);

	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
	DECLARE_EVENTSINK_MAP()

private:
	
	CComPtr<IDispatch>	m_ComDisp;
	CString				m_StrURL;
	CString             m_PostData;
	BOOL                m_IsSaveCooike;
	BSTR                m_StrCookie;
	CString             m_Session;
	BOOL                m_AddSession;
	BOOL                m_IsRecordSession;
	HWND                m_ProgressHwnd;
	static CString      m_HomeUrl;
	static CString      m_LastUrl;
	static vector<CString>     m_FilterList;
};
