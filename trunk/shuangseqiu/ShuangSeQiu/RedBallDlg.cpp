// RedBallDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ShuangSeQiu.h"
#include "RedBallDlg.h"

#define TEXT_WIDTH                  20
#define TEXT_HEIGHT                 20
#define ZUOBIAO_WIDTH               50
#define ZUOBIAO_HEIGHT              20
// CRedBallDlg 对话框

IMPLEMENT_DYNAMIC(CRedBallDlg, CDialog)

CRedBallDlg::CRedBallDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRedBallDlg::IDD, pParent)
{
	m_DrawType = DRAW_RED_BALL_1;
	m_DrawIndex = 0;
}

CRedBallDlg::~CRedBallDlg()
{
}

void CRedBallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRedBallDlg, CDialog)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON1, &CRedBallDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CRedBallDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CRedBallDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CRedBallDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CRedBallDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON4, &CRedBallDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON7, &CRedBallDlg::OnBnClickedButton7)
END_MESSAGE_MAP()


// CRedBallDlg 消息处理程序

BOOL CRedBallDlg::OnEraseBkgnd(CDC* pDC)
{
	CDC MemDC;
	CBitmap Bmp;
	CRect Rect;
	GetClientRect(Rect);

	MemDC.CreateCompatibleDC(pDC);
	Bmp.CreateCompatibleBitmap(pDC,Rect.Width(),Rect.Height());
	CBitmap* Old =(CBitmap*)MemDC.SelectObject(&Bmp);
	
	MemDC.FillSolidRect(Rect,RGB(0,0,0));
	DrawZuoBiao(&MemDC,Rect);
	
	if(m_DrawType == DRAW_RED_BALL_1)
	{
		int Width =60*7;
		int Count=Rect.Width()/Width;
		for(int Index=0; Index < Count; Index++)
		{
			int DrawIndex=m_DrawIndex+Index;
			if(DrawIndex >= m_DataList.size())
				break;

			CRect TempRect=Rect;
			TempRect.left=Rect.left+Index*Width;
			TempRect.right=TempRect.left + Width;
			DrawPoint(&MemDC,m_DrawType,TempRect,DrawIndex);
		}
	}
	else
	{
		int Width = 60;
		int Count=Rect.Width()/Width-1;
		for(int Index=0; Index < Count; Index++)
		{
			int DrawIndex=m_DrawIndex+Index;
			if(DrawIndex >= m_DataList.size())
				break;

			CRect TempRect=Rect;
			TempRect.left=Rect.left+Index*Width;
			TempRect.right=TempRect.left + Width;
			DrawPoint(&MemDC,m_DrawType,TempRect,DrawIndex);
		}
	}

	GetClientRect(Rect);
	pDC->BitBlt(0,0,Rect.Width(),Rect.Height(),&MemDC,0,0,SRCCOPY);

	Old=MemDC.SelectObject(Old);
	MemDC.DeleteDC();

	return true;
}

void CRedBallDlg::DrawZuoBiao(CDC* pDC,CRect& Rect)
{
	int Height = TEXT_HEIGHT;
	int Width  = TEXT_WIDTH;

	int HeightH =20;
	int WidthH  = 60;

	CRect LineRect=Rect;
	LineRect.left+=Width+10;

	CPen DotPen(PS_DOT,1,RGB(222,222,222));
	CPen* OldPen=pDC->SelectObject(&DotPen);

	pDC->SetTextColor(RGB(255,0,0));
	for(int Index = 0; Index < 33; Index++)
	{
		CString Text;
		Text.Format("%02d",Index+1);
		CRect TextRect=Rect;
		TextRect.bottom = Rect.bottom-10-(Index+1)*Height -HeightH;
		TextRect.top = TextRect.bottom - Height;
		TextRect.right = TextRect.left + Width;
		
		pDC->MoveTo(LineRect.left,TextRect.bottom);
		pDC->LineTo(LineRect.right,TextRect.bottom);
		TextRect.top = TextRect.bottom-Height/2;
		TextRect.bottom=TextRect.bottom+Height/2;
		pDC->DrawText(Text,TextRect,DT_LEFT|DT_VCENTER);
	}

	LineRect.bottom -= HeightH+10;
	Rect = LineRect;
	pDC->SelectObject(OldPen);


}

void CRedBallDlg::DrawPoint(CDC* pDC,eDrawType Type,CRect Rect,int DrawIndex)
{
	if(m_DataList.empty())
		return;

	int HeightH =20;
	int WidthH  = 60;
	CPen Pen(PS_SOLID,1,RGB(255,0,0));
    CPen* OldPen=(CPen*)pDC->SelectObject(&Pen);
	

	int TempIndex=DrawIndex;
	if(Type == DRAW_RED_BALL_1)
	{
		for(int Index = 0; Index < 6; Index++)
		{
			DWORD Data = m_DataList[TempIndex].m_HongQiu[Index];
			CPoint Point;
			Point.x = Rect.left+(Index+1)*WidthH;
			Point.y = Rect.bottom - Data*HeightH;
			if(Index == 0)
				pDC->MoveTo(Point.x,Point.y);
			else
				pDC->LineTo(Point.x,Point.y);

			//CBursh Bursh(
			CBrush Brush(RGB(167,167,205));
			CBrush* OldBrush=(CBrush*)pDC->SelectObject(&Brush);
			pDC->Ellipse(Point.x-4,Point.y-4,Point.x+4,Point.y+4);
			pDC->SelectObject(OldBrush);
			
			CRect TextRect2=Rect;
			TextRect2.top =Point.y;
			TextRect2.bottom= TextRect2.top + HeightH;
			TextRect2.left =Point.x+4+5;
			TextRect2.right = TextRect2.left + WidthH;
			CString Text2;
			Text2.Format(_T("%02d"),Data);
			pDC->DrawText(Text2,TextRect2,DT_CENTER|DT_VCENTER);

			
			CRect TextRect=Rect;
			TextRect.top =Rect.bottom-10;
			TextRect.bottom= TextRect.top + HeightH;
			TextRect.left = Rect.left + (Index+1)*WidthH;
			TextRect.right = TextRect.left + WidthH;
			CString Text;
			Text.Format("%02d",Index+1);
			pDC->DrawText(Text,TextRect,DT_LEFT|DT_VCENTER);
		}

		CRect TextRect=Rect;
		TextRect.top = Rect.bottom+HeightH-30;
		TextRect.bottom= TextRect.top + HeightH+20;	
		CString Text= m_DataList[TempIndex].m_QiShu;
		pDC->DrawText(Text,TextRect,DT_CENTER|DT_VCENTER);
	}
	else
	{
		//for(int Index = 0; Index < 1; Index++)
		
		int Index=0;
		{
			int iii=0;
			if(Type == DRAW_RED_BALL_3)
				iii=5;
			DWORD Data = m_DataList[TempIndex].m_HongQiu[iii];


			CPoint Point;
			Point.x = Rect.left+(Index+1)*WidthH;
			Point.y = Rect.bottom - Data*HeightH;
			if(TempIndex == m_DrawIndex)
				pDC->MoveTo(Point.x,Point.y);
			else
				pDC->LineTo(Point.x,Point.y);


			CBrush Brush(RGB(167,167,205));
			CBrush* OldBrush=(CBrush*)pDC->SelectObject(&Brush);
			pDC->Ellipse(Point.x-4,Point.y-4,Point.x+4,Point.y+4);
			pDC->SelectObject(OldBrush);
			
			CRect TextRect2=Rect;
			TextRect2.top =Point.y;
			TextRect2.bottom= TextRect2.top + HeightH;
			TextRect2.left =Point.x+4+5;
			TextRect2.right = TextRect2.left + WidthH;
			CString Text2;
			Text2.Format(_T("%02d"),Data);
			pDC->DrawText(Text2,TextRect2,DT_CENTER|DT_VCENTER);

			
			CRect TextRect=Rect;
			TextRect.top =Rect.bottom-10;
			TextRect.bottom= TextRect.top + HeightH;
			TextRect.left = Rect.left + (Index+1)*WidthH;
			TextRect.right = TextRect.left + WidthH;
			CString Text;
			Text.Format("%02d",Index+1);
			pDC->DrawText(Text,TextRect,DT_LEFT|DT_VCENTER);
		}

		CRect TextRect=Rect;
		TextRect.top = Rect.bottom+HeightH-30;
		TextRect.bottom= TextRect.top + HeightH+20;	
		CString Text= m_DataList[TempIndex].m_QiShu;
		pDC->DrawText(Text,TextRect,DT_CENTER|DT_VCENTER);
	}
	pDC->SelectObject(OldPen);
}

void CRedBallDlg::DrawHongQiu(CDC* pDC,eDrawType Type,CRect Rect)
{
	switch(Type)
	{
	case DRAW_RED_BALL_1:
		{
			CPen Pen(PS_SOLID,2,RGB(251,215,209));
			pDC->SelectObject(&Pen);
			DrawPoint(pDC,Type,Rect);
		}
		break;

	case DRAW_RED_BALL_2:
		{
			CPen Pen(PS_SOLID,2,RGB(240,236,64));
			pDC->SelectObject(&Pen);
			DrawPoint(pDC,Type,Rect);
		}
		break;

	case DRAW_RED_BALL_3:
		{
			CPen Pen(PS_SOLID,2,RGB(67,233,87));
			pDC->SelectObject(&Pen);
			DrawPoint(pDC,Type,Rect);
		}
		break;

	case DRAW_RED_BALL_4:
		{
			CPen Pen(PS_SOLID,2,RGB(66,206,234));
			pDC->SelectObject(&Pen);
			DrawPoint(pDC,Type,Rect);
		}
		break;

	case DRAW_RED_BALL_5:
		{
			CPen Pen(PS_SOLID,2,RGB(124,73,227));
			pDC->SelectObject(&Pen);
			DrawPoint(pDC,Type,Rect);
		}
		break;

	case DRAW_RED_BALL_6:
		{
			CPen Pen(PS_SOLID,2,RGB(230,70,196));
			pDC->SelectObject(&Pen);
			DrawPoint(pDC,Type,Rect);
		}
		break;

	case DRAW_RED_BALL_ALL:
		{
			CPen Pen1(PS_SOLID,2,RGB(251,215,209));
			pDC->SelectObject(&Pen1);

			CPen Pen2(PS_SOLID,2,RGB(240,236,64));
			pDC->SelectObject(&Pen2);
			DrawPoint(pDC,Type,Rect);

			CPen Pen3(PS_SOLID,2,RGB(67,233,87));
			pDC->SelectObject(&Pen3);
			DrawPoint(pDC,Type,Rect);

			
			CPen Pen4(PS_SOLID,2,RGB(66,206,234));
			pDC->SelectObject(&Pen4);
			DrawPoint(pDC,Type,Rect);

			CPen Pen5(PS_SOLID,2,RGB(124,73,227));
			pDC->SelectObject(&Pen5);
			DrawPoint(pDC,Type,Rect);

			CPen Pen6(PS_SOLID,2,RGB(230,70,196));
			pDC->SelectObject(&Pen6);
			DrawPoint(pDC,Type,Rect);

		}

		break;
	}
}

void CRedBallDlg::OnBnClickedButton1()
{
	m_DrawType = DRAW_RED_BALL_1;
	Invalidate();
}

void CRedBallDlg::OnBnClickedButton2()
{
	m_DrawType = DRAW_RED_BALL_2;
	Invalidate();
}

void CRedBallDlg::OnBnClickedButton3()
{
	m_DrawType = DRAW_RED_BALL_3;
	Invalidate();
}

void CRedBallDlg::OnBnClickedButton5()
{
	m_DrawType = DRAW_RED_BALL_5;
	Invalidate();
}

void CRedBallDlg::OnBnClickedButton6()
{
	m_DrawType = DRAW_RED_BALL_6;
	Invalidate();
}

void CRedBallDlg::OnBnClickedButton4()
{
	m_DrawType = DRAW_RED_BALL_4;
	Invalidate();
}

void CRedBallDlg::OnBnClickedButton7()
{
	m_DrawType = DRAW_RED_BALL_ALL;
	Invalidate();
}

BOOL CRedBallDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	for(int Index = IDC_BUTTON4; Index <=IDC_BUTTON7; Index++)
	{
		GetDlgItem(Index)->ShowWindow(SW_HIDE);
	}

	return TRUE; 
}

BOOL CRedBallDlg::PreTranslateMessage(MSG* pMsg)
{
	int Offset=2;
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_UP)
		{
			if(m_DrawIndex-Offset>0)
			{
				m_DrawIndex-=Offset;
			}
			else
				m_DrawIndex=0;

			Invalidate();
			return 1;
		}
		else if(pMsg->wParam == VK_DOWN)
		{
			if(m_DrawIndex +Offset < m_DataList.size())
			{
				m_DrawIndex+=Offset;
				
			}
			else
				m_DrawIndex=m_DataList.size()-Offset;
			if(m_DrawIndex < 0)
				m_DrawIndex=0;

			Invalidate();
			return 1;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}
