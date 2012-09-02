#pragma once

//数据引擎接口
#include "DataDefine.h"
#include <vector>
#include <map>
using std::vector;
using std::map;

class EXPORT_CLASS IDataEngine
{
public:

	//连接手机
	virtual void ConnectPhone(CString PhoneDes)=0;

	//断开连接手机
	virtual void StopConnectPhone()=0;

	//请求手机信息
	virtual void RequestPhoneInfo()=0;

	//获取手机信息
	virtual sPhoneInfo GetPhoneInfo()=0;


	/************联系人操作接口*************/

	//请求联系人数据
	virtual void RequestContactInfo()=0;

	//请求删除联系人
	virtual void RequestDeleteContactInfo(CString ID)=0;

	//请求批量删除联系人
	virtual void RequestBatchDeleteContactInfo(vector<CString>& ID)=0;

	//请求删除所有联系人
	virtual void RequestDeleteAllContactInfo()=0;

	//请求添加联系人
	virtual void RequestAddContactInfo(sContactInfo& Info)=0;

	//请求批量添加联系人
	virtual void RequestBatchAddContactInfo(vector<sContactInfo>& InfoList)=0;

	//请求编辑联系人
	virtual void RequestEditContactInfo(sContactInfo& Info)=0;

	//请求联系人分组
	virtual void RequestContactGroupInfo()=0;

	//请求删除联系人分组
	virtual void RequestDeleteContactGroupInfo(CString ID)=0;

	//请求批量删除联系人分组
	virtual void RequestBatchDeleteContactGroupInfo(vector<CString>& ID)=0;

	//请求删除所有联系人分组
	virtual void RequestDeleteAllContactGroupInfo()=0;

	//请求添加联系人分组
	virtual void RequestAddContactGroupInfo(sGroupInfo& Info)=0;

	//请求批量添加联系人分组
	virtual void RequestBatchAddContactGroupInfo(vector<sGroupInfo>& InfoList)=0;
		
	//请求编辑联系人
	virtual void RequestEditContactGroupInfo(sGroupInfo& Info)=0;

	//获取联系人列表
	virtual vector<sContactInfo>* GetContactInfoList()=0; 

	//获取单个联系人
	virtual bool  GetContactInfo(CString ID,sContactInfo& Info)=0;    

	//获取指定联系人 
	virtual void GetContactInfo(vector<CString>& IDList,vector<sContactInfo>& Info)=0;    

	//获取联系人分组列表
	virtual vector<sGroupInfo>* GetContactGroupInfoList()=0;   

	//获取联系人分组
	virtual bool  GetContactGroupInfo(CString ID,sGroupInfo& Info)=0;        

	//获取联系人指定分组
	virtual void GetContactGroupInfo(vector<CString>& IDList, vector<sGroupInfo>& InfoList)=0;          

	//获取通话记录列表
	virtual vector<sCallLogInfo>* GetCallLogInfoList()=0;


	/************短信操作接口**************/

	//请求短信信息
	virtual void ReqeustSmsInfo()=0; 

	//请求删除短信
	virtual void RequestDeleteSmsInfo(CString ID)=0;

	//请求批量删除短信
	virtual void RequestBatchDeleteSmsInfo(vector<CString>& IDList)=0;

	//请求删除所有短信 
	virtual void RequestDeletAllSmsInfo()=0;

	//请求发送短信
	virtual void RequestSendSmsInfo(sSendSmsInfo& Info)=0;

	//请求批量发送短信
	virtual void RequestBatchSendSmsInfo(vector<sSendSmsInfo>& Info)=0;


	/************应用操作接口**************/

	virtual void RequestInstallApk(CString ApkPath,ePathType Type)=0;

	virtual void RequestBatchInstallApk(vector<CString> ApkPath,ePathType Type)=0;

	virtual void UninstallApk(CString ApkPackName)=0;

	virtual void BatchUninstallApk(vector<CString> ApkPackName)=0;
	

	/************文件操作接口**************/
	
	

};

//获取数据引擎实例
extern EXPORT_API IDataEngine* GetDataEngineInterface(ePhoneOSType Type=PHONE_OS_ANDROID);