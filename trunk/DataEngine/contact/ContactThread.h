#pragma once
#include "../common/Include/basethread.h"



/***********************************************************************************
* 说明      ：  联系人处理线程                                                     *
* 创建人    ：  谭军红                                                             *
* 创建日期  ：  2012-2-24                                                          *
***********************************************************************************/

class EXPORT_CLASS CContactThread : public CBaseThread
{
public:

	CContactThread(void);

	~CContactThread(void);

	//开启线程
	virtual bool StartThread();
	
	//联系人处理线程
	static DWORD WINAPI ContactWorkThread(LPVOID lpVoid);

	//添加工作命令
	void AddWorkCmd(sContactCmd& Cmd);

	//移除工作命令
	void DeleteWorkCmd(sContactCmd& Cmd);

	//获取命令字符串
	CString GetCmdStr(sContactCmd& Cmd);

	//解析命令返回字符串
	void ParseCmdRetStr(sContactCmd& Cmd,CString CmdRetStr);

	//解析联系人相应命令返回值
	static void ParseContactRequestCmdRet(CString&      CmdRetStr);
	void ParseContactAddCmdRet(sContactCmd&            Cmd,CString&       CmdRetStr);
	void ParseContactDeleteCmdRet(sContactCmd&         Cmd,CString&       CmdRetStr);
	void ParseContactEditCmdRet(sContactCmd&           Cmd,CString&       CmdRetStr);
	void ParseContactBackupCmdRet(sContactCmd&         Cmd,CString&       CmdRetStr);
	void ParseContactGroupRequestCmdRet(sContactCmd&   Cmd,CString&       CmdRetStr);
	void ParseContactGroupAddCmdRet(sContactCmd&       Cmd,CString&       CmdRetStr);
	void ParseContactGroupDeleteCmdRet(sContactCmd&    Cmd,CString&       CmdRetStr);
	void ParseContactGroupEditCmdRet(sContactCmd&      Cmd,CString&       CmdRetStr);


private:

	HANDLE                     m_WorkEvent;       //处理事件
	vector<sContactCmd>        m_ContactCmd;      //联系人处理命令
	vector<DWORD>              m_ExecCmdIdList;   //联系人已处理完的命令ID

};
