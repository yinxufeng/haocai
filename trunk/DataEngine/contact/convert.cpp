
#include "stdafx.h"
#include<stdlib.h>
#include"convert.h"
#include"fstream"
#include".\vocl\export.h"
#include"base64.h"
#include <time.h>
#include <atlenc.h>
#include"../CommonApi/common.h"
 
//这个函数为非导出函数，用于根据用户指定的编码类型，将编码类型作为参数写到条目中
//7IBT为默认编码，不用写，如过给的编码范围不是所指定的即>3或<0，则按默认的编码(7BIT)处理。
//现在都安默认的规则处理。这个函数暂且不用。供以后的升级版本使用。
void mySetEncoding(VProperty* vp,int encoding)
{
	//if(encoding==0||encoding>3||encoding<0)
	//	;//vp->addParameter(L"ENCODING",L"7BIT");之所以写上，是因为，例如名字为汉字时会用编码QUOTED-PRINTABLE；而不是7BIT。但对于英文字符不写编码方式时为是7BIT
	//else if(encoding==1)
	//	vp->addParameter(L"ENCODING",L"BASE64");
	//else if(encoding==2)
	//	vp->addParameter(L"ENCODING",L"QUOTED-PRINTABLE");
	//else
	//	vp->addParameter(L"ENCODING",L"8BIT");
}

//这个函数是从网上找的，有时间好好地去研究一下,
// 用于对QUOTED-PRINTABLE进行解码，转换成进行qpencoding之前的表示形式
string Qp_decode(string src)
{
    // 输出的字符计数     
    int i = 0;
    string dst;
    char tmp=0;
    while (i < src.size())
    {
        if (src[i] == '=')        // 是编码字节     
        {
            if(i<src.size()-2)
            {
                char ch1=src[i+1];
                char ch2=src[i+2];
                if ((src[i+1]=='\r')||(src[i+1]=='\n')) continue;
                tmp = ((ch1>'9')?(ch1-'A'+10):(ch1-'0'))*16+((ch2>'9')?(ch2-'A'+10):(ch2-'0'));
                dst+=tmp;
                i += 3;
            }
        }
        else        // 非编码字节       
        {
            dst += src[i];
            i++;
        }

    }       // 输出加个结束符     
    dst += '\0';
    return dst;
}

//这两个函数是从网上搜到的。
//将char* 转成wchar_t*的实现函数如下：  
char* w2c(char *pcstr,const wchar_t *pwstr, size_t len)  
{  
	int nlength=wcslen(pwstr);  
	//获取转换后的长度  
	int nbytes = WideCharToMultiByte( 0, // specify the code page used to perform the conversion  
	0,         // no special flags to handle unmapped characters  
	pwstr,     // wide character string to convert  
	nlength,   // the number of wide characters in that string  
	NULL,      // no output buffer given, we just want to know how long it needs to be  
	0,  
	NULL,      // no replacement character given  
	NULL );    // we don't want to know if a character didn't make it through the translation  
	// make sure the buffer is big enough for this, making it larger if necessary  
	if(nbytes>len)   nbytes=len;  
	// 通过以上得到的结果，转换unicode 字符为ascii 字符  
	WideCharToMultiByte( 0, // specify the code page used to perform the conversion  
	0,         // no special flags to handle unmapped characters  
	pwstr,   // wide character string to convert  
	nlength,   // the number of wide characters in that string  
	pcstr, // put the output ascii characters at the end of the buffer  
	nbytes,                           // there is at least this much space there  
	NULL,      // no replacement character given  
	NULL );  
	return pcstr ;  
} 

//这是把asii字符转换为unicode字符，和上面相同的原理  
void c2w(wchar_t *pwstr,size_t len,const char *str)  
{  
	if(str)  
    {  
      size_t nu = strlen(str);  
      size_t n =(size_t)MultiByteToWideChar(CP_ACP,0,(const char *)str,(int)nu,NULL,0);  
      if(n>=len)n=len-1;  
      MultiByteToWideChar(CP_ACP,0,(const char *)str,(int)nu,pwstr,(int)n);  
      pwstr[n]=0;  
    }  
}  

//因为电话的类型多，所以用一个函数专门实现它。 第一个参数的值的含义：
//1 cell 2 cell home 3 cell work 4 tel 5 tel home 6 tel work 7tel fax
//最后一个参数encoding为encoding方式，用于给函数mySetEncoding(..)传递参数。
//第二个参数为要将此TEL条目写入的VCARD对象，第三个参数为TEL的值，即电话号码。
bool AddTELToVObject(int type,VObject* vbp,const char telstr[TR_MAX_CONTACT_ID_LENGTH])
{
	bool ret=false;
	VProperty* vp=0;
	if(type>7||type<1||telstr[0]=='\0')//如果tel的值为空则不加人
		return false;

	wchar_t mywchar[200];//字符串格式转换
	 mywchar[0]='\0'; mywchar[1]='\0';
	mywchar[0]='\0';
	c2w(mywchar,200,telstr);

	vp=new VProperty(L"TEL");
	if(vp==0)
		return false;
	vp->setValue(mywchar);
	//mySetEncoding(vp,encoding);
   if(type==1)//cell
   {
		//vp->addParameter(L"TYPE",L"CELL");//按这种格式，生成的是TEL;TYPE=CELL:telnum,虽然也对，但不符合习惯。
		vp->addParameter(L"CELL",NULL);
   }
   else if(type==2)
   {
		vp->addParameter(L"HOME",NULL);
		vp->addParameter(L"CELL",NULL);
   }
   else if(type==3)
   {
	   vp->addParameter(L"WORK",NULL);
	   vp->addParameter(L"CELL",NULL);

   }
   else if(type==4)
   {
   }
   else if(type==5)
   {
		vp->addParameter(L"HOME",NULL);
   }
   else if(type==6)
   {
		vp->addParameter(L"WORK",NULL);
   }
    else if(type==7)
   {
		vp->addParameter(L"FAX",NULL);
   }
   vbp->addProperty (vp);
   delete vp;
   return true;
}

//这个函数和下一个函数的作用是添加一个地址到vcard中
//type  为参数，0为HOME
//[PostOfficeAddress]; [ExtendedAddress];[Street];[Locality];[Region];[Postalcode];[Country]
//这行变量是供添加地址专用的。
char pos[65];	char ext[105];	char str[105];	char loc[55];	char reg[55];	char pcode[25];	char con[55];
void tostore(int begin,int end,const char homeaddress[],int ind)
{
	if(ind==0)//给postaddress赋值
	{
		int i=0;
		for(;i<end;i++)
			pos[i]=homeaddress[i];
		pos[i+1]='\0';
	}
	else if(ind==1)//extended address
	{
		int j=0;
		for(int h=begin;h<end;h++)
		{	ext[j]=homeaddress[h];	j++;	}
		ext[j+1]='\0';
	}
	else if(ind==2)//street
	{
		int j=0;
		for(int h=begin;h<end;h++)
		{	str[j]=homeaddress[h];	j++;	}
		str[j+1]='\0';
	}
	else if(ind==3)//locality
	{
		int j=0;
		for( int h=begin;h<end;h++)
		{	loc[j]=homeaddress[h];	j++;	}
		loc[j+1]='\0';
	}
	else if(ind==4)//region
	{
		int j=0;
		for( int h=begin;h<end;h++)
		{	reg[j]=homeaddress[h];	j++;	}
		reg[j+1]='\0';
	}
	else if(ind==5)//pcode
	{
		int j=0;
		for( int h=begin;h<end;h++)
		{	pcode[j]=homeaddress[h];	j++;	}
		pcode[j+1]='\0';
	}
	else if(ind==6)//contry
	{
		int j=0;
		for(int h=begin;h<end;h++)
		{	con[j]=homeaddress[h];	j++;	}
		con[j+1]='\0';
	}
}
void AddADRtoVObject(int type,VObject* vbp,const char homeaddress[TR_MAX_CONTACT_ID_LENGTH])
{
	pos[0]='\0';ext[0]='\0';str[0]='\0';loc[0]='\0';reg[0]='\0';pcode[0]='\0';con[0]='\0';
	//分离出每一个字段
	int i=0,ind=0;// i用于计数，ind用于标志该往那个变量里写东西
	int begin=0,end=0;
	for(;homeaddress[i]!='\0'&&i<TR_MAX_CONTACT_ID_LENGTH;i++)
	{
		if(homeaddress[i]==';')
		{
			if(ind==0) end=i;// 对于第一个，不用更改begin的值
			else
			{
				begin=end+1; end=i; 
			}
			tostore(begin,end,homeaddress,ind);
			ind++;
		}
	}
	begin=end+1; end=i; 
	tostore(begin,end,homeaddress,ind);//将最后一个性质值加到里边

	if(pos[0]=='\0'&&ext[0]=='\0'&&str[0]=='\0'&&loc[0]=='\0'&&reg[0]=='\0'&&pcode[0]=='\0'&&con[0]=='\0')
		return;
	else
	{
		//将每个字段和参数加到里边
		VProperty* vp=0;
		wchar_t mywchar[107];//字符串格式转换
		mywchar[0]='\0';mywchar[1]='\0';
		vp=new VProperty(L"ADR");//插入名字
		if(vp!=0)
		{
			if(type==0)
				vp->addParameter(L"HOME",NULL);//插入参数

			//插入值		char pos[65],ext[105],str[105],loc[55],reg[55],pcode[25],con[55];
			c2w(mywchar,107,pos);
			vp->setValue(mywchar);

			mywchar[0]='\0';mywchar[1]='\0';
			c2w(mywchar,107,ext);
			vp->setValue(mywchar);

			mywchar[0]='\0';mywchar[1]='\0';
			c2w(mywchar,107,str);
			vp->setValue(mywchar);
			mywchar[0]='\0';mywchar[1]='\0';
			c2w(mywchar,107,loc);
			vp->setValue(mywchar);

			mywchar[0]='\0';mywchar[1]='\0';
			c2w(mywchar,107,reg);
			vp->setValue(mywchar);

			mywchar[0]='\0';mywchar[1]='\0';
			c2w(mywchar,107,pcode);
			vp->setValue(mywchar);

			mywchar[0]='\0';mywchar[1]='\0';
			c2w(mywchar,107,con);
			vp->setValue(mywchar);

			vbp->addProperty (vp);
			delete vp;
		}
	}
}
//这个函数用于获取当前时间，VCARD格式的REV条目需要用到，时间的获取不难，
//不好处理的是要把他们写到char数组中，比较容易出错（时间函数获取的时间的格式
// 与需要的时间格式不大一样）但时间，月份，日期都是两位的，这点比较好比较好
//
void gettime(char ch[])
{//422T222 共15个
	ch[0]='\0';
	char* temp=new char[30];
	temp[0]='\0';

	time_t now=time(&now); // 变量声明 
	temp=ctime(&now);//用于获取年份，用其他函数获取的年份为两位，不合规范。
	int i;
	for(i=0;temp[i]!='\0';i++) ;
    strcpy(ch,&temp[i-5]);

	temp[0]='\0';//获取月份 日
	now=time(&now);//temp format 12/27/10
	_strdate(temp);
	ch[4]=temp[0];
	ch[5]=temp[1];
	ch[6]=temp[3];
	ch[7]=temp[4];

	ch[8]='T';
	
	temp[0]='\0';//获取时间14:26:36
	_strtime(temp);
	ch[9]=temp[0];
	ch[10]=temp[1];
	ch[11]=temp[3];
	ch[12]=temp[4];
	ch[13]=temp[6];
	ch[14]=temp[7];
	ch[15]='\0';
}


//将sContactInfo中的内容转换成card2.1格式的字符串。 
//当b的值为true时，写version属性，为false则不写。
int innerConvertsContactInfotoVcard21(const sContactInfo& trPbItem, wstring & myvcard21str, bool bIsWriteVersion)
{
	VObject* pMyVcard = VObjectFactory::createInstance(L"VCARD",L"2.1");
	if (pMyVcard == NULL)
	{
		return FAILNEW_VCARDOBJECT;
	}

	//
	VProperty* pVProperty = NULL;//c2w(wchar_t *pwstr,size_t len,const char *str)
	wchar_t wchTemp[500];

	//------------------------------------------
	// 添加头
	pVProperty = new VProperty(L"BEGIN", L"VCARD");//为何要这样写，可以参看WinContact::toString() 函数，在vocl项目中。
	if(pVProperty != NULL)
	{
		pMyVcard->addProperty(pVProperty);
		delete pVProperty;
		pVProperty = NULL;
	}
	else
	{
		if (pMyVcard)
		{
			delete pMyVcard;
			pMyVcard = NULL;
		}
		return ALLO_FAIL;
	}

	// 添加版本
	if(bIsWriteVersion)
	{
		pVProperty = new VProperty(L"VERSION", L"2.1");
		if(pVProperty != NULL)
		{
			pMyVcard->addProperty(pVProperty);
			delete pVProperty;
			pVProperty = NULL;
		}
		else
		{
			if (pMyVcard)
			{
				delete pMyVcard;
				pMyVcard = NULL;
			}
			return ALLO_FAIL;
		}
	}
 
	//名字
	if(trPbItem.)
	{
		memset(wchTemp, 0, 500);
		wchar_t* pwch = ConvertToAnsiFromUtf8(trPbItem.name);
		//c2w(wchTemp, 500, trPbItem.name);
		wcscpy(wchTemp, pwch);
		if (pwch)
		{
			delete pwch;
			pwch = NULL;
		}
		pVProperty = new VProperty(L"N", wchTemp);
		if(pVProperty != NULL)
		{
			pMyVcard->addProperty(pVProperty);
			delete pVProperty;
			pVProperty = NULL;
		}
		else
		{
			if (pMyVcard)
			{
				delete pMyVcard;
				pMyVcard = NULL;
			}
			return ALLO_FAIL;
		}


		pVProperty = new VProperty(L"FN", wchTemp);
		if(pVProperty != NULL)
		{
			pMyVcard->addProperty(pVProperty);
			delete pVProperty;
			pVProperty = NULL;
		}
		else
		{
			if (pMyVcard)
			{
				delete pMyVcard;
				pMyVcard = NULL;
			}
			return ALLO_FAIL;
		}
	}

	//TEL
	AddTELToVObject(1, pMyVcard, trPbItem.mobilenumber);
	AddTELToVObject(2, pMyVcard, trPbItem.mobilehome);
	AddTELToVObject(3 ,pMyVcard, trPbItem.mobilework);
	AddTELToVObject(4 ,pMyVcard, trPbItem.phonenumber);
	AddTELToVObject(5, pMyVcard, trPbItem.phonehome);
	AddTELToVObject(6, pMyVcard, trPbItem.phonework);
	AddTELToVObject(7, pMyVcard, trPbItem.fax);

	// 邮箱
	if(trPbItem.email[0]!='\0')
	{
		pVProperty = new VProperty(L"EMAIL");
		if(pVProperty != NULL)
		{
			memset(wchTemp, 0, 500);
			c2w(wchTemp, 500, trPbItem.email);
			pVProperty->setValue (wchTemp);
			pMyVcard->addProperty(pVProperty);
			delete pVProperty;
			pVProperty = NULL;
		}
		else
		{
			if (pMyVcard)
			{
				delete pMyVcard;
				pMyVcard = NULL;
			}
			return ALLO_FAIL;
		}
	}

	//加入家庭地址 make by kjb for android
	//if(trPbItem.homeaddress[0]!='\0')
	//{
	//	VProperty* vp=new VProperty(L"LABEL");//家庭地址
	//	if(vp!=0)
	//	{
	//		wchar_t mywchar[200];
	//		mywchar[0]='\0';
	//		mywchar[1]='\0';
	//		c2w(mywchar,200,trPbItem.homeaddress);
	//		vp->setValue (mywchar);
	//		vp->addParameter(L"HOME",NULL);
	//		//vp->addParameter(L"TYPE",L"HOME");
	//		//mySetEncoding(vp,enchset.homeaddressEn);
	//		pMyVcard->addProperty (vp);
	//		delete vp;
	//		vp=0;
	//	}
	//	else
	//		return ALLO_FAIL;
	//}
	AddADRtoVObject(0, pMyVcard, trPbItem.homeaddress);

	

	//公司　部门
	if(trPbItem.company[0]!='\0'||trPbItem.departments [0]!='\0')
	{
		pVProperty = new VProperty(L"ORG");
		if(pVProperty != NULL)
		{
			// 在性质中加入公司
			if(trPbItem.company[0]!='\0')
			{
				memset(wchTemp, 0, 500);
				c2w(wchTemp, 500, trPbItem.company);
				pVProperty->setValue (wchTemp);
			}
			else
			{
				pVProperty->setValue(L"");
			}

			// 在性质中插入部门
			if(trPbItem.departments [0]!='\0')
			{
				memset(wchTemp, 0, 500);
				c2w(wchTemp, 500, trPbItem.departments);
				pVProperty->setValue (wchTemp);
			}

			// 添加
			pMyVcard->addProperty (pVProperty);
			delete pVProperty;
			pVProperty = NULL;
		}
		else
		{
			if (pMyVcard)
			{
				delete pMyVcard;
				pMyVcard = NULL;
			}
			return ALLO_FAIL;
		}
	}

	//生日
	if(trPbItem.birthday[0]!='\0')
	{
		pVProperty = new VProperty(L"BDAY");
		if(pVProperty != NULL)
		{
			memset(wchTemp, 0, 500);
			c2w(wchTemp, 500, trPbItem.birthday);
			pVProperty->setValue (wchTemp);

			// 添加
			pMyVcard->addProperty (pVProperty);
			delete pVProperty;
			pVProperty = NULL;
		}
		else
		{
			if (pMyVcard)
			{
				delete pMyVcard;
				pMyVcard = NULL;
			}
			return ALLO_FAIL;
		}
	}

	// 职务 title
	if(trPbItem.duties[0] !=  '\0')
	{
		pVProperty = new VProperty(L"TITLE");
		if(pVProperty != NULL)
		{
			memset(wchTemp, 0, 500);
			c2w(wchTemp,500,trPbItem.duties);
			pVProperty->setValue (wchTemp);

			// 添加
			pMyVcard->addProperty (pVProperty);
			delete pVProperty;
			pVProperty = NULL;
		}
		else
		{
			if (pMyVcard)
			{
				delete pMyVcard;
				pMyVcard = NULL;
			}
			return ALLO_FAIL;
		}
	}

	// 组ID集
	if(trPbItem.GroupIDs[0] !=  '\0')
	{
		pVProperty = new VProperty(L"GROUP");
		if(pVProperty != NULL)
		{
			//循环添加组
			memset(wchTemp, 0, 500);
			c2w(wchTemp, 500, trPbItem.GroupIDs);

			wstring wstrGroupID;
			wstring wstrTemp(wchTemp);
			wstring::size_type pos = wstrTemp.find(L";");

			while (pos != wstring::npos)
			{
				wstrGroupID = wstrTemp.substr(0, pos);
				wstrTemp = wstrTemp.substr(pos+1);

				if (!wstrGroupID.empty())
				{
					pVProperty->setValue(wstrGroupID.c_str());
				}

				pos = wstrTemp.find(L";");
			}

			if (wstrTemp.length() != 0)	//没有以“;”结尾
			{
				pVProperty->setValue(wstrTemp.c_str());
			}

			// 添加
			pMyVcard->addProperty (pVProperty);
			delete pVProperty;
			pVProperty = NULL;
		}
		else
		{
			if (pMyVcard)
			{
				delete pMyVcard;
				pMyVcard = NULL;
			}
			return ALLO_FAIL;
		}
	}

	// 插入最近修改的时间
	pVProperty = new VProperty(L"REV");
	if(pVProperty != NULL)
	{
		char chTime[22];
		memset(chTime, 0, 22);
		gettime(chTime);
		memset(wchTemp, 0, 500);
		c2w(wchTemp, 500, chTime);
		pVProperty->setValue (wchTemp);

		// 添加
		pMyVcard->addProperty(pVProperty);
		delete pVProperty;
		pVProperty = NULL;
	}
	else
	{
		if (pMyVcard)
		{
			delete pMyVcard;
			pMyVcard = NULL;
		}
		return ALLO_FAIL;
	}

	//
	pVProperty = new VProperty(L"END", L"VCARD");
	if(pVProperty != NULL)
	{
		// 添加
		pMyVcard->addProperty (pVProperty);
		delete pVProperty;
		pVProperty = NULL;
	}

	//
	WCHAR* wchar1=pMyVcard->toString();
	myvcard21str.empty ();
	myvcard21str+=wchar1;
	if (wchar1)
	{
		delete[] wchar1;
		wchar1 = NULL;
	}
	//delete wchar1;//这是上面那个函数要求的

	if (pMyVcard)
	{
		delete pMyVcard;
		pMyVcard = NULL;
	}
	return 0;
}
 


int ConverTrpbItemToVcard21Str(const sContactInfo& trPbItem, wstring & myvcard21str, bool bIsWriteVersion)
{

	return innerConvertsContactInfotoVcard21(trPbItem, myvcard21str, bIsWriteVersion);
}


/*******************************************************************************************************************************
* 将sContactInfo格式的数据转换成VCard2.1格式，并存存到指定的文件中。
********************************************************************************************************************************/
int ConvertsContactInfotoVcard21andWriteToFile(const sContactInfo& trPbItem, WCHAR* pwchPath)
{
	// 生成数据流
	wstring str=L"\0";
	int rv = innerConvertsContactInfotoVcard21(trPbItem, str, true);
	if (rv != 0)
	{
		return -1;
	}

/*	// 写入
	FILE* fpFile = NULL;

	// to Utf-8 path
	int nLen = WideCharToMultiByte( CP_ACP, 0, pwchPath, -1, 0, 0, 0, 0 );
	char* pBuffer8Path = new char[nLen+1];
	WideCharToMultiByte( CP_ACP, 0, pwchPath, -1, pBuffer8Path, nLen, 0, 0 );
	pBuffer8Path[nLen] = '\0';

	// 打开文件
	fpFile = fopen(pBuffer8Path, "wb");
	if ( fpFile == NULL )
	{
		if (pBuffer8Path)
		{
			delete[] pBuffer8Path;
			pBuffer8Path = NULL;
		}
		return FALSE;
	}

	// to Utf-8
	nLen = WideCharToMultiByte( CP_UTF8, 0, str.c_str(), -1, 0, 0, 0, 0 );
	char* pBuffer8 = new char[nLen+1];
	WideCharToMultiByte( CP_UTF8, 0, str.c_str(), -1, pBuffer8, nLen, 0, 0 );
	pBuffer8[nLen] = '\0';

	//写入
	fwrite(pBuffer8, nLen, 1, fpFile);
	fclose(fpFile);

	//
	if (pBuffer8Path)
	{
		delete[] pBuffer8Path;
		pBuffer8Path = NULL;
	}*/


	// 写入文件
	wofstream fout;//=ofstream(L"d:\my.txt",wios::app);
	fout.open (pwchPath, ios_base::binary );
	const wchar_t * pch = str.c_str ();
	fout<<str;
	return 0;
}

/*******************************************************************************************************************************
* 将数组中sContactInfo格式的数据转换成VCard2.1格式，并存存到指定的文件中。
********************************************************************************************************************************/
int ConvertsContactInfotoVcard21andWriteToOneFile(const vector< sContactInfo> &m_PbContactsMgr, WCHAR* path)
{
	wstring str=L"\0";
	wofstream fout;//=ofstream(L"d:\my.txt",wios::app);
	fout.open (path);
	fout<<L"BEGIN:VCARD\nVERSION:2.1\n";
	int num=m_PbContactsMgr.size();
	for(int i=0;i<num;i++)
	{
		int j=innerConvertsContactInfotoVcard21(m_PbContactsMgr[i],str,false);
		if (j!=0)
			return j;
		const wchar_t * pch=str.c_str ();
		fout<<str<<L"\n";
		str.clear();
	}

	fout<<L"END:VCARD";
	return 0;
}

/*******************************************************************************************************************************
* 将sContactInfo格式的数据转换成VCard3.0格式，并存存到指定的文件中。
********************************************************************************************************************************/
int ConvertsContactInfotoVcard30andWriteToFile(const sContactInfo& trPbItem,WCHAR* path)
{
	wstring str=L"\0";
	ConvertsContactInfotoVcard30(trPbItem, str);
	wofstream fout;//=ofstream(L"d:\my.txt",wios::app);
	fout.open (path);
	const wchar_t * pch=str.c_str ();
	fout<<str;
	return 1;
}

int innerConvertsContactInfotoVcard30(const sContactInfo& pbitem,wstring& myvcard30str,bool b)
{
	myvcard30str.empty();
	VObject* myVcard=VObjectFactory::createInstance(L"VCARD",L"3.0");
	if (myVcard==0)
		return FAILNEW_VCARDOBJECT;

	VProperty* vp=0;//c2w(wchar_t *pwstr,size_t len,const char *str)
	wchar_t mywchar[200];

	vp = new VProperty(L"BEGIN", L"VCARD");//为何要这样写，可以参看WinContact::toString() 函数，在vocl项目中。
	if(vp!=0)
	{
		myVcard->addProperty(vp);
		delete vp;
	}

	if(b==true)
	{
		vp=0;
		vp = new VProperty(L"VERSION", L"3.0");
		if(vp!=0)
		{
			myVcard->addProperty(vp);
			delete vp;
		}
	}
	vp=0;

	if(pbitem.name[0]!='\0')//名字
	{
		vp=new VProperty(L"FN");
		if(vp!=0)
		{
			mywchar[0]='\0';mywchar[1]='\0';
			c2w(mywchar,200,pbitem.name);
			vp->setValue (mywchar);
			myVcard->addProperty (vp);
	WCHAR* pnew=vp->toString(L"3.0");
	WCHAR* p;
	p=vp->getValue();
	delete pnew;
			delete vp;
		}
		else
			return ALLO_FAIL;
	}
	
	//TEL
	AddTELToVObject(1,myVcard,pbitem.mobilenumber);
	AddTELToVObject(2,myVcard,pbitem.mobilehome);
	AddTELToVObject(3,myVcard,pbitem.mobilework);
	AddTELToVObject(4,myVcard,pbitem.phonenumber);
	AddTELToVObject(5,myVcard,pbitem.phonehome);
	AddTELToVObject(6,myVcard,pbitem.phonework);
	AddTELToVObject(7,myVcard,pbitem.fax);

	if(pbitem.email[0]!='\0')//邮箱
	{
		vp=new VProperty(L"EMAIL");
		if(vp!=0)
		{
			mywchar[0]='\0';mywchar[1]='\0';
			c2w(mywchar,200,pbitem.email);
			vp->setValue (mywchar);
			//mySetEncoding(vp,enchset.emailEn);
			myVcard->addProperty (vp);
			delete vp;
		}
		else
			return ALLO_FAIL;
	}

	AddADRtoVObject(0,myVcard,pbitem.homeaddress);//加入家庭地址

	if(pbitem.company[0]!='\0'||pbitem.departments [0]!='\0')//公司　部门
	{
		vp=new VProperty(L"ORG");
		if(vp!=0)
		{
			if(pbitem.company[0]!='\0')//在性质中加入公司
			{
				mywchar[0]='\0';mywchar[1]='\0';
				c2w(mywchar,200,pbitem.company);
				vp->setValue (mywchar);
				//mySetEncoding(vp,enchset.companyEn);
			}
			else
				vp->setValue(L"");
			if(pbitem.departments [0]!='\0')//在性质中插入部门
			{
				mywchar[0]='\0';mywchar[1]='\0';
				c2w(mywchar,200,pbitem.departments);
				vp->setValue (mywchar);
				//mySetEncoding(vp,enchset.companyEn);
			}
			myVcard->addProperty (vp);
			delete vp;
			vp=0;
		}
		else
			return ALLO_FAIL;
	}

	if(pbitem.birthday[0]!='\0')//生日
	{
		vp=new VProperty(L"BDAY");
		if(vp!=0)
		{
			mywchar[0]='\0';mywchar[1]='\0';
			c2w(mywchar,200,pbitem.birthday);
			vp->setValue (mywchar);
			//mySetEncoding(vp,enchset.birthdayEn);
			myVcard->addProperty (vp);
			delete vp;
			vp=0;
		}
		else
			return ALLO_FAIL;
	}

	if(pbitem.duties[0]!='\0')//职务 title
	{
		vp=new VProperty(L"TITLE");
		if(vp!=0)
		{
			mywchar[0]='\0';mywchar[1]='\0';
			c2w(mywchar,200,pbitem.duties);
			vp->setValue (mywchar);
			//mySetEncoding(vp,enchset.birthdayEn);
			myVcard->addProperty (vp);
			delete vp;
			vp=0;
		}
		else
			return ALLO_FAIL;
	}


	char ch[20];//插入最近修改的时间
	ch[0]='\0';
	gettime(ch);
	mywchar[0]='\0';mywchar[1]='\0';
	c2w(mywchar,200,ch);
	//vp->setValue (mywchar);
	vp= new VProperty(L"REV", mywchar);
	if(vp!=0)
	{
		myVcard->addProperty(vp);
		delete vp;
		vp=0;
	}
	
	vp = new VProperty(L"END", L"VCARD");
	if(vp!=0)
	{
		myVcard->addProperty(vp);
		delete vp;
		vp=0;
	}

	WCHAR* tempstr=myVcard->toString();
	myvcard30str.empty();
	myvcard30str=tempstr;
	delete tempstr;
	return 1;
}

/*******************************************************************************************************************************
* 将sContactInfo格式的数据转换成VCard2.1格式的字符串。
********************************************************************************************************************************/
int ConvertsContactInfotoVcard30(const sContactInfo& pbitem,wstring& myvcard30str)
{
	return innerConvertsContactInfotoVcard30(pbitem,myvcard30str,false);
}

/*******************************************************************************************************************************
* 将数组中sContactInfo格式的数据转换成VCard3.0格式，并存存到指定的文件中。
********************************************************************************************************************************/
int ConvertsContactInfotoVcard30andWriteToOneFile(const sContactInfo pbitem[],WCHAR* path,int num)
{
	wstring str=L"\0";
	wofstream fout;//=ofstream(L"d:\my.txt",wios::app);
	fout.open (path);
	fout<<L"BEGIN:VCARD\nVERSION:2.1\n";

	for(int i=0;i<num;i++)
	{
		int j=innerConvertsContactInfotoVcard30(pbitem[i],str,false);
		if (j!=1)
			return j;
		const wchar_t * pch=str.c_str ();
		fout<<str<<L"\n";
		str.clear();
	}

	fout<<L"END:VCARD";
	return 1;
}

//UTF8编码到Unicode转换
void unicodeToUTF8(const wstring &src, string& result)
{
	int n = WideCharToMultiByte( CP_UTF8, 0, src.c_str(), -1, 0, 0, 0, 0 );
	 result.resize(n);
	::WideCharToMultiByte( CP_UTF8, 0, src.c_str(), -1, (char*)result.c_str(), result.length(), 0, 0 );
}

//将utf8编码转换成Unicode
WCHAR des[300];
wchar_t* ConvertUtf8ToUnicode(char* putf8)
{
	des[0]='\0';
	MultiByteToWideChar(CP_UTF8,0,putf8,-1,des,300);
	return des;
}

wchar_t* ConvertUnicodeFromUtf8(char *utf8)
{
	DWORD wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, utf8, -1, NULL, 0);//CP_UTF8
	wchar_t* unicode = new wchar_t[wcsLen + 1];
	::MultiByteToWideChar(CP_UTF8, NULL, utf8, -1, unicode, wcsLen);//CP_UTF8
	unicode[wcsLen]=0;
	return unicode;
}

//这个函数专用于当编码类型为base64（一般在vcard3.0中）时，将每一个性质的值加到里面
void addvaluetoprop(VProperty* vp,WCHAR* wch)
{
	char ch[1500];ch[0]='\0';char temp[100];temp[0]='\0';
	size_t len1=wcslen(wch);
	int nbytes = WideCharToMultiByte( 0, 0,wch,len1,   NULL, 0,  NULL,   NULL ); 
	w2c(ch,wch,1500);//
	ch[nbytes]='\0';
	int end=0,i=0,ind=0,j=0;//ind用于标志是第几个性质值
	for(;ch[i]!='\0';i++,j++)
	{
		if(ch[i]==';')
		{
			temp[j]='\0';j=-1;//退出循环后就会加1 这样才是从0开始拷贝
			end=i;
			//将temp加到性质中去
			WCHAR my1[512];my1[0]='\0';my1[1]='\0';
			c2w(my1,512,temp);
			if(vp!=0)
				vp->setValue (my1);
		}
		else
			temp[j]=ch[i];
	}
	temp[j]='\0';//处理最后一个性质值
	//将temp加到性质中去
	WCHAR my1[512];my1[0]='\0';my1[1]='\0';
	c2w(my1,512,temp);
	if(vp!=0)
		vp->setValue (my1);
}

//用于将从vcard中读出的一行性质转到vObject类的对象中去。之所以这样做(将其从字符串在中读出来，
//而后又将其放到vObject中而不是直接分析其性质),而不直接将其读出，
//是为了防止以后会加入一些难以处理的性质
//
//析取每一行，并把每一行加到一个对象中去，
void deal(VObject* myVcard,char curchar[])
{
	bool isbase64=false, isutf8=false,isqp=false; //用于标志是否是base64编码
	VProperty* vp=0;
	char my[1025];my[0]='\0';
	WCHAR my1[512];my1[0]='\0';my1[1]='\0';
	int j=0;
	bool isname=true,ispara=false,isvalue=false;
	for(int i=0;curchar[i]!='\0';i++)
	{
		if(curchar[i]!=';'&&curchar[i]!=':')
		{
			my[j]=curchar[i];
			j++;
		}
		else
		{
			if(curchar[i-1]=='\\')//为分号或冒号时，看看是否是转义字符，如果是，则i加1即可。
			{
				my[j]=curchar[i];
				j++;
			}
			else//为非转义字符，则为一个字段
			{
				if(isname==true)
				{
					isname=false;	
					if(curchar[i]==':')//如果为冒号，则开始进行属性值分析。
					{
						ispara=false;isvalue=true;
					}
					else
						ispara=true;//如果不是冒号，则下一个为参数
					my[j]='\0';my[j+1]=='\0';j=0;
					for(int i=0;i<j;++i) 
					{ 
						if(my[i]>='a'&&my[i]<='z')//小写字母转成大写
							my[i] = my[i]-32;//   或者写成a[i]   =   a[i]-( 'a '- 'A '); 
					}
					c2w(my1,512,my);
					vp=new VProperty(my1);//新建一个性质。
					//vp->addParameter(L"CHARSET",L"UTF-8");

					my1[0]='\0';my1[1]='\0';
				}
				else if(ispara==true)//添加参数
				{
					if(curchar[i]==':')//如果为冒号，则开始进行属性值分析。
					{
						ispara=false;isvalue=true;
					}
					my[j]='\0';my[j+1]=='\0';

					//查找参数中是否有等号，有的话另行处理
					int jjj=0;//用于标志参数名与参数值之间的界限即等号的位置。
					char paravalue[100];//用于盛放参数的值。
					WCHAR paravalue1[100];
					paravalue[0]='\0'; paravalue[1]='\0';
					for(;jjj<j;jjj++)//分离出参数名和参数值
					{ 
						if(my[jjj]=='=')
						{
							int k=0;
							int kkk=jjj;
							jjj++;
							while(jjj<=j+1)
							{
								paravalue[k]=my[jjj];//paravalue中为参数取值，且把\0也写进去了
								jjj++;k++;
							}
							jjj=kkk;
							my[jjj]='\0';;my[jjj+1]='\0';// jjj++;//my中为参数名 paravalue[0]=my[jjj+1]
							break;
						}
						//jjj++;
					}
					if(vp!=0)//在新建了一个性质的基础上，把参数加到性质中
					{
						for(int i=0;i<j;++i) 
						{ 
							if(my[i]>='a'&&my[i]<='z')//小写字母转成大写,便于后面的处理
								my[i] = my[i]-32;//   或者写成a[i]   =   a[i]-( 'a '- 'A '); 
						}
						for(int i=0;i<j;++i) 
						{ 
							if(paravalue[i]>='a'&&paravalue[i]<='z')//小写字母转成大写
								paravalue[i] = paravalue[i]-32;//   或者写成a[i]   =   a[i]-( 'a '- 'A '); 
						}
						if(strcmp(my,"CHARSET") == 0)
						{
							if(strcmp(paravalue,"UTF-8") == 0)
								isutf8;
						}
						c2w(my1,512,my);
						c2w(paravalue1,100,paravalue);
						vp->addParameter(my1,paravalue1);
						my1[0]='\0';my1[1]='\0';
						paravalue1[0]='\0'; paravalue1[1]='\0';
					}
					j=0;
				}
				else//对性质值的处理
				{
					if(vp!=0)
					{
						my[j]='\0';my[j+1]=='\0';
						int len=1024;
						//if(isbase64==true)//不可能在这里出现
						//{
						//	char curmy[1025];curmy[0]='\0';
						//	strcpy(curmy,my);
						//	Base64Decode(curmy,j,(BYTE*)my,&len);
						//}
						char temp[1024];temp[0]='\0';
						strcpy(temp,my);
						if(isqp==true)
						{
							string des=Qp_decode(temp);//qp到char*
							des.copy(my,1024);
						}
						if(isutf8==true)
						{
							//WCHAR* wchar2=ConvertUtf8ToUnicode(my);//utf8到Unicode
// 							WCHAR* wchar2=ConvertUnicodeFromUtf8(my);//utf8到Unicode
// 							char* curp=ConvertFromAnsiToUtf8(wchar2);//转成char*
// 							my[0]='\0';
// 							strcpy(my,curp);
// 							delete curp;
						}
						j=0;
						my1[0]='\0';my1[1]='\0';
						c2w(my1,512,my);
						vp->setValue (my1);
						my1[0]='\0';my1[1]='\0';my[0]='\0';
					}
				}
			}
			if(curchar[i]==':')//如果为冒号，判断一下所用的编码类型
			{
				if(vp!=0)
				{
					bool bb=vp->containsParameter(L"CHARSET")||vp->containsParameter(L"charset");//这个参数总是取不到，郁闷
					if(bb==true)
					{
						WCHAR*pvp= vp->getParameterValue(L"CHARSET");
						if(wcscmp(pvp,L"UTF-8")==0||wcscmp(pvp,L"utf-8")==0||wcscmp(pvp,L"Utf-8")==0)
							isutf8=true;
					}
					bool b=vp->containsParameter(L"ENCODING");
					if(b==true)
					{
						WCHAR*pvp= vp->getParameterValue(L"ENCODING");
						if(wcscmp(pvp,L"QP")==0||wcscmp(pvp,L"qp")==0||wcscmp(pvp,L"QUOTED-PRINTABLE")==0||wcscmp(pvp,L"Qp")==0||wcscmp(pvp,L"quoted-printable")==0)
							isqp=true;
						if(wcscmp(pvp,L"b")==0||wcscmp(pvp,L"B")==0||wcscmp(pvp,L"BASE64")==0||wcscmp(pvp,L"BASE64")==0)
							isbase64=true;
					}
				}
			}
		}
	}
	if(vp!=0)
	{
		my[j]='\0';my[j+1]=='\0';//处理最后一个性质值。因为最后一个性质值后没有分号或冒号。
		int len=1024;
		if(isbase64==true)//转换成此种编码后，各个性质值不再以分号隔开。
		{
			char curmy[1025];curmy[0]='\0';
			strcpy(curmy,my);my[0]='\0';
			int len=b64_decode(my,curmy);
			my[len]='\0';
			WCHAR* wchar2=0;
			// 经过测试，当为base64时 ，其charset为utf8
			wchar2=ConvertUtf8ToUnicode(my);//utf8到Unicode wchar2中方的就是性质值，需要将性质分字段放在里面
			addvaluetoprop(vp,wchar2);
		}
		else
		{
			char temp[1024];temp[0]='\0';
			strcpy(temp,my);
			if(isqp==true)
			{
				string des=Qp_decode(temp);//qp到char*
				des.copy(my,1024);
			}
			if(isutf8==true)
			{
// 				WCHAR* wchar2=ConvertUtf8ToUnicode(my);//utf8到Unicode
// 				char* curp=ConvertFromAnsiToUtf8(wchar2);//转成char*
// 				my[0]='\0';
// 				strcpy(my,curp);
// 				delete curp;
			}
			j=0;
			my1[0]='\0';my1[1]='\0';
			c2w(my1,512,my);
			vp->setValue (my1);
			my1[0]='\0';my1[1]='\0';my[0]='\0';
		}
		myVcard->addProperty (vp);//将性质插到vcard对象中
		delete vp;
	}
}

/*
*下面带//的是设计这个函数的初衷，但......
* //用的是QP（可打印）编码，用getValue返回时，不会自动转换为原来的编码，故，在这里转换一下。
* //借用他的toString（）函数，这样也就免去了判断当前字符串编码类型的麻烦
* //但toString不能转换，这个函数在后面没有用到。
*
*这个函数的作用是取得指定的值
*/
void getvalue(char mych[],int ind,VProperty* vp)
{
	WCHAR* wch=vp->toString(L"3.0");
	char ch[1024];
	ch[0]='\0';mych[0]='\0';
	size_t len1=wcslen(wch);
	int bytes = WideCharToMultiByte( 0, 0,wch,len1,NULL,0,NULL,NULL ); 
	w2c(ch,wch,1024);
	ch[bytes]='\0';
	bool beginvalue=false;
	int begin=0,end=0,order=0,curend=0;//begin，end用于标志所要的值的开始结束位置，order用于标志当前所引导的是第几个变量的值
	int i;
	for(i=0;ch[i]!='\0';i++)
	{
		if(ch[i]==':')
		{
			beginvalue=true;
			if(ind==order)
				begin=i;//如果是第0个，则在此处标志出
		}
		else if(beginvalue==true&&ch[i]==';')
		{
			if(ind==order)
			{	end=i-1;	i=len1;}//用于结束循环
			else
				order++;//不是当前索引的变量，则计数后继续找
			if(ind==order+1)
				begin=i+1;
			curend=i+1;
		}
	}
	if(ind>order||ind==0)//对于最后一个域，因为结尾符不是分号，而是\0,所以要单独处理
	{
		begin=curend; end=i-1;
	}
	int aa=0;
	for(int j=begin;j<=end&&aa<1023;j++,aa++)
		mych[aa]=ch[j];
	mych[aa+1]='\0';

}

/*******************************************************************************************************************************
* 从含有vcard2.1结构数据的数组中提取出信息并存储到pbitem中
********************************************************************************************************************************/
int ConvertVcard21tosContactInfo(const wstring & myvcard21str, sContactInfo* psContactInfo)
{
	//变量 
	int nLen = myvcard21str.length();
	if(nLen == 0)
	{
		return STRING_NULL;
	}

	//
	WCHAR* pwchVcard = new WCHAR[nLen+1];
	memset(pwchVcard, 0, (nLen+1)*sizeof(WCHAR));
	myvcard21str.copy (pwchVcard, nLen);//将字符串中的东西取出来，放到数组中。

	//
	VObject* pMyVcard = VObjectFactory::createInstance(L"VCARD",L"2.1");//建立一个vcard对象,直接调用vObject的构造函数初始化会失败
	if (pMyVcard == 0)
	{
		delete[] pwchVcard;
		pwchVcard = NULL;
		return FAILNEW_VCARDOBJECT;
	}

	//------------------------------------------
	WCHAR wchCurLine[2048];//用于存储vcard中的每一行，即一个性质
	memset(wchCurLine, 0, 2048*sizeof(WCHAR));
	char chCurLine[5000];

	//
	int j = 0;
	for (int i= 0 ; i< nLen; i++)
	{
		if(pwchVcard[i] != '\n')
		{
			wchCurLine[j] = pwchVcard[i];
			j++;
		}
		else
		{
			memset(chCurLine, 0, 5000*sizeof(char));
			w2c(chCurLine, wchCurLine,5000);
			//strcpy(chCurLine,ConvertFromUnicodeToUtf8(wchCurLine));
			deal( pMyVcard, chCurLine);//将这一行性质分析，并写入到vcard对象中
			memset(wchCurLine, 0, 2048*sizeof(WCHAR));
			j=0;
		}
	}

	//到此时，所有的性质都已经放到vcard对象中了
	delete[] pwchVcard;
	pwchVcard = NULL; 


	//------------------------------------------
	VProperty* pVProperty = NULL;
	WCHAR* pwchar2 = NULL;	
	char ch[1024], temp[200],value[1500]; 
	memset(ch, 0, 1024);
	memset(temp, 0, 200);
	memset(value, 0, 1500);
 
	// 
	size_t len1=0;
	pVProperty = pMyVcard->getProperty(L"N");//获取名字
	//bool fname=false,name1=false;//标志名字字段的姓,名是否为空
	if(pVProperty!=0)
	{
		pwchar2=pVProperty->getValue(0);//姓
		if(pwchar2!=0)
		{
			char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*
			memset(value, 0, 1500);
			strcat(value,curp);
			delete[] curp;
			curp = NULL;
		}
		temp[0]='\0';
		pwchar2=0;
		pwchar2=pVProperty->getValue(1);//名
		if(pwchar2!=0)
		{
			char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*
			strcat(value,curp);
			delete[] curp; curp = NULL;
		}
		strcpy(psContactInfo->name,value);
	}
	else
	{
		pVProperty=pMyVcard->getProperty(L"FN");//如果没有N，则用这个来代替值
		if(pVProperty!=0)
		{
			pwchar2=pVProperty->getValue(0);//取得姓名
			if(pwchar2!=0)
			{//wchar_t* ConvertToUnicodeFromUtf8(const char *utf8)//要自己释放内存将char*到Unicode
				//char* ConvertFromAnsiToUtf8(wchar_t *unicode)//Unicode到char*
				char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*
				strcpy(psContactInfo->name,curp);
				delete[] curp; curp = NULL;
			}
		}
	}

	pVProperty=0;
	memset(value, 0, 1500);pwchar2=0;
	pVProperty=pMyVcard->getProperty(L"EMAIL");//获取email
	if(pVProperty!=0)
	{
		pwchar2=pVProperty->getValue(0);
		if(pwchar2!=0)
		{
			char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*
			memset(value, 0, 1500);
			strcpy(value,curp);
			delete[] curp; curp = NULL;
		}
	}
	strcpy(psContactInfo->email,value);

	pVProperty=0;
	memset(value, 0, 1500);pwchar2=0;
	pVProperty=pMyVcard->getProperty(L"ORG");//获取org
	if(pVProperty!=0)
	{
		pwchar2=pVProperty->getValue(0);//company
		if(pwchar2!=0)
		{
			char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*
			strcpy(value,curp);
			delete[] curp; curp = NULL;
		}
		strcpy(psContactInfo->company,value);

		memset(value, 0, 1500);pwchar2=0;
		pwchar2=pVProperty->getValue(1);//departments
		if(pwchar2!=0)
		{
			char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*

			strcpy(value,curp);
			delete[] curp; curp = NULL;
		}
		strcpy(psContactInfo->departments,value);
	}

	pVProperty=0;
	memset(value, 0, 1500);pwchar2=0;
	pVProperty=pMyVcard->getProperty(L"BDAY");//获取生日
	if(pVProperty!=0)
	{
		pwchar2=pVProperty->getValue(0);
		if(pwchar2!=0)
		{
			char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*
			strcpy(value,curp);
			delete[] curp; curp = NULL;
		}
	}
	strcpy(psContactInfo->birthday,value);

	pVProperty=0;
	memset(value, 0, 1500);pwchar2=0;
	pVProperty=pMyVcard->getProperty(L"TITLE");//获取职务
	if(pVProperty!=0)
	{
		pwchar2=pVProperty->getValue(0);
		if(pwchar2!=0)
		{
			char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*
			strcpy(value,curp);
			delete[] curp; curp = NULL;
		}
	}
	strcpy(psContactInfo->duties,value);

	//组
	pVProperty=0;
	memset(value, 0, 1500);pwchar2=0;
	pVProperty=pMyVcard->getProperty(L"GROUP");//获取职务
	if(pVProperty!=0)
	{
		pwchar2=pVProperty->getValue(0);
		if(pwchar2!=0)
		{
			char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*
			strcpy(value,curp);
			delete[] curp; curp = NULL;
		}
	}
	psContactInfo->nGroupID = atoi(value);
	//strcpy(psContactInfo->cGroupName,value);


	//处理电话
	bool tel=false;//用于寻找TEL:123 这一项，因为有时 其可能会有参数如voice等，参数不一定为0个
	int num=pMyVcard->propertiesCount();//得到性质条目的数目
	int numpara=0;//参数的个数;
	WCHAR* name=0;
	int equals=-1;
	for(int i=0;i<num;i++)//遍历性质，获得tel属性
	{
		name=0;
		pwchar2=0;pVProperty=0;memset(value, 0, 1500);
		pVProperty=pMyVcard->getProperty(i);//得到一个属性
		if(pVProperty!=0)
		{
			name=pVProperty->getName();
			if(name!=0)
			{
				equals=wcscmp(name,L"TEL");
				if(equals!=0)
					equals=wcscmp(name,L"tel");
				name=0;
				if(equals==0)//如果这一项是TEL
				{
					equals=-1;
					numpara=pVProperty->parameterCount();//获取参数个数
					if(numpara==0)		//-----phonenumber
					{
						pwchar2=pVProperty->getValue(0);
						if(pwchar2!=0)
						{
							char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*
							string des=Qp_decode(curp);//qp到char*
							delete[] curp; curp = NULL;
							des.copy(value,1500);
							WCHAR* pwchar2=ConvertUtf8ToUnicode(value);//utf8到Unicode
							curp=ConvertFromAnsiToUtf8(pwchar2);//Unicode到char*
							memset(value, 0, 1500);
							strcpy(value,curp);
							delete[] curp; curp = NULL;

							strcpy(psContactInfo->phonenumber,value);
							tel=true;
						}
					}
					else//参数个数>0时，就去遍历
					{
						bool hashome=false,haswork=false,hascell=false,hasfax=false;//是否有这个参数
						hashome=pVProperty->containsParameter(L"HOME");
						haswork=pVProperty->containsParameter(L"WORK");
						hascell=pVProperty->containsParameter(L"CELL");
						hasfax=pVProperty->containsParameter(L"FAX");
						if(hasfax)//-----phonehome
						{
							pwchar2=pVProperty->getValue(0);
							if(pwchar2!=0)
							{
								char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*
								memset(value, 0, 1500);
								strcpy(value,curp);
								delete[] curp; curp = NULL;

								strcpy(psContactInfo->fax,value);
							}
						}
						if(hascell==false&&hashome==true)//-----phonehome
						{
							pwchar2=pVProperty->getValue(0);
							if(pwchar2!=0)
							{
								char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*
								memset(value, 0, 1500);
								strcpy(value,curp);
								delete[] curp; curp = NULL;

								strcpy(psContactInfo->phonehome,value);
							}
						}
						else if(hascell==false&&haswork==true)//----phonework
						{
							pwchar2=pVProperty->getValue(0);
							if(pwchar2!=0)
							{
								char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*
								memset(value, 0, 1500);
								strcpy(value,curp);
								delete[] curp; curp = NULL;

								strcpy(psContactInfo->phonework,value);
							}
						}
						else if(hascell==true&&haswork==false&&hashome==false)//----mobilehome
						{
							pwchar2=pVProperty->getValue(0);
							if(pwchar2!=0)
							{
								char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*
								memset(value, 0, 1500);
								strcpy(value,curp);
								delete[] curp; curp = NULL;

								strcpy(psContactInfo->mobilenumber,value);
							}
						}
						if(hascell==true&&hashome==true)//----mobilehome为例防止有TEL;HOME;WORK;CELL的样式
						{
							pwchar2=pVProperty->getValue(0);
							if(pwchar2!=0)
							{
								char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*
								memset(value, 0, 1500);
								strcpy(value,curp);
								delete[] curp; curp = NULL;

								strcpy(psContactInfo->mobilehome,value);
							}
						}
						if(hascell==true&&haswork==true)//----mobilehome
						{
							pwchar2=pVProperty->getValue(0);
							if(pwchar2!=0)
							{
								char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*
								memset(value, 0, 1500);
								strcpy(value,curp);
								delete[] curp; curp = NULL;

								strcpy(psContactInfo->mobilework,value);
							}
						}
						if(tel==false&&hascell==false&&haswork==false&&hashome==false&&hasfax==false)//----tel
						{
							pwchar2=pVProperty->getValue(0);
							if(pwchar2!=0)
							{
								char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*
								memset(value, 0, 1500);
								strcpy(value,curp);
								delete[] curp; curp = NULL;

								strcpy(psContactInfo->phonenumber,value);
							}
						}
					}
				}
			}
		}
	}

	//获取家庭住址
	bool hashomeaddr=false;
	num=0;	name=0;	equals=-1;
	num=pMyVcard->propertiesCount();//得到性质条目的数目
	for(int i=0;i<num;i++)//遍历性质，获得LABEL属性
	{
		numpara=0;	name=0;	pwchar2=0;	pVProperty=0;	memset(value, 0, 1500);
		pVProperty=pMyVcard->getProperty(i);//得到一个属性
		if(pVProperty!=0)
		{
			name=pVProperty->getName();
			if(name!=0)
			{
				equals=wcscmp(name,L"LABEL");
				if(equals==0)//如果这一项是LABEL
				{
					equals=-1;
					numpara=pVProperty->parameterCount();//获取参数个数
					if(numpara>0)
					{
						bool hashome=false;
						hashome=pVProperty->containsParameter(L"HOME");
						if(hashome==true)
						{
							pwchar2=pVProperty->getValue(0);
							if(pwchar2!=0)
							{
								char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*
								memset(value, 0, 1500);
								strcpy(value,curp);
								delete[] curp; curp = NULL;
								strcpy(psContactInfo->homeaddress,value);
								hashomeaddr=true;
								i=num;//停止循环
								//hashomeaddr=true;
							}
						}
					}
				}
			}
		}
	}
	
	if(hashomeaddr==false)
	{
		num=0;	name=0;	equals=-1;
		num=pMyVcard->propertiesCount();//得到性质条目的数目
		for(int i=0;i<num;i++)//遍历性质，获得ADR属性
		{
			numpara=0;	name=0;	pwchar2=0;	pVProperty=0;	memset(value, 0, 1500);
			pVProperty=pMyVcard->getProperty(i);//得到一个属性
			if(pVProperty!=0)
			{
				name=pVProperty->getName();
				if(name!=0)
				{
					equals=wcscmp(name,L"ADR");
					if(equals==0)//如果这一项是ADR
					{
						equals=-1;
						numpara=pVProperty->parameterCount();//获取参数个数
						if(numpara>0)
						{
							bool hashome=false;
							hashome=pVProperty->containsParameter(L"HOME");
							if(hashome==true)
							{
								temp[0]='\0';
								equals=-1;
								for(int addrnum=0;addrnum<=6;addrnum++)//将性质按格式写入homeaddress中
								{
									len1=0;
									pwchar2=pVProperty->getValue(addrnum);
									if(pwchar2!=0)
									{
										char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*
										temp[0]='\0';
										strcpy(temp,curp);
										delete[] curp; curp = NULL;
										strcat(value,temp);
										temp[0]='\0';
										pwchar2=0;
									}
									strcat(value,";");
								}
								strcpy(psContactInfo->homeaddress,value);
								i=num;//停止循环
								//hashomeaddr=true;
							}
						}
					}
				}
			}
		}
		
	}
	return 1;
}
 
/*******************************************************************************************************************************
* 从含有vcard3.0结构数据的数组中提取出信息并存储到pbitem中
********************************************************************************************************************************/
int ConvertVcard30tosContactInfo(const wstring & myvcard30str,sContactInfo& pbitem)
{
//	//变量进行清空初始化
//	pbitem.birthday[0]='\0';	pbitem.company[0]='\0';		pbitem.departments[0]='\0';
//	pbitem.duties[0]='\0';	pbitem.email[0]='\0';	pbitem.fax[0]='\0';	pbitem.homeaddress[0]='\0';	
//	pbitem.mobilehome[0]='\0';	pbitem.mobilenumber[0]='\0';	pbitem.mobilework[0]='\0';
//	pbitem.name[0]='\0';	pbitem.phonehome[0]='\0';	pbitem.phonenumber[0]='\0';	pbitem.phonework[0]='\0';
//
//	int len=myvcard30str.length();
//	if(len==0) return STRING_NULL;
//	WCHAR* pvcardwchar=new WCHAR[len+1];
//	myvcard30str.copy (pvcardwchar,len);//将字符串中的东西取出来，放到数组中。
//
//	VObject* myVcard=VObjectFactory::createInstance(L"VCARD",L"3.0");//建立一个vcard对象,直接调用vObject的构造函数初始化会失败
//	if (myVcard==0)
//		return FAILNEW_VCARDOBJECT;
//
//	WCHAR curchar[2048];//用于存储vcard中的每一行，即一个性质
//	curchar[0]='\0';curchar[1]='\0';//双字节，所以这样初始化，保险起见嘛
//	int j=0;
//	for (int i=0;i<len;i++)
//	{
//		if(pvcardwchar[i]!='\n')
//		{
//			curchar[j]=pvcardwchar[i];
//			j++;
//		}
//		else
//		{
//			curchar[j]='\0';curchar[j+1]='\0';//从里面析取出每一行。
//			char* curp=ConvertFromAnsiToUtf8(curchar);//转成char*
//			deal( myVcard,curp);//将这一行性质分析，并写入到vcard对象中
//			curchar[0]='\0';curchar[1]='\0';//字符串清零
//			j=0;
//		}
//	}
//	delete pvcardwchar;//到此时，所有的性质都已经放到vcard对象中了。
//
//WCHAR* chh=myVcard->toString();
//delete chh;
//
//	VProperty* vp=0;WCHAR* wchar2;	char ch[1024];ch[0]='\0';
//	char temp[200],value[1500];//对于值为多字段的，则先暂存在temp中，而后在将其放到value中
//	
//	temp[0]='\0';value[0]='\0';wchar2=0;
//	size_t len1=0;
//	vp=myVcard->getProperty(L"N");//获取名字
//	//bool fname=false,name1=false;//标志名字字段的姓,名是否为空
//	if(vp!=0)
//	{
//		wchar2=vp->getValue(0);//姓
//		if(wchar2!=0)
//		{
//			char* curp=ConvertFromAnsiToUtf8(wchar2);//转成char*
//			value[0]='\0';
//			strcat(value,curp);
//			delete curp;curp=0;
//			//fname=true;
//		}
//		temp[0]='\0';
//		wchar2=0;
//		wchar2=vp->getValue(1);//名
//		if(wchar2!=0)
//		{
//			char* curp=ConvertFromAnsiToUtf8(wchar2);//转成char*
//			strcat(value,curp);
//			delete curp;curp=0;
//		}
//		strcpy(pbitem.name,value);
//	}
//	else
//	{
//		vp=myVcard->getProperty(L"FN");//如果没有N，则用这个来代替值
//		if(vp!=0)
//		{
//			wchar2=vp->getValue(0);//取得姓名
//			if(wchar2!=0)
//			{//wchar_t* ConvertToUnicodeFromUtf8(const char *utf8)//要自己释放内存将char*到Unicode
//				//char* ConvertFromAnsiToUtf8(wchar_t *unicode)//Unicode到char*
//				char* curp=ConvertFromAnsiToUtf8(wchar2);//转成char*
//				strcpy(pbitem.name,curp);
//				delete curp;curp=0;
//			}
//		}
//	}
//
//	vp=0;
//	value[0]='\0';wchar2=0;
//	vp=myVcard->getProperty(L"EMAIL");//获取email
//	if(vp!=0)
//	{
//		wchar2=vp->getValue(0);
//		if(wchar2!=0)
//		{
//			char* curp=ConvertFromAnsiToUtf8(wchar2);//转成char*
//			value[0]='\0';
//			strcpy(value,curp);
//			delete curp;curp=0;
//		}
//	}
//	strcpy(pbitem.email,value);
//
//	vp=0;
//	value[0]='\0';wchar2=0;
//	vp=myVcard->getProperty(L"ORG");//获取org
//	if(vp!=0)
//	{
//		wchar2=vp->getValue(0);//company
//		if(wchar2!=0)
//		{
//			char* curp=ConvertFromAnsiToUtf8(wchar2);//转成char*
//			value[0]='\0';
//			strcpy(value,curp);
//			delete curp;curp=0;
//		}
//		strcpy(pbitem.company,value);
//		
//		value[0]='\0';wchar2=0;
//		wchar2=vp->getValue(1);//departments
//		if(wchar2!=0)
//		{
//			char* curp=ConvertFromAnsiToUtf8(wchar2);//转成char*
//			value[0]='\0';
//			strcpy(value,curp);
//			delete curp;curp=0;
//		}
//		strcpy(pbitem.departments,value);
//	}
//
//	vp=0;
//	value[0]='\0';wchar2=0;
//	vp=myVcard->getProperty(L"BDAY");//获取生日
//	if(vp!=0)
//	{
//		wchar2=vp->getValue(0);
//		if(wchar2!=0)
//		{
//			char* curp=ConvertFromAnsiToUtf8(wchar2);//转成char*
//			value[0]='\0';
//			strcpy(value,curp);
//			delete curp;curp=0;
//		}
//	}
//	strcpy(pbitem.birthday,value);
//
//	vp=0;
//	value[0]='\0';wchar2=0;
//	vp=myVcard->getProperty(L"TITLE");//获取职务
//	if(vp!=0)
//	{
//		wchar2=vp->getValue(0);
//		if(wchar2!=0)
//		{
//			char* curp=ConvertFromAnsiToUtf8(wchar2);//转成char*
//			value[0]='\0';
//			strcpy(value,curp);
//			delete curp;curp=0;
//		}
//	}
//	strcpy(pbitem.duties,value);
//
//	//处理电话
//	bool tel=false;//用于寻找TEL:123 这一项，因为有时 其可能会有参数如voice等，参数不一定为0个
//	int num=myVcard->propertiesCount();//得到性质条目的数目
//	int numpara=0;//参数的个数;
//	WCHAR* name=0;
//	int equals=-1;
//	for(int i=0;i<num;i++)//遍历性质，获得tel属性
//	{
//		name=0;
//		wchar2=0;vp=0;value[0]='\0';
//		vp=myVcard->getProperty(i);//得到一个属性
//		if(vp!=0)
//		{
//			name=vp->getName();
//			if(name!=0)
//			{
//				equals=wcscmp(name,L"TEL");
//				if(equals!=0)
//					equals=wcscmp(name,L"tel");
//				name=0;
//				if(equals==0)//如果这一项是TEL
//				{
//					equals=-1;
//					numpara=vp->parameterCount();//获取参数个数
//					if(numpara==0)		//-----phonenumber
//					{
//						wchar2=vp->getValue(0);
//						if(wchar2!=0)
//						{
//							char* curp=ConvertFromAnsiToUtf8(wchar2);//转成char*
//							value[0]='\0';
//							strcpy(value,curp);
//							delete curp;curp=0;
//
//							strcpy(pbitem.phonenumber,value);
//							tel=true;
//						}
//					}
//					else//参数个数>0时，就去遍历
//					{
//						bool hashome=false,haswork=false,hascell=false,hasfax=false;//是否有这个参数
//						hashome=vp->containsParameter(L"HOME");
//						haswork=vp->containsParameter(L"WORK");
//						hascell=vp->containsParameter(L"CELL");
//						hasfax=vp->containsParameter(L"FAX");
//						if(hasfax)//-----phonehome
//						{
//							wchar2=vp->getValue(0);
//							if(wchar2!=0)
//							{
//								char* curp=ConvertFromAnsiToUtf8(wchar2);//转成char*
//								value[0]='\0';
//								strcpy(value,curp);
//								delete curp;curp=0;
//
//								strcpy(pbitem.fax,value);
//							}
//						}
//						if(hascell==false&&hashome==true)//-----phonehome
//						{
//							wchar2=vp->getValue(0);
//							if(wchar2!=0)
//							{
//								char* curp=ConvertFromAnsiToUtf8(wchar2);//转成char*
//								value[0]='\0';
//								strcpy(value,curp);
//								delete curp;curp=0;
//
//								strcpy(pbitem.phonehome,value);
//							}
//						}
//						else if(hascell==false&&haswork==true)//----phonework
//						{
//							wchar2=vp->getValue(0);
//							if(wchar2!=0)
//							{
//								char* curp=ConvertFromAnsiToUtf8(wchar2);//转成char*
//								value[0]='\0';
//								strcpy(value,curp);
//								delete curp;curp=0;
//
//								strcpy(pbitem.phonework,value);
//							}
//						}
//						else if(hascell==true&&haswork==false&&hashome==false)//----mobilehome
//						{
//							wchar2=vp->getValue(0);
//							if(wchar2!=0)
//							{
//								char* curp=ConvertFromAnsiToUtf8(wchar2);//转成char*
//								value[0]='\0';
//								strcpy(value,curp);
//								delete curp;curp=0;
//
//								strcpy(pbitem.mobilenumber,value);
//							}
//						}
//						if(hascell==true&&hashome==true)//----mobilehome为例防止有TEL;HOME;WORK;CELL的样式
//						{
//							wchar2=vp->getValue(0);
//							if(wchar2!=0)
//							{
//								char* curp=ConvertFromAnsiToUtf8(wchar2);//转成char*
//								value[0]='\0';
//								strcpy(value,curp);
//								delete curp;curp=0;
//
//								strcpy(pbitem.mobilehome,value);
//							}
//						}
//						if(hascell==true&&haswork==true)//----mobilehome
//						{
//							wchar2=vp->getValue(0);
//							if(wchar2!=0)
//							{
//								char* curp=ConvertFromAnsiToUtf8(wchar2);//转成char*
//								value[0]='\0';
//								strcpy(value,curp);
//								delete curp;curp=0;
//
//								strcpy(pbitem.mobilework,value);
//							}
//						}
//						if(tel==false&&hascell==false&&haswork==false&&hashome==false&&hasfax==false)//----tel
//						{
//							wchar2=vp->getValue(0);
//							if(wchar2!=0)
//							{
//								char* curp=ConvertFromAnsiToUtf8(wchar2);//转成char*
//								value[0]='\0';
//								strcpy(value,curp);
//								delete curp;curp=0;
//
//								strcpy(pbitem.phonenumber,value);
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//
//	//获取家庭住址
//	num=0;	name=0;	equals=-1;
//	num=myVcard->propertiesCount();//得到性质条目的数目
//	bool hashomeaddr=false;
//	for(int i=0;i<num;i++)//遍历性质，获得ADR属性
//	{
//		numpara=0;	name=0;	wchar2=0;	vp=0;	value[0]='\0';
//		vp=myVcard->getProperty(i);//得到一个属性
//		if(vp!=0)
//		{
//			name=vp->getName();
//			if(name!=0)
//			{
//				equals=wcscmp(name,L"ADR");
//				if(equals==0)//如果这一项是ADR
//				{
//					equals=-1;
//					numpara=vp->parameterCount();//获取参数个数
//					if(numpara>0)
//					{
//						bool hashome=false;
//						hashome=vp->containsParameter(L"HOME");
//						if(hashome==true)
//						{
//							temp[0]='\0';
//							equals=-1;
//							for(int addrnum=0;addrnum<=6;addrnum++)//将性质按格式写入homeaddress中
//							{
//								len1=0;
//								wchar2=vp->getValue(addrnum);
//								if(wchar2!=0)
//								{
//									char* curp=ConvertFromAnsiToUtf8(wchar2);//转成char*
//									temp[0]='\0';
//									strcpy(temp,curp);
//									delete curp;curp=0;
//
//									strcat(value,temp);
//									temp[0]='\0';
//									wchar2=0;
//								}
//								strcat(value,";");
//							}
//							strcpy(pbitem.homeaddress,value);
//							i=num;//停止循环
//							hashomeaddr=true;
//						}
//					}
//				}
//			}
//		}
//	}
//	if(hashomeaddr==false)
//	{
//		num=0;	name=0;	equals=-1;
//		num=myVcard->propertiesCount();//得到性质条目的数目
//		for(int i=0;i<num;i++)//遍历性质，获得LABEL属性
//		{
//			numpara=0;	name=0;	wchar2=0;	vp=0;	value[0]='\0';
//			vp=myVcard->getProperty(i);//得到一个属性
//			if(vp!=0)
//			{
//				name=vp->getName();
//				if(name!=0)
//				{
//					equals=wcscmp(name,L"LABEL");
//					if(equals==0)//如果这一项是LABEL
//					{
//						equals=-1;
//						numpara=vp->parameterCount();//获取参数个数
//						if(numpara>0)
//						{
//							bool hashome=false;
//							hashome=vp->containsParameter(L"HOME");
//							if(hashome==true)
//							{
//								wchar2=vp->getValue(0);
//								if(wchar2!=0)
//								{
//									char* curp=ConvertFromAnsiToUtf8(wchar2);//转成char*
//									value[0]='\0';
//									strcpy(value,curp);
//									delete curp;curp=0;
//
//									strcpy(pbitem.homeaddress,value);
//									i=num;//停止循环
//									hashomeaddr=true;
//								}
//							}
//						}
//					}
//				}
//			}
//		}
//	}
	return 1;
}

/*******************************************************************************************************************************
* 从含有vcard2.1结构数据的文件中提取出信息并存储到pbitem中
********************************************************************************************************************************/
int ConvertVcard21tosContactInfoandReadFromFile(const WCHAR* path, sContactInfo* psContactInfo)
{
	//wstring str=L"\0";
	//ifstream fin;
	//fin.open (path);
	//if (!fin.is_open())
	//{ 
	//	return -1;
	//}

	//char ch[2000];
	//WCHAR wch[2000];
	//while(!fin.eof())
	//{
	//	//
	//	memset(ch, 0, 2000*sizeof(char));
	//	memset(wch, 0, 2000*sizeof(WCHAR));

	//	//
	//	fin.getline(ch,2000);
	//	size_t len=strlen(ch);
	//	if(ch[len-1]==0x0d)
	//		ch[len-1]='\0';
	//	c2w(wch, 2000, ch);
	//	str+=wch;
	//	str+=L"\n";
	//}
	//return	ConvertVcard21tosContactInfo(str, psContactInfo);
	return 0;
}

/*******************************************************************************************************************************
* 得到一个文件中含有的的联系人（vcard独立个体）的个数。
********************************************************************************************************************************/
int GetVcardObjectNum(const WCHAR* path)
{
	//int MynumofObj=0;bool hasallbegin=false,hasbegin=false,hasend=false;
	////前一个bool变量用于标志是否有两个最外面一层的beginvcard endvcard，后面的标志一个子对象的开始和结束
	//wstring str=L"\0";
	//ifstream fin;
	//fin.open (path);
	//if (!fin.is_open())
	//{ 
	//	return -1;
	//}
	//char ch[600]; 
	//WCHAR wch[600];
	//ch[0]='\0';
	//fin.getline(ch,600);
	//while(!fin.eof()&&(ch[0]=='\0'||ch[0]=='\n'))
	//	fin.getline(ch,600);
	//if(!strcmp(ch,"BEGIN:VCARD")||!strcmp(ch,"begin:vcard")||!strcmp(ch,"BEGIN:VCARD\r")||!strcmp(ch,"begin:vcard\r"))
	//	hasallbegin=true;
	//while(!fin.eof())
	//{
	//	ch[0]='\0';
	//	fin.getline(ch,600);
	//	while(!fin.eof()&&(ch[0]=='\0'||ch[0]=='\n'))
	//	fin.getline(ch,600);
	//	if(!strcmp(ch,"BEGIN:VCARD")||!strcmp(ch,"begin:vcard")||!strcmp(ch,"BEGIN:VCARD\r")||!strcmp(ch,"begin:vcard\r"))
	//		hasbegin=true;
	//	if(hasbegin==true&&(!strcmp(ch,"END:VCARD")||!strcmp(ch,"end:vcard")||!strcmp(ch,"END:VCARD\r")||!strcmp(ch,"end:vcard\r")))//即不是只有一个vcard对象的情况下
	//	{
	//		hasbegin=false;	MynumofObj++;//含有的对象数加1，并把hasbegin置为false，标志这个对象已经读完了
	//	}
	//	if(hasbegin==false&&(!strcmp(ch,"END:VCARD")||!strcmp(ch,"end:vcard")||!strcmp(ch,"END:VCARD\r")||!strcmp(ch,"end:vcard\r")))
	//		hasend=true;
	//}
	//if(MynumofObj>0)
	//	return MynumofObj;
	//if(MynumofObj==0&&hasend==true&&hasallbegin==true)
	//	return 1;
	return 0;//其他情况
}

/*******************************************************************************************************************************
* 从含有vcard2.1结构数据的文件中提取出信息并存储到pbitem数组中
********************************************************************************************************************************/
int ConvertVcard21tosContactInfoandReadFromFile(const WCHAR* path,vector< sContactInfo> &m_PbContactsMgr,int n)
{
	//wstring str=L"\0";	ifstream fin;	fin.open (path);
	//if (!fin.is_open())
	//{ 
	//	return -1;
	//}
	//char ch[600];	WCHAR wch[600],version[50];
	//bool hasbegin=true,issub=false;

	//fin.getline(ch,600);//得到第一行
	//while(!fin.eof()&&(ch[0]=='\0'||ch[0]=='\n'))
	//	fin.getline(ch,600);
	//if(!strcmp(ch,"BEGIN:VCARD")||!strcmp(ch,"begin:vcard")||!strcmp(ch,"BEGIN:VCARD\r")||!strcmp(ch,"begin:vcard\r"))
	//{
	//	c2w(wch,600,ch);	str+=wch;	str+=L"\n";
	//	hasbegin=true;
	//}
	//else
	//	return -7;//文件格式错误。
	//
	//fin.getline(ch,600);//得到第二行	
	//while(!fin.eof()&&(ch[0]=='\0'||ch[0]=='\n'))
	//	fin.getline(ch,600);
	//if(!strcmp(ch,"VERSION:2.1")||!strcmp(ch,"VERSION:3.0")||!strcmp(ch,"VERSION:2.1\r")||!strcmp(ch,"VERSION:3.0\r"))
	//{
	//	c2w(wch,600,ch);	str+=wch;	str+=L"\n";
	//	wcscpy(version,wch);
	//}
	//else
	//	return -7;//文件格式错误。

	//fin.getline(ch,600);
	//while(!fin.eof()&&(ch[0]=='\0'||ch[0]=='\n'))
	//	fin.getline(ch,600);
	//if(!strcmp(ch,"BEGIN:VCARD")||!strcmp(ch,"begin:vcard")||!strcmp(ch,"BEGIN:VCARD\r")||!strcmp(ch,"begin:vcard\r"))//寻找第三行是否为一个对象
	//	issub=true;
	//else
	//{	c2w(wch,600,ch);	str+=wch;	str+=L"\n";		}

	//int ind=0;
	//while(!fin.eof())
	//{
	//	fin.getline(ch,600);
	//	while(!fin.eof()&&(ch[0]=='\0'||ch[0]=='\n'))
	//		fin.getline(ch,600);
	//	if(hasbegin==true&&(!strcmp(ch,"END:VCARD")||!strcmp(ch,"end:vcard")||!strcmp(ch,"END:VCARD\r")||!strcmp(ch,"end:vcard\r")))
	//	{
	//		c2w(wch,600,ch);	str+=wch;	str+=L"\n";
	//		if(ind<n)
	//		{	
	//			sContactInfo pbitem=sContactInfo();
	//			ConvertVcard21tosContactInfo(str, &pbitem);
	//			m_PbContactsMgr.insert(m_PbContactsMgr.begin(),pbitem);
	//			ind++;	
	//			hasbegin=false;
	//		}
	//		else return 3;//成功返回，当数组分配的空间不足
	//		str=L"";
	//	}
	//	else if(hasbegin==true&&(!strcmp(ch,"END:VCARD")||!strcmp(ch,"end:vcard")||!strcmp(ch,"END:VCARD\r")||!strcmp(ch,"end:vcard\r")))
	//	{
	//		c2w(wch,600,ch);
	//		fin.getline(ch,600);
	//		while(!fin.eof()&&(ch[0]=='\0'||ch[0]=='\n'))
	//			fin.getline(ch,600);
	//		if(fin.eof())// 即到了文件结尾
	//			continue;//
	//		else
	//			return -7;
	//		//什么都不做，这是最外层的那个end:vcard
	//	}
	//	else if(issub==true&&(!strcmp(ch,"BEGIN:VCARD")||!strcmp(ch,"begin:vcard")||!strcmp(ch,"BEGIN:VCARD\r")||!strcmp(ch,"begin:vcard\r")))//一个对象已经结束，新的对象已经开始
	//	{	
	//		if(hasbegin==true) return -7;//文件格式错误
	//		c2w(wch,600,ch);	str+=wch;	str+=L"\n";
	//		str+=version;	str+=L"\n";	hasbegin=true;
	//	}
	//	else
	//	{	c2w(wch,600,ch);	str+=wch;	str+=L"\n";		}
	//}
	return 1;
}

/*******************************************************************************************************************************
* 从含有vcard3.0结构数据的文件中提取出信息并存储到pbitem中
********************************************************************************************************************************/
int ConvertVcard30tosContactInfoandReadFromFile(const WCHAR* path,sContactInfo& pbitem)
{
	/*wstring str=L"\0";
	ifstream fin;
	fin.open (path);
	if (!fin.is_open())
	{ 
		return -1;
	}

	char ch[600];
	WCHAR wch[600];
	while(!fin.eof())
	{
		fin.getline(ch,600);
		c2w(wch,600,ch);
		str+=wch;
		str+=L"\n";
	}
	return	ConvertVcard30tosContactInfo(str,pbitem);*/
	return 0;
}

/*******************************************************************************************************************************
* 从含有vcard2.1结构数据的文件中提取出信息并存储到pbitem数组中
********************************************************************************************************************************/
int ConvertVcard30tosContactInfoandReadFromFile(const WCHAR* path,sContactInfo pbitem[],int n)
{
	//wstring str=L"\0";	ifstream fin;	fin.open (path);
	//if (!fin.is_open())
	//{ 
	//	return -1;
	//}
	//char ch[600];	WCHAR wch[600],version[50];
	//bool hasbegin=true,issub=false;

	//fin.getline(ch,600);//得到第一行
	//while(!fin.eof()&&(ch[0]=='\0'||ch[0]=='\n'))
	//	fin.getline(ch,600);
	//if(!strcmp(ch,"BEGIN:VCARD")||!strcmp(ch,"begin:vcard")||!strcmp(ch,"BEGIN:VCARD\r")||!strcmp(ch,"begin:vcard\r"))
	//{
	//	c2w(wch,600,ch);	str+=wch;	str+=L"\n";
	//	hasbegin=true;
	//}
	//else
	//	return -7;//文件格式错误。
	//
	//fin.getline(ch,600);//得到第二行	
	//while(!fin.eof()&&(ch[0]=='\0'||ch[0]=='\n'))
	//	fin.getline(ch,600);
	//if(!strcmp(ch,"VERSION:2.1")||!strcmp(ch,"VERSION:3.0")||!strcmp(ch,"VERSION:2.1\r")||!strcmp(ch,"VERSION:3.0\r"))
	//{
	//	c2w(wch,600,ch);	str+=wch;	str+=L"\n";
	//	wcscpy(version,wch);
	//}
	//else
	//	return -7;//文件格式错误。

	//fin.getline(ch,600);
	//while(!fin.eof()&&(ch[0]=='\0'||ch[0]=='\n'))
	//	fin.getline(ch,600);
	//if(!strcmp(ch,"BEGIN:VCARD")||!strcmp(ch,"begin:vcard")||!strcmp(ch,"BEGIN:VCARD\r")||!strcmp(ch,"begin:vcard\r"))//寻找第三行是否为一个对象
	//	issub=true;
	//else
	//{	c2w(wch,600,ch);	str+=wch;	str+=L"\n";		}

	//int ind=0;
	//while(!fin.eof())
	//{
	//	fin.getline(ch,600);
	//	while(!fin.eof()&&(ch[0]=='\0'||ch[0]=='\n'))
	//		fin.getline(ch,600);
	//	if(hasbegin==true&&(!strcmp(ch,"END:VCARD")||!strcmp(ch,"end:vcard")||!strcmp(ch,"END:VCARD\r")||!strcmp(ch,"end:vcard\r")))
	//	{
	//		c2w(wch,600,ch);	str+=wch;	str+=L"\n";
	//		if(ind<n)
	//		{	ConvertVcard21tosContactInfo(str,&pbitem[ind]);	ind++;	hasbegin=false;	}
	//		else return 3;//成功返回，当数组分配的空间不足
	//		str=L"";
	//	}
	//	else if(hasbegin==true&&(!strcmp(ch,"END:VCARD")||!strcmp(ch,"end:vcard")||!strcmp(ch,"END:VCARD\r")||!strcmp(ch,"end:vcard\r")))
	//	{
	//		c2w(wch,600,ch);
	//		fin.getline(ch,600);
	//		while(!fin.eof()&&(ch[0]=='\0'||ch[0]=='\n'))
	//			fin.getline(ch,600);
	//		if(fin.eof())// 即到了文件结尾
	//			continue;//
	//		else
	//			return -7;
	//		//什么都不做，这是最外层的那个endvcard
	//	}
	//	else if(issub==true&&(!strcmp(ch,"BEGIN:VCARD")||!strcmp(ch,"begin:vcard")||!strcmp(ch,"BEGIN:VCARD\r")||!strcmp(ch,"begin:vcard\r")))//一个对象已经结束，新的对象已经开始
	//	{	
	//		if(hasbegin==true) return -7;//文件格式错误
	//		c2w(wch,600,ch);	str+=wch;	str+=L"\n";
	//		str+=version;	str+=L"\n";	hasbegin=true;
	//	}
	//	else
	//	{	c2w(wch,600,ch);	str+=wch;	str+=L"\n";		}
	//}

	return 0;
}

//用于将sContactInfo结构转化为CSV时，对个值中含有的双引号，逗号进行处理
//用于处理sContactInfo结构中各个char型数组中有逗号存在时的情况，此时将其转换成引号 逗号，如果有引号，将其转换成引号引号的形式写入文件
wchar_t* ConverCharToCsvData(wchar_t* wchSrcBuffur)
{
	////
	//if (wchSrcBuffur == NULL)
	//{
	//	return NULL;
	//}

	//// 申请控件 
	//int nLen = wcslen(wchSrcBuffur);
	//if (nLen == 0)
	//{
	//	return NULL;
	//}
	//wchar_t* pwchReBuff = new wchar_t[nLen*2];
	//memset(pwchReBuff, 0, sizeof(wchar_t)*nLen*2);

	//// 遍历
	//int nReBufferPos = 0;	
	//for(int i = 0; i < nLen; i++)
	//{
	//	// 判断
	//	if(wchSrcBuffur[i]==',')
	//	{
	//		pwchReBuff[nReBufferPos] = '"';
	//		nReBufferPos++;
	//		pwchReBuff[nReBufferPos] = ',';
	//		nReBufferPos++;
	//		pwchReBuff[nReBufferPos] = '"';
	//		nReBufferPos++;
	//	}
	//	else if(wchSrcBuffur[i]=='"')// 有引号时变成双引号
	//	{
	//		pwchReBuff[nReBufferPos] = '"';
	//		nReBufferPos++;
	//		pwchReBuff[nReBufferPos] = '"';
	//		nReBufferPos++;
	//		pwchReBuff[nReBufferPos] = '"';
	//		nReBufferPos++;
	//	}
	//	else
	//	{
	//		pwchReBuff[nReBufferPos] = wchSrcBuffur[i];
	//		nReBufferPos++;
	//	}
	//}
	// 
    //
	//return pwchReBuff;
	return NULL;
}


 
/*******************************************************************************************************************************
* 将sContactInfo结构中的数据转换成CSV结构，并放在字符串中
********************************************************************************************************************************/
int ConvertsContactInfotoCSV(const vector< sContactInfo*>* pVectorContacts, wstring& CSVstr)
{
	////
	//CSVstr.empty();
	//wchar_t wchBuffer[TR_MAX_CONTACT_ID_LENGTH];
	//wchar_t* pwchBuffer = NULL;
	//CSVstr += L"姓名,手机号码(移动),手机号码(家庭),手机号码(办公),电话号码,电话号码(家庭),电话号码(办公),私人邮箱,家庭地址,公司名称,个人生日,传真,部门,职务\n";

	//// 遍历

	//int num = pVectorContacts->size();
	//for(int i = 0;i<num; i++) 
	//{
	//	sContactInfo* psContactInfo = pVectorContacts->at(i);
	//	if (psContactInfo == NULL)
	//	{
	//		continue;
	//	}
 //

	//	// 姓名
	//	memset(wchBuffer, 0, sizeof(WCHAR)*TR_MAX_CONTACT_ID_LENGTH);
	//	c2w(wchBuffer, TR_MAX_CONTACT_ID_LENGTH, psContactInfo->name);
	//	pwchBuffer = ConverCharToCsvData(wchBuffer);
	//	if (pwchBuffer)
	//	{
	//		CSVstr.append(pwchBuffer, wcslen(pwchBuffer));
	//		delete pwchBuffer;
	//		pwchBuffer = NULL;
	//	}
	//	CSVstr.append(L",", 1);


	//	// 手机号码(移动)
	//	memset(wchBuffer, 0, sizeof(WCHAR)*TR_MAX_CONTACT_ID_LENGTH);
	//	c2w(wchBuffer, TR_MAX_CONTACT_ID_LENGTH, psContactInfo->mobilenumber);
	//	pwchBuffer = ConverCharToCsvData(wchBuffer);
	//	if (pwchBuffer)
	//	{
	//		CSVstr.append(pwchBuffer, wcslen(pwchBuffer));
	//		delete pwchBuffer;
	//		pwchBuffer = NULL;
	//	}
	//	CSVstr.append(L",", 1);

	//	// 手机号码(家庭)
	//	memset(wchBuffer, 0, sizeof(WCHAR)*TR_MAX_CONTACT_ID_LENGTH);
	//	c2w(wchBuffer, TR_MAX_CONTACT_ID_LENGTH, psContactInfo->mobilehome);
	//	pwchBuffer = ConverCharToCsvData(wchBuffer);
	//	if (pwchBuffer)
	//	{
	//		CSVstr.append(pwchBuffer, wcslen(pwchBuffer));
	//		delete pwchBuffer;
	//		pwchBuffer = NULL;
	//	}
	//	CSVstr.append(L",", 1);

	//	// 手机号码(办公)
	//	memset(wchBuffer, 0, sizeof(WCHAR)*TR_MAX_CONTACT_ID_LENGTH);
	//	c2w(wchBuffer, TR_MAX_CONTACT_ID_LENGTH, psContactInfo->mobilework);
	//	pwchBuffer = ConverCharToCsvData(wchBuffer);
	//	if (pwchBuffer)
	//	{
	//		CSVstr.append(pwchBuffer, wcslen(pwchBuffer));
	//		delete pwchBuffer;
	//		pwchBuffer = NULL;
	//	}
	//	CSVstr.append(L",", 1);

	//	// 电话号码
	//	memset(wchBuffer, 0, sizeof(WCHAR)*TR_MAX_CONTACT_ID_LENGTH);
	//	c2w(wchBuffer, TR_MAX_CONTACT_ID_LENGTH, psContactInfo->phonenumber);
	//	pwchBuffer = ConverCharToCsvData(wchBuffer);
	//	if (pwchBuffer)
	//	{
	//		CSVstr.append(pwchBuffer, wcslen(pwchBuffer));
	//		delete pwchBuffer;
	//		pwchBuffer = NULL;
	//	}
	//	CSVstr.append(L",", 1);

	//	// 电话号码(家庭)
	//	memset(wchBuffer, 0, sizeof(WCHAR)*TR_MAX_CONTACT_ID_LENGTH);
	//	c2w(wchBuffer, TR_MAX_CONTACT_ID_LENGTH, psContactInfo->phonehome);
	//	pwchBuffer = ConverCharToCsvData(wchBuffer);
	//	if (pwchBuffer)
	//	{
	//		CSVstr.append(pwchBuffer, wcslen(pwchBuffer));
	//		delete pwchBuffer;
	//		pwchBuffer = NULL;
	//	}
	//	CSVstr.append(L",", 1);

	//	// 电话号码(办公)
	//	memset(wchBuffer, 0, sizeof(WCHAR)*TR_MAX_CONTACT_ID_LENGTH);
	//	c2w(wchBuffer, TR_MAX_CONTACT_ID_LENGTH, psContactInfo->phonework);
	//	pwchBuffer = ConverCharToCsvData(wchBuffer);
	//	if (pwchBuffer)
	//	{
	//		CSVstr.append(pwchBuffer, wcslen(pwchBuffer));
	//		delete pwchBuffer;
	//		pwchBuffer = NULL;
	//	}
	//	CSVstr.append(L",", 1);
	//	// 私人邮箱
	//	memset(wchBuffer, 0, sizeof(WCHAR)*TR_MAX_CONTACT_ID_LENGTH);
	//	c2w(wchBuffer, TR_MAX_CONTACT_ID_LENGTH, psContactInfo->email);
	//	pwchBuffer = ConverCharToCsvData(wchBuffer);
	//	if (pwchBuffer)
	//	{
	//		CSVstr.append(pwchBuffer, wcslen(pwchBuffer));
	//		delete pwchBuffer;
	//		pwchBuffer = NULL;
	//	}
	//	CSVstr.append(L",", 1);

	//	// 家庭地址
	//	memset(wchBuffer, 0, sizeof(WCHAR)*TR_MAX_CONTACT_ID_LENGTH);
	//	c2w(wchBuffer, TR_MAX_CONTACT_ID_LENGTH, psContactInfo->homeaddress);
	//	pwchBuffer = ConverCharToCsvData(wchBuffer);
	//	if (pwchBuffer)
	//	{
	//		CSVstr.append(pwchBuffer, wcslen(pwchBuffer));
	//		delete pwchBuffer;
	//		pwchBuffer = NULL;
	//	}
	//	CSVstr.append(L",", 1);

	//	// 公司名称
	//	memset(wchBuffer, 0, sizeof(WCHAR)*TR_MAX_CONTACT_ID_LENGTH);
	//	c2w(wchBuffer, TR_MAX_CONTACT_ID_LENGTH, psContactInfo->company);
	//	pwchBuffer = ConverCharToCsvData(wchBuffer);
	//	if (pwchBuffer)
	//	{
	//		CSVstr.append(pwchBuffer, wcslen(pwchBuffer));
	//		delete pwchBuffer;
	//		pwchBuffer = NULL;
	//	}
	//	CSVstr.append(L",", 1);

	//	// 个人生日
	//	memset(wchBuffer, 0, sizeof(WCHAR)*TR_MAX_CONTACT_ID_LENGTH);
	//	c2w(wchBuffer, TR_MAX_CONTACT_ID_LENGTH, psContactInfo->birthday);
	//	pwchBuffer = ConverCharToCsvData(wchBuffer);
	//	if (pwchBuffer)
	//	{
	//		CSVstr.append(pwchBuffer, wcslen(pwchBuffer));
	//		delete pwchBuffer;
	//		pwchBuffer = NULL;
	//	}
	//	CSVstr.append(L",", 1);

	//	// 传真
	//	memset(wchBuffer, 0, sizeof(WCHAR)*TR_MAX_CONTACT_ID_LENGTH);
	//	c2w(wchBuffer, TR_MAX_CONTACT_ID_LENGTH, psContactInfo->fax);
	//	pwchBuffer = ConverCharToCsvData(wchBuffer);
	//	if (pwchBuffer)
	//	{
	//		CSVstr.append(pwchBuffer, wcslen(pwchBuffer));
	//		delete pwchBuffer;
	//		pwchBuffer = NULL;
	//	}
	//	CSVstr.append(L",", 1);

	//	// 部门
	//	memset(wchBuffer, 0, sizeof(WCHAR)*TR_MAX_CONTACT_ID_LENGTH);
	//	c2w(wchBuffer, TR_MAX_CONTACT_ID_LENGTH, psContactInfo->departments);
	//	pwchBuffer = ConverCharToCsvData(wchBuffer);
	//	if (pwchBuffer)
	//	{
	//		CSVstr.append(pwchBuffer, wcslen(pwchBuffer));
	//		delete pwchBuffer;
	//		pwchBuffer = NULL;
	//	}
	//	CSVstr.append(L",", 1);

	//	// 职务
	//	memset(wchBuffer, 0, sizeof(WCHAR)*TR_MAX_CONTACT_ID_LENGTH);
	//	c2w(wchBuffer, TR_MAX_CONTACT_ID_LENGTH, psContactInfo->duties);
	//	pwchBuffer = ConverCharToCsvData(wchBuffer);
	//	if (pwchBuffer)
	//	{
	//		CSVstr.append(pwchBuffer, wcslen(pwchBuffer));
	//		delete pwchBuffer;
	//		pwchBuffer = NULL;
	//	}
	//	CSVstr.append(L",", 1);

	//	// 最后分行
	//	CSVstr+=L"\n";
	//}
	//return num;
     
    return 0;
}
 
//
void ConverCsvToCharData(char* chDesBuffur, char* chSrcBuffur)
{
	////
	//if (chSrcBuffur == NULL || chDesBuffur == NULL)
	//{
	//	return;
	//}

	//// 申请控件 
	//int nLen = strlen(chSrcBuffur);
	//if (nLen == 0)
	//{
	//	return;
	//}

	//// 遍历
	//int nReBufferPos = 0;	
	//for(int i = 0; i < nLen; i++)
	//{
	//	// 判断
	//	if(chSrcBuffur[i]=='"')
	//	{
	//		i++;
	//		chDesBuffur[nReBufferPos] = chSrcBuffur[i];
	//		nReBufferPos++;
	//		i++;
	//	}
	//	else
	//	{
	//		chDesBuffur[nReBufferPos] = chSrcBuffur[i];
	//		nReBufferPos++;
	//	}
	//}

	////
	//return;
}


/*******************************************************************************************************************************
* 从含有CSV结构数据的数组中提取出信息并存储到pbitem中
********************************************************************************************************************************/
int ConvertCSVtosContactInfo(char* pchLineText, sContactInfo* pContactInfo)
{
	//int rv = 0;
	//if (pchLineText == NULL || psContactInfo == NULL)
	//{
	//	return -1;
	//}
 //
	//// 长度
	//int nTextLen = strlen(pchLineText);
	//if (nTextLen == 0)
	//{
	//	return -1;
	//}
	//
 //   // 遍历
	//int nItemNum = 0;
	//int i = 0, j = 0;
	//int nDataPosBegin = 0, nDataPosEnd = 0;    // 数据位置
	//char chDataBuffer[TR_MAX_CONTACT_ID_LENGTH];        // 数据
	//while(i != nTextLen)
	//{
	//	// 查找分割串
	//	nDataPosBegin = i;
	//	for (j = nDataPosBegin; j < nTextLen; j++)
	//	{
	//		// 判断，分割
	//		if(pchLineText[j]== ',' && j == 0)
	//		{
	//			nDataPosEnd = j;
	//			break;
	//		}
	//		else if(pchLineText[j]== ',' && pchLineText[j-1] != '"')
	//		{
	//			nDataPosEnd = j;
	//			break;
	//		}
	//	}
	//	if (j == nTextLen)
	//	{
	//		nDataPosEnd = nTextLen-1;
	//	}
	//	i = nDataPosEnd;
	//	i++;

	//	// 取值
	//	memset(chDataBuffer, 0, TR_MAX_CONTACT_ID_LENGTH);
	//	memcpy(chDataBuffer, pchLineText+nDataPosBegin, nDataPosEnd-nDataPosBegin);

	//	// 取值
	//	switch(nItemNum)
	//	{
	//	case 0: // 姓名
	//		ConverCsvToCharData(psContactInfo->name, chDataBuffer);
	//		break;
	//	case 1: // 手机号码(移动)
	//		ConverCsvToCharData(psContactInfo->mobilenumber, chDataBuffer);
	//		break;
	//	case 2: // 手机号码(家庭)
	//		ConverCsvToCharData(psContactInfo->mobilehome, chDataBuffer);
	//	    break;
	//	case 3: // 手机号码(办公)
	//		ConverCsvToCharData(psContactInfo->mobilework, chDataBuffer);
	//	    break;
	//	case 4: // 电话号码
	//		ConverCsvToCharData(psContactInfo->phonenumber, chDataBuffer);
	//		break;
	//	case 5: // 电话号码(家庭)
	//		ConverCsvToCharData(psContactInfo->phonehome, chDataBuffer);
	//		break;
	//	case 6: // 电话号码(办公) 
	//		ConverCsvToCharData(psContactInfo->phonework, chDataBuffer);
	//	    break;
	//	case 7: // 私人邮箱
	//		ConverCsvToCharData(psContactInfo->email, chDataBuffer);
	//		break;
	//	case 8: // 家庭地址
	//		ConverCsvToCharData(psContactInfo->homeaddress, chDataBuffer);
	//	    break;
	//	case 9: // 公司名称
	//		ConverCsvToCharData(psContactInfo->company, chDataBuffer);
	//		break;
	//	case 10: // 个人生日 
	//		ConverCsvToCharData(psContactInfo->birthday, chDataBuffer);
	//		break;
	//	case 11: // 传真
	//		ConverCsvToCharData(psContactInfo->fax, chDataBuffer);
	//		break;
	//	case 12: // 部门
	//		ConverCsvToCharData(psContactInfo->departments, chDataBuffer);
	//		break;
	//	case 13: // 职务
	//		ConverCsvToCharData(pContactInfo->m_Duties, chDataBuffer);
	//		break;
	//	default:
	//	    break;
	//	}

	//	//
	//	nItemNum++;
	//} 

	return 0;
}


////////////////////////////////////////////////////////////////////////
int ConvertVcard211tosContactInfo(CString cStrTmp, sContactInfo* pContactInfo)
{
	//变量 
	int nLen = cStrTmp.GetLength();
	if(nLen == 0)
	{
		return STRING_NULL;
	}

	//
	//char* pwchVcard = new char[nLen];
	//memset(pwchVcard, 0, (nLen)*sizeof(char));
	//pwchVcard = cStrTmp.GetBuffer();//将字符串中的东西取出来，放到数组中。

	char* pwchVcard = cStrTmp.GetBuffer();
	//
	VObject* pMyVcard = VObjectFactory::createInstance(L"VCARD",L"2.1");//建立一个vcard对象,直接调用vObject的构造函数初始化会失败
	if (pMyVcard == 0)
	{
		delete[] pwchVcard;
		pwchVcard = NULL;
		return FAILNEW_VCARDOBJECT;
	}

	//------------------------------------------
	char wchCurLine[5000];//用于存储vcard中的每一行，即一个性质
	memset(wchCurLine, 0, 2048*sizeof(char));
	//char chCurLine[5000];

	//
	int j = 0;
	for (int i= 0 ; i< nLen; i++)
	{
		if(pwchVcard[i] != '\n')
		{
			wchCurLine[j] = pwchVcard[i];
			j++;
		}
		else
		{
			//memset(chCurLine, 0, 5000*sizeof(char));
			//w2c(chCurLine, wchCurLine,5000);
			//strcpy(chCurLine,ConvertFromUnicodeToUtf8(wchCurLine));
			deal( pMyVcard, wchCurLine);//将这一行性质分析，并写入到vcard对象中
			memset(wchCurLine, 0, 5000*sizeof(char));
			j=0;
		}
	}

	//到此时，所有的性质都已经放到vcard对象中了
	//delete[] pwchVcard;
	pwchVcard = NULL; 


	//------------------------------------------
	VProperty* pVProperty = NULL;
	WCHAR* pwchar2 = NULL;	
	char ch[1024], temp[200],value[1500]; 
	memset(ch, 0, 1024);
	memset(temp, 0, 200);
	memset(value, 0, 1500);

	CString csValue; 
	// 
	size_t len1=0; 
	{
		pVProperty=pMyVcard->getProperty(L"FN");//如果没有N，则用这个来代替值
		if(pVProperty!=0)
		{
			pwchar2=pVProperty->getValue(0);//取得姓名
			if(pwchar2!=0)
			{
				char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*
				//strcpy(psContactInfo->name,curp);
				memset(value, 0, 1500);
				strcpy(value,curp);
				delete[] curp; curp = NULL;
				
				csValue = CString(value);				
				csValue.Replace(_T("\\;"), _T(";"));
				csValue.Replace(_T("\\:"), _T(":"));
				csValue.Replace(_T("\\\\"), _T("\\"));
				pContactInfo->m_Name = csValue;
			
			}
		}
	}

	pVProperty=0;
	memset(value, 0, 1500);pwchar2=0;
	pVProperty=pMyVcard->getProperty(L"EMAIL");//获取email
	if(pVProperty!=0)
	{
		pwchar2=pVProperty->getValue(0);
		if(pwchar2!=0)
		{
			char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*
			memset(value, 0, 1500);
			strcpy(value,curp);
			delete[] curp; curp = NULL;
		}
	}

	csValue = CString(value);	
	csValue.Replace(_T("\\;"), _T(";"));
	csValue.Replace(_T("\\:"), _T(":"));
	csValue.Replace(_T("\\\\"), _T("\\"));
	pContactInfo->m_Email = csValue;
	csValue.ReleaseBuffer();

	pVProperty=0;
	memset(value, 0, 1500);pwchar2=0;
	pVProperty=pMyVcard->getProperty(L"ORG");//获取org
	if(pVProperty!=0)
	{
		pwchar2=pVProperty->getValue(0);//company
		if(pwchar2!=0)
		{
			char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*
			strcpy(value,curp);
			delete[] curp; curp = NULL;
		}
	
		csValue = CString(value);
		csValue.Replace(_T("\\;"), _T(";"));
		csValue.Replace(_T("\\:"), _T(":"));
		csValue.Replace(_T("\\\\"), _T("\\"));
		pContactInfo->m_Company=csValue;
		
		memset(value, 0, 1500);pwchar2=0;
		pwchar2=pVProperty->getValue(1);//departments
		if(pwchar2!=0)
		{
			char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*

			strcpy(value,curp);
			delete[] curp; curp = NULL;
		}
	
		csValue = CString(value);
		csValue.Replace(_T("\\;"), _T(";"));
		csValue.Replace(_T("\\:"), _T(":"));
		csValue.Replace(_T("\\\\"), _T("\\"));
		pContactInfo->m_Departments=csValue
	}

	pVProperty=0;
	memset(value, 0, 1500);pwchar2=0;
	pVProperty=pMyVcard->getProperty(L"BDAY");//获取生日
	if(pVProperty!=0)
	{
		pwchar2=pVProperty->getValue(0);
		if(pwchar2!=0)
		{
			char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*
			strcpy(value,curp);
			delete[] curp; curp = NULL;
		}
	}
	pContactInfo->m_Birthday = CString(value);


	//------------- 获取分组ID--------------
	psContactInfo->nGroupID = 0;
	pVProperty=0;
	memset(value, 0, 1500);
	pwchar2=0;
	pVProperty=pMyVcard->getProperty(L"GROUP");//获取分组号
	if(pVProperty!=0)
	{
		int nSum = pVProperty->valueCount();
		for (int i=0; i< nSum; i++)
		{
			pwchar2=pVProperty->getValue(i);
			if(pwchar2!=0)
			{
				char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*
				strcpy(value,curp);
				delete[] curp; curp = NULL;

				csValue = CString(value);
				csValue.Replace(_T("\\;"), _T(";"));
				csValue.Replace(_T("\\:"), _T(":"));
				csValue.Replace(_T("\\\\"), _T("\\"));
				pContactInfo->m_GroupIDs.push_back(csValue);
			}
		}
	}
	//---------------------------------------

	pVProperty=0;
	memset(value, 0, 1500);
	pwchar2=0;
	pVProperty=pMyVcard->getProperty(L"TITLE");//获取职务
	if(pVProperty!=0)
	{
		pwchar2=pVProperty->getValue(0);
		if(pwchar2!=0)
		{
			char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*
			strcpy(value,curp);
			delete[] curp; curp = NULL;
		}
	}


	csValue = CString(value);
	csValue.Replace(_T("\\;"), _T(";"));
	csValue.Replace(_T("\\:"), _T(":"));
	csValue.Replace(_T("\\\\"), _T("\\"));
	pContactInfo->m_Duties = csValue;
	
	//处理电话
	bool tel=false;//用于寻找TEL:123 这一项，因为有时 其可能会有参数如voice等，参数不一定为0个
	int num=pMyVcard->propertiesCount();//得到性质条目的数目
	int numpara=0;//参数的个数;
	WCHAR* name=0;
	int equals=-1;
	for(int i=0;i<num;i++)//遍历性质，获得tel属性
	{
		name=0;
		pwchar2=0;pVProperty=0;memset(value, 0, 1500);
		pVProperty=pMyVcard->getProperty(i);//得到一个属性
		if(pVProperty!=0)
		{
			name=pVProperty->getName();
			if(name!=0)
			{
				equals=wcscmp(name,L"TEL");
				if(equals!=0)
					equals=wcscmp(name,L"tel");
				name=0;
				if(equals==0)//如果这一项是TEL
				{
					equals=-1;
					numpara=pVProperty->parameterCount();//获取参数个数
					if(numpara==0)		//-----phonenumber
					{
						pwchar2=pVProperty->getValue(0);
						if(pwchar2!=0)
						{
							char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*
							string des=Qp_decode(curp);//qp到char*
							delete[] curp; curp = NULL;
							des.copy(value,1500);
							WCHAR* pwchar2=ConvertUtf8ToUnicode(value);//utf8到Unicode
							curp=ConvertFromAnsiToUtf8(pwchar2);//Unicode到char*
							memset(value, 0, 1500);
							strcpy(value,curp);
							delete[] curp; curp = NULL;

							pContactInfo->m_Phonenumber=CString(value);
							tel=true;
						}
					}
					else//参数个数>0时，就去遍历
					{
						bool hashome=false,haswork=false,hascell=false,hasfax=false;//是否有这个参数
						hashome=pVProperty->containsParameter(L"HOME");
						haswork=pVProperty->containsParameter(L"WORK");
						hascell=pVProperty->containsParameter(L"CELL");
						hasfax=pVProperty->containsParameter(L"FAX");
						if(hasfax)//-----phonehome
						{
							pwchar2=pVProperty->getValue(0);
							if(pwchar2!=0)
							{
								char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*
								pContactInfo->m_Fax=CString(curp);
								delete[] curp; curp = NULL;

								
							}
						}
						if(hascell==false&&hashome==true)//-----phonehome
						{
							pwchar2=pVProperty->getValue(0);
							if(pwchar2!=0)
							{
								char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*
								pContactInfo->m_PhoneHome=CString(curp);
								delete[] curp; curp = NULL;

								
							}
						}
						else if(hascell==false&&haswork==true)//----phonework
						{
							pwchar2=pVProperty->getValue(0);
							if(pwchar2!=0)
							{
								char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*
								pContactInfo->m_PhoneWork=CString(curp);
								delete[] curp; curp = NULL;
							}
						}
						else if(hascell==true&&haswork==false&&hashome==false)//----mobilehome
						{
							pwchar2=pVProperty->getValue(0);
							if(pwchar2!=0)
							{
								char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*
								pContactInfo->m_MobileNumber=CString(curp);
								delete[] curp; curp = NULL;
							}
						}
						if(hascell==true&&hashome==true)//----mobilehome为例防止有TEL;HOME;WORK;CELL的样式
						{
							pwchar2=pVProperty->getValue(0);
							if(pwchar2!=0)
							{
								char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*
								pContactInfo->m_MobileHome = CString(curp);
								delete[] curp; curp = NULL;

								strcpy(psContactInfo->mobilehome,value);
							}
						}
						if(hascell==true&&haswork==true)//----mobilehome
						{
							pwchar2=pVProperty->getValue(0);
							if(pwchar2!=0)
							{
								char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*
								pContactInfo->m_MobileWork = CString(curp);
								delete[] curp; curp = NULL;
							}
						}
						if(tel==false&&hascell==false&&haswork==false&&hashome==false&&hasfax==false)//----tel
						{
							pwchar2=pVProperty->getValue(0);
							if(pwchar2!=0)
							{
								char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*
								pContactInfo->m_PhoneNumber = CString(curp);
								delete[] curp; curp = NULL;
							}
						}
					}
				}
			}
		}
	}

	//获取家庭住址
	bool hashomeaddr=false;
	num=0;	name=0;	equals=-1;
	num=pMyVcard->propertiesCount();//得到性质条目的数目
	for(int i=0;i<num;i++)//遍历性质，获得LABEL属性
	{
		numpara=0;	name=0;	pwchar2=0;	pVProperty=0;	memset(value, 0, 1500);
		pVProperty=pMyVcard->getProperty(i);//得到一个属性
		if(pVProperty!=0)
		{
			name=pVProperty->getName();
			if(name!=0)
			{
				equals=wcscmp(name,L"LABEL");
				if(equals==0)//如果这一项是LABEL
				{
					equals=-1;
					numpara=pVProperty->parameterCount();//获取参数个数
					if(numpara>0)
					{
						bool hashome=false;
						hashome=pVProperty->containsParameter(L"HOME");
						if(hashome==true)
						{
							pwchar2=pVProperty->getValue(0);
							if(pwchar2!=0)
							{
								char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*
								memset(value, 0, 1500);
								strcpy(value,curp);
								delete[] curp; curp = NULL;
								//strcpy(psContactInfo->homeaddress,value);

								csValue = CString(value);
								csValue.Replace(_T("\\;"), _T(";"));
								csValue.Replace(_T("\\:"), _T(":"));
								csValue.Replace(_T("\\\\"), _T("\\"));
								pContactInfo->m_HomeAddress=csValue;
								hashomeaddr=true;
								i=num;//停止循环
								//hashomeaddr=true;
							}
						}
					}
				}
			}
		}
	}
	
	if(hashomeaddr==false)
	{
		num=0;	name=0;	equals=-1;
		num=pMyVcard->propertiesCount();//得到性质条目的数目
		for(int i=0;i<num;i++)//遍历性质，获得ADR属性
		{
			numpara=0;	name=0;	pwchar2=0;	pVProperty=0;	memset(value, 0, 1500);
			pVProperty=pMyVcard->getProperty(i);//得到一个属性
			if(pVProperty!=0)
			{
				name=pVProperty->getName();
				if(name!=0)
				{
					equals=wcscmp(name,L"ADR");
					if(equals==0)//如果这一项是ADR
					{
						equals=-1;
						numpara=pVProperty->parameterCount();//获取参数个数
						if(numpara>0)
						{
							bool hashome=false;
							hashome=pVProperty->containsParameter(L"HOME");
							if(hashome==true)
							{
								temp[0]='\0';
								equals=-1;
								for(int addrnum=0;addrnum<=6;addrnum++)//将性质按格式写入homeaddress中//
								{
									len1=0;
									pwchar2=pVProperty->getValue(addrnum);
									if(pwchar2!=0)
									{
										char* curp=ConvertFromAnsiToUtf8(pwchar2);//转成char*
										temp[0]='\0';
										strcpy(temp,curp);
										delete[] curp; curp = NULL;
										strcat(value,temp);
										if(temp[0]!='\0')
										strcat(value," ");//;
										temp[0]='\0';
										pwchar2=0;
									}
								}
								csValue = CString(value);
								csValue.Replace(_T("\\;"), _T(";"));
								csValue.Replace(_T("\\:"), _T(":"));
								csValue.Replace(_T("\\\\"), _T("\\"));
								pContactInfo->m_HomeAddress=csValue;
								i=num;//停止循环
								//hashomeaddr=true;
							}
						}
					}
				}
			}
		}
		
	}
	return 1;
}