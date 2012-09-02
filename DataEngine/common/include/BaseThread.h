#pragma once
#include "DataDefine.h"
#include "Markup.h"

/***********************************************************************************
* 说明      ：  线程基础类                                                         *
* 创建人    ：  谭军红                                                             *
* 创建日期  ：  2012-2-24                                                          *
***********************************************************************************/

typedef DWORD (*CallBackFunction)(WPARAM wParam,LPARAM lParam);

class EXPORT_CLASS CBaseThread
{
public:
	CBaseThread(void);

	~CBaseThread(void);

	//开启线程
	virtual bool StartThread();

	//终止线程
	virtual bool StopThread();

	//设置回调函数
	virtual void SetCallBackFunction(CallBackFunction CallBack);

protected:

	HANDLE              m_StopEvent;                //线程停止事件
	HANDLE              m_ThreadHandle;             //线程句柄
	CallBackFunction    m_CallBackFuntion;          //回调函数

};
