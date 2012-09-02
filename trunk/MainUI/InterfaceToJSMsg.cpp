#include "stdafx.h"
#include "InterfaceToJS.h"

/***********************************************************************************
* 说明      ：  CPP_JS消息处理                                                     *
* 创建人    ：  郭庆轩                                                             *
* 创建日期  ：  2012-5-10                                                          *
***********************************************************************************/

//注册消息
void InterfaceToJS::RegisterMsg()
{
	//联系人
	CMessageCenter::RegisterMsgHandle((IMessageHandle*)this,MSG_CONTACT_REQUEST_CMD);
	CMessageCenter::RegisterMsgHandle((IMessageHandle*)this,MSG_CONTACT_ADD_CMD);
	CMessageCenter::RegisterMsgHandle((IMessageHandle*)this,MSG_CONTACTGROUP_REQUEST_CMD);

	//短信
	CMessageCenter::RegisterMsgHandle((IMessageHandle*)this,MSG_SMS_REQUEST_CMD);

	//文件管理
}
//注销消息
void InterfaceToJS::LogoutMsg()
{
	//联系人
	CMessageCenter::LogoutMsgHandle((IMessageHandle*)this,MSG_CONTACT_REQUEST_CMD);
	CMessageCenter::LogoutMsgHandle((IMessageHandle*)this,MSG_CONTACT_ADD_CMD);
	CMessageCenter::LogoutMsgHandle((IMessageHandle*)this,MSG_CONTACTGROUP_REQUEST_CMD);

	//短信
	CMessageCenter::RegisterMsgHandle((IMessageHandle*)this,MSG_SMS_REQUEST_CMD);

	//文件管理
}
//底层消息响应
void InterfaceToJS::OnMessage(eMessage Message,DWORD SystemMsg,WPARAM wParam,LPARAM lParam)
{
//短信手机消息返回
	SmsReturnWeb(Message,wParam, lParam);
	
//联系人手机消息返回
	ContacReturnWeb(Message,wParam,lParam);
}

//处理联系人消息
void InterfaceToJS::ContacReturnWeb(eMessage Message,WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case MSG_CONTACT_REQUEST_CMD:
		{
			vector<sContactInfo>* tmpVctContact = (vector<sContactInfo>*)wParam;
			DoContactJsIntface(_T("JS_OnRequestContactData"),*tmpVctContact);
		}
		break;
	case MSG_CONTACT_ADD_CMD:
		{
			vector<sContactInfo>* tmpVctContact = (vector<sContactInfo>*)wParam;
			DoContactJsIntface(_T("JS_OnRequestContactData"),*tmpVctContact);
			//		RetPhoMsg(L"JS_OnRequestAddContactData",1);
		}
		break;
	case MSG_CONTACT_DELTE_CMD:
		{
			vector<sContactInfo>* tmpVctContact = (vector<sContactInfo>*)wParam;
			DoContactJsIntface(_T("JS_OnRequestContactData"),*tmpVctContact);
			//		RetPhoMsg(L"JS_OnRequestDeleteContactData",1);
		}

		break;
	case MSG_CONTACT_DELTE_ALL_CMD:
		{
			vector<sContactInfo>* tmpVctContact = (vector<sContactInfo>*)wParam;
			DoContactJsIntface(_T("JS_OnRequestContactData"),*tmpVctContact);
			//		RetPhoMsg(L"JS_OnRequestDeleteAllContactData",1);
		}
		break;
	case MSG_CONTACT_EDIT_CMD:
		{
			vector<sContactInfo>* tmpVctContact = (vector<sContactInfo>*)wParam;
			DoContactJsIntface(_T("JS_OnRequestContactData"),*tmpVctContact);
			//		RetPhoMsg(L"JS_OnRequestEditContactData",1);
		}
		break;
	case MSG_CONTACT_BACKUP_CMD:
	//	RetPhoMsg(L"JS_OnRequestBackUpContactData",1);
		break;
	case MSG_CONTACTGROUP_REQUEST_CMD:
		{
			vector<sGroupInfo>* tmpVctGroup = (vector<sGroupInfo>*)wParam;
			CString strJsonSms = L"" ;
			CString strResult = L"";
			CombinGroupInfo(*tmpVctGroup,strJsonSms);
			strResult = MakeStrJsIntface(_T("JS_OnRequestGroupData"),strJsonSms);
			ExecJsScript(strResult);
		}
		break;
	case MSG_CONTACTGROUP_ADD_CMD:
	//	RetPhoMsg(L"JS_OnRequestAddGroup",1);
		break;
	case MSG_CONTACTGROUP_DELETE_CMD:
	//	RetPhoMsg(L"JS_OnRequestDeleteGroupData",1);
		break;
	case MSG_CONTACTGROUP_DELETE_ALL_CMD:
	//	RetPhoMsg(L"JS_OnRequestDeleteAllGroupData",1);
		break;
	case MSG_CONTACTGROUP_EDIT_CMD:
		//RetPhoMsg(L"JS_OnRequestEditGroupData",1);
		break;
	}
}

//处理短信消息
void InterfaceToJS::SmsReturnWeb(eMessage Message,WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case MSG_SMS_REQUEST_CMD:
		{
			vector<sSmsInfo>* tmpVctContact = (vector<sSmsInfo>*)wParam;
			DoSmsJsIntface(_T("JS_OnRequestSmsData"),*tmpVctContact);
		}
		break;
	case MSG_SMS_ADD_CMD:
		//RetPhoMsg(L"JS_OnRequestAddSmsData",(int)lParam);
		break;
	case MSG_SMS_DELTE_CMD:
		//RetPhoMsg(L"JS_OnRequestDeleteSmsData",(int)lParam);
		break;
	case MSG_SMS_DELTE_ALL_CMD:
		//RetPhoMsg(L"",(int)lParam);
		break;
	case MSG_SMS_EDIT_CMD:
		//RetPhoMsg(L"",(int)lParam);
		break;
	case MSG_SMS_BACKUP_CMD:
		//RetPhoMsg(L"",(int)lParam);
		break;
	case MSG_SMS_SEND_CMD:
		//RetPhoMsg(L"JS_OnRequestSendSms",(int)lParam);
		break;
	}
}