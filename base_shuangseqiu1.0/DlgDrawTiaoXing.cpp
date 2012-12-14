// DlgDrawTiaoXing.cpp : 实现文件
//

#include "stdafx.h"
#include "ShuangSeQiu.h"
#include "DlgDrawTiaoXing.h"


// CDlgDrawTiaoXing 对话框

IMPLEMENT_DYNAMIC(CDlgDrawTiaoXing, CDialog)

CDlgDrawTiaoXing::CDlgDrawTiaoXing(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDrawTiaoXing::IDD, pParent)
{
	m_DrawIndex = 0;
}

CDlgDrawTiaoXing::~CDlgDrawTiaoXing()
{
}

void CDlgDrawTiaoXing::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgDrawTiaoXing, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_PREV_BTN, &CDlgDrawTiaoXing::OnBnClickedPrevBtn)
	ON_BN_CLICKED(IDC_NEXT_BTN, &CDlgDrawTiaoXing::OnBnClickedNextBtn)
	ON_BN_CLICKED(IDC_FIRST_BTN, &CDlgDrawTiaoXing::OnBnClickedFirstBtn)
	ON_BN_CLICKED(IDC_CLEAN_BTN, &CDlgDrawTiaoXing::OnBnClickedCleanBtn)
END_MESSAGE_MAP()


// CDlgDrawTiaoXing 消息处理程序

BOOL CDlgDrawTiaoXing::OnEraseBkgnd(CDC* pDC)
{
	//CDialog::OnEraseBkgnd(pDC);

	
	//CDC MemDC;
	//CBitmap Bmp;
	//MemDC.CreateCompatibleDC(pDC);
	//Bmp.CreateCompatibleBitmap(pDC,Rect.Width(),Rect.Height());
	//CBitmap* Old =(CBitmap*)MemDC.SelectObject(&Bmp);
	//
	//MemDC.BitBlt(0,0,Rect.Width(),Rect.Height(),pDC,0,0,SRCCOPY);

	//for(int Index = 0; Index < m_RectList.size(); Index++)
	//{
	//	DrawFrame(&MemDC,m_RectList[Index],WRITE);
	//	DrawTiaoXing(&MemDC,m_RectList[Index]);
	//}


	//CPen Pen(PS_SOLID,1,YELOW);
	//MemDC.SetTextColor(YELOW);

	//CPen* OldPen=MemDC.SelectObject(&Pen);
	//MemDC.SetBkMode(TRANSPARENT);
	//for(int Index = 0; Index < m_DrawLineInfoList.size(); Index++)
	//{
	//	MemDC.MoveTo(m_DrawLineInfoList[Index].m_StartPoint.x,m_DrawLineInfoList[Index].m_StartPoint.y);
	//	MemDC.LineTo(m_DrawLineInfoList[Index].m_EndPoint.x,m_DrawLineInfoList[Index].m_EndPoint.y);
	//}

	//if( !m_DrawText.IsEmpty())
	//{
	//	CRect TextRect;
	//	TextRect.left = m_TextPoint.x;
	//	TextRect.top = m_TextPoint.y;
	//	TextRect.right=TextRect.left+500;
	//	TextRect.bottom=TextRect.top+100;
	//	MemDC.DrawText(m_DrawText,TextRect,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	//}
	//MemDC.SelectObject(OldPen);

	CRect Rect;
	GetClientRect(Rect);
	pDC->BitBlt(0,0,Rect.Width(),Rect.Height(),&MemDC,0,0,SRCCOPY);
	
	/*Bmp.DeleteObject();
	MemDC.DeleteDC();
	*/
	
	return true;
}

//绘制条形
void CDlgDrawTiaoXing::DrawTiaoXing(CDC* pDC,CRect Rect,int DataIndex)
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
	for(int Index = 0; Index < RectList.size(); Index++)
	{
		CString Text=m_DrawData[DataIndex].m_DrawDataList[Index].m_DrawText;
		int Height=atoi(Text.GetBuffer());
		CRect TempRect= RectList[Index];
		TempRect.top = TempRect.bottom- m_TiaoXingHeight*Height;
		if(m_DrawData[DataIndex].m_DrawDataList[Index].m_IsTrue)
			pDC->FillSolidRect(TempRect,ZISE);
		else
			pDC->FillSolidRect(TempRect,RED);
		
	}
	
}

void CDlgDrawTiaoXing::DrawFrame(CDC* pDC,CRect TempRect,COLORREF Color,int FrameWidth)
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
void CDlgDrawTiaoXing::InitRect()
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
vector<CRect> CDlgDrawTiaoXing::GetTiaoXingRect(CRect Rect)
{
	vector<CRect> RectList;

	int WidthCount=33;
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
CString CDlgDrawTiaoXing::GetTextByPoint(CPoint Point)
{
	for(int Index = 0; Index < m_RectList.size(); Index++)
	{
		if(m_RectList[Index].PtInRect(Point))
		{
			vector<CRect> RectList = GetTiaoXingRect(m_RectList[Index]);
			for(int i=0; i < RectList.size(); i++)
			{
				if(RectList[i].PtInRect(Point))
				{
					CString Text;
					CString Title;
					GetWindowText(Title);
					Text.Format("%s 球：%02d  ",Title,i+1);

					int TempIndex =m_DrawIndex - Index;
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

		}
	}

	return "";
}


BOOL CDlgDrawTiaoXing::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitRect();
	CreateMemDC();
	Draw();
	CenterWindow();
	return TRUE; 
}

void CDlgDrawTiaoXing::OnLButtonDown(UINT nFlags, CPoint point)
{

	CDialog::OnLButtonDown(nFlags, point);
	m_CurrentDrawLine.m_StartPoint = point;
}

void CDlgDrawTiaoXing::OnLButtonUp(UINT nFlags, CPoint point)
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

void CDlgDrawTiaoXing::OnMouseMove(UINT nFlags, CPoint point)
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

//创建内存设备环境
void CDlgDrawTiaoXing::CreateMemDC()
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
void CDlgDrawTiaoXing::Draw()
{
	CRect Rect;
	GetClientRect(Rect);
	MemDC.FillSolidRect(Rect,WRITE);
	

	for(int Index = 0; Index < m_RectList.size(); Index++)
	{
		int TempIndex= m_DrawIndex-Index;
		if(TempIndex < 0 || TempIndex >= m_DrawData.size())
			break;

		DrawFrame(&MemDC,m_RectList[Index],WRITE);
		DrawTiaoXing(&MemDC,m_RectList[Index],TempIndex);
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
void CDlgDrawTiaoXing::SetDrawData(vector<sDrawInfoList>& DrawAllInfo,CString Title)
{
	m_DrawData = DrawAllInfo;
	SetWindowText(Title);
	m_DrawIndex=DrawAllInfo.size()-1;
	Draw();
	
}
void CDlgDrawTiaoXing::OnBnClickedPrevBtn()
{
	m_DrawIndex+=m_RectList.size();
	if(m_DrawIndex >= m_DrawData.size())
		m_DrawIndex=m_DrawData.size()-1;

	int Count = m_DrawIndex+m_RectList.size();
	if(Count >=m_DrawData.size()-1)
		Count=m_DrawData.size()-1;
	
	UpdateBtnStatus();
	Invalidate();
}

void CDlgDrawTiaoXing::OnBnClickedNextBtn()
{
	int Count=0;
	m_DrawIndex-=m_RectList.size();
	if(m_DrawIndex < 0)
		m_DrawIndex=0;

	Count= m_DrawIndex+m_RectList.size();
	if(Count > m_DrawData.size())
		Count=m_DrawData.size()-1;

	UpdateBtnStatus();

	Draw();
}

void CDlgDrawTiaoXing::OnBnClickedFirstBtn()
{
	m_DrawIndex=m_DrawData.size()-1;
	if(m_DrawIndex< 0)
		m_DrawIndex=0;

	Draw();
}

void CDlgDrawTiaoXing::OnBnClickedCleanBtn()
{
	m_DrawLineInfoList.clear();
	Draw();
}

void CDlgDrawTiaoXing::UpdateBtnStatus()
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