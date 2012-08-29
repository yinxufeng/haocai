
#include "stdafx.h"
#pragma comment(lib, "Msimg32.lib")	//ÎªAPI£ºGradientFillËùÓÃ

#include "GlobalFunction.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


void GradientFillRect(HDC hdc, const CRect &rt,COLORREF crColor1,COLORREF crColor2,int fillType)
{
	COLORREF Color[2]={crColor1,crColor2};
	GradientFillRect(hdc,rt,Color,fillType);
}

void GradientFillRect(HDC hdc, const CRect &rt, COLORREF crColor[], int fillType)
{
	TRIVERTEX        vert[4] ;
	GRADIENT_RECT    gRect;
	vert[0].x      = rt.left;
	vert[0].y      = rt.top;
	vert[0].Red    = (GetRValue(crColor[0]))<<8;
	vert[0].Green  = (GetGValue(crColor[0]))<<8;
	vert[0].Blue   = (GetBValue(crColor[0]))<<8;
	vert[0].Alpha  = 0x0000;
	vert[1].Red    = (GetRValue(crColor[1]))<<8;
	vert[1].Green  = (GetGValue(crColor[1]))<<8;
	vert[1].Blue   = (GetBValue(crColor[1]))<<8;
	vert[1].Alpha  = 0x0000;
	if ( fillType != GRADIENT_FILL_TRIANGLE )
	{
		vert[1].x      = rt.right;
		vert[1].y      = rt.bottom; 
		gRect.UpperLeft  = 0;
		gRect.LowerRight = 1;
		::GradientFill(hdc,vert,2,&gRect,1,fillType);
		return ;
	}
	
	vert[1].x      = rt.right;
	vert[1].y      = rt.top;
	vert[2].x      = rt.left;
	vert[2].y      = rt.bottom;
	vert[2].Red    = (GetRValue(crColor[2]))<<8;
	vert[2].Green  = (GetGValue(crColor[2]))<<8;
	vert[2].Blue   = (GetBValue(crColor[2]))<<8;
	vert[2].Alpha  = 0x0000;
	vert[3].x      = rt.right;
	vert[3].y      = rt.bottom; 
	vert[3].Red    = (GetRValue(crColor[3]))<<8;
	vert[3].Green  = (GetGValue(crColor[3]))<<8;
	vert[3].Blue   = (GetBValue(crColor[3]))<<8;
	vert[3].Alpha  = 0x0000;
	GRADIENT_TRIANGLE GTrg;
	GTrg.Vertex1=0;
	GTrg.Vertex2=1;
	GTrg.Vertex3=2;
	::GradientFill(hdc,vert,4,&GTrg,1,fillType);
	GTrg.Vertex1=1;
	GTrg.Vertex2=2;
	GTrg.Vertex3=3;
	::GradientFill(hdc,vert,4,&GTrg,1,fillType);

}


#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)

/* RGB2HSL:
 *  Converts an RGB value into the HSV colorspace.
 */
void RGB2HSL(COLORREF* RGB,DWORD ColorCount,COLOR_HSL* HSL)
{
	ASSERT(RGB!=NULL && HSL!=NULL && ColorCount>0);

	for(DWORD n=0;n<ColorCount;n++)
	{
		float rc = GetRValue(RGB[n]) / 255.0f;
		float gc = GetGValue(RGB[n]) / 255.0f;
		float bc = GetBValue(RGB[n]) / 255.0f;
		float max = MAX(rc, MAX(gc, bc));
		float min = MIN(rc, MIN(gc, bc));
		float delta = max - min;
		HSL[n].m_Luminance = max;

		if (max != 0.0f)
			HSL[n].m_Saturation = delta / max;
		else
			HSL[n].m_Saturation = 0.0;

		if (HSL[n].m_Saturation == 0.0f)
			HSL[n].m_Hue = 0.0f; 
		else 
		{
			if (rc == max)
				HSL[n].m_Hue = (gc - bc) / delta;
			else if (gc == max)
				HSL[n].m_Hue = 2 + (bc - rc) / delta;
			else if (bc == max)
				HSL[n].m_Hue = 4 + (rc - gc) / delta;

			HSL[n].m_Hue *= 60.0f;
			if (HSL[n].m_Hue < 0)
				HSL[n].m_Hue += 360.0f;
		}
	}
}
/* HSL2RGB:
 *  Converts from HSV colorspace to RGB values.
 */
void HSL2RGB(COLOR_HSL* HSL,DWORD ColorCount,COLORREF* RGB)
{
	for(DWORD n=0;n<ColorCount;n++)
	{
		BYTE r,g,b;
		HSL[n].m_Luminance *= 255.0;
		if (HSL[n].m_Saturation == 0.0)
			r=g=b=(BYTE)HSL[n].m_Luminance;
		else 
		{
			while (HSL[n].m_Hue < 0)
				HSL[n].m_Hue  += 360;
			HSL[n].m_Hue = fmod(HSL[n].m_Hue, 360) / 60.0f;
			int i = (int)HSL[n].m_Hue;
			float f = HSL[n].m_Hue - i;
			float x = HSL[n].m_Luminance * (1.0f - HSL[n].m_Saturation);
			float y = HSL[n].m_Luminance * (1.0f - (HSL[n].m_Saturation * f));
			float z = HSL[n].m_Luminance * (1.0f - (HSL[n].m_Saturation * (1.0f - f)));

			switch (i) 
			{
				case 0: r =(BYTE)HSL[n].m_Luminance; g =(BYTE)z; b =(BYTE)x; break;
				case 1: r =(BYTE)y; g =(BYTE)HSL[n].m_Luminance; b =(BYTE)x; break;
				case 2: r =(BYTE)x; g =(BYTE)HSL[n].m_Luminance; b =(BYTE)z; break;
				case 3: r =(BYTE)x; g =(BYTE)y; b =(BYTE)HSL[n].m_Luminance; break;
				case 4: r =(BYTE)z; g =(BYTE)x; b =(BYTE)HSL[n].m_Luminance; break;
				case 5: r =(BYTE)HSL[n].m_Luminance; g =(BYTE)x; b =(BYTE)y; break;
			}
		}

		RGB[n]=r;
		RGB[n]<<=8;
		RGB[n]+=g;
		RGB[n]<<=8;
		RGB[n]+=b;
	}
}

