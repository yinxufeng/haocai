/**************************************************************
*  说明: 用于管理整个界面框架下皮肤元素的类  采用单实例模式   *
*  创建: 吴得绶                                               *
*  时间: 2011-09-14                                           *
***************************************************************/

#pragma once

class CSkinGetElement
{
public:
	static CSkinGetElement *InitSkinInstance();
	
	static void DeleteSkinInstance();

	CFont *GetSpecialFont(int size, int weight=700);

	//获取带下划线的字体
	CFont *GetUnlineFont(int size, int weight=700);

private:
	CSkinGetElement();
	~CSkinGetElement();

	 CString GetCompatibleFontName(bool HasFont=false);

	 //根据操作系统变换字体大小，按照雅黑大小输入，根据操作系统调整大小。宋体字号=雅黑字号-5
	 int	 GetCompatibleFontSize(int orgFontSize,bool fontByOs=true);

protected:

private:
	map<long, CFont *> m_FontMap;
	map<long, CFont* > m_UnlineFontMap;
	static CSkinGetElement *SkinInstance;

};
