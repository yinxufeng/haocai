/***********************************************************************************
* 说明      ：  此文件用于消息枚举的定义                                           *
* 创建人    ：  谭军红                                                             *
* 创建日期  ：  2011-9-8                                                           *
***********************************************************************************/

#pragma once

//消息定义
enum eMessage
{
	//系统消息
	MSG_SYSTEM,				           //转发系统消息

	//数据引擎消息
	MSG_GET_PHONEINFO_OVER,           //获取手机信息完成

	/****************数据引擎消息*****************************/  
	 
	MSG_CONTACT_INFO_TO_DATA_ENGINE,          //联系人到数据引擎消息
	MSG_CONTACTGROUP_INFO_TO_DATA_ENGINE,     //联系人分组到数据引擎消息
	MSG_SMS_INFO_TO_DATA_ENGINE,              //短信到数据引擎消息

	/****************联系人模块消息*****************************/
	MSG_CONTACT_REQUEST_CMD,                  //请求联系人所有数据命令
	MSG_CONTACT_ADD_CMD,                      //添加联系人命令
	MSG_CONTACT_DELTE_CMD,                    //删除联系人命令
	MSG_CONTACT_DELTE_ALL_CMD,                //删除所有联系人
	MSG_CONTACT_EDIT_CMD,                     //编辑联系人命令
	MSG_CONTACT_BACKUP_CMD,                   //联系人备份

	MSG_CONTACTGROUP_REQUEST_CMD,             //联系人分组消息
	MSG_CONTACTGROUP_ADD_CMD,                 //添加联系人分组
	MSG_CONTACTGROUP_DELETE_CMD,              //删除联系人分组
	MSG_CONTACTGROUP_DELETE_ALL_CMD,          //删除所有联系人分组
	MSG_CONTACTGROUP_EDIT_CMD,                //编辑联系人分组

	/****************短信模块消息*****************************/
	MSG_SMS_REQUEST_CMD,                  //请求短信所有数据命令
	MSG_SMS_ADD_CMD,                      //添加短信命令
	MSG_SMS_DELTE_CMD,                    //删除短信命令
	MSG_SMS_DELTE_ALL_CMD,                //删除所有短信
	MSG_SMS_EDIT_CMD,                     //编辑短信命令
	MSG_SMS_BACKUP_CMD,                   //短信备份
	MSG_SMS_SEND_CMD,					  //发送短信

	/****************界面消息*****************************/
	
	MSG_START_CONNECT_PHONE_WIFI,              //通过局域网连接WIFI
	MSG_UPDATE_USB_DEVICES_LIST,              //更新USB设备列表消息
	MSG_UPDATE_WIFI_DEVICES_LIST,             //更新WIFI设备列表消息
	MSG_UPDATE_DLG_STATUS_BY_WIFI,            //更新对话框状态

	//主页消息
	MSG_START_CONECT_PHONE,           //开始连接手机消息
	MSG_UPDATE_DRIVE_INFO_LIST,       //更新驱动信息列表
	MSG_GOTO_DEVICE_LIST,             //跳转到设备列表
	MSG_GOTO_USB_TIPDLG,              //跳转到USB提示页面
	MSG_GOTO_USB_CONNECTDLG,          //跳转到USB连接页面
	MSG_GOTO_INSTALL_DRIVE_DLG,       //跳转到驱动安装页面
	MSG_GOTO_TAB_DOWNLOAD,			//跳转到下载店页面
	MSG_GOTO_TAB_CONTACTS,			  //跳转到联系人页面
	MSG_GOTO_TAB_SMS,				  //跳转到短信页面
	MSG_GOTO_TAB_FILEMANAGE,		  //跳转到文件管理界面	
	MSG_UPDATE_COUNTDATA_SUM,		  //更新数据统计总数
	MSG_DISCONNECT_PHONE,			  //手机断连消息
	MSG_CONNECTED_PHONE,			  //手机连接消息
	MSG_UPDATE_LOGINED_STATE,			//登陆状态刷新
	MSG_DOWN_PHONE_BORAD_IMAGE,         //下载手机外壳消息
	MSG_UPDATE_PHONE_BORAD_IMAGE,       //更新手机外壳消息
	MSG_UPDATE_DOWNLOAD_COUNT,			//更新任务管理统计数
	MSG_SHOW_DOWNLOAD_TIP,				//显示下载提示信息


	//联系人消息
	MSG_QUERY_INPUT_VALUE,				  //编辑框输入搜索结果
	MSG_EDIT_KILLFFOUSE,				//编辑框失去焦点消息
	MSG_CONTACT_GROUP_COMMIT,			//联系人分组提交事件
	MSG_COMBOX_KIILFOUSE,				//失去焦点事件
	MSG_CONTACT_LBCLICK,				//联系人单击事件
	MSG_EDIT_WHEEL,						//编辑框滚动事件
	MSG_UPDATE_CONTACT_GROUP,			//更新联系人组数据
	MSG_UPDATE_SHOW_CONTACT_LIST,		//显示联系人列表
	MSG_EDIT_CLICKACTIVE,				// 编辑框通过鼠标点击而激活

	//短信消息
	MSG_BEGIN_IMPORT_SMS,             //开始导入短信
	MSG_EDIT_CHANGE,				  // 编辑框的内容发生改变时发送

	//文件管理消息
	MSG_UPDATE_APP_LIST,					//刷新当前列表消息
	MSG_UPNETDISK_DATA,                     //更新网盘数据
	MSG_QUERY_APP,						//搜索应用程序消息

	//公共消息
	MSG_OVER_PROGRESS,					//进度条结束消息，用于销毁进度条对话框
	MSG_CLOSE_PROGRESS,					//关闭进度条
	MSG_UPDATE_PROGRESS,				//更新进度条消息 (注：按百分比显示需要传全量, 按范围显示需要传增量。)
	MSG_RESET_PROGRESS,					//重置进度消息
	MSG_STARTDOWN_INSTALL_PACK,         //开始下载安装包消息
	MSG_DOWNING_INSTALL_PACK,            //安装包下载进行中消息
	MSG_CHECK_PACK_STATUS,                //检测安装包状态
	MSG_DOWNOVER_INSTALL_PACK ,            //下载安装完成消息
	MSG_STARTCHECK_INSTALL_PACK,          //启动检测新版本
	MSG_SHOW_TOOLTIP,					//显示提示信息
	MSG_LIST_MOUSE_MOVE,				//列表鼠标滑过事件
	MSG_GET_MOUSE_POINT,				//获取鼠标窗口坐标
	

	MSG_CREATE_SHADE_FLOOR,            //重新创建蒙层消息

	MSG_UPDATE_USB_LIST,              //更新USB机型列表
	MSG_UPDATE_WIFI_LIST,              //更新WIFI机型列表	
};

const	WORD	MRSSAGE_TYPE_COUNT	=	74;			//消息种类数
//每次增加一种消息时MRSSAGE_TYPE_COUNT需增加1，且MRSSAGE_TYPE_COUNT计数从1开始而不是0
