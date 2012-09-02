// MySocket.cpp: implementation of the CBaseSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../Include/BaseSocket.h"
#include "../Include/CommonFunction.h"
#define XWriteEventLog TRACE

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
////static int addlen;
////static sockaddr_in ServerAddress;
////static SOCKET Server_Socket[MAXCOUNT];
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

////CBaseSocket* CBaseSocket::m_pInstance = 0;
////
////CBaseSocket* CBaseSocket::GetInstance()
////{
////	if( m_pInstance == 0)
////	{
////			m_pInstance = new CBaseSocket();
////	}
////
////	return m_pInstance ;
////}

////void  CBaseSocket::DesInstance()
////{
////
////	if( m_pInstance != NULL)
////	{
////		delete m_pInstance;
////		m_pInstance = NULL;
////
////	}
////}


CBaseSocket::CBaseSocket()
{

	////WORD wVersionRequested;
	////WSADATA wsaData;
	////int err;

	////wVersionRequested=MAKEWORD(1,1);  // for mobile it 1.1 C Sock
	////err=WSAStartup(wVersionRequested,&wsaData);
	////if (LOBYTE(wsaData.wVersion)!=1||HIBYTE(wsaData.wVersion)!=1)
	////{
	////	WSACleanup();
	////}
	
		//  初始化 Socket 数组
	////for (int Loop = 0;Loop < MAXCOUNT;Loop++)
	////	Server_Socket[Loop] = NULL;

	m_strCallFuncName = _T("");
}

CBaseSocket::~CBaseSocket()
{
		///WSACleanup();
		//m_pInstance = NULL;
}

/***********************************************************
*  功能：初始化并创建 Socket
*  参数 0 ：Socket
*  返回值：若返回 0 成功
*                 1 初始化并创建 Socket 时出现了异常
*                 2 创建 Socket 失败
*				 -1 不能装入 Windows Sockets DLL
*                -2 获取主机名失败
************************************************************/
	/*  调用WSAStartup(WORD wVersionRequested,LPWSADATA lpWSAData)函数初始化 Winsock
	
	参数：   
	wVersionRequested	表示想使用的Windows Sockets API 版本
	lpWSAData				指向的WSADATA 资料的指针
	  
	返回值： 成功返回 0 ；
		
	失败返回如下值：
	WSASYSNOTREADY：     表示网络设备没有准备好
	WSAVERNOTSUPPORTED： Winsock  的版本信息号不支持
	WSAEINPROGRESS：     一个阻塞式的Winsock1.1 存在于进程中
	WSAEPROCLIM：        已经达到 Winsock 使用量的上限
    WSAEFAULT:           lpWSAData 不是一个有效的指针*/

int CBaseSocket::InitializeAndCreateSocket(SOCKET* SocketIn,bool IsSetWaitOutTime)
{
	WSADATA wsaData;
	char chLocalInfo[64];
	
	try
	{

		if (gethostname(chLocalInfo, sizeof(chLocalInfo)))
		{
			int iR = WSAGetLastError();
			return -2;
		}

		//  创建 socket
		*SocketIn = socket(PF_INET,SOCK_STREAM,0);
			
		if (*SocketIn == INVALID_SOCKET)
		{
			return -3;
		}

		int nRet = 0x00;
		int nTimeOut = 10*1000;
		if(IsSetWaitOutTime)
		{
			nRet = ::setsockopt(*SocketIn, SOL_SOCKET, SO_SNDTIMEO, (char*)&nTimeOut, sizeof(nTimeOut) );
			if( SOCKET_ERROR== nRet)
			{
				return -4;
			}
			nRet = ::setsockopt(*SocketIn, SOL_SOCKET, SO_RCVTIMEO, (char*)&nTimeOut, sizeof(nTimeOut) );
			if( SOCKET_ERROR ==  nRet)
			{
				return -5;
			}	

		}
		else
		{
			nTimeOut = 40*1000;
			
			nRet = ::setsockopt(*SocketIn, SOL_SOCKET, SO_SNDTIMEO, (char*)&nTimeOut, sizeof(nTimeOut) );
			if( SOCKET_ERROR== nRet)
			{
				return -4;
			}
			nRet = ::setsockopt(*SocketIn, SOL_SOCKET, SO_RCVTIMEO, (char*)&nTimeOut, sizeof(nTimeOut) );
			if( SOCKET_ERROR ==  nRet)
			{
				return -5;
			}	
		}

	
		//IPPROTO_TCP;
		BOOL nCloseNagle = TRUE;
		nRet = ::setsockopt(*SocketIn, IPPROTO_TCP, TCP_NODELAY, (char*)&nCloseNagle, sizeof(nCloseNagle) );
		if( SOCKET_ERROR ==  nRet)
		{
			return -6;
		}	

		///// SO_DONTLINER
		//BOOL nNoDelay = TRUE;
		//nRet = ::setsockopt(*SocketIn, SOL_SOCKET, SO_DONTLINGER, (char*)&nNoDelay, sizeof(nNoDelay) );
		//if( SOCKET_ERROR ==  nRet)
		//{
		//	return -7;
		//}	
		
		linger m_sLinger;
		m_sLinger.l_onoff = 1;  // (在closesocket()调用,但是还有数据没发送完毕的时候容许逗留)
		m_sLinger.l_linger = 3; // (容许逗留的时间为3秒)
		nRet = setsockopt(*SocketIn,SOL_SOCKET,SO_LINGER, (const char*)&m_sLinger,sizeof(linger)); 
		if( SOCKET_ERROR ==  nRet)
		{
			return -7;
		}

		/// SO_REUSEADDR
		BOOL nReUseAddress = TRUE;
		nRet = ::setsockopt(*SocketIn, SOL_SOCKET, SO_REUSEADDR, (char*)&nReUseAddress, sizeof(nReUseAddress) );
		if( SOCKET_ERROR ==  nRet)
		{
			return -8;
		}	

	}  //  End_try
	catch (...)
	{
		return 1;
	}

//  若成功返回 0
return 0;
}


int CBaseSocket::NoNagleCreateSocket(SOCKET* SocketIn)
{
	WSADATA wsaData;
	char chLocalInfo[64];
	
	try
	{

		if (gethostname(chLocalInfo, sizeof(chLocalInfo)))
		{
			int iR = WSAGetLastError();
			return -2;
		}

		//  创建 socket
		*SocketIn = socket(PF_INET,SOCK_STREAM,0);
			
		if (*SocketIn == INVALID_SOCKET)
		{
			return -3;
		}

		int nTimeOut = 30*1000;
		int nRet = 0x00;
		nRet = ::setsockopt(*SocketIn, SOL_SOCKET, SO_SNDTIMEO, (char*)&nTimeOut, sizeof(nTimeOut) );
		if( SOCKET_ERROR== nRet)
		{
			return -4;
		}
		nRet = ::setsockopt(*SocketIn, SOL_SOCKET, SO_RCVTIMEO, (char*)&nTimeOut, sizeof(nTimeOut) );
		if( SOCKET_ERROR ==  nRet)
		{
			return -5;
		}		

		//IPPROTO_TCP;
		BOOL nCloseNagle = TRUE;
		nRet = ::setsockopt(*SocketIn, IPPROTO_TCP, TCP_NODELAY, (char*)&nCloseNagle, sizeof(nCloseNagle) );
		if( SOCKET_ERROR ==  nRet)
		{
			return -6;
		}		
		///// SO_DONTLINER
		//BOOL nNoDelay = TRUE;
		//nRet = ::setsockopt(*SocketIn, SOL_SOCKET, SO_DONTLINGER, (char*)&nNoDelay, sizeof(nNoDelay) );
		//if( SOCKET_ERROR ==  nRet)
		//{
		//	return -7;
		//}		

		linger m_sLinger;
		m_sLinger.l_onoff = 1;  // (在closesocket()调用,但是还有数据没发送完毕的时候容许逗留)
		m_sLinger.l_linger = 3; // (容许逗留的时间为3秒)
		nRet = setsockopt(*SocketIn,SOL_SOCKET,SO_LINGER, (const char*)&m_sLinger,sizeof(linger)); 
		if( SOCKET_ERROR ==  nRet)
		{
			return -7;
		}


		/// SO_REUSEADDR
		BOOL nReUseAddress = TRUE;
		nRet = ::setsockopt(*SocketIn, SOL_SOCKET, SO_REUSEADDR, (char*)&nReUseAddress, sizeof(nReUseAddress) );
		if( SOCKET_ERROR ==  nRet)
		{
			return -8;
		}

		BOOL nDebug = TRUE;
		nRet = ::setsockopt(*SocketIn, SOL_SOCKET, SO_DEBUG, (char*)&nDebug, sizeof(nDebug) );
		if( SOCKET_ERROR ==  nRet)
		{
			return -9;
		}	

		/////设置阻塞模式
		//u_long iMode = 1;
		//ioctlsocket(*SocketIn, FIONBIO, &iMode);


	}  //  End_try
	catch (...)
	{
		return 1;
	}

//  若成功返回 0
return 0;
}

/***********************************************************
*  功能：创建 Socket 并连接到服务器
*  参数 0 ：客户端 Socket
*  参数 1 ：端口号
*  参数 2 ：IP 地址
*  返回值：若返回 0 成功
*                 1 连接服务器时出现了异常
*				 -1 非法 IP 地址
*                -2 系统连接服务器失败
************************************************************/
int CBaseSocket::ConnectToServer(SOCKET* Socket_Client,int nProt, CString  sIPAddress)
{
	DWORD dwIPAddr;
	SOCKADDR_IN sockAddr;
	CString strLogMsg;

	try
	{
		char * TempIP= TransUncodeWcharToUtf8Char(sIPAddress.GetBuffer());

		//  验证IP 地址若错误则信息提示并终止	
		if((dwIPAddr = inet_addr(TempIP)) == INADDR_NONE)
		{
			delete []TempIP;
			return -1;
		}
		delete []TempIP;
		
		sockAddr.sin_family = AF_INET;
		sockAddr.sin_port = htons(nProt);
		sockAddr.sin_addr.S_un.S_addr = dwIPAddr;
		
		//  调用 connect(m_hSocket,(LPSOCKADDR)&sockAddr,sizeof(sockAddr)) 函数连接通信对象
		/// 若连接失败时返回SOCKET_ERROR
		int nConnect = connect(*Socket_Client,(LPSOCKADDR)&sockAddr,sizeof(sockAddr));

		if(nConnect)
		{
			int nRet = GetLastError();
			////strLogMsg.Format(_T("[CBaseSocket::ConnectToServer] 系统连接服务器失败 [%d]\r\n"), nRet);
			////XWriteEventLog(m_strCallFuncName + strLogMsg );

			return -2;
		}
	}  //  End_try
	catch (...) 
	{
			strLogMsg.Format(_T("[CBaseSocket::ConnectToServer] 连接服务器时出现了异常 [%d]\r\n"),GetLastError());
			XWriteEventLog(m_strCallFuncName + strLogMsg);
		return 1;
	}
return 0;
}

/***********************************************************
*  功能：绑定并监听 Socket
*  参数 0 ：服务器端 Socket
*  参数 1 ：端口号
*  返回值：若返回 0 成功
*                 1 绑定并监听 Socket 时出现了异常
*				 -1 绑定 Socket 失败
*                -2 服务器监听失败
************************************************************/
int CBaseSocket::BindAndListenSocket(SOCKET* Socket_Server, unsigned short nProt)
{
    u_long  ul = 1;  


	//  本地端口号设为 8802
	try
	{
		//  设置服务器端地址
		m_oServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);   
		m_oServerAddress.sin_family = AF_INET;
		m_oServerAddress.sin_port = htons(nProt);
		m_addlen = sizeof(m_oServerAddress);
		
		//  绑定
		if(bind(*Socket_Server, (sockaddr*)&m_oServerAddress, m_addlen) == SOCKET_ERROR)
		{
		    //CReadOrWriteInfo::WriteInfoToiniFile("SOCKET","绑定 Socket 失败!",2);
			return -1;
			
		}
		
		//设置非阻塞方式连接   
		//ioctlsocket(*Socket_Server,FIONBIO, (u_long*)&ul);  
		
		//  监听 socket
		if (listen(*Socket_Server, QUEUE_SIZE) == SOCKET_ERROR)
		{
			//  调用视图类中的显示函数将 MO 消息输出到界面
		    //CReadOrWriteInfo::WriteInfoToiniFile("SOCKET","服务器监听失败!",2);
			return -2;
		}
		
		else
		{    
			AfxMessageBox(_T("系统开始服务!"));
			//  启动服务器线程
            //AfxBeginThread(&ServerThread,Socket_Server,NULL);
			return 0;

		}

	}  //  End_try
	catch (...) 
	{
		//CReadOrWriteInfo::WriteInfoToiniFile("SOCKET","绑定监听 Socket 时出现了异常!",1);
		return 1;
	}

}

/***********************************************************
*  功能：发送信息
*  参数 0 ：发送 Socket
*  参数 1 ：发送的信息
*  返回值：若返回 0 成功
*                 1 发送信息时出现了异常
*				 -1 发送信息时出错
************************************************************/
int CBaseSocket::SendMsg(SOCKET *Socket_Send, CString  Sendstr)
{
	// TODO: Add your control notification handler code here
	char buffer[65536] = {0};    ///64K        
	int Len;
	CString  strLogMsg;
	int nRet = 0x00;
	char* TempData = NULL;

	try
	{
		
		TempData =TransUncodeWcharToUtf8Char(Sendstr.GetBuffer());
		Sendstr.ReleaseBuffer();
		Len=strlen(TempData);
		
		if(send(*Socket_Send,TempData,Len,0) == SOCKET_ERROR)
		{
			delete []TempData;
			return -1;
		}
	
		delete [] TempData;

		//  若发送信息正确时返回 0
		return 0;
	}
	catch (...) 
	{
		if(TempData != NULL)
			delete [] TempData;
		return -1;
	}
			
}



/***********************************************************
*  功能：接收信息
*  参数 0 ：接收 Socket
*  参数 1 ：发送的信息
*  返回值：若返回 0 成功
*                 1 接收信息时出现了异常
*				 -1 接收信息时出错
************************************************************/
int CBaseSocket::RecvMsg(SOCKET *Socket_Recv, BYTE* Recvstr,long RecvstrLegth)
{
	int nRet = 0x00;
	long ReveLength = 0;
	CString  strLogMsg;
	try
	{

		ReveLength = recv(*Socket_Recv,(LPSTR)Recvstr,RecvstrLegth,0);
		
		//调用recv函数接收数据
		if(ReveLength == SOCKET_ERROR)
		{
			//nRet  = GetLastError();
			//strLogMsg.Format(_T("[CBaseSocket::RecvMsg]  接收信息时出错[%d]\r\n"), nRet);
			//XWriteEventLog(m_strCallFuncName + strLogMsg);

			return SOCKET_ERROR;
		}
		return ReveLength;
	}
	catch (...)
	{
		nRet  = GetLastError();
		strLogMsg.Format(_T("[CBaseSocket::RecvMsg]  接收信息时出现了异常[%d]\r\n"), nRet);
		XWriteEventLog(m_strCallFuncName + strLogMsg);

		return SOCKET_ERROR;
	}
}

int CBaseSocket::RecvMsg(SOCKET *Socket_Recv,CString& Recvstr,FunctionSocketCallBack CallBack)
{
	while(true)
	{
		char buffer[1024*10+1];
		memset(buffer,'\0',1024*10+1);
		int RecvByte = recv(*Socket_Recv,buffer,1024*10,0);
		if(RecvByte != -1 && RecvByte != 0)
		{
		
			wchar_t* Temp=TransUtf8CharToUncodeWchar(buffer);
			Recvstr+=CString(Temp);
			delete []Temp;
			if(Recvstr.Find(_T("</res>")) == -1)
				continue;

			if(CallBack != NULL)
			{
				CallBack(Recvstr);
				if(Recvstr.Find(_T("<value>end</value>")) != -1 && Recvstr.Find(_T("<name>flag</name>")) != -1 || Recvstr.Find(_T("<name>error</name>")) != -1 )
					break;

				Sleep(1000);
				Recvstr.Empty();
				char ContinueChar='R';
				send(*Socket_Recv,&ContinueChar,1,0);
		
			}
		}

		else
			break;
	}

	if(Recvstr.IsEmpty())
		return 0;
	return 1;
}

/***********************************************************
*  功能：关闭 Socket 短开连接
*  参数0：
*  返回值：0  关闭 Socket 成功
*		  -1  关闭 Socket 时出现了异常
************************************************************/
int CBaseSocket::CloseSocket(SOCKET *SocketIn)
{
	CString strLogMsg;
	int nRet  = -1;
	try
	{
		//  关闭 Socket 短开连接
		nRet = closesocket(*SocketIn);

		//strLogMsg.Format(_T("[CBaseSocket::CloseSocket]  CloseSocket[%d]\r\n"), nRet);
		//XWriteEventLog(strLogMsg);
		return nRet;
	}
	catch (...)
	{
		nRet = ::GetLastError();
		strLogMsg.Format(_T("[CBaseSocket::CloseSocket]  关闭 Socket 时出现了异常[%d]\r\n"), nRet);
		XWriteEventLog(m_strCallFuncName + strLogMsg);
		return -1;
	}
}

/***********************************************************
*  功能：获得还没有使用的 Socket数组号
*  返回值：返回尚未使用的 Socket 数组号
*		   -1  没有空闲的 Socket 数组号
************************************************************/
////int CBaseSocket::GetCount()
////{
////	for (int Loop = 0;Loop < MAXCOUNT;Loop++)
////	{
////		if (Server_Socket[Loop] == NULL)
////			return Loop;
////	}
////	return -1;
////}


/*
 利用FormatMessage函数得到错误代码的文本显示。而错误代号则可由GetLastError()获得。（_WINDOWS）
 */
//char * ErrorToString()
//{
//	DWORD nErrorNo = GetLastError ( ); // 得到错误代码
//	 LPSTR lpBuffer;    
//	 FormatMessage ( FORMAT_MESSAGE_ALLOCATE_BUFFER  |
//	 FORMAT_MESSAGE_IGNORE_INSERTS  |
//	 FORMAT_MESSAGE_FROM_SYSTEM,
//	 NULL,
//	nErrorNo, // 此乃错误代码，通常在程序中可由 GetLastError()得之
//	LANG_NEUTRAL,
//	 (LPTSTR) & lpBuffer,
//	0 ,
//	NULL );
//	CString strErrorCause  =  lpBuffer  ?  _T(lpBuffer) : _T( " Sorry, cannot find this error info. " );
//	UpdateData (FALSE);
//	//  Free the buffer.
//	LocalFree (lpBuffer); 
//}


int CBaseSocket::SetCallFuncName(CString strCallFuncName)
{
		m_strCallFuncName = strCallFuncName;
		return 0;
 }

