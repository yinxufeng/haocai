// DlgLianHaoLanQiu.cpp : 实现文件
//

#include "stdafx.h"
#include "ShuangSeQiu.h"
#include "DlgLianHaoLanQiu.h"
#include "FormulaCenter.h"
#include "Markup.h"

// CDlgLianHaoLanQiu 对话框

#define FORMULA_COUNT 24
#define PAGE_COUNT 22

//获取模块路径
CString GetAppCurrentPath3()
{
	CString server_ip;
	CString StrDes=_T("");
	::GetModuleFileName(NULL,StrDes.GetBuffer(MAX_PATH),MAX_PATH); 
	//::GetCurrentDirectory(MAX_PATH,StrDes.GetBuffer(MAX_PATH));
	StrDes.ReleaseBuffer();
	StrDes=StrDes.Left(StrDes.ReverseFind('\\'));
	if(StrDes.Right(1)!='\\')
		StrDes+="\\";

	return StrDes;
}



IMPLEMENT_DYNAMIC(CDlgLianHaoLanQiu, CDialog)

CDlgLianHaoLanQiu::CDlgLianHaoLanQiu(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLianHaoLanQiu::IDD, pParent)
{
	m_IsInitData = false;
	m_CurrentIndex=0;
}

CDlgLianHaoLanQiu::~CDlgLianHaoLanQiu()
{
}

void CDlgLianHaoLanQiu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
	DDX_Control(pDX, IDC_COMBO1, m_ComboBox);
}


BEGIN_MESSAGE_MAP(CDlgLianHaoLanQiu, CDialog)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_SEARCH_BTN, &CDlgLianHaoLanQiu::OnBnClickedSearchBtn)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_PREV_BTN, &CDlgLianHaoLanQiu::OnBnClickedPrevBtn)
	ON_BN_CLICKED(IDC_NEXT_BTN, &CDlgLianHaoLanQiu::OnBnClickedNextBtn)
	ON_BN_CLICKED(IDC_BUTTON5, &CDlgLianHaoLanQiu::OnBnClickedButton5)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDlgLianHaoLanQiu::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_JINGXUAN_BTN, &CDlgLianHaoLanQiu::OnBnClickedJingxuanBtn)
END_MESSAGE_MAP()


// CDlgLianHaoLanQiu 消息处理程序

//初始化列表头
void CDlgLianHaoLanQiu::InitListHeader()
{
	CRect Rect;
	//初始化应用程序列表控件
	m_ListCtrl.GetWindowRect(&Rect);
	int nWidth = Rect.Width()/(FORMULA_COUNT+2);

	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(222,0,0);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;

	m_ListCtrl.InsertColumn(0,_TEXT("期数"),    LVCFMT_CENTER,	2*nWidth);
	m_ListCtrl.SetColumStyle(0,Style);

	for(int Index = 1; Index <= PAGE_COUNT; Index++)
	{
		CString Str;
		Str.Format("%02d",Index);
		m_ListCtrl.InsertColumn(Index,Str,    LVCFMT_CENTER,	nWidth);
		m_ListCtrl.SetColumStyle(Index,Style);
	}

	m_ListCtrl.InsertColumn(PAGE_COUNT+1,"统计",    LVCFMT_CENTER,	nWidth);
	m_ListCtrl.SetColumStyle(PAGE_COUNT+1,Style);
	m_ListCtrl.InsertColumn(PAGE_COUNT+2,"对错",    LVCFMT_CENTER,	nWidth);
	m_ListCtrl.SetColumStyle(PAGE_COUNT+2,Style);

	
	m_ListCtrl.SetRowHeight(30);
	m_ListCtrl.ShowHeader(true);

	sItemBkData ItemBkData;
	ItemBkData.m_BkFillMode = MODE_FILL_RGB;
	ItemBkData.m_HeightColor = RGB(222,22,100);
	ItemBkData.m_HeightFillMode = MODE_FILL_RGB;
	ItemBkData.m_HeightColor = RGB(100,100,100);
	ItemBkData.m_BkColor = RGB(222,222,222);
	m_ListCtrl.SetItemBkData(ItemBkData);

}

void CDlgLianHaoLanQiu::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	CDialog::OnShowWindow(bShow, nStatus);
	if(!m_IsInitData)
	{
		m_IsInitData = true;
		sItemStyle Style;
		Style.m_ItemType = TEXT_TYPE;
		Style.m_DrawData.m_TextData.m_TextColor=RGB(222,0,0);
		Style.m_DrawData.m_TextData.m_TextFont = NULL;
		Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;

		m_ListCtrl.DeleteAllItems();
		OnBnClickedJingxuanBtn();
	
	}
			
}

// 生成的消息映射函数
BOOL CDlgLianHaoLanQiu::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitListHeader();

	m_ComboBox.InsertString(0,"正确率大于");
	m_ComboBox.InsertString(1,"正确率等于");
	m_ComboBox.InsertString(2,"正确率小于");
	m_ComboBox.InsertString(3,"正确率区间");

	m_ComboBox.InsertString(4,"特码尾小于");
	m_ComboBox.InsertString(5,"特码尾等于");
	m_ComboBox.InsertString(6,"特码尾大于");
	m_ComboBox.InsertString(7,"特码尾区间");
	m_ComboBox.InsertString(8,"最后一次错");

	m_ComboBox.InsertString(9,"特码大于");
	m_ComboBox.InsertString(10,"特码等于");
	m_ComboBox.InsertString(11,"特码小于");
	m_ComboBox.InsertString(12,"特码区间");

	m_ComboBox.SetCurSel(0);
	CenterWindow();
	return true;
}

void CDlgLianHaoLanQiu::OnClose()
{
	ShowWindow(SW_HIDE);
}

void CDlgLianHaoLanQiu::OnBnClickedSearchBtn()
{
	int Cursel=m_ComboBox.GetCurSel();
	int Data=-1;
	int Data1=-1;
	CString Text;
	GetDlgItemText(IDC_EDIT1,Text);
	if(!Text.IsEmpty())
		Data = atoi(Text.GetBuffer());
	Text.Empty();
	GetDlgItemText(IDC_EDIT6,Text);
	if(!Text.IsEmpty())
		Data1=atoi(Text.GetBuffer());
	m_CurrentIndex=0;
	m_FormulaInfoList=CFormulaCenter::GetInstance()->SearchFormulaInfoByType(FORMULA_SHA_LAN,eSearchVType(Cursel),Data,Data1);
	FillData(m_FormulaInfoList);
	UpdateBtnStatus();
}

BOOL CDlgLianHaoLanQiu::OnEraseBkgnd(CDC* pDC)
{

	return CDialog::OnEraseBkgnd(pDC);
}

void CDlgLianHaoLanQiu::FillData(vector<sFormulaInfo>& FormulList)
{
	sItemStyle Style;
	Style.m_ItemType = TEXT_TYPE;
	Style.m_DrawData.m_TextData.m_TextColor=RGB(222,0,0);
	Style.m_DrawData.m_TextData.m_TextFont = NULL;
	Style.m_DrawData.m_TextData.m_TextFormat=DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS;

	m_ListCtrl.DeleteAllItems();
	int DataSize = CDataManageCenter::GetInstance()->GetDataList()->size();
	for(int Index = 0; Index < DataSize; Index++)
	{
		m_ListCtrl.InsertItem(Index,_T(""));	
	}

	m_ListCtrl.InsertItem(DataSize+1,_T(""));

	int EndIndex = FormulList.size() > PAGE_COUNT ? PAGE_COUNT:FormulList.size();
	if(FormulList.empty())
		return;

	for(int Index =0; Index < EndIndex; Index++)
	{
		m_ListCtrl.SetItemText(0,Index+1,FormulList[Index].m_FormulaName);
	}

	m_ListCtrl.SetItemText(0,PAGE_COUNT+1,_T("统计"));
	m_ListCtrl.SetItemText(0,PAGE_COUNT+2,_T("对错"));

	
	for(int Index = 0; Index < EndIndex;Index++)
	{
		for(int i = 0; i < FormulList[Index].m_DataList.size(); i++)
		{
			int TempIndex = Index;
			if(TempIndex ==0)
			{
				m_ListCtrl.SetItemText(i+1,0,FormulList[Index].m_DataList[i].m_QiShu);
			}
			m_ListCtrl.SetItemText(i+1,TempIndex+1,FormulList[Index].m_DataList[i].m_Data);
			if(FormulList[Index].m_DataList[i].m_IsTrue)
			{
				if(Index %2 == 0)
					Style.m_DrawData.m_TextData.m_TextColor=RGB(22,22,22);
				else
					Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);

				m_ListCtrl.SetItemSpecialStyle(i+1,TempIndex+1,Style);
			}
			else
			{

				Style.m_DrawData.m_TextData.m_TextColor=RGB(222,0,0);
				m_ListCtrl.SetItemSpecialStyle(i+1,TempIndex+1,Style);
			}
		}
	}

	int AllErrorCount=0;
	int AllTrueCount=0;

	for(int Index = 0; Index < FormulList[0].m_DataList.size(); Index++)
	{
		int ErrorCount=0;
		
		int Array[50];
		memset(Array,0,50*sizeof(int));
		for(int i=0; i < EndIndex; i++)
		{
			int Data=abs(atoi(FormulList[i].m_DataList[Index].m_Data.GetBuffer()));
			if(!FormulList[i].m_DataList[Index].m_IsTrue)
				ErrorCount++;

			if(Index == FormulList[0].m_DataList.size()-1)
				Array[Data]++;

		}


		CString Str2;

		if(ErrorCount)
		{
			Str2="错";
			AllErrorCount++;
		}
		else
		{
			Str2="对";
			AllTrueCount++;
		}

		CString Temp;
		Temp.Format("%02d",ErrorCount);

		m_ListCtrl.SetItemText(Index+1,PAGE_COUNT+1,Temp);
		m_ListCtrl.SetItemText(Index+1,PAGE_COUNT+2,Str2);

		if(!ErrorCount)
		{
			Style.m_DrawData.m_TextData.m_TextColor=RGB(22,22,22);
			m_ListCtrl.SetItemSpecialStyle(Index+1,PAGE_COUNT+1,Style);
			m_ListCtrl.SetItemSpecialStyle(Index+1,PAGE_COUNT+2,Style);
		}
		else
		{
			Style.m_DrawData.m_TextData.m_TextColor=RGB(222,0,0);
			m_ListCtrl.SetItemSpecialStyle(Index+1,PAGE_COUNT+1,Style);
			m_ListCtrl.SetItemSpecialStyle(Index+1,PAGE_COUNT+2,Style);
		}


		CString Str;
		int TempCount=0;
		for(int k= 0; k < 50; k++)
		{
			if(Array[k])
			{
				CString TempStr;
				TempStr.Format("%02d ",k);
				Str+=TempStr;
				TempCount++;
			}

		}

		CString TempStr2;
		TempStr2.Format("杀号个数=%02d 杀号= ",TempCount);
		Str=TempStr2+Str;
		 
		//SetDlgItemText(IDC_RESULT2,Str);
		GetDlgItem(IDC_RESULT2)->SetWindowText(Str);

	}




	m_ListCtrl.InsertItem(DataSize+2,_T(""));
	m_ListCtrl.SetItemText(DataSize+2,0,_T("正确率"));
	for(int Index = 0; Index < EndIndex; Index++)
	{
		int TempIndex = Index ;
		CString Str;
		if(FormulList[Index].m_ErrorCount+FormulList[Index].m_TrueCount != 0)
			Str.Format(_T("%d%%"),FormulList[Index].m_TrueCount*100/(FormulList[Index].m_ErrorCount+FormulList[Index].m_TrueCount));
		m_ListCtrl.SetItemText(DataSize+1,TempIndex+1,Str);
		Style.m_DrawData.m_TextData.m_TextColor=RGB(222,0,0);
		m_ListCtrl.SetItemSpecialStyle(DataSize,TempIndex+1,Style);
	}

	if(AllErrorCount+AllTrueCount)
	{
		CString TempStr;
		TempStr.Format(_T("%d%%"),AllTrueCount*100/(AllErrorCount+AllTrueCount));
		m_ListCtrl.SetItemText(DataSize+1,PAGE_COUNT+2,TempStr);
		Style.m_DrawData.m_TextData.m_TextColor=RGB(222,0,0);
		m_ListCtrl.SetItemSpecialStyle(DataSize+1,18,Style);
	}
}

void CDlgLianHaoLanQiu::OnBnClickedPrevBtn()
{
	if(m_FormulaInfoList.empty())
		return;

	int Count=0;
	m_CurrentIndex-=PAGE_COUNT;
	if(m_CurrentIndex < 0)
		m_CurrentIndex=0;

	Count=m_CurrentIndex+PAGE_COUNT;
	if(Count > m_FormulaInfoList.size())
		Count=m_FormulaInfoList.size()-1;

	UpdateBtnStatus();




	vector<sFormulaInfo>::iterator it = m_FormulaInfoList.begin();
	vector<sFormulaInfo> Temp;
	Temp.insert(Temp.begin(),it+m_CurrentIndex,it+Count);
	FillData(Temp);
}

void CDlgLianHaoLanQiu::OnBnClickedNextBtn()
{
	if(m_FormulaInfoList.empty())
		return;

		m_CurrentIndex+=PAGE_COUNT;
	if(m_CurrentIndex >= m_FormulaInfoList.size())
		m_CurrentIndex=m_FormulaInfoList.size()-1;

	int Count = m_CurrentIndex+PAGE_COUNT;
	if(Count >= m_FormulaInfoList.size()-1)
		Count=m_FormulaInfoList.size()-1;


	vector<sFormulaInfo>::iterator it = m_FormulaInfoList.begin();
	vector<sFormulaInfo> Temp;
	Temp.insert(Temp.begin(),it+m_CurrentIndex,it+Count);
	FillData(Temp);
	UpdateBtnStatus();
}

void CDlgLianHaoLanQiu::OnBnClickedButton5()
{
	m_FormulaInfoList=CFormulaCenter::GetInstance()->GetFormulaInfoByType(FORMULA_SHA_LAN);
	m_CurrentIndex=0;
	FillData(m_FormulaInfoList);
	UpdateBtnStatus();
}

void CDlgLianHaoLanQiu::UpdateBtnStatus()
{
	if(m_CurrentIndex + PAGE_COUNT < m_FormulaInfoList.size())
		GetDlgItem(IDC_NEXT_BTN)->EnableWindow(true);
	else
		GetDlgItem(IDC_NEXT_BTN)->EnableWindow(false);

	if(m_CurrentIndex - PAGE_COUNT < 0)
		GetDlgItem(IDC_PREV_BTN)->EnableWindow(false);
	else
		GetDlgItem(IDC_PREV_BTN)->EnableWindow(true);

}
void CDlgLianHaoLanQiu::OnCbnSelchangeCombo1()
{
		OnBnClickedSearchBtn();
}

void CDlgLianHaoLanQiu::OnBnClickedJingxuanBtn()
{
	CMarkup Xml;
	CString FormulaName=GetAppCurrentPath()+"FormulaNameList.xml";
	Xml.Load(FormulaName.GetBuffer());
	FormulaName.ReleaseBuffer();

	vector<CString> NameList;

	while(Xml.FindChildElem("FormulaInfo"))
	{
		Xml.IntoElem();
		Xml.FindChildElem("FormulaName");
		CString Name=Xml.GetChildData().c_str();

		Xml.FindChildElem("FormulaType");
		CString StrType=Xml.GetChildData().c_str();
		
		int Type = atoi(StrType.GetBuffer());
		StrType.ReleaseBuffer();

		if(Type == FORMULA_SHA_LAN_WEI && !Name.IsEmpty())
			NameList.push_back(Name);
			
		Xml.OutOfElem();
	}

	if(NameList.empty())
	{
		m_FormulaInfoList=CFormulaCenter::GetInstance()->GetFormulaInfoByType(FORMULA_SHA_LAN);
	}
	else
		m_FormulaInfoList=CFormulaCenter::GetInstance()->GetFormulaInfoByName(FORMULA_SHA_LAN,NameList);

	m_CurrentIndex=0;
	FillData(m_FormulaInfoList);
	UpdateBtnStatus();
}
