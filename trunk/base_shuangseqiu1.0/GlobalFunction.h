#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if !defined(AFX_GRADIENT_H__B34ED849_B7C4_4462_A257_41000D0D7213__INCLUDED_)
#define AFX_GRADIENT_H__B34ED849_B7C4_4462_A257_41000D0D7213__INCLUDED_

//#include "stdafx.h"
//#pragma comment(lib, "Msimg32.lib")	//为API：GradientFill所用

//渐变填充
void GradientFillRect(HDC hdc, const CRect &rt, COLORREF crColor[], int fillType);

//渐变填充
void GradientFillRect(HDC hdc, const CRect &rt,COLORREF crColor1,COLORREF crColor2,int fillType);


//HSL色彩结构
struct COLOR_HSL
{   
    float m_Hue;              // 色相，取值[0,360]   
    float m_Saturation;       // 饱和度，取值[0,1]   
    float m_Luminance;        // 亮度，[0,1]
}; 

//RGB色彩转化成HSL色彩
void RGB2HSL(COLORREF* RGB,DWORD ColorCount,COLOR_HSL* HSL);

//HSL色彩转化成RGB色彩
void HSL2RGB(COLOR_HSL* HSL,DWORD ColorCount,COLORREF* RGB);

#endif // !defined(AFX_GRADIENT_H__B34ED849_B7C4_4462_A257_41000D0D7213__INCLUDED_)