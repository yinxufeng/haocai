#pragma once
#include <vector>
#include <map>
using std::vector;
using std::map;

#define EXPORT_API   __declspec(dllexport)
#define EXPORT_CLASS __declspec(dllexport)


#define __WRITE_LOG__
#ifdef __WRITE_LOG__
#define  XWriteEventLog  WriteLog
#endif

/**********************************SOCKET回调函数定义*************************************/
typedef void (*FunctionSocketCallBack)(CString& SocketStr);

/**********************************枚举定义***********************************************/

//应用程序路径定义
enum ePathType
{
	PATH_UNKOWN,
	PATH_SDCARD,
	PATH_PHONE,
};

//手机操作系统定义
enum ePhoneOSType
{
	PHONE_OS_ANDROID,
};

 //连接类型
enum eConnectMode 
{
	CONNECT_MODE_BY_USB,
	CONNECT_MODE_BY_WIFI
};

//联系人排序方式
enum eContactSortType
{
	CONTACT_SORT_BY_NAME,  //按姓名排序   
	CONTACT_SORT_BY_TIME,  //按时间排序
};

//短信状态
enum eSmsStaus
{
	SMS_IS_READ,            //短信已读
	SMS_NOT_READ,           //短信未读
};

//短信信箱
enum eSmsBox
{
	SMSBOX_INBOX     = 1   ,     //收件箱  
	SMSBOX_SENTBOX   = 2   ,     //已发件箱
	SMSBOX_DRAFT     = 3   ,     //草稿箱
	SMSBOX_OUTBOX    = 4   ,     //发件箱
	SMSBOX_DELETEBOX = 5   ,     //已删除信箱
};

//短信排序方式
enum eSmsSortType
{
	SMS_SORT_BY_TIME,                //按时间排序
	SMS_SORT_BY_NAME,                //按姓名排序
	SMS_SORT_BY_READ,                //按是否已读排序
};




/**********************************结构体定义***********************************************/



/*********************************手机信息结构体定义****************************************/
//手机信息
struct sPhoneInfo
{
	CString m_CompayName;         //手机厂商
	CString m_PhoneModel;         //手机型号
	CString m_PhoneIMEI;          //手机IMEI
	CString m_PhoneIMSI;          //手机IMSI
	CString m_PhoneOS;            //手机操作系统
	CString m_PhoneOSVer;         //手机操作系统版本
	CString m_InstallType;        //支持的安装类型


	__int64 m_PhoneFreeMem;       //手机内存空余大小
	__int64 m_PhoneTotalMem;      //手机内存总大小
	__int64 m_PhoneUsedMem;       //手机内存已用大小

	__int64 m_SDFreeMem;          //SD卡空余大小
	__int64 m_SDTotalMem;         //SD卡总大小
	__int64 m_SDUsedMem;          //SD卡已用大小

	__int64 m_PicMemInPhone;      //图片在手机中所占空间
	__int64 m_PicMemInSD;         //图片在SD卡所占空间

	__int64 m_VideoMemInPhone;    //视频在手机中所占空间
	__int64 m_VideoMemInSD;       //视频在SD卡所占的空间

	__int64 m_MusicMemInPhone;    //音乐在手机中所占空间
	__int64 m_MusicMemInSD;       //音乐在SD卡所占空间

	__int64 m_AppSum;             //应用程序总数
	__int64 m_ContactSum;         //联系人总数
	__int64 m_SmsSum;             //短信总数
	__int64 m_MusicSum;           //音乐总数
	__int64 m_PicSum;             //图片总数
	__int64 m_VideoSum;           //视频总数
	__int64 m_DocSum;             //文档总数


};

/*********************************应用程序结构体定义****************************************/
//定义应用程序信息
struct sAppInfo
{
	CString m_AppName;         //应用程序名称
	CString m_ApkName;         //应用程序APK包名称
	CString m_AppType;         //应用程序类型
	CString m_AppSize;         //应用程序大小
	CString m_AppVersion;      //应用程序版本
	CString m_AppPackName;     //应用程序安装包名
	ePathType m_PathType;      //应用程序路径
	
	sAppInfo()
	{
		m_PathType = PATH_UNKOWN;
	}
};


/*********************************联系人结构体定义****************************************/
//定义联系人信息
struct sContactInfo
{
	CString m_ID;                        //数据库ID
	vector<CString> m_GroupIDs;          //所属分组ID集


	CString m_Name;                      //姓名
	CString m_MobileNumber;              //手机号码(移动)  TEL;CELLCELL   
	CString m_MobileHome;                //手机号码(家庭)  TEL;CELL;HOME
	CString m_MobileWork;                //手机号码(办公)  TEL;CELL;WORK
	CString m_PhoneNumber;               //电话号码        TEL
	CString m_PhoneHome;                 //电话号码(家庭)  TEL;HOME
	CString m_PhoneWork;                 //电话号码(办公)  TEL;WORK
	CString m_Email;                     //私人邮箱  EMAIL
	CString m_HomeAddress;               //家庭地址  ADR
	CString m_Company;                   //公司名称  ORG1 ORG第一个域
	CString m_Birthday;                  //个人生日  BDAY	
	CString m_Fax;                       //传真 TEL;FAX 
	CString m_Departments;               //部门  ORG2 ORG第二个域  
	CString m_Duties;                    //职务  TITLE 

	ePathType m_PathType;                //联系人位置

	sContactInfo()
	{
		m_PathType = PATH_UNKOWN;
	}
};


/*********************************联系人操作命令定义****************************************/
enum eContactCmdType
{
	CONTACT_REQUEST_CMD,                  //请求联系人所有数据命令
	CONTACT_ADD_CMD,                      //添加联系人命令
	CONTACT_DELTE_CMD,                    //删除联系人命令
	CONTACT_DELTE_ALL_CMD,                //删除所有联系人
	CONTACT_EDIT_CMD,                     //编辑联系人命令
	CONTACT_BACKUP_CMD,                   //联系人备份

	CONTACTGROUP_REQUEST_CMD,             //请求联系人分组
	CONTACTGROUP_ADD_CMD,                 //添加联系人分组
	CONTACTGROUP_DELETE_CMD,              //删除联系人分组
	CONTACTGROUP_DELETE_ALL_CMD,              //删除所有联系人分组
	CONTACTGROUP_EDIT_CMD,                //编辑联系人分组
};

struct sContactCmd                        //联系人命令类型
{
	eContactCmdType    m_CmdType;         //命令类型
	DWORD              m_CmdId;           //命令ID
	WPARAM             m_CmdParam;        //命令参数
	LPARAM             m_CmdParamCount;   //命令参数个数
};



//定义分组信息
struct sGroupInfo
{
	CString m_GroupID;          //分组ID
	CString m_GroupName;        //分组姓名
	int     m_ContactCount;     //联系人数
	bool    m_IsSystem;         //是否属于系统分组

	sGroupInfo()
	{
		m_ContactCount = 0;
		m_IsSystem     = false;
	}
};

//定义通话记录
struct sCallLogInfo
{
	CString m_LogName;          //记录名 号码_时间
	CString m_PhoneNumber;      //电话号码
	CString m_CallName;         //呼叫人
	CString m_CallType;         //呼叫类型  receivedcall/outgoing/incoming/missed
	CString m_Date;             //日期
	CString m_DurationTime;     //通话时长
};

/*********************************短信结构体定义****************************************/
struct sSmsInfo
{
	CString   m_SmsID;                    //短信ID   短信的唯一标志
	CString   m_ContactName;              //联系人姓名
	CString   m_SmsBody;                  //短信内容
	CString   m_SmsCaller;                //短信号码
	CString   m_TimeStamp;                //短信时间戳
	eSmsStaus m_SmsStaus;                 //短信状态
	eSmsBox   m_SmsBox;                   //短信标志

	sSmsInfo()
	{
		m_SmsBox = SMSBOX_INBOX;
		m_SmsStaus = SMS_NOT_READ;
	}
};

//发送短信
struct sSendSmsInfo
{
	CString m_PhoneNumber;                //手机号码
	CString m_Text;                       //文本信息
};

/*********************************短信操作命令定义******************************************/
enum eSmsCmdType
{
	SMS_REQUEST_CMD,                  //请求短信所有数据命令
	SMS_ADD_CMD,                      //添加短信命令
	SMS_DELTE_CMD,                    //删除短信命令
	SMS_DELTE_ALL_CMD,                //删除所有短信
	SMS_EDIT_CMD,                     //编辑短信命令
	SMS_BACKUP_CMD,                   //短信备份
	SMS_SEND_CMD,					  //发送短信
};

struct sSmsCmd                        //短信命令类型
{
	eSmsCmdType        m_CmdType;         //命令类型
	DWORD              m_CmdId;           //命令ID
	WPARAM             m_CmdParam;        //命令参数
	LPARAM             m_CmdParamCount;   //命令参数个数
};


/*********************************文件结构体定义****************************************/
struct sFileInfo
{
	CString m_FileName;                    //文件或者文件夹的名称
	CString m_FileAuthority;               //文件权限，'R'代表可以读取，'W'代表可以写入，'D'代表可以删除
	CString m_FileSize;                    //文件大小
	CString m_FileCreateTime;              //文件创建时间
	bool    m_IsFileDir;                   //是否是文件夹
	ePathType m_PathType;                  //文件所处文件位置

	CString m_FileTime;                    //文件时长 视频 音频需要
	CString m_FileTile;                    //文件标题
	CString m_Format;                      //文件格式
	CString m_Special;                     //文件专辑
	CString m_Artist;                      //艺术家
	CString m_ThumbPath;                   //缩略图路径
};


/*********************************手机连接结构体定义****************************************/

//定义USB连接结构体
struct sUsbConnectInfo
{
	CString m_PhoneName;              //手机名字
	CString m_DeviceId;               //设备ID 下载店使用
	CString m_DriveUrl;               //驱动下载路径
	CString m_PhoneImageUrl;          //手机图片
	CString m_PhoneScreenInfo;        //手机截屏信息
	CString m_PhoneVidPid;            //手机的厂商ID和产品ID
	BOOL    m_IsInstallDrive;         //是否已经安装了驱动
};

//定义wifi连接结构体
struct sWifiConnectInfo
{
	CString m_WiFiIp;             //IP地址
	CString m_SecurityCode;       //验证码
	CString m_PhoneName;          //手机名字
	CString m_ID;                 //手机唯一标识

	DWORD   m_WiFiPort;           //端口
	DWORD   m_WiFiFlag;           //WIFI标识
	DWORD   m_IsAddFlag;          //是否添加标识
};

 //手机状态
 struct sPhoneStatus                     
 {
	 CString m_PhoneDesId;                //手机描述id
	 BOOL    m_IsOffLine;                 //手机是否处于offline下
 };
