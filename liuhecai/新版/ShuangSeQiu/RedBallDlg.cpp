// RedBallDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ShuangSeQiu.h"
#include "RedBallDlg.h"
#include <math.h>

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

			vector<int> ListData;
			for(int k=3; k >= 0; k--)
			{
				if(TempIndex -k >=0)
				{
					bool IsEqual=false;
					for(int f=0; f < ListData.size(); f++)
					{
						if(m_DataList[TempIndex-k].m_LanQiu == ListData[f])
						{
							IsEqual=true;
							break;
						}
					}
					
					if(IsEqual)
						ListData.push_back((m_DataList[TempIndex-k].m_LanQiu+7)%QIU_COUNT);
					else
						ListData.push_back(m_DataList[TempIndex-k].m_LanQiu);
				}
			}
	//		ListData.push_back(m_DataList[TempIndex].m_HongQiu[0]);
		//	ListData.push_back(m_DataList[TempIndex].m_HongQiu[2]);
	//		ListData.push_back(m_DataList[TempIndex].m_HongQiu[5]);
			DrawData(&MemDC,TempRect,m_DataList[TempIndex].m_LanQiu,ListData);
			

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

//获取数据位置
CPoint CRedBallDlg::GetPointByData(int Data)
{
	//int HCount=7;
	//int VCount=7;
	//int Width = Rect.Width()/HCount;
	//int Height= Rect.Width()/VCount;
	CPoint Point;
	return Point;


}

void CRedBallDlg::DrawData(CDC* pDC,CRect Rect,int Data,vector<int>&DataList)
{
	int HCount=7;
	int VCount=7;
	int Width = Rect.Width()/HCount;
	int Height= Rect.Width()/VCount;

	int DrawData=0;
	vector<CPoint> PointList;

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
			{
				pDC->FillSolidRect(TempRect,RGB(255,0,0));
			}
			for(int k=0; k < DataList.size(); k++)
			{
				if(DataList[k] == DrawData)
				{
					CPoint Point; 
					Point.x = TempRect.left+Width/2;
					Point.y =TempRect.top+Height/2;
					PointList.push_back(Point);
				}
			}
	
			pDC->DrawText(Text,TempRect, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		}
	}

	/*if(PointList.size() == 3)
	{
		float A=0;
		float B=0;
		float C=0;
		GetPaoWuXianCanShu(PointList[0],PointList[1],PointList[2],A,B,C);

		for(int x=0;x < Rect.Width();x++)
		{
			float y=A*x*x+B*x+C;
			int Y=(int)y;
			if(x == 0)
			{
				pDC->MoveTo(Rect.left+x,Rect.top+Y);
			}
			else
				pDC->LineTo(Rect.left+x,Rect.top+Y);
		}
	}*/


	CPen Pen(PS_SOLID,2,RGB(255,0,0));
	CPen* Old=(CPen*)pDC->SelectObject(&Pen);
	POINT* Array= new POINT[PointList.size()];
	if(Array != NULL)
	{
		for(int k=0; k < PointList.size(); k++)
		{
			Array[k].x = PointList[k].x;
			Array[k].y = PointList[k].y;
		}

		pDC->PolyBezier(Array,PointList.size());
		delete []Array;
	}

	if(PointList.size()==4)
	{
		/*int  temp=PointList[3].x -Rect.left-(PointList[2].x-Rect.left);
		if(temp == 0)
			temp=1;

		float k=PointList[3].y - Rect.left-(PointList[2].y-Rect.left);
		float b=PointList[3].y-k*(PointList[3].y-Rect.left);

		float x1=-b/k;
		CPoint Point1;
		Point1.x=(int)(Rect.left+x1);
		Point1.y=Rect.top;
		float x2=((Rect.bottom-Rect.top)-b)/k;
		CPoint Point2;
		Point2.x=(int)(Rect.left+x2);
		Point2.y=Rect.bottom;
		CPen Pen2(PS_SOLID,2,RGB(21,222,0));
		pDC->SelectObject(&Pen2);
		pDC->MoveTo(Point1.x,Point1.y);
		pDC->LineTo(Point2.x,Point2.y);*/
	}

	/*for(int k=0; k < PointList.size(); k++)
	{
		CPen Pen2(PS_SOLID,2,RGB(21,222,0));
		pDC->SelectObject(&Pen2);
		if(k%2 == 0)
			pDC->MoveTo(PointList[k].x,PointList[k].y);
		else
			pDC->LineTo(PointList[k].x,PointList[k].y);
		
	}*/
	
	pDC->SelectObject(Old);

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

CPoint CRedBallDlg::GetCenterPoint(CRect Rect)
{
	CPoint Temp;
	Temp.x = Rect.left+Rect.Width()/2;
	Temp.y = Rect.top +Rect.Height()/2;
	return Temp;
}

//X'=x*cos(n)+y*sin(n)
//Y'=-x*sin(n)+y*cos(n)

CRect CRedBallDlg::MapCenterPoint(CPoint Point,CRect Rect)
{
	/*int HCount=7;
	int VCount=7;
	int Width = Rect.Width()/HCount;
	int Height= Rect.Width()/VCount;*/

	double Du=(60*3.14)/180;
	CRect Temp;
	Temp.left=Rect.left*cos(Du)+Rect.top*sin(Du);
	Temp.top=Rect.left*sin(Du)+Rect.top*cos(Du);

	Temp.right=Rect.right*cos(Du)+Rect.bottom*sin(Du);
	Temp.bottom=Rect.right*cos(Du)+Rect.bottom*sin(Du);

	if(Temp.left > Temp.right)
	{
		int TempData=Temp.left;
		Temp.left=Temp.right;
		Temp.right=TempData;
	}
	if(Temp.top > Temp.bottom)
	{
		int TempData=Temp.top;
		Temp.left=Temp.bottom;
		Temp.right=TempData;
	}
	return Temp;
}

//获取抛物线参数
void CRedBallDlg::GetPaoWuXianCanShu(CPoint Point1,CPoint Point2,CPoint Point3,float& A,float& B,float& C)
{
	int X1=Point1.x-Point2.x != 0 ?Point1.x-Point2.x:1;
	int X2=Point1.x-Point3.x != 0 ?Point1.x-Point3.x:1;
	int X3=Point2.x-Point3.x != 0 ?Point2.x-Point3.x:1;

	A=(Point1.y-Point2.y)/((X1)*(X3))-(Point1.y-Point3.y)/((X2)*(X3));
	B=(Point1.y-Point3.y)/(X2)-A*(Point1.x+Point3.x);
	C=Point1.y-A*Point1.x*Point1.x+B*Point1.x;
}