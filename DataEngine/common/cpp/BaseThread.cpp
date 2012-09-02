#include "StdAfx.h"
#include "../Include/BaseThread.h"

CBaseThread::CBaseThread(void)
{    
    m_ThreadHandle = INVALID_HANDLE_VALUE;
	m_CallBackFuntion = NULL;

	m_StopEvent = ::CreateEvent(NULL,true,false,NULL);         
}

CBaseThread::~CBaseThread(void)
{
	if(m_StopEvent != INVALID_HANDLE_VALUE)
		CloseHandle(m_StopEvent);
}



	//开启线程
bool CBaseThread::StartThread()
{
	StopThread();
	return true;
}

//终止线程
bool CBaseThread::StopThread()
{
	if(m_StopEvent != INVALID_HANDLE_VALUE)
	{
		::SetEvent(m_StopEvent);
	}

	if(m_ThreadHandle != INVALID_HANDLE_VALUE)
	{
		::WaitForSingleObject(m_ThreadHandle,INFINITE);
		CloseHandle(m_ThreadHandle);
	}

	if(m_StopEvent != INVALID_HANDLE_VALUE)
		ResetEvent(m_StopEvent);

	return true;
}


//设置回调函数
void CBaseThread::SetCallBackFunction(CallBackFunction CallBack)
{
	if(CallBack != NULL)
		m_CallBackFuntion = CallBack;
}