
/***********************************************************************************
* 说明      ：  此类是所有和JS交互的接口类                                         *
* 创建人    ：  郭庆轩                                                             *
* 创建日期  ：  2012-5-13                                                          *
***********************************************************************************/

#pragma once

#include "webbrowser2.h"
#include "MessageCenter.h"
#include "DataDefine.h"


#include <MSHTML.H>
#include <atlbase.h>
#include <vector>
#include <map>
using std::vector;
using std::map;
using std::string;
#include <atlbase.h>
#include "FormulaCenter.h"

class InterfaceToJS: public IMessageHandle
{
public:
	InterfaceToJS(IDispatch* DisPath);

	virtual ~InterfaceToJS(void);

	enum eTypeID{ECONTACTID, ESMSID, EGROUPID};

	// 底层消息响应
	virtual void OnMessage(eMessage Message,DWORD SystemMsg=0,WPARAM wParam=0,LPARAM lParam=0);

	// 注册消息
	void RegisterMsg();

	// 注销消息
	void LogoutMsg();

	// 设置DisPath	
	virtual void SetDisPath(IDispatch* DisPath); 
 
public:
/****************主对话框操作管理************/

	// 关闭主对话框
	virtual void CPP_Close(); 

	// 最小化对话框
	virtual void CPP_MinDlg();

	// 拖动主对话框
	virtual void CPP_MoveMianDlg(int Xpoint, int Ypoint);

	/*******************************杀红模块*****************************************/
	//获取杀红数据
	virtual void CPP_OnRequestShaHongData();

	//杀红数据转化成json数据
	void ShaHongDataToJson(vector<sFormulaInfo>& FormulaInfo,CString& Str);

/*******************************联系人模块*****************************************/
//	// 切换模块时的刷新
//	virtual void CPP_OnRequestRfreshContactData();
//
//	// 响应 联系人 数据 请求
//	virtual void CPP_OnRequestContactData(); 
//
//	// 添加联系人
//	virtual void CPP_OnRequestAddContactData( const CString &contactDate );
//
//	// 添加联系人文件
//	virtual void CPP_OnRequestAddContactFile( const CString & FilePath );
//
//	// 删除联系人
//	virtual void CPP_OnRequestDeleteContactData( const CString &  ID );
//
//	// 编辑联系人
//	virtual void CPP_OnRequestEditContactData( const CString & strConnect );
//
//	// 联系人备份
//	virtual void CPP_OnRequestBackUpContactData( const CString &  ID );
//
//	// 请求分组数据
//	virtual void CPP_OnRequestGroupData();
//
//	// 添加分组
//	virtual void CPP_OnRequestAddGroupData( const CString & str );
//
//	// 删除分组
//	virtual void CPP_OnRequestDeleteGroupData( const CString & str);
//	// 编辑分组
//	virtual void CPP_OnRequestEditGroupData( const CString & str);
//
///******************************短信模块*****************************************/
//
//	// 请求短信数据：
//	virtual void CPP_OnRequestSmsData();
//
//	//	添加短信
//	virtual void CPP_OnRequestAddSmsData( const CString & contactDate ){}
//
//	//	添加短信文件
//	virtual void CPP_OnRequestAddSmsFile( const CString & FilePath ){}
//
//	//	删除短信
//	virtual void CPP_OnRequestDeleteSmsData( const CString &  ID );
//
//	//	编辑短信
//	virtual void CPP_OnRequestEditSmsData( const CString & str ){}
//
//	//	发送短信
//	virtual void CPP_OnRequestSendSms( const CString & str );
//
//	//	接收到新短信
//	virtual void CPP_OnRequestAcceptSms(){}    				//无
//
///******************************文件管理模块**************************************/
//
//	// 请求安装APK
//	virtual void CPP_OnRequestInstallApk( const CString & ){}
//
//	// 请求批量安装APK
//	virtual void CPP_OnRequestBatchInstallApk( const CString & ){}
//
//	// 请求卸载APK
//	virtual void CPP_OnRequestUninstallApk(const CString & ){}
//
//	// 请求批量卸载APK
//	virtual void CPP_OnRequestBatchUninstallApk(const CString &){}
//
//private:	    
///********************************数据解析与组装部分************************************/
//
//	//// 解析联系人数据 
//	//void AnalyContactInfo( const CString& JsonConatct, vector<sContactInfo>&);
//
//	//// 解析短信数据 
//	//void AnalySmsInfo( const CString& JsonSms, vector<sSmsInfo>&);
//
//	//// 解析联系人 分组 数据
//	//void AnalyContactGroupinfo(const CString& JsonConatct, vector<sGroupInfo>&);
//
//	//// 解析发送短信内容
//	//void AnalySendSmsInfo(const CString& JsonSendSms, vector<sSendSmsInfo>&);
//
//	//// 解析联系人或者短信的ID 
//	//int CommonAnalyInfo(const CString& JsonData, vector<CString>& vctinfo, eTypeID etype);
//
//	//// 解析JS传过来的路径
//	//void CommonAnalyPath(const CString& JsonData, CString& filePath);
//
//	//// 组合 结构体 联系人 成 JSON格式
//	//void CombinContactToJson(const vector<sContactInfo>& , CString&);
//
//	//// 组合 结构体 分组 变成 JSON格式
//	//void CombinGroupInfo(const vector<sGroupInfo>&, CString&);
//
//	//// 组合 结构体 短信 变成 JSON格式
//	//void CombinSmsToJson(const vector<sSmsInfo>&, CString&);
//
//	// Cstring 转 string 字符 
//	const string CstringtoString( const CString &Cstr ); 
//
//private:

	// 执行JS脚本 程序
	virtual void ExecJsScript(CString& JsStr); 

	//// JS接口+参数的CString格式
	CString MakeStrJsIntface(const CString& JsIntface,const CString& JsParame );

	//// 执行联系人JS接口+参数
	//void DoContactJsIntface(const CString&JsIntface, vector<sContactInfo>& ContactInfo);

	//// 执行短信JS接口+参数
	//void DoSmsJsIntface(const CString&JsIntface, vector<sSmsInfo>& ContactInfo);

	 

	//// 处理联系人消息
	//void ContacReturnWeb(eMessage Message,WPARAM wParam, LPARAM lParam);

	//// 处理联系人消息
	//void SmsReturnWeb(eMessage Message,WPARAM wParam, LPARAM lParam);

private:
	IDispatch*   m_DisPath;
	
};
