// SkinListCtrlEx.cpp : 实现文件
//

#include "stdafx.h"
#include "ListCtrlEx.h"

#define SPACE_WIDTH 3    //空隙

// CListCtrlEx

IMPLEMENT_DYNAMIC(CListCtrlEx, CListCtrl)

CListCtrlEx::CListCtrlEx()
{
	m_RowCount = -1;
	m_ColumnCount = -1;
	m_ButtonHwnd = NULL;
	m_LineColor = RGB(233, 235, 235);
	m_RowHeight = 30;
	m_VecDrawLine=true;
	m_HorDrawLine = true;
	m_CurrentSelectRow = -1;
	m_OldSelectRow = -1;
	m_IsVirtualMode = false;
	m_VirtualID = 0;
	m_ShowVedio = false;
	m_ShowOther = false;
	m_HScrollBar=false;

}

CListCtrlEx::~CListCtrlEx()
{

}


BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_MEASUREITEM_REFLECT()
	ON_WM_LBUTTONUP()
	ON_WM_SIZE()
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, &CListCtrlEx::OnLvnItemchanged)
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

//插入列
int CListCtrlEx::InsertColumn(int nCol,LPCTSTR HeaderStr,int Format,int Width,int Height)
{
//    m_ColumnStyleMap[nCol]=ColoumnStyle;
	m_ColumnCount++;
	return CListCtrl::InsertColumn(nCol,HeaderStr,Format,Width,Height);
}


//插入数据
int CListCtrlEx::InsertItem(int Item, LPCTSTR Str)
{
	m_RowCount++;
	return CListCtrl::InsertItem(Item,Str);
}

//删除数据
BOOL CListCtrlEx::DeleteItem(int Item)
{
	if( CListCtrl::DeleteItem(Item))
	{
		m_RowCount--;
		return TRUE;
	}
	return FALSE;
}

//删除列
BOOL CListCtrlEx::DeleteColumn(int Col)
{
	if( CListCtrl::DeleteColumn(Col) )
	{
		m_ColumnCount--;
		return TRUE;
	}

	return FALSE;
}

//获取整体列显示风格
 bool CListCtrlEx::GetColumStyle(int ColumIndex,sItemStyle& Style)
 {
	 map<int,sItemStyle>::iterator it=m_ColumnStyleMap.find(ColumIndex);
	 if(it != m_ColumnStyleMap.end())
	 {
		 Style=it->second;
		 return true;
	 }

	 return false;
 }

//获取特定单元显示风格
bool CListCtrlEx::GetItemSpeialStyle(int RowIndex, int ColumIndex, sItemStyle& Style)
{
	long Key=MAKELONG(RowIndex,ColumIndex);
	map<long,sItemStyle>::iterator it= m_ItemStyleMap.find(Key);
	if(it != m_ItemStyleMap.end())
	{
		 Style=it->second;
		 return true;
	}

	return false;
}

//设置整体列显示风
void CListCtrlEx::SetColumStyle(int ColumIndex, sItemStyle& Style)
{
	m_ColumnStyleMap[ColumIndex]=Style;
}

//设置单元特定风格
void CListCtrlEx::SetItemSpecialStyle(int RowIndex,int ColoumIndex,sItemStyle& ItemStyle)
{
	long Key=MAKELONG(RowIndex,ColoumIndex);
	m_ItemStyleMap[Key]=ItemStyle;
}

//设置行高
void CListCtrlEx::SetRowHeight(int RowHeight)
{
	m_RowHeight = RowHeight;
	CRect Rect;
	GetWindowRect(&Rect);
	WINDOWPOS WP;
	WP.hwnd = m_hWnd;
	WP.cx = Rect.Width();
	WP.cy = Rect.Height();
	WP.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;

	SendMessage(WM_WINDOWPOSCHANGED, 0, (LPARAM)&WP);

}

//删除所有
BOOL CListCtrlEx::DeleteAllItems()
{
	map<long,sItemStyle>::iterator it=m_ItemStyleMap.begin();
	for(it; it != m_ItemStyleMap.end(); )
	{
		switch(it->second.m_ItemType)
		{
		case IMGE_TYPE:
		//	SAFE_DELETE(it->second.m_DrawData.m_ImageData.m_ActiveImage);
		//	SAFE_DELETE(it->second.m_DrawData.m_ImageData.m_NormalImage);
			break;
		case CHECKBOX_IMAGE_AND_TEXT_TYPE:
			{
				int Row=LOWORD(it->first);
				int Column=HIWORD(it->first);
				if( it->second.m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_IsDeleteNormalImage)
				{
					DeleteImage(it->second.m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_NormalImage);
					it->second.m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_IsDeleteNormalImage = false;
				}

				if( it->second.m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_IsDeleteActiveImage)
				{
					DeleteImage(it->second.m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_ActiveImage);
					it->second.m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_IsDeleteActiveImage = false;
				}
				sItemStyle Style;
			/*	GetColumStyle(Column,Style);
				if(Style.m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_ActiveImage != it->second.m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_ActiveImage)
					DeleteImage(it->second.m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_ActiveImage);
				if(Style.m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_NormalImage != it->second.m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_NormalImage)
					DeleteImage(it->second.m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_NormalImage);*/
			}
		//	it->second.m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_ActiveImage->
			//SAFE_DELETE(it->second.m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_ActiveImage);
		//	SAFE_DELETE(it->second.m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_NormalImage);
			break;
		case IMAGE_AND_TEXT_TYPE:  
		//	DeleteImage(it->second.m_DrawData.m_ImageAndTextData.m_ImageData.m_ActiveImage);
		//	DeleteImage(it->second.m_DrawData.m_ImageAndTextData.m_ImageData.m_NormalImage);
		//	SAFE_DELETE(it->second.m_DrawData.m_ImageAndTextData.m_ImageData.m_ActiveImage);
			//SAFE_DELETE(it->second.m_DrawData.m_ImageAndTextData.m_ImageData.m_NormalImage);
			break;

		}
		it=m_ItemStyleMap.erase(it);
	}

	m_RowIndex.clear();
	m_RowCount = -1;
	return CListCtrl::DeleteAllItems();
}

//删除所有列
BOOL CListCtrlEx::DeleteAllColumn()
{
	if(m_ColumnCount < 0)
		return false;

	for(int Index =0; Index <= m_ColumnCount; Index++)
		CListCtrl::DeleteColumn(0);
	m_ColumnStyleMap.clear();
	m_ColumnCount=-1;
	return true;
}

//删除列
BOOL CListCtrlEx::DeleteColumnStyle(int nCol)
{
	ASSERT( nCol >= 0 && nCol < m_ColumnIndex.size());
	map<int,sItemStyle>::iterator it=m_ColumnStyleMap.find(nCol);
	if(it != m_ColumnStyleMap.end())
	{
		m_ColumnStyleMap.erase(it);
		return true;
	}

	return false;
}


//删除所有列风格
void CListCtrlEx::DeleteAllColumnStyle()
{
	m_ColumnStyleMap.clear();
}

//删除所有行风格
void CListCtrlEx::DeleteAllItemStyle()
{
	m_ItemStyleMap.clear();
}

//删除行
BOOL CListCtrlEx::DeleteItemStyle(int nItem)
{
	BOOL Ret= false;
	for(int Index = 0; Index <= m_ColumnCount; Index++)
	{
		int Key = MAKELONG(nItem,Index);
		map<long,sItemStyle>::iterator it=m_ItemStyleMap.find(Key);
		if(it != m_ItemStyleMap.end() )
		{
			CleanStyle(Index,&it->second);
		//	m_ItemStyleMap.erase(it);
			Ret=true;
		}
	}
	return Ret;
}

//设置复合框状态
BOOL CListCtrlEx::SetCheck(int RowIndex, BOOL Check )
{
	sItemStyle Style;
	map<int,sItemStyle>::iterator it=m_ColumnStyleMap.find(0);
	if(it != m_ColumnStyleMap.end())
		Style=it->second;

	long Key = MAKELONG(RowIndex,0);
	if(Style.m_ItemType  == CHECK_BOX_TYPE)
		Style.m_DrawData.m_CheckBoxData.m_IsCheck = Check;
	else if (Style.m_ItemType == CHECKBOX_IMAGE_AND_TEXT_TYPE)
		Style.m_DrawData.m_CheckBoxImageAndTextData.m_BoxData.m_IsCheck = Check;
	m_ItemStyleMap[Key] = Style;
	
	return CListCtrl::SetCheck(RowIndex,Check);
}

//获取是否选择
BOOL CListCtrlEx::GetCheck(int RowIndex,int ColumIndex)
{
	int Key = MAKELONG(RowIndex,ColumIndex);
	map<long,sItemStyle>::iterator it=m_ItemStyleMap.find(Key);
	if(it != m_ItemStyleMap.end() )
	{
		if(it->second.m_ItemType == CHECK_BOX_TYPE)
			return it->second.m_DrawData.m_CheckBoxData.m_IsCheck;
		else if(it->second.m_ItemType == CHECKBOX_IMAGE_AND_TEXT_TYPE)
			return it->second.m_DrawData.m_CheckBoxImageAndTextData.m_BoxData.m_IsCheck;
	}

	return FALSE;
}

//绘制子项
void CListCtrlEx::DrawSubItem(CDC *pDC, int nItem, int nSubItem, CRect &rSubItem)
{
	CRect Temp=rSubItem;
	DrawBkItem(pDC,nItem,rSubItem);
	long Key = MAKELONG(nItem,nSubItem);
	CRect DrawRect=rSubItem;
	DrawRect.left++;
	DrawRect.top++;
	DrawRect.right--;
	DrawRect.bottom--;
	map<long,sItemStyle>::iterator it=m_ItemStyleMap.find(Key);
	if(it != m_ItemStyleMap.end())
	{
		if(m_ShowVedio)
		{
			//绘制视频的新显示方式
			DrawShowVedio(pDC,nItem,nSubItem,DrawRect,&it->second);
		}
		else
			DrawByStyle(pDC,nItem,nSubItem,DrawRect,&it->second);
	}
	else
	{
		map<int,sItemStyle>::iterator ItemIt=m_ColumnStyleMap.find(nSubItem);
		if(ItemIt != m_ColumnStyleMap.end())
		{
			DrawByStyle(pDC,nItem,nSubItem,DrawRect,&ItemIt->second);
		}
	}
	
}

//自绘函数
void CListCtrlEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CPoint Point;
	CRect Rect = lpDrawItemStruct->rcItem;
	CRect ClientRect;
	GetItemRect(0,ClientRect,LVIR_BOUNDS);
	
	int RowIndex=0;
	if(Rect.top != ClientRect.top )
	{
		RowIndex=(Rect.top-ClientRect.top)/m_RowHeight; 
		if((Rect.top-ClientRect.top)%m_RowHeight)
			RowIndex+=1;
	}
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);
	//CRect fillRect = Rect;
	//fillRect.InflateRect(1,1,1,1);
	//dc.FillSolidRect(Rect, (COLORREF)RGB(0xff, 0xff, 0xff));
	
	
	int Offset=0;
	for(int ColumnIndex = 0; ColumnIndex <= m_ColumnCount; ColumnIndex++)
	{
		CRect TempRect=Rect;
		int Width =GetColumnWidth(ColumnIndex);
		TempRect.left= Offset;
		TempRect.right = Offset + Width;
		Offset+=Width;
		//Rect = TempRect;
		//Rect.InflateRect(1,1,2,2);
		dc.FillSolidRect(TempRect, (COLORREF)RGB(0xff, 0xff, 0xff));
		if(lpDrawItemStruct->itemID%2 && m_ShowOther)
		{
			dc.FillSolidRect(TempRect, (COLORREF)RGB(0xe8, 0xe8, 0xe8));
		}
		DrawSubItem(&dc,RowIndex,ColumnIndex,TempRect);	
	}
	CRect tRect = Rect;
	tRect.top = tRect.bottom - 1;
	tRect.bottom += 1;
	dc.FillSolidRect(tRect, (COLORREF)RGB(0xff, 0xff, 0xff));
	tRect = Rect;
	tRect.left = Rect.right - 1;
	tRect.right += 1;
	dc.FillSolidRect(tRect, (COLORREF)RGB(0xff, 0xff, 0xff));
	if(lpDrawItemStruct->itemID%2 && m_ShowOther)
	{
		tRect = Rect;
		tRect.top = tRect.bottom - 1;
		tRect.bottom += 1;
		dc.FillSolidRect(tRect, (COLORREF)RGB(0xe8, 0xe8, 0xe8));
		tRect = Rect;
		tRect.left = Rect.right - 1;
		tRect.right += 1;
		dc.FillSolidRect(tRect, (COLORREF)RGB(0xe8, 0xe8, 0xe8));
		
	}
	//while(Rect.bottom + m_RowHeight < ClientRect.bottom)
	//{
	//	dc.MoveTo(Rect.left,Rect.bottom);
	//	dc.LineTo(Rect.right,Rect.bottom);
	//	Rect.bottom+=m_RowHeight;
	//}
	dc.Detach();
}


void CListCtrlEx::DrawShowVedio(CDC *pDC, int nItem, int nSubItem, CRect &rSubItem, sItemStyle *pStyle)
{
	if(!pStyle)
		return;

	Graphics Display(pDC->GetSafeHdc());
	switch(pStyle->m_ItemType)
	{
		case CHECKBOX_IMAGE_AND_TEXT_TYPE:
		{
			CString Text;
            Text = GetItemText(nItem, nSubItem);
			int pos = Text.Find('+');
			CString Name = Text.Mid(0, pos);
			int sPos = Text.Find('+', pos+1);
			CString size = _T("大小:");
			size += Text.Mid(pos+1, sPos-pos-1);
			CString format = _T("格式:");
			format += Text.Mid(sPos+1);
			size += _T("   ");
			size += format;

			pDC->SetTextColor(pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_TextData.m_TextColor);
			Image* pCheckBoxImage = pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_BoxData.m_IsCheck ? pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_BoxData.m_CheckBoxSelectedImage : pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_BoxData.m_CheckBoxUnSelectedImage;
			Image* pImage=pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_IsNormal ? pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_NormalImage : pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_ActiveImage;
			if(pCheckBoxImage && pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_DrawStyle != TEXT_UP_IMAGE_DOWN && pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_DrawStyle != TEXT_DOWN_IMAGE_UP)
			{
				CPoint Point=GetImageDrawPoint(pCheckBoxImage,rSubItem);
				//Point.x = (rSubItem.Width() - pImage->GetWidth())/2;
				Display.DrawImage(pCheckBoxImage,Point.x,Point.y);
				rSubItem.left=Point.x + pCheckBoxImage->GetWidth()+SPACE_WIDTH;
			}
			if(pImage && pImage->GetLastStatus() == Ok)
			{
				CRect TextRect;
				CRect ImageRect;
				CRect sLineText;
				if(pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_BoxData.m_IsCheck)
				{
					COLORREF bkColor = RGB(0xc8, 0xe9, 0xfb);//如果是获得焦点则绘制背景
					pDC->FillSolidRect(rSubItem, bkColor);
					pDC->SetTextColor((COLORREF)RGB(0x00, 0x5e, 0xff));
				}
				GetVedioImageTextRect(pImage,rSubItem,ImageRect,TextRect,pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_DrawStyle);
				if( pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_DrawStyle == TEXT_UP_IMAGE_DOWN || pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_DrawStyle == TEXT_DOWN_IMAGE_UP)
				{
					CPoint Point=GetImageDrawPoint(pCheckBoxImage,TextRect);
					Point.x = TextRect.left + (TextRect.Width() - pImage->GetWidth())/2;
			    	Display.DrawImage(pCheckBoxImage,Point.x,Point.y);
					TextRect.left=Point.x + pCheckBoxImage->GetWidth();
					TextRect.right = TextRect.left + pImage->GetWidth();
					sLineText = rSubItem;
					sLineText.top += 165;
				}
				RectF DrawRect = RectToRectF(ImageRect);
				Display.DrawImage(pImage,DrawRect);
				//pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_TextData.m_TextFormat = DT_SINGLELINE | DT_LEFT| DT_VCENTER | DT_END_ELLIPSIS;
				pDC->DrawText(Name,TextRect,pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_TextData.m_TextFormat);
				pDC->DrawText(size,sLineText,pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_TextData.m_TextFormat);
			}

		}
		break;
	default:
		break;
	}
	Display.ReleaseHDC(pDC->GetSafeHdc());

}
//绘制
void CListCtrlEx::DrawByStyle(CDC* pDC,int nItem,int nSubItem,CRect& rSubItem,sItemStyle* pStyle)
{
	if(!pStyle)
		return;

	Graphics Display(pDC->GetSafeHdc());
	switch(pStyle->m_ItemType)
	{
	case TEXT_TYPE:
		{
			CString Text;
            Text = GetItemText(nItem, nSubItem);
			if(pStyle->m_DrawData.m_TextData.m_IsFillBG)
				pDC->FillSolidRect(rSubItem,pStyle->m_DrawData.m_TextData.m_BGColor);

			pDC->SetTextColor(pStyle->m_DrawData.m_TextData.m_TextColor);
			pDC->DrawText(Text, &rSubItem,pStyle->m_DrawData.m_TextData.m_TextFormat);
			
		}
		break;

	case BUTTON_TYPE:
		{
			Image* pImage= pStyle->m_DrawData.m_ButtonData.m_IsNormal ?  pStyle->m_DrawData.m_ButtonData.m_ButtonNormalImage : pStyle->m_DrawData.m_ButtonData.m_ButtonActiveImage;
			if(pImage)
			{
				CRect TempRect = GetImageDrawRect(pImage,rSubItem);
				RectF DrawRect = RectToRectF(TempRect);
				Display.DrawImage(pImage,DrawRect);
				if(pStyle->m_DrawData.m_ButtonData.m_HasText)
				{
					CString Text;
					Text = GetItemText(nItem, nSubItem);
					pDC->SetTextColor(pStyle->m_DrawData.m_ButtonData.m_TextData.m_TextColor);
				    pDC->DrawText(Text, &TempRect,pStyle->m_DrawData.m_ButtonData.m_TextData.m_TextFormat);
				}
				
			}
			else if(pStyle->m_DrawData.m_ButtonData.m_HasText)
			{
				CString Text;
				Text = GetItemText(nItem, nSubItem);
				pDC->SetTextColor(pStyle->m_DrawData.m_ButtonData.m_TextData.m_TextColor);
				pDC->DrawText(Text, &rSubItem,pStyle->m_DrawData.m_ButtonData.m_TextData.m_TextFormat);
			}
		}
		break;

	case CHECK_BOX_TYPE:
		{
			Image* pImage = pStyle->m_DrawData.m_CheckBoxData.m_IsCheck ? pStyle->m_DrawData.m_CheckBoxData.m_CheckBoxSelectedImage : pStyle->m_DrawData.m_CheckBoxData.m_CheckBoxUnSelectedImage;
			if(pImage)
			{
				
				if(pStyle->m_DrawData.m_CheckBoxData.m_HasText)
				{
					CRect TextRect;
					CRect ImageRect;

					GetTextAndImageDrawRect(pImage,rSubItem,ImageRect,TextRect,pStyle->m_DrawData.m_CheckBoxData.m_DrawStyle);
					ImageRect=GetImageDrawRect(pImage,ImageRect);
				    RectF DrawRect = RectToRectF(ImageRect);
				    Display.DrawImage(pImage,DrawRect);

					CString Text = GetItemText(nItem, nSubItem);
					pDC->SetTextColor(pStyle->m_DrawData.m_CheckBoxData.m_TextData.m_TextColor);
					pDC->DrawText(Text, &TextRect,pStyle->m_DrawData.m_CheckBoxData.m_TextData.m_TextFormat);
				}
				else
				{
					CRect TempRect = GetImageDrawRect(pImage,rSubItem);
				    RectF DrawRect = RectToRectF(TempRect);
				    Display.DrawImage(pImage,DrawRect);
				}
			}
			//checkbox and text
			/*CString Text;
            Text = GetItemText(nItem, nSubItem);
			pDC->SetTextColor(pStyle->m_DrawData.m_ImageAndTextData.m_TextData.m_TextColor);
			Image* pCheckBoxImage = pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_BoxData.m_IsCheck ? pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_BoxData.m_CheckBoxSelectedImage : pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_BoxData.m_CheckBoxUnSelectedImage;
			if(pCheckBoxImage)
			{
				CPoint Point=GetImageDrawPoint(pCheckBoxImage,rSubItem);
				Display.DrawImage(pCheckBoxImage,Point.x,Point.y);
				rSubItem.left=Point.x + pCheckBoxImage->GetWidth();
			}
			Image* pImage=pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_IsNormal ? pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_NormalImage : pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_ActiveImage;
		    if(pImage)
			{

				CString Text = GetItemText(nItem, nSubItem);
				pDC->SetTextColor(pStyle->m_DrawData.m_ButtonData.m_TextData.m_TextColor);
				pDC->DrawText(Text, &rSubItem,pStyle->m_DrawData.m_ButtonData.m_TextData.m_TextFormat);
			}	*/
		}
		break;
	case IMGE_TYPE:
		{
			Image* pImage = pStyle->m_DrawData.m_ImageData.m_IsNormal ? pStyle->m_DrawData.m_ImageData.m_NormalImage :  pStyle->m_DrawData.m_ImageData.m_ActiveImage;
			if(pImage)
			{
				CRect TempRect = GetImageDrawRect(pImage,rSubItem);
				RectF DrawRect = RectToRectF(TempRect);
				Display.DrawImage(pImage,DrawRect);
			}
		}
		break;
	case CHECKBOX_IMAGE_AND_TEXT_TYPE:
		{
			CString Text;
            Text = GetItemText(nItem, nSubItem);
			pDC->SetTextColor(pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_TextData.m_TextColor);
			Image* pCheckBoxImage = pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_BoxData.m_IsCheck ? pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_BoxData.m_CheckBoxSelectedImage : pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_BoxData.m_CheckBoxUnSelectedImage;
			if(pCheckBoxImage && pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_DrawStyle != TEXT_UP_IMAGE_DOWN && pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_DrawStyle != TEXT_DOWN_IMAGE_UP)
			{
				CPoint Point=GetImageDrawPoint(pCheckBoxImage,rSubItem);
				Display.DrawImage(pCheckBoxImage,Point.x,Point.y);
				rSubItem.left=Point.x + pCheckBoxImage->GetWidth()+SPACE_WIDTH;
			}
			if(pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_BoxData.m_IsCheck && (pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_DrawStyle == TEXT_UP_IMAGE_DOWN || pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_DrawStyle == TEXT_DOWN_IMAGE_UP))
			{
				COLORREF bkColor = RGB(0xc8, 0xe9, 0xfb);//如果是获得焦点则绘制背景
				pDC->FillSolidRect(rSubItem, bkColor);
				pDC->SetTextColor((COLORREF)RGB(0x00, 0x5e, 0xff));
			}
			Image* pImage=pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_IsNormal ? pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_NormalImage : pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_ActiveImage;
			if(pImage && pImage->GetLastStatus() == Ok)
			{
				CRect TextRect;
				CRect ImageRect;
				GetTextAndImageDrawRect(pImage,rSubItem,ImageRect,TextRect,pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_DrawStyle);
				if( pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_DrawStyle == TEXT_UP_IMAGE_DOWN || pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_DrawStyle == TEXT_DOWN_IMAGE_UP)
				{
					CPoint Point=GetImageDrawPoint(pCheckBoxImage,TextRect);
			    	Display.DrawImage(pCheckBoxImage,Point.x,Point.y);
					TextRect.left=Point.x + pCheckBoxImage->GetWidth();
				}
				RectF DrawRect = RectToRectF(ImageRect);
				Display.DrawImage(pImage,DrawRect);
				pDC->DrawText(Text,TextRect,pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_TextData.m_TextFormat);
			}

		}
		break;
	case IMAGE_AND_TEXT_TYPE:
		{
			CString Text;
            Text = GetItemText(nItem, nSubItem);
			pDC->SetTextColor(pStyle->m_DrawData.m_ImageAndTextData.m_TextData.m_TextColor);
		    Image* pImage=pStyle->m_DrawData.m_ImageAndTextData.m_ImageData.m_IsNormal ? pStyle->m_DrawData.m_ImageAndTextData.m_ImageData.m_NormalImage : pStyle->m_DrawData.m_ImageAndTextData.m_ImageData.m_ActiveImage;
			if(pImage)
	    	{
				CRect TextRect;
				CRect ImageRect;
				GetTextAndImageDrawRect(pImage,rSubItem,ImageRect,TextRect,pStyle->m_DrawData.m_ImageAndTextData.m_DrawStyle);
				RectF DrawRect = RectToRectF(ImageRect);
				Display.DrawImage(pImage,DrawRect);
				pDC->DrawText(Text,TextRect,pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_TextData.m_TextFormat);
			}
		}
		break;
	default:
		break;
	}

	Display.ReleaseHDC(pDC->GetSafeHdc());
}

	
//获取图片绘制区域
CRect CListCtrlEx::GetImageDrawRect(Image* pImage,CRect Rect)
{
	ASSERT(pImage != NULL);
	CRect TempRect  = Rect;
	int ImageWidth  = pImage->GetWidth();
	int ImageHeight = pImage->GetHeight();
	int RectWidth   = Rect.Width();
	int RectHeight  = Rect.Height();

	if(ImageWidth < RectWidth)
	{
		TempRect.left = Rect.left + (RectWidth-ImageWidth)/2;
		TempRect.right = TempRect.left + ImageWidth;
	}

	if(ImageHeight < RectHeight)
	{
		TempRect.top = Rect.top + (RectHeight-ImageHeight)/2;
		TempRect.bottom = TempRect.top + ImageHeight;
	}

	return TempRect;
	
}

//获取文本绘制区域
CRect CListCtrlEx::GetTextDrawRect(Image* pImage,CRect Rect,eDrawStyle Style)
{
	
	CRect TempRect  = Rect;
	if(pImage == NULL)
		return TempRect;
	int ImageWidth  = pImage->GetWidth();
	int ImageHeight = pImage->GetHeight();
	int RectWidth   = Rect.Width();
	int RectHeight  = Rect.Height();

	switch(Style)
	{
	case TEXT_LEFT_IMAGE_RIGHT:
		TempRect.left = Rect.left;
		TempRect.right = TempRect.left + RectWidth-ImageWidth;
		break;

	case TEXT_RIGHT_IMAGE_LEFT:
		TempRect.left = Rect.left + ImageWidth;
		TempRect.right= Rect.right;
		break;

	case TEXT_UP_IMAGE_DOWN:
		TempRect.top= Rect.top;
		TempRect.bottom = Rect.top + RectHeight - ImageHeight;
		break;

	case TEXT_DOWN_IMAGE_UP:
		TempRect.top = Rect.top+ImageHeight;
		TempRect.bottom = Rect.bottom;
		break;

	case TEXT_ON_IMAGE:
	default:
		break;
	}

	return TempRect;
}

void CListCtrlEx::GetVedioImageTextRect(Image* pImage,CRect Rect,CRect& ImageRect,CRect& TextRect,eDrawStyle Style)
{
	if(pImage == NULL)
		return;

	ASSERT(pImage != NULL);
	TextRect  = Rect;
	ImageRect = Rect;
	int ImageWidth  = pImage->GetWidth();
	int ImageHeight = pImage->GetHeight();
	int RectWidth   = Rect.Width();
	int RectHeight  = Rect.Height();
	int HeightOffset = (RectHeight-ImageHeight)/2;
	if(HeightOffset < 0)
		HeightOffset = 0;
	int WidthOffset = (RectWidth - ImageWidth)/2;
	if(WidthOffset < 0)
		WidthOffset = 0;

	switch(Style)
	{
		case TEXT_DOWN_IMAGE_UP:
		ImageRect.top += 18/*ImageRect.bottom-ImageHeight*/;
		ImageRect.bottom = ImageRect.top + ImageHeight;
		ImageRect.left =Rect.left + WidthOffset ;
		ImageRect.right = ImageRect.left+ImageWidth;
		TextRect.left = ImageRect.left;
		TextRect.right = ImageRect.right;
		TextRect.top = ImageRect.bottom + 5;//Rect.top+ImageHeight;
		TextRect.bottom = TextRect.top + 16;
		break;

		default:
			break;
	}

}

void CListCtrlEx::GetTextAndImageDrawRect(Image* pImage,CRect Rect,CRect& ImageRect,CRect& TextRect,eDrawStyle Style)
{
	if(pImage == NULL)
		return;

	ASSERT(pImage != NULL);
	TextRect  = Rect;
	ImageRect = Rect;
	int ImageWidth  = pImage->GetWidth();
	int ImageHeight = pImage->GetHeight();
	int RectWidth   = Rect.Width();
	int RectHeight  = Rect.Height();
	int HeightOffset = (RectHeight-ImageHeight)/2;
	if(HeightOffset < 0)
		HeightOffset = 0;
	int WidthOffset = (RectWidth - ImageWidth)/2;
	if(WidthOffset < 0)
		WidthOffset = 0;

	switch(Style)
	{
	case TEXT_LEFT_IMAGE_RIGHT:
		TextRect.left = Rect.left;
		TextRect.right = TextRect.left + RectWidth-ImageWidth;
		ImageRect.left = TextRect.right+SPACE_WIDTH;
		ImageRect.right = ImageRect.left+ImageWidth;
		ImageRect.top+=HeightOffset;
		ImageRect.bottom=ImageRect.top+ImageHeight;
		break;

	case TEXT_RIGHT_IMAGE_LEFT:
		TextRect.left = Rect.left + ImageWidth+16 + 16;
		TextRect.right= Rect.right;
		ImageRect.right = Rect.left + ImageWidth + 16;
		ImageRect.left =ImageRect.right - ImageWidth ;
		ImageRect.top+=HeightOffset;
		ImageRect.bottom=ImageRect.top+ImageHeight;

		break;

	case TEXT_UP_IMAGE_DOWN:
		TextRect.top= Rect.top;
		TextRect.bottom = Rect.top + RectHeight - ImageHeight;
		ImageRect.top = TextRect.bottom;
		ImageRect.left =Rect.left + WidthOffset ;
		ImageRect.right = ImageRect.left+ImageWidth;
		ImageRect.bottom=ImageRect.top+ImageHeight;
		break;

	case TEXT_DOWN_IMAGE_UP:
		ImageRect.top += SPACE_WIDTH + 10;/*ImageRect.bottom-ImageHeight*/;
		ImageRect.bottom = ImageRect.top + ImageHeight;
		ImageRect.left =Rect.left + WidthOffset ;
		ImageRect.right = ImageRect.left+ImageWidth;
		TextRect.left = ImageRect.left;
		TextRect.right = ImageRect.right;
		TextRect.top = ImageRect.bottom + SPACE_WIDTH + 2;//Rect.top+ImageHeight;
		TextRect.bottom = Rect.bottom;
		break;

	case TEXT_ON_IMAGE:
	default:
		break;
	}

}

//获取图片绘制点
CPoint CListCtrlEx::GetImageDrawPoint(Image* pImage,CRect Rect)
{
	CPoint Point;
	Point.x = Rect.left;
	Point.y = Rect.top;

	if(pImage == NULL)
		return Point;

	int ImageHeight = pImage->GetHeight();
	int RectHeight  = Rect.Height();
	
	if(ImageHeight < RectHeight)
		Point.y = Rect.top + (RectHeight - ImageHeight)/2;
	return Point;
}

//Rect 到 RectF 的转换
RectF CListCtrlEx::RectToRectF(CRect Rect)
{
	RectF Temp;
	Temp.X = Rect.left;
	Temp.Y = Rect.top;
	Temp.Width = Rect.Width();
	Temp.Height = Rect.Height();
	return Temp;
}

void CListCtrlEx::OnLButtonDown(UINT nFlags, CPoint point)
{
	int RowIndex = 0;
	int ColumnIndex = 0;
	CRect SubRect;
	bool IsFind=FindRowAndColumnPos(point,RowIndex,ColumnIndex,SubRect);
	if(IsFind)
	{
		long Key = MAKELONG(RowIndex,ColumnIndex);
		map<long,sItemStyle>::iterator it=m_ItemStyleMap.find(Key);
		if(it != m_ItemStyleMap.end())
		{
			switch(it->second.m_ItemType)
			{
				case BUTTON_TYPE:
					{
						CRect ButtonRect=GetImageDrawRect(it->second.m_DrawData.m_ButtonData.m_ButtonNormalImage,SubRect);
						if(ButtonRect.PtInRect(point) )
						{
							if(m_ButtonHwnd == NULL)
								m_ButtonHwnd = GetParent()->GetSafeHwnd();
							::PostMessage(m_ButtonHwnd,WM_LIST_BUTTON_CLICK,RowIndex,ColumnIndex);
							it->second.m_DrawData.m_ButtonData.m_IsNormal = false;
							CRect RowRect;
							GetItemRect(RowIndex,RowRect,LVIR_BOUNDS);
							InvalidateRect(RowRect);
						}
					}
					break;
				case CHECK_BOX_TYPE:
					{
						CRect TextRect;
						CRect ImageRect;
						CRect RowRect;
		                GetItemRect(RowIndex,RowRect,LVIR_BOUNDS);
						Image* pImage = it->second.m_DrawData.m_CheckBoxData.m_CheckBoxUnSelectedImage;
						GetTextAndImageDrawRect(pImage,RowRect,ImageRect,TextRect,it->second.m_DrawData.m_CheckBoxData.m_DrawStyle);
						ImageRect=GetImageDrawRect(pImage,ImageRect);

						if(ImageRect.PtInRect(point))
						{
							it->second.m_DrawData.m_CheckBoxData.m_IsCheck = !it->second.m_DrawData.m_CheckBoxData.m_IsCheck;
							
							InvalidateRect(RowRect);
						}
						//列表点击事件 勾选框
						else
							::PostMessage(m_ButtonHwnd,WM_LIST_CHECKBOX_CLICK,RowIndex,ColumnIndex);
					}
					break;
				case CHECKBOX_IMAGE_AND_TEXT_TYPE:
					{
						CRect TempRect;
						CPoint Point;
						if(it->second.m_DrawData.m_CheckBoxImageAndTextData.m_DrawStyle != TEXT_UP_IMAGE_DOWN && it->second.m_DrawData.m_CheckBoxImageAndTextData.m_DrawStyle != TEXT_DOWN_IMAGE_UP)
							Point=GetImageDrawPoint(it->second.m_DrawData.m_CheckBoxImageAndTextData.m_BoxData.m_CheckBoxUnSelectedImage,SubRect);

						if(it->second.m_DrawData.m_CheckBoxImageAndTextData.m_DrawStyle == TEXT_UP_IMAGE_DOWN || it->second.m_DrawData.m_CheckBoxImageAndTextData.m_DrawStyle == TEXT_DOWN_IMAGE_UP)
						{
							CRect TextRect;
							CRect ImageRect;
							if(m_ShowVedio)
								GetVedioImageTextRect(it->second.m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_NormalImage,SubRect,ImageRect,TextRect,it->second.m_DrawData.m_CheckBoxImageAndTextData.m_DrawStyle);
							else
								GetTextAndImageDrawRect(it->second.m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_NormalImage,SubRect,ImageRect,TextRect,it->second.m_DrawData.m_CheckBoxImageAndTextData.m_DrawStyle);
							Point=GetImageDrawPoint(it->second.m_DrawData.m_CheckBoxImageAndTextData.m_BoxData.m_CheckBoxUnSelectedImage,TextRect);
					    }
					
					
			        	TempRect.left = Point.x;
						TempRect.top = Point.y;
						TempRect.right=TempRect.left+it->second.m_DrawData.m_CheckBoxImageAndTextData.m_BoxData.m_CheckBoxUnSelectedImage->GetWidth();
						TempRect.bottom = TempRect.top+it->second.m_DrawData.m_CheckBoxImageAndTextData.m_BoxData.m_CheckBoxUnSelectedImage->GetHeight();
						
						if(TempRect.PtInRect(point) )
						{
						    it->second.m_DrawData.m_CheckBoxImageAndTextData.m_BoxData.m_IsCheck = !it->second.m_DrawData.m_CheckBoxImageAndTextData.m_BoxData.m_IsCheck;
						}
						//列表点击事件 勾选框
						else
							::PostMessage(m_ButtonHwnd,WM_LIST_CHECKBOX_CLICK,RowIndex,ColumnIndex);

						if(it->second.m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_IsTouchClickMsg)
						{
							Image* pImage = it->second.m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_NormalImage;
							CRect TextRect;
							CRect ImageRect;
							TempRect.left=TempRect.right;
							TempRect.right=SubRect.right;
							TempRect.top = SubRect.top;
							TempRect.bottom = SubRect.bottom;
							GetTextAndImageDrawRect(pImage,TempRect,ImageRect,TextRect,it->second.m_DrawData.m_CheckBoxImageAndTextData.m_DrawStyle);
							if( ImageRect.PtInRect(point))
							{

								if(m_ButtonHwnd == NULL)
									m_ButtonHwnd = GetParent()->GetSafeHwnd();
								::PostMessage(m_ButtonHwnd,WM_LIST_BUTTON_CLICK,RowIndex,ColumnIndex);
							}
						}

						InvalidateRect(SubRect);
					}
					break;
				case IMGE_TYPE:
					{
						it->second.m_DrawData.m_ImageData.m_IsNormal = false;
						if(it->second.m_DrawData.m_ImageData.m_IsTouchClickMsg)
						{
							if(m_ButtonHwnd == NULL)
								m_ButtonHwnd = GetParent()->GetSafeHwnd();
							::PostMessage(m_ButtonHwnd,WM_LIST_BUTTON_CLICK,RowIndex,ColumnIndex);
							
						}

						CRect RowRect;
						GetItemRect(RowIndex,RowRect,LVIR_BOUNDS);
						InvalidateRect(RowRect);
					}
					break;

				case IMAGE_AND_TEXT_TYPE:
					{
						it->second.m_DrawData.m_ImageAndTextData.m_ImageData.m_IsNormal= false;
						if(it->second.m_DrawData.m_ImageAndTextData.m_ImageData.m_IsTouchClickMsg)
						{
							if(m_ButtonHwnd == NULL)
								m_ButtonHwnd = GetParent()->GetSafeHwnd();
							::PostMessage(m_ButtonHwnd,WM_LIST_BUTTON_CLICK,RowIndex,ColumnIndex);
						}
						CRect RowRect;
						GetItemRect(RowIndex,RowRect,LVIR_BOUNDS);
						InvalidateRect(RowRect);
					}
					break;
				default:
					break;
			}
		}
		else
		{
			map<int,sItemStyle>::iterator ItemIt = m_ColumnStyleMap.find(ColumnIndex);
			if(ItemIt != m_ColumnStyleMap.end())
			{
				switch(ItemIt->second.m_ItemType)
				{
					case BUTTON_TYPE:
						{
							CRect ButtonRect=GetImageDrawRect(ItemIt->second.m_DrawData.m_ButtonData.m_ButtonNormalImage,SubRect);
							if(ButtonRect.PtInRect(point) )
							{
								if(m_ButtonHwnd == NULL)
									m_ButtonHwnd = GetParent()->GetSafeHwnd();

							     ::PostMessage(m_ButtonHwnd,WM_LIST_BUTTON_CLICK,RowIndex,ColumnIndex);
								  m_ItemStyleMap[Key]=ItemIt->second;
								  m_ItemStyleMap[Key].m_DrawData.m_ButtonData.m_IsNormal = false;
								  CRect RowRect;
								  GetItemRect(RowIndex,RowRect,LVIR_BOUNDS);
								  InvalidateRect(RowRect);
							  
							}
					  
						}
						break;
					case CHECK_BOX_TYPE:
						{
							CRect TextRect;
							CRect ImageRect;
							CRect RowRect;
							GetItemRect(RowIndex,RowRect,LVIR_BOUNDS);
							Image* pImage = ItemIt->second.m_DrawData.m_CheckBoxData.m_CheckBoxUnSelectedImage;
							GetTextAndImageDrawRect(pImage,RowRect,ImageRect,TextRect,ItemIt->second.m_DrawData.m_CheckBoxData.m_DrawStyle);
							ImageRect=GetImageDrawRect(pImage,ImageRect);
							if(ImageRect.PtInRect(point))
							{
								m_ItemStyleMap[Key]=ItemIt->second;
								m_ItemStyleMap[Key].m_DrawData.m_CheckBoxData.m_IsCheck=true;
								InvalidateRect(RowRect);
							}
							//列表点击事件 勾选框
							else
								::PostMessage(m_ButtonHwnd,WM_LIST_CHECKBOX_CLICK,RowIndex,ColumnIndex);

						}
						break;
					case CHECKBOX_IMAGE_AND_TEXT_TYPE:
						{
							m_ItemStyleMap[Key]=ItemIt->second;
							CRect TempRect;
							CPoint Point=GetImageDrawPoint(ItemIt->second.m_DrawData.m_CheckBoxImageAndTextData.m_BoxData.m_CheckBoxUnSelectedImage,SubRect);
							TempRect.left = Point.x;
							TempRect.top = Point.y;
							TempRect.right=TempRect.left+ItemIt->second.m_DrawData.m_CheckBoxImageAndTextData.m_BoxData.m_CheckBoxUnSelectedImage->GetWidth();
							TempRect.bottom = TempRect.top+ItemIt->second.m_DrawData.m_CheckBoxImageAndTextData.m_BoxData.m_CheckBoxUnSelectedImage->GetHeight();
							if(TempRect.PtInRect(point) )
							{
								m_ItemStyleMap[Key].m_DrawData.m_CheckBoxImageAndTextData.m_BoxData.m_IsCheck=true;
								CRect RowRect;
								GetItemRect(RowIndex,RowRect,LVIR_BOUNDS);
								InvalidateRect(RowRect);
							}
							//列表点击事件 勾选框
							else
								::PostMessage(m_ButtonHwnd,WM_LIST_CHECKBOX_CLICK,RowIndex,ColumnIndex);
						}
						break;
					case IMGE_TYPE:
						{
							m_ItemStyleMap[Key]=ItemIt->second;
							m_ItemStyleMap[Key].m_DrawData.m_ImageData.m_IsNormal = false;
							CRect RowRect;
							GetItemRect(RowIndex,RowRect,LVIR_BOUNDS);
							InvalidateRect(RowRect);
						}
						break;

					case IMAGE_AND_TEXT_TYPE:
						{
							m_ItemStyleMap[Key]=ItemIt->second;
							m_ItemStyleMap[Key].m_DrawData.m_ImageAndTextData.m_ImageData.m_IsNormal= false;
							CRect RowRect;
							GetItemRect(RowIndex,RowRect,LVIR_BOUNDS);
							InvalidateRect(RowRect);
						}
						break;
					default:
						break;
				}
			}
		
		}

	}
	CListCtrl::OnLButtonDown(nFlags, point);
}

void CListCtrlEx::OnLButtonUp(UINT nFlags, CPoint point)
{
	int RowIndex = 0;
	int ColumnIndex = 0;
	CRect SubRect;
	bool IsFind=FindRowAndColumnPos(point,RowIndex,ColumnIndex,SubRect);
	if(IsFind)
	{
		long Key = MAKELONG(RowIndex,ColumnIndex);
		map<long,sItemStyle>::iterator it=m_ItemStyleMap.find(Key);
		if(it != m_ItemStyleMap.end())
		{
			switch(it->second.m_ItemType)
			{
				case BUTTON_TYPE:
					if(m_ButtonHwnd)
					{
						CRect ButtonRect=GetImageDrawRect(it->second.m_DrawData.m_ButtonData.m_ButtonNormalImage,SubRect);
						if(ButtonRect.PtInRect(point) )
						{
							it->second.m_DrawData.m_ButtonData.m_IsNormal = true;
							CRect RowRect;
							GetItemRect(RowIndex,RowRect,LVIR_BOUNDS);
							InvalidateRect(RowRect);
						}
					}
					break;
				case CHECKBOX_IMAGE_AND_TEXT_TYPE:
					{
					}
					break;
				case IMGE_TYPE:
					{
						it->second.m_DrawData.m_ImageData.m_IsNormal = true;
						CRect RowRect;
						GetItemRect(RowIndex,RowRect,LVIR_BOUNDS);
						InvalidateRect(RowRect);
					}
					break;

				case IMAGE_AND_TEXT_TYPE:
					{
						it->second.m_DrawData.m_ImageAndTextData.m_ImageData.m_IsNormal= true;
						CRect RowRect;
						GetItemRect(RowIndex,RowRect,LVIR_BOUNDS);
						InvalidateRect(RowRect);
					}
					break;
				default:
					break;
			}
		}
	}

	CListCtrl::OnLButtonUp(nFlags, point);
}

//更改行高
void CListCtrlEx::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	if(m_RowHeight > 0 )
		lpMeasureItemStruct->itemHeight = m_RowHeight;
}

//通过点查找当前位置
bool CListCtrlEx::FindRowAndColumnPos(CPoint Point,int& RowIndex,int& ColumnIndex,CRect& SubItemRect)
{
	for(int Row = 0; Row <= m_RowCount; Row++)
	{
		CRect RowRect;
		GetItemRect(Row,RowRect,LVIR_BOUNDS);
		if( !RowRect.PtInRect(Point))
			continue;

		int Offset=0;
		for(int Column = 0; Column <= m_ColumnCount; Column++)
		{
			int ColumnWidth= GetColumnWidth(Column);
			CRect TempRect = RowRect;
			TempRect.left  = RowRect.left + Offset;
			TempRect.right = TempRect.left + ColumnWidth;
			if( TempRect.PtInRect(Point) )
			{
				RowIndex = Row;
				ColumnIndex = Column;
				SubItemRect=TempRect;
				return true;
			}
			Offset+=ColumnWidth;
		}
	}

	return false;
}

//显示编辑框
void CListCtrlEx::ShowEdit(CRect Rect,CString Str,CFont* Font)
{
	
	//创建编辑框
	if (m_Edit.m_hWnd == NULL)
	{
		m_Edit.Create(WS_CHILD|WS_CLIPSIBLINGS|WS_EX_TOOLWINDOW|WS_BORDER,Rect,this,1001);
		m_Edit.ShowWindow(SW_HIDE);
		if(Font)
		   m_Edit.SetFont(Font);
	}

	m_Edit.MoveWindow(Rect);
	m_Edit.ShowWindow(SW_SHOW);
	m_Edit.SetWindowText(Str);
	m_Edit.SetFocus();	
	
}

//绘制背景
void CListCtrlEx::DrawBkItem(CDC* pDC, int RowIndex,CRect Rect)
{
	
	if(m_BkData.m_BkFillMode == MODE_FILL_IMG)
		FillRectByImage(pDC,m_BkData.m_Image,Rect);
	else if (m_BkData.m_BkFillMode == MODE_FILL_RGB)
		pDC->FillSolidRect(Rect,m_BkData.m_BkColor);

	if(m_CurrentSelectRow == RowIndex)
	{
		if(m_BkData.m_HeightFillMode == MODE_FILL_IMG)
			FillRectByImage(pDC,m_BkData.m_HeightImage,Rect);
		else if (m_BkData.m_HeightFillMode == MODE_FILL_RGB)
			pDC->FillSolidRect(Rect,m_BkData.m_HeightColor);
	}
	else if(m_OldSelectRow == RowIndex)//当传进来的row为原来选中的时候就将其显示为原来的颜色
	{
		if (m_BkData.m_HeightFillMode == MODE_FILL_RGB)
		{
			sItemBkData ItemData;
			ItemData.m_BkColor = RGB(24,25,25);
			pDC->FillSolidRect(Rect,ItemData.m_BkColor);
		}
	}


	CPen LinePen(PS_SOLID,1,m_LineColor);
	CPen* OldPen=(CPen*)pDC->SelectObject(LinePen);

	if(m_VecDrawLine )
	{
		pDC->MoveTo(Rect.right,Rect.top);
		pDC->LineTo(Rect.right,Rect.bottom);
	}
	if(m_HorDrawLine)
	{
		pDC->MoveTo(Rect.left, Rect.bottom);
		pDC->LineTo(Rect.right, Rect.bottom);
	}

}

//填充矩行区
void CListCtrlEx::FillRectByImage(CDC* pDC,Image* pImage,CRect Rect)
{
	if(!pImage)
		return;

	Graphics Display(pDC->GetSafeHdc());
	RectF Temp;
	Temp.X = Rect.top;
	Temp.Y = Rect.bottom;
	Temp.Width = pImage->GetWidth();
	Temp.Height = pImage->GetHeight();

	int Count = Rect.Width()/pImage->GetWidth() + (Rect.Width()%pImage->GetWidth() ? 1:0);
	int HeightCount = Rect.Height()/pImage->GetHeight() + (Rect.Height()%pImage->GetHeight() ? 1: 0);

	for(int Index = 0; Index < Count;Index++ )
	{
		Temp.X = Rect.left+Index*pImage->GetWidth();
		if( Temp.X +Temp.Width > Rect.left + Rect.Width())
			Temp.Width = Rect.Width() - Index*pImage->GetWidth();
		Temp.Height = pImage->GetHeight();

		Temp.Y = Rect.top;
		Display.DrawImage(pImage,Temp);
		
		for(int HeightIndex = 0; HeightIndex < HeightCount; HeightIndex++)
		{
			Temp.Y = Rect.top + HeightIndex*pImage->GetHeight();
			if(Temp.Y + Temp.Height > Rect.top + Rect.Height())
				Temp.Height = Rect.Height() - HeightIndex*pImage->GetHeight();
			Display.DrawImage(pImage,Temp);
		}
	}

	Display.ReleaseHDC(pDC->GetSafeHdc());
}

void CListCtrlEx::PreSubclassWindow()
{
	if(GetHeaderCtrl())
	{
		m_HeaderCtrl.SubclassWindow(GetHeaderCtrl()->m_hWnd);
	}
	CListCtrl::PreSubclassWindow();
}

//设置当前选中行
void CListCtrlEx::SetCurrentSelectRow(int Row)
{
	m_CurrentSelectRow = Row;
	if(m_CurrentSelectRow == -1)
	{	
		CRect RectCurr;
		GetItemRect(Row,RectCurr,LVIR_BOUNDS);
		InvalidateRect(RectCurr);
	}
	else
	{
		//取消原来的选中状态
		if(m_OldSelectRow == m_CurrentSelectRow)
			return;//当前选中和之前选中行相同时不再重绘
		CRect Rect;
		GetItemRect(m_OldSelectRow,Rect,LVIR_BOUNDS);
		InvalidateRect(Rect);
		//再显示当前选中状态
		CRect RectCurr;
		GetItemRect(Row,RectCurr,LVIR_BOUNDS);
		InvalidateRect(RectCurr);

	}
	m_OldSelectRow = Row;
}
//设置全选
void CListCtrlEx::SetAllLineSelected(int iRow)
{
	m_OldSelectRow = -1;
	m_CurrentSelectRow = iRow;

	CRect RectCurr;
	GetItemRect(iRow,RectCurr,LVIR_BOUNDS);
	InvalidateRect(RectCurr);
}

void CListCtrlEx::SetSelProperty(int iRow)
{
	this->SetItemState(iRow,LVIS_SELECTED,LVIS_SELECTED);
}
void CListCtrlEx::OnSize(UINT nType, int cx, int cy)
{
	CListCtrl::OnSize(nType, cx, cy);
	ShowScrollBar(SB_HORZ,m_HScrollBar);
}

void CListCtrlEx::OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	if((pNMLV->uChanged & LVIF_STATE))
		SetCurrentSelectRow(pNMLV->iItem);
	*pResult = 0;
}

//删除图片
void CListCtrlEx::DeleteImage(Image* pImage)
{
	if(pImage&& pImage->GetLastStatus() == Ok)
	{
		delete pImage;
	}
}

//清除风格
void CListCtrlEx::CleanStyle(int ColumnIndex,sItemStyle* pStyle)
{
	if(pStyle == NULL)
		return;

	switch(pStyle->m_ItemType)
	{
	case IMGE_TYPE:
	//	SAFE_DELETE(it->second.m_DrawData.m_ImageData.m_ActiveImage);
	//	SAFE_DELETE(it->second.m_DrawData.m_ImageData.m_NormalImage);
		break;
	case CHECKBOX_IMAGE_AND_TEXT_TYPE:
		{
			sItemStyle Style;
			GetColumStyle(ColumnIndex,Style);
			if(pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_ActiveImage == pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_NormalImage 
				&& Style.m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_NormalImage != pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_NormalImage
				&& Style.m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_ActiveImage != pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_ActiveImage)
			{
				DeleteImage(pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_ActiveImage);
				pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_ActiveImage = NULL;
				pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_NormalImage = NULL;

			}
			if(Style.m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_ActiveImage != pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_ActiveImage)
			{
				DeleteImage(pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_ActiveImage);
				pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_ActiveImage = NULL;

			}
			if(Style.m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_NormalImage != pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_NormalImage)
			{
				DeleteImage(pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_NormalImage);
				pStyle->m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_NormalImage = NULL;
			}
		}
	//	it->second.m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_ActiveImage->
		//SAFE_DELETE(it->second.m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_ActiveImage);
	//	SAFE_DELETE(it->second.m_DrawData.m_CheckBoxImageAndTextData.m_ImageData.m_NormalImage);
		break;
	case IMAGE_AND_TEXT_TYPE:  
	//	DeleteImage(it->second.m_DrawData.m_ImageAndTextData.m_ImageData.m_ActiveImage);
	//	DeleteImage(it->second.m_DrawData.m_ImageAndTextData.m_ImageData.m_NormalImage);
	//	SAFE_DELETE(it->second.m_DrawData.m_ImageAndTextData.m_ImageData.m_ActiveImage);
		//SAFE_DELETE(it->second.m_DrawData.m_ImageAndTextData.m_ImageData.m_NormalImage);
		break;

	}
}

void CListCtrlEx::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{

	CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);

	if(m_IsVirtualMode)
	{
		SCROLLINFO ScrollInfo;
		ScrollInfo.cbSize = sizeof(SCROLLINFO);
		ScrollInfo.fMask = SIF_ALL;
		GetScrollInfo(SB_VERT,&ScrollInfo,SIF_ALL);
		int AllRowCount = GetItemCount();
		if(AllRowCount == 0 || ScrollInfo.nMax == 0)
			return;

		int CurrrentRow=AllRowCount*ScrollInfo.nPos/ScrollInfo.nMax;
		::PostMessage(GetParent()->GetSafeHwnd(),WM_VIRTUAL_LIST_MSG,m_VirtualID,CurrrentRow);
		
	}
}

BOOL CListCtrlEx::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	BOOL Temp=CListCtrl::OnMouseWheel(nFlags, zDelta, pt);
	if(m_IsVirtualMode)
	{
		SCROLLINFO ScrollInfo;
		ScrollInfo.cbSize = sizeof(SCROLLINFO);
		ScrollInfo.fMask = SIF_ALL;
		GetScrollInfo(SB_VERT,&ScrollInfo,SIF_ALL);
		int AllRowCount = GetItemCount();
		if(AllRowCount == 0 || ScrollInfo.nMax == 0)
			return Temp;
		int CurrrentRow=AllRowCount*ScrollInfo.nPos/ScrollInfo.nMax;
		::PostMessage(GetParent()->GetSafeHwnd(),WM_VIRTUAL_LIST_MSG,m_VirtualID,CurrrentRow);
		
	}
	return Temp;
}

//触发当前位置：针对虚模式
void CListCtrlEx::TouchCurrentScrollPos()
{
	if(m_IsVirtualMode)
	{
		SCROLLINFO ScrollInfo;
		ScrollInfo.cbSize = sizeof(SCROLLINFO);
		ScrollInfo.fMask = SIF_ALL;
		GetScrollInfo(SB_VERT,&ScrollInfo,SIF_ALL);
		int AllRowCount = GetItemCount();
		if(AllRowCount == 0 || ScrollInfo.nMax == 0)
			return ;
		int CurrrentRow=AllRowCount*ScrollInfo.nPos/ScrollInfo.nMax;
		::PostMessage(GetParent()->GetSafeHwnd(),WM_VIRTUAL_LIST_MSG,m_VirtualID,CurrrentRow);
		
	}
}

//子类化控件的列表头
//void CListCtrlEx::PreSubclassWindow()
//{
//	if(GetHeaderCtrl())
//	{
//		m_skinHead.SubclassWindow(GetHeaderCtrl()->m_hWnd);
//	}
//	CListCtrl::PreSubclassWindow();
//}

//屏蔽列表头移动事件
BOOL CListCtrlEx::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	switch (((NMHDR*)lParam)->code)
	{
	case HDN_BEGINTRACKW:
	case HDN_BEGINTRACKA:
		*pResult = TRUE;                // disable tracking
		return TRUE;                    // Processed message
	}

	return CListCtrl::OnNotify(wParam, lParam, pResult);
}