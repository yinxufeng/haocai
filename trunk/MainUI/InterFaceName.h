

CString cszCB_IsOurCustomBrowser	    = _T("CB_IsOurCustomBrowser");

//关于 主对话框 的操作
CString csCPP_MoveMianDlg				= _T("CPP_MoveMainDlg");				//移动主对话框
CString csCPP_Close						= _T("CB_Close");						//关闭主对话框
CString csCPP_MinDlg					= _T("CPP_Min");						//最小化主对话框

//联系人模块函数
CString csCPP_OnRequestContactData      = _T("CPP_OnRequestContactData");		//请求联系人数据
CString csCPP_OnRequestRfreshContactData= _T("CPP_OnRequestRfreshContactData"); //请求刷新联系人数据
CString csCPP_OnRequestAddContactData   = _T("CPP_OnRequestAddContactData");	//添加联系人数据
CString csCPP_OnRequestAddContactFile   = _T("CPP_OnRequestAddContactFile");	//添加联系人文件
CString csCPP_OnRequestBackUpContactData= _T("CPP_OnRequestBackUpContactData"); //备份联系人
CString csCPP_OnRequestDeletContactData = _T("CPP_OnRequestDeleteContactData");	//删除联系人
CString csCPP_OnRequestEditContactData  = _T("CPP_OnRequestEditContactData");	//编辑联系人

CString csCPP_OnRequestGroupData        = _T("CPP_OnRequestGroupData");			//请求分组
CString csCPP_OnRequestAddGroupData     = _T("CPP_OnRequestAddGroupData");		//添加分组
CString csCPP_OnRequestDeleteGroupData  = _T("CPP_OnRequestDeleteGroupData");	//删除分组
CString csCPP_OnRequestEditGroupData    = _T("CPP_OnRequestEditGroupData");		//编辑分组
//短信模块函数
CString csCPP_OnRequestSmsData      = _T("CPP_OnRequestSmsData");		//请求短信数据
CString csCPP_OnRequestDeleteSmsData= _T("CPP_OnRequestDeleteSmsData");	//请求删除短信
CString csCPP_OnRequestSendSms      = _T("CPP_OnRequestSendSms");		//请求发送短信
//文件管理模块函数

//接口定义
enum DISPID_CPP {
	DISPID_CB_IsOurCustomBrowser = 1,
	//关于主对话框的操作
	DISPID_CB_Close,						//关闭对话框
	DISPID_CB_MoveMianDlg,					//鼠标移动主对话框
	DISPID_CB_MinDlg,						//最小化对话框
	//联系人模块的操作
	DISPID_CB_RequestContactData,			//请求联系人数据
	DISPID_CB_RequestRfreshContactData,		//请求刷新联系人数据
	DISPID_CB_RequestAddContactData,		//添加联系人数据
	DISPID_CB_RequestAddContactFile,        //添加联系人文件
	DISPID_CB_RequestDeleteContactData,     //删除联系人
	DISPID_CB_RequestEditContactData,       //编辑联系人
	DISPID_CB_RequestBackUpContactData,     //备份联系人
	
	DISPID_CB_RequestGroupData,             //请求分组
	DISPID_CB_RequestAddGroupData,          //添加分组
	DISPID_CB_RequestDeleteGroupData,       //删除分组
	DISPID_CB_RequestEditGroupData,         //编辑分组
	//短信模块的操作
	DISPID_CB_RequestSmsData,				//请求短信数据
	DISPID_CB_RequestAddSmsData,			//添加短信
	DISPID_CB_RequestAddSmsFile,			//添加短信文件
	DISPID_CB_RequestDeleteSmsData,			//删除短信
	DISPID_CB_RequestEditSmsData,			//编辑短信
	DISPID_CB_RequestSendSms,				//发送短信
	DISPID_CB_RequestAcceptSms,				//接收到了新的短信
	//文件管理模块的操作
	DISPID_CB_RequestInstallApk,			//请求安装APK
	DISPID_CB_RequestBatchInstallApk,		//请求批量安装APK
	DISPID_CB_RequestUninstallApk,			//请求卸载APK
	DISPID_CB_RequestBatchUninstallApk,		//请求批量卸载APK
};