/***********************************************************************************
* 说明      ：  联系人转化工具                                                     *
* 创建人    ：  谭军红                                                             *
* 创建日期  ：  2012-2-24                                                          *
***********************************************************************************/

//自定义的一些返回值
#define TRANS_OK                 1  //转换成功
#define ALLO_FAIL                 -1  //内存分配失败
#define FAILNEW_VCARDOBJECT       -2  // 生成VObject失败
#define STRING_NULL	              -4  //传递来的字符串为空串
#define NMU_IS_LESSTHANONE        -5  //num的值小于1
#define NMU_ERROR                 -6  //num的值小于比结构体中的字段数多，或为负数
#define FILE_FORMAT_ERROR         -7  //格式化出错



//从Vcard211字符串转化为联系人信息
int TransVcard211ToContactInfo(CString& VcardStr,sContactInfo& Info);

//从联系人信息转化为Vcard211字符串
int TransContactInfoToVard211(sContactInfo& Info,CString& VcardStr);

//从Vcard30字符串转化为联系人信息
int TransVcard30ToContactInfo(CString& VcardStr,sContactInfo& Info);

//从联系人信息转化为Vcard30
int TransContactInfoToVcard30(sContactInfo& Info,CString& VcardStr);

//从CSV格式转化为联系人信息
int TransCSVToContactInfo(CString& CSVStr,sContactInfo& Info);

//从联系人信息转化为CSV格式字符串
int TransContactInfoToCSV(sContactInfo& Info,CString& CSVStr);

//从字符串转化为VCARD
//int TransStrToVcardObject(CString& VcardStr,VObject* pVcard);

