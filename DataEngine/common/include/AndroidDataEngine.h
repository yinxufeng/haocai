#pragma once
#include "idataengine.h"
#include "MessageCenter.h"
#include "../../connect/ConnectThread.h"
#include "../../contact/ContactThread.h"
#include "../../sms/SmsThread.h"

class EXPORT_CLASS CAndroidDataEngine :public IDataEngine,public IMessageHandle
{
public:
	CAndroidDataEngine(void);

	~CAndroidDataEngine(void);

public:

	//注册消息
	void RegisterMessage();

	//注销消息
	void UnRegisterMessage();

	//响应消息
	virtual void OnMessage(eMessage Message,DWORD SystemMsg=0,WPARAM wParam=0,LPARAM lParam=0);

	//连接手机
	void ConnectPhone(CString ConnectInfo);

	//断开连接手机
	void StopConnectPhone();

	//请求手机信息
	void RequestPhoneInfo();

	//获取手机信息
	sPhoneInfo GetPhoneInfo();


	/************联系人操作接口*************/

	//请求联系人数据
	void RequestContactInfo();

	//请求删除联系人
	void RequestDeleteContactInfo(CString ID);

	//请求批量删除联系人
	void RequestBatchDeleteContactInfo(vector<CString>& IDList);

	//请求删除所有联系人
	void RequestDeleteAllContactInfo();

	//请求添加联系人
	void RequestAddContactInfo(sContactInfo& Info);

	//请求批量添加联系人
	void RequestBatchAddContactInfo(vector<sContactInfo>& InfoList);

	//请求编辑联系人
	void RequestEditContactInfo(sContactInfo& Info);

	//请求联系人分组
	void RequestContactGroupInfo();

	//请求删除联系人分组
	void RequestDeleteContactGroupInfo(CString ID);

	//请求批量删除联系人分组
	void RequestBatchDeleteContactGroupInfo(vector<CString>& IDList);

	//请求删除所有联系人分组
	void RequestDeleteAllContactGroupInfo();

	//请求添加联系人分组
	void RequestAddContactGroupInfo(sGroupInfo& Info);

	//请求批量添加联系人分组
	void RequestBatchAddContactGroupInfo(vector<sGroupInfo>& InfoList);
		
	//请求编辑联系人分组
	void RequestEditContactGroupInfo(sGroupInfo& Info);

	//获取联系人列表
	vector<sContactInfo>* GetContactInfoList(); 

	//获取单个联系人
	bool GetContactInfo(CString ID,sContactInfo& Info);

	//获取指定联系人 
	void GetContactInfo(vector<CString>& IDList,vector<sContactInfo>& InfoList);    

	//获取联系人分组列表
	vector<sGroupInfo>* GetContactGroupInfoList();   

	//获取联系人分组
	bool GetContactGroupInfo(CString ID,sGroupInfo& Info);        

	//获取联系人指定分组
	void GetContactGroupInfo(vector<CString>& IDList,vector<sGroupInfo>& InfoList);       

	//获取通话记录列表
	vector<sCallLogInfo>* GetCallLogInfoList();


	/************短信操作接口**************/

	//请求短信信息
	void ReqeustSmsInfo(); 

	//请求删除短信
	void RequestDeleteSmsInfo(CString ID);

	//请求批量删除短信
	void RequestBatchDeleteSmsInfo(vector<CString>& IDList);

	//请求删除所有短信 
	void RequestDeletAllSmsInfo();

	//请求发送短信
	void RequestSendSmsInfo(sSendSmsInfo& Info);

	//请求批量发送短信
	void RequestBatchSendSmsInfo(vector<sSendSmsInfo>& Info);

	/************应用操作接口**************/

	void RequestInstallApk(CString ApkPath,ePathType Type);

	void RequestBatchInstallApk(vector<CString> ApkPath,ePathType Type);

	void UninstallApk(CString ApkPackName);

	void BatchUninstallApk(vector<CString> ApkPackName);
	

	/************文件操作接口**************/

private:

	//联系人排序
	void SortContactInfo(vector<sContactInfo>&SortData,eContactSortType Type=CONTACT_SORT_BY_NAME);

	//处理联系人消息
	void DoContactMsg(WPARAM wParam,LPARAM lParam);

	//处理短信消息
	void DoSmsMsg(WPARAM wParam,LPARAM lParam);

	//处理联系人分组消息
	void DoContactGroupMsg(WPARAM wParam,LPARAM lParam);

	//短信与联系人匹配
	void SmsMatchContact(vector<sSmsInfo>*);


private:
	vector<sContactInfo>            m_ContactInfoList;         //联系人数据列表
	vector<sGroupInfo>              m_GroupInfoList;           //联系人分组数据列表
	vector<sCallLogInfo>            m_CallLogInfoList;         //通话记录列表
	map<CString,vector<sSmsInfo>>   m_SmsInfoList;             //短信列表
	sPhoneInfo                      m_PhoneInfo;               //手机信息

private:

	CConnectThread                  m_ConnectThread;           //连接管理线程
	CContactThread                  m_ContactThread;           //联系人管理线程

	CSmsThread						m_SmsThread;			   //短信管理线程
};




