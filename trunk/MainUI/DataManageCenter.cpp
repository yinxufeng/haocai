#include "StdAfx.h"
#include "DataManageCenter.h"

CDataManageCenter* CDataManageCenter::m_Self = NULL;
CDataManageCenter::CDataManageCenter(void)
{
	m_IsIdentify = FALSE;
	m_MMUrl=_T("http://pcmm.shequ.10086.cn:9090/");

//	m_ConnectMode = CONNECT_MODE_NULL;
	m_ConnectMode = CONNECT_MODE_BY_USB;
}

CDataManageCenter::~CDataManageCenter(void)
{
}


//初始实例
CDataManageCenter* CDataManageCenter::Init()
{
	if(m_Self==NULL)
		m_Self=new CDataManageCenter();
	return m_Self;
}

//删除实例
void CDataManageCenter::Delete()
{
	if(m_Self != NULL)
	{
		delete m_Self;
		m_Self = NULL;
	}
}


//获取驱动信息
sUsbConnectInfo* CDataManageCenter::GetUsbConnectInfo(CString DesId)
{
	if(DesId.IsEmpty())
		return NULL;
	DesId.MakeUpper();
	map<CString,sUsbConnectInfo*>::iterator it=m_UsbConnectInfoList.find(DesId);
	if(it == m_UsbConnectInfoList.end())
		return NULL;

	return it->second;
}

//获取当前Wifi连接信息
sWifiConnectInfo CDataManageCenter::GetWifiInfo(CString WifiId)
{
	sWifiConnectInfo Temp;
	if(WifiId.IsEmpty())
		return Temp;
	
	map<CString,sWifiConnectInfo>::iterator it=m_WifiConenctInfoList.find(WifiId);
	if(it == m_WifiConenctInfoList.end())
		return Temp;

	return it->second;
}

//添加连接手机信息
void CDataManageCenter::AddUsbConnectInfo(CString DesId,sUsbConnectInfo* UsbConnectInfo)
{
	if(DesId.IsEmpty())
		return;

	DesId.MakeUpper();
	map<CString,sUsbConnectInfo*>::iterator it=m_UsbConnectInfoList.find(DesId);
	if(it != m_UsbConnectInfoList.end() && it->second)
		delete it->second;
	m_UsbConnectInfoList[DesId] = UsbConnectInfo;
}

//删除连接手机信息
void CDataManageCenter::DeleteUsbConnectInfo(CString DesId)
{
	if(DesId.IsEmpty())
		return ;

	DesId.MakeUpper();
	map<CString,sUsbConnectInfo*>::iterator it=m_UsbConnectInfoList.find(DesId);
	if(it == m_UsbConnectInfoList.end())
		return ;

	if(it->second)	
	{
		delete it->second;
		it->second = NULL;
	}

	m_UsbConnectInfoList.erase(it);
}

void CDataManageCenter::DeleteAllUsbConnectInfo()
{
	map<CString,sUsbConnectInfo*>::iterator it = m_UsbConnectInfoList.begin();
	while(it != m_UsbConnectInfoList.end())
	{
		if(it->second)	
		{
			delete it->second;
			it->second = NULL;
		}

		it++;
	}
	m_UsbConnectInfoList.clear();
}


//获取WIFI模式下所有手机连接信息
map<CString,sWifiConnectInfo>* CDataManageCenter::GetAllWifiConenctInfoList()
{
	m_WifiConenctInfoList.clear();
	//m_WifiConenctInfoList=CBroadServer::GetWifiConenctInfoList();
	return &m_WifiConenctInfoList;
}

//删除当前WIFI连接信息
void CDataManageCenter::DeleteWifiInfo(CString WifiId)
{
	/*if(!WifiId.IsEmpty())
		CBroadServer::DeleteWifiConnectInfo(WifiId);*/
}