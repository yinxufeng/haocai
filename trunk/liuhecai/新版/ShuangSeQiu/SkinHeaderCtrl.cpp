// SkinHeaderCtrl.cpp : implementation file
//

#include "stdafx.h"
//#include "TopMost.h"
#include "SkinHeaderCtrl.h"
#include "GlobalFunction.h"
#include <atlbase.h>
#include <atlimage.h>

// CSkinHeaderCtrl
IMPLEMENT_DYNAMIC(CSkinHeaderCtrl, CHeaderCtrl)

CSkinHeaderCtrl::CSkinHeaderCtrl()
{
	m_HeaderShow = true;
	m_DrawRGB = false;
	m_LineWidth = 2;
	m_BkColor = RGB(201,223,244);
	m_LineColor = RGB(142,170,189);
}

CSkinHeaderCtrl::~CSkinHeaderCtrl()
{
}


BEGIN_MESSAGE_MAP(CSkinHeaderCtrl, CHeaderCtrl)
	ON_MESSAGE(HDM_LAYOUT,OnLayout)
	ON_WM_PAINT()
	//ON_NOTIFY(HDN_ITEMCHANGEDA, 0, &CSkinHeaderCtrl::OnHdnItemchanged)
	//ON_NOTIFY(HDN_ITEMCHANGEDW, 0, &CSkinHeaderCtrl::OnHdnItemchanged)
	ON_WM_ERASEBKGND()
	//ON_MESSAGE(HDM_LAYOUT, OnLayout)
END_MESSAGE_MAP()

//LRESULT CSkinHeaderCtrl::OnLayout( WPARAM wParam, LPARAM lParam )
//{
//	LRESULT lResult = CHeaderCtrl::DefWindowProc(HDM_LAYOUT, 0, lParam); 
//	HD_LAYOUT &hdl = *( HD_LAYOUT * ) lParam; 
//	RECT *prc = hdl.prc; 
//	WINDOWPOS *pwpos = hdl.pwpos; 
//	int nHeight = 33;//(int)(pwpos->cy * m_Height); //改变高度,m_Height为倍数
//	pwpos->cy = nHeight; 
//	prc->top = nHeight; 
//	return lResult; 
//}

// CSkinHeaderCtrl message handlers
void CSkinHeaderCtrl::SetItemSortState(int iItem, UINT sortState)
{
	ASSERT(sortState == _nSortUp || sortState == _nSortUp || sortState == _nSortDown);
	ASSERT(m_hWnd != NULL && IsWindow(m_hWnd));

	int nItemCount = GetItemCount();
	ASSERT(iItem >= 0 && iItem < nItemCount);

	HDITEM hditem;
	hditem.mask = HDI_FORMAT;
	GetItem(iItem, &hditem);

	if (sortState == _nSortUp)
	{
		hditem.fmt &= ~HDF_SORTDOWN;
		hditem.fmt |= HDF_SORTUP;
	}
	else
	{
		hditem.fmt &= ~HDF_SORTUP;
		hditem.fmt |= HDF_SORTDOWN;
	}
	SetItem(iItem, &hditem);

	CRect rect;
	GetItemRect(iItem, &rect);
	InvalidateRect(&rect);
}

UINT CSkinHeaderCtrl::GetItemSortState(int iItem)
{
	ASSERT(m_hWnd != NULL && IsWindow(m_hWnd));
	int nItemCount = GetItemCount();
	ASSERT(iItem >= 0 && iItem < nItemCount);

	HDITEM hditem;
	hditem.mask = HDI_FORMAT;
	GetItem(iItem, &hditem);

	if (hditem.fmt & HDF_SORTUP)
	{
		return _nSortUp;
	}
	else if (hditem.fmt & HDF_SORTDOWN)
	{
		return _nSortDown;
	}
	else
	{
		return _nSortNone;
	}
}

LRESULT CSkinHeaderCtrl::OnLayout(WPARAM wParam,LPARAM lParam)
{
	//LRESULT lResult = CHeaderCtrl::DefWindowProc(HDM_LAYOUT, 0, lParam); 
	//HD_LAYOUT &hdl = *(HD_LAYOUT *) lParam; 
	//RECT *prc = hdl.prc; 
	//WINDOWPOS *pwpos = hdl.pwpos; 
	//pwpos->cy = 22; 
	//prc->top = 22;
	//return lResult;

	LRESULT lResult = CHeaderCtrl::DefWindowProc(HDM_LAYOUT, 0, lParam); 
	HD_LAYOUT &hdl = *( HD_LAYOUT * ) lParam; 
	RECT *prc = hdl.prc; 
	WINDOWPOS *pwpos = hdl.pwpos; 
	int nHeight = 24;//(int)(pwpos->cy * m_Height); //改变高度,m_Height为倍数
	pwpos->cy = nHeight; 
	prc->top = nHeight; 
	return lResult; 

}

void CSkinHeaderCtrl::Init()
{
	//ModifyStyle(0, HDS_FLAT | LVS_EX_CHECKBOXES);

}

void CSkinHeaderCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	if(m_HeaderShow)
		DoPaint(&dc);
	else
	{
		CRect Rect;
		GetClientRect(Rect);
		dc.FillSolidRect(Rect,RGB(255,255,255));
	}
}

void CSkinHeaderCtrl::DoPaint(CDC *pDC)
{
	CRect rect, rcItem;
	GetClientRect(&rect);
	
	CDC memDC;
	CBitmap bmp;
	memDC.CreateCompatibleDC(pDC);
	bmp.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	memDC.SelectObject(&bmp);
	memDC.FillSolidRect(rect,RGB(255,255,255));

	memDC.SetBkMode(TRANSPARENT);
	memDC.SetTextColor(RGB(255,255,255));
	
	int nItems = GetItemCount();
	for (int i = 0; i < nItems; ++i)
	{
		TCHAR buf[256];
		HDITEM hditem;

		hditem.mask = HDI_TEXT | HDI_FORMAT | HDI_ORDER;
		hditem.pszText = buf;
		hditem.cchTextMax = 255;
		GetItem(i, &hditem);
		GetItemRect(i, &rcItem);

		if (rcItem.IsRectEmpty())
		{
			continue;
		}

		// 转换
		RectF rcfDestRect;
		rcfDestRect.X = rcItem.left;
		rcfDestRect.Y = rcItem.top;
		rcfDestRect.Width = rcItem.Width();
		rcfDestRect.Height = rcItem.Height();

		//渐变填充
		GradientFillRect(memDC.GetSafeHdc(),rcItem,RGB(100,100,122),RGB(255,0,0),1);
	//	memDC.FillSolidRect(rcItem,m_BkColor);

		CRect LineRect= rcItem;
		LineRect.left=rcItem.right-m_LineWidth;
		LineRect.right=LineRect.left + m_LineWidth;

		// 转换
		rcfDestRect.X = LineRect.left;
		rcfDestRect.Y = LineRect.top;
		rcfDestRect.Width = m_LineWidth;
		rcfDestRect.Height = LineRect.Height();

		//// 绘制 
		//if (m_pImageLine && !m_DrawRGB && m_pImageLineSep)
		//{
		//	Graphics graphicsDisplay(memDC.GetSafeHdc());
		//	
		//	graphicsDisplay.DrawImage(m_pImageLine, rcfDestRect, 0, 0, m_pImageLine->GetWidth(), m_pImageLine->GetHeight(), UnitPixel);
		//	
		//	graphicsDisplay.DrawImage(m_pImageLineSep, rcfDestRect, 0, 0, m_pImageLineSep->GetWidth(), m_pImageLineSep->GetHeight(), UnitPixel);
		//}
		//else
			memDC.FillSolidRect(LineRect,m_LineColor);

		//// 画分割线
		//image.LoadFromResource(AfxGetResourceHandle(), IDB_HEADERCTRL_END_NORMAL);
		//image.Draw(memDC, rcItem.right - 1, rcItem.top);
		//image.Destroy();

		// 画文字和排序箭头
		UINT uFormat = DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_CENTER;
		if (hditem.fmt & HDF_RIGHT)
		{
			uFormat |= DT_CENTER;//DT_RIGHT;
		}
		else if (hditem.fmt & HDF_CENTER)
		{
			uFormat |= DT_CENTER;
		}

		CRect rcText = rcItem;
		if ((hditem.fmt & HDF_SORTUP) | (hditem.fmt & HDF_SORTDOWN))
		{
			rcText.DeflateRect(5, 1, 13, 1);
			memDC.DrawText(buf, static_cast<int> (_tcslen(buf)), &rcText, uFormat);
		}
		else
		{
			rcText.DeflateRect(5, 1, 5, 1);
			memDC.DrawText(buf, static_cast<int>(_tcslen(buf)), &rcText, uFormat);
		}
	}

	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&memDC,0,0,SRCCOPY);
}

void CSkinHeaderCtrl::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class
    Init();
	CHeaderCtrl::PreSubclassWindow();
}

void CSkinHeaderCtrl::OnHdnItemchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	//Invalidate();
	*pResult = 0;
}

BOOL CSkinHeaderCtrl::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
    //return TRUE;
	return CHeaderCtrl::OnEraseBkgnd(pDC);
}

//void CSkinHeaderCtrl::DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/)
//{
//     Invalidate();
//	// TODO:  Add your code to draw the specified item
//}
