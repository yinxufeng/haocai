// DlgLianHaoHongQiu.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ShuangSeQiu.h"
#include "DlgLianHaoHongQiu.h"


// CDlgLianHaoHongQiu �Ի���

IMPLEMENT_DYNAMIC(CDlgLianHaoHongQiu, CDialog)

CDlgLianHaoHongQiu::CDlgLianHaoHongQiu(CWnd* pParent /*=NULL*/)
: CDialog(CDlgLianHaoHongQiu::IDD, pParent)
{
	m_IsInitData = false;
}

CDlgLianHaoHongQiu::~CDlgLianHaoHongQiu()
{
}

void CDlgLianHaoHongQiu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CDlgLianHaoHongQiu, CDialog)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()

END_MESSAGE_MAP()


// CDlgLianHaoHongQiu ��Ϣ��������

//��ʼ���б�ͷ
void CDlgLianHaoHongQiu::InitListHeader()
{
	CRect Rect;
	//��ʼ��Ӧ�ó����б��ؼ�
	m_ListCtrl.GetWindowRect(&Rect);
	//int nWidth = Rect.Width()/12;
	int nWidth=100;
	m_ListCtrl.InsertColumn(0,_TEXT("����"),    LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(1,_TEXT("Χ��1"),	LVCFMT_CENTER,	2*nWidth);
	m_ListCtrl.InsertColumn(2,_TEXT("Χ��2"),	LVCFMT_CENTER,	2*nWidth+50); 
	m_ListCtrl.InsertColumn(3,_TEXT("Χ��3"),	LVCFMT_CENTER,	2*nWidth); 
	m_ListCtrl.InsertColumn(4,_TEXT("ɱ��1"),	LVCFMT_CENTER,	2*nWidth);
	m_ListCtrl.InsertColumn(5,_TEXT("ɱ��2"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(6,_TEXT("ɱ��3"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(7,_TEXT("ɱ��4"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(8,_TEXT("ɱ��5"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(9,_TEXT("ɱ��6"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(10,_TEXT("ɱ��7"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(11,_TEXT("ɱ��8"),	LVCFMT_CENTER,	nWidth);
	m_ListCtrl.InsertColumn(12,_TEXT("ɱ��9"),	LVCFMT_CENTER,	nWidth);


}

void CDlgLianHaoHongQiu::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	if(!m_IsInitData)
	{
		m_IsInitData = true;

		m_ListCtrl.DeleteAllItems();
		m_ListCtrl.InsertItem(0,"");
		vector<sShuangSeQiu>* DataList=CDataManageCenter::GetInstance()->GetDataList();



		for(int Index = 1; Index < (int)DataList->size()+1; Index++)
		{
			int InsertItemPos=0;
			m_ListCtrl.InsertItem(Index,"");
			if(Index == DataList->size())
			{
				m_ListCtrl.SetItemText(Index,InsertItemPos,"Ԥ��");
			}
			else
			{
				CString LanQiu;
				LanQiu.Format("%d",(*DataList)[Index].m_LanQiu);
				m_ListCtrl.SetItemText(Index,InsertItemPos,LanQiu);
			}

			InsertItemPos++;
			bool IsAddS = false;
			int TempLanQiu = (*DataList)[Index-1].m_LanQiu;
			int Temp = (TempLanQiu%10)*2;
			if(Temp >= 10)
				Temp = Temp%10;

			if(Index >=2)
			{
				int TempLanCha = abs((*DataList)[Index-1].m_LanQiu%10 - (*DataList)[Index-2].m_LanQiu%10);
				int TempLanHe  = abs((*DataList)[Index-1].m_LanQiu%10 + (*DataList)[Index-2].m_LanQiu%10);
				int TempLanHeArray[7];
				int TempLanChaArray[7];

				for(int i = 0; i < 7; i++)
				{
					if(i < 3)
					{
						TempLanHeArray[i]=TempLanHe-(i+1);
						if(TempLanHeArray[i] > 9)
							TempLanHeArray[i] =TempLanHeArray[i]-10;
						if(TempLanHeArray[i] < 0)
							TempLanHeArray[i] =TempLanHeArray[i]+10;


						TempLanChaArray[i]=TempLanCha-(i+1);
						if(TempLanChaArray[i] > 9)
							TempLanChaArray[i] = TempLanChaArray[i]-10;
						if(TempLanChaArray[i] < 0)
							TempLanChaArray[i] = TempLanChaArray[i]+10;

					}
					else if(i ==3)
					{
						TempLanHeArray[i]=TempLanHe;
						TempLanChaArray[i] = TempLanCha;
						if(TempLanHeArray[i] < 0)
							TempLanHeArray[i] =TempLanHeArray[i]+10;
						if(TempLanHeArray[i] > 9)
							TempLanHeArray[i] =TempLanHeArray[i]-10;

						if(TempLanChaArray[i] < 0)
							TempLanChaArray[i] = TempLanChaArray[i]+10;
						if(TempLanChaArray[i] > 9)
							TempLanChaArray[i] = TempLanChaArray[i]-10;
					}
					else
					{
						TempLanHeArray[i]=TempLanHe+i-3;
						if(TempLanHeArray[i] < 0)
							TempLanHeArray[i] =TempLanHeArray[i]+10;
						if(TempLanHeArray[i] > 9)
							TempLanHeArray[i] =TempLanHeArray[i]-10;

						TempLanChaArray[i]=TempLanCha+i-3;
						if(TempLanChaArray[i] < 0)
							TempLanChaArray[i] = TempLanChaArray[i]+10;
						if(TempLanChaArray[i] > 9)
							TempLanChaArray[i] = TempLanChaArray[i]-10;
					}


				}


				int Array[100];
				memset(Array,0,sizeof(int)*10);

				bool IsSu=false;

				for(int i = 0; i < 7; i++)
				{
					int Data = TempLanChaArray[i];
					int Data2= TempLanHeArray[i];
					Array[Data]++;
					Array[Data2]++;
				}

				CString LanStr2;
				for(int j =0; j < 10; j++)
				{
					if(Array[j] == 1)
					{
						CString TempStr;
						TempStr.Format("%02d",j);
						LanStr2+=TempStr;

						if(!IsSu)
						{
							if(Index == DataList->size())
							{
								IsSu=true;
								continue;
							}

							if(CDataManageCenter::IsLanQiuInData((*DataList)[Index],j,true))
								IsSu = true;
						}
					}
				}

				LanStr2+="V";

				AddFlag(LanStr2,IsSu);
				m_ListCtrl.SetItemText(Index,1,LanStr2);
			}

			CString LanQiu10;
			Temp = (*DataList)[Index-1].m_LanQiu;
			switch(Temp)
			{
			case 1:
				LanQiu10="06 08 09 11 12 13 14 15 16";
				break;
			case 2:
				LanQiu10="03 05 07 11 12 13 14 15 16";
				break;
			case 3:
				LanQiu10="02 06 08 09 10 13 14 15 16";
				break;
			case 4:
				LanQiu10="01 05 06 07 09 10 13 14 15 16";
				break;

			case 5:
				LanQiu10="02 06 08 09 10 13 14 15 16";
				break;

			case 6:
				LanQiu10="01 03 07 09 10 11 12 15 16";
				break;

			case 7:
				LanQiu10="02 04 06 09 10 11 12 13 14";
				break;

			case 8:
				LanQiu10="01 02 05 06 07 08 09 13 15";
				break;
			case 9:
				LanQiu10="03 04 05 06 07 08 13 14 16";
				break;
			case 10:
				LanQiu10="03 04 05 06 07 08 11 13 15";
				break;
			case 11:
				LanQiu10="01 02 05 06 07 08 10 14 16";
				break;
			case 12:
				LanQiu10="01 02 05 06 07 08 09 13 15";
				break;
			case 13:
				LanQiu10="01 02 03 04 07 08 10 12 16";
				break;
			case 14:
				LanQiu10="01 02 03 04 07 08 09 11 15";
				break;
			case 15:
				LanQiu10="01 02 03 04 05 06 10 12 14";
				break;
			case 16:
				LanQiu10="01 02 03 04 05 06 09 11 13";
				break;

			}


			if(Index == DataList->size())
			{
				IsAddS = true;
			}
			else
			{
				CString TempStr;
				TempStr.Format("%02d",(*DataList)[Index].m_LanQiu);
				if(LanQiu10.Find(TempStr) != -1)
					IsAddS = true;
				else
					IsAddS = false;
			}
			AddFlag(LanQiu10,IsAddS);
			m_ListCtrl.SetItemText(Index,2,LanQiu10);

			if(Index >= 5)
			{
				int Sum=0;
				for(int j=0 ; j < 5; j++)
				{
					Sum+=(*DataList)[Index-1-j].m_LanQiu;
				}


				int MinLan = Sum/5-5;
				int MaxLan = Sum/5+5;
				if(MinLan < 0)
					MinLan = 1;
				if(MaxLan > 16)
					MaxLan = 16;

				if(Index == DataList->size())
				{
					IsAddS = true;
				}else
				{
					if((*DataList)[Index].m_LanQiu < MinLan || (*DataList)[Index].m_LanQiu > MaxLan)
						IsAddS = false;
					else
						IsAddS = true;
				}

				CString WeiLan;
				if(MinLan < MaxLan)
					WeiLan.Format("[%02d %02d]",MinLan,MaxLan);
				else
					WeiLan.Format("[%02d %02d]",MaxLan,MinLan);

				AddFlag(WeiLan,IsAddS);

				m_ListCtrl.SetItemText(Index,3,WeiLan);

			}

			CString LanQiu9;
			Temp=(*DataList)[Index-1].m_HongQiu[5]%10+1;
			CString TempLanQiu9;
			TempLanQiu9.Format("%02d",Temp);
			LanQiu9 += TempLanQiu9;
			TempLanQiu9.Empty();
			if(Index == DataList->size())
			{
				IsAddS = true;
			}
			else
				IsAddS=!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,true);
			AddFlag(LanQiu9,IsAddS);


			Temp=(*DataList)[Index-1].m_HongQiu[0]+3;
			if(Temp> 16)
				Temp -=16;

			TempLanQiu9.Format("%02d",Temp);
			LanQiu9 += TempLanQiu9;
			TempLanQiu9.Empty();
			if(Index == DataList->size())
			{
				IsAddS = true;
			}
			else
				IsAddS=!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,true);
			AddFlag(LanQiu9,IsAddS);


			Temp=(*DataList)[Index-1].m_HongQiu[0]*2;
			if(Temp> 16)
				Temp -=16;
			TempLanQiu9.Format("%02d",Temp);
			LanQiu9 += TempLanQiu9;
			TempLanQiu9.Empty();
			if(Index == DataList->size())
			{
				IsAddS = true;
			}
			else
				IsAddS=!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,true);
			AddFlag(LanQiu9,IsAddS);


			Temp=CDataManageCenter::GetInstance()->GetACCount((*DataList)[Index-1])*2-6;
			if(Temp> 16)
				Temp -=16;
			TempLanQiu9.Format("%02d",Temp);
			LanQiu9 += TempLanQiu9;
			TempLanQiu9.Empty();
			if(Index == DataList->size())
			{
				IsAddS = true;
			}
			else
				IsAddS=!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,true);
			AddFlag(LanQiu9,IsAddS);

			if(Index >= 3)
			{
				Temp=(*DataList)[Index-1].m_LanQiu%10+(*DataList)[Index-2].m_LanQiu%10+(*DataList)[Index-3].m_LanQiu%10;
				if(Temp> 16)
					Temp -=16;
				TempLanQiu9.Format("%02d",Temp);
				LanQiu9 += TempLanQiu9;
				TempLanQiu9.Empty();
				if(Index == DataList->size())
				{
					IsAddS = true;
				}
				else
					IsAddS=!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,true);
				AddFlag(LanQiu9,IsAddS);

			}


			if( Index>=2)
			{
				Temp=((*DataList)[Index-1].m_LanQiu%10)*((*DataList)[Index-2].m_LanQiu%10)+5;
				if(Temp > 16)
					Temp-=16;
				TempLanQiu9.Format("%02d",Temp);
				LanQiu9 += TempLanQiu9;
				TempLanQiu9.Empty();
				if(Index == DataList->size())
				{
					IsAddS = true;
				}
				else
					IsAddS=!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,true);
				AddFlag(LanQiu9,IsAddS);

			}

			Temp=(*DataList)[Index-1].m_HongQiu[3]%10 + (*DataList)[Index-1].m_LanQiu%10;
			if(Temp> 16)
				Temp -=16;
			TempLanQiu9.Format("%02d",Temp);
			LanQiu9 += TempLanQiu9;
			TempLanQiu9.Empty();
			if(Index == DataList->size())
			{
				IsAddS = true;
			}
			else
				IsAddS=!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,true);
			AddFlag(LanQiu9,IsAddS);
			m_ListCtrl.SetItemText(Index,4,LanQiu9);


			if( Index >= 2)
			{
				Temp = 	abs((*DataList)[Index-1].m_LanQiu - (*DataList)[Index-2].m_LanQiu);
				Temp = Temp%10;
				CString LanQiu2;
				LanQiu2.Format("ɱ%02dV",Temp);
				if(Index == DataList->size())
				{
					IsAddS = true;
				}
				else
					IsAddS=!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,true);
				AddFlag(LanQiu2,IsAddS);
				m_ListCtrl.SetItemText(Index,5,LanQiu2);
			}

			if( Index >= 2)
			{
				Temp = 	(*DataList)[Index-1].m_LanQiu + (*DataList)[Index-2].m_LanQiu;
				if(Temp > 16)
					Temp-=16;

				CString LanQiu3;
				LanQiu3.Format("ɱ%02d",Temp);
				if(Index == DataList->size())
				{
					IsAddS = true;
				}
				else
					IsAddS=!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,false);
				AddFlag(LanQiu3,IsAddS);
				m_ListCtrl.SetItemText(Index,6,LanQiu3);
			}


			CString LanQiu4;
			int Temp1=(*DataList)[Index-1].m_LanQiu+2;
			int Temp2=(*DataList)[Index-1].m_LanQiu-2;
			if(Temp1 < 0)
				Temp1 +=16;
			if(Temp2 < 0)
				Temp2 +=16;

			if(Temp1 > 16)
				Temp1 -=16;
			if(Temp2 > 16)
				Temp2 -=16;
			LanQiu4.Format("ɱ%02d %02d",Temp1,Temp2);
			if(Index == DataList->size())
			{
				IsAddS = true;
			}
			else
				IsAddS=CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp1,false);

			bool IsAddS2=false;
			if(Index == DataList->size())
			{
				IsAddS2 = true;
			}
			else
				IsAddS2=CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp2,false);

			if(IsAddS || IsAddS2)
				IsAddS=false;
			else
				IsAddS=true;
			AddFlag(LanQiu4,IsAddS);
			m_ListCtrl.SetItemText(Index,7,LanQiu4);

			CString LanQiu5;
			Temp =(*DataList)[Index-1].m_LanQiu +(*DataList)[Index-1].m_HongQiu[0];
			if(Temp > 16)
				Temp -=16;
			LanQiu5.Format("ɱ%02d",Temp);
			if(Index == DataList->size())
			{
				IsAddS = true;
			}
			else
				IsAddS=!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,false);
			AddFlag(LanQiu5,IsAddS);
			m_ListCtrl.SetItemText(Index,8,LanQiu5);

			CString LanQiu6;
			int QiShu = atoi((*DataList)[Index-1].m_QiShu.GetBuffer())%100+(*DataList)[Index-1].m_LanQiu;
			QiShu=QiShu%10;
			Temp = QiShu;
			LanQiu6.Format("ɱ%02d",Temp);
			if(Index == DataList->size())
			{
				IsAddS = true;
			}
			else
				IsAddS=!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,false);
			AddFlag(LanQiu6,IsAddS);
			m_ListCtrl.SetItemText(Index,9,LanQiu6);

			CString LanQiu7;
			Temp = (*DataList)[Index-1].m_HongQiu[1]%10+1;
			LanQiu7.Format("ɱ%02dV",Temp);
			if(Index == DataList->size())
			{
				IsAddS = true;
			}
			else
				IsAddS=!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,true);
			AddFlag(LanQiu7,IsAddS);
			m_ListCtrl.SetItemText(Index,10,LanQiu7);




			CString LanQiu8;
			Temp = (*DataList)[Index-1].m_LanQiu+5;
			Temp=Temp%16;
			LanQiu8.Format("ɱ%02d",Temp);

			/*switch(Temp)
			{
			case 1:
				LanQiu8="ɱ06 10";
				break;
			case 2:
				LanQiu8="ɱ03 07 08 09";
				break;
			case 3:
				LanQiu8="ɱ03";
				break;
			case 4:
				LanQiu8="ɱ05 07 09";
				break;

			case 5:
				LanQiu8="ɱ02 04 10 16";
				break;

			case 6:
				LanQiu8="ɱ05 08 10 12 16";
				break;

			case 7:
				LanQiu8="ɱ09 12 15";
				break;

			}*/


			if(Index == DataList->size())
			{
				IsAddS = true;
			}
			else
			{
				CString TempStr;
				TempStr.Format("%02d",(*DataList)[Index].m_LanQiu);
				if(LanQiu8.Find(TempStr) != -1)
					IsAddS = false;
				else
					IsAddS = true;
			}
			AddFlag(LanQiu8,IsAddS);
			m_ListCtrl.SetItemText(Index,11,LanQiu8);


			CString LanQiu1;
			Temp = (*DataList)[Index-1].m_LanQiu%10*2;
			Temp =Temp%10;
			LanQiu1.Format("ɱ%02dV",Temp);
			if(Index == DataList->size())
			{
				IsAddS = true;
			}
			else
				IsAddS=!CDataManageCenter::IsLanQiuInData((*DataList)[Index],Temp,true);
			AddFlag(LanQiu1,IsAddS);
			m_ListCtrl.SetItemText(Index,12,LanQiu1);

		}

		if(!DataList->empty())
			m_IsInitData = true;
	}

}

// ���ɵ���Ϣӳ�亯��
BOOL CDlgLianHaoHongQiu::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitListHeader();
	return true;
}

void CDlgLianHaoHongQiu::OnClose()
{
	ShowWindow(SW_HIDE);
}

void CDlgLianHaoHongQiu::OnBnClickedSearchBtn()
{
	CString Text;
	GetDlgItem(IDC_EDIT1)->GetWindowText(Text);
	DWORD Data=::atoi(Text.GetBuffer());
	m_ListCtrl.DeleteAllItems();
	vector<sShuangSeQiu>* DataList = NULL;
	vector<sShuangSeQiu> Temp;
	if(Data == 0)
	{
		DataList=CDataManageCenter::GetInstance()->GetLianHaoHongQiu();
	}
	else
	{
		Temp=CDataManageCenter::GetInstance()->SearchLianHaoHongQiu(Data);
		DataList=&Temp;
	}

	for(int Index = 0; Index < (int)DataList->size(); Index++)
	{
		m_ListCtrl.InsertItem(Index,"");
		m_ListCtrl.SetItemText(Index,0,(*DataList)[Index].m_QiShu);
		for(int HongQiu=0; HongQiu < 6; HongQiu++)
		{
			CString Temp;
			Temp.Format("%d",(*DataList)[Index].m_HongQiu[HongQiu]);
			m_ListCtrl.SetItemText(Index,HongQiu+1,Temp);
		}

		CString HongQiuSum;
		HongQiuSum.Format("%d",(*DataList)[Index].m_HongQiuSum);
		m_ListCtrl.SetItemText(Index,7,HongQiuSum);

		CString LanQiu;
		LanQiu.Format("%d",(*DataList)[Index].m_LanQiu);
		m_ListCtrl.SetItemText(Index,8,LanQiu);
	}
}

void CDlgLianHaoHongQiu::AddFlag(CString& Str,bool IsTrue)
{
	if(IsTrue)
		Str+="S";
	else
		Str+="F";
}