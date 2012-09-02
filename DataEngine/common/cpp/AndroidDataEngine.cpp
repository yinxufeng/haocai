#include "StdAfx.h"
#include "../Include/AndroidDataEngine.h"

//获取联系人命令序列ID
DWORD GetContactCmdID()
{
	static DWORD ID=0;

	return ID++;
};

//获取短信命令序列ID
DWORD GetSMSCmdID()
{
	static DWORD ID=0;

	return ID++;
};



CAndroidDataEngine::CAndroidDataEngine(void)
{
	//注册消息
	RegisterMessage();

	m_ConnectThread.StartThread();
	m_ContactThread.StartThread();
}

CAndroidDataEngine::~CAndroidDataEngine(void)
{
	//注销消息
	UnRegisterMessage();
	m_ConnectThread.StopThread();
	m_ContactThread.StopThread();
}


//连接手机
void CAndroidDataEngine::ConnectPhone(CString PhoneDes)
{
	m_ConnectThread.StartConnectPhone(PhoneDes);
}

//断开连接手机
void CAndroidDataEngine::StopConnectPhone()
{
	m_ConnectThread.StopConnectPhone();
}

//请求手机信息
void CAndroidDataEngine::RequestPhoneInfo()
{

}

//获取手机信息
sPhoneInfo CAndroidDataEngine::GetPhoneInfo()
{
	return m_PhoneInfo;
}


/************联系人操作接口*************/

//请求联系人数据
void CAndroidDataEngine::RequestContactInfo()
{
	m_ContactInfoList.clear();
//	m_GroupInfoList.clear();
	sContactCmd Cmd;
	/*Cmd.m_CmdId = GetContactCmdID();
	Cmd.m_CmdParam = NULL;
	Cmd.m_CmdParamCount = 0;
	Cmd.m_CmdType = CONTACTGROUP_REQUEST_CMD;*/
	//m_ContactThread.AddWorkCmd(Cmd);

	Cmd.m_CmdId = GetContactCmdID();
	Cmd.m_CmdParam = NULL;
	Cmd.m_CmdParamCount = 0;
	Cmd.m_CmdType = CONTACT_REQUEST_CMD;
	m_ContactThread.AddWorkCmd(Cmd);
}

//请求删除联系人
void CAndroidDataEngine::RequestDeleteContactInfo(CString ID)
{
	vector<CString>* pVector=new vector<CString>;
	pVector->push_back(ID);

	sContactCmd Cmd;
	Cmd.m_CmdId = GetContactCmdID();
	Cmd.m_CmdParam = (WPARAM)pVector;
	Cmd.m_CmdParamCount = 1;
	Cmd.m_CmdType = CONTACT_DELTE_CMD;
	m_ContactThread.AddWorkCmd(Cmd);
}

//请求批量删除联系人
void CAndroidDataEngine::RequestBatchDeleteContactInfo(vector<CString>& IDList)
{
	vector<CString>* pVector=new vector<CString>;
	*pVector=IDList;
	sContactCmd Cmd;
	Cmd.m_CmdId = GetContactCmdID();
	Cmd.m_CmdParam = (WPARAM)pVector;
	Cmd.m_CmdParamCount = IDList.size();
	Cmd.m_CmdType = CONTACT_DELTE_CMD;
	m_ContactThread.AddWorkCmd(Cmd);
}

//请求删除所有联系人
void CAndroidDataEngine::RequestDeleteAllContactInfo()
{
	sContactCmd Cmd;
	Cmd.m_CmdId =GetContactCmdID();
	Cmd.m_CmdParam = NULL;
	Cmd.m_CmdParamCount = 0;
	Cmd.m_CmdType = CONTACT_DELTE_ALL_CMD;
	m_ContactThread.AddWorkCmd(Cmd);
}

//请求添加联系人
void CAndroidDataEngine::RequestAddContactInfo(sContactInfo& Info)
{
	vector<sContactInfo>* pVector=new vector<sContactInfo>;
	pVector->push_back(Info);

	sContactCmd Cmd;
	Cmd.m_CmdId = GetContactCmdID();
	Cmd.m_CmdParam = (WPARAM)pVector;
	Cmd.m_CmdParamCount = 1;
	Cmd.m_CmdType = CONTACT_ADD_CMD;
	m_ContactThread.AddWorkCmd(Cmd);
}

//请求批量添加联系人
void CAndroidDataEngine::RequestBatchAddContactInfo(vector<sContactInfo>& InfoList)
{
	vector<sContactInfo>* pVector=new vector<sContactInfo>;
	*pVector = InfoList;

	sContactCmd Cmd;
	Cmd.m_CmdId = GetContactCmdID();
	Cmd.m_CmdParam = (WPARAM) pVector;
	Cmd.m_CmdParamCount = InfoList.size();
	Cmd.m_CmdType = CONTACT_ADD_CMD;
	m_ContactThread.AddWorkCmd(Cmd);
}

//请求编辑联系人
void CAndroidDataEngine::RequestEditContactInfo(sContactInfo& Info)
{
	vector<sContactInfo>* pVector=new vector<sContactInfo>;
	pVector->push_back(Info);
	sContactCmd Cmd;
	Cmd.m_CmdId = GetContactCmdID();
	Cmd.m_CmdParam = (WPARAM) pVector;
	Cmd.m_CmdParamCount = 1;
	Cmd.m_CmdType = CONTACT_EDIT_CMD;
	m_ContactThread.AddWorkCmd(Cmd);
}

//请求联系人分组
void CAndroidDataEngine::RequestContactGroupInfo()
{
	sContactCmd Cmd;
	m_GroupInfoList.clear();
	Cmd.m_CmdId = GetContactCmdID();
	Cmd.m_CmdParam = NULL;
	Cmd.m_CmdParamCount = 0;
	Cmd.m_CmdType = CONTACTGROUP_REQUEST_CMD;
	m_ContactThread.AddWorkCmd(Cmd);
}

//请求删除联系人分组
void CAndroidDataEngine::RequestDeleteContactGroupInfo(CString ID)
{
	vector<CString>* pVector=new vector<CString>;
	pVector->push_back(ID);
	sContactCmd Cmd;
	Cmd.m_CmdId = GetContactCmdID();
	Cmd.m_CmdParam = (WPARAM) pVector;
	Cmd.m_CmdParamCount = 1;
	Cmd.m_CmdType = CONTACTGROUP_DELETE_CMD;
	m_ContactThread.AddWorkCmd(Cmd);
}

//请求批量删除联系人分组
void CAndroidDataEngine::RequestBatchDeleteContactGroupInfo(vector<CString>& IDList)
{
	vector<CString>* pVector=new vector<CString>;
	*pVector = IDList;
	sContactCmd Cmd;
	Cmd.m_CmdId = GetContactCmdID();
	Cmd.m_CmdParam = (WPARAM) pVector;
	Cmd.m_CmdParamCount = IDList.size();
	Cmd.m_CmdType = CONTACTGROUP_DELETE_CMD;
	m_ContactThread.AddWorkCmd(Cmd);
}

//请求删除所有联系人分组
void CAndroidDataEngine::RequestDeleteAllContactGroupInfo()
{
	sContactCmd Cmd;
	Cmd.m_CmdId = GetContactCmdID();
	Cmd.m_CmdParam = NULL;
	Cmd.m_CmdParamCount = 0;
	Cmd.m_CmdType = CONTACTGROUP_DELETE_ALL_CMD;
	m_ContactThread.AddWorkCmd(Cmd);
}

//请求添加联系人分组
void CAndroidDataEngine::RequestAddContactGroupInfo(sGroupInfo& Info)
{
	vector<sGroupInfo>* pVector=new vector<sGroupInfo>;
	pVector->push_back(Info);
	sContactCmd Cmd;
	Cmd.m_CmdId =GetContactCmdID();
	Cmd.m_CmdParam = (WPARAM) pVector;
	Cmd.m_CmdParamCount = 1;
	Cmd.m_CmdType = CONTACTGROUP_ADD_CMD;
	m_ContactThread.AddWorkCmd(Cmd);
}

//请求批量添加联系人分组
void CAndroidDataEngine::RequestBatchAddContactGroupInfo(vector<sGroupInfo>& InfoList)
{
	vector<sGroupInfo>* pVector=new vector<sGroupInfo>;
	*pVector = InfoList;
	sContactCmd Cmd;
	Cmd.m_CmdId =GetContactCmdID();
	Cmd.m_CmdParam = (WPARAM) pVector;
	Cmd.m_CmdParamCount = 1;
	Cmd.m_CmdType = CONTACTGROUP_ADD_CMD;
	m_ContactThread.AddWorkCmd(Cmd);
}
	
//请求编辑联系人分组
void CAndroidDataEngine::RequestEditContactGroupInfo(sGroupInfo& Info)
{
	vector<sGroupInfo>* pVector=new vector<sGroupInfo>;
	pVector->push_back(Info);
	sContactCmd Cmd;
	Cmd.m_CmdId =GetContactCmdID();
	Cmd.m_CmdParam = (WPARAM) pVector;
	Cmd.m_CmdParamCount = 1;
	Cmd.m_CmdType = CONTACTGROUP_EDIT_CMD;
	m_ContactThread.AddWorkCmd(Cmd);
}

//获取联系人列表
vector<sContactInfo>* CAndroidDataEngine::GetContactInfoList()
{
	return &m_ContactInfoList;
}

//获取单个联系人
bool  CAndroidDataEngine::GetContactInfo(CString ID,sContactInfo& Info)
{
	for(int Index = 0; Index < (int)m_ContactInfoList.size(); Index++)
	{
		if(m_ContactInfoList[Index].m_ID == ID)
		{
			Info = m_ContactInfoList[Index];
			return true;
		}
	}
	return false;
}

//获取指定联系人 
void CAndroidDataEngine::GetContactInfo(vector<CString>& IDList,vector<sContactInfo>& InfoList)
{
	for(int Index = 0; Index < (int)m_ContactInfoList.size(); Index++)
	{
		for(int IDIndex=0; IDIndex < IDList.size(); IDIndex++)
		{
			if(m_ContactInfoList[Index].m_ID == IDList[IDIndex])
			{
				InfoList.push_back(m_ContactInfoList[Index]);
				break;
			}
		}
	}
}

//获取联系人分组列表
vector<sGroupInfo>* CAndroidDataEngine::GetContactGroupInfoList()
{
	return &m_GroupInfoList;
}

//获取联系人分组
bool CAndroidDataEngine::GetContactGroupInfo(CString ID,sGroupInfo& Info)
{
	
	for(int Index = 0; Index < (int)m_GroupInfoList.size(); Index++)
	{
		if(m_GroupInfoList[Index].m_GroupID == ID)
		{
			Info = m_GroupInfoList[Index];
			return true;
		}
	}
	return false;
}

//获取联系人指定分组
void CAndroidDataEngine::GetContactGroupInfo(vector<CString>& IDList,vector<sGroupInfo>& InfoList)
{
	for(int Index = 0; Index < (int)m_GroupInfoList.size(); Index++)
	{
		for(int IDIndex=0; IDIndex < IDList.size(); IDIndex++)
		{
			if(m_GroupInfoList[Index].m_GroupID == IDList[IDIndex])
			{
				InfoList.push_back(m_GroupInfoList[Index]);
				break;
			}
		}
	}
}

//获取通话记录列表
vector<sCallLogInfo>* CAndroidDataEngine::GetCallLogInfoList()
{
	return &m_CallLogInfoList;
}

      

/************************************短信操作接口***********************************s************/

//请求短信信息
void CAndroidDataEngine::ReqeustSmsInfo()
{
	m_SmsInfoList.clear();
	sSmsCmd Cmd;

	Cmd.m_CmdId = GetSMSCmdID();
	Cmd.m_CmdParam = NULL;
	Cmd.m_CmdParamCount = 0;
	Cmd.m_CmdType = SMS_REQUEST_CMD;
	m_SmsThread.AddWorkCmd(Cmd);
}

//请求删除短信
void CAndroidDataEngine::RequestDeleteSmsInfo(CString ID)
{
	vector<CString>* pVector=new vector<CString>;
	pVector->push_back(ID);

	sSmsCmd Cmd;
	Cmd.m_CmdId = GetContactCmdID();
	Cmd.m_CmdParam = (WPARAM)pVector;
	Cmd.m_CmdParamCount = 1;
	Cmd.m_CmdType = SMS_DELTE_CMD;
	m_SmsThread.AddWorkCmd(Cmd);
}

//请求批量删除短信
void CAndroidDataEngine::RequestBatchDeleteSmsInfo(vector<CString>& IDList)
{
	vector<CString> *pVector = new vector<CString>;
	*pVector = IDList;
	sSmsCmd Cmd;
	Cmd.m_CmdId = GetSMSCmdID();
	Cmd.m_CmdParam = (WPARAM)pVector;
	Cmd.m_CmdParamCount = IDList.size();
	Cmd.m_CmdType = SMS_DELTE_CMD;
	m_SmsThread.AddWorkCmd(Cmd);
}

//请求删除所有短信 
void CAndroidDataEngine::RequestDeletAllSmsInfo()
{
	sSmsCmd Cmd;
	Cmd.m_CmdId =GetSMSCmdID();
	Cmd.m_CmdParam = NULL;
	Cmd.m_CmdParamCount = 0;
	Cmd.m_CmdType = SMS_DELTE_ALL_CMD;
	m_SmsThread.AddWorkCmd(Cmd);
}

//请求发送短信
void CAndroidDataEngine::RequestSendSmsInfo(sSendSmsInfo& Info)
{
	vector<sSendSmsInfo> *pvect = new vector<sSendSmsInfo>;
	pvect->push_back(Info);
	sSmsCmd Cmd;
	Cmd.m_CmdId =GetSMSCmdID();
	Cmd.m_CmdParam = (WPARAM)pvect;
	Cmd.m_CmdParamCount = 1;
	Cmd.m_CmdType = SMS_SEND_CMD;
	m_SmsThread.AddWorkCmd(Cmd);
}

//请求批量发送短信
void CAndroidDataEngine::RequestBatchSendSmsInfo(vector<sSendSmsInfo>& InfoList)
{
	vector<sSendSmsInfo> *pvect = new vector<sSendSmsInfo>;
	*pvect = InfoList;
	sSmsCmd Cmd;
	Cmd.m_CmdId =GetSMSCmdID();
	Cmd.m_CmdParam = (WPARAM)pvect;
	Cmd.m_CmdParamCount = pvect->size();
	Cmd.m_CmdType = SMS_DELTE_ALL_CMD;
	m_SmsThread.AddWorkCmd(Cmd);
}


/************应用操作接口**************/

void CAndroidDataEngine::RequestInstallApk(CString ApkPath,ePathType Type)
{
}

void CAndroidDataEngine::RequestBatchInstallApk(vector<CString> ApkPath,ePathType Type)
{
}

void CAndroidDataEngine::UninstallApk(CString ApkPackName)
{
}

void CAndroidDataEngine::BatchUninstallApk(vector<CString> ApkPackName)
{

}


/************文件操作接口**************/

// 获取Android数据引擎实例
IDataEngine* GetAndroidDataEngineInterface()
{
	static CAndroidDataEngine DataEngine;
	IDataEngine* pDataEngine=(IDataEngine*)&DataEngine;
	return pDataEngine;
}

//获取数据引擎实例
EXPORT_API IDataEngine* GetDataEngineInterface(ePhoneOSType Type)
{
	if(Type == PHONE_OS_ANDROID)
		return GetAndroidDataEngineInterface();
	return NULL;
}
