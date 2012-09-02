#pragma once

#include "DataDefine.h"



// Input: strSrc,原始字符串 abc&defg&123
// strEsc 需要转义的字符串，比如"&"
// strReplaceEsc 代替转义的字符串，比如"&amp;"
// Output: abc&amp;def&amp;123
// 将原始字符串中特殊字符串转化成转义字符串
CString ReplaceStr( CString strSrc, CString strSub, CString strReplace ); // 转义字符处理


/*****************************************转码函数****************************************/
//从GBK　转码到　UTF8
void TransGBKToUtf8(CString&  strGBK);

//从Utf8　转码到　GBK
void TransUtf8ToGBK(CString&  strUtf8);

//从GBK　转码到　Unicode
void TransGBKToUnicode(CString&  strGBK);

//从UTF8 转码到 UNICODE
void TransUtf8ToUnicode(CString&  strUtf8);

//从Uincode 转码到UTF8
void TransUnicodeToUtf8(CString& strUnicode);

//从UTF8 转码到 URLCODE
void TransUtf8ToURLCode(CString& strUtf8);

//从UNICODE 转码到　URLCODE
void TransUnicodeToURLCode(CString& strUnicode);

//从UNICODE 转码到　BASE64
void TransUnicodeToBase64(CString& strUnicode);

//从Base64 转码到　Unicode
void TransBase64ToUnicode(CString& strBase64);

//将字符串转化为unicode
wchar_t* TransUtf8CharToUncodeWchar(char *utf8);

//将字符串转换为utf-8
char* TransUncodeWcharToUtf8Char(const wchar_t *unicode);


/*****************************************执行adb函数****************************************/
//执行adb命令
bool ExecAdbCmd(CString CmdStr,CString& CmdRetStr);



/*****************************************公共函数****************************************/
//获取应用程序路径
CString GetAppPath(void);

//获取应用程序路径
CString GetAppPath2(CString Temp);

//判断文件是否存在
bool IsFilesExit(CString FileName);

//获取首字母 类型 1 首字母 0 全字母
CString GetFirstLetter(CString Name, int Type=1);

//安装手机应用程序
bool InstallPhoneApp(CString PhoneDes,CString AppName,bool IsReInstall,ePathType Type=PATH_PHONE);


//获取Android设备列表
void GetAndroidDeviceList(vector<sPhoneStatus>& DeviceList);

//获取Android设备列表
void GetApplicationPath(CString& Path);





//写人操作日志文件
void WriteLog(const char* Format,...);

//写人操作日志文件
void WriteLog(const wchar_t* Format,...);