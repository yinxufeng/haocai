#include "StdAfx.h"
#include "../Include/Communication.h"
#include "../Include/CommonFunction.h"

#define XWriteEventLog WriteLog

BOOL CCommunication::m_bPhoneStatus  = FALSE;
BOOL CCommunication::m_bUsbRemoved  = FALSE;
BOOL CCommunication::m_bExit        =FALSE;

long  CCommunication::m_nExceptionCounter  = 0x00;
long  CCommunication::m_nExceptionHeart	    = 0x00;
long  CCommunication::m_nHeartCounter  	    = 0x00;

CString CCommunication::m_Ip = _T("127.0.0.1");
DWORD   CCommunication::m_Port=2011;
eConnectType CCommunication::m_ConnectType  = CONNECT_BY_USB;

//CString   CCommunication::m_strCallFuncName = _T("");



CCommunication::CCommunication(void)
{
}

CCommunication::~CCommunication(void)
{
}

int CCommunication::SendXmlToPhone(CString  argRequest, CString& argResponse,FunctionSocketCallBack CallBack,bool IsSetOutTime)
{
//	argRequest = ReplaceStr( argRequest, _T("&"), _T("&amp;") ); // zhaoshan [2012.01.11]

//  argRequest = ReplaceStr( argRequest, _T("<"), _T("&lt;") ); // zhaoshan [2012.02.27]

	//argRequest = ReplaceStr(argRequest, _T("&"), _T("&amp;") ); // zhaoshan [2012.01.11]

//  argRequest = ReplaceStr( argRequest, _T("\""), _T("&quot;") );

//  argRequest = ReplaceStr( argRequest, _T("\'"), _T("&apos; ") );


	CString FunName=GetRequestFuncationName(argRequest);
	if(CCommunication::m_nExceptionHeart > 0x03)
	{
		XWriteEventLog(_T("[CCommunication::SendXmlToPhone] %s CCommunication::ExceptionHeart > 0x02.\r\n"),FunName);
		return -1;
	}
	//建立连接
	CString  strShowInfo;
	argResponse.Empty();
	CBaseSocket  OclsBSocket ; 
	CBaseSocket* clsBSocket = &OclsBSocket; 
	//CBaseSocket* clsBSocket = CBaseSocket::GetInstance(); 

	if(NULL == clsBSocket) 
	{
		XWriteEventLog(_T("[CCommunication::SendXmlToPhone] CBaseSocket::GetInstance Failed.\r\n"));
		m_nExceptionCounter++;
		return -1;
	}

	int nRet = -1;
	SOCKET sendSocket;
	nRet = clsBSocket->InitializeAndCreateSocket(&sendSocket,IsSetOutTime);
	if(0x00 != nRet)
	{
		nRet = GetLastError();

		strShowInfo.Format(_T("[CCommunication::SendXmlToPhone] InitializeAndCreateSocket ErrorNo=[%d].\r\n"), nRet);
		XWriteEventLog(strShowInfo);

		clsBSocket->CloseSocket( &sendSocket);
		return -2;
	}
	
	nRet = clsBSocket->ConnectToServer(&sendSocket, CCommunication::m_Port, CCommunication::m_Ip);
	if(0x00 != nRet)
	{	
		nRet = GetLastError();
		strShowInfo.Format(_T("[CCommunication::SendXmlToPhone] FunName=[%s] ConnectToServer ErrorNo=[%d].\r\n"),FunName, nRet);
		XWriteEventLog(strShowInfo);

		m_nExceptionCounter++;
		clsBSocket->CloseSocket( &sendSocket);

		if( 10061 == nRet)
		{
			return -33;
		}
		return -3;
	}
	
	//发送命令
	if( ! argRequest.IsEmpty())
	{
		nRet = clsBSocket->SendMsg(&sendSocket, argRequest);
		if(0x00 != nRet)
		{
			int iRevLen=-4;
			nRet = GetLastError();
			::XWriteEventLog(_T("[CCommunication::SendXmlToPhone] %s Request Error=[%d]\n"),FunName,nRet);
			if(nRet == 10060)
				iRevLen=-6;      //Socket 超时返回值        

			clsBSocket->CloseSocket( &sendSocket);
			return iRevLen;
		}
	}else
	{
		XWriteEventLog(_T("[CCommunication::SendXmlToPhone] argRequest is Empty.\r\n"));
		return -5;
	}


	//接收返回值
	argResponse = "";

	clsBSocket->RecvMsg(&sendSocket,argResponse,CallBack);
	return  argResponse.GetLength();
}


int  CCommunication::GetHeart4Phone(CString argRequest, CString& argResponse)
{
	//建立连接
	CString  strShowInfo;
	argResponse.Empty();
	CBaseSocket  OclsBSocket ; 
	CBaseSocket* clsBSocket = &OclsBSocket; 
	//CBaseSocket* clsBSocket = CBaseSocket::GetInstance(); 

	if(NULL == clsBSocket) 
	{
		XWriteEventLog(_T("[CCommunication::GetHeart4Phone] CBaseSocket::GetInstance Failed.\r\n"));
		return -1;
	}

	int nRet = -1;
	SOCKET sendSocket, oldSock;
	nRet = clsBSocket->NoNagleCreateSocket(&sendSocket);
	if(0x00 != nRet)
	{
		nRet = GetLastError();

		strShowInfo.Format(_T("[CCommunication::GetHeart4Phone] InitializeAndCreateSocket ErrorNo=[%d].\r\n"), nRet);
		XWriteEventLog(strShowInfo);

		clsBSocket->CloseSocket( &sendSocket);
		return -2;
	}

	HANDLE hCurProcess = ::GetCurrentProcess();
	BOOL bIsOK = ::DuplicateHandle(
								hCurProcess, (HANDLE)oldSock, 
								hCurProcess, (LPHANDLE)&sendSocket, 
								0x00, FALSE,  ///关闭子进程继承标志
								DUPLICATE_CLOSE_SOURCE);

	if(FALSE == bIsOK)
	{
		sendSocket = oldSock;
		strShowInfo.Format(_T("[CCommunication::GetHeart4Phone] DuplicateHandle Failed\r\n"));
		XWriteEventLog(strShowInfo);
	}

	nRet = clsBSocket->ConnectToServer(&sendSocket, CCommunication::m_Port, CCommunication::m_Ip);
	if(0x00 != nRet)
	{	
		nRet = GetLastError();
		strShowInfo.Format(_T("[CCommunication::GetHeart4Phone] ConnectToServer ErrorNo=[%d].\r\n"), nRet);
		XWriteEventLog(strShowInfo);

		//m_nExceptionHeart++;
		clsBSocket->CloseSocket( &sendSocket);

		if( 10061 == nRet)
		{
			return -33;
		}
		return -3;
	}
	//发送命令
	if( ! argRequest.IsEmpty())
	{
		nRet = clsBSocket->SendMsg(&sendSocket, argRequest);
		if(0x00 != nRet)
		{
			nRet = GetLastError();
			strShowInfo.Format(_T("[CCommunication::GetHeart4Phone] SendMsg ErrorNo=[%d].\r\n"), nRet);
			XWriteEventLog(strShowInfo);

			//m_nExceptionHeart++;
			clsBSocket->CloseSocket( &sendSocket);
			return -4;
		}
	}else
	{
		XWriteEventLog(_T("[CCommunication::GetHeart4Phone] argRequest is Empty.\r\n"));
		return -5;
	}


	//接收返回值
	argResponse = "";
	clsBSocket->RecvMsg( &sendSocket, argResponse);
	//BYTE pRevStrTmp[1024 + 1] = {0};
	//int dword=0, iRevLen = 0;

	//Sleep(200);
	//do
	//{
	//	memset(pRevStrTmp, 0x00, sizeof(pRevStrTmp));
	//	dword = clsBSocket->RecvMsg( &sendSocket, pRevStrTmp, 1024);

	//	if(dword > 0x00 )
	//	{
	//		argResponse += (CHAR*)pRevStrTmp;
	//		iRevLen += dword;
	//		/// 接收完成 GetHeart4Phone
	//		if((-1) != argResponse.Find(_T("</res>"))) dword = 0x00;
	//	}

	//}while( dword != SOCKET_ERROR && dword != 0);

	//if(SOCKET_ERROR != dword)
	//{
	//	m_bPhoneStatus = TRUE;
	//}else
	//{
	//	//m_nExceptionHeart++;
	//	iRevLen = dword;
	//	nRet = GetLastError();
	//	strShowInfo.Format(_T("[CCommunication::GetHeart4Phone]  ErrorNo=[%d].\r\n"), nRet);
	//	XWriteEventLog(strShowInfo);
	//}

	//if(argResponse.IsEmpty())
	//{
	//	strShowInfo.Format(_T("[CCommunication::GetHeart4Phone]  Resp Data is Empty.\r\n"));
	//	XWriteEventLog(strShowInfo);
	//}
	//关闭连接
	clsBSocket->CloseSocket( &sendSocket);
	return  argResponse.GetLength();

}


int  CCommunication::CheckHeart4PhoneS1(CBaseSocket  & ttBSocket , SOCKET & sendSocket)
{
	//建立连接
	CString  strShowInfo;

	int nRet = -1;

	nRet = ttBSocket.NoNagleCreateSocket(&sendSocket);
	if(0x00 != nRet)
	{
		nRet = GetLastError();

		strShowInfo.Format(_T("[CCommunication::CheckHeart4PhoneS1] InitializeAndCreateSocket ErrorNo=[%d].\r\n"), nRet);
		XWriteEventLog(strShowInfo);

		m_nExceptionHeart++;
		ttBSocket.CloseSocket( &sendSocket);
		return -2;
	}

	nRet = ttBSocket.ConnectToServer(&sendSocket, CCommunication::m_Port, CCommunication::m_Ip);
	if(0x00 != nRet)
	{	
		Sleep(1000);
		nRet = ttBSocket.ConnectToServer(&sendSocket, CCommunication::m_Port, CCommunication::m_Ip);
		if(nRet != 0x00)
		{
			Sleep(2000);
			nRet = ttBSocket.ConnectToServer(&sendSocket, CCommunication::m_Port, CCommunication::m_Ip);
		}

		if(nRet != 0x00)
		{
			nRet = GetLastError();
			strShowInfo.Format(_T("[CCommunication::CheckHeart4PhoneS1] ConnectToServer IP=[%s] Port =[%d] ErrorNo=[%d].\r\n"), CCommunication::m_Ip,CCommunication::m_Port,nRet);
			XWriteEventLog(strShowInfo);

			m_nExceptionHeart++;
			ttBSocket.CloseSocket( &sendSocket);

			if( 10061 == nRet)
			{
				return -33;
			}
			return -3;
		}
	}
	else
	{
		strShowInfo.Format(_T("[CCommunication::CheckHeart4PhoneS1] ConnectToServer IP=[%s] Port =[%d] Connect OK\r\n"), CCommunication::m_Ip,CCommunication::m_Port);
		XWriteEventLog(strShowInfo);

	}

	//////////////////////////////////////////////////////////////////////
	return  0;

}


int  CCommunication::CheckHeart4PhoneS2(CBaseSocket  & ttBSocket , SOCKET & sendSocket, CString argRequest, CString& argResponse)
{
		//////////////////////////////////////////////////////////////////////
	
		int nRet = 0;
		CString strShowInfo;
			//发送命令
		if( ! argRequest.IsEmpty())
		{
			//nRet = ttBSocket.SetCallFuncName(CCommunication::m_strCallFuncName);
			nRet = ttBSocket.SendMsg(&sendSocket, argRequest);
			if(0x00 != nRet)
			{
				nRet = GetLastError();
				strShowInfo.Format(_T("[CCommunication::CheckHeart4PhoneS2] SendMsg ErrorNo=[%d].\r\n"), nRet);
				XWriteEventLog(strShowInfo);

				m_nExceptionHeart++;
				//ttBSocket.CloseSocket( &sendSocket);
				return -4;
			}
		}else
		{
			XWriteEventLog(_T("[CCommunication::CheckHeart4PhoneS2] argRequest is Empty.\r\n"));
			return -5;
		}

		//接收返回值
		argResponse = "";
		BYTE pRevStrTmp[1024 + 1] = {0};
		int dword=0, iRevLen = 0;

		Sleep(200);
		do
		{
			memset(pRevStrTmp, 0x00, sizeof(pRevStrTmp));
			dword = ttBSocket.RecvMsg( &sendSocket, pRevStrTmp, 1024);

			if(dword > 0x00 )
			{
				argResponse += (CHAR*)pRevStrTmp;
				iRevLen += dword;
				/// 接收完成 CheckHeart4Phone
				if((-1) != argResponse.Find(_T("</res>"))) dword = 0x00;
			}else
			{
				Sleep(200);
			}

		}while( dword != SOCKET_ERROR && dword != 0);

		if(SOCKET_ERROR != dword)
		{
			m_bPhoneStatus = TRUE;
		}else
		{
			iRevLen = dword;
			m_nExceptionHeart++;

			nRet = GetLastError();
			strShowInfo.Format(_T("[CCommunication::CheckHeart4PhoneS2]  ErrorNo=[%d].\r\n"), nRet);
			XWriteEventLog(strShowInfo);
		}

		if(argResponse.IsEmpty())
		{
			strShowInfo.Format(_T("[CCommunication::CheckHeart4PhoneS2]  Resp Data is Empty.\r\n"));
			XWriteEventLog(strShowInfo);
		}

		//CString  strAckEnd = _T("===ack===");
		//nRet = ttBSocket.SendMsg(&sendSocket, strAckEnd);

	return  iRevLen;

}
void CCommunication::SetConnectIpAndPort(CString Ip,DWORD Port)
{
	m_Ip=Ip;
	m_Port=Port;
}

CString CCommunication::GetRequestFuncationName(CString argReqeust)
{
	CString Str=_T("<fun>");
	int Pos = argReqeust.Find(Str);
	int EndPos = argReqeust.Find(_T("</fun>"));
	CString Temp=argReqeust.Mid(Pos+Str.GetLength(),EndPos-Pos-Str.GetLength());
	return Temp;
}
