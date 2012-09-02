#include "StdAfx.h"
#include "ConnectThread.h"
#include "../common/Include/Communication.h"
#include "../common/Include/MessageCenter.h"
#include "../common/Include/Markup.h"
#include "../common/Include/CommonFunction.h"



CConnectThread::CConnectThread(void)
{
	m_StartConnectEvent=::CreateEvent(NULL,true,false,NULL);
	m_StopConnectEvent =::CreateEvent(NULL,true,false,NULL);
}

CConnectThread::~CConnectThread(void)
{
	if(m_StartConnectEvent!= INVALID_HANDLE_VALUE)
		CloseHandle(m_StartConnectEvent);
	if(m_StopConnectEvent != INVALID_HANDLE_VALUE)
		CloseHandle(m_StopConnectEvent);
}


//开启线程
bool CConnectThread::StartThread()
{

	CBaseThread::StartThread();
	m_ThreadHandle = ::CreateThread(NULL,0,ConnectWorkThread,this,0,NULL);
	if(m_ThreadHandle != INVALID_HANDLE_VALUE)
		return true;

	return false;

}

//连接处理线程
DWORD CConnectThread::ConnectWorkThread(LPVOID lpVoid)
{
	CConnectThread* Self=(CConnectThread*)lpVoid;
	
	//创建定时器
	LARGE_INTEGER   TimeOut;    
	TimeOut.QuadPart=-100000000;
	HANDLE TimerEvent=CreateWaitableTimer(NULL,FALSE,NULL);   
	if(SetWaitableTimer(TimerEvent,&TimeOut,10000,NULL,NULL,FALSE)==FALSE)
		return 0;

	int PORT = 6060;
	SOCKET Socket=socket(AF_INET,SOCK_DGRAM,0);
	int Val = TRUE; 
    setsockopt(Socket,SOL_SOCKET,SO_REUSEADDR,(char *)&Val,sizeof(Val));
 

	SOCKADDR_IN local;
    local.sin_family=AF_INET;
    local.sin_addr.S_un.S_addr=INADDR_ANY;
    local.sin_port=htons(PORT);
    if(SOCKET_ERROR != bind(Socket,(sockaddr*)&local,sizeof(local)))
	{

		::XWriteEventLog(_T("[CConnectThread::ConnectWorkThread] Start OK \r\n"));
		
		HANDLE ReadEvent=::CreateEvent(NULL,true,false,NULL);
		 ::WSAEventSelect(Socket,ReadEvent, FD_READ);
		 HANDLE EventArray[5]={Self->m_StartConnectEvent,Self->m_StopConnectEvent,TimerEvent,ReadEvent,Self->m_StopEvent};

		BOOL IsConnected = false;
		int ErrorCount=0;

		while(true)
		{
			DWORD Ret=::WaitForMultipleObjects(5,EventArray,false,INFINITE);
			switch(Ret)
			{
			case 0:
				{
					if(IsConnected)
					{
						sPhoneInfo PhoneInfo;
						IsConnected =Self->GetPhoneInfo(PhoneInfo);
						if(IsConnected)
						{
							CMessageCenter::SendMsg(MSG_GET_PHONEINFO_OVER,(WPARAM)&PhoneInfo);
						}
					}
					else
						Self->StartPhoneServer();

					ResetEvent(EventArray[0]);
				}
				break;

			case 1:
				{
					IsConnected = false;
					ResetEvent(EventArray[1]);
				}
				break;
			case 2:
				{
					if(!IsConnected)
						continue;
					else
					{
						CString CmdStr;
						CString CmdRetStr;
						CCommunication::SendXmlToPhone(CmdStr,CmdRetStr);
						if(CmdRetStr.IsEmpty())
						{
							ErrorCount++;
						}
						else
							ErrorCount=0;

						if(ErrorCount > 3)
						{
							IsConnected = true;
							CMessageCenter::SendMsg(MSG_DISCONNECT_PHONE);

						}
					}
				}
				break;
			case 3:
				{
					::ResetEvent(ReadEvent);
					char buff[1024];
					memset(buff,0,1024);

					SOCKADDR_IN addrRemote;
					int nlen=sizeof(SOCKADDR_IN);
					int RecvLen=recvfrom(Socket,buff,1023,0,(sockaddr *)&addrRemote,&nlen);
					if(RecvLen == SOCKET_ERROR)
					{
						int Error=GetLastError();
						CString Str;
						Str.Format(_T("BroadServer recvfrom Error=[%d]"),Error);
						::XWriteEventLog(Str);
						continue;
					}

					CString Msg=CString(buff);
					if(!Msg.IsEmpty())
					{
						CString Version;
						if(Version != _T("1.0.0.1"))
						{
							Self->InstallPhoneServer();
							Self->StartPhoneServer();
						}
						else
						{
							IsConnected  = true;
							SetEvent(Self->m_StartConnectEvent);
						}
					}
				}
				break;

			case 4:
				break;

			default:
				break;
			}
		}

		CloseHandle(ReadEvent);
	}

	CloseHandle(TimerEvent);

	return 0;

}

//开始连接
bool CConnectThread::StartConnectPhone(CString PhoneDes)
{
	m_PhoneDes = PhoneDes;
	SetEvent(m_StartConnectEvent);
	return true;
}

//中断连接
void CConnectThread::StopConnectPhone()
{

}

//重定向端口
bool  CConnectThread::ForwardAdbPort()
{
	XWriteEventLog(_T("CConnectThread::ForwardAdbPort Start\r\n"));
	CString CmdStr;
	CString CmdRetStr;

	CmdStr.Format(_T("adb -s %s forward tcp:%d tcp:2012"),m_PhoneDes.GetBuffer(),CCommunication::m_Port);
	m_PhoneDes.ReleaseBuffer();
	ExecAdbCmd(CmdStr,CmdRetStr);
	if(CmdRetStr.Find(_T("error")) != -1)
	{
		CCommunication::m_Port++;
		if(CCommunication::m_Port > 10000)
			CCommunication::m_Port = 2011;
		XWriteEventLog(_T("CConnectThread::ForwardAdbPort Error\r\n"));
		return false;
	}

	return true;
}

//开启手机服务
void CConnectThread::StartPhoneServer()
{
	int ForwardCount = 0;
	while(!ForwardAdbPort())
	{
		ForwardCount++;
		if(ForwardCount > 5)
		{
			XWriteEventLog(_T("CConnectThread::StartPhoneServer Forward 5 Error\r\n"));
			break;
		}
	}

	CString CmdStr;
	CString CmdRetStr;
	CmdStr.Format(_T("adb -s %s shell am broadcast -a com.aspire.daemon.LAUNCH"),m_PhoneDes.GetBuffer());
	m_PhoneDes.ReleaseBuffer();
	ExecAdbCmd(CmdStr,CmdRetStr);

	
}

//安装手机服务
bool CConnectThread::InstallPhoneServer()
{
	CString Path =GetAppPath();
	Path+=_T("PhoneServer.apk");
	return ::InstallPhoneApp(m_PhoneDes,Path,true);
}

//获取手机信息
bool CConnectThread::GetPhoneInfo(sPhoneInfo& Info)
{
	GetPhoneSystemInfo(Info);
	GetPhoneMemInfo(Info);
	GetPhoneCountInfo(Info);

	return true;
}

//获取手机系统信息
bool CConnectThread::GetPhoneSystemInfo(sPhoneInfo& Info)
{
	bool Ret=false;
	CString CmdStr;
	CString CmdRetStr;
	CmdStr=_T("<?xml version='1.0'?><req><fun>GetSystemAgentVar</fun><ps count='0'></ps></req>");

	if(CCommunication::SendXmlToPhone(CmdStr,CmdRetStr) < 0x00)
		return Ret;
	if(CmdRetStr.IsEmpty())
		return Ret;

	CMarkup Xml;
	if(Xml.SetDoc(CmdRetStr))
	{
		CString strData;
		Xml.ResetMainPos();
		Xml.FindChildElem(_T("ps"));

		if (Xml.IntoElem())
		{
			Ret=true;
			while ( Xml.FindChildElem(_T("p")) )
			{
				
				CString strMsg;
				Xml.IntoElem();

				Xml.FindChildElem(_T("name"));
				strData = Xml.GetChildData().c_str();
				if (strData == _T("msg"))
				{
					Xml.FindChildElem(_T("value"));							
					strMsg = Xml.GetChildData().c_str();

					if (strMsg != _T("0"))
					{
						return false;
					}
				}else if  (strData == _T("var"))
				{				
					Xml.FindChildElem(_T("value"));							
					Info.m_PhoneOSVer = Xml.GetChildData().c_str();
					Info.m_PhoneOS = Info.m_PhoneOSVer.Mid(0x00, Info.m_PhoneOSVer.Find(_T(" "))); //Andriod 2.1-Update-1

				}else if  (strData == _T("agent"))
				{				
					Xml.FindChildElem(_T("value"));							
					Info.m_PhoneModel= Xml.GetChildData().c_str();

				}else if  (strData == _T("programver"))
				{				
					Xml.FindChildElem(_T("value"));							
					CString strApkVer = Xml.GetChildData().c_str();
				}else if  (strData == _T("imei"))
				{				
					Xml.FindChildElem(_T("value"));							
					Info.m_PhoneIMEI = Xml.GetChildData().c_str();

				}else if  (strData == _T("imsi"))
				{				
					Xml.FindChildElem(_T("value"));							
					Info.m_PhoneIMSI = Xml.GetChildData().c_str();

				}else{;}

				Xml.OutOfElem();
			}
		}
	}

	return Ret;
}


//获取手机内存信息
bool CConnectThread::GetPhoneMemInfo(sPhoneInfo& Info)
{
	bool Ret=false;
	CString CmdStr;
	CString CmdRetStr;

	CmdStr =_T("<?xml version='1.0'?><req><fun>GetMemSize</fun><ps count='0'>/ps></req>");
	if(CCommunication::SendXmlToPhone(CmdStr,CmdRetStr) < 0)
		return Ret;

	if (!CmdRetStr.IsEmpty())
	{
		CMarkup Xml;
		if (Xml.SetDoc(CmdRetStr) )
		{			
			CString strXmlName;
			Xml.FindChildElem(_T("ps"));
			if (Xml.IntoElem())
			{
				Ret = true;

				while ( Xml.FindChildElem(_T("p")) )
				{
					Xml.IntoElem();
					CString strXmlValue ;

					Xml.FindChildElem(_T("name"));
					strXmlName = Xml.GetChildData().c_str();
					if (strXmlName == _T("msg"))
					{
						Xml.FindChildElem(_T("value"));							
						strXmlValue = Xml.GetChildData().c_str();

						if (strXmlValue != _T("0"))
						{
							return false;
						}
					}
					else if (strXmlName == _T("sdcardall"))
					{
						Xml.FindChildElem(_T("value"));							
						strXmlValue = Xml.GetChildData().c_str();

						if (!strXmlValue.IsEmpty())
						{							
							Info.m_SDTotalMem = _wtoi(strXmlValue.GetBuffer());
							strXmlValue.ReleaseBuffer();
						}
						else
							Info.m_SDTotalMem = 0;
					}
					else if (strXmlName == _T("sdcarduse"))
					{

						Xml.FindChildElem(_T("value"));							
						strXmlValue = Xml.GetChildData().c_str();

						if (!strXmlValue.IsEmpty())
						{							
							Info.m_SDUsedMem = _wtoi(strXmlValue.GetBuffer());
							strXmlValue.ReleaseBuffer();
						}
						else
							Info.m_SDUsedMem= 0;
					}
					else if (strXmlName == _T("phoneall"))
					{
						Xml.FindChildElem(_T("value"));							
						strXmlValue = Xml.GetChildData().c_str();
						if (!strXmlValue.IsEmpty())
						{							
							Info.m_PhoneTotalMem = _wtoi(strXmlValue.GetBuffer());
							strXmlValue.ReleaseBuffer();
						}
						else
						{
							Info.m_PhoneTotalMem = 0;
						}
					}
					else if (strXmlName == _T("phoneuse"))
					{
						Xml.FindChildElem(_T("value"));							
						strXmlValue = Xml.GetChildData().c_str();

						if (!strXmlValue.IsEmpty())
						{							
							Info.m_PhoneUsedMem = _wtoi(strXmlValue.GetBuffer());
							strXmlValue.ReleaseBuffer();
						}
						else
						{
							Info.m_PhoneUsedMem = 0;
						}
					}/////////////////////////////////////////////
					else if (strXmlName == _T("sdcardimage"))
					{
						Xml.FindChildElem(_T("value"));							
						strXmlValue = Xml.GetChildData().c_str();

						if (!strXmlValue.IsEmpty())
						{							
							Info.m_PicMemInSD = _wtoi(strXmlValue.GetBuffer());
							strXmlValue.ReleaseBuffer();
						}
						else
						{
							Info.m_PicMemInSD = 0;
						}
					}else if (strXmlName == _T("sdcardmusic"))
					{
						Xml.FindChildElem(_T("value"));							
						strXmlValue = Xml.GetChildData().c_str();

						if (!strXmlValue.IsEmpty())
						{							
							Info.m_MusicMemInSD = _wtoi(strXmlValue.GetBuffer());
							strXmlValue.ReleaseBuffer();
						}
						else
						{
							Info.m_MusicMemInSD = 0;
						}
					}else if (strXmlName == _T("sdcardvideo"))
					{
						Xml.FindChildElem(_T("value"));							
						strXmlValue = Xml.GetChildData().c_str();

						if (!strXmlValue.IsEmpty())
						{							
							Info.m_VideoMemInSD = _wtoi(strXmlValue.GetBuffer());
							strXmlValue.ReleaseBuffer();
						}
						else
						{
							Info.m_VideoMemInSD = 0;
						}
					}else{;}

					Xml.OutOfElem();
				}
			}
		}
	}

	Info.m_PhoneFreeMem = Info.m_PhoneTotalMem - Info.m_PhoneUsedMem;
	Info.m_SDFreeMem    = Info.m_SDTotalMem - Info.m_SDUsedMem;
	return Ret;
}

//获取手机统计信息
bool CConnectThread::GetPhoneCountInfo(sPhoneInfo& Info)
{
	bool Ret=false;

	CString CmdStr;
	CString CmdRetStr;


	CString TypeValue;
	TypeValue = _T("app;contacts;sms;music;video;picture");

	CmdStr  = _T("<?xml version='1.0'?>");
	CmdStr += _T("<req>");
	CmdStr += _T("<fun>GetStatisticsData</fun>");
	CmdStr += _T("<ps count='0'>");
	CmdStr += _T("<p>");
	CmdStr += _T("<name>request</name>");
	CmdStr += _T("<value>") + TypeValue + _T("</value>");
	CmdStr += _T("</p>");
	CmdStr += _T("</ps>\n");
	CmdStr += _T("</req>\n");

	CCommunication::SendXmlToPhone(CmdStr,CmdRetStr);

	//解析返回值
	//分析返回的XML数据
	CString strData;
	CString strMsg;

	if ( !CmdRetStr.IsEmpty())
	{

		CMarkup Xml;
		if (Xml.SetDoc(CmdStr) )
		{			
			Xml.FindChildElem(_T("ps"));
			if (Xml.IntoElem())
			{
				Ret = true;
				while ( Xml.FindChildElem(_T("p")) )
				{
					strMsg.Empty();

					Xml.IntoElem();

					Xml.FindChildElem(_T("name"));
					strData = Xml.GetChildData().c_str();
					if (strData == _T("msg"))
					{
						Xml.FindChildElem(_T("value"));							
						strMsg = Xml.GetChildData().c_str();

						if (strMsg != _T("0"))
						{
							return false;
						}
					}
					else
					{	
						if (strData == _T("app"))
						{
							Xml.FindChildElem(_T("value"));							
							strMsg = Xml.GetChildData().c_str();
							
							Info.m_AppSum = _wtoi(strMsg.GetBuffer());
							strMsg.ReleaseBuffer();
						}

						if (strData == _T("contacts"))
						{
							Xml.FindChildElem(_T("value"));							
							strMsg = Xml.GetChildData().c_str();

							Info.m_ContactSum = _wtoi(strMsg.GetBuffer());
							strMsg.ReleaseBuffer();
						}

						if (strData == _T("sms"))
						{
							Xml.FindChildElem(_T("value"));							
							strMsg = Xml.GetChildData().c_str();

							Info.m_SmsSum = _wtoi(strMsg.GetBuffer());
							strMsg.ReleaseBuffer();
						}

						if (strData == _T("music"))
						{
							Xml.FindChildElem(_T("value"));							
							strMsg = Xml.GetChildData().c_str();

							Info.m_MusicSum = _wtoi(strMsg.GetBuffer());
							strMsg.ReleaseBuffer();
						}

						if (strData == _T("video"))
						{
							Xml.FindChildElem(_T("value"));							
							strMsg = Xml.GetChildData().c_str();

							Info.m_VideoSum = _wtoi(strMsg.GetBuffer());
							strMsg.ReleaseBuffer();
						}

						if (strData == _T("picture"))
						{
							Xml.FindChildElem(_T("value"));							
							strMsg = Xml.GetChildData().c_str();

							Info.m_PicSum= _wtoi(strMsg.GetBuffer());
							strMsg.ReleaseBuffer();
						}

					}
					Xml.OutOfElem();
				}
			}
		}
	}

	return Ret;
}