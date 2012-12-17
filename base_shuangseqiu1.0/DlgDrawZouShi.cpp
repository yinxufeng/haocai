// DlgDrawZouShi.cpp : 实现文件
//

#include "stdafx.h"
#include "ShuangSeQiu.h"
#include "DlgDrawZouShi.h"


// CDlgDrawZouShi 对话框

IMPLEMENT_DYNAMIC(CDlgDrawZouShi, CDialog)

CDlgDrawZouShi::CDlgDrawZouShi(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDrawZouShi::IDD, pParent)
{
	m_DrawIndex = 0;
	m_TiaoXingCount=33;
	m_IsDrawSingle=false;
	m_SingleDrawIndex=0;
}

CDlgDrawZouShi::~CDlgDrawZouShi()
{
}

void CDlgDrawZouShi::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgDrawZouShi, CDialog)
    ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_PREV_BTN, &CDlgDrawZouShi::OnBnClickedPrevBtn)
	ON_BN_CLICKED(IDC_NEXT_BTN, &CDlgDrawZouShi::OnBnClickedNextBtn)
	ON_BN_CLICKED(IDC_FIRST_BTN, &CDlgDrawZouShi::OnBnClickedFirstBtn)
	ON_BN_CLICKED(IDC_CLEAN_BTN, &CDlgDrawZouShi::OnBnClickedCleanBtn)
END_MESSAGE_MAP()


BOOL CDlgDrawZouShi::OnEraseBkgnd(CDC* pDC)
{

	CRect Rect;
	GetClientRect(Rect);
	pDC->BitBlt(0,0,Rect.Width(),Rect.Height(),&MemDC,0,0,SRCCOPY);
	return true;
}

//绘制条形
void CDlgDrawZouShi::DrawTiaoXing(CDC* pDC,CRect Rect,int DataIndex)
{
	if(DataIndex < 0 || DataIndex >=m_DrawData.size())
		return;


	int TextHeight=40;
	CRect TempRect=Rect;
	TempRect.bottom-=TextHeight;

	CRect TextRect=Rect;
	TextRect.top=TextRect.bottom-TextHeight;

	CString Text;
	
	int QiShu=atoi(m_DrawData[DataIndex].m_QiShu.GetBuffer());
	m_DrawData[DataIndex].m_QiShu.ReleaseBuffer();

	if(QiShu == 0)
		Text=m_DrawData[DataIndex].m_QiShu;
	else
		Text.Format("%d ",QiShu);
	pDC->DrawText(Text,TextRect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	
	vector<CRect> RectList=GetTiaoXingRect(TempRect);

	int Min=100;
	for(int Index = 0; Index < RectList.size(); Index++)
	{
		CString Text=m_DrawData[DataIndex].m_DrawDataList[Index].m_DrawText;
		int Height=atoi(Text.GetBuffer());
		if(Min > Height)
			Min=Height;
	}

	for(int Index = 0; Index < RectList.size(); Index++)
	{
		CString Text=m_DrawData[DataIndex].m_DrawDataList[Index].m_DrawText;
		int Height=atoi(Text.GetBuffer());
		CRect TempRect= RectList[Index];
		if(Height < 50)
			TempRect.top = TempRect.bottom- m_TiaoXingHeight*Height;
		else
		{
			TempRect.top = TempRect.bottom- 2*m_TiaoXingHeight*(Height-50);
		}
		if(m_DrawData[DataIndex].m_DrawDataList[Index].m_IsTrue)
		{
			if(Height != Min)
				pDC->FillSolidRect(TempRect,ZISE);
			else
				pDC->FillSolidRect(TempRect,YELOW);
		}
		else
			pDC->FillSolidRect(TempRect,RED);
		
	}
	
}

void CDlgDrawZouShi::DrawFrame(CDC* pDC,CRect TempRect,COLORREF Color,int FrameWidth)
{
	CPen pen(PS_SOLID,FrameWidth,Color);
	pDC->SelectObject(&pen);
	pDC->MoveTo(TempRect.left,TempRect.top);
	pDC->LineTo(TempRect.right,TempRect.top);
	pDC->LineTo(TempRect.right,TempRect.bottom);
	pDC->LineTo(TempRect.left,TempRect.bottom);
	pDC->LineTo(TempRect.left,TempRect.top);
}

//初始化条形区域
void CDlgDrawZouShi::InitRect()
{
	CRect ClientRect;
	GetClientRect(ClientRect);
	int Height = 250;
	int Width  = 500;
	int TextWidth  =Width;
	int TextHeight =40;
	int SpaceWidth = 20;
	int SpaceHeight=20;
	int OffsetWidth= 80;
	int OffsetHeight=40;
	int V_PAGE_COUNT=2;
    int H_PAGE_COUNT=2;

	for(int i = 0; i < V_PAGE_COUNT; i++)
	{
		for(int j=0; j < H_PAGE_COUNT; j++)
		{
			CRect Rect=ClientRect;
			Rect.left = ClientRect.left+Width*j+SpaceWidth*j + OffsetWidth;
			Rect.right = Rect.left+Width;
			Rect.top = ClientRect.top + Height*i +TextHeight*i+OffsetHeight+SpaceHeight*i;
			Rect.bottom =Rect.top + Height;
			m_RectList.push_back(Rect);
		}
	}
}

//获取条形区域
vector<CRect> CDlgDrawZouShi::GetTiaoXingRect(CRect Rect)
{
	vector<CRect> RectList;

	int WidthCount=33;
	if(m_TiaoXingCount)
		WidthCount=m_TiaoXingCount;

	int HeightCount=100;
	Rect.left+=3;
	Rect.right-=3;
	int Width=Rect.Width()/WidthCount;
	int Height=Rect.Height()/HeightCount;
	m_TiaoXingHeight=Height;

	for(int i =0; i < WidthCount; i++)
	{
		CRect TempRect=Rect;
		TempRect.left=Rect.left+i*Width;
		TempRect.right=TempRect.left + Width;

		TempRect.left+=1;
		TempRect.right-=1;
		RectList.push_back(TempRect);
	}

	return RectList;
}


//通过位置获取文本
CString CDlgDrawZouShi::GetTextByPoint(CPoint Point)
{
	vector<CRect> RectList;
	int TempIndex =0;
	if(! m_IsDrawSingle )
	{
		for(int Index = 0; Index < m_RectList.size(); Index++)
		{
			if(m_RectList[Index].PtInRect(Point))
			{
				RectList= GetTiaoXingRect(m_RectList[Index]);
				TempIndex =m_DrawIndex - Index;
				break;
				
			}
		}
	}
	else
	{
		RectList = GetTiaoXingRect(m_SingleRect);
		TempIndex =m_SingleDrawIndex;
	}


	for(int i=0; i < RectList.size(); i++)
	{
		if(RectList[i].PtInRect(Point))
		{
			CString Text;
			CString Title;
			GetWindowText(Title);
			Text.Format("%s 球：%02d  ",Title,i+1);

			
			if(TempIndex >= 0 && TempIndex < m_DrawData.size())
			{
				CString TempText;
				TempText.Format("平均：%s  综合：",m_DrawData[TempIndex].m_DrawDataList[i].m_DrawText);
				Text+=TempText;
				Text=m_DrawData[TempIndex].m_QiShu+" ： "+Text;
				for(int j=0; j < m_DrawData[TempIndex].m_DrawDataList[i].m_InfoList.size();j++)
				{
					CString TempText2;
					TempText2.Format("  %s  ",m_DrawData[TempIndex].m_DrawDataList[i].m_InfoList[j]);
					Text+=TempText2;

				}
			}
			return Text;
		}
	}


	return "";
}

//通过位置获取索引
int CDlgDrawZouShi::GetIndexByPoint(CPoint Point)
{
	for(int Index = 0; Index < m_RectList.size(); Index++)
	{
		if(m_RectList[Index].PtInRect(Point))
		{
			return m_DrawIndex-Index;
		}
	}

	return -1;
}

BOOL CDlgDrawZouShi::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitRect();
	CreateMemDC();
	Draw();
	CenterWindow();
	return TRUE; 
}

void CDlgDrawZouShi::OnLButtonDown(UINT nFlags, CPoint point)
{

	CDialog::OnLButtonDown(nFlags, point);
	m_CurrentDrawLine.m_StartPoint = point;
}

void CDlgDrawZouShi::OnLButtonUp(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonUp(nFlags, point);
	if(m_CurrentDrawLine.m_EndPoint != m_CurrentDrawLine.m_StartPoint)
	{
		m_CurrentDrawLine.m_EndPoint=point;
		m_DrawLineInfoList.push_back(m_CurrentDrawLine);
		Draw();
		Invalidate();
	}
	
}

void CDlgDrawZouShi::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_TextPoint != point)
	{
		CString Text=GetTextByPoint(point);
		m_DrawText =Text;
		m_TextPoint = point;
	
		Draw();
		
	}

	CDialog::OnMouseMove(nFlags, point);

}

void CDlgDrawZouShi::OnLButtonDblClk(UINT nFlags, CPoint point)
{

	if(!m_IsDrawSingle)
	{
		m_SingleDrawIndex=GetIndexByPoint(point);
		if(m_SingleDrawIndex >= 0 && m_SingleDrawIndex < m_DrawData.size())
		{
			m_IsDrawSingle=true;
			Draw();
		}
		
	}
	else
	{
		m_IsDrawSingle=false;
		Draw();
	}
	
	CDialog::OnLButtonDblClk(nFlags, point);


}

//创建内存设备环境
void CDlgDrawZouShi::CreateMemDC()
{
	CRect Rect;
	GetClientRect(Rect);

	CDC* pDC = GetDC();
	MemDC.CreateCompatibleDC(pDC);
	Bmp.CreateCompatibleBitmap(pDC,Rect.Width(),Rect.Height());
	CBitmap* Old =(CBitmap*)MemDC.SelectObject(&Bmp);


	ReleaseDC(pDC);
}
//绘制图形
void CDlgDrawZouShi::Draw()
{
	CRect Rect;
	GetClientRect(Rect);
	MemDC.FillSolidRect(Rect,WRITE);
	

	if(!m_IsDrawSingle)
	{
		for(int Index = 0; Index < m_RectList.size(); Index++)
		{
			int TempIndex= m_DrawIndex-Index;
			if(TempIndex < 0 || TempIndex >= m_DrawData.size())
				break;

			//DrawFrame(&MemDC,m_RectList[Index],WRITE);
			DrawTiaoXing(&MemDC,m_RectList[Index],TempIndex);
		}
	}
	else
	{
		CRect TempRect=Rect;
		
		TempRect.top +=30;
		TempRect.bottom-=100;
		TempRect.left+=200;
		TempRect.right-=200;
		m_SingleRect=TempRect;

		DrawTiaoXing(&MemDC,TempRect,m_SingleDrawIndex);
	}


	CPen Pen(PS_SOLID,1,YELOW);
	MemDC.SetTextColor(YELOW);

	CPen* OldPen=MemDC.SelectObject(&Pen);
	MemDC.SetBkMode(TRANSPARENT);
	for(int Index = 0; Index < m_DrawLineInfoList.size(); Index++)
	{
		MemDC.MoveTo(m_DrawLineInfoList[Index].m_StartPoint.x,m_DrawLineInfoList[Index].m_StartPoint.y);
		MemDC.LineTo(m_DrawLineInfoList[Index].m_EndPoint.x,m_DrawLineInfoList[Index].m_EndPoint.y);
	}

	if( !m_DrawText.IsEmpty())
	{
		CRect TextRect;
		TextRect.left = m_TextPoint.x;
		TextRect.bottom = m_TextPoint.y;
		TextRect.top = TextRect.bottom-50;
		TextRect.right=TextRect.left+600;

		if(TextRect.right > Rect.right)
		{
			TextRect.right=m_TextPoint.x;
			TextRect.left=TextRect.right-600;
		}
	
		MemDC.FillSolidRect(TextRect,RGB(111,111,111));
		MemDC.DrawText(m_DrawText,TextRect,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	}
	MemDC.SelectObject(OldPen);

	Rect.bottom-=60;
	InvalidateRect(Rect);
}

//设置绘制数据
void CDlgDrawZouShi::SetDrawData(vector<sDrawInfoList>& DrawAllInfo,CString Title,int TiaoXingCount)
{
	m_DrawData = DrawAllInfo;
	m_TiaoXingCount=TiaoXingCount;
	SetWindowText(Title);
	m_DrawIndex=DrawAllInfo.size()-1;
	Draw();
	
}
void CDlgDrawZouShi::OnBnClickedPrevBtn()
{
	if(!m_IsDrawSingle)
	{
		m_DrawIndex+=m_RectList.size();
		if(m_DrawIndex >= m_DrawData.size())
			m_DrawIndex=m_DrawData.size()-1;

		int Count = m_DrawIndex+m_RectList.size();
		if(Count >=m_DrawData.size()-1)
			Count=m_DrawData.size()-1;
	}
	else
	{
		m_SingleDrawIndex++;
		if(m_SingleDrawIndex >= m_DrawData.size())
			m_SingleDrawIndex=m_DrawData.size()-1;

	}

	
	UpdateBtnStatus();
	Draw();
}

void CDlgDrawZouShi::OnBnClickedNextBtn()
{
	if(!m_IsDrawSingle)
	{
		int Count=0;
		m_DrawIndex-=m_RectList.size();
		if(m_DrawIndex < 0)
			m_DrawIndex=0;

		Count= m_DrawIndex+m_RectList.size();
		if(Count > m_DrawData.size())
			Count=m_DrawData.size()-1;
	}
	else
	{
		m_SingleDrawIndex--;
		if(m_SingleDrawIndex < 0)
			m_SingleDrawIndex=0;

	}

	UpdateBtnStatus();

	Draw();
}

void CDlgDrawZouShi::OnBnClickedFirstBtn()
{
	if(!m_IsDrawSingle)
	{
		m_DrawIndex=m_DrawData.size()-1;
		if(m_DrawIndex< 0)
			m_DrawIndex=0;
	}
	else
	{
		m_SingleDrawIndex=m_DrawData.size()-1;
		if(m_SingleDrawIndex< 0)
			m_SingleDrawIndex=0;
	}

	Draw();
}

void CDlgDrawZouShi::OnBnClickedCleanBtn()
{
	m_DrawLineInfoList.clear();
	Draw();
}

void CDlgDrawZouShi::UpdateBtnStatus()
{
	if(!m_IsDrawSingle)
	{
		if(m_DrawIndex + m_RectList.size() < m_DrawData.size())
			GetDlgItem(IDC_PREV_BTN)->EnableWindow(true);
		else
			GetDlgItem(IDC_PREV_BTN)->EnableWindow(false);

		if(m_DrawIndex - m_RectList.size() < 0)
			GetDlgItem(IDC_NEXT_BTN)->EnableWindow(false);
		else
			GetDlgItem(IDC_NEXT_BTN)->EnableWindow(true);
		
	}
	else
	{
		if(m_SingleDrawIndex+1 < m_DrawData.size())
			GetDlgItem(IDC_PREV_BTN)->EnableWindow(true);
		else
			GetDlgItem(IDC_PREV_BTN)->EnableWindow(false);

		if(m_SingleDrawIndex-1 < 0)
			GetDlgItem(IDC_NEXT_BTN)->EnableWindow(false);
		else
			GetDlgItem(IDC_NEXT_BTN)->EnableWindow(true);
		
	}

}