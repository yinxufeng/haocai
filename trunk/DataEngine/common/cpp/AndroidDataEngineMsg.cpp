#include "StdAfx.h"
#include "../Include/AndroidDataEngine.h"
#include "../Include/CommonFunction.h"
#include <algorithm>   


bool SortContactByName(sContactInfo tp1, sContactInfo tp2)
{
	CString Name1=::GetFirstLetter(tp1.m_Name);
	CString Name2=::GetFirstLetter(tp2.m_Name);
	
	return Name1 < Name2;
}

//注册消息
void CAndroidDataEngine::RegisterMessage()
{
	CMessageCenter::RegisterMsgHandle((IMessageHandle*)this,MSG_GET_PHONEINFO_OVER);
	CMessageCenter::RegisterMsgHandle((IMessageHandle*)this,MSG_CONTACT_INFO_TO_DATA_ENGINE);
	CMessageCenter::RegisterMsgHandle((IMessageHandle*)this,MSG_CONTACTGROUP_INFO_TO_DATA_ENGINE);
	
}

//注销消息
void CAndroidDataEngine::UnRegisterMessage()
{
	CMessageCenter::LogoutMsgHandle((IMessageHandle*)this,MSG_GET_PHONEINFO_OVER);
	CMessageCenter::LogoutMsgHandle((IMessageHandle*)this,MSG_CONTACT_INFO_TO_DATA_ENGINE);
	CMessageCenter::LogoutMsgHandle((IMessageHandle*)this,MSG_CONTACTGROUP_INFO_TO_DATA_ENGINE);
}

//响应消息
void CAndroidDataEngine::OnMessage(eMessage Message,DWORD SystemMsg,WPARAM wParam,LPARAM lParam)
{
	switch(Message)
	{
	case MSG_GET_PHONEINFO_OVER:
		{
			sPhoneInfo* pPhoneInfo = (sPhoneInfo*)wParam;
			if(pPhoneInfo != NULL)
				m_PhoneInfo = *pPhoneInfo;
		}
		break;
	case MSG_CONTACT_INFO_TO_DATA_ENGINE:
		{
			DoContactMsg(wParam,lParam);
		}
		break;
	case MSG_SMS_INFO_TO_DATA_ENGINE:
		{
			DoSmsMsg(wParam,lParam);
		}
		break;
	case MSG_CONTACTGROUP_INFO_TO_DATA_ENGINE:
		{
			DoContactGroupMsg(wParam,lParam);
		}
		break;
	}
}


//联系人排序
void CAndroidDataEngine::SortContactInfo(vector<sContactInfo>&SortData,eContactSortType Type)
{
	if(Type == CONTACT_SORT_BY_NAME)
	{
		sort(SortData.begin(), SortData.end()-1, SortContactByName);
	}
}

//处理联系人消息
void CAndroidDataEngine::DoContactMsg(WPARAM wParam,LPARAM lParam)
{
	switch(wParam)
	{
	case CONTACT_REQUEST_CMD:
		{
			vector<sContactInfo>* pVector = (vector<sContactInfo>*)lParam;
			if(pVector != NULL && !pVector->empty())
			{
				m_ContactInfoList.insert(m_ContactInfoList.end(),pVector->begin(),pVector->end());
				SortContactInfo(m_ContactInfoList);
				CMessageCenter::PostMsg(MSG_CONTACT_REQUEST_CMD,(WPARAM)&m_ContactInfoList);
			}
		}
		break;

	case CONTACT_ADD_CMD:             //添加联系人命令
		{
			vector<sContactInfo>* pVector = (vector<sContactInfo>*)lParam;
			if(pVector != NULL && !pVector->empty())
			{
				m_ContactInfoList.insert(m_ContactInfoList.end(),pVector->begin(),pVector->end());
				SortContactInfo(m_ContactInfoList);
				CMessageCenter::PostMsg(MSG_CONTACT_ADD_CMD,(WPARAM)&m_ContactInfoList);
			}
		}
		break;

	case CONTACT_DELTE_CMD:           //删除联系人命令
		{
			vector<CString>* pVector = (vector<CString>*)lParam;
			if(pVector != NULL && !pVector->empty())
			{
				vector<sContactInfo>::iterator it = m_ContactInfoList.begin();
				while(it != m_ContactInfoList.end())
				{
					vector<CString>::iterator StrIt=pVector->begin();
					if(StrIt == pVector->end())
						break;

					bool IsEraseIt=false;

					while(StrIt != pVector->end())
					{
						if(it->m_ID == *StrIt)
						{
							StrIt=pVector->erase(StrIt);
							IsEraseIt=true;
							break;
						}
						else
							StrIt++;
					}

					if(IsEraseIt)
						it = m_ContactInfoList.erase(it);
					else
						it++;
				}

				CMessageCenter::PostMsg(MSG_CONTACT_DELTE_CMD,(WPARAM)&m_ContactInfoList);
			}

		}break;
		
	case CONTACT_DELTE_ALL_CMD:       //删除所有联系人
		{
			if(lParam)
			{
				m_ContactInfoList.clear();
				CMessageCenter::PostMsg(MSG_CONTACT_DELTE_ALL_CMD,(WPARAM)&m_ContactInfoList);
			}
		}
		break;
		
	case CONTACT_EDIT_CMD:            //编辑联系人命令
		{
			vector<sContactInfo>* pVector = (vector<sContactInfo>*)lParam;
			if(pVector != NULL && pVector->size() == 1)
			{
				vector<sContactInfo>::iterator it = m_ContactInfoList.begin();
				while(it != m_ContactInfoList.end())
				{
					if(it->m_ID == (*pVector)[0].m_ID)
					{
						*it = (*pVector)[0];
						break;
					}
					it++;
				}

				CMessageCenter::PostMsg(MSG_CONTACT_EDIT_CMD,(WPARAM)&(*it));
			}

		}
		break;
	}
}

//匹配短信与联系人
void CAndroidDataEngine::SmsMatchContact(vector<sSmsInfo>* pVector)
{
	for(int Index=0; Index < (int )pVector->size(); Index++)
	{

		CString mobileNumber;
		CString tempNumber((*pVector)[Index].m_SmsCaller);  //与联系人匹配
		if(tempNumber.Find(_T("+86"))!= -1)
		{
			tempNumber.Delete(0,3);
			mobileNumber = tempNumber;
		}
		else
			mobileNumber = tempNumber;

		for (int i = 0;i<(int)m_ContactInfoList.size();i++)
		{ 
			if ((mobileNumber == m_ContactInfoList[i].m_MobileHome) || \
				(mobileNumber == m_ContactInfoList[i].m_MobileNumber) || \
				(mobileNumber == m_ContactInfoList[i].m_MobileWork) || \
				(mobileNumber == m_ContactInfoList[i].m_PhoneHome) || \
				(mobileNumber == m_ContactInfoList[i].m_PhoneNumber) || \
				(mobileNumber == m_ContactInfoList[i].m_PhoneWork) )

			{
				(*pVector)[Index].m_ContactName = m_ContactInfoList[i].m_Name;
			}else
			{
				(*pVector)[Index].m_ContactName = (*pVector)[Index].m_SmsCaller;
			}
		}
		CString Key= (*pVector)[Index].m_SmsCaller;
		m_SmsInfoList[Key].push_back((*pVector)[Index]);
	}

}

//处理短信消息
void CAndroidDataEngine::DoSmsMsg(WPARAM wParam,LPARAM lParam)
{
	switch(wParam)
	{
	case SMS_REQUEST_CMD:
		{
			vector<sSmsInfo>* pVectorSms = (vector<sSmsInfo>*)lParam;
			if(pVectorSms != NULL && !pVectorSms->empty())
			{
					SmsMatchContact(pVectorSms);
					CMessageCenter::PostMsg(MSG_SMS_REQUEST_CMD,(WPARAM)&m_SmsInfoList);
			}		
		}

		break;
	case SMS_ADD_CMD:                      //添加短信命令
		break;
	case SMS_DELTE_CMD:                    //删除短信命令
		{			
			vector<CString>* pVector = (vector<CString>*)lParam;
			if(pVector != NULL && !pVector->empty())
			{
				map<CString,vector<sSmsInfo>>::iterator it = m_SmsInfoList.begin();
				while(it != m_SmsInfoList.end())
				{
					vector<CString>::iterator StrIt=pVector->begin();
					if(StrIt == pVector->end())
						break;

					bool IsEraseIt=false;

					while(StrIt != pVector->end())
					{
						for (int index = 0; index < (int)it->second.size(); index++)
						{
							if (it->second[index].m_SmsID == *StrIt)
							{
								StrIt=pVector->erase(StrIt);
								IsEraseIt=true;
								break;
							}
							else
								it++;
						}
					}

					if(IsEraseIt)
						it = m_SmsInfoList.erase(it);
					else
						it++;
				}
				CMessageCenter::PostMsg(MSG_CONTACT_DELTE_CMD,(WPARAM)&m_SmsInfoList);
				}

		}
		break;
	case SMS_DELTE_ALL_CMD:                //删除所有短信
		break;
	case SMS_EDIT_CMD:                     //编辑短信命令
		break;
	case SMS_BACKUP_CMD:                   //短信备份
		break;
	case SMS_SEND_CMD:					  //发送短信
		{
			sSmsInfo senSmsInfo = *(sSmsInfo*)lParam;
			

		}
		break;
	default: 
		break;

	}
}

//处理联系人分组消息
void CAndroidDataEngine::DoContactGroupMsg(WPARAM wParam,LPARAM lParam)
{
		switch(wParam)
		{
		case CONTACTGROUP_REQUEST_CMD:
			{
				vector<sGroupInfo>* pVector = (vector<sGroupInfo>*)lParam;
				if(pVector != NULL && !pVector->empty())
				{
					m_GroupInfoList.insert(m_GroupInfoList.end(),pVector->begin(),pVector->end());
					CMessageCenter::PostMsg(MSG_CONTACTGROUP_REQUEST_CMD,(WPARAM)&m_GroupInfoList);
				}
			}
			break;
		case CONTACTGROUP_ADD_CMD:
			{
				vector<sGroupInfo>* pVector = (vector<sGroupInfo>*)lParam;
				if(pVector != NULL && !pVector->empty())
				{
					m_GroupInfoList.insert(m_GroupInfoList.end(),pVector->begin(),pVector->end());
					CMessageCenter::PostMsg(MSG_CONTACTGROUP_ADD_CMD,(WPARAM)&m_GroupInfoList);
				}

			}
			break; 
		case CONTACTGROUP_DELETE_CMD:  
			{
				vector<CString>* pVector = (vector<CString>*)lParam;
				if(pVector != NULL && !pVector->empty())
				{
					vector<sGroupInfo>::iterator it = m_GroupInfoList.begin();
					while(it != m_GroupInfoList.end())
					{
						vector<CString>::iterator StrIt=pVector->begin();
						if(StrIt == pVector->end())
							break;

						bool IsEraseIt=false;

						while(StrIt != pVector->end())
						{
							if(it->m_GroupID == *StrIt)
							{
								StrIt=pVector->erase(StrIt);
								IsEraseIt=true;
								break;
							}
							else
								StrIt++;
						}

						if(IsEraseIt)
							it = m_GroupInfoList.erase(it);
						else
							it++;
					}

					CMessageCenter::PostMsg(MSG_CONTACTGROUP_DELETE_CMD,(WPARAM)&m_GroupInfoList);
				}


			}
			break;
		case CONTACTGROUP_DELETE_ALL_CMD:   
			{
				if(lParam)
				{
					m_GroupInfoList.clear();
					CMessageCenter::PostMsg(MSG_CONTACTGROUP_DELETE_ALL_CMD,(WPARAM)&m_GroupInfoList);
				}
			}
			break;
		case CONTACTGROUP_EDIT_CMD:  
			{
				vector<sGroupInfo>* pVector = (vector<sGroupInfo>*)lParam;
				if(pVector != NULL && pVector->size() == 1)
				{
					vector<sGroupInfo>::iterator it = m_GroupInfoList.begin();
					while(it != m_GroupInfoList.end())
					{
						if(it->m_GroupID == (*pVector)[0].m_GroupID)
						{
							*it = (*pVector)[0];
							break;
						}
						it++;
					}

					CMessageCenter::PostMsg(MSG_CONTACTGROUP_EDIT_CMD,(WPARAM)&(*it));
				}
			}
			break;

		}
}

