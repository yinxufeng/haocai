// ShiFaDingHong.cpp : 实现文件
//

#include "stdafx.h"
#include "ShuangSeQiu.h"
#include "DlgShiFaDingHong.h"


// CShiFaDingHong 对话框

IMPLEMENT_DYNAMIC(CDlgShiFaDingHong, CDialog)

CDlgShiFaDingHong::CDlgShiFaDingHong(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShiFaDingHong::IDD, pParent)
{
	m_IsInitData = false;
}

CDlgShiFaDingHong::~CDlgShiFaDingHong()
{
}

void CDlgShiFaDingHong::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CDlgShiFaDingHong, CDialog)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


//初始化列表头
void CDlgShiFaDingHong::InitListHeader()
{
	CRect Rect;
	//初始化应用程序列表控件
	m_ListCtrl.GetWindowRect(&Rect);
	int nWidth = Rect.Width()/12;
	m_ListCtrl.InsertColumn(0,_TEXT("开奖号"),  LVCFMT_CENTER,	2*nWidth);
	m_ListCtrl.InsertColumn(1,_TEXT("定红1"),	LVCFMT_CENTER,	nWidth); 
	m_ListCtrl.InsertColumn(2,_TEXT("定红2"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(3,_TEXT("定红3"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(4,_TEXT("定红4"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(5,_TEXT("定红5"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(6,_TEXT("定红6"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(7,_TEXT("定红7"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(8,_TEXT("定红8"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(9,_TEXT("定红9"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(10,_TEXT("定红10"),	LVCFMT_CENTER,	nWidth);
	
}

/*
定红1：[用19减上期和值的尾数+-1]        
              例如：19-4=15点位14 15 16出 14
定红2：上上期的期数减上期的蓝号。
               例如：？46-10=3  6两尾全出 26  33
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
		m_ListCtrl.InsertItem(0,"");
		vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();
		for(int Index = 1; Index <= DataList->size(); Index++)
		{
			m_ListCtrl.InsertItem(Index,"");
			
			if(Index !=  DataList->size())
			{
			CString Str;
			Str.Format("%s ",(*DataList)[Index].m_QiShu);
			for(int i =0; i < 6; i++)
			{
				CString Temp;
				Temp.Format("%02d ",(*DataList)[Index].m_HongQiu[i]);
				Str+=Temp;
			}

			CString TempLan;
			TempLan.Format("+%02d",(*DataList)[Index].m_LanQiu);
			Str+=TempLan;
			m_ListCtrl.SetItemText(Index,0,Str);
			}

/*
			int DingHong1 = 19-(*DataList)[Index-1].m_HongQiuSum % 10;
			CString StrDing1;
			StrDing1.Format("%02d %02d %02d",DingHong1-1,DingHong1,DingHong1+1);
			m_ListCtrl.SetItemText(Index,1, StrDing1);
*/
			CString StrDing2;
			if(Index > 1)
			{
	    		int Data = atoi((*DataList)[Index-2].m_QiShu)-2012000;

				Data = abs(Data - (*DataList)[Index-1].m_LanQiu);
				bool IsTrue=false;
				int Temp = Data/10;
		    	IsTrue =  Index == DataList->size() ? true:CDataManageCenter::IsHongQiuInData((*DataList)[Index],Temp,true);
			    StrDing2+=" "+CDataManageCenter::GetDataStr(Temp,IsTrue,true);

				Temp = Data%10;
		    	IsTrue =  Index == DataList->size() ? true:CDataManageCenter::IsHongQiuInData((*DataList)[Index],Temp,true);
			    StrDing2+=" "+CDataManageCenter::GetDataStr(Temp,IsTrue,true);
				
			}
			m_ListCtrl.SetItemText(Index,2, StrDing2);
			

			CString StrDing3;
		 /*   int DingHong3 = (*DataList)[Index-1].m_HongQiu[4]*5;
			DingHong3 = DingHong3%33;
			StrDing3.Format("%02d %02d %02d",DingHong3-1,DingHong3,DingHong3+1);
			m_ListCtrl.SetItemText(Index,3, StrDing3);*/
			int DingHong3 = (*DataList)[Index-1].m_HongQiu[5]+(*DataList)[Index-1].m_HongQiu[0];
			DingHong3 = DingHong3%10 +DingHong3/10;
			DingHong3=DingHong3%10;
			bool IsTrue = Index == DataList->size() ? true:CDataManageCenter::IsHongQiuInData((*DataList)[Index],DingHong3);
		//	StrDing3+=CDataManageCenter::GetDataStr(DingHong3,IsTrue);

			float Ag1 = float((*DataList)[Index-1].m_HongQiuSum)/6;
			for(int i = 0; i < 6; i++)
			{
				float Ag2=float((*DataList)[Index-1].m_HongQiu[i])/6;
				CString TempStr;
				TempStr.Format("%02f ",Ag1+Ag2);
				StrDing3+=TempStr;
			}
		//	StrDing3.Format("%02f %02f %02f %02f %02f %02f",Ag1+(*DataList)[Index-1].m_HongQiu[0]);
			m_ListCtrl.SetItemText(Index,3, StrDing3);


			CString StrDing4;
			int DingHong4 = (*DataList)[Index-1].m_HongQiuSum/100 + ((*DataList)[Index-1].m_HongQiuSum/10)%10 +(*DataList)[Index-1].m_HongQiuSum%10;
			StrDing4.Format("%02d %02d %02d",DingHong4-1,DingHong4,DingHong4+1);
			m_ListCtrl.SetItemText(Index,4, StrDing4);

		/*	CString StrDing5;
			int DingHong5 = (*DataList)[Index-1].m_HongQiu[0];
			if(Index > 2)
			{
				DingHong5 =abs(DingHong5-(*DataList)[Index-2].m_HongQiu[0]);
			    StrDing5.Format("%02d %02d %02d",DingHong5-1,DingHong5,DingHong5+1);
			    m_ListCtrl.SetItemText(Index,5, StrDing5);
			}*/

			int DingHong5=(*DataList)[Index-1].m_HongQiu[0] + (*DataList)[Index-1].m_HongQiu[5];
			DingHong5 = DingHong5/10 + DingHong5%10;
			CString StrDing5;
			IsTrue =  Index == DataList->size() ? true:CDataManageCenter::IsHongQiuInData((*DataList)[Index],DingHong5,true);
			StrDing5+=CDataManageCenter::GetDataStr(DingHong5,IsTrue,true);
			  m_ListCtrl.SetItemText(Index,5, StrDing5);
			
			int DingHong6=(*DataList)[Index-1].m_HongQiuSum;// + CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1]);
			int HeSum=0;
			int WeiSum=0;
			for(int i = 0; i < 6; i++)
			{
				WeiSum=HeSum+(*DataList)[Index-1].m_HongQiu[i]%10;
				if(CDataManageCenter::IsHeShuData((*DataList)[Index-1].m_HongQiu[i]))
					HeSum+=(*DataList)[Index-1].m_HongQiu[i];

			}

			CString StrDing6;
			DingHong6 +=WeiSum;
			int QuYu = DingHong6%33;
			int QuShang = DingHong6/33;
			int Temp = abs(QuYu-QuShang);

			IsTrue = Index == DataList->size() ? true:CDataManageCenter::IsHongQiuInData((*DataList)[Index],Temp);
			StrDing6+=CDataManageCenter::GetDataStr(Temp,IsTrue);

		    Temp = QuYu+QuShang;
			IsTrue =  Index == DataList->size() ? true:CDataManageCenter::IsHongQiuInData((*DataList)[Index],Temp);
			StrDing6+=" "+CDataManageCenter::GetDataStr(Temp,IsTrue);
		    m_ListCtrl.SetItemText(Index,6, StrDing6);


			CString StrDing7;
			int DingHong7=(*DataList)[Index-1].m_HongQiuSum;
			DingHong7 +=HeSum;
			QuYu = DingHong7%33;
			QuShang = DingHong7/33;
			Temp = abs(QuYu-QuShang);

			IsTrue = Index == DataList->size() ? true:CDataManageCenter::IsHongQiuInData((*DataList)[Index],Temp);
			StrDing7+=CDataManageCenter::GetDataStr(Temp,IsTrue);

		    Temp = QuYu+QuShang;
			if(Temp > 33)
				Temp-=33;

			IsTrue =  Index == DataList->size() ? true:CDataManageCenter::IsHongQiuInData((*DataList)[Index],Temp);
			StrDing7+=" "+CDataManageCenter::GetDataStr(Temp,IsTrue);
		    m_ListCtrl.SetItemText(Index,7, StrDing7);

		//	StrDing6.Format("%02d %02d",,QuYu+QuShang);
		 
		/*	CString StrDing6;
			int DingHong6 = (*DataList)[Index-1].m_HongQiu[4]-(*DataList)[Index-1].m_HongQiu[1];
			int Temp=DingHong6+2;
			int Temp2=DingHong6-2;
			StrDing6.Format("+2=%02d %02d %02d;-2=%02d %02d %02d",Temp-1,Temp,Temp+1,Temp2-1,Temp2,Temp2+1);
		    m_ListCtrl.SetItemText(Index,6, StrDing6);

			*/
		/*	CString StrDing7;
			int DingHong7 = (*DataList)[Index-1].m_LanQiu*4;
			if(DingHong7 > 33)
				DingHong7 = DingHong7%33;
			StrDing7.Format("%02d %02d %02d",DingHong7-1,DingHong7,DingHong7+1);
		    m_ListCtrl.SetItemText(Index,7, StrDing7);*/

			CString StrDing8;
			int DingHong8 = (*DataList)[Index-1].m_LanQiu%10 +(*DataList)[Index-1].m_HongQiu[2]%10;
			//StrDing8.Format("%dV",DingHong8);
			Temp = DingHong8;
			IsTrue =  Index == DataList->size() ? true:CDataManageCenter::IsHongQiuInData((*DataList)[Index],Temp,true);
			StrDing8+=" "+CDataManageCenter::GetDataStr(Temp,IsTrue,true);

		    m_ListCtrl.SetItemText(Index,8, StrDing8);

			CString StrDing9;
			int DingHong9 = (*DataList)[Index-1].m_HongQiu[5] - (*DataList)[Index-1].m_HongQiu[4];
			Temp = DingHong9;
			IsTrue =  Index == DataList->size() ? true:!CDataManageCenter::IsHongQiuInData((*DataList)[Index],Temp,true);
			StrDing9+="杀"+CDataManageCenter::GetDataStr(Temp,IsTrue,true);

		//	StrDing9.Format("杀%dV",DingHong9);
		    m_ListCtrl.SetItemText(Index,9, StrDing9);


		}

		/*for(int Index = 0; Index < (int)DataList->size(); Index++)
		{
		
			m_ListCtrl.SetItemText(Index,0,(*DataList)[Index].m_QiShu);
			for(int HongQiu=0; HongQiu < 6; HongQiu++)
			{
				CString Temp;
				Temp.Format("%d",(*DataList)[Index].m_HongQiuChaZhi[HongQiu]);
				m_ListCtrl.SetItemText(Index,HongQiu+1,Temp);
			}

			CString LanQiu;
			LanQiu.Format("%d",(*DataList)[Index].m_LanQiuChaZhi);
			m_ListCtrl.SetItemText(Index,7,LanQiu);
		}

		if(!DataList->empty())
			m_IsInitData = true;
			*/
}

}

// 生成的消息映射函数
BOOL CDlgShiFaDingHong::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitListHeader();
	return true;
}

void CDlgShiFaDingHong::OnClose()
{
	ShowWindow(SW_HIDE);
}