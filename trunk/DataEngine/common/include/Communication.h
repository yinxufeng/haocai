#pragma once

#include "BaseSocket.h"
#define CMOBILEPLUG_API __declspec(dllexport)
//#ifdef CMOBILEPLUG_EXPORTS
//#define CMOBILEPLUG_API __declspec(dllexport)
//#else
//#define CMOBILEPLUG_API __declspec(dllimport)
//#endif


//#define  PCSUITE_IP_PORT	2011
//#define  PCSUITE_IP_ADDR	"127.0.0.1"
enum eConnectType 
{
	CONNECT_BY_USB,
	CONNECT_BY_WIFI
};


class CMOBILEPLUG_API CCommunication
{
public:
	CCommunication(void);
public:
	~CCommunication(void);

public:
	 

	 static long  m_nExceptionCounter;
	 static long  m_nExceptionHeart;
	 static long  m_nHeartCounter;

	 static BOOL m_bPhoneStatus;
	 static BOOL m_bUsbRemoved;
	 static BOOL m_bExit;

	 static CString        m_Ip;
	 static DWORD          m_Port;
	 static eConnectType   m_ConnectType;
	///*static*/ CString   m_strCallFuncName;

public:

	static void SetConnectIpAndPort(CString Ip,DWORD Port);

	///  static fun not use  refrence arg
	static int SendXmlToPhone(CString  argRequest, CString& argResponse,FunctionSocketCallBack CallBack=NULL,bool IsSetOutTime=true);

	static int GetHeart4Phone(CString  argRequest, CString& argResponse);
////////////////////////////////////////////////////////////
	static int  CheckHeart4PhoneS1(CBaseSocket  & ttBSocket , SOCKET & sendSocket);
	static int  CheckHeart4PhoneS2(CBaseSocket  & ttBSocket , SOCKET & sendSocket, CString argRequest, CString& argResponse);
	static CString GetRequestFuncationName(CString argReqeust);
};

//extern BOOL g_bPhoneStatus;

