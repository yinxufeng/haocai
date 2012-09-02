#pragma once
#include "..\common\include\basethread.h"

/***********************************************************************************
* 说明      ：  连接线程管理                                                       *
* 创建人    ：  谭军红                                                             *
* 创建日期  ：  2012-2-24                                                          *
***********************************************************************************/

class EXPORT_CLASS CConnectThread :public CBaseThread
{
public:

	CConnectThread(void);

	~CConnectThread(void);

	//开启线程
	virtual bool StartThread();
	
	//连接处理线程
	static DWORD WINAPI ConnectWorkThread(LPVOID lpVoid);

	//开始连接
	virtual bool StartConnectPhone(CString PhoneDes);

	//中断连接
	virtual void StopConnectPhone();

	//开启手机服务
	virtual void StartPhoneServer();

	//安装手机服务
	virtual bool InstallPhoneServer();

	//获取手机信息
	virtual bool GetPhoneInfo(sPhoneInfo& Info);

protected:
	
	//获取手机系统信息
	virtual bool GetPhoneSystemInfo(sPhoneInfo& Info);

	//获取手机内存信息
	virtual bool GetPhoneMemInfo(sPhoneInfo& Info);

	//获取手机统计信息
	virtual bool GetPhoneCountInfo(sPhoneInfo& Info);

	//重定向端口
	virtual bool ForwardAdbPort();

private:

	HANDLE    m_StartConnectEvent;         //开始连接事件
	HANDLE    m_StopConnectEvent;          //中断连接事件
	CString   m_PhoneDes;                  //手机唯一描述符
};
