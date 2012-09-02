#include "StdAfx.h"
#include "ContactThread.h"
#include "ContactTransUntil.h"
#include "../common/Include/CommonFunction.h"
#include "../common/Include/Communication.h"
#include "../common/Include/MessageCenter.h"


CContactThread::CContactThread(void)
{
	m_WorkEvent = ::CreateEvent(NULL,true,false,NULL);
}

CContactThread::~CContactThread(void)
{
	if(m_WorkEvent != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_WorkEvent);
	}
}


//开启线程
bool CContactThread::StartThread()
{
	CBaseThread::StartThread();

	m_ThreadHandle = ::CreateThread(NULL,0,ContactWorkThread,this,0,NULL);
	if(m_ThreadHandle != INVALID_HANDLE_VALUE)
		return true;

	return false;
}

//联系人处理线程
DWORD CContactThread::ContactWorkThread(LPVOID lpVoid)
{
	CContactThread* Self=(CContactThread*)lpVoid;
	HANDLE EventArray[2]={Self->m_WorkEvent,Self->m_StopEvent};
	while(true)
	{
		DWORD Ret=::WaitForMultipleObjects(2,EventArray,false,INFINITE);
		if(Ret != 0)
			break;

		::ResetEvent(Self->m_WorkEvent);
		sContactCmd Cmd;
		vector<sContactCmd>::iterator it = Self->m_ContactCmd.begin();
		if(it == Self->m_ContactCmd.end())
			continue;
		
		Cmd=*it;
		Self->m_ContactCmd.erase(it);
		CString CmdStr=Self->GetCmdStr(Cmd);
		CString CmdRetStr;
		if(Cmd.m_CmdType == CONTACT_REQUEST_CMD)
			CCommunication::SendXmlToPhone(CmdStr,CmdRetStr,ParseContactRequestCmdRet);
		else
		{
			CCommunication::SendXmlToPhone(CmdStr,CmdRetStr);
			Self->ParseCmdRetStr(Cmd,CmdRetStr);
		}
	
	;
	}

	return 0;
}


//添加工作命令
void CContactThread::AddWorkCmd(sContactCmd& Cmd)
{
	XWriteEventLog(_T("[CContactThread::AddWorkCmd] CmdType=%d CmdId=%d"),Cmd.m_CmdType,Cmd.m_CmdId);

	m_ContactCmd.push_back(Cmd);
	SetEvent(m_WorkEvent);
}

//移除工作命令
void CContactThread::DeleteWorkCmd(sContactCmd& Cmd)
{
	XWriteEventLog(_T("[CContactThread::DeleteWorkCmd] CmdType=%d CmdId=%d"),Cmd.m_CmdType,Cmd.m_CmdId);

	vector<sContactCmd>::iterator it= m_ContactCmd.begin();
	for(;it != m_ContactCmd.end(); it++)
	{
		if(it->m_CmdId == Cmd.m_CmdId && it->m_CmdType == Cmd.m_CmdType)
		{
			switch(Cmd.m_CmdType)
			{

			case CONTACT_REQUEST_CMD:
				break;
			case CONTACT_ADD_CMD:
			case CONTACT_EDIT_CMD:
				{
					vector<sContactInfo>* pVector = (vector<sContactInfo>*)Cmd.m_CmdParam;
					if(pVector != NULL)
					{
						pVector->clear();
						delete pVector;
					}
				}
				break;
			case CONTACT_DELTE_CMD:
			case CONTACTGROUP_DELETE_CMD:
				{
					vector<CString>* pVector = (vector<CString>*)Cmd.m_CmdParam;
					if(pVector != NULL)
					{
						pVector->clear();
						delete pVector;
					}
				}
				break;
			case CONTACT_BACKUP_CMD:
				break;

			case CONTACTGROUP_ADD_CMD:
			case CONTACTGROUP_EDIT_CMD:
				{
					vector<sGroupInfo>* pVector=(vector<sGroupInfo>*)Cmd.m_CmdParam;
					if(pVector != NULL)
					{
						pVector->clear();
						delete pVector;
					}
					
				}
				break;
			}
			it=m_ContactCmd.erase(it);
		}
	}
}

//获取命令字符串
CString CContactThread::GetCmdStr(sContactCmd& Cmd)
{
	XWriteEventLog(_T("[CContactThread::GetCmdStr] CmdType=%d CmdId=%d"),Cmd.m_CmdType,Cmd.m_CmdId);

	CString CmdStr;

	switch(Cmd.m_CmdType)
	{
	case CONTACT_REQUEST_CMD:
		{
			CmdStr =_T("<?xml version=\"1.0\"?>")
					_T("<req>")
					_T("<cmd>1</cmd>")
					_T("<fun>GetContactListBatch</fun>")
					_T("<ps count='1'>")
					_T("<p>")
					_T("<name>position</name>")
					_T("<value>all</value>")
					_T("</p>")
					_T("</ps>\n")
					_T("</req>\n");

		}
		break;
	case CONTACT_ADD_CMD:
		{
			CString Head;
			CString End=_T("</ps>\n</req>\n");
			CString Mid;
			vector<sContactInfo>* pVector= (vector<sContactInfo>*)Cmd.m_CmdParam;
			if(pVector && pVector->size() > 1)
			{
				Head = _T("<?xml version='1.0'?><req><fun>RestoreContactInfo</fun><ps count='2'>");
				for(int Index = 0; Index < (int)pVector->size(); Index++)
				{
					CString Temp;
					::TransContactInfoToVard211((*pVector)[Index],Temp);
					Temp.Format(_T("<p><name>%d</name><value>%s</value></p>"),(*pVector)[Index].m_ID,Temp);
					Mid+=Temp;
				}

				CmdStr=Head+Mid+End;
			}
			else
			{
				if(pVector && pVector->size() == 1)
				{
					Head = _T("<?xml version='1.0'?><req><fun>AddContactInfo</fun><ps count='2'>");
					CString Temp;
					::TransContactInfoToVard211((*pVector)[0],Temp);
					CString Path=_T("phone");
					if((*pVector)[0].m_PathType == PATH_SDCARD)
					{
						Path = _T("sdcard");
					}
					Mid.Format(_T("<p><name>Position</name><value>%s</value></p><p><name>csdata</name><value>%s</value></p>"),Path,Temp);
					CmdStr=Head+Mid+End;
				}
			}
		
		}
		break;

	case CONTACT_DELTE_CMD:
		{
			vector<CString>* pVector= (vector<CString>*)Cmd.m_CmdParam;
			if(pVector && pVector->size() > 0)
			{
				CString Head=_T("<?xml version='1.0'?><req><fun>DelContactInfo</fun><ps count='2'>");
				CString End=_T("</ps>\n</req>\n");
				CString Mid;
				CString MidTemp;
				for(int Index = 0; Index < pVector->size(); Index++)
				{
					CString Temp;
					Temp.Format(_T("%s"),(*pVector)[Index]);
					MidTemp+=Temp;
					if(Index < pVector->size()-1)
						MidTemp+=_T(";");
				}
				Mid.Format(_T("<p><name>id</name><value>%s</value></p><p><name>Position</name><value>phone</value></p>"),MidTemp);
				CmdStr=Head+Mid+End;
				return CmdStr;
			}
		}
		break;

	case CONTACT_EDIT_CMD:
		{
			vector<sContactInfo>* pVector= (vector<sContactInfo>*)Cmd.m_CmdParam;
			if(pVector && pVector->size() == 1)
			{
				CString Path=_T("phone");
				if((*pVector)[0].m_PathType == PATH_SDCARD)
				{
					Path = _T("sdcard");
				}

				CString Temp;
				::TransContactInfoToVard211((*pVector)[0],Temp);
				CmdStr=_T("<?xml version='1.0'?><req><fun>ModifyContactInfo</fun><ps count='3'>");
				CString MidTemp;
				MidTemp.Format(_T("<p><name>id</name><value>%s</value></p><p><name>csdata</name><value>%s</value></p><p><name>Position</name><value>%s</value></p>"),(*pVector)[0].m_ID,Temp,Path);
				CmdStr+=MidTemp+_T("</ps>\n</req>\n");				
			}
		}
		break;
	case CONTACT_BACKUP_CMD:
		break;

	case CONTACTGROUP_REQUEST_CMD:
		{
			CmdStr  = _T("<?xml version='1.0'?>");
			CmdStr += _T("<req>");
			CmdStr += _T("<fun>GetContactsGroup</fun>");
			CmdStr += _T("<ps count='0'>");
			CmdStr += _T("</ps>\n");
			CmdStr += _T("</req>\n");
		}
		break;
	case CONTACTGROUP_ADD_CMD:
		{
			vector<sGroupInfo>* pVector= (vector<sGroupInfo>*)Cmd.m_CmdParam;
			if(pVector && pVector->size() == 1)
			{
				CmdStr  = _T("<?xml version='1.0'?>");
				CmdStr += _T("<req>");
				CmdStr += _T("<fun>ContactsGroup</fun>");
				CmdStr += _T("<ps count='2'>");

				CmdStr += _T("<p>");
				CmdStr += _T("<name>id</name>");
				CmdStr += _T("<value>0</value>");
				CmdStr += _T("</p>");

				CmdStr += _T("<p>");
				CmdStr += _T("<name>type</name>");
				CmdStr += _T("<value>add</value>");
				CmdStr += _T("</p>");

				CmdStr += _T("<p>");
				CmdStr += _T("<name>content</name>");
				CmdStr += _T("<value>") + (*pVector)[0].m_GroupName + _T("</value>");
				CmdStr += _T("</p>");
				CmdStr += _T("</ps>\n");
				CmdStr += _T("</req>\n");
			}
		}
		break;
	case CONTACTGROUP_DELETE_CMD:
		{
			vector<sGroupInfo>* pVector= (vector<sGroupInfo>*)Cmd.m_CmdParam;
			if(pVector && pVector->size() == 1)
			{
				CmdStr  = _T("<?xml version='1.0'?>");
				CmdStr += _T("<req>");
				CmdStr += _T("<fun>ContactsGroup</fun>");
				CmdStr += _T("<ps count='2'>");

				CmdStr += _T("<p>");
				CmdStr += _T("<name>id</name>");
				CmdStr += _T("<value>")+(*pVector)[0].m_GroupID+_T("</value>");
				CmdStr += _T("</p>");

				CmdStr += _T("<p>");
				CmdStr += _T("<name>type</name>");
				CmdStr += _T("<value>delete</value>");
				CmdStr += _T("</p>");

				CmdStr += _T("<p>");
				CmdStr += _T("<name>content</name>");
				CmdStr += _T("<value>") + (*pVector)[0].m_GroupName + _T("</value>");
				CmdStr += _T("</p>");
				CmdStr += _T("</ps>\n");
				CmdStr += _T("</req>\n");
			}
		}
		break;
	case CONTACTGROUP_EDIT_CMD:
		{
			vector<sGroupInfo>* pVector= (vector<sGroupInfo>*)Cmd.m_CmdParam;
			if(pVector && pVector->size() == 1)
			{
				CmdStr  = _T("<?xml version='1.0'?>");
				CmdStr += _T("<req>");
				CmdStr += _T("<fun>ContactsGroup</fun>");
				CmdStr += _T("<ps count='2'>");

				CmdStr += _T("<p>");
				CmdStr += _T("<name>id</name>");
				CmdStr += _T("<value>")+(*pVector)[0].m_GroupID+_T("</value>");
				CmdStr += _T("</p>");

				CmdStr += _T("<p>");
				CmdStr += _T("<name>type</name>");
				CmdStr += _T("<value>change</value>");
				CmdStr += _T("</p>");

				CmdStr += _T("<p>");
				CmdStr += _T("<name>content</name>");
				CmdStr += _T("<value>") + (*pVector)[0].m_GroupName + _T("</value>");
				CmdStr += _T("</p>");
				CmdStr += _T("</ps>\n");
				CmdStr += _T("</req>\n");
			}
		}
		break;
	}

	return CmdStr;
}

//解析命令返回字符串
void CContactThread::ParseCmdRetStr(sContactCmd& Cmd,CString CmdRetStr)
{
	switch(Cmd.m_CmdType)
	{
	case CONTACT_REQUEST_CMD:
		{
			ParseContactRequestCmdRet(CmdRetStr);
		}
		break;
	case CONTACT_ADD_CMD:
		{
			ParseContactAddCmdRet(Cmd,CmdRetStr);
		}
		break;

	case CONTACT_DELTE_CMD:
		{
			ParseContactDeleteCmdRet(Cmd,CmdRetStr);
		}
		break;
	case CONTACT_EDIT_CMD:
		{
			ParseContactEditCmdRet(Cmd,CmdRetStr);
		}
		break;
	case CONTACT_BACKUP_CMD:
		{
			ParseContactBackupCmdRet(Cmd,CmdRetStr);
		}
		break;
	case CONTACTGROUP_REQUEST_CMD:
		{
			ParseContactGroupRequestCmdRet(Cmd,CmdRetStr);
		}
		break;
	case CONTACTGROUP_ADD_CMD:
		{
			ParseContactGroupAddCmdRet(Cmd,CmdRetStr);
		}
		break;
	case CONTACTGROUP_DELETE_CMD:
		{
			ParseContactGroupDeleteCmdRet(Cmd,CmdRetStr);
		}
		break;
	case CONTACTGROUP_EDIT_CMD:
		{
			ParseContactGroupEditCmdRet(Cmd,CmdRetStr);
		}
		break;
	}
}

//解析联系人相应命令返回值
void CContactThread::ParseContactRequestCmdRet(CString&  CmdRetStr)
{
	if(CmdRetStr.IsEmpty())
	{
		CMessageCenter::SendMsg(MSG_CONTACT_INFO_TO_DATA_ENGINE,CONTACT_REQUEST_CMD,NULL);
		return;
	}

	CMarkup Xml;
	bool IsOk=Xml.SetDoc(CmdRetStr.GetBuffer());
	CmdRetStr.ReleaseBuffer();

	vector<sContactInfo> ContactList;

	if(IsOk)
	{
		if(Xml.FindChildElem(_T("ps")))
		{
			Xml.IntoElem();
			while(Xml.FindChildElem(_T("p")))
			{
				Xml.IntoElem();
				Xml.FindChildElem(_T("name"));
				CString StrData=Xml.GetChildData().c_str();
				CString StrMsg;
				if(StrData ==_T("msg"))
				{
					Xml.FindChildElem(_T("value"));							
					StrMsg = Xml.GetChildData().c_str();
					if (StrMsg != "0")
					{
						return ;
					}
				}
				else if (StrData == _T("error"))
				{
					Xml.FindChildElem(_T("value"));							
					StrMsg = Xml.GetChildData().c_str();
					return ;
				}
				else
				{
					sContactInfo Info;
					Info.m_ID = StrData;
					Xml.FindChildElem(_T("value"));		
					CString StrVcard = Xml.GetChildData().c_str();
					
					if (StrVcard != "")
					{
						if( TRANS_OK  == ::TransVcard211ToContactInfo(StrVcard,Info))
						{
							ContactList.push_back(Info);
						}
					}
				
				}
				Xml.OutOfElem();	
			}
			
		}
	}

	if(!ContactList.empty())
		CMessageCenter::SendMsg(MSG_CONTACT_INFO_TO_DATA_ENGINE,CONTACT_REQUEST_CMD,(WPARAM)&ContactList);
	else
		CMessageCenter::SendMsg(MSG_CONTACT_INFO_TO_DATA_ENGINE,CONTACT_REQUEST_CMD,(WPARAM)NULL);
}

void CContactThread::ParseContactAddCmdRet(sContactCmd& Cmd, CString&      CmdRetStr)
{
	BOOL IsAddOK=false;
	if(!CmdRetStr.IsEmpty())
	{
		CMarkup Xml;
		if(Xml.SetDoc(CmdRetStr))
		{
			Xml.FindChildElem(_T("ps"));
			if(Xml.IntoElem())
			{
				while ( Xml.FindChildElem(_T("p")) )
				{
					Xml.IntoElem();
					Xml.FindChildElem(_T("name"));
					CString StrData = Xml.GetChildData().c_str();
					if (StrData == _T("msg"))
					{
						Xml.FindChildElem(_T("value"));						
						CString StrMsg = Xml.GetChildData().c_str();
						if (StrMsg == _T("0"))
						{
							IsAddOK=true;
							break;
						}
						else
							break;
					}
					else
					{
						Xml.FindChildElem(_T("value"));							
						CString StrMsg = Xml.GetChildData().c_str();
						vector<sContactInfo>* pVector = (vector<sContactInfo>*)Cmd.m_CmdParam;
						if(pVector != NULL && pVector->size() == 1)
							(*pVector)[0].m_ID = StrMsg;

					}
					Xml.OutOfElem();
				}
			}
		}
	}
	
	if(IsAddOK)
		CMessageCenter::SendMsg(MSG_CONTACT_INFO_TO_DATA_ENGINE,CONTACT_ADD_CMD,(LPARAM)Cmd.m_CmdParam);
	else
		CMessageCenter::SendMsg(MSG_CONTACT_INFO_TO_DATA_ENGINE,CONTACT_ADD_CMD,NULL);

}
void CContactThread::ParseContactDeleteCmdRet(sContactCmd& Cmd, CString&   CmdRetStr)
{
	BOOL DeleteIsOK=false;
	if(!CmdRetStr.IsEmpty())
	{
		CMarkup Xml;
		if(Xml.SetDoc(CmdRetStr))
		{
			Xml.FindChildElem(_T("ps"));
			if(Xml.IntoElem())
			{
				while ( Xml.FindChildElem(_T("p")) )
				{
					Xml.IntoElem();
					Xml.FindChildElem(_T("name"));
					CString StrData = Xml.GetChildData().c_str();
					if (StrData == _T("msg"))
					{
						Xml.FindChildElem(_T("value"));							
						CString StrMsg = Xml.GetChildData().c_str();
						if (StrMsg == _T("0"))
						{
							DeleteIsOK=true;
							break;
						}
						else
							break;
					}
					Xml.OutOfElem();
				}
			}
		}
	}

	if(DeleteIsOK)
		CMessageCenter::SendMsg(MSG_CONTACT_INFO_TO_DATA_ENGINE,CONTACT_DELTE_CMD,(WPARAM)Cmd.m_CmdParam);
	else
		CMessageCenter::SendMsg(MSG_CONTACT_INFO_TO_DATA_ENGINE,CONTACT_DELTE_CMD,NULL);

}
void CContactThread::ParseContactEditCmdRet(sContactCmd& Cmd, CString&     CmdRetStr)
{
	BOOL EditIsOK=false;
	if(!CmdRetStr.IsEmpty())
	{
		CMarkup Xml;
		if(Xml.SetDoc(CmdRetStr))
		{
			Xml.FindChildElem(_T("ps"));
			if(Xml.IntoElem())
			{
				while ( Xml.FindChildElem(_T("p")) )
				{
					Xml.IntoElem();
					Xml.FindChildElem(_T("name"));
					CString StrData = Xml.GetChildData().c_str();
					if (StrData == _T("msg"))
					{
						Xml.FindChildElem(_T("value"));							
						CString StrMsg = Xml.GetChildData().c_str();
						if (StrMsg == _T("0"))
						{
							EditIsOK=true;
							break;
						}
						else
							break;
					}
					else if(StrData == _T("id"))
					{
						Xml.FindChildElem(_T("value"));							
						CString StrMsg = Xml.GetChildData().c_str();
						
					}

					Xml.OutOfElem();
				}
			}
		}
	}

	if( EditIsOK)
		CMessageCenter::SendMsg(MSG_CONTACT_INFO_TO_DATA_ENGINE,CONTACT_EDIT_CMD,(WPARAM)&Cmd.m_CmdParam);
	else
		CMessageCenter::SendMsg(MSG_CONTACT_INFO_TO_DATA_ENGINE,CONTACT_EDIT_CMD,NULL);
}

void CContactThread::ParseContactBackupCmdRet(sContactCmd& Cmd, CString&   CmdRetStr)
{
	
}

void CContactThread::ParseContactGroupRequestCmdRet(sContactCmd& Cmd, CString& CmdRetStr)
{
	if(CmdRetStr.IsEmpty())
	{
		CMessageCenter::SendMsg(MSG_CONTACTGROUP_INFO_TO_DATA_ENGINE,CONTACTGROUP_REQUEST_CMD,NULL);
		return;
	}

	CMarkup Xml;
	bool IsOk=Xml.SetDoc(CmdRetStr.GetBuffer());
	CmdRetStr.ReleaseBuffer();

	vector<sGroupInfo> InfoList;

	if(IsOk)
	{
		if (Xml.IntoElem())
		{

			while (Xml.FindChildElem(_T("p")) )
			{

				Xml.IntoElem();
				Xml.FindChildElem(_T("name"));
				CString StrData =Xml.GetChildData().c_str();

				if (StrData == _T("msg"))
				{
					Xml.FindChildElem(_T("value"));							
					CString StrMsg = Xml.GetChildData().c_str();
					if (StrMsg != _T("0"))
						break;
					
				}
				else if (StrData == _T("error"))
					break;
				else
				{	
					sGroupInfo Info;

					//组ID
					Info.m_GroupID = StrData;

					//组名
					Xml.FindChildElem(_T("value"));	
					Xml.IntoElem();
					Xml.FindChildElem(_T("title"));	//组名
					StrData = Xml.GetChildData().c_str();
					Info.m_GroupName = StrData;

					//是否为系统分组
					Xml.FindChildElem(_T("system"));						
					StrData = Xml.GetChildData().c_str();
					if(StrData == _T("false"))
						Info.m_IsSystem = false;
					else
						Info.m_IsSystem = true;

					InfoList.push_back(Info);
					Xml.OutOfElem();
				}

				Xml.OutOfElem();
			}
		}
	}

	if(InfoList.empty())
		CMessageCenter::SendMsg(MSG_CONTACTGROUP_INFO_TO_DATA_ENGINE,CONTACTGROUP_REQUEST_CMD,NULL);
	else
		CMessageCenter::SendMsg(MSG_CONTACTGROUP_INFO_TO_DATA_ENGINE,CONTACTGROUP_REQUEST_CMD,(LPARAM)&InfoList);


}

void CContactThread::ParseContactGroupAddCmdRet(sContactCmd& Cmd, CString&    CmdRetStr)
{
	BOOL IsAddOK=false;
	vector<sGroupInfo>* pVector = (vector<sGroupInfo>*)Cmd.m_CmdParam;
	if(pVector != 0 && pVector->size() == 1)
	{
		if( !CmdRetStr.IsEmpty() )
		{
			CMarkup Xml;
			if(Xml.SetDoc(CmdRetStr))
			{
				Xml.FindChildElem(_T("ps"));
				if(Xml.IntoElem())
				{
					while( Xml.FindChildElem(_T("p")) )
					{
						Xml.IntoElem();
						Xml.FindChildElem(_T("name"));
						CString StrData = Xml.GetChildData().c_str();
						if (StrData == _T("msg"))
						{
							Xml.FindChildElem(_T("value"));							
							CString StrMsg = Xml.GetChildData().c_str();

							if (StrMsg == _T("0"))
								IsAddOK=true;
							
						}
						else if (StrData == _T("groupid"))
						{	
							Xml.FindChildElem(_T("value"));							
							CString StrMsg = Xml.GetChildData().c_str();
							(*pVector)[0].m_GroupID = StrMsg;
						}
						Xml.OutOfElem();
					}
				}
			}
		}
	}
	
	if(!IsAddOK)
		CMessageCenter::SendMsg(MSG_CONTACTGROUP_INFO_TO_DATA_ENGINE,CONTACTGROUP_ADD_CMD,NULL);
	else
		CMessageCenter::SendMsg(MSG_CONTACTGROUP_INFO_TO_DATA_ENGINE,CONTACTGROUP_ADD_CMD,(LPARAM)Cmd.m_CmdParam);

}

void CContactThread::ParseContactGroupDeleteCmdRet(sContactCmd& Cmd, CString& CmdRetStr)
{
	BOOL IsDeleteOK=false;
	vector<sGroupInfo>* pVector = (vector<sGroupInfo>*)Cmd.m_CmdParam;
	if(pVector != 0 && pVector->size() == 1)
	{
		if( !CmdRetStr.IsEmpty() )
		{
			CMarkup Xml;
			if(Xml.SetDoc(CmdRetStr))
			{
				Xml.FindChildElem(_T("ps"));
				if(Xml.IntoElem())
				{
					while( Xml.FindChildElem(_T("p")) )
					{
						Xml.IntoElem();
						Xml.FindChildElem(_T("name"));
						CString StrData = Xml.GetChildData().c_str();
						if (StrData == _T("msg"))
						{
							Xml.FindChildElem(_T("value"));							
							CString StrMsg = Xml.GetChildData().c_str();

							if (StrMsg == _T("0"))
								IsDeleteOK=true;
							
						}
						Xml.OutOfElem();
					}
				}
			}
		}
	}
	
	if(!IsDeleteOK)
		CMessageCenter::SendMsg(MSG_CONTACTGROUP_INFO_TO_DATA_ENGINE,CONTACTGROUP_DELETE_CMD,NULL);
	else
		CMessageCenter::SendMsg(MSG_CONTACTGROUP_INFO_TO_DATA_ENGINE,CONTACTGROUP_DELETE_CMD,(LPARAM)Cmd.m_CmdParam);

}

void CContactThread::ParseContactGroupEditCmdRet(sContactCmd& Cmd, CString&   CmdRetStr)
{
	BOOL IsEditOK=false;
	vector<sGroupInfo>* pVector = (vector<sGroupInfo>*)Cmd.m_CmdParam;
	if(pVector != 0 && pVector->size() == 1)
	{
		if( !CmdRetStr.IsEmpty() )
		{
			CMarkup Xml;
			if(Xml.SetDoc(CmdRetStr))
			{
				Xml.FindChildElem(_T("ps"));
				if(Xml.IntoElem())
				{
					while( Xml.FindChildElem(_T("p")) )
					{
						Xml.IntoElem();
						Xml.FindChildElem(_T("name"));
						CString StrData = Xml.GetChildData().c_str();
						if (StrData == _T("msg"))
						{
							Xml.FindChildElem(_T("value"));							
							CString StrMsg = Xml.GetChildData().c_str();

							if (StrMsg == _T("0"))
								IsEditOK=true;
							
						}
						Xml.OutOfElem();
					}
				}
			}
		}
	}
	
	if(!IsEditOK)
		CMessageCenter::SendMsg(MSG_CONTACTGROUP_INFO_TO_DATA_ENGINE,CONTACTGROUP_EDIT_CMD,NULL);
	else
		CMessageCenter::SendMsg(MSG_CONTACTGROUP_INFO_TO_DATA_ENGINE,CONTACTGROUP_EDIT_CMD,(LPARAM)Cmd.m_CmdParam);

}