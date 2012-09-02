#pragma once

#include "BaseThread.h"

/*****************************************************************
* 说明        :  短信处理线程                                   *
* 创建人      :  郭庆轩                                         *
* 创建日期    :  2012/5/9                                       *
*****************************************************************/


class CSmsThread :	public CBaseThread
{
public:

	CSmsThread(void);

	~CSmsThread(void);
	
	//线程操作
	//开启线程
	virtual BOOL StartThread();

	//短信处理线程
	static DWORD WINAPI SmsWorkThread(LPVOID lpVoid);

	//命令处理
	//添加工作命令
	void AddWorkCmd(sSmsCmd& Cmd);

	//移除工作命令
	void DeleteWorkCmd(sSmsCmd& Cmd);

	//获取命令字符串
	CString GetCmdStr(sSmsCmd& Cmd);

	//解析命令返回字符串
	void ParseCmdRetStr(sSmsCmd& Cmd,CString CmdRetStr);

private:

	HANDLE                     m_WorkEvent;       //处理事件
	vector<sSmsCmd>        m_SmsCmd;      //短信处理命令

};
