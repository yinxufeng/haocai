#include "StdAfx.h"
#include "../common/Include/DataDefine.h"
#include "../common/Include/base64.h"
#include "export.h"
#include "ContactTransUntil.h"

void deal(VObject* myVcard,char curchar[]);

//char转化为wchar_t
 wchar_t* TransCharToWchar(char *utf8)
{
	DWORD wcsLen = ::MultiByteToWideChar(CP_ACP, NULL, utf8, -1, NULL, 0);
	wchar_t* unicode = new wchar_t[wcsLen];
	::MultiByteToWideChar(CP_ACP, NULL, utf8, -1, unicode, wcsLen);
	return unicode;
}

 //wchar_t转化为char
char* TransWcharToChar(const wchar_t *unicode)
{
	int len = WideCharToMultiByte( CP_ACP, 0, unicode, -1, 0, 0, 0, 0 );
	char* buffer = new char[len+1];
	WideCharToMultiByte( CP_ACP, 0, unicode, -1, buffer,len, 0, 0 );
	buffer[len] = '\0';
	return buffer;
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

//这个函数专用于当编码类型为base64（一般在vcard3.0中）时，将每一个性质的值加到里面
void addvaluetoprop(VProperty* vp,WCHAR* wch)
{
	char* ch=TransWcharToChar(wch);
	int len=strlen(ch);
	char* temp = new char[len+1];
	memset(temp,0,sizeof(char)*(len+1));

	int end=0,i=0,ind=0,j=0;//ind用于标志是第几个性质值
	for(;ch[i]!='\0';i++,j++)
	{
		if(ch[i]==';')
		{
			temp[j]='\0';j=-1;//退出循环后就会加1 这样才是从0开始拷贝
			end=i;
			//将temp加到性质中去
			if(vp!=0)
			{
				CString Value=CString(temp);
				vp->setValue (Value.GetBuffer());
				Value.ReleaseBuffer();
			}
		}
		else
			temp[j]=ch[i];
	}
	temp[j]='\0';//处理最后一个性质值
	//将temp加到性质中去
	if(vp!=0)
	{
		CString Value=CString(temp);
		vp->setValue (Value.GetBuffer());
		Value.ReleaseBuffer();
	}

	delete []ch;
	delete []temp;
}

//从字符串转化为VCARD
int TransStrToVcardObject(CString& VcardStr,VObject* pVcard)
{
	char* pwchVcard  =TransWcharToChar(VcardStr.GetBuffer());
	int   nLen       =strlen(pwchVcard);
	char* wchCurLine = new char[nLen];
	memset(wchCurLine,0,sizeof(char)*nLen);

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
			deal( pVcard, wchCurLine);//将这一行性质分析，并写入到vcard对象中
			memset(wchCurLine, 0, nLen*sizeof(char));
			j=0;
		}
	}

	delete [] wchCurLine;
	delete [] pwchVcard;
	return TRANS_OK;
}


//从Vcard211字符串转化为联系人信息
int TransVcard211ToContactInfo(CString& VcardStr,sContactInfo& Info)
{
	if(VcardStr.IsEmpty())
		return STRING_NULL;

	VObject* pMyVcard = VObjectFactory::createInstance(L"VCARD",L"2.1");//建立一个vcard对象,直接调用vObject的构造函数初始化会失败
	if (pMyVcard == NULL)
		return FAILNEW_VCARDOBJECT;
	

	TransStrToVcardObject(VcardStr,pMyVcard);
	
	//------------------------------------------
	VProperty* pVProperty = NULL;	

	//取得姓名
	pVProperty=pMyVcard->getProperty(L"FN");//如果没有N，则用这个来代替值
	if(pVProperty != NULL)
	{
		WCHAR* pValue = pVProperty->getValue(0);
		if(pValue != NULL)
		{
			Info.m_Name = CString(pValue);			
			Info.m_Name.Replace(_T("\\;"), _T(";"));
			Info.m_Name.Replace(_T("\\:"), _T(":"));
			Info.m_Name.Replace(_T("\\\\"), _T("\\"));
		}
	}
	
	//获取email
	pVProperty=NULL;
	pVProperty=pMyVcard->getProperty(L"EMAIL");
	if(pVProperty != NULL)
	{
		WCHAR* pValue = pVProperty->getValue(0);
		if(pValue != NULL)
		{
			Info.m_Email=CString(pValue);
			Info.m_Email.Replace(_T("\\;"), _T(";"));
			Info.m_Email.Replace(_T("\\:"), _T(":"));
			Info.m_Email.Replace(_T("\\\\"), _T("\\"));
		}
	}


    //获取Org
	pVProperty=NULL;
	pVProperty=pMyVcard->getProperty(L"ORG");//获取org
	if(pVProperty != NULL)
	{
		//获取company
		WCHAR* pValue=pVProperty->getValue(0);
		if(pValue != NULL)
		{
			Info.m_Company = CString(pValue);
			Info.m_Company.Replace(_T("\\;"), _T(";"));
			Info.m_Company.Replace(_T("\\:"), _T(":"));
			Info.m_Company.Replace(_T("\\\\"), _T("\\"));
		}
	
		//获取departments
		pValue=NULL;
		pValue=pVProperty->getValue(1);
		if(pValue != NULL)
		{
			Info.m_Departments = CString(pValue);
			Info.m_Departments.Replace(_T("\\;"), _T(";"));
		    Info.m_Departments.Replace(_T("\\:"), _T(":"));
		    Info.m_Departments.Replace(_T("\\\\"), _T("\\"));

		}
	}

	//获取生日
	pVProperty = NULL;
	pVProperty=pMyVcard->getProperty(L"BDAY");
	if(pVProperty!=0)
	{
		WCHAR* pValue=pVProperty->getValue(0);
		if(pValue != NULL)
			Info.m_Birthday = CString(pValue);
		
	}
	
	//------------- 获取分组ID--------------
	pVProperty=NULL;
	pVProperty=pMyVcard->getProperty(L"GROUP");//获取分组号
	if(pVProperty!=0)
	{
		int nSum = pVProperty->valueCount();
		for (int i=0; i< nSum; i++)
		{
			WCHAR* pValue=pVProperty->getValue(i);
			if(pValue != NULL)
			{
				CString GroupStr=CString(pValue);
				GroupStr.Replace(_T("\\;"), _T(";"));
				GroupStr.Replace(_T("\\:"), _T(":"));
				GroupStr.Replace(_T("\\"),_T(" "));
				GroupStr.TrimLeft();
				GroupStr.TrimRight();
				Info.m_GroupIDs.push_back(GroupStr);
			}
		}
	}
	
	//获取职务
	pVProperty=0;
	pVProperty=pMyVcard->getProperty(L"TITLE");
	if(pVProperty!=0)
	{
		WCHAR* pValue=pVProperty->getValue(0);
		if( pValue != NULL)
		{
			Info.m_Duties = CString(pValue);
			Info.m_Duties.Replace(_T("\\;"), _T(";"));
			Info.m_Duties.Replace(_T("\\:"), _T(":"));
			Info.m_Duties.Replace(_T("\\\\"), _T("\\"));

		}
	}
	

	//处理电话
	bool tel=false;//用于寻找TEL:123 这一项，因为有时 其可能会有参数如voice等，参数不一定为0个
	int num=pMyVcard->propertiesCount();//得到性质条目的数目
	for(int i=0;i<num;i++)//遍历性质，获得tel属性
	{
		pVProperty=NULL;
		pVProperty=pMyVcard->getProperty(i);//得到一个属性

		if(pVProperty!=0)
		{
			WCHAR* name=pVProperty->getName();
			if(name!= NULL)
			{
				CString NameStr=CString(name);
				NameStr.MakeLower();
				if(NameStr == _T("tel"))
				{
					int numpara=pVProperty->parameterCount();//获取参数个数
					if(numpara==0)		//-----phonenumber
					{
						WCHAR* pValue=pVProperty->getValue(0);
						if(pValue != NULL)
						{
							//string des=Qp_decode(curp);//qp到char*
							Info.m_PhoneNumber = CString(pValue);
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
							WCHAR* pValue=pVProperty->getValue(0);
							if(pValue != NULL)
								Info.m_Fax = CString(pValue);
						}
						if(hascell==false&&hashome==true)//-----phonehome
						{
							WCHAR* pValue = pVProperty->getValue(0);
							if(pValue != NULL)
								Info.m_PhoneHome = CString(pValue);
							
						}
						else if(hascell==false&&haswork==true)//----phonework
						{
							WCHAR* pValue =pVProperty->getValue(0);
							if(pValue != NULL)
								Info.m_PhoneWork = CString(pValue);
						}
						else if(hascell==true&&haswork==false&&hashome==false)//----mobilehome
						{
							WCHAR* pValue = pVProperty->getValue(0);
							if(pValue != NULL)
								Info.m_MobileNumber = CString(pValue);
						}
						if(hascell==true&&hashome==true)//----mobilehome为例防止有TEL;HOME;WORK;CELL的样式
						{
							WCHAR* pValue=pVProperty->getValue(0);
							if( pValue != NULL)
								Info.m_MobileHome = CString(pValue);

						}
						if(hascell==true&&haswork==true)//----mobilehome
						{
							WCHAR* pValue=pVProperty->getValue(0);
							if(pValue != NULL )
								Info.m_MobileWork = CString(pValue);
						}
						if(tel==false&&hascell==false&&haswork==false&&hashome==false&&hasfax==false)//----tel
						{
							WCHAR* pValue=pVProperty->getValue(0);
							if(pValue != NULL)
								Info.m_PhoneNumber = CString(pValue);

						}
					}
				}
			}
		}
	}

	//获取家庭住址
	bool hashomeaddr=false;
	num=0;
	num=pMyVcard->propertiesCount();//得到性质条目的数目
	for(int i=0;i<num;i++)//遍历性质，获得LABEL属性
	{
		pVProperty = NULL;
		pVProperty=pMyVcard->getProperty(i);//得到一个属性
		if(pVProperty!=0)
		{
			WCHAR* Name=pVProperty->getName();
			if(Name!= NULL)
			{
				CString NameStr=CString(Name);
				NameStr.MakeLower();
				if(NameStr == _T("label"))//如果这一项是LABEL
				{
					int numpara=pVProperty->parameterCount();//获取参数个数
					if(numpara>0)
					{
						bool hashome=false;
						hashome=pVProperty->containsParameter(L"HOME");
						if(hashome==true)
						{
							WCHAR* pValue=pVProperty->getValue(0);
							if(pValue != NULL)
							{
								Info.m_HomeAddress = CString(pValue);
								Info.m_HomeAddress.Replace(_T("\\;"), _T(";"));
								Info.m_HomeAddress.Replace(_T("\\:"), _T(":"));
								Info.m_HomeAddress.Replace(_T("\\\\"), _T("\\"));
								hashomeaddr=true;
								i=num;//停止循环
							}
						}
					}
				}
			}
		}
	}
	
	if(hashomeaddr==false)
	{
		num=pMyVcard->propertiesCount();//得到性质条目的数目
		for(int i=0;i<num;i++)//遍历性质，获得ADR属性
		{
			pVProperty=0;
			pVProperty=pMyVcard->getProperty(i);//得到一个属性
			if(pVProperty!=0)
			{
				WCHAR* Name=pVProperty->getName();
				if(Name != NULL)
				{
					CString NameStr=CString(Name);
					NameStr.MakeLower();
					if(NameStr == _T("adr"))
					{
						int numpara=pVProperty->parameterCount();//获取参数个数
						if(numpara>0)
						{
							bool hashome=false;
							hashome=pVProperty->containsParameter(L"HOME");
							if(hashome==true)
							{
								CString HomeStr;
								for(int addrnum=0;addrnum<=6;addrnum++)//将性质按格式写入homeaddress中//
								{
									WCHAR* pValue=pVProperty->getValue(addrnum);
									if(pValue != NULL)
									{
										HomeStr+=CString(pValue);
									}
								}
								HomeStr.Replace(_T("\\;"), _T(";"));
								HomeStr.Replace(_T("\\:"), _T(":"));
								HomeStr.Replace(_T("\\\\"), _T("\\"));
								Info.m_HomeAddress = HomeStr;
								i=num;//停止循环
							
							}
						}
					}
				}
			}
		}
		
	}

	delete pMyVcard;
	return TRANS_OK;
}


//因为电话的类型多，所以用一个函数专门实现它。 第一个参数的值的含义：
//1 cell 2 cell home 3 cell work 4 tel 5 tel home 6 tel work 7tel fax
//最后一个参数encoding为encoding方式，用于给函数mySetEncoding(..)传递参数。
//第二个参数为要将此TEL条目写入的VCARD对象，第三个参数为TEL的值，即电话号码。
bool AddTELToVObject(int type,VObject* vbp,CString& Number)
{
	bool ret=false;
	VProperty* vp=0;
	if(type>7||type<1||Number.IsEmpty())//如果tel的值为空则不加人
		return false;

	vp=new VProperty(L"TEL");
	if(vp==0)
		return false;
	vp->setValue(Number.GetBuffer());
	Number.ReleaseBuffer();

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

//添加地址
void AddADRtoVObject(int type,VObject* vbp,CString& HomeAddress)
{
	int StartPos=0;
	int EndPos = 0;
	vector<CString> AddressList;
	EndPos=HomeAddress.Find(_T(";"),StartPos);
	while( EndPos != -1)
	{
		CString TempStr = HomeAddress.Mid(StartPos,EndPos-StartPos-1);
		AddressList.push_back(TempStr);
		StartPos=EndPos+1;
	}

	CString LastStr = HomeAddress.Mid(StartPos);
	if( !LastStr.IsEmpty() )
	{
		AddressList.push_back(LastStr);
	}

	if(!AddressList.empty())
	{
		//将每个字段和参数加到里边
		VProperty* vp=NULL;
		vp=new VProperty(L"ADR");//插入名字
		if(vp!= NULL)
		{
			if(type==0)
				vp->addParameter(L"HOME",NULL);//插入参数

			for(int Index =0; Index < (int)AddressList.size(); Index++)
			{
				vp->setValue(AddressList[Index].GetBuffer());
				AddressList[Index].ReleaseBuffer();
				
			}
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


//从联系人信息转化为Vcard211字符串
int TransContactInfoToVard211(sContactInfo& Info,CString& VcardStr)
{
	VObject* pMyVcard = VObjectFactory::createInstance(L"VCARD",L"2.1");
	if (pMyVcard == NULL)
		return FAILNEW_VCARDOBJECT;
	
	VProperty* pVProperty = NULL;
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

	//添加版本
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
	
 
	//名字
	if(!Info.m_Name.IsEmpty())
	{
		pVProperty = new VProperty(L"N", Info.m_Name.GetBuffer());
		Info.m_Name.ReleaseBuffer();

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

		pVProperty = new VProperty(L"FN", Info.m_Name.GetBuffer());
		Info.m_Name.ReleaseBuffer();
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
	AddTELToVObject(1, pMyVcard, Info.m_MobileNumber);
	AddTELToVObject(2, pMyVcard, Info.m_MobileHome);
	AddTELToVObject(3 ,pMyVcard, Info.m_MobileWork);
	AddTELToVObject(4 ,pMyVcard, Info.m_PhoneNumber);
	AddTELToVObject(5, pMyVcard, Info.m_PhoneHome);
	AddTELToVObject(6, pMyVcard, Info.m_PhoneWork);
	AddTELToVObject(7, pMyVcard, Info.m_Fax);

	// 邮箱
	if(!Info.m_Email.IsEmpty())
	{
		pVProperty = new VProperty(L"EMAIL");
		if(pVProperty != NULL)
		{
			pVProperty->setValue (Info.m_Email.GetBuffer());
			Info.m_Email.ReleaseBuffer();
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

	AddADRtoVObject(0, pMyVcard,Info.m_HomeAddress);
	
	//公司　部门
	if( !Info.m_Company.IsEmpty() || !Info.m_Departments.IsEmpty())
	{
		pVProperty = new VProperty(L"ORG");
		if(pVProperty != NULL)
		{
			// 在性质中加入公司
			if(!Info.m_Company.IsEmpty())
			{
				pVProperty->setValue(Info.m_Company.GetBuffer());
				Info.m_Company.ReleaseBuffer();
			}
			else
			{
				pVProperty->setValue(L"");
			}

			// 在性质中插入部门
			if(!Info.m_Departments.IsEmpty())
			{
				pVProperty->setValue(Info.m_Departments.GetBuffer());
				Info.m_Departments.ReleaseBuffer();
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
	if(!Info.m_Birthday.IsEmpty())
	{
		pVProperty = new VProperty(L"BDAY");
		if(pVProperty != NULL)
		{
			pVProperty->setValue (Info.m_Birthday.GetBuffer());
			Info.m_Birthday.ReleaseBuffer();

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
	if(!Info.m_Duties.IsEmpty())
	{
		pVProperty = new VProperty(L"TITLE");
		if(pVProperty != NULL)
		{
			pVProperty->setValue (Info.m_Duties.GetBuffer());
			Info.m_Duties.ReleaseBuffer();

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
	if(!Info.m_GroupIDs.empty())
	{
		pVProperty = new VProperty(L"GROUP");
		if(pVProperty != NULL)
		{
			for(int Index =0; Index < (int)Info.m_GroupIDs.size(); Index++)
			{
				pVProperty->setValue(Info.m_GroupIDs[Index].GetBuffer());
				Info.m_GroupIDs[Index].ReleaseBuffer();

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
		CString TimeStr=CString(chTime);
		pVProperty->setValue (TimeStr.GetBuffer());
		TimeStr.ReleaseBuffer();

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
	VcardStr=CString(wchar1);

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

//从Vcard30字符串转化为联系人信息
int TransVcard30ToContactInfo(CString& VcardStr,sContactInfo& Info)
{
	return TRANS_OK;

}

//从联系人信息转化为Vcard30
int TransContactInfoToVcard30(sContactInfo& Info,CString& VcardStr)
{
	return TRANS_OK;
}

//从CSV格式转化为联系人信息
int TransCSVToContactInfo(CString& CSVStr,sContactInfo& Info)
{
	return TRANS_OK;
}

//从联系人信息转化为CSV格式字符串
int TransContactInfoToCSV(sContactInfo& Info,CString& CSVStr)
{
	return TRANS_OK;
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
					my[j]='\0';my[j+1]='\0';j=0;
					for(int i=0;i<j;++i) 
					{ 
						if(my[i]>='a'&&my[i]<='z')//小写字母转成大写
							my[i] = my[i]-32;//   或者写成a[i]   =   a[i]-( 'a '- 'A '); 
					}
					CString Value=CString(my);
					vp=new VProperty(Value.GetBuffer());//新建一个性质。
					Value.ReleaseBuffer();
					
				}
				else if(ispara==true)//添加参数
				{
					if(curchar[i]==':')//如果为冒号，则开始进行属性值分析。
					{
						ispara=false;isvalue=true;
					}
					my[j]='\0';my[j+1]='\0';

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
					
						CString Name=CString(my);
						CString Value=CString(paravalue);
						vp->addParameter(Name.GetBuffer(),Value.GetBuffer());
						Value.ReleaseBuffer();
						Name.ReleaseBuffer();
					}
					j=0;
				}
				else//对性质值的处理
				{
					if(vp!=0)
					{
						my[j]='\0';my[j+1]='\0';
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
						CString Value=CString(my);
						vp->setValue (Value.GetBuffer());
						Value.ReleaseBuffer();
					
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
		my[j]='\0';my[j+1]='\0';//处理最后一个性质值。因为最后一个性质值后没有分号或冒号。
		int len=1024;
		if(isbase64==true)//转换成此种编码后，各个性质值不再以分号隔开。
		{
			char curmy[1025];curmy[0]='\0';
			strcpy(curmy,my);my[0]='\0';
			int len=b64_decode(my,curmy);
			my[len]='\0';
			WCHAR* wchar2=0;
			// 经过测试，当为base64时 ，其charset为utf8
			//wchar2=ConvertUtf8ToUnicode(my);//utf8到Unicode wchar2中方的就是性质值，需要将性质分字段放在里面
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
			CString Value=CString(my);
			vp->setValue (Value.GetBuffer());
			Value.ReleaseBuffer();
	
		}
		myVcard->addProperty (vp);//将性质插到vcard对象中
		delete vp;
	}
}

