
 
#include "contact_define.h"
  


//这两个头文件中定义了一些要用的常量和数据结构。
#include <vector>
#include <string>//  用于字符串的处理
using namespace std;


//自定义的一些返回值
#define SUCESS_BUT_SPACE_SHORT 3
#define CONVERT_OK  1 //转换成功
#define ALLO_FAIL -1 //内存分配失败
#define FAILNEW_VCARDOBJECT -2  // 生成VObject失败
#define FILE_OPEN_FAILED -3
#define STRING_NULL	 -4	//传递来的字符串为空串
#define NMU_IS_LESSTHANONE -5 //num的值小于1
#define NMU_ERROR -6 //num的值小于比结构体中的字段数多，或为负数
#define FILE_FORMAT_ERROR -7


///**********************************************************************************************************************
//* 这个类用于说明一些VCARD中每一个条目的值的ENCODING（主要用于在网络传输过程中对数据的完整性保护）
//* 编码类型有：7BIT、BASE64、QUOTED-PRINTABLE、8BIT，默认值是7BIT。
//* 在TrPbItem结构中的条目中homeaddress一般设置为QUOTED-PRINTABLE，其他的一般都是用默认值。
//* 0 表示7BIT；	1 BASE64；	2 QUOTED-PRINTABLE；	3	8BIT
//* 如果指定的值非法，则按7BIT编码。
//************************************************************************************************************************/
//class encodingcharset
//{
//public:
//	encodingcharset()
//	{
//		nameEn=phoneworkEn=emailEn=homeaddressEn=companyEn=birthdayEn=IDEn=typeEn=0;//默认赋值全为0
//	}
//	
//	int nameEn;
//	int phoneworkEn;  
//	int emailEn;        
//	int homeaddressEn;
//	int companyEn;
//	int birthdayEn; 
//	int IDEn;
//	int typeEn;
//private://暂且保留，不可用。
//	encodingcharset(int na,int ph,int em,int add,int comp,int bir,int id,int type)
//	{
//		nameEn=na;	phoneworkEn=ph;	emailEn=em;	homeaddressEn=add;
//		companyEn=comp;	birthdayEn=bir;	IDEn=id;	typeEn=type;
//	}
//};

/*********************************************************************************************************************
* 将TrPbItem格式的数据转换成VCard2.1格式
*
* @pbitem (in)为被转换的数据	TrPbItem 结构中homeaddress的结构是: 
*  住宅邮递地址(邮政信箱);住宅扩展地址;住宅所在街道;市;省（自治区）;邮编;国家地区各个值之间用英文的分号隔开（字段中都不
*  能有分号）。如果一个值为空，也要加分号（如除了国家地区外其他的都为空的写法：;;;;;;国家地区
* @myvcard21str (out) 用于存储转换后的数据；myvcard21str是使用者建立的数据结构，将他的引用传递给函数。
* @enchset (in)中存储的为VCARD中各条目所使用的编码类型，供以后升级此插件使用，在这里只需先这样处理：
*
* @ret 如果转换成功，返回CONVERT_OK，否则返回相应的错误代码
*
* 如果输入的格式不对，这个函数不作检查，故不会报错，如email地址写成akflajfasdf 也不会报错。
* 如果某一个值中有分号(';')，则会自动加上'\'；因为在VCARD中,分号是分隔符，因此自动加上了转义字符。
* 注意：使用时如果pbitem某一项的值为空，则一定要'\0'放在char[0]位置上，pbitem.mobilenumber的值为空
* 则令pbitem.mobilenumber[0]='\0';否则会出现乱码
***********************************************************************************************************************/
 

/**********************************************************************************************************************
* 详细注解减函数ConvertTrPbItemtoVcard21(.....);只是将这个函数生成的字符串写到指定的文件当中去了,
* @pbitem (in) 说明略； @path (in)要写入的文件的目录和文件名；	@enchset(in) 说明略
* @ret 如果转换成功，返回CONVERT_OK，否则返回相应的错误代码
*
* 注意：这里的写文件按是覆盖式写，即原来文件中的内容都被覆盖掉了
***********************************************************************************************************************/
int ConvertTrPbItemtoVcard21andWriteToFile(const TrPbItem& trPbItem, WCHAR* pwchPath);

/**********************************************************************************************************************
* 这个函数将一堆pbitem的信息写入到一个文件当中去。
* @pbitem (in) TrPbItem数组； @path (in)要写入的文件的目录和文件名；	@enchset (in)说明略 @num (in)表示pbitem数组的维数。
* @ret 如果转换成功，返回CONVERT_OK，否则返回相应的错误代码

* 不建议使用这个函数。建议一个联系人写到一个文件中去，这样这个文件的兼容性更好。一个文件中写多个联系人的话有些程序可能会不识别。
***********************************************************************************************************************/
int ConvertTrPbItemtoVcard21andWriteToOneFile(const vector< TrPbItem> &pbContactsMgr, WCHAR* path);

/**********************************************************************************************************************
* 将一个含有vcard2.1格式的字符串中的数据读到TrPbItem结构中
* @myvcard21str (in)包含vcard2.1格式的字符串	@pbitem (out)用于盛放转换后的结果。，是用户自己建立的数据结构。
*
* 转换成功，返回返回CONVERT_OK，否则返回相应的错误代码
***********************************************************************************************************************/
int ConvertVcard21toTrPbItem(const wstring & myvcard21str, TrPbItem* pTrPbItem);

/**********************************************************************************************************************
* 从文件中读数据并把其中的数据提取到TrPbItem结构中
***********************************************************************************************************************/
int ConvertVcard21toTrPbItemandReadFromFile(const WCHAR* path,vector< TrPbItem> &m_PbContactsMgr,int n);

/**********************************************************************************************************************
* 与函数ConvertVcard21toTrPbItem(..)的功能类似，只是从文件中读数据，而不是用字符串
***********************************************************************************************************************/
int ConvertVcard21toTrPbItemandReadFromFile(const WCHAR* path, TrPbItem* pTrPbItem);

/**********************************************************************************************************************
* 用以得到一个vcard2.1或vcard3.0文件中有多少个vcard对象（即联系人）。即一个文件中存储了几个联系人
* @path (in)文件的路径及文件名
* @ret 返回文件中含有多少个联系人的信息。如果有错误返回0或负值。
***********************************************************************************************************************/
int GetVcardObjectNum(const WCHAR* path);


/**********************************************************************************************************************
* 下面几个函数的功能及实现与上面的几个函数类似，请参考上面几个相应函数的说明
***********************************************************************************************************************/
int ConvertTrPbItemtoVcard30(const TrPbItem& pbitem,wstring& myvcard30str);

int ConvertTrPbItemtoVcard30andWriteToFile(const TrPbItem& pbitem,WCHAR* path);

int ConvertTrPbItemtoVcard30andWriteToOneFile(const TrPbItem pbitem[],WCHAR* path,int num);

int ConvertVcard30toTrPbItem(const wstring & myvcard30str,TrPbItem& pbitem);

int ConvertVcard30toTrPbItemandReadFromFile(const WCHAR* path,TrPbItem& pbitem);

int ConvertVcard30toTrPbItemandReadFromFile(const WCHAR* path,TrPbItem pbitem[],int n);

/**********************************************************************************************************************
* 这个结构体在函数ConvertCSVtoTrPbItem(...)中使用，用于指定各个数据在CSV文件中的顺序。不同的csv文件各个数据排放的顺序可能不同
* 因此设计了这个数据结构，用于指定各个值存在的顺序。
* 是从1开始，而不是从0开始。（即第一个数据在字符串中的位置是1，而不是0）
***********************************************************************************************************************/
struct orderofpropincsv
{
	int name;	int mobilenumber;	int mobilehome;	int mobilework;		int phonenumber;	int phonehome;	
	int phonework;	int email;		int PostOfficeAddress; int ExtendedAddress;int Street;int Locality;
	int Region;int Postalcode;int Country;		int company;		int birthday;
	int fax;		int departments;	int duties;
};

/**********************************************************************************************************************
* 将一些TrPbItem结构的数据转换成CSV格式。
* @pbitem[] (in)为pbitem的数组，盛放将要转换的数据。	@CSVstr (out)用户建立的数据结构，用于接收输出。@num (in)为pbitem数组的长度
*
* 转换成功，返回返回CONVERT_OK，否则返回相应的错误代码
*
***********************************************************************************************************************/
int ConvertTrPbItemtoCSV(const vector< TrPbItem*>* pVectorContacts, wstring& CSVstr);


/**********************************************************************************************************************
* 将包含CSV结构的数据存储到TrPbItem结构中。
* @CSVstr包含CSV结构的数据的字符串.注意这个字符串中直接包含数据即可，不用包含说明所用的头。即csv文件的第一行数据。	
* @pbitem，用于盛放转换后的数据，用户建立。@order用于说明各个数据在CSV结构中的排列顺序。
*
***********************************************************************************************************************/
int ConvertCSVtoTrPbItem(char* pchLineText, TrPbItem* pTrPbItem);
