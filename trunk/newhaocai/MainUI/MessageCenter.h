/***********************************************************************************
* 说明      ：  CMessageCenter为消息处理中心，采用观察者模式                       *
* 创建人    ：  谭军红                                                             *
* 创建日期  ：  2011-9-8                                                           *
***********************************************************************************/

#pragma once
#include "memorypool.h"
#include "messageDefine.h"

const	int		WM_SUB_THREAD_MSG	=	WM_USER+100;	//子线程消息(通过PostMsg发送的消息)
const	int		WM_SUB_THREAD_DATA	=	WM_USER+101;	//子线程数据(通过PostData发送的消息)

#define EXPORT_CLASS __declspec(dllexport)


//消息处理接口
interface EXPORT_CLASS IMessageHandle
{
	virtual void OnMessage(eMessage Message,DWORD SystemMsg=0,WPARAM wParam=0,LPARAM lParam=0)=0;
};

//消息中心
class EXPORT_CLASS CMessageCenter
{
public:

	static void Init();

	static void Delete();

	//注册消息处理句柄
	static void RegisterMsgHandle(IMessageHandle* Handle,eMessage Message);

	//注销消息处理句柄
	static void LogoutMsgHandle(IMessageHandle* Handle,eMessage Message);

	//转发系统消息(如果没有消息接收者，返回FALSE，否则返回TRUE)
	static BOOL SendSystemMsg(DWORD Message,WPARAM wParam,LPARAM lParam);

	//发送消息(如果没有消息接收者，返回FALSE，否则返回TRUE，主线程内使用)
	static BOOL SendMsg(eMessage Message,WPARAM wParam=0,LPARAM lParam=0);

	//发送数据(如果没有消息接收者，返回FALSE，否则返回TRUE，主线程内使用)
	static BOOL SendData(eMessage Message,sMemory* Param,BOOL Racord=FALSE);
	
	//投递消息(子线程内使用)
	static void PostMsg(eMessage Message,WPARAM Param=0);

	//投递数据(子线程内使用)
	static void PostData(eMessage Message,sMemory* Param);

private:

	//消息窗口的过程
	static LRESULT WINAPI MsgWinProc(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);

	//记录指针
	static void RecordMsg(sMemory* Param);

	//删除记录
	static void DeleteRecord(sMemory* Param);

	//消息处理句柄结构
	struct sMessageItem
	{
		int					m_HandleCount;	//句柄数
		IMessageHandle**	m_HandleList;	//句柄指针列表
	};

	//消息记录结构
	struct sMsgRecord
	{
		sMemory*	m_Param;
		sMsgRecord*	m_Next;
	};

	static sMsgRecord*			m_RecordHead;	//记录头
	static sMsgRecord*			m_RecordEnd;	//记录尾
	static sMsgRecord*			m_FreeHead;		//空闲头
	static CRITICAL_SECTION		m_RecordLock;	//记录锁

	static	sMessageItem		m_MessageList[MRSSAGE_TYPE_COUNT];	//消息列表
	static	HWND				m_MsgWnd;		//用于接收子线程消息的窗口
};
