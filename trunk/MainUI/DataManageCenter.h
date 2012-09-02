/***********************************************************************************
* 说明      ：  CDataManageCenter数据管理中心，负责管理公共数据，采用单件模式      *
* 创建人    ：  谭军红                                                             *
* 创建日期  ：  2011-9-8                                                           *
***********************************************************************************/
#pragma once

#include "DataDefine.h"

class CDataManageCenter
{
public:

	//初始实例
	static CDataManageCenter* Init();

	//删除实例
	static void Delete();

	//获取驱动信息
	sUsbConnectInfo* GetUsbConnectInfo(CString DesId);

	//获取当前Wifi连接信息
	sWifiConnectInfo GetWifiInfo(CString WifiId);

	//添加连接手机信息
	void AddUsbConnectInfo(CString DesId,sUsbConnectInfo* UsbConnectInfo);

	//删除连接手机信息
	void DeleteUsbConnectInfo(CString DesId);

	//删除所有连接手机信息
	void DeleteAllUsbConnectInfo();

	//删除当前WIFI连接信息
	void DeleteWifiInfo(CString WifiId);

	//设置当前连接的手机ID
	void SetCurrentConnectPhoneDesId(CString DesId) { if(!DesId.IsEmpty()) m_PhoneDesId = DesId; m_WifiInfoId.Empty(); }

	//设置当前WIFI连接的手机ID
	void SetCurrentConnectWifiId(CString Id) { if(!Id.IsEmpty()) m_WifiInfoId = Id; m_PhoneDesId.Empty();}

	//获取当前连接的手机ID
	CString GetCurrentConnectPhoneDesId() { return m_PhoneDesId; }

	//获取当前连接的手机ID
	CString GetCurrentConnectWifiId() { return m_WifiInfoId; }

	//获取USB当前连接手机信息
	sUsbConnectInfo* GetCurrentConnectUsbConnectInfo() { return GetUsbConnectInfo(m_PhoneDesId);}

	//获取所USB有连接手机信息
	map<CString,sUsbConnectInfo*>* GetAllConnectPhoneList() { return &m_UsbConnectInfoList; }

	//获取WIFI模式下所有手机连接信息
	map<CString,sWifiConnectInfo>* GetAllWifiConenctInfoList();

	//获取当前Wifi连接信息
	sWifiConnectInfo GetCurrentConenctWifiInfo() { return GetWifiInfo(m_WifiInfoId); }

	//设置当前驱动版本号
	void SetDriveVersion(CString Version) { if(!Version.IsEmpty()) m_DriveVersion = Version; }

	//获取驱动版本
	CString GetDrivVersion() { return m_DriveVersion; }

	//设置驱动配置信息下载路径
	void SetDriveURL(CString Url) { if(!Url.IsEmpty()) m_DriveUrl = Url; }

	//驱动配置信息下载路径
	CString GetDriveURL() { return m_DriveUrl;}

	//设置MM下载店URL
	void SetMMUrl(CString Url) { if(!Url.IsEmpty()) m_MMUrl = Url; }

	//获取MM下载店URL
	CString GetMMUrl() { return m_MMUrl; }

	//设置是否在识别标志
	void SetIsIdentify(BOOL IsIdentify){ m_IsIdentify = IsIdentify; }

	//获取是否在识别标志
	BOOL GetIsIdentify() { return m_IsIdentify; }

	//设置应用程序版本号
	void SetCurrentProgramVersion(CString Version){  if(!Version.IsEmpty()) m_ProgramVersion= Version; }
	
	//获取应用程序版本号
	CString GetCurrentProgramVersion() { return m_ProgramVersion;}

	//获取当前连接类型
	eConnectMode GetCurrentConnectMode(){ return m_ConnectMode;}

	//设置当前连接类型
	void SetCurrentConenctMode(eConnectMode Mode){ m_ConnectMode = Mode;}
private:

	CDataManageCenter(void);

	~CDataManageCenter(void);


private:
	static CDataManageCenter*      m_Self;                   
	map<CString,sUsbConnectInfo*>       m_UsbConnectInfoList;          //连接手机信息列表  
	map<CString,sWifiConnectInfo>  m_WifiConenctInfoList;    //手机在WIFI模式下连接的列表
	CString                        m_PhoneDesId;             //当前手机连接的ID
	CString                        m_MMUrl;                  //MM下载店URL
	CString                        m_DriveVersion;           //驱动版本
	CString                        m_DriveUrl;               //驱动配置信息下载路径
	CString                        m_ProgramVersion;         //程序版本信息
	CString                        m_WifiInfoList;           //WIFI模式下手机连接列表
	CString                        m_WifiInfoId;             //当前WIFI手机连接ID
	BOOL                           m_IsIdentify;             //手机是否正在识别标志
	eConnectMode                   m_ConnectMode;            //当前连接模式
};
