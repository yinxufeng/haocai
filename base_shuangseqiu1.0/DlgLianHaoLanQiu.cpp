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

extern CString GetAppCurrentPath();



IMPLEMENT_DYNAMIC(CDlgLianHaoLanQiu, CDialog)

CDlgLianHaoLanQiu::CDlgLianHaoLanQiu(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLianHaoLanQiu::IDD, pParent)
{
	m_IsInitData = false;
	m_CurrentIndex=0;
    m_FormulaType=FORMULA_SHA_LAN;
	bool                 m_ReLoadData=false;
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
	ON_BN_CLICKED(IDC_ZIDONG_BTN, &CDlgLianHaoLanQiu::OnBnClickedZidongBtn)
	ON_BN_CLICKED(IDC_TONGJI_BTN, &CDlgLianHaoLanQiu::OnBnClickedTongjiBtn)
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

	m_ComboBox.InsertString(4,"球尾小于");
	m_ComboBox.InsertString(5,"球尾等于");
	m_ComboBox.InsertString(6,"球尾大于");
	m_ComboBox.InsertString(7,"球尾区间");
	m_ComboBox.InsertString(8,"最后一次错");

	m_ComboBox.InsertString(9,"球大于");
	m_ComboBox.InsertString(10,"球等于");
	m_ComboBox.InsertString(11,"球小于");
	m_ComboBox.InsertString(12,"球区间");

	m_ComboBox.SetCurSel(0);

	m_DlgDrawTiaoXing.Create(CDlgDrawTiaoXing::IDD,this);
	m_DlgDrawTiaoXing.ShowWindow(SW_HIDE);
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
	m_FormulaInfoList=CFormulaCenter::GetInstance()->SearchFormulaInfoByType(m_FormulaType,eSearchVType(Cursel),Data,Data1);
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

	vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
	int DataSize = DataList->size();
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
		int TempArray[QIU_COUNT+1];
		memset(TempArray,0,(QIU_COUNT+1)*sizeof(int));

		for(int i = 0; i < FormulList[Index].m_DataList.size(); i++)
		{
			int TempIndex = Index;
			if(TempIndex ==0)
			{
				CString QiShu=FormulList[Index].m_DataList[i].m_QiShu;
				if(i+1 < DataList->size())
				{
					CString TempStr;
					TempStr.Format(" %02d",(*DataList)[i+1].m_LanQiu);
					QiShu=(*DataList)[i+1].m_QiShu+TempStr;
				}
				m_ListCtrl.SetItemText(i+1,0,QiShu);
			}
			int TempData=atoi(FormulList[Index].m_DataList[i].m_Data.GetBuffer());
			FormulList[Index].m_DataList[i].m_Data.ReleaseBuffer();
			if(TempData>=0 && TempData <= QIU_COUNT && FormulList[Index].m_DataList[i].m_IsTrue)
				TempArray[TempData]++;

			m_ListCtrl.SetItemText(i+1,TempIndex+1,FormulList[Index].m_DataList[i].m_Data);
			if(FormulList[Index].m_DataList[i].m_IsTrue)
			{
				if(Index %2 == 0)
					Style.m_DrawData.m_TextData.m_TextColor=RGB(22,22,22);
				else
					Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);

				Style.m_DrawData.m_TextData.m_BGColor =RGB(205,250,213);
				m_ListCtrl.SetItemSpecialStyle(i+1,TempIndex+1,Style);
			}
			else
			{

				Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);
				Style.m_DrawData.m_TextData.m_BGColor = RGB(248,183,173);
				m_ListCtrl.SetItemSpecialStyle(i+1,TempIndex+1,Style);
			}
		}

	/*	if(m_FormulaType == FORMULA_DING_HONG_WEI)
		{
			for(int i = 0; i < FormulList[Index].m_DataList.size(); i++)
			{
				int TempIndex = Index;
				if(FormulList[Index].m_DataList[i].m_IsTrue && !FormulList[Index].m_DataList[i].m_Data.IsEmpty())
				{
					int TempData=atoi(FormulList[Index].m_DataList[i].m_Data.GetBuffer());
					FormulList[Index].m_DataList[i].m_Data.ReleaseBuffer();
					Style.m_DrawData.m_TextData.m_TextColor=RGB(0,0,0);
					Style.m_DrawData.m_TextData.m_BGColor =GetColor(TempArray[TempData]);
					m_ListCtrl.SetItemSpecialStyle(i+1,TempIndex+1,Style);
				}
			}
		}*/
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
	m_FormulaInfoList=CFormulaCenter::GetInstance()->GetFormulaInfoByType(m_FormulaType);
	
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

		if(Type == m_FormulaType && !Name.IsEmpty())
			NameList.push_back(Name);
			
		Xml.OutOfElem();
	}

	if(NameList.empty())
	{
		m_FormulaInfoList=CFormulaCenter::GetInstance()->GetFormulaInfoByType(m_FormulaType);
	}
	else
		m_FormulaInfoList=CFormulaCenter::GetInstance()->GetFormulaInfoByName(m_FormulaType,NameList);

	m_CurrentIndex=0;
	FillData(m_FormulaInfoList);
	UpdateBtnStatus();
}

void CDlgLianHaoLanQiu::OnBnClickedZidongBtn()
{
	
	m_CurrentIndex=0;
	m_FormulaInfoList=AutoFindJiXian(m_FormulaInfoList);
	FillData(m_FormulaInfoList);
	UpdateBtnStatus();
}

//设置窗口标题
void CDlgLianHaoLanQiu::SetWondowsTitle(CString Title,eFormulaType Type)
{
	if(Type != m_FormulaType)
	{
		m_FormulaType=Type;
		SetWindowText(Title);
		m_ListCtrl.DeleteAllItems();
		OnBnClickedJingxuanBtn();

		if(m_FormulaType >= FORMUAL_SHA_JI_JU && m_FormulaType <=FORMUAL_SHA_NEW_JIXIAN_LAN)
		{
			GetDlgItem(IDC_TONGJI_BTN)->EnableWindow(true);
		}
		else
			GetDlgItem(IDC_TONGJI_BTN)->EnableWindow(false);

	}
}

//获取颜色值
COLORREF CDlgLianHaoLanQiu::GetColor(int Data)
{
	switch(Data)
	{
	case 0:
		return RGB(112,48,160);
	case 1:
		return RGB(255,0,0);
	case 2:
		return RGB(198,198,200);
	case 3:
		return RGB(255,192,0);
	/*case 4:
		return RGB(128,128,128);*/

	default:
		return RGB(128,128,128);

	/*default:
		return RGB(248,183,173);*/
	}
}

//自动寻找极限
vector<sFormulaInfo> CDlgLianHaoLanQiu::AutoFindJiXian(vector<sFormulaInfo>& FormulList)
{
	vector<sFormulaInfo> WantList;
	for(int Index = 0; Index < FormulList.size(); Index++)
	{

		bool IsWant=false;
		int Count=FormulList[Index].m_ErrorCount+FormulList[Index].m_TrueCount;
		if(Count > 0 && (FormulList[Index].m_TrueCount*100)/Count > 98 )
		{
			WantList.push_back(FormulList[Index]);
			continue;
		}


		int TrueCount = 0;
		int ErrorCount=0;



		sFormulaInfo Formula = FormulList[Index];
		for(int i = Formula.m_DataList.size()-2; i >= 0; i--)
		{
			if(i <  0 )
				break;

			
			bool IsTrue=Formula.m_DataList[ Formula.m_DataList.size()-2].m_IsTrue;
			if(!IsTrue)
			{
				if(!Formula.m_DataList[i].m_IsTrue)
				{
					ErrorCount++;
					continue;
				}
			}
			else
			{
				if(Formula.m_DataList[i].m_IsTrue)
				{
					TrueCount++;
				}
				else
				{
					break;
				}
			}
		}

		/*if(TrueCount)
		{
			if(TrueCount > ( Formula.m_MinLianDuiCount+2) && TrueCount < ( Formula.m_MaxLianDuiCount-3))
			{
				WantList.push_back(Formula);
		    	continue;
			}
		}*/

		if(ErrorCount)
		{
			if(ErrorCount >= Formula.m_MaxLianCuoCount)
			{
				WantList.push_back(Formula);
		    	continue;
			}

		}
	}

	return WantList;

}

//统计错误信息
void CDlgLianHaoLanQiu::TongJiErrorInfo(vector<sDrawInfoList>& DrawAllInfo)
{

	CString FilePath=GetAppCurrentPath()+_T("error_tongji.txt");
	
	DWORD Flag = CREATE_ALWAYS;
	HANDLE FileHandle=CreateFile(FilePath,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL,Flag,FILE_ATTRIBUTE_NORMAL,NULL);
	if(FileHandle == INVALID_HANDLE_VALUE)
		return;

	CString FilePath2=GetAppCurrentPath()+_T("true_tongji.txt");
	HANDLE FileHandle2=CreateFile(FilePath2,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL,Flag,FILE_ATTRIBUTE_NORMAL,NULL);
	if(FileHandle2 == INVALID_HANDLE_VALUE)
		return;

	

	CString Title;
	GetWindowText(Title);
	Title+=_T("\r\n");
	DWORD WriteBytes=0;
	::WriteFile(FileHandle,Title.GetBuffer(),Title.GetLength(),&WriteBytes,NULL);
	Title.ReleaseBuffer();
	::WriteFile(FileHandle2,Title.GetBuffer(),Title.GetLength(),&WriteBytes,NULL);
	Title.ReleaseBuffer();

	vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();



	int DataSize = DataList->size();

	

	for(int Index = 1; Index < DataSize+1; Index++)
	{
		CString WriteLine= Index + 1 > DataSize ? "下期               ":(*DataList)[Index].ToString()+_T("             ");
		CString WriteLine2=Index + 1 > DataSize ? "下期                             ":(*DataList)[Index].ToString()+_T("     ");

		map<CString,vector<CString>> MapData;

		int ErrorCount=0;
		int ErrorSize=0;
		CString ErrorDataStr;


		for(int i=0; i < m_FormulaInfoList.size(); i++)
		{


			if(!m_FormulaInfoList[i].m_DataList[Index-1].m_IsTrue && Index != DataSize)
			{
				CString Str;
				Str.Format("%s ",m_FormulaInfoList[i].m_DataList[Index-1].m_TrueBaiFenBi);

				for(int j=Str.GetLength(); j < 10; j++)
					Str+=_T(" ");

				int Data=atoi(m_FormulaInfoList[i].m_DataList[Index-1].m_TrueBaiFenBi.GetBuffer());
				m_FormulaInfoList[i].m_DataList[Index-1].m_TrueBaiFenBi.ReleaseBuffer();
				ErrorCount+=Data;
				ErrorSize++;
				ErrorDataStr=m_FormulaInfoList[i].m_DataList[Index-1].m_Data;
				WriteLine+=Str;

			}
			
			
			MapData[m_FormulaInfoList[i].m_DataList[Index-1].m_Data].push_back(m_FormulaInfoList[i].m_DataList[Index-1].m_TrueBaiFenBi);

		}


		sDrawInfoList DrawInfoList;
		DrawInfoList.m_QiShu = Index + 1 > DataSize ? "下期 ":(*DataList)[Index].m_QiShu;
		
		map<CString,vector<CString>>::iterator it = MapData.begin(); 
		for(it ; it != MapData.end(); it++)
		{
			sDrawDataInfo DrawData;

			int AllData=0;
			for(int k=0; k < it->second.size(); k++)
			{
				int Data=atoi(it->second[k].GetBuffer());
				DrawData.m_InfoList.push_back(it->second[k]);
				it->second[k].ReleaseBuffer();
				AllData+=Data;
			}

			int ArgvData=AllData/it->second.size();
			

			

			CString TempStr;
			TempStr.Format("%02d",ArgvData);
			DrawData.m_DrawText = TempStr;

			if(it->first ==ErrorDataStr)
				DrawData.m_IsTrue = false;
			else
				DrawData.m_IsTrue = true;

			for(int i=TempStr.GetLength(); i < 4; i++)
					TempStr+=_T(" ");

			DrawInfoList.m_DrawDataList.push_back(DrawData);

			WriteLine2+=TempStr;

		}

		DrawAllInfo.push_back(DrawInfoList);

		CString ErrorStr;
		if(ErrorSize > 0)
			ErrorStr.Format("    %s ：%02d",ErrorDataStr,ErrorCount/ErrorSize);
		else
			ErrorStr.Format("   %s",ErrorDataStr);


		WriteLine2+=ErrorStr+_T("\r\n");
		WriteLine+=ErrorStr+_T("\r\n");

	    WriteBytes=0;
		::WriteFile(FileHandle,WriteLine.GetBuffer(),WriteLine.GetLength(),&WriteBytes,NULL);
		WriteLine.ReleaseBuffer();
		::WriteFile(FileHandle2,WriteLine2.GetBuffer(),WriteLine2.GetLength(),&WriteBytes,NULL);
		WriteLine2.ReleaseBuffer();
	}


	CloseHandle(FileHandle);
	CloseHandle(FileHandle2);

	return ;
	//ShellExecute(NULL, "open",FilePath2, NULL, NULL, SW_SHOWNORMAL);
}

////统计公式信息
//void CFormulaCenter::ToJiFormulaInfo(sFormulaInfo& Formula)
//{
//	int                    MaxLianCuoCount=0;    
//	int                    MaxLianDuiCount=0;      
//	int                    MinLianCuoCount=0;      
//	int                    MinLianDuiCount=0;    
//	int                    ErrorCount=0;      
//	int                    TrueCount = 0;
//	bool                   LastStatus=false;  
//
//
//	int                    TempLianCuoCount=0;    
//	int                    TempLianDuiCount=0; 
//
//
//
//	for(int Index = 0; Index < Formula.m_DataList.size(); Index++)
//	{
//		if(Formula.m_DataList[Index].m_IsTrue)
//		{
//			TrueCount++;
//			if(MaxLianCuoCount < TempLianCuoCount)
//				MaxLianCuoCount = TempLianCuoCount;
//			else if(MinLianCuoCount > TempLianCuoCount)
//				MinLianCuoCount = TempLianCuoCount;
//			TempLianCuoCount=0;
//			TempLianDuiCount++;
//		}
//		else
//		{
//			ErrorCount++;
//			if(MaxLianDuiCount < TempLianDuiCount)
//				MaxLianDuiCount = TempLianDuiCount;
//			else if(MinLianDuiCount > TempLianDuiCount)
//				MinLianDuiCount = TempLianDuiCount;
//			TempLianDuiCount=0;
//
//			TempLianDuiCount  = 0;
//			TempLianCuoCount++;
//		}
//
//		if(Index == Formula.m_DataList.size()-2)
//			LastStatus = Formula.m_DataList[Index].m_IsTrue;
//	}
//
//	Formula.m_ErrorCount      = ErrorCount;
//	Formula.m_TrueCount       = TrueCount;
//	Formula.m_MaxLianCuoCount = MaxLianCuoCount;
//	Formula.m_MinLianCuoCount = MinLianCuoCount;
//	Formula.m_MaxLianDuiCount = MaxLianDuiCount;
//	Formula.m_MaxLianCuoCount = MaxLianCuoCount;
//	Formula.m_LastStatus      = LastStatus;
//
//}
void CDlgLianHaoLanQiu::OnBnClickedTongjiBtn()
{
	static eFormulaType  FormualType=(eFormulaType)-1;
	CString Title;
	GetWindowText(Title);

	if(FormualType != m_FormulaType)
	{
		vector<sDrawInfoList> DrawAllInfo;
		TongJiErrorInfo(DrawAllInfo);
		int TiaoXingCount=33;
		if(m_FormulaType == FORMUAL_SHA_NEW_JIXIAN_LAN)
			TiaoXingCount=16;

		m_DlgDrawTiaoXing.SetDrawData(DrawAllInfo,Title,TiaoXingCount);
		FormualType=m_FormulaType;
	}

	m_DlgDrawTiaoXing.ShowWindow(SW_SHOW);
}
