
#include "stdafx.h"
#include "SkinGetElement.h"

enum WinVer
{
    wvUndefined,
    wvWin32s,
    wvWin95,
    wvWin98,
    wvWinME,
    wvWinNT3,
    wvWinNT4,
    wvWin2000,
    wvWinXP,
    wvWinVista,
    wvWin7,

};


WinVer WINAPI GetWinVersion ()
{
    static WinVer s_wvVal = wvUndefined;

    if ( s_wvVal != wvUndefined )
    {
        return s_wvVal;
    }
    OSVERSIONINFO osvi;

    ZeroMemory (&osvi, sizeof OSVERSIONINFO);
    osvi.dwOSVersionInfoSize = sizeof OSVERSIONINFO;

    if ( !GetVersionEx (&osvi) )
    {
        return s_wvVal = wvUndefined;
    }
    if ( osvi.dwPlatformId == VER_PLATFORM_WIN32s )
    {
        return s_wvVal = wvWin32s;
    }
    if ( osvi.dwPlatformId == VER_PLATFORM_WIN32_NT )
    {
        if ( osvi.dwMajorVersion == 4L )
        {
            return s_wvVal = wvWinNT4;
        }
        if ( osvi.dwMajorVersion == 5L && osvi.dwMinorVersion == 0L )
        {
            return s_wvVal = wvWin2000;
        }
        if ( osvi.dwMajorVersion == 5L && osvi.dwMinorVersion == 1L )
        {
            return s_wvVal = wvWinXP;
        }
        if ( osvi.dwMajorVersion == 6L && osvi.dwMinorVersion == 0L )
        {
            return s_wvVal = wvWinVista;
        }
        if ( osvi.dwMajorVersion == 6L && osvi.dwMinorVersion == 1L )
        {
            return s_wvVal = wvWin7;
        }
        return s_wvVal = wvWinNT3;
    }
    ASSERT(osvi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS);

    if ( osvi.dwMajorVersion == 4L && osvi.dwMinorVersion == 10L )
    {
        return s_wvVal = wvWin98;
    }
    if ( osvi.dwMajorVersion == 4L && osvi.dwMinorVersion == 90L )
    {
        return s_wvVal = wvWinME;
    }
    return s_wvVal = wvWin95;
}



CSkinGetElement *CSkinGetElement::SkinInstance = NULL;
CSkinGetElement::CSkinGetElement()
{

}

CSkinGetElement::~CSkinGetElement()
{

	map<long, CFont *>::iterator it = m_FontMap.begin();
	for(; it != m_FontMap.end(); it++)
	{
		it->second->DeleteObject();
		delete it->second;
	}
	m_FontMap.clear();

	it = m_UnlineFontMap.begin();
	for(; it != m_UnlineFontMap.end(); it++)
	{
		it->second->DeleteObject();
		delete it->second;
	}
	m_UnlineFontMap.clear();

}


CSkinGetElement *CSkinGetElement::InitSkinInstance()
{

	if(NULL == SkinInstance)
		SkinInstance = new CSkinGetElement;
	return SkinInstance;

}

void CSkinGetElement::DeleteSkinInstance()
{
	if(NULL != SkinInstance)
		delete SkinInstance;
	SkinInstance = NULL;
}

CFont *CSkinGetElement::GetSpecialFont(int size, int weight)
{
	bool isExcist = TRUE;
	long FontTokens = MAKELONG(size, weight);
	map<long, CFont *>::iterator it;
	if(m_FontMap.size() > 0)
	{
		it = m_FontMap.find(FontTokens);
		if(it != m_FontMap.end())
			return it->second;
		else
			isExcist = FALSE;
	}
	else
		isExcist = FALSE;


	if(!isExcist)
	{
		CFont *SpecialFont = new CFont;
		SpecialFont->CreateFont(GetCompatibleFontSize(size), 0, 0, 0, weight,\
			FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,\
			CLEARTYPE_NATURAL_QUALITY,DEFAULT_PITCH | FF_SWISS, GetCompatibleFontName());
		m_FontMap[FontTokens] = SpecialFont;
		return SpecialFont;
	}

	return NULL;

}

//获取带下划线的字体
CFont *CSkinGetElement::GetUnlineFont(int size, int weight)
{
	bool isExcist = TRUE;
	long FontTokens = MAKELONG(size, weight);
	map<long, CFont *>::iterator it;
	if(m_UnlineFontMap.size() > 0)
	{
		it = m_UnlineFontMap.find(FontTokens);
		if(it != m_UnlineFontMap.end())
			return it->second;
		else
			isExcist = FALSE;
	}
	else
		isExcist = FALSE;


	if(!isExcist)
	{
		CFont *SpecialFont = new CFont;
		SpecialFont->CreateFont(GetCompatibleFontSize(size), 0, 0, 0, weight,\
			FALSE, TRUE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,\
			PROOF_QUALITY,DEFAULT_PITCH | FF_SWISS, GetCompatibleFontName());
		m_UnlineFontMap[FontTokens] = SpecialFont;
		return SpecialFont;
	}

	return NULL;
}

 //根据操作系统给出字体名称，vista及以上是雅黑，以下是宋体
 CString CSkinGetElement::GetCompatibleFontName(bool HasFont)
 {
	WinVer windowsVersion = GetWinVersion();
	if (windowsVersion<=wvWinXP && !HasFont)
	{
		return CString("宋体");
	}
	return CString("微软雅黑");
 }

 //根据操作系统变换字体大小，按照雅黑大小输入，根据操作系统调整大小。宋体字号=雅黑字号-5
 int CSkinGetElement::GetCompatibleFontSize(int orgFontSize,bool fontByOs)
 {
	 if(!fontByOs)
		 return orgFontSize;

	 WinVer windowsVersion = GetWinVersion();
	 if (windowsVersion<=wvWinXP)
	 {
		 return orgFontSize-5;
	 }
	 return orgFontSize;
 }