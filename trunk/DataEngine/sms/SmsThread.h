
#pragma once
#include "../common/Include/basethread.h"
#include "../common/Include/CommonFunction.h"
#include "../common/Include/Communication.h"
#include "../common/Include/MessageCenter.h"

/***********************************************************************************
* 说明      ：  短信人处理线程                                                    *
* 创建人    ：  郭庆轩                                                             *
* 创建日期  ：  2012-5-14                                                          *
***********************************************************************************/

class EXPORT_CLASS CSmsThread : public CBaseThread
{
public:

	CSmsThread(void);

	~CSmsThread(void);

	//开启线程
	virtual bool StartThread();

	//联系人处理线程
	static DWORD WINAPI SmsWorkThread(LPVOID lpVoid);

	//添加工作命令
	void AddWorkCmd(sSmsCmd& Cmd);

	//移除工作命令
	void DeleteWorkCmd(sSmsCmd& Cmd);

	//获取命令字符串
	CString GetCmdStr(sSmsCmd& Cmd);

	/*****************************解析短信相应命令返回值*************************************/
	//解析命令返回字符串
	void ParseCmdRetStr(sSmsCmd& Cmd,CString CmdRetStr);

	//请求短信数据
	void ParseSmsRequestCmdRet(CString&   CmdRetStr,sSmsCmd);

	//添加短信
	void ParseSmsAddCmdRet(CString&       CmdRetStr,sSmsCmd);

	//删除短信
	void ParseSmsDeleteCmdRet(CString&    CmdRetStr,sSmsCmd);

	//删除所有短信
	void ParseSmsDeleteAllCmdRet(CString& CmdRetStr,sSmsCmd);

	//编辑短信
	void ParseSmsEditCmdRet(CString&     CmdRetStr,sSmsCmd);

	//备份短信
	void ParseSmsBackupCmdRet(CString&   CmdRetStr,sSmsCmd);

	//发送短信
	void ParseSmsSendCmd(CString&        CmdRetStr,sSmsCmd);

private:

	HANDLE                     m_WorkEvent;       //处理事件
	vector<sSmsCmd>			   m_SmsCmd;          //短信处理命令
	vector<DWORD>              m_ExecCmdIdList;   //短信已处理完的命令ID

};
