#pragma once

#include <gdiplus.h>


using namespace Gdiplus;



enum
{
	_nSortNone = 0,
	_nSortUp,
	_nSortDown,

	_nSortCount = 3,
};

// CSkinHeaderCtrl

class CSkinHeaderCtrl : public CHeaderCtrl
{
	DECLARE_DYNAMIC(CSkinHeaderCtrl)

public:
	CSkinHeaderCtrl();
	virtual ~CSkinHeaderCtrl();
public:
	void SetItemSortState(int iItem, UINT sortState);
	UINT GetItemSortState(int iItem);

	Image* m_pImageBg;
	Image* m_pImageSep;
	Image* m_pImageLine;
	Image* m_pImageLineSep;

	CFont fontList;

	COLORREF m_BkColor;
	COLORREF m_LineColor;

	BOOL     m_DrawRGB;
	int      m_LineWidth;
	BOOL     m_HeaderShow;

	//LRESULT OnLayout( WPARAM wParam, LPARAM lParam );

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnLayout(WPARAM wParam,LPARAM lParam);
private:
	void Init();
public:
	afx_msg void OnPaint();
	virtual void DoPaint(CDC *pDC);
protected:
	virtual void PreSubclassWindow();
public:
	afx_msg void OnHdnItemchanged(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};


