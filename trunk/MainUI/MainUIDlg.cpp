
// MainUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MainUI.h"
#include "MainUIDlg.h"
#include "ImpIDispatch.h"
#include "CommonFunction.h"
#include <TlHelp32.h>
#include <atlbase.h>
#include <cfgmgr32.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMainUIDlg::CMainUIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainUIDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pIHTMLDoc		= NULL;
	m_DataEngine = GetDataEngineInterface();

	
}

void CMainUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EXPLORER_MAIN, m_wndWeb);
}

BEGIN_MESSAGE_MAP(CMainUIDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_MESSAGE( WM_DEVICECHANGE,UsbStateChange)	
	ON_WM_DESTROY()
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CMainUIDlg, CDialog)
	ON_EVENT(CMainUIDlg, IDC_EXPLORER_MAIN, 259, OnDocumentCompleteExplorerMain, VTS_DISPATCH VTS_PVARIANT)
END_EVENTSINK_MAP()

void CMainUIDlg::OnDocumentCompleteExplorerMain(LPDISPATCH pDisp, VARIANT FAR* URL) 
{
	IDispatch*				pIDisp			= NULL;
	pIDisp = m_wndWeb.GetDocument();
	if(pIDisp)
	{
		theApp.m_pCustDisp->m_InterfaceToJs->SetDisPath(pIDisp);
	}
}

BOOL CMainUIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	RegisterUsbListenEvent();

     CString StrDes=_T("");
     ::GetModuleFileName(NULL,StrDes.GetBuffer(MAX_PATH),MAX_PATH); 
     StrDes.ReleaseBuffer();
     StrDes=StrDes.Left(StrDes.ReverseFind('\\'));
     if(StrDes.Right(1)!='\\')
         StrDes+="\\";
	 StrDes +=_T("Custom.html");


	CRect Rect;
	GetWindowRect(Rect);
	int Width   = 910;
	int Height  = 683;
	Rect.right  = Rect.left + Width;
	Rect.bottom = Rect.top + Height;
	MoveWindow(Rect);                    //设置对话框大小
	this->CenterWindow(NULL);            //居中
	SetRoundWindows(Width,Height,4);     //设置圆角的对话框
	m_wndWeb.Navigate(StrDes, NULL, NULL, NULL, NULL);

	m_wndWeb.SetWidth(Width);
	m_wndWeb.SetHeight(Height);

	CMessageCenter::RegisterMsgHandle((IMessageHandle*)this,MSG_START_CONECT_PHONE);
	CMessageCenter::SendMsg(MSG_START_CONECT_PHONE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMainUIDlg::SetRoundWindows(int Width, int Height, int round)  //设置弧度 对话框 宽 高 弧度
{
	CRgn m_frmRgn;
	POINT PointArray[7];
	PointArray[0].x=4;
	PointArray[0].y=0;
	PointArray[1].x=Width-4;
	PointArray[1].y=0;
	PointArray[2].x=Width;
	PointArray[2].y=4;
	PointArray[3].x=Width;
	PointArray[3].y=Height;
	PointArray[4].x=0;
	PointArray[4].y=Height;
	PointArray[5].x=0;
	PointArray[5].y=4;
	PointArray[6].x=4;
	PointArray[6].y=0;
	m_frmRgn.CreatePolygonRgn(PointArray,7,ALTERNATE);
	SetWindowRgn(m_frmRgn,TRUE);
	m_frmRgn.DeleteObject();
}

void CMainUIDlg::MoveMainDlg(int iArg1 , int iArg2)
{
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(iArg1,iArg2));
	return;
}

BOOL CMainUIDlg::IsAppRun(CString AppName) 
{ 
	char   pPath[_MAX_PATH]; 
	pPath[0]=0; 
	const char *cExeName = CStrToChar(AppName);
	_searchenv(cExeName, "PATH ",pPath); 
	VERIFY(pPath);
	DWORD id=GetProcessIdFromName(AppName);//这样查杀AppName 
	if(id!=NULL) 
	{ 
		HANDLE   myhandle=OpenProcess(PROCESS_ALL_ACCESS,TRUE,id); 
		DWORD   exitcode=0; 
		TerminateProcess(myhandle,exitcode); 
		return   TRUE; 
	} 
	return   FALSE; 
}

DWORD  CMainUIDlg::GetProcessIdFromName(LPCTSTR   name) 
{ 

	PROCESSENTRY32   pe; 
	DWORD   id   =   0; 
	HANDLE   hSnapshot   =   CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0); 
	pe.dwSize   =   sizeof(PROCESSENTRY32); 
	if(   !Process32First(hSnapshot,&pe)   ) 
		return   0; 
	CString   name1,name2; 
	do 
	{ 
		pe.dwSize   =   sizeof(PROCESSENTRY32); 
		if(   Process32Next(hSnapshot,&pe)==FALSE   ) 
			break; 
		name1=pe.szExeFile; 
		name2=name; 
		name1.MakeUpper(); 
		name2.MakeUpper(); 
		if(name1 == name2) 
		{ 
			id   =   pe.th32ProcessID; 
			break; 
		} 
	}   while(1); 
	CloseHandle(hSnapshot); 
	return   id; 
}

const char* CMainUIDlg::CStrToChar(CString strSrc)
{
#ifdef UNICODE
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, strSrc.GetBuffer(0), -1, NULL, 0, NULL, FALSE);
	char *psText;
	psText = new char[dwNum];
	if (!psText)
		delete []psText;
	WideCharToMultiByte(CP_OEMCP, NULL, strSrc.GetBuffer(0), -1, psText, dwNum, NULL, FALSE);
	return (const char*)psText;
#else
	return (LPCTSTR)strSrc;
#endif
}



void CMainUIDlg::OnTimer(UINT_PTR nIDEvent)
{

}

void CMainUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CMainUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CMainUIDlg::UsbStateChange ( WPARAM wParam, LPARAM lParam )
{
	switch(wParam)
	{ 
	case  DBT_DEVICEARRIVAL:
		{
			//if(CDataManageCenter::Init()->GetCurrentConnectMode() != CONNECT_MODE_BY_WIFI)
			{
				PDEV_BROADCAST_HDR pHdr = (PDEV_BROADCAST_HDR)lParam;
				PDEV_BROADCAST_DEVICEINTERFACE pDevInf;
         		pDevInf = (PDEV_BROADCAST_DEVICEINTERFACE)pHdr;
				CString ClassName;
				CString DevId;
				CString PhoneDes;

				if(lstrlen(pDevInf->dbcc_name) < 4) 
					break;

         		CString DesStr= pDevInf->dbcc_name+4;
				XWriteEventLog(_T("[CMainUIDlg::UsbStateChange]  USB Device DBT_DEVICEARRIVAL  ")+DesStr+_T("\r\n"));
				GetClassNameAndDevId(DesStr,ClassName,DevId,PhoneDes);
				if(ClassName.IsEmpty() || DevId.IsEmpty() || PhoneDes.IsEmpty())
					break;

				CString Vid,Pid;
				GetVidAndPid(DevId,Vid,Pid);
				if(Vid.IsEmpty() || Pid.IsEmpty())
					break;
			
				CString Temp=Vid+_T("-") + Pid;
				if(!IsMatchPhone(Temp,PhoneDes))
				{
					CDataManageCenter::Init()->AddUsbConnectInfo(PhoneDes,NULL);
				}

				
				sUsbConnectInfo* Phone= CDataManageCenter::Init()->GetUsbConnectInfo(PhoneDes);
				if(Phone)
				{
					Phone->m_IsInstallDrive = TRUE;
					Phone->m_PhoneVidPid = Temp;
				}

				if( IsConnectedPhone())
					break;

				if(m_IsConnecting)
					break;

				CDataManageCenter::Init()->SetCurrentConnectPhoneDesId(PhoneDes);
				m_IsUsbEnable = TRUE;
				
				////设置手机信息
				char szDateTime[32] = {0};
	
				Sleep(2000);  //休眠3秒用于系统加载完此设备
				CMessageCenter::SendMsg(MSG_START_CONECT_PHONE);
				XWriteEventLog(_T("[CMainUIDlg::UsbStateChange] USB Device Connected and Arrival\r\n"));
			}
		}
		break;
	case DBT_DEVICEQUERYREMOVE:
		{
			XWriteEventLog(_T("[CMainUIDlg::UsbStateChange] USB Device DBT_DEVICEQUERYREMOVE\r\n"));
		}
		break;
	case DBT_DEVICEQUERYREMOVEFAILED:
		{
		}
		break;
	case DBT_DEVICEREMOVECOMPLETE:
		{
			if(CDataManageCenter::Init()->GetCurrentConnectMode() != CONNECT_MODE_BY_WIFI)
			{
				if( m_IsUsbEnable)
				{
					m_IsUsbEnable = false;
					vector<sPhoneStatus> PhoneList;
					GetAndroidDeviceList(PhoneList);
					if(PhoneList.empty())
						break;
					

					CString CurrentDesId = CDataManageCenter::Init()->GetCurrentConnectPhoneDesId();
					CString TempCurrentId = CurrentDesId;
					TempCurrentId.MakeUpper();
					BOOL IsRemove = TRUE;
					for(int Index = 0; Index < (int)PhoneList.size(); Index++)
					{
						CString TempDesId=PhoneList[Index].m_PhoneDesId;
						TempDesId.MakeUpper();
						if(TempCurrentId == TempDesId && !PhoneList[Index].m_IsOffLine)
						{
							IsRemove = FALSE;
							break;
						}
					}

					if(IsRemove)
					{
					/*	if(!IsConnectedPhone())
							SendMessage(WM_PHONE_DISCONNECTED,NULL,NULL);
						m_pConnectMonitorThread->StopThreadWatch();
						m_pConnectMonitorThread->m_bWatch = false;
						CDataManageCenter::Init()->DeleteUsbConnectInfo(CurrentDesId);
						m_pConnectMonitorThread->m_bUsbReMoveOK = TRUE;
						m_pConnectMonitorThread->ExitInstance();
						m_pConnectMonitorThread = (CConnectMonitorThread*)AfxBeginThread(RUNTIME_CLASS(CConnectMonitorThread));
						m_pConnectMonitorThread->m_hParentWnd = m_hWnd;
						XWriteEventLog(_T("USB Device ReMoved ") + CurrentDesId+_T("\r\n"));
						*/
				    
					}
				}
			}
			XWriteEventLog(_T("[CMainUIDlg::UsbStateChange] USB Device DBT_DEVICEREMOVECOMPLETE\r\n"));
		}
		break;
	case DBT_DEVNODES_CHANGED:
		{
			map<CString,CString> DesMap;
			FilterNotInstallDriveDevice(DesMap);
			if(DesMap.empty())
				break;


	//		SetTimer(START_DOWN_DRIVER_TIMER,6000,NULL);
	//		SetTimer(START_CHECK_DLG_TIMER,1000,NULL);
			break;
		}

		XWriteEventLog(_T("[CMainUIDlg::UsbStateChange] USB Device DBT_DEVNODES_CHANGED\r\n"));
		break;
	case DBT_DEVICEREMOVEPENDING:
		{
 
		}
		break;
	default:
		break;
	}
	return 0;
}

//获取类名和设备ID
void CMainUIDlg::GetClassNameAndDevId(CString DesStr,CString& ClassName,CString& DevId,CString& PhoneDes)
{
	CString szDevId = DesStr;
	int idx = szDevId.ReverseFind(L'#');
	if( -1 == idx ) 
		return ;

	CString szDevIdTmp;
	szDevIdTmp=szDevId;
	szDevId=szDevIdTmp.Left(idx);
	szDevId.Replace(L'#', L'\\');
	idx = szDevId.ReverseFind('\\');
	if( -1 == idx )
		return;

	PhoneDes = szDevId.Mid(idx+1);

	szDevId.MakeUpper();

	CString szClass;
	CString tmp =(L"\\");
	idx = szDevId.Find(L"\\");
	if(-1 == idx )
		return ;
	szClass=(szDevId.Left(idx));

	ClassName=szClass;
	DevId=szDevId;
}

//获取厂商ID和产品ID
void CMainUIDlg::GetVidAndPid(CString DevId,CString& Vid,CString& Pid)
{
	DevId= DevId.MakeUpper();
	int Pos = DevId.Find(_T("VID_"));
	if(Pos == -1)
		return;
	int EndPos = DevId.Find(_T("&"),Pos);
	if(EndPos == -1)
		return;

	Vid = DevId.Mid(Pos+4,EndPos-Pos-4);

	Pos = DevId.Find(_T("PID_"));
	if(Pos == -1)
		return;
	EndPos = DevId.Find(_T("\\"),Pos);
	if(EndPos == -1)
		return;

	Pid = DevId.Mid(Pos+4,EndPos-Pos-4);
	Pos = Pid.Find(_T("&"));
	if(Pos != -1)
		Pid = Pid.Left(Pos);
}

void CMainUIDlg::GetVidAndPid(CString DevId,CString& Vid,CString& Pid,CString& PhoneDes)
{
	DevId=DevId.Mid(DevId.Find(_T("\\"))+1);
	int Pos = DevId.ReverseFind(_T('\\'));
	PhoneDes = DevId.Mid(Pos+1);
	GetVidAndPid(DevId,Vid,Pid);
}



//响应消息
void CMainUIDlg::OnMessage(eMessage Message,DWORD SystemMsg,WPARAM wParam,LPARAM lParam)
{
	switch(Message)
	{
	case MSG_START_CONECT_PHONE:
		{
			//if(IsOpenUsbDebug())
			{
			
				vector<sPhoneStatus> StatusList;
				GetAndroidDeviceList(StatusList);
				if(StatusList.empty())
				{
					if(wParam)
					{
						map<CString,CString> DesMap;
						FilterNotInstallDriveDevice(DesMap);
						if(DesMap.empty())
						{
							vector<CString> DesList;
							GetConnectUsbPortDes(DesList);
							if(!DesList.empty())
							{
								for(int Index = 0; Index < (int)DesList.size(); Index++)
								{
									CString DesStr=DesList[Index].Mid(4);
									CString ClassName,DevId,PhoneDes;
									GetClassNameAndDevId(DesStr,ClassName,DevId,PhoneDes);
									if(ClassName.IsEmpty() || DevId.IsEmpty() || PhoneDes.IsEmpty())
										continue;

									CString Vid,Pid;
									GetVidAndPid(DevId,Vid,Pid);
									if(Vid.IsEmpty() || Pid.IsEmpty())
										continue;
								
									CString Temp=Vid+_T("-") + Pid;
									if(IsMatchPhone(Temp,PhoneDes))
									{
										CDataManageCenter::Init()->SetCurrentConnectPhoneDesId(PhoneDes);
										CMessageCenter::SendMsg(MSG_GOTO_USB_TIPDLG);
										break;
									}
								}

							}
							break;
						}

						map<CString,CString>::iterator it=DesMap.begin();

						for(it; it != DesMap.end(); it++)
						{
							if(IsMatchPhone (it->second,it->first))
							{
								sUsbConnectInfo* Phone= CDataManageCenter::Init()->GetUsbConnectInfo(it->first);
								if(CDataManageCenter::Init()->GetIsIdentify())
									break;

								if( IsConnectedPhone())
									break;
								
								CDataManageCenter::Init()->SetCurrentConnectPhoneDesId(it->first);
								CDataManageCenter::Init()->SetIsIdentify(TRUE);
								break;
							}
						}

					}
					else
					{
						vector<CString> DesList;
						GetConnectUsbPortDes(DesList);
						if(!DesList.empty())
						{
							for(int Index = 0; Index < (int)DesList.size(); Index++)
							{
								CString DesStr=DesList[Index].Mid(4);
								CString ClassName,DevId,PhoneDes;
								GetClassNameAndDevId(DesStr,ClassName,DevId,PhoneDes);
								if(ClassName.IsEmpty() || DevId.IsEmpty() || PhoneDes.IsEmpty())
									continue;

								CString Vid,Pid;
								GetVidAndPid(DevId,Vid,Pid);
								if(Vid.IsEmpty() || Pid.IsEmpty())
									continue;
							
								CString Temp=Vid+_T("-") + Pid;
								Temp.MakeUpper();

								sUsbConnectInfo* UsbConnectInfo=CDataManageCenter::Init()->GetCurrentConnectUsbConnectInfo();
								CString CurrentVidPid;
								if(UsbConnectInfo)
								{
									CurrentVidPid = UsbConnectInfo->m_PhoneVidPid;
									CurrentVidPid.MakeUpper();
								}
								
								if(CurrentVidPid == Temp && !CurrentVidPid.IsEmpty() || IsMatchPhone(Temp,PhoneDes))
								{
									CDataManageCenter::Init()->SetCurrentConnectPhoneDesId(PhoneDes);
									CMessageCenter::SendMsg(MSG_GOTO_USB_TIPDLG);
									break;
								}
							}

						}
					}
					break;
				}

				BOOL IsInit=false;
				CString PhoneDesId = CDataManageCenter::Init()->GetCurrentConnectPhoneDesId();
				if(PhoneDesId.IsEmpty())
				{
					InitUsbConnectInfo();
					IsInit = true;
					PhoneDesId = CDataManageCenter::Init()->GetCurrentConnectPhoneDesId();
					if(PhoneDesId.IsEmpty())
					{
						PhoneDesId = StatusList[0].m_PhoneDesId;
						CDataManageCenter::Init()->SetCurrentConnectPhoneDesId(PhoneDesId);
					}
				}

				if(PhoneDesId.Find(_T("&")) != -1)
				{
					sUsbConnectInfo * TempInfo = CDataManageCenter::Init()->GetCurrentConnectUsbConnectInfo();
					if( TempInfo != NULL)
					{
						CString TempDesId = PhoneDesId;
						PhoneDesId = StatusList[0].m_PhoneDesId;
						sUsbConnectInfo* UsbConnectInfo = new sUsbConnectInfo;
						*UsbConnectInfo = *TempInfo;
						CDataManageCenter::Init()->AddUsbConnectInfo(PhoneDesId,UsbConnectInfo);
						CDataManageCenter::Init()->SetCurrentConnectPhoneDesId(PhoneDesId);
						CDataManageCenter::Init()->DeleteUsbConnectInfo(TempDesId);

					}
				}
				BOOL AutoPhone=FALSE;
				for(int Index = 0; Index < (int)StatusList.size(); Index++)
				{
					CString TempPhoneId=StatusList[Index].m_PhoneDesId;
					TempPhoneId.MakeUpper();
					PhoneDesId.MakeUpper();
					if(TempPhoneId == PhoneDesId)
					{
						if(StatusList[Index].m_IsOffLine)
						{
							CMessageCenter::SendMsg(MSG_GOTO_USB_TIPDLG);
				    		return;
						}
						PhoneDesId = StatusList[Index].m_PhoneDesId;
						CDataManageCenter::Init()->SetCurrentConnectPhoneDesId(PhoneDesId);
						AutoPhone = TRUE;
						break;
					}
				}

				if( !AutoPhone && IsInit)
				{
					PhoneDesId = StatusList[0].m_PhoneDesId;
					CDataManageCenter::Init()->SetCurrentConnectPhoneDesId(PhoneDesId);
					AutoPhone = TRUE;
				}
				
				if(AutoPhone)
				{
					m_IsConnecting = true;
					m_IsUsbEnable = true;
					CDataManageCenter::Init()->SetCurrentConenctMode(CONNECT_MODE_BY_USB);
					CString DesId=CDataManageCenter::Init()->GetCurrentConnectPhoneDesId();
					m_DataEngine->ConnectPhone(DesId);
				}
			}
		}
		break;
	case MSG_UPDATE_DRIVE_INFO_LIST:
		LoadDriveInfo();
		break;

	case MSG_START_CONNECT_PHONE_WIFI:
		{
			break;
		}
	default:
		break;
	}
}

//导入驱动信息
void CMainUIDlg::LoadDriveInfo()
{
	CString Path= GetAppPath()+_T("cfg\\DriveInfo.xml");
	if(m_DriveInfoXml.Load(Path.GetBuffer()))
	{
		if(m_DriveInfoXml.FindChildElem(_T("version")))
			CDataManageCenter::Init()->SetDriveVersion(m_DriveInfoXml.GetChildData().c_str());
		if(m_DriveInfoXml.FindChildElem(_T("mmurl")))
			CDataManageCenter::Init()->SetMMUrl(m_DriveInfoXml.GetChildData().c_str());
		m_DriveInfoXml.ResetPos();
		
	}
	Path.ReleaseBuffer();
}

//判断是否为匹配中的手机
BOOL CMainUIDlg::IsMatchPhone(CString VidPid,CString PhoneDes)
{
	m_DriveInfoXml.ResetPos();
	while(m_DriveInfoXml.FindChildElem(_T("driver")))
	{
		m_DriveInfoXml.IntoElem();
		CString Name = m_DriveInfoXml.GetAttrib(_T("id")).c_str();
		Name.MakeUpper();
		VidPid.MakeUpper();
		if(Name == VidPid)
		{
			sUsbConnectInfo* UsbConnectInfo = new sUsbConnectInfo;
			UsbConnectInfo->m_IsInstallDrive = FALSE;

			m_DriveInfoXml.FindChildElem(_T("name"));
			UsbConnectInfo->m_PhoneName = m_DriveInfoXml.GetChildData().c_str();
			m_DriveInfoXml.FindChildElem(_T("qid"));
			UsbConnectInfo->m_DeviceId = m_DriveInfoXml.GetChildData().c_str();
			m_DriveInfoXml.FindChildElem(_T("image"));
			UsbConnectInfo->m_PhoneImageUrl = m_DriveInfoXml.GetChildData().c_str();
			m_DriveInfoXml.FindChildElem(_T("url"));
			UsbConnectInfo->m_DriveUrl = m_DriveInfoXml.GetChildData().c_str();
			m_DriveInfoXml.FindChildElem(_T("screencoordinate"));
			UsbConnectInfo->m_PhoneScreenInfo = m_DriveInfoXml.GetChildData().c_str();

			CDataManageCenter::Init()->AddUsbConnectInfo(PhoneDes,UsbConnectInfo);
			m_DriveInfoXml.OutOfElem();
			return TRUE;
		}
		m_DriveInfoXml.OutOfElem();
	}

	m_DriveInfoXml.ResetPos();
	CString Vid = VidPid.Left(VidPid.Find('-'));
	while(m_DriveInfoXml.FindChildElem(_T("vid")))
	{
		m_DriveInfoXml.IntoElem();
		CString Name = m_DriveInfoXml.GetAttrib(_T("id")).c_str();
		Name.MakeUpper();
		Vid.MakeUpper();
		if(Name == Vid)
		{
			sUsbConnectInfo* UsbConnectInfo = new sUsbConnectInfo;
			UsbConnectInfo->m_IsInstallDrive = FALSE;

			m_DriveInfoXml.FindChildElem(_T("name"));
			UsbConnectInfo->m_PhoneName = m_DriveInfoXml.GetChildData().c_str();
			m_DriveInfoXml.FindChildElem(_T("qid"));
			UsbConnectInfo->m_DeviceId = m_DriveInfoXml.GetChildData().c_str();
			m_DriveInfoXml.FindChildElem(_T("image"));
			UsbConnectInfo->m_PhoneImageUrl = m_DriveInfoXml.GetChildData().c_str();
			m_DriveInfoXml.FindChildElem(_T("url"));
			UsbConnectInfo->m_DriveUrl = m_DriveInfoXml.GetChildData().c_str();
			m_DriveInfoXml.FindChildElem(_T("screencoordinate"));
			UsbConnectInfo->m_PhoneScreenInfo = m_DriveInfoXml.GetChildData().c_str();

			CDataManageCenter::Init()->AddUsbConnectInfo(PhoneDes,UsbConnectInfo);
			m_DriveInfoXml.OutOfElem();
			return TRUE;
		}
		m_DriveInfoXml.OutOfElem();
	}


	return FALSE;
}

//过滤没有安装驱动的设备
void CMainUIDlg::FilterNotInstallDriveDevice(map<CString,CString>& DesMap)
{
	HDEVINFO          hDevInfo;
	SP_DEVINFO_DATA   DeviceInfoData;
	hDevInfo  = SetupDiGetClassDevs(NULL,_T("USB"),0,DIGCF_PRESENT | DIGCF_ALLCLASSES);/*DIGCF_ALLCLASSES );*///DIGCF_DEVICEINTERFACE);
	if(hDevInfo == INVALID_HANDLE_VALUE)
		return;

	DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	for(int i=0; SetupDiEnumDeviceInfo(hDevInfo, i, &DeviceInfoData); i++)
	{
		DWORD nSize=0 ;
		TCHAR buf[MAX_PATH];
		
		DWORD Status=0,Problem=0;
		if(CM_Get_DevNode_Status(&Status,&Problem,DeviceInfoData.DevInst,0) != CR_SUCCESS)
			continue;

		if(Problem)
		{
			if (!SetupDiGetDeviceInstanceId(hDevInfo, &DeviceInfoData, buf, sizeof(buf), &nSize) )
				continue;

			CString DesStr = buf;
			CString Vid,Pid;
			CString PhoneDes;
			GetVidAndPid(DesStr,Vid,Pid,PhoneDes);
			if(Vid.IsEmpty() || Pid.IsEmpty() || PhoneDes.IsEmpty())
				continue;


			DesMap[PhoneDes] = Vid+_T("-")+Pid;
		}
	}

	SetupDiDestroyDeviceInfoList(hDevInfo);
}


//初始化手机信息
void CMainUIDlg::InitUsbConnectInfo()
{
	HDEVINFO          hDevInfo;
	SP_DEVINFO_DATA   DeviceInfoData;
	hDevInfo  = SetupDiGetClassDevs(NULL,_T("USB"),0,DIGCF_PRESENT | DIGCF_ALLCLASSES);/*DIGCF_ALLCLASSES );*///DIGCF_DEVICEINTERFACE);
	if(hDevInfo == INVALID_HANDLE_VALUE)
		return;

	DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	BOOL IsFirst = TRUE;

	for(int i=0; SetupDiEnumDeviceInfo(hDevInfo, i, &DeviceInfoData); i++)
	{
		DWORD nSize=0 ;
		TCHAR buf[MAX_PATH];
		BOOL IsInstallDrive=SetupDiGetDeviceRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_DRIVER,0,(PBYTE)buf, sizeof(buf), 0);
		DWORD ConfigFlags=0;
		SetupDiGetDeviceRegistryProperty(hDevInfo,&DeviceInfoData,SPDRP_CONFIGFLAGS,0,(PBYTE)&ConfigFlags,sizeof(DWORD),0);

		if(ConfigFlags)
			IsInstallDrive = FALSE;

		if (!SetupDiGetDeviceInstanceId(hDevInfo, &DeviceInfoData, buf, sizeof(buf), &nSize) )
				continue;

		CString DesStr = buf;
		CString Vid,Pid;
		CString PhoneDes;
		GetVidAndPid(DesStr,Vid,Pid,PhoneDes);
		if(Vid.IsEmpty() || Pid.IsEmpty() || PhoneDes.IsEmpty())
			continue;

	
		CString VidPid=Vid+_T("-")+Pid;
		if( IsMatchPhone(VidPid,PhoneDes) )
		{
			sUsbConnectInfo* UsbConnectInfo=CDataManageCenter::Init()->GetUsbConnectInfo(PhoneDes);
			if(UsbConnectInfo)
				UsbConnectInfo->m_IsInstallDrive = IsInstallDrive;
			if(IsFirst)
			{
				IsFirst = FALSE;
				CDataManageCenter::Init()->SetCurrentConnectPhoneDesId(PhoneDes);
			}
		}
	}

	SetupDiDestroyDeviceInfoList(hDevInfo);
}

//是否已连接手机
BOOL CMainUIDlg::IsConnectedPhone()
{
	return true;
}

//获取连接USB端口的硬件VID和PID
void CMainUIDlg::GetConnectUsbPortDes(vector<CString>& DesList)
{
	
	HDEVINFO                         deviceInfo;
	SP_DEVICE_INTERFACE_DATA         deviceInfoData;
	PSP_DEVICE_INTERFACE_DETAIL_DATA deviceDetailData;
	ULONG                            index;
	ULONG                            requiredLength;
	HANDLE      hHCDev;
	PTSTR       leafName;
	CString str = _T("");

	GUID GUID_CLASS_USB_HOST_CONTROLLER = {0xA5DCBF10L, 0x6530, 0x11D2, 0x90, 0x1F, 0x00,0xC0, 0x4F, 0xB9, 0x51, 0xED};
	deviceInfo = SetupDiGetClassDevs((LPGUID)&GUID_CLASS_USB_HOST_CONTROLLER,
		NULL,
		NULL,
		(DIGCF_PRESENT | DIGCF_DEVICEINTERFACE));

	if (deviceInfo != INVALID_HANDLE_VALUE)
	{
		deviceInfoData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

		for (index=0;SetupDiEnumDeviceInterfaces(deviceInfo,0,(LPGUID)&GUID_CLASS_USB_HOST_CONTROLLER,index,&deviceInfoData);index++)
		{
			SetupDiGetDeviceInterfaceDetail(deviceInfo,
				&deviceInfoData,
				NULL,
				0,
				&requiredLength,
				NULL);
			deviceDetailData=(PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(requiredLength);
			deviceDetailData->cbSize=sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

			SetupDiGetDeviceInterfaceDetail(deviceInfo,
				&deviceInfoData,
				deviceDetailData,
				requiredLength,
				&requiredLength,
				NULL);

			hHCDev = CreateFile(deviceDetailData->DevicePath,
				GENERIC_WRITE,
				FILE_SHARE_WRITE,
				NULL,
				OPEN_EXISTING,
				0,
				NULL);

			if (hHCDev != INVALID_HANDLE_VALUE)
			{
				leafName = deviceDetailData->DevicePath;
				DesList.push_back(leafName);
				CloseHandle(hHCDev);
			}

		}

		SetupDiDestroyDeviceInfoList(deviceInfo);
	}
}
void CMainUIDlg::OnDestroy()
{

	CMessageCenter::LogoutMsgHandle((IMessageHandle*)this,MSG_START_CONECT_PHONE);
	__super::OnDestroy();

}



//注册USB监听事件
void CMainUIDlg::RegisterUsbListenEvent()
{
	HDEVNOTIFY hDevNotify;
	DEV_BROADCAST_DEVICEINTERFACE NotificationFilter;
	ZeroMemory( &NotificationFilter, sizeof(NotificationFilter) );
	NotificationFilter.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
	NotificationFilter.dbcc_devicetype =DBT_DEVTYP_DEVICEINTERFACE;
	for(int i=0; i<sizeof(GUID_DEVINTERFACE_LIST)/sizeof(GUID); i++) {
		NotificationFilter.dbcc_classguid = GUID_DEVINTERFACE_LIST[i];
		hDevNotify = RegisterDeviceNotification(m_hWnd, &NotificationFilter, DEVICE_NOTIFY_WINDOW_HANDLE);
	}
}
