#pragma once
#include <stdio.h>
#include <tlhelp32.h>
#include <winnls.h>
#include <windows.h>
#include <dbt.h> 
#include <vector>
#include <string>

using std::vector;

#define   WINVER   0x0500 

char *  Time2String(char * szDT, time_t time);
void  KillAdb(void );

/// 查看进程数
int  PSAdb(void);

/// 查看进程数
vector<DWORD>  SearchAdb(void);

const DWORD PIPE_TIME_OUT  = 30*1000;   // 30 seconds

void ConvertGBKToUtf8(CString&  strGBK);
void ConvertUtf8ToGBK(CString&  strUtf8);
int ConvertGBKToUnicode(CString&  strGBK,char * pBuf);
int ConvertUtf8ToUnicode(CString&  strUtf8, char * pBuf);
void Convert(const char* strIn,char* strOut, int sourceCodepage, int targetCodepage);
CString ConvertUnicodeToGBK(unsigned short * pUcs,int nNum);


// 字符串转换函数
wchar_t* ConvertToUnicodeFromUtf8(char *utf8);
char* ConvertFromUnicodeToUtf8(const wchar_t *unicode);

// 把文件时间编码为系统时间格式:yyyy-mm-dd
char* EnCodeFileTimeToSystemTime(FILETIME);

// 文本格式的系统时间解码为文件时间   系统时间格式为:yyyy-mm-dd
FILETIME DeCodeSystemTimeToFileTime(char*);

// 转换短信状态
char* GetSmsState(unsigned short);


//你觉得是个啥，就是个啥
 void runCmdAndResult(LPSTR argCmd, CString& argResult,bool IsReadResult=true);

 // 安装应用程序专用
 //void runAdbInstallApp(LPSTR argCmd, CString& argResult,bool IsReadResult=true);

 //获取当前执行文件目录
 CString GetCurrentDir();

  //获取当前时间
char *  Time2String(char * szDT, time_t time);


// Input: strSrc,原始字符串 abc&defg&123
// strEsc 需要转义的字符串，比如"&"
// strReplaceEsc 代替转义的字符串，比如"&amp;"
// Output: abc&amp;def&amp;123
// 将原始字符串中特殊字符串转化成转义字符串
CString ReplaceStr( CString strSrc, CString strSub, CString strReplace ); // 转义字符处理
/*
// 将所有需要转义的字符串全部转化
CString GetEscChar( CString strSrc );
*/
/**
* @brief   实现字符串替换
* @param   orignStr 源串
* @param   oldStr  查找的串
* @param   newStr  替换的新串
* @return  返回修改后的串
*/
wstring ReplaceWstr(const wstring& orignStr, const wstring& oldStr, const wstring& newStr);
