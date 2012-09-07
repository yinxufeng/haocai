/***********************************************************************************
* 说明      ：  CMemoryPool为内存池，负责内存的分配                                *
* 创建人    ：  谭军红                                                             *
* 创建日期  ：  2011-9-8                                                           *
***********************************************************************************/

#pragma once
//高速缓冲区结构
struct sMemory
{
	char*		m_Buffer;	//缓冲区
	DWORD		m_Bytes;	//缓冲区数据的字节数
};

//高速缓冲区附属信息结构
struct sMemoryInfo
{
	sMemory			m_Memory;	//缓冲区
	DWORD			m_Size;		//缓冲区大小
	volatile long	m_Reference;//引用计数器
};

/********************************************************************
						高速内存池
********************************************************************/
class CMemoryPool
{
public:
	
	//创建内存池
	static void CreateMemPool();

	//删除内存池
	static void DeleteMemPool();

	//获取缓冲区
	static sMemory* GetMemory(DWORD Size);

	//释放缓冲区
	static void FreeMemory(sMemory* Memory);

	//获取缓冲区大小
	static DWORD GetMemorySize(sMemory* Memory)
	{ 
		if(Memory==NULL) return 0;
		sMemoryInfo *MemoryInfo=CONTAINING_RECORD(Memory,sMemoryInfo,m_Memory);
		return MemoryInfo->m_Size;									
	};

	//引用计数器+1
	static void IncReference(sMemory* Memory)
	{ 
		InterlockedIncrement(&((sMemoryInfo*)Memory)->m_Reference);
	};

private:

	//内存堆栈结构
	struct sMemoryStackList
	{
		sMemoryInfo			**m_Stack;		//内存堆栈
		volatile int		m_StackTop;		//堆栈顶
		CRITICAL_SECTION	m_StackLock;	//栈锁
	};

	//构造
	CMemoryPool(void){};

	//析构
	~CMemoryPool(void){};

	static sMemoryStackList		*m_MemoryStackList;	//内存堆栈列表
};
