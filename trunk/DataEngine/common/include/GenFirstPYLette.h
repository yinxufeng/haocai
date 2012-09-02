/* ------------------------------------------------------------------------- 
//  FileName    :   GenFirstPYLetter.h 
//  Creator     :   debehe 
//  Date        :   2009/9/28 17:40:24 
//  Brief       :   需要用MultiByte才能正确转换 
//                  Unicode转成MultiByte时不要用W2A 
// 
//  $Id: $ 
// -----------------------------------------------------------------------*/  
// How to use:  
//   
// std::wstring strA = L"WPS电子表格";  
// std::wstring strOutput;  
// BOOL bRet = GenFirstPYLetter(strA, strOutput);  
//   
// 结果应该是:  
// strOutput == L"WPSDZBG";  
// bRet == TRUE; // 以字母开头  
  
// -------------------------------------------------------------------------  
  
#ifndef __GETFIRSTLETTER_H__  
#define __GETFIRSTLETTER_H__  
  
#include <Windows.h>  
#include <string>  
using std::string;
// -------------------------------------------------------------------------  
  
/* 
@ Function  : GenFirstPYLetter 
@ brief     : 转换汉字为拼音首字母 
@ parameter : [in]strName 
@ parameter : [out]strResult 
@ return    : 是否以字母开头 
@ remark    :  
@ Date      : 2009/9/28 20:37:19 linyehui 
@*/  
BOOL GenFirstPYLetter(std::string strName, std::string&strResult );  
  
BOOL GenFirstPYLetter(std::wstring strName, std::wstring&strResult);  

string GetPinYinLetter(int nCode); 
// -------------------------------------------------------------------------  
// $Log: $  
  
#endif /* __GETFIRSTLETTER_H__ */