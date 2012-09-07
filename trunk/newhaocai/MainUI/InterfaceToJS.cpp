#include "stdafx.h"
#include "InterfaceToJS.h"
#include "MainUI.h"
#include "MainUIDlg.h"
#include "json.h"
#include "DataDefine.h"


InterfaceToJS::InterfaceToJS(IDispatch* DisPath)
{
	m_DisPath = DisPath;
	
}

InterfaceToJS::~InterfaceToJS(void)
{
}
//执行JS脚本
void InterfaceToJS::ExecJsScript(CString& JsStr)
{
	if(m_DisPath == NULL)
		return;
	IHTMLDocument2*		pIHTMLDoc=NULL;
	m_DisPath->QueryInterface(IID_IHTMLDocument2, (void**)&pIHTMLDoc);
	if(pIHTMLDoc != NULL)
	{
		IHTMLWindow2*			pIHTMLWindow	= NULL;
		HRESULT					hr				= NOERROR;
		VARIANT					pvarRet;
		pIHTMLDoc->get_parentWindow(&pIHTMLWindow);
		if(pIHTMLWindow)
		{
			hr = pIHTMLWindow->execScript(CComBSTR(JsStr), CComBSTR("JScript"), &pvarRet);
			pIHTMLWindow->Release();
			pIHTMLWindow = NULL;
		}
		pIHTMLDoc->Release();
	}
}


CString InterfaceToJS::MakeStrJsIntface(const CString& JsIntface,const CString& JsParame )
{
	CString StrResult = _T("");
	StrResult.Format(_T("(\"%s\")"),JsParame);
	StrResult = JsIntface+StrResult;
	return StrResult;
}

void InterfaceToJS::SetDisPath(IDispatch* DisPath)
{
	this->m_DisPath = DisPath;
}

/******************************主对话框操作管理******************************************/

//移动对话框
void InterfaceToJS::CPP_MoveMianDlg(int Xpoint, int Ypoint)					
{
	CMainUIDlg*	pDlg	= (CMainUIDlg*)theApp.m_pMainWnd;
	pDlg->MoveMainDlg(Xpoint,Ypoint);
}

//关闭对话框
void InterfaceToJS::CPP_Close()												
{
	CMainUIDlg*	pDlg	= (CMainUIDlg*)theApp.m_pMainWnd;
	pDlg->IsAppRun(_T("MainUI.exe"));
	pDlg->EndDialog(0);
}

//最小化对话框
void InterfaceToJS::CPP_MinDlg()											
{
	CMainUIDlg*	pDlg	= (CMainUIDlg*)theApp.m_pMainWnd;
	pDlg->ShowWindow(SW_MINIMIZE);
}

//获取杀红数据
void InterfaceToJS::CPP_OnRequestShaHongData()
{
	
	vector<sFormulaInfo> FormulaInfo=CFormulaCenter::GetInstance()->GetFormulaInfoByType(FORMULA_SHA_HONG);
	CString JsonStr;
	ShaHongDataToJson(FormulaInfo,JsonStr);
	MakeStrJsIntface(_T("JS_OnRequestShaHongData"),JsonStr);

}

//杀红数据转化成json数据
void InterfaceToJS::ShaHongDataToJson(vector<sFormulaInfo>& FormulaInfo,CString& Str)
{
	//CString FormuInfoJason;
	//for(int Index = 0; Index < FormulaInfo.size(); Index++)
	//{
	//	CString FormatJsonStr;
	//	FormatJsonStr=_T("{FormuName:\'%s\',MaxLianCuoCount:\'%d\',MaxLianDuiCount:\'%d\',MinLianCuoCount:\'%d\',MinLianDuiCount:\'%d\',ErrorCount:\'%d\',TrueBaiFenBi:\'%d%%\',DataCount:\'%d\',DataList:[%s]}");
	//	CString FormatDataJson;
	////	FormatDataJson=_T("{Data:\'%d\',IsTrue:\'%d\'}");

	//	CString DataStr;
	//	for(int i=0; i < FormulaInfo[Index].m_DataList.size(); i++)
	//	{
	//		CString TempStr;
	//		TempStr.Format(_T("{Data:\'%s\',IsTrue:\'%d\'}"),FormulaInfo[Index].m_DataList[i].m_Data,FormulaInfo[Index].m_DataList[i].m_IsTrue);
	//		DataStr+=TempStr;
	//		if(i !=FormulaInfo[Index].m_DataList.size()-1)
	//			DataStr+=_T(",");
	//
	//	}

	//	int BaiFenBi=0;
	//	int TempData=FormulaInfo[Index].m_ErrorCount+FormulaInfo[Index].m_TrueCount;
	//	if(TempData)
	//		BaiFenBi=FormulaInfo[Index].m_TrueCount*100/TempData;
	//	CString ObjectStr;
	//	ObjectStr.Format(FormatJsonStr,FormulaInfo[Index].m_FormulaName,FormulaInfo[Index].m_MaxLianCuoCount,FormulaInfo[Index].m_MaxLianDuiCount,FormulaInfo[Index].m_MinLianCuoCount,FormulaInfo[Index].m_MinLianDuiCount,FormulaInfo[Index].m_ErrorCount, BaiFenBi,FormulaInfo[Index].m_DataList.size(),DataStr);

	//	FormuInfoJason+=ObjectStr;
	//	if(Index !=FormulaInfo.size()-1)
	//		FormuInfoJason+=_T(",");
	//}

	//FormuInfoJason=_T("{ShaHong:[")+FormuInfoJason+_T("]}");
	//Str=FormuInfoJason;

	//int DataCount=CDataManageCenter::GetInstance()->GetDataList()->size();
	//for(int i = 0; i < DataCount; i++)
	//{
	//	for(int j= 0; j < FormulaInfo.size(); j++)
	//	{

	//	}
	//}
}

/********************************数据解析与组装部分****************************************************/
/*
//组合： vector 联系人 转换成 JSON String
void InterfaceToJS::CombinContactToJson(const vector<sContactInfo> &vectContact, CString& ContactStrJson)
{
	int countContact = (int)vectContact.size();
	if (countContact == 0)
		return ;

	CString LastNamePos;

	for (int i=0; i<countContact; i++)
	{
		CString tempItem = L"";
		CString tempGrpstr = L"";

		sContactInfo tempInfo = vectContact[i];
		for (int count=0; count<(int)vectContact[i].m_GroupIDs.size(); count++)
		{			
			CString tempGrpItemStr = L"";
			tempGrpItemStr.Format(L"{group:\'%s\'}",tempInfo.m_GroupIDs[count]);
			if (count == 0)
				tempGrpstr =  tempGrpItemStr;
			else
				tempGrpstr =tempGrpstr + L"," +tempGrpItemStr;
		}
		CString NamePos=::GetFirstLetter(tempInfo.m_Name);
		if(LastNamePos != NamePos)
			LastNamePos = NamePos;
		else
			NamePos.Empty();
		tempGrpstr = L"groupid:[" +tempGrpstr+L"],";
		CString pathType = _T("");
		switch (tempInfo.m_PathType)
		{
		case PATH_UNKOWN:
			pathType = _T("0");
			break;
		case PATH_PHONE:
			pathType = _T("1");
			break;
		case PATH_SDCARD:
			pathType = _T("2");
			break;
		}
		
		tempItem.Format(_T("position:\'%s\',id:\'%s\',name:\'%s\',mobilenumber:\'%s\',\
						 mobilehome:\'%s\',mobilework:\'%s\',phoneNumber:\'%s\',\
						 phonehome:\'%s\',phonework:\'%s\',email:\'%s\',homeaddress:\'%s\',\
						 company:\'%s\',birthday:\'%s\',fax:\'%s\',departtment:\'%s\',duties:\'%s\',pathtype:%s")\
						 ,NamePos,tempInfo.m_ID,tempInfo.m_Name,tempInfo.m_MobileNumber,tempInfo.m_MobileHome,tempInfo.m_MobileWork,tempInfo.m_PhoneNumber \
						 ,tempInfo.m_PhoneHome,tempInfo.m_PhoneWork,tempInfo.m_Email,tempInfo.m_HomeAddress,tempInfo.m_Company \
						 ,tempInfo.m_Birthday,tempInfo.m_Fax,tempInfo.m_Departments,tempInfo.m_Duties,pathType);
		tempItem = L"{" + tempGrpstr + tempItem +L"}";
		if (i == 0)
			ContactStrJson = tempItem;
		else
			ContactStrJson = ContactStrJson + L"," + tempItem;
	}
	ContactStrJson = L"{person:["+ContactStrJson+L"]}";
}

//组合： vector 短信 转换成 JSON String
void InterfaceToJS::CombinSmsToJson(const vector<sSmsInfo> &vectSms, CString& SmsStrJson)
{
	int countSms = (int)vectSms.size();
	if (countSms == 0)
		return;

	Json::Value SmsRoot;
	Json::Value SmsItem;
	Json::Value SmsArray;
	
	for (int i=0; i<countSms; i++)
	{
		CString strTempItemSms;
		sSmsInfo temSmsInfo = vectSms[i];
		strTempItemSms.Format(_T("{smsid:\'%s\',contactname:\'%s\',smscaller:\'%s\',smsbody:\'%s\', \
								 timestamp:\'%s\',smsstaus:%d,smsbox:%d}"), \
								 temSmsInfo.m_SmsID,temSmsInfo.m_ContactName,temSmsInfo.m_SmsCaller, \
								 temSmsInfo.m_SmsBody,temSmsInfo.m_TimeStamp,(int)temSmsInfo.m_SmsStaus,(int)temSmsInfo.m_SmsBox);
		if (i == 0)
			SmsStrJson = strTempItemSms;
		else
			SmsStrJson = SmsStrJson + L"," + strTempItemSms;
	}
	SmsStrJson = L"{sms:["+SmsStrJson+L"]}";
}

//组合： vecttor分组 转换成JSON String
void InterfaceToJS::CombinGroupInfo(const vector<sGroupInfo>&groupInfo, CString&StrGroupJson)
{
	int countGroup = (int)groupInfo.size();
	if (countGroup == 0)
		return;

	Json::Value GroupRoot;
	Json::Value GroupItem;
	Json::Value GroupArray;

	for (int i=0; i<countGroup; i++)
	{
		CString strTempItemGroup;
		sGroupInfo temGroupInfo = groupInfo[i];
		strTempItemGroup.Format(_T("{id:\'%s\',name:\'%s\',count:\'%s\',issystem:\'%s\'}"), \
								 temGroupInfo.m_GroupID,temGroupInfo.m_GroupName,temGroupInfo.m_ContactCount, \
								 temGroupInfo.m_IsSystem);
		if (i == 0)
			StrGroupJson = strTempItemGroup;
		else
			StrGroupJson = StrGroupJson + L"," + strTempItemGroup;
	}
	StrGroupJson = L"{group:["+StrGroupJson+L"]}";
}

//解析联系人分组信息    JSON转换成vector
//_T("{\"group\":[{\"id\":\"123456\",\"name\":\"123456\",\"count\":\"123456\",\"issystem\":\"123456\"}]}");
void InterfaceToJS::AnalyContactGroupinfo(const CString& JsonGroup, vector<sGroupInfo>& vctGroupInfo)
{
	Json::Reader GroupReader;
	Json::Value  GroupValue;
	if (GroupReader.parse(CstringtoString(JsonGroup), GroupValue))
	{
		Json::Value arrayObj = GroupValue["group"];
		int i_size = arrayObj.size();
		for (int i = 0; i < i_size; i++)
		{
			sGroupInfo tempGroupInfo;
			CString cContactCount, cIsSystem;
			cContactCount = arrayObj[i]["count"].asCString();
			cIsSystem	  = arrayObj[i]["issystem"].asCString();
			tempGroupInfo.m_ContactCount = _ttoi(cContactCount);
			if (_ttoi(cIsSystem) == 1)
				tempGroupInfo.m_IsSystem = true;
			else if (_ttoi(cIsSystem) == 0)
				tempGroupInfo.m_IsSystem = false;

			tempGroupInfo.m_GroupID		 = arrayObj[i]["id"].asCString();
			tempGroupInfo.m_GroupName	 = arrayObj[i]["name"].asCString();
			vctGroupInfo.push_back(tempGroupInfo);
		}
	}
}*/