#include "StdAfx.h"
#include "../Include/LogServer.h"



long                                CLogServer::m_UpLogTime      = 1000*60*1;               //15分钟上传一次           
long                                CLogServer::m_WriteLogTime   = 1000*60;                  //一分钟写一次日志   
long                                CLogServer::m_LogFileSize    = 1024*10;                //10K
HANDLE                              CLogServer::m_StopEvent      = INVALID_HANDLE_VALUE;             
HANDLE                              CLogServer::m_StopUpEvent    = INVALID_HANDLE_VALUE;           
HANDLE                              CLogServer::m_WriteLogEvent  = INVALID_HANDLE_VALUE; 
HANDLE                              CLogServer::m_UpLogEvent     = INVALID_HANDLE_VALUE;
HANDLE                              CLogServer::m_LogThread      = INVALID_HANDLE_VALUE;            
HANDLE                              CLogServer::m_UpLogThread    = INVALID_HANDLE_VALUE;          
CRITICAL_SECTION                    CLogServer::m_CriticalSection;       
map<CLogServer::eLogFileType,vector<CString>>   CLogServer::m_CaheLog;              

//CString                             CLogServer::m_strDiskSerial  = _T(""); 
//CString                             CLogServer::m_strMacAddress  = _T("");
//CString                             CLogServer::m_strDerivation  = _T("");

CLogServer::CLogServer(void)
{
}

CLogServer::~CLogServer(void)
{
}

//开启日志服务
void CLogServer::StartLogServer()
{
	//初始化临界区
	InitializeCriticalSection(&m_CriticalSection);
	CloseEventHandle();

	m_StopEvent      = ::CreateEvent(NULL,true,false,NULL);
	m_StopUpEvent    = ::CreateEvent(NULL,true,false,NULL);
	m_UpLogEvent     = ::CreateEvent(NULL,true,false,NULL);
	m_WriteLogEvent  = ::CreateEvent(NULL,true,false,NULL);
	m_LogThread      = ::CreateThread( NULL, 0, ManageLogThread, NULL, 0, NULL );
	m_UpLogThread    = ::CreateThread( NULL, 0, UpLogThread, NULL, 0, NULL );

	// zhaoshan [2012.02.26]	
	// 硬盘序列号
/*	CDiskData disk;
	disk.Init();
	m_strDiskSerial = disk.m_HardDriveSerialNumber;
*/	
	// 获取MAC网卡
/*	CStatisticLogInfo* pCStatisticLogInfo = NULL; // 统计信息类
	pCStatisticLogInfo = new CStatisticLogInfo();
	if( pCStatisticLogInfo )
	{
		pCStatisticLogInfo->m_oHttpBase.GetMacAddress2( m_strMacAddress );
	}
*/

}


//关闭日志服务
void CLogServer::StopLogServer()
{
	CloseEventHandle();
	DeleteCriticalSection(&m_CriticalSection);
}

//设置多久上传一次日志
void CLogServer::SetUpLogTime(long TimeLog)                     //TimeLog 以秒为单位
{
	m_UpLogTime = TimeLog;
}

//设置多久写日志到文件中
void CLogServer::SetWriteLogTime(long TimeLog)                  //TimeLog 以秒为单位
{
	m_WriteLogTime = TimeLog;
}

//设置日志文件大小 
void CLogServer::SetLogSize(long LogSize)                       //LogSize 日志文件大小 以M为单位
{
	m_LogFileSize = LogSize*1024*1024;
}

//写人操作日志文件
void CLogServer::WriteLog(CString LogStr,eLogFileType LogFileType)  //LogStr 日志,LogFileType 日志文件类型，当前只支持操作日志
{
	if(LogFileType == MAIN_LOG_FILE_TYPE)
	{
		InsertData(LogStr);
	}
}

//写人操作日志文件
void CLogServer::WriteLog(const char* Format,...)
{
	va_list   ParamList; 
	va_start(ParamList,Format);
	char Buffer[1025];
	memset(Buffer,0,1025);
	_vsnprintf(Buffer,1024,Format,ParamList);
	va_end(ParamList);
	InsertData(CString(Buffer));
}

//写人操作日志文件
void CLogServer::WriteLog(const wchar_t* Format,...)
{
	va_list   ParamList; 
	va_start(ParamList,Format);
	wchar_t Buffer[1025];
	memset(Buffer,0,1025*sizeof(wchar_t));
	vswprintf_s(Buffer,1024,Format,ParamList);
	va_end(ParamList);
	InsertData(Buffer);
}


//日志管理线程
DWORD WINAPI CLogServer::ManageLogThread(LPVOID lpVoid)
{
	CString FileName=GetLogFileName();
	CString TempFileName=FileName+_T("_tmp");
	DWORD Flag=CREATE_ALWAYS;
	if(::IsFilesExit(TempFileName))
		Flag = OPEN_EXISTING;

	HANDLE FileHandle=CreateFile(TempFileName,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL,Flag,FILE_ATTRIBUTE_NORMAL,NULL);
	if(FileHandle == INVALID_HANDLE_VALUE)
		return 2;

	HANDLE WriteLogTime = ::CreateWaitableTimer(NULL,false,NULL);
	LARGE_INTEGER Time;
	Time.QuadPart = m_WriteLogTime*(-10000000);
	::SetWaitableTimer(WriteLogTime, &Time,m_WriteLogTime , NULL, NULL, 0);

	HANDLE EventArray[3]={WriteLogTime,m_WriteLogEvent,m_StopEvent};

	while(true)
	{
		bool IsExit=false;
		DWORD Ret = ::WaitForMultipleObjects(3,EventArray,false,INFINITE);
		switch(Ret)
		{
		case 0:
		case 1:
			{
				if(Ret == 1)
					::ResetEvent(m_WriteLogEvent);

				EnterCriticalSection(&m_CriticalSection);
				vector<CString> LogStr=m_CaheLog[MAIN_LOG_FILE_TYPE];
				if(!LogStr.empty())
					m_CaheLog[MAIN_LOG_FILE_TYPE].clear();
				LeaveCriticalSection(&m_CriticalSection);
				if(LogStr.empty())
					continue;

				::SetFilePointer(FileHandle,0,0,FILE_END);
				for(int Index = 0; Index < (int)LogStr.size(); Index++)
				{
					DWORD WriteBytes=0;
					char* TempStr=::ConvertFromUnicodeToUtf8(LogStr[Index].GetBuffer());
					LogStr[Index].ReleaseBuffer();
					::WriteFile(FileHandle,TempStr,strlen(TempStr),&WriteBytes,NULL);
					delete []TempStr;
				}

				DWORD dwFileSize;
				dwFileSize = ::GetFileSize(FileHandle,NULL);
			
				if( dwFileSize == 0xFFFFFFFF )
				{
					DWORD dwError = GetLastError();
				}
				else if( dwFileSize > m_LogFileSize )
				{
					CloseHandle(FileHandle);
					if(::CopyFile(TempFileName,FileName,false))
						::DeleteFile(TempFileName);

					::SetEvent(m_UpLogEvent);
					FileName=GetLogFileName();
					TempFileName=FileName+_T("_tmp");
					DWORD Flag=CREATE_ALWAYS;
					if(::IsFilesExit(TempFileName))
						Flag = OPEN_EXISTING;

					FileHandle=CreateFile(TempFileName,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL,Flag,FILE_ATTRIBUTE_NORMAL,NULL);
				}
			}
			break;
		default:
			IsExit = true;
			break;
		}
		if(IsExit == true)
			break;
	}


	if(WriteLogTime != INVALID_HANDLE_VALUE)
		CloseHandle(WriteLogTime);
	return 0;
}

//日志上传线程
DWORD CLogServer::UpLogThread(LPVOID lpVoid)
{
	LARGE_INTEGER Time;
	HANDLE UpLogTime    = ::CreateWaitableTimer(NULL,false,NULL);
	Time.QuadPart = -m_UpLogTime*10000000;    
	::SetWaitableTimer(UpLogTime, &Time,m_UpLogTime , NULL, NULL, 0);
	HANDLE EventArray[3]={UpLogTime,m_UpLogEvent,m_StopUpEvent};

	while(true)
	{
		bool IsExit=false;
		DWORD Ret = ::WaitForMultipleObjects(3,EventArray,false,INFINITE);
		switch(Ret)
		{
		case 0:
		case 1:
			{
				if(Ret == 1)
					::ResetEvent(m_UpLogEvent);

				vector<CString> FileNameList=GetLogFileNameList();
				if(FileNameList.empty())
					continue;

				CString  strServer, strObjectPath ,  strTemp;
				INTERNET_PORT nPort;
				DWORD  nServiceType;
				CString strUpLoadRedirectionUrl = CAppManager::GetInstance()->m_strLogServerUrl;//_T("http://10.36.64.72:9091/pcserver/uploadLog");

				if (!AfxParseURL(strUpLoadRedirectionUrl,  nServiceType,  strServer,  strObjectPath,  nPort))
					continue;

				for(int Index = 0; Index < (int)FileNameList.size(); Index++)
				{
					if(!::WaitForSingleObject(m_StopUpEvent,0))
							break;

					CString FilePath = GetLogFileDir()+FileNameList[Index];
					HANDLE FileHandle=CreateFile(FilePath,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
					if(FileHandle == INVALID_HANDLE_VALUE)
						continue;
					
					DWORD AllLen = GetFileSize(FileHandle,NULL);
				
					if( AllLen <= 0 ) // zhaoshan [2012.02.09]
					{
						CloseHandle(FileHandle);				
						continue;
					}					
				
					CInternetSession  InernetSession;
					CHttpConnection * pHttpConnection  = NULL;
					CHttpFile *	pHttpFile = NULL;
					try
					{
						const int nTimeOut = 5000;
						InernetSession.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, nTimeOut);  //重试之间的等待延时
						InernetSession.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);		    //重试次数
						pHttpConnection =  InernetSession.GetHttpConnection( strServer, INTERNET_FLAG_DONT_CACHE, nPort, NULL, NULL ); 
						if(!pHttpConnection)
						{
							InernetSession.Close();
							continue;
						}

						pHttpFile = pHttpConnection->OpenRequest(CHttpConnection::HTTP_VERB_POST,strObjectPath,NULL,0x00, NULL, _T("HTTP/1.1"));
						if(pHttpFile == NULL)
						{
							pHttpConnection->Close();
							InernetSession.Close();
							continue;
						}

						CString   ReqMsgHeader;
						
						ReqMsgHeader +=  _T("Content-Type: image/jpeg;  UTF-8  name=")+FileNameList[Index];
						ReqMsgHeader +=  _T("\r\n");
						CString FileSize;
						FileSize.Format(_T("contentSize: %d"),AllLen);
						ReqMsgHeader +=  FileSize;
						ReqMsgHeader +=  _T("\r\n");
						ReqMsgHeader +=  _T("UploadName: ")+FileNameList[Index];
						ReqMsgHeader +=  _T("\r\n");

						BOOL bSendMsgOK;
						bSendMsgOK = pHttpFile->AddRequestHeaders(ReqMsgHeader,  HTTP_ADDREQ_FLAG_COALESCE  |  HTTP_ADDREQ_FLAG_ADD );
						bSendMsgOK = pHttpFile->SendRequestEx(AllLen, HSR_SYNC | HSR_INITIATE); 
						if(!bSendMsgOK)
						{
							pHttpFile->Close();
							pHttpConnection->Close();
							InernetSession.Close();
						}

						DWORD WriteLen=0;
						bool IsOk=false;
						while (true)   
						{
							char Buffer[1024];
							DWORD ReadBytes=0;
							::ReadFile(FileHandle,Buffer,1024,&ReadBytes,NULL);
							if(ReadBytes == 0)
								break;

							pHttpFile->Write(Buffer, ReadBytes);
							WriteLen+=ReadBytes;
							if(WriteLen == AllLen)
							{
								IsOk=true;
								break;
							}

							if(!::WaitForSingleObject(m_StopUpEvent,0))
								break;
						}
						CloseHandle(FileHandle);
						if(IsOk)
							DeleteFile(FilePath);
						pHttpFile->Close();
						pHttpConnection->Close();
						InernetSession.Close();
					}catch(...)
					{
						if(pHttpFile)
							pHttpFile->Close();

						if(pHttpConnection)
							pHttpConnection->Close();
						InernetSession.Close();
					}

				}
			}
			break;
		default:
			IsExit = true;
			break;
		}
		if(IsExit == true)
			break;
	}

	if(UpLogTime != INVALID_HANDLE_VALUE)
		CloseHandle(UpLogTime);
	return 0;
}

//关闭句柄
void CLogServer::CloseEventHandle()
{
	if(m_WriteLogEvent != INVALID_HANDLE_VALUE)
		SetEvent(m_WriteLogEvent);
	if(m_StopUpEvent != INVALID_HANDLE_VALUE)
		SetEvent(m_StopUpEvent);
	if(m_StopEvent != INVALID_HANDLE_VALUE)
		SetEvent(m_StopEvent);

	if(m_UpLogThread != INVALID_HANDLE_VALUE)
	{
		if(WaitForSingleObject(m_UpLogThread,1000) != 0)
		{
			::TerminateThread(m_UpLogThread,1);
		}
		CloseHandle(m_UpLogThread);
	}

	if(m_LogThread != INVALID_HANDLE_VALUE)
	{
		if(WaitForSingleObject(m_LogThread,2000) != 0)
		{
			::TerminateThread(m_LogThread,1);
		}
		CloseHandle(m_LogThread);
	}

	if(m_WriteLogEvent != INVALID_HANDLE_VALUE)
		CloseHandle(m_WriteLogEvent);
	if(m_StopUpEvent != INVALID_HANDLE_VALUE)
		CloseHandle(m_StopUpEvent);
	if(m_StopEvent != INVALID_HANDLE_VALUE)
		CloseHandle(m_StopEvent);

	if(m_UpLogEvent != INVALID_HANDLE_VALUE)
		CloseHandle(m_UpLogEvent);

	m_StopEvent      = INVALID_HANDLE_VALUE;             
	m_StopUpEvent    = INVALID_HANDLE_VALUE;           
	m_WriteLogEvent  = INVALID_HANDLE_VALUE;         
	m_LogThread      = INVALID_HANDLE_VALUE;            
	m_UpLogThread    = INVALID_HANDLE_VALUE;  
	m_UpLogEvent     = INVALID_HANDLE_VALUE;
}

//获取日志头部
CString CLogServer::GetLogHeader(eLogFileType LogFileType)
{
	if(LogFileType == MAIN_LOG_FILE_TYPE)
	{
		CString MacAddress   = theApp.m_strUserMacAddress.IsEmpty() ? _T("NULL"):theApp.m_strUserMacAddress;

		CString MobileID     = theApp.m_strUserMobileID.IsEmpty() ? _T("NULL"):theApp.m_strUserMobileID;
		CString ParamVersion = theApp.m_strParamVersion.IsEmpty() ? _T("NULL"):theApp.m_strParamVersion;
		CString ApkVersion   = theApp.m_strApkVersion.IsEmpty() ? _T("NULL"):theApp.m_strApkVersion;
		CString Date         = GetLocalTime();

		CString strMainBoard = theApp.m_strMainBord.IsEmpty() ? _T("NULL") : theApp.m_strMainBord; // 主板

		// 渠道标识
		CString strDerivation;
		CAppManager *pAppMgr = CAppManager::GetInstance();
		CString Derivation = _T("");
		if( NULL != pAppMgr )
		{
			strDerivation = pAppMgr->m_strDerivation;
		}
		 
 		CString strDiskSerial = theApp.m_strDiskSerial.IsEmpty() ? _T("NULL") : theApp.m_strDiskSerial;
// 
// 		CString m_strIMEI; // 手机ID
// 		CString m_strSIM; // sim卡
// 		CString m_strPhoneType; // 手机型号

		CString strIMEI = theApp.m_strIMEI.IsEmpty() ? _T("NULL") : theApp.m_strIMEI;
		CString strSIM = theApp.m_strSIM.IsEmpty() ? _T("NULL") : theApp.m_strSIM;
		CString strPhoneType = theApp.m_strPhoneType.IsEmpty() ? _T("NULL") : theApp.m_strPhoneType;

		CString Header = MacAddress + _T(",") + 
						 strDerivation + _T(",") + 
						 strDiskSerial + _T(",") +
						 strMainBoard + _T(",") + 
						 strIMEI + _T(",") + 
						 strSIM + _T(",") +
						 strPhoneType + _T(",") +
						 MobileID + _T(",") +
					     ParamVersion + _T(",") +
						 ApkVersion + _T(",") +
						 Date + _T(":");

		return Header;
	}
	return _T("");
}

//获取日志文件名
CString CLogServer::GetLogFileName(eLogFileType LogFileType)
{
	if(LogFileType == MAIN_LOG_FILE_TYPE)
	{
		CString FileDir=GetLogFileDir();
		vector<CString> TempFileList=GetLogFileNameList(true);
		CString FileName;
		if(TempFileList.empty())
			FileName=theApp.m_strUserMacAddress+GetLocalTime()+_T(".log");
		else
			FileName = TempFileList[0]+_T(".log");

		FileName = FileDir+FileName;
		return FileName;
	}
	return _T("");
}

//遍历日志文件夹
vector<CString> CLogServer::GetLogFileNameList(BOOL IsGetTempLog,eLogFileType LogFileType)
{
	vector<CString> FileNameList;

	CFileFind Find;
	CString DirName=GetLogFileDir();
	DirName+=_T("*.*");
	BOOL IsFinded=Find.FindFile(DirName);
	while(IsFinded) 
	{
		IsFinded=Find.FindNextFile();
		if(!Find.IsDots())
		{
			if(!Find.IsDirectory())
			{
				CString Name = Find.GetFileName();
				if(IsGetTempLog)
				{
					int Pos= Name.Find(_T(".log_tmp"));
					if( -1 != Pos)
					{
						CString FileName;
						FileName = Name.Left(Pos);
						FileNameList.push_back(FileName);
					}
				}
				else
				{
					if( -1==Name.Find(_T(".log_tmp")) && -1 != Name.Find(_T(".log")))
					{
						FileNameList.push_back(Name);
					}
				}
			}
		}
	}

	return  FileNameList;
}

//获取日志文件路径
CString CLogServer::GetLogFileDir(eLogFileType LogFileType)
{
	if(LogFileType == MAIN_LOG_FILE_TYPE)
	{
		CString Dir=::GetAppCurrentPath()+_T("\\Log");
		::CreateDirectory(Dir,NULL);
		Dir=Dir+_T("\\WorkLog");
		::CreateDirectory(Dir,NULL);
		return Dir+_T("\\");
	}
	return _T("");
}


//获取当前时间
CString CLogServer::GetLocalTime()
{
	COleDateTime Time=time(0);
	return Time.Format(_T("%Y%m%d%H%M%S"));
}

//插入数据
void CLogServer::InsertData(CString StrData,eLogFileType LogFileType)
{
	if(LogFileType == MAIN_LOG_FILE_TYPE)
	{
		CString TempLog = GetLogHeader()+StrData+_T("\r\n");
		EnterCriticalSection(&m_CriticalSection);
		m_CaheLog[LogFileType].push_back(TempLog);
		LeaveCriticalSection(&m_CriticalSection);
	}
}