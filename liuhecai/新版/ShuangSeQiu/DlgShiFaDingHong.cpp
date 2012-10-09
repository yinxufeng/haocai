// ShiFaDingHong.cpp : 实现文件
//

#include "stdafx.h"
#include "ShuangSeQiu.h"
#include "DlgShiFaDingHong.h"
#include "Markup.h"


#define FORMULA_COUNT 20
#define BEGIN_FORMULA 0
#define END_FORMULA  16

#define PAGE_COUNT 16

extern CString GetAppCurrentPath();

IMPLEMENT_DYNAMIC(CDlgShiFaDingHong, CDialog)

CDlgShiFaDingHong::CDlgShiFaDingHong(CWnd* pParent /*=NULL*/)
: CDialog(CDlgShiFaDingHong::IDD, pParent)
{
	m_IsInitData = false;
	m_CurrentIndex=0;
}

CDlgShiFaDingHong::~CDlgShiFaDingHong()
{
}

void CDlgShiFaDingHong::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
	DDX_Control(pDX, IDC_COMBO1, m_ComboBox);
}


BEGIN_MESSAGE_MAP(CDlgShiFaDingHong, CDialog)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_SEARCH_BTN, &CDlgShiFaDingHong::OnBnClickedSearchBtn)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDlgShiFaDingHong::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON5, &CDlgShiFaDingHong::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_PREV_BTN, &CDlgShiFaDingHong::OnBnClickedPrevBtn)
	ON_BN_CLICKED(IDC_NEXT_BTN, &CDlgShiFaDingHong::OnBnClickedNextBtn)
	ON_BN_CLICKED(IDC_JINXUAN_BTN, &CDlgShiFaDingHong::OnBnClickedJinxuanBtn)
END_MESSAGE_MAP()


//初始化列表头
void CDlgShiFaDingHong::InitListHeader()
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

	m_ListCtrl.InsertColumn(0,_TEXT("期号"),    LVCFMT_CENTER,	2*nWidth);
	m_ListCtrl.SetColumStyle(0,Style);

	for(int Index = 1; Index < 17; Index++)
	{
		CString Text;
		Text.Format("%02d",Index);
		m_ListCtrl.InsertColumn(Index,Text,    LVCFMT_CENTER,	nWidth);
		m_ListCtrl.SetColumStyle(Index,Style);
	}


	m_ListCtrl.InsertColumn(17,"17",    LVCFMT_CENTER,	3*nWidth);
	m_ListCtrl.SetColumStyle(17,Style);
	m_ListCtrl.InsertColumn(18,"18",    LVCFMT_CENTER,	nWidth);
	m_ListCtrl.SetColumStyle(18,Style);



	m_ListCtrl.SetRowHeight(30);
	sItemBkData ItemBkData;
	ItemBkData.m_BkFillMode = MODE_FILL_RGB;
	ItemBkData.m_HeightColor = RGB(222,22,100);
	ItemBkData.m_HeightFillMode = MODE_FILL_RGB;
	ItemBkData.m_HeightColor = RGB(100,100,100);
	ItemBkData.m_BkColor = RGB(222,222,222);
	m_ListCtrl.SetItemBkData(ItemBkData);
}

/*
定红1：[用19减上期和值的尾数+-1]        
例如：19-4=15点位14 15 16出 14
定红2：上上期的期数减上期的蓝号。
例如：？46-10=3  6两尾全出 26  QIU_COUNT
定红3：花蘑菇的独胆公式大小顺序：红5位*5：前后各取一码（大于33减33）
例如：31*5=155-99=23点位22 23 24出 22
定红4：和合点位公式：上期6红和值拆分求和是红点位！即：114=6点位05 06 07上期出 07
定红5：极合和开奖号码第二红有密切关系，极合加减第二红（大小序）大部分出左右码，有时直出，规律比较明显，好 
掌握，对预测胆码有好处。例如：第二红08极间距32-07=25极合7+8=15点位14 15 16 上期出 14
定红6：本期红1位与上上期和与差的绝对值正负1是点位一般化!
例如：146期红1位+-144期红1位07+02=9点位08 09 10上期出 08
定红7：刘大勇新出胆方法：红5位-红1位+-固定2=点位下期出胆码！期期用！
例如：32-07+2=27点位26 27 28出 26         32-07-2=23点位22 23 24出 22
定红8：公式:蓝号＊４　得数大16就减33　得数再取正负１数---期期用! 
即：10＊４=40-33=7点位06 07 08上期出 07  08
定红9：蓝尾+第三位尾=和尾是下期金胆尾----期期用！
即：0+8=8尾正确开 08
定红10：上期第六红－第五红！ 得数取个位数 杀下期尾
例：126期 31－26＝05  127期杀5尾  正确
127期 28－24＝04  128期杀4尾  正确
128期 31－27＝04  129期杀4尾  正确
*/

void CDlgShiFaDingHong::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	if(!m_IsInitData)
	{
		m_IsInitData=true;

		OnBnClickedJinxuanBtn();
	/*	m_FormulaInfoList=CFormulaCenter::GetInstance()->GetFormulaInfoByType(FORMULA_SHA_LAN_WEI);
		m_CurrentIndex=0;
		FillData(m_FormulaInfoList);
		UpdateBtnStatus();*/
	}

}



// 生成的消息映射函数
BOOL CDlgShiFaDingHong::OnInitDialog()
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

	m_ComboBox.SetCurSel(0);
	CenterWindow();

	return true;
}

void CDlgShiFaDingHong::OnClose()
{
	ShowWindow(SW_HIDE);
}

void CDlgShiFaDingHong::OnBnClickedSearchBtn()
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
	m_FormulaInfoList=CFormulaCenter::GetInstance()->SearchFormulaInfoByType(FORMULA_SHA_LAN_WEI,eSearchVType(Cursel),Data,Data1);
	FillData(m_FormulaInfoList);
	UpdateBtnStatus();

}

void CDlgShiFaDingHong::OnCbnSelchangeCombo1()
{
	OnBnClickedSearchBtn();
}


void CDlgShiFaDingHong::FillData(vector<sFormulaInfo>& FormulList)
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

	int EndIndex = FormulList.size() > 16 ? 16:FormulList.size();
	if(FormulList.empty())
		return;

	for(int Index =0; Index < EndIndex; Index++)
	{
		m_ListCtrl.SetItemText(0,Index+1,FormulList[Index].m_FormulaName);
	}

	m_ListCtrl.SetItemText(0,17,_T("统计"));
	m_ListCtrl.SetItemText(0,18,_T("对错"));

	
	for(int Index = 0; Index < EndIndex;Index++)
	{
		for(int i = 0; i < FormulList[Index].m_DataList.size(); i++)
		{
			int TempIndex = Index -BEGIN_FORMULA;
			if(TempIndex ==0)
			{
				m_ListCtrl.SetItemText(i+1,0,FormulList[Index].m_DataList[i].m_QiShu);
			}
			m_ListCtrl.SetItemText(i+1,TempIndex+1,FormulList[Index].m_DataList[i].m_Data+_T("V"));
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
		int Array[10];
		int ErrorCount=0;
		memset(Array,0,10*sizeof(int));

		for(int i=0; i < EndIndex; i++)
		{
			int Data=atoi(FormulList[i].m_DataList[Index].m_Data.GetBuffer());
			Data=Data%10;
			Array[Data]++;
			if(!FormulList[i].m_DataList[Index].m_IsTrue)
				ErrorCount++;

		}

		CString Str;

		for(int j=0; j < 10; j++)
		{
			if(Array[j])
			{
				CString Temp;
				Temp.Format("%d",j);
				Str+=Temp;
			}
		}
		Str+=_T("V");

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


		m_ListCtrl.SetItemText(Index+1,17,Str);
		m_ListCtrl.SetItemText(Index+1,18,Str2);

		if(!ErrorCount)
		{
			Style.m_DrawData.m_TextData.m_TextColor=RGB(22,22,22);
			m_ListCtrl.SetItemSpecialStyle(Index+1,17,Style);
			m_ListCtrl.SetItemSpecialStyle(Index+1,18,Style);
		}
		else
		{
			Style.m_DrawData.m_TextData.m_TextColor=RGB(222,0,0);
			m_ListCtrl.SetItemSpecialStyle(Index+1,17,Style);
			m_ListCtrl.SetItemSpecialStyle(Index+1,18,Style);
		}


		SetDlgItemText(IDC_RESULT,Str);

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
		m_ListCtrl.SetItemText(DataSize+1,18,TempStr);
		Style.m_DrawData.m_TextData.m_TextColor=RGB(222,0,0);
		m_ListCtrl.SetItemSpecialStyle(DataSize+1,18,Style);
	}
}

void CDlgShiFaDingHong::OnBnClickedButton5()
{
	m_FormulaInfoList=CFormulaCenter::GetInstance()->GetFormulaInfoByType(FORMULA_SHA_LAN_WEI);
	m_CurrentIndex=0;
	FillData(m_FormulaInfoList);
	UpdateBtnStatus();
}

void CDlgShiFaDingHong::OnBnClickedPrevBtn()
{
	
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

void CDlgShiFaDingHong::OnBnClickedNextBtn()
{
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

void CDlgShiFaDingHong::UpdateBtnStatus()
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

void CDlgShiFaDingHong::OnBnClickedJinxuanBtn()
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
		m_FormulaInfoList=CFormulaCenter::GetInstance()->GetFormulaInfoByType(FORMULA_SHA_LAN_WEI);
	}
	else
		m_FormulaInfoList=CFormulaCenter::GetInstance()->GetFormulaInfoByName(FORMULA_SHA_LAN_WEI,NameList);

	m_CurrentIndex=0;
	FillData(m_FormulaInfoList);
	UpdateBtnStatus();
}
