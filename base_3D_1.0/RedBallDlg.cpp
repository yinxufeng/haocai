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
	m_IsShowHong=false;
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
	ON_BN_CLICKED(IDC_HONG_BTN, &CRedBallDlg::OnBnClickedHongBtn)
	ON_BN_CLICKED(IDC_LAN_BTN, &CRedBallDlg::OnBnClickedLanBtn)
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


			vector<int> ListData2;
			if(!m_IsShowHong)
			{
				int date=atoi(m_DataList[TempIndex].m_QiShu.GetBuffer());
				date+=m_DataList[TempIndex].m_LanQiu;
				srand(m_DataList[TempIndex].m_LanQiu);
				int TempData=abs(rand()%16);
				TempData=TempData%16;
				ListData2.push_back(TempData);
				DrawData2(&MemDC,TempRect,m_DataList[TempIndex].m_LanQiu,ListData2);
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
							ListData.push_back((m_DataList[TempIndex-k].m_LanQiu+4)%QIU_COUNT);
						else
							ListData.push_back(m_DataList[TempIndex-k].m_LanQiu);
					}
				}

				DrawData(&MemDC,TempRect,m_DataList[TempIndex].m_LanQiu,ListData);
			}
			else
			{
				for(int f=0; f < 6; f++)
					ListData2.push_back(m_DataList[TempIndex].m_HongQiu[f]);
				DrawData2(&MemDC,TempRect,0,ListData2);

				/*vector<int> ListData;
				for(int k=3; k >= 0; k--)
				{
					ListData.push_back(m_DataList[TempIndex-k].m_HongQiu[k]);
				}

				DrawData(&MemDC,TempRect,0,ListData);*/
			}

			

		
			
			Count++;
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

void CRedBallDlg::DrawData2(CDC* pDC,CRect Rect,int Data,vector<int>&DataList)
{
	int HCount=4;
	int VCount=4;
	if(m_IsShowHong)
	{
		VCount=6;
		HCount=6;
	}
	int Width = Rect.Width()/HCount;
	int Height= Rect.Width()/VCount;


	CPen pen(PS_SOLID,1,RGB(110,110,110));
	CPen* old=(CPen*)pDC->SelectObject(&pen);
	pDC->MoveTo(Rect.left,Rect.top);
	pDC->LineTo(Rect.right,Rect.bottom);
	pDC->MoveTo(Rect.right,Rect.top);
	pDC->LineTo(Rect.left,Rect.bottom);

	pDC->SelectObject(old);


	int DrawData=0;

	int Row = Data%HCount;
	int Colun=Data/VCount;



	CRect ERect=Rect;
	ERect.left = Rect.left+Width*(Colun);
	ERect.right = ERect.left+3*Width;
	ERect.top = Rect.top + Height*(Row);
	ERect.bottom =ERect.top + 3*Height;
	//pDC->Ellipse(ERect);



	for(int i = 0; i < HCount; i++)
	{
		for(int j=0; j < VCount; j++)
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

			for(int Index=0; Index < DataList.size(); Index++)
			{
				if(DrawData == DataList[Index] && DrawData !=Data)
					pDC->FillSolidRect(TempRect,RGB(222,222,0));
			}

		
			pDC->DrawText(Text,TempRect, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		}

	}
}

void CRedBallDlg::DrawData(CDC* pDC,CRect Rect,int Data,vector<int>&DataList)
{
	int HCount=4;
	int VCount=4;
	if(m_IsShowHong)
	{
		VCount=6;
		HCount=6;
	}
	int Width = Rect.Width()/HCount;
	int Height= Rect.Width()/VCount;

	int DrawData=0;
	vector<CPoint> PointList;

	for(int i = 0; i < VCount; i++)
	{
		for(int j=0; j < HCount; j++)
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

			/*CString Text;
			Text.Format("%02d",DrawData);*/
			if(DrawData == Data)
			{
			//	pDC->FillSolidRect(TempRect,RGB(255,0,0));
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
	
		//	pDC->DrawText(Text,TempRect, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		}
	}

	

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

		CPen Pen2(PS_SOLID,2,RGB(21,222,0));
		pDC->SelectObject(&Pen2);
		
			pDC->MoveTo(PointList[2].x,PointList[2].y);
			pDC->LineTo(PointList[3].x,PointList[3].y);

	}
	
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

void CRedBallDlg::OnBnClickedHongBtn()
{
	m_IsShowHong=true;
	this->Invalidate();
}

void CRedBallDlg::OnBnClickedLanBtn()
{
	m_IsShowHong=false;
	Invalidate();
}
