#pragma once
/***********************************************************************************
* 说明      ：  CLogServer为日志服务，用于处理日志上传和写文件                     *
* 创建人    ：  谭军红                                                             *
* 创建日期  ：  2012-1-10                                                          *
***********************************************************************************/

#include <map>
#include <vector>

using namespace::std;

class CLogServer
{
public:

	//日志文件类型
	enum eLogFileType{ MAIN_LOG_FILE_TYPE, //日志操作文件
                 };


	//开启日志服务
	static void StartLogServer();

	//关闭日志服务
	static void StopLogServer();

	//设置多久上传一次日志
	static void SetUpLogTime(long TimeLog);                     //TimeLog 以秒为单位
	
	//设置多久写日志到文件中
	static void SetWriteLogTime(long TimeLog);                  //TimeLog 以秒为单位

	//设置日志文件大小 
	static void SetLogSize(long LogSize);                       //LogSize 日志文件大小 以M为单位

	//写人操作日志文件
	static void WriteLog(CString LogStr,eLogFileType LogFileType=MAIN_LOG_FILE_TYPE);  //LogStr 日志,LogFileType 日志文件类型，当前只支持操作日志

	//写人操作日志文件
	static void WriteLog(const char* Format,...);

	//写人操作日志文件
	static void WriteLog(const wchar_t* Format,...);

private:
	
	//日志管理线程
	static DWORD WINAPI ManageLogThread(LPVOID lpVoid);

	//日志上传线程
	static DWORD WINAPI UpLogThread(LPVOID lpVoid);

	//获取日志头部
	static CString GetLogHeader(eLogFileType LogFileType=MAIN_LOG_FILE_TYPE);

	//获取日志文件名
	static CString GetLogFileName(eLogFileType LogFileType=MAIN_LOG_FILE_TYPE);
	
	//遍历日志文件夹
	static vector<CString> GetLogFileNameList(BOOL IsGetTempLog=FALSE,eLogFileType LogFileType=MAIN_LOG_FILE_TYPE);

	//获取日志文件路径
	static CString GetLogFileDir(eLogFileType LogFileType=MAIN_LOG_FILE_TYPE);

	//关闭句柄
	static void CloseEventHandle();

	//获取当前时间
	static CString GetLocalTime();

	//插入数据
	static void InsertData(CString StrData,eLogFileType LogFileType=MAIN_LOG_FILE_TYPE);

	CLogServer(void);

	~CLogServer(void);

private:
	static long                                m_UpLogTime;              //日志上传时间间隔
	static long                                m_WriteLogTime;           //日志缓存时间间隔
	static long                                m_LogFileSize;
	static HANDLE                              m_StopEvent;              //管理线程停止事件
	static HANDLE                              m_StopUpEvent;            //日志上传停止事件
	static HANDLE                              m_WriteLogEvent;          //写日志事件
	static HANDLE                              m_UpLogEvent;             //日志上传事件
	static HANDLE                              m_LogThread;              //Log管理线程句柄
	static HANDLE                              m_UpLogThread;            //上传日志线程句柄
	static CRITICAL_SECTION                    m_CriticalSection;        //临界区
	static map<eLogFileType,vector<CString>>   m_CaheLog;                //日志缓存信息

//	static CString m_strDiskSerial; // 硬盘序列号
//	static CString m_strMacAddress; // 网卡地址
//	static CString m_strDerivation; // 应用程序渠道标识
};
