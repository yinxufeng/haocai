#include "StdAfx.h"
#include "SmsThread.h"


CSmsThread::CSmsThread(void)
{
	m_WorkEvent = ::CreateEvent(NULL,true,false,NULL);
}

CSmsThread::~CSmsThread(void)
{
	if(m_WorkEvent != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_WorkEvent);
	}
}


//开启线程
bool CSmsThread::StartThread()
{
	CBaseThread::StartThread();

	m_ThreadHandle = ::CreateThread(NULL,0,SmsWorkThread,this,0,NULL);
	if(m_ThreadHandle != INVALID_HANDLE_VALUE)
		return true;

	return false;
}

//短信处理线程
DWORD CSmsThread::SmsWorkThread(LPVOID lpVoid)
{
	CSmsThread* Self=(CSmsThread*)lpVoid;
	HANDLE EventArray[2]={Self->m_WorkEvent,Self->m_StopEvent};
	while(true)
	{
		DWORD Ret=::WaitForMultipleObjects(2,EventArray,false,INFINITE);
		if(Ret != 0)
			break;

		::ResetEvent(Self->m_WorkEvent);
		sSmsCmd Cmd;
		vector<sSmsCmd>::iterator it = Self->m_SmsCmd.begin();
		if(it == Self->m_SmsCmd.end())
			continue;

		Cmd=*it;
		Self->m_SmsCmd.erase(it);
		CString CmdStr=Self->GetCmdStr(Cmd);
		CString CmdRetStr;
		CCommunication::SendXmlToPhone(CmdStr,CmdRetStr);
		Self->ParseCmdRetStr(Cmd,CmdRetStr);
	}
	return 0;
}


//添加工作命令
void CSmsThread::AddWorkCmd(sSmsCmd& Cmd)
{
	XWriteEventLog(_T("[CSmsThread::AddWorkCmd] CmdType=%d CmdId=%d"),Cmd.m_CmdType,Cmd.m_CmdId);

	m_SmsCmd.push_back(Cmd);
	SetEvent(m_WorkEvent);
}

//移除工作命令
void CSmsThread::DeleteWorkCmd(sSmsCmd& Cmd)
{
	XWriteEventLog(_T("[CSmsThread::DeleteWorkCmd] CmdType=%d CmdId=%d"),Cmd.m_CmdType,Cmd.m_CmdId);
	vector<sSmsCmd>::iterator it= m_SmsCmd.begin();
	for(;it != m_SmsCmd.end(); it++)
	{
		if(it->m_CmdId == Cmd.m_CmdId && it->m_CmdType == Cmd.m_CmdType)
		{
			switch(Cmd.m_CmdType)
			{
				
			case SMS_REQUEST_CMD:
				break;
			case SMS_ADD_CMD:
			case SMS_EDIT_CMD:
				{
					vector<sSmsInfo>* pVector = (vector<sSmsInfo>*)Cmd.m_CmdParam;
					if(pVector != NULL)
					{
						pVector->clear();
						delete pVector;
					}
				}
				break;
			case SMS_DELTE_CMD:
			
			case SMS_BACKUP_CMD:
				break;

			}
			it=m_SmsCmd.erase(it);
		}
	}
}

//获取命令字符串
CString CSmsThread::GetCmdStr(sSmsCmd& Cmd)
{
	XWriteEventLog(_T("[CSmsThread::GetCmdStr] CmdType=%d CmdId=%d"),Cmd.m_CmdType,Cmd.m_CmdId);

	CString CmdStr;
	switch(Cmd.m_CmdType)
	{
	case SMS_REQUEST_CMD:
		{
			CmdStr = L"<?xml version='1.0'?>"
				L"<req>"
				L"<fun>GetSms</fun>"
				L"<ps count='2'>"
				L"<p>"
				L"<name>id</name>"
				L"<value>all</value>"
				L"</p>"
				L"<p>"
				L"<name>type</name>"
				L"<value>normal</value>"
				L"</p>"									
				L"</ps>\n"
				L"</req>\n";
		}
		break;

	case SMS_DELTE_CMD:
		{
			CString strType = L"sendbox";
			CString *strID = (CString*)Cmd.m_CmdParam;
			CmdStr.Format(L"<?xml version='1.0'?>"
				L"<req>"
				L"<fun>DelSms</fun>"
				L"<ps count='2'>"
				L"<p>"
				L"<name>smsbox</name>"
				L"<value>%s</value>"
				L"</p>"
				L"<name>id</name>"
				L"<value>%s</value>"
				L"</ps>\n"
				L"</req>\n", strType, strID);
		}
		break;

	case SMS_SEND_CMD:
		{
			vector<CString> tempPhone = (vector<CString>)Cmd.m_CmdParam;
			CString pchPhoneNumber = tempPhone[0];
			CString pchSmsBody = tempPhone[1];
			CmdStr.Format(L"<?xml version='1.0'?>"
				L"<req>"
				L"<fun>SendSms</fun>"
				L"<ps count='2'>"
				L"<p>"
				L"<name>phoneNum</name>"
				L"<value>%s</value>"
				L"</p>"
				L"<p>"
				L"<name>text</name>"
				L"<value>%s</value>"
				L"</p>"
				L"</ps>\n"
				L"</req>\n", pchPhoneNumber, pchSmsBody);
		}
		break;
	case SMS_ADD_CMD:
		{
			sSmsInfo *tempSmsInfo = (sSmsInfo*)Cmd.m_CmdParam;
			CString BoxStr;
			BoxStr.Format(L"%d",tempSmsInfo->m_SmsBox);
			int State=(int)tempSmsInfo->m_SmsStaus;
	
			CString strID = tempSmsInfo->m_SmsID;
			CString StrValue;
			CString TempData;
			TempData.Format(_T("add:%s\ndata:%s\n"),tempSmsInfo->m_SmsCaller,tempSmsInfo->m_SmsBody);
			StrValue.Format(_T("date:%s\nstate:%d\ntype:%d\n"),tempSmsInfo->m_TimeStamp,State,tempSmsInfo->m_SmsBox);
			StrValue=TempData+StrValue;
			CmdStr.Format(L"<?xml version='1.0'?>"
				L"<req>"									
				L"<fun>RestoreSms</fun>"					
				L"<ps count='2'>"						
				L"<p>"									
				L"<name>smsbox</name>"					
				L"<value>%s</value>"					
				L"</p>"									
				L"<p>"									
				L"<name>%s</name>"						
				L"<value>%s</value>"						
				L"</p>"									
				L"</ps>\n"								
				L"</req>\n",BoxStr,strID,StrValue);
		}
		break;
	case SMS_DELTE_ALL_CMD:
		{
			CmdStr.Format(L"<?xml version='1.0'?>"
				L"<req>"
				L"<fun>DelSms</fun>"
				L"<ps count='2'>"
				// 		"<p>"
				// 		"<name>smsbox</name>"
				// 		"<value>%s</value>"
				// 		"</p>"
				L"<p>"
				L"<name>id</name>"
				L"<value>all</value>"
				L"</p>"
				L"</ps>\n"
				L"</req>\n");
		}
		break;
	case SMS_EDIT_CMD:
		{
		}
		break;
	case SMS_BACKUP_CMD:
		{
		}
		break;
	}

	return CmdStr;
}

//解析命令返回字符串
void CSmsThread::ParseCmdRetStr(sSmsCmd& Cmd,CString CmdRetStr)
{
	switch(Cmd.m_CmdType)
	{
	case SMS_SEND_CMD:
		{
			ParseSmsSendCmd(CmdRetStr,Cmd);
		}
		break;
	case SMS_DELTE_ALL_CMD:
		{
			ParseSmsDeleteAllCmdRet(CmdRetStr,Cmd);
		}
		break;
	case SMS_REQUEST_CMD:
		{
			ParseSmsRequestCmdRet(CmdRetStr,Cmd);
		}
		break;
	case SMS_ADD_CMD:
		{
			ParseSmsAddCmdRet(CmdRetStr,Cmd);
		}
		break;

	case SMS_DELTE_CMD:
		{
			ParseSmsDeleteCmdRet(CmdRetStr,Cmd);
		}
		break;
	case SMS_EDIT_CMD:
		{
			ParseSmsEditCmdRet(CmdRetStr,Cmd);
		}
		break;
	case SMS_BACKUP_CMD:
		{
			ParseSmsBackupCmdRet(CmdRetStr,Cmd);
		}
		break;
	}
}

//解析短信相应命令返回值  请求数据
void CSmsThread::ParseSmsRequestCmdRet(CString&  CmdRetStr,sSmsCmd cmd)
{
	CMarkup xml;
	if (xml.SetDoc(CmdRetStr) )
	{			
		CString strData;
		xml.ResetMainPos();
		xml.FindChildElem(L"ps");
		if (xml.IntoElem())
		{
			CString strAdd;
			CString strData;
			CString strRead;
			CString strDate;
			CString strXmlName;

		
			int iTick = 0;
			vector<sSmsInfo> vctSmsInfo;
			while ( xml.FindChildElem(L"p") )
			{
				sSmsInfo SmsInfo;
				CString strMsg;
				xml.IntoElem();
				xml.FindChildElem(L"name");
				strXmlName = xml.GetChildData().c_str();
				CString StrID = strXmlName;
				if (strXmlName == L"msg")
				{
					xml.FindChildElem(L"value");							
					strMsg = xml.GetChildData().c_str();

					if (strMsg != L"0")
					{
						return ;
					}
				}
				else if(strXmlName ==L"flag")
				{
					xml.FindChildElem(L"value");							
					strMsg = xml.GetChildData().c_str();
					if(strMsg == L"end")
						return;
				}
				else
				{
					//处理短信内容
					xml.FindChildElem(L"value");
					xml.IntoElem();
					if (xml.FindChildElem(L"state"))
					{
						//短信状态
						xml.FindChildElem(L"state");
						strRead = xml.GetChildData().c_str();
						if (strRead == L"1")
							SmsInfo.m_SmsStaus = SMS_IS_READ;
						else
							SmsInfo.m_SmsStaus = SMS_NOT_READ;
						//短信内容
						xml.FindChildElem(L"data");
						strData = xml.GetChildData().c_str();
						if(strData == L"")	
							SmsInfo.m_SmsBody = L"无";
						else
							SmsInfo.m_SmsBody = xml.GetChildData().c_str();
						//短信所属信息类型
						xml.FindChildElem(L"type");
						strRead = xml.GetChildData().c_str();
						if (strRead == L"1")	//收件
						{
							SmsInfo.m_SmsBox = SMSBOX_INBOX;
						}
						else if (strRead == L"2")	//发件
						{
							SmsInfo.m_SmsBox = SMSBOX_SENTBOX;
						}
						else
						{
							xml.OutOfElem();
							xml.OutOfElem();
							continue;
						}
						//短信时间
						xml.FindChildElem(L"date");
						SmsInfo.m_TimeStamp = xml.GetChildData().c_str();
						//短信地址
						xml.FindChildElem(_T("add"));
						strAdd = xml.GetChildData().c_str();
						if(strAdd == _T(""))
						{
							SmsInfo.m_SmsCaller =_T("");
							SmsInfo.m_ContactName = _T("");
						}

					xml.OutOfElem();
					}
				xml.OutOfElem();
				}
			vctSmsInfo.push_back(SmsInfo);
			}
			CMessageCenter::SendMsg(MSG_SMS_INFO_TO_DATA_ENGINE,SMS_REQUEST_CMD,(WPARAM)&vctSmsInfo);
		}
	}
}

void CSmsThread::ParseSmsAddCmdRet(CString&      CmdRetStr,sSmsCmd cmd)
{
}

//删除短信
void CSmsThread::ParseSmsDeleteCmdRet(CString&   CmdRetStr,sSmsCmd cmd)  
{
	//分析删除短信返回的XML数据    成功返回0，失败返回-1
	if (CmdRetStr != L"")
	{
		CMarkup xml;
		if (xml.SetDoc(CmdRetStr) )
		{			
			CString strData;
			xml.ResetMainPos();
			xml.FindChildElem(L"ps");
			if (xml.IntoElem())
			{
				int iTick = 0;
				while ( xml.FindChildElem(L"p") )
				{
					CString strMsg;
					xml.IntoElem();
					xml.FindChildElem(L"name");
					strData = xml.GetChildData().c_str();
					strData.MakeLower();
					if (strData == L"msg")
					{
						xml.FindChildElem(L"value");							
						strMsg = xml.GetChildData().c_str();
						if (strMsg != L"0")
						{
							cmd.m_CmdParam = -1;
						}
					}
					else
					{
						cmd.m_CmdParam = -1;
					}
					xml.OutOfElem();
				}
			}
		}
	}
	CMessageCenter::SendMsg(MSG_SMS_INFO_TO_DATA_ENGINE,SMS_DELTE_CMD,(WPARAM)cmd.m_CmdParam);
}

void CSmsThread::ParseSmsEditCmdRet(CString&     CmdRetStr,sSmsCmd cmd)
{
}
void CSmsThread::ParseSmsBackupCmdRet(CString&   CmdRetStr,sSmsCmd cmd)
{
}

//删除所有短信
void CSmsThread::ParseSmsDeleteAllCmdRet(CString &CmdRetStr,sSmsCmd cmd)
{
	if(CmdRetStr.Find(L"<value>0</value>") == -1)
		cmd.m_CmdParam = -1;//手机返回信息失败
	else
		cmd.m_CmdParam = 0;

		CMessageCenter::SendMsg(MSG_SMS_INFO_TO_DATA_ENGINE,SMS_DELTE_ALL_CMD,(WPARAM)cmd.m_CmdParam);
}

//发送短信
void CSmsThread::ParseSmsSendCmd(CString& CmdRetStr,sSmsCmd cmd)
{
	bool regFlag; //发送后返回是否成功
	sSmsInfo* pOneSms = new sSmsInfo();
// 	strcpy(pOneSms->szSmsCallerID, pchPhoneNumber);
// 	strcpy(pOneSms->szSmsBody, pchSmsBody);	
// 	strcpy(pOneSms->szSmsStatus, "已读");
// 	pOneSms->wBoxNumber = 2; // 发件箱

	//处理返回值
	//分析返回的XML数据
	if (CmdRetStr != L"")
	{		
		CMarkup xml;
		if (xml.SetDoc(CmdRetStr) )
		{			
			CString strData;
			xml.ResetMainPos();
			xml.FindChildElem(L"ps");
			if (xml.IntoElem())
			{
				int iTick = 0;
				while ( xml.FindChildElem(L"p") )
				{
					CString strMsg;
					xml.IntoElem();
					xml.FindChildElem(L"name");
					strData = xml.GetChildData().c_str();
					strData.MakeLower();
					if (strData == L"msg")
					{
						xml.FindChildElem(L"value");							
						strMsg = xml.GetChildData().c_str();
						if (strMsg != L"0")
						{
							delete pOneSms;
							pOneSms = NULL;
							return;
						}
					}
					else
					{						
						pOneSms->m_SmsID = (char*)(LPCTSTR)strData;
						xml.FindChildElem(L"value");
						xml.IntoElem();
						//短信发送结果
						xml.FindChildElem(L"result");	//返回结果 2 成功 5 失败
						strData = xml.GetChildData().c_str();
						int nResult = _wtoi(strData);
						//pOneSms->bSuccess = (nResult == 2) ? true : false;
					    regFlag = (nResult == 2) ? true : false;  //发送短信后，返回成功或失败
						//时间
						xml.FindChildElem(L"time");
						strData = xml.GetChildData().c_str();						
						pOneSms->m_TimeStamp = strData;					
					}
					xml.OutOfElem();					
				}
			}
		}
	}
	else
		regFlag = false;
	CMessageCenter::SendMsg(MSG_SMS_INFO_TO_DATA_ENGINE,SMS_SEND_CMD,(WPARAM)pOneSms);
}