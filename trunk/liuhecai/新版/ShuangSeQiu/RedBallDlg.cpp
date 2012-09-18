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
#define V_PAGE_COUNT                 2
#define H_PAGE_COUNT                 4
#define PAGE_COUNT                   (V_PAGE_COUNT*H_PAGE_COUNT)

IMPLEMENT_DYNAMIC(CRedBallDlg, CDialog)

CRedBallDlg::CRedBallDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRedBallDlg::IDD, pParent)
{
	
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
	
	ON_BN_CLICKED(IDC_PREV_BTN, &CRedBallDlg::OnBnClickedPrevBtn)
	ON_BN_CLICKED(IDC_NEXT_BTN, &CRedBallDlg::OnBnClickedNextBtn)
	ON_BN_CLICKED(IDC_FIRST_BTN, &CRedBallDlg::OnBnClickedFirstBtn)
END_MESSAGE_MAP()


// CRedBallDlg 消息处理程序

BOOL CRedBallDlg::OnEraseBkgnd(CDC* pDC)
{
	CDC MemDC;
	CBitmap Bmp;
	CRect Rect;
	GetClientRect(Rect);
	CDialog::OnEraseBkgnd(pDC);

	MemDC.CreateCompatibleDC(pDC);
	Bmp.CreateCompatibleBitmap(pDC,Rect.Width(),Rect.Height());
	CBitmap* Old =(CBitmap*)MemDC.SelectObject(&Bmp);
	
	MemDC.BitBlt(0,0,Rect.Width(),Rect.Height(),pDC,0,0,SRCCOPY);
	

	
	int Height = 210;
	int Width  = 210;
	int TextWidth  =Width;
	int TextHeight =40;
	int SpaceWidth = 20;
	int SpaceHeight=20;
	int OffsetWidth= 80;
	int OffsetHeight=40;

	CRect FrameRect=Rect;
	FrameRect.left  += OffsetWidth-20; 
	FrameRect.right -= OffsetWidth;
	FrameRect.top   += OffsetHeight-20;
	FrameRect.bottom-= OffsetHeight+20;
	DrawFrame(&MemDC,FrameRect,RGB(255,0,0),3);


	if(m_DataList.empty())
		return true;
	int Count=0;

	MemDC.SetBkMode(TRANSPARENT);
	for(int i = 0; i < V_PAGE_COUNT; i++)
	{
		for(int j=0; j < H_PAGE_COUNT; j++)
		{
			
			CRect TempRect=Rect;
			TempRect.left = Rect.left+Width*j+SpaceWidth*j + OffsetWidth;
			TempRect.right = TempRect.left+Width;
			TempRect.top = Rect.top + Height*i +TextHeight*i+OffsetHeight+SpaceHeight*i;
			TempRect.bottom =TempRect.top + Height;
			
			int TempIndex= m_DrawIndex-Count;
			if(TempIndex < 0 || TempIndex >= m_DataList.size())
				break;

			Count++;
			DrawData(&MemDC,TempRect,m_DataList[TempIndex].m_LanQiu);
			

			CString Text;
			Text=m_DataList[TempIndex].m_QiShu;
			CRect TextRect=Rect;
			TextRect.left = Rect.left+Width*j+SpaceWidth*j + OffsetWidth;
			TextRect.right = TextRect.left+Width;
			TextRect.top = Rect.top + Height*(i+1) +TextHeight*i+OffsetHeight+SpaceHeight*i;
			TextRect.bottom =TextRect.top + TextHeight;

			MemDC.DrawText(Text,TextRect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		}

	}

	GetClientRect(Rect);
	pDC->BitBlt(0,0,Rect.Width(),Rect.Height(),&MemDC,0,0,SRCCOPY);

	Old=MemDC.SelectObject(Old);
	MemDC.DeleteDC();

	return true;
}



BOOL CRedBallDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CenterWindow();
	
	return TRUE; 
}

void CRedBallDlg::DrawData(CDC* pDC,CRect Rect,int Data)
{
	int HCount=7;
	int VCount=7;
	int Width = Rect.Width()/HCount;
	int Height= Rect.Width()/VCount;

	int DrawData=0;

	for(int i = 0; i < 7; i++)
	{
		for(int j=0; j < 7; j++)
		{
			DrawData++;
			CRect TempRect=Rect;
			TempRect.left = Rect.left+Width*j;
			TempRect.right = TempRect.left+Width;
			TempRect.top = Rect.top + Height*i;
			TempRect.bottom =TempRect.top + Height;
		    DrawFrame(pDC,TempRect,RGB(255,255,255));

			TempRect.left+=1;
			TempRect.top +=1;
			TempRect.bottom-=1;
			TempRect.right-=1;

			CString Text;
			Text.Format("%02d",DrawData);
			if(DrawData == Data)
				pDC->FillSolidRect(TempRect,RGB(255,0,0));
			pDC->DrawText(Text,TempRect, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		}

	}
}

void CRedBallDlg::DrawFrame(CDC* pDC,CRect TempRect,COLORREF Color,int FrameWidth)
{
	CPen pen(PS_SOLID,FrameWidth,Color);
	pDC->SelectObject(&pen);
	pDC->MoveTo(TempRect.left,TempRect.top);
	pDC->LineTo(TempRect.right,TempRect.top);
	pDC->LineTo(TempRect.right,TempRect.bottom);
	pDC->LineTo(TempRect.left,TempRect.bottom);
	pDC->LineTo(TempRect.left,TempRect.top);
}

BOOL CRedBallDlg::PreTranslateMessage(MSG* pMsg)
{
	/*int Offset=V_PAGE_COUNT*H_PAGE_COUNT;
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
	}*/

	return CDialog::PreTranslateMessage(pMsg);
}

void CRedBallDlg::OnBnClickedPrevBtn()
{
	
	m_DrawIndex+=PAGE_COUNT;
	if(m_DrawIndex >= m_DataList.size())
		m_DrawIndex=m_DataList.size()-1;

	int Count = m_DrawIndex+PAGE_COUNT;
	if(Count >= m_DataList.size()-1)
		Count=m_DataList.size()-1;
	
	UpdateBtnStatus();
	Invalidate();
}

void CRedBallDlg::OnBnClickedNextBtn()
{


	int Count=0;
	 m_DrawIndex-=PAGE_COUNT;
	if(m_DrawIndex < 0)
		m_DrawIndex=0;

	Count= m_DrawIndex+PAGE_COUNT;
	if(Count > m_DataList.size())
		Count=m_DataList.size()-1;

	UpdateBtnStatus();

	Invalidate();
	
	
}



void CRedBallDlg::UpdateBtnStatus()
{
	if(m_DrawIndex + PAGE_COUNT < m_DataList.size())
		GetDlgItem(IDC_PREV_BTN)->EnableWindow(true);
	else
		GetDlgItem(IDC_PREV_BTN)->EnableWindow(false);

	if(m_DrawIndex - PAGE_COUNT < 0)
		GetDlgItem(IDC_NEXT_BTN)->EnableWindow(false);
	else
		GetDlgItem(IDC_NEXT_BTN)->EnableWindow(true);

}
void CRedBallDlg::OnBnClickedFirstBtn()
{
	m_DrawIndex=m_DataList.size()-1;
	if(m_DrawIndex< 0)
		m_DrawIndex=0;
	Invalidate();
}
