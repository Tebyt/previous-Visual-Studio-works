/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	ZLink.h

							Describe:	链表

							Author:		赵洪松(xueren)

							CreateTime: 2002.3
							UpdateTime: 2003.08.20
*/

#ifndef _ZEPHYR_LINK_H
#define _ZEPHYR_LINK_H

#include <Zephyr.h>

#if _MSC_VER <= 1020
# define TYPENAME
#else
# define TYPENAME typename
#endif

#include <vector>

// 定义_ZEPHYR_LINK_DEBUG 就会在初始化和释放的时候输出log
/*
#ifdef _DEBUG
#ifndef _ZEPHYR_LINK_DEBUG
#define _ZEPHYR_LINK_DEBUG
#endif	//_ZEPHYR_LINK_DEBUG
#endif	//_DEBUG
*/

#include <zdebug.h>

/*
#ifdef _ZEPHYR_3_USE_ZEPHYR_5_
#	define _ZEPHYR_5_MEMORY_SAFE_
#	include <Zephyr5\BaseDef.h>
#endif // _ZEPHYR_3_USE_ZEPHYR_5_
*/

//////////////////////////////////////////////////////////////////////
// ZLink
// 说明：单纯的链表，结点实际内存空间自己控制
//		链表长度可以根据实际使用程度自行调整

// 算法介绍
// 有3个结点指针，一个始终指向链表的头结点，一个指向已分配空间的整个链表的尾结点
// Last，另外一个指向现在可以使用的链表结点End

// 增加链表结点 直接给End结点赋值，End结点后移
// 删除链表结点 连接要删除结点前后的结点，然后将它移动到Last结点的位置，如果刚好删
// 除End结点前面的结点，则将End前移

// 外部遍历结点可以通过 GetData()

template<class T,unsigned int SIZE = 1024,unsigned int LINKSZ = 64>
class ZLink{
private:
	struct link{
		T		*object;
		link	*next;

		link()
		{
			object = NULL;
			next = NULL;
		}
	};

	typedef std::vector<link*> Array;
private:
	link *m_Head,*m_End,*m_Last;	// link head & used end & alloc end
	unsigned int m_uLen;			// total length
	unsigned int m_uUsed;			// used length
	Array			m_memory;
public:
	// 构造函数
	inline ZLink();
	// 析构函数
	~ZLink() { Release(); }

	// 资源释放
	void Release();

	// 获得链表大小
	unsigned int GetLen() const { return m_uLen; }
	// 获得链表使用度
	unsigned int GetUsed() const { return m_uUsed; }

	// 获得头结点Object
	inline T *GetHeadObj();
	// 获得头结点
	void *GetHead() { return m_Head; }

	// 获得结点的 Object
	inline T *GetNodeObj(void *Node);

	// GetData()
	// 参数 -	obj 为 Object指针，初始化为 NULL
	//			index 为结点指针，初始化为 NULL，可以循环执行，直到index == NULL
	void GetData(T* &obj,void* &index);

	// 清空链表
	inline void Clear();

	// 添加 Object
	HRESULT Add(T *obj);

	// 删除 Object
	HRESULT Del(T *obj);
	// 删除 Object
	HRESULT Del(T &obj);
private:
	// 分配空间，返回的是一个排好顺序的 link
	TYPENAME ZLink<T,SIZE,LINKSZ>::link *Alloc(unsigned int Size);

	// 删除结点
	// 参数	-	pre 为前一个结点
	//			node 为待删除结点
	HRESULT Del(TYPENAME ZLink<T,SIZE,LINKSZ>::link *pre,TYPENAME ZLink<T,SIZE,LINKSZ>::link *node);

	// 调试输出
	void DebugLog()	const;
};

// 构造函数
template<class T,unsigned int SIZE,unsigned int LINKSZ>
inline ZLink<T,SIZE,LINKSZ>::ZLink()
{
	m_uLen = m_uUsed = 0;
	m_Last = NULL;

	m_End = m_Head = Alloc(SIZE);
	if(m_Head == NULL)
		Debug("ZLink<%d,%d>::ZLink fail!",SIZE,LINKSZ);
}

// 分配空间，返回的是一个排好顺序的 link
template<class T,unsigned int SIZE,unsigned int LINKSZ>
TYPENAME ZLink<T,SIZE,LINKSZ>::link *ZLink<T,SIZE,LINKSZ>::Alloc(unsigned int Size)
{
	ZASSERT(Size > 0);

	link *tmp = NULL;
	link *tmp1;
	unsigned int i = 1;

	tmp = new link[Size];
	if(tmp == NULL)
	{
		Debug("ZLink::alloc(%d) fail!",Size);

		return NULL;
	}

	tmp1 = &tmp[0];

	while(i < Size)
	{
		tmp1->next = &tmp[i++];
		tmp1 = tmp1->next;
	}

	m_Last = tmp1;

	m_uLen += Size;

	m_memory.push_back(tmp);

	return &tmp[0];
}

// 获得头结点Object
template<class T,unsigned int SIZE,unsigned int LINKSZ>
inline T *ZLink<T,SIZE,LINKSZ>::GetHeadObj()
{
	ZASSERT(m_Head != NULL);

	return m_Head->object;
}

// 获得结点的 Object
template<class T,unsigned int SIZE,unsigned int LINKSZ>
inline T *ZLink<T,SIZE,LINKSZ>::GetNodeObj(void *Node)
{
	ZASSERT(Node != NULL);

	return ((link *)Node)->object;
}

// GetData()
// 参数 -	obj 为 Object指针，初始化为 NULL
//			index 为结点指针，初始化为 NULL，可以循环执行，直到index == NULL
template<class T,unsigned int SIZE,unsigned int LINKSZ>
void ZLink<T,SIZE,LINKSZ>::GetData(T* &obj,void* &index)
{
	if(m_uUsed == 0 || index == m_End)
	{
		index = NULL;
		obj = NULL;
	}
	else if(index == NULL)
	{
		obj = m_Head->object;
		index = m_Head->next;
	}
	else
	{
		obj = ((link *)index)->object;
		index = ((link *)index)->next;
	}
}

// 添加 Object
template<class T,unsigned int SIZE,unsigned int LINKSZ>
HRESULT ZLink<T,SIZE,LINKSZ>::Add(T *obj)
{
	ZASSERT(obj != NULL);

	m_End->object = obj;

	if(m_End->next == NULL)
	{
		m_End->next = Alloc(LINKSZ);
		if(m_End->next == NULL)
			return ZRet(ZEPHYR_RET_FAILED,"ZLink::Add()");
	}

	m_End = m_End->next;

	m_uUsed++;

	return S_OK;
}

// 删除结点
// 参数	-	pre 为前一个结点
//			node 为待删除结点
template<class T,unsigned int SIZE,unsigned int LINKSZ>
HRESULT ZLink<T,SIZE,LINKSZ>::Del(TYPENAME ZLink<T,SIZE,LINKSZ>::link *pre,TYPENAME ZLink<T,SIZE,LINKSZ>::link *node)
{
	m_uUsed--;

	if(pre == NULL||node == m_Head)	//if del head
	{
		node->object = NULL;

		if(m_End == m_Head->next)	//if only a node
			m_End = m_Head;
		else
		{
			//move head to last
			m_Last->next = m_Head;
			m_Last = m_Last->next;

			m_Head = m_Head->next;
			m_Last->next = NULL;
		}
	}
	else if(node->next == m_End)
	{
		node->object = NULL;

		m_End = node;
	}
	else
	{
		node->object = NULL;

		pre->next = node->next;
		m_Last->next = node;
		node->next = NULL;
		m_Last = m_Last->next;
	}

	return S_OK;
}

// 删除 Object
template<class T,unsigned int SIZE,unsigned int LINKSZ>
HRESULT ZLink<T,SIZE,LINKSZ>::Del(T *obj)
{
	ZASSERT(obj != NULL);

	link *tmp,*pre = NULL;

	if(m_uUsed  ==  0)
	{
#ifdef _ZEPHYR_LINK_DEBUG
		return ZRet(ZEPHYR_RET_FAILED,"ZLink::Del() Empty");
#else
		return E_FAIL;
#endif
	}

	for(tmp = m_Head; tmp->object != obj && tmp != m_End; pre = tmp,tmp = tmp->next);

	if(tmp->object != obj)
	{
#ifdef _ZEPHYR_LINK_DEBUG
		return ZRet(ZEPHYR_RET_FAILED,"ZLink::Del() Can't find obj");
#else
		return E_FAIL;
#endif
	}

	//m_uUsed--;

	return Del(pre,tmp);
}

// 删除 Object
template<class T,unsigned int SIZE,unsigned int LINKSZ>
HRESULT ZLink<T,SIZE,LINKSZ>::Del(T &obj)
{
	link *tmp,*pre = NULL;

	if(m_uUsed  ==  0)
	{
#ifdef _ZEPHYR_LINK_DEBUG
		return ZRet(ZEPHYR_RET_FAILED,"zlink::Del() empty");
#else
		return E_FAIL;
#endif
	}

	for(tmp=m_Head;*(tmp->object) != obj&&tmp != m_End;pre=tmp,tmp=tmp->next);

	if(*(tmp->object) != obj)
	{
#ifdef _ZEPHYR_LINK_DEBUG
		return ZRet(ZEPHYR_RET_FAILED,"zlink::Del() Can't find obj");
#else
		return E_FAIL;
#endif
	}

	//m_uUsed--;

	return Del(pre,tmp);
}

// 资源释放
template<class T,unsigned int SIZE,unsigned int LINKSZ>
void ZLink<T,SIZE,LINKSZ>::Release()
{
#ifdef _ZEPHYR_LINK_DEBUG
	DebugLog();
#endif

	if(m_Head == NULL)
		return ;

	m_Head = m_End = m_Last = NULL;

	m_uLen = 0;
	m_uUsed = 0;

	for(Array::size_type i = 0; i < m_memory.size(); i++)
	{
		if(m_memory[i] != NULL)
			delete[] m_memory[i];
	}

	m_memory.clear();
}

// 清空链表
template<class T,unsigned int SIZE,unsigned int LINKSZ>
inline void ZLink<T,SIZE,LINKSZ>::Clear()
{
	m_uUsed = 0;
	m_End = m_Head;
}

// 调试输出
template<class T,unsigned int SIZE,unsigned int LINKSZ>
void ZLink<T,SIZE,LINKSZ>::DebugLog() const
{
#ifdef _ZEPHYR_LINK_DEBUG
	unsigned int i = 0;
	link *tmp = m_Head,*pre = NULL;

	while(tmp != NULL)
	{
		pre = tmp;

		tmp = tmp->next;

		i++;
	}

	if(m_Last != pre)
		OutputLog("ZLink debug:check error!");

	OutputLog("ZLink debug:total size is %d(%d)",m_uLen,i);

	if(m_uUsed != 0)
	{
		i = 0;
		tmp = m_Head;

		while(tmp != m_End)
		{
			tmp = tmp->next;
			i++;
		}

		OutputLog("ZLink debug:used size is %d(%d)",m_uUsed,i);
	}
#endif
}

//////////////////////////////////////////////////////////////////////
//	ZLinkEx
// 说明：单向链表，全方位的管理结点
//		链表长度可以根据实际使用程度自行调整

// 算法介绍
// 有3个结点指针，一个始终指向链表的头结点，一个指向已分配空间的整个链表的尾结点
// Last，另外一个指向现在可以使用的链表结点End

// 增加链表结点 直接给End结点赋值，End结点后移
// 删除链表结点 连接要删除结点前后的结点，然后将它移动到Last结点的位置，如果刚好删
// 除End结点前面的结点，则将End前移

// 外部遍历结点可以通过 GetData()

template<class T,unsigned int SIZE = 1024,unsigned int LINKSZ = 64>
class ZLinkEx{
private:
	struct link{
		T object;
		link *next;

		link() { next = NULL; }
	};

	typedef std::vector<link*> Array;
private:
	link *m_Head,*m_End,*m_Last;	//link head & used end & alloc end
	unsigned int m_uLen;			//total length
	unsigned int m_uUsed;			//used length
	Array			m_memory;
public:
	// 构造函数
	inline ZLinkEx();
	// 析构函数
	~ZLinkEx() { Release(); }

	// 返回链表长度
	unsigned int GetLen() const { return m_uLen; }
	// 返回链表已使用度
	unsigned int GetUsed() const { return m_uUsed; }

	// 返回头结点 Object 指针
	inline T *GetHeadObjPoint();
	// 返回头结点 Object
	inline T &GetHeadObj();
	// 返回头结点
	void *GetHead() { return m_Head; }

	// 返回尾结点 Object 指针
	inline T* GetEndObjPoint();
	// 返回尾结点
	void *GetEnd() { return m_End; }

	// 获得结点 Object 指针
	inline T *GetNodeObj(void *Node);

	// 清空链表
	void Clear();

	// GetData()
	// 参数 -	obj 为 Object指针，初始化为 NULL
	//			index 为结点指针，初始化为 NULL，可以循环执行，直到index == NULL
	void GetData(T* &obj,void* &index);

	// 添加结点
	HRESULT Add();
	// 添加结点
	HRESULT Add(T &obj);
	// 插入结点
	HRESULT Insert(void *node,T &obj);

	// 将 src 移到 dst 后面
	HRESULT MoveToNext(void *dst,void *src);
	// 将 src 移到 dst 前面
	HRESULT MoveToPre(void *dst,void *src);

	// 删除 pre 后面的结点
	HRESULT Del_PreNode(void *pre);

	// 删除结点
	HRESULT Del(T *obj);
	// 删除结点
	HRESULT Del(T &obj);

	void Release();
private:
	// 分配空间，返回的是一个排好顺序的 link
	TYPENAME ZLinkEx<T,SIZE,LINKSZ>::link *Alloc(unsigned int Size);

	// 删除结点
	// 参数	-	pre 为前一个结点
	//			node 为待删除结点
	HRESULT Del(TYPENAME ZLinkEx<T,SIZE,LINKSZ>::link *pre,TYPENAME ZLinkEx<T,SIZE,LINKSZ>::link *node);

	// 调试输出
	void DebugLog()	const;
};

template<class T,unsigned int SIZE,unsigned int LINKSZ>
inline ZLinkEx<T,SIZE,LINKSZ>::ZLinkEx()
{
	m_uLen = m_uUsed = 0;
	m_Last = NULL;

	m_End = m_Head = Alloc(SIZE);
	if(m_Head  ==  NULL)
		Debug("ZLink<%d,%d>::ZLink fail!",SIZE,LINKSZ);
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
TYPENAME ZLinkEx<T,SIZE,LINKSZ>::link *ZLinkEx<T,SIZE,LINKSZ>::Alloc(unsigned int Size)
{
	ZASSERT(Size>0);

	link *tmp=NULL;
	link *tmp1;
	unsigned int i=1;

	tmp=new link[Size];
	if(tmp  ==  NULL)
		Debug("ZLink::alloc(%d) fail!",Size);

	tmp1=&tmp[0];

	while(i<Size)
	{
		tmp1->next=&tmp[i++];
		tmp1=tmp1->next;
	}

	m_Last=tmp1;

	m_uLen+=Size;

	m_memory.push_back(tmp);

	return &tmp[0];
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
inline T &ZLinkEx<T,SIZE,LINKSZ>::GetHeadObj()
{
	ZASSERT(m_Head);

	return m_Head->object;
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
inline T *ZLinkEx<T,SIZE,LINKSZ>::GetHeadObjPoint()
{
	ZASSERT(m_Head);

	return &(m_Head->object);
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
inline T *ZLinkEx<T,SIZE,LINKSZ>::GetNodeObj(void *Node)
{
	ZASSERT(Node);

	return ((link *)Node)->object;
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
inline void ZLinkEx<T,SIZE,LINKSZ>::Clear()
{
	m_uUsed = 0;
	m_End = m_Head;
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
void ZLinkEx<T,SIZE,LINKSZ>::GetData(T* &obj,void* &index)
{
	if(m_uUsed  ==  0)
	{
		obj = NULL;
		index = NULL;
	}
	else if(index  ==  m_End)
	{
		index = NULL;
		obj = NULL;
	}
	else if(index  ==  NULL)
	{
		obj = &(m_Head->object);
		index = m_Head->next;
	}
	else
	{
		obj = &(((link *)index)->object);
		index = ((link *)index)->next;
	}

	if(index == m_End)
		index = NULL;
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
inline T *ZLinkEx<T,SIZE,LINKSZ>::GetEndObjPoint()
{
	ZASSERT(m_End);

	return &(m_End->object);
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
HRESULT ZLinkEx<T,SIZE,LINKSZ>::Add()
{
	if(!m_End->next)
	{
		m_End->next=Alloc(LINKSZ);
		if(m_End->next  ==  NULL)
			return ZRet(ZEPHYR_RET_FAILED,"ZLink::Add()");
	}

	m_End = m_End->next;

	m_uUsed++;

	return S_OK;
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
HRESULT ZLinkEx<T,SIZE,LINKSZ>::Add(T &obj)
{
	m_End->object=obj;

	if(!m_End->next)
	{
		m_End->next=Alloc(LINKSZ);
		if(m_End->next  ==  NULL)
			return ZRet(ZEPHYR_RET_FAILED,"ZLink::Add()");
	}

	m_End = m_End->next;

	m_uUsed++;

	return S_OK;
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
HRESULT ZLinkEx<T,SIZE,LINKSZ>::MoveToNext(void *dst,void *src)
{
	link *tmp;
	link *pre = NULL;

	if(src  ==  NULL)
		return E_FAIL;

	if(dst  ==  NULL)
		dst=m_Head;

//find src's pre
	for(tmp=m_Head;tmp != src&&tmp != m_End;tmp=tmp->next)
		pre=tmp;

	if(tmp  ==  m_End)
		return E_FAIL;

//del src
	if(pre  ==  NULL)	//src is head ?
	{
//src is head
		if(m_End  ==  m_Head->next)	//only a node ?
		{
			m_End=m_Head;
		}
		else
		{
			//del head
			m_Head=m_Head->next;
		}
	}
	else if(((link *)src)->next == m_End)	//src is end ?
	{
		pre->next=m_End;
	}
	else
	{
		pre->next=tmp->next;
	}

//check dst
	for(tmp=m_Head;tmp != dst&&tmp != m_End;tmp=tmp->next);

	if(tmp == m_End)
		return E_FAIL;

//move to
	tmp=((link *)dst)->next;
	((link *)dst)->next=(link *)src;
	((link *)src)->next=tmp;

	return S_OK;
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
HRESULT ZLinkEx<T,SIZE,LINKSZ>::MoveToPre(void *dst,void *src)
{
	link *tmp;
	link *pre=NULL;

	if(src == NULL)
		return E_FAIL;

	if(dst == NULL)
		dst=m_Head;

//find src's pre
	for(tmp=m_Head;tmp != src&&tmp != m_End;tmp=tmp->next)
		pre=tmp;

	if(tmp == m_End)
		return E_FAIL;

//del src
	if(pre == NULL)	//src is head ?
	{
//src is head
		if(m_End == m_Head->next)	//only a node ?
		{
			m_End=m_Head;
		}
		else
		{
			//del head
			m_Head=m_Head->next;
		}
	}
	else if(tmp->next == m_End)	//src is end ?
	{
		pre->next=m_End;
	}
	else
	{
		pre->next=tmp->next;
	}

//find dst's pre
	for(tmp=m_Head;tmp != dst&&tmp != m_End;tmp=tmp->next)
		pre=tmp;

	if(tmp == m_End)
		return E_FAIL;

//move to
	if(pre == NULL)	//dst is head ?
	{
//dst is head
		m_Head=src;
		m_Head->next=dst;
	}
	else
	{
		pre->next=(link *)src;
		((link *)src)->next=(link *)dst;
	}

	return S_OK;
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
HRESULT ZLinkEx<T,SIZE,LINKSZ>::Insert(void *node,T &obj)
{
	link *tmp=m_End;

	m_End->object=obj;

	if(Add() != S_OK)
		return E_FAIL;

	return MoveToNext(m_Head,tmp);
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
HRESULT ZLinkEx<T,SIZE,LINKSZ>::Del(TYPENAME ZLinkEx<T,SIZE,LINKSZ>::link *pre,TYPENAME ZLinkEx<T,SIZE,LINKSZ>::link *node)
{
	m_uUsed--;

	if(pre == NULL||node == m_Head)
	{
//if del head
		if(m_End == m_Head->next)
		{
			//if only a node
			m_End=m_Head;
		}
		else
		{
			//move head to last
			m_Last->next=m_Head;
			m_Last=m_Last->next;

			m_Head=m_Head->next;
			m_Last->next=NULL;
		}
	}
	else if(node->next == m_End)
	{
//		pre->next=m_End;

		m_End=node;
	}
	else
	{
		pre->next=node->next;
		m_Last->next=node;
		node->next=NULL;
		m_Last=m_Last->next;
	}

	return S_OK;
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
HRESULT ZLinkEx<T,SIZE,LINKSZ>::Del(T *obj)
{
	link *tmp,*pre=NULL;

	ZASSERT(obj);

	if(m_uUsed == 0)
	{
#ifdef _ZEPHYR_LINK_DEBUG
		return ZRet(ZEPHYR_RET_FAILED,"ZLink::Del() Empty");
#else
		return E_FAIL;
#endif
	}

	for(tmp=m_Head;&(tmp->object) != obj && tmp != m_End;pre=tmp,tmp=tmp->next);

	if(&(tmp->object) != obj)
	{
#ifdef _ZEPHYR_LINK_DEBUG
		return ZRet(ZEPHYR_RET_FAILED,"ZLink::Del() Can't find obj");
#else
		return E_FAIL;
#endif
	}

	//m_uUsed--;

	return Del(pre,tmp);
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
HRESULT ZLinkEx<T,SIZE,LINKSZ>::Del(T &obj)
{
	link *tmp,*pre=NULL;

	if(m_uUsed == 0)
	{
#ifdef _ZEPHYR_LINK_DEBUG
		return ZRet(ZEPHYR_RET_FAILED,"zlink::Del() empty");
#else
		return E_FAIL;
#endif
	}

	for(tmp=m_Head;tmp->object != obj&&tmp != m_End;pre=tmp,tmp=tmp->next);

	if(tmp == m_End)
	{
#ifdef _ZEPHYR_LINK_DEBUG
		return ZRet(ZEPHYR_RET_FAILED,"zlink::Del() Can't find obj");
#else
		return E_FAIL;
#endif
	}

	//m_uUsed--;

	return Del(pre,tmp);
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
void ZLinkEx<T,SIZE,LINKSZ>::Release()
{
#ifdef _ZEPHYR_LINK_DEBUG
	Debug("ZLinkEx 0x%.8x Release!",this);
	DebugLog();
#endif

	if(!m_Head)
		return ;

	m_Head = m_End = m_Last = NULL;

	m_uLen = 0;
	m_uUsed = 0;

	for(Array::size_type i = 0; i < m_memory.size(); i++)
	{
		if(m_memory[i] != NULL)
			delete[] m_memory[i];
	}

	m_memory.clear();
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
void ZLinkEx<T,SIZE,LINKSZ>::DebugLog() const
{
#ifdef _ZEPHYR_LINK_DEBUG
	unsigned int i=0;
	link *tmp=m_Head,*pre=NULL;

	while(tmp)
	{
		pre=tmp;

		tmp=tmp->next;

		i++;
	}

	if(m_Last != pre)
		OutputLog("ZLink debug:check error!");

	OutputLog("ZLink debug:total size is %d(%d)",m_uLen,i);

	if(m_uUsed != 0)
	{
		i=0;
		tmp=m_Head;

		while(tmp != m_End)
		{
			tmp=tmp->next;
			i++;
		}

		OutputLog("ZLink debug:used size is %d(%d)",m_uUsed,i);
	}
#endif
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
HRESULT  ZLinkEx<T,SIZE,LINKSZ>::Del_PreNode(void* pre)
{
	if(m_uUsed == 0)
		return E_FAIL;

	//m_uUsed--;

	if(pre == NULL)
		return Del(NULL,m_Head);
	else
		return Del((link *)pre,((link*)pre)->next);
}

//////////////////////////////////////////////////////////////////////
//	ZDLinkEx

template<class T,unsigned int SIZE = 1024,unsigned int LINKSZ = 64>
class ZDLinkEx{
public:
	struct link{
		T object;
		link *pre;
		link *next;

		link()
		{
			next = NULL;
			pre = NULL;
		}
	};

	typedef std::vector<link*> Array;
private:
	link *m_Head,*m_End,*m_Last;	//link head & used end & alloc end
	unsigned int m_uLen;			//total length
	unsigned int m_uUsed;			//used length
	Array			m_memory;
private:
	TYPENAME ZDLinkEx<T,SIZE,LINKSZ>::link *Alloc(unsigned int Size);

	HRESULT Del(TYPENAME ZDLinkEx<T,SIZE,LINKSZ>::link *node);
public:
	inline ZDLinkEx();
	~ZDLinkEx() { Release(); }

	unsigned int GetLen() const { return m_uLen; }
	unsigned int GetUsed() const { return m_uUsed; }

	inline T *GetHeadObjPoint();
	inline T &GetHeadObj();
	void *GetHead() { return m_Head; }

	inline T* GetEndObjPoint();
	void *GetEnd() { return m_End; }

	inline T *GetNodeObj(void *Node);

	void Clear();

	void GetData(T* &obj,void* &index);

	HRESULT Add();
	HRESULT Add(T &obj);
	HRESULT Insert(void *node,T &obj);

	HRESULT MoveToNext(void *dst,void *src);
	HRESULT MoveToPre(void *dst,void *src);

	HRESULT Del(T *obj);
	HRESULT Del(T &obj);
	inline HRESULT Del(void *index);

	void* Pre(void* node) { return ((link*)node)->pre; }

	void Release();

	void DebugLog()	const;
};

template<class T,unsigned int SIZE,unsigned int LINKSZ>
inline ZDLinkEx<T,SIZE,LINKSZ>::ZDLinkEx()
{
	m_uLen = m_uUsed = 0;
	m_Last = NULL;

	m_End = m_Head = Alloc(SIZE);
	if(m_Head  ==  NULL)
		Debug("ZLink<%d,%d>::ZLink fail!",SIZE,LINKSZ);
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
TYPENAME ZDLinkEx<T,SIZE,LINKSZ>::link *ZDLinkEx<T,SIZE,LINKSZ>::Alloc(unsigned int Size)
{
	ZASSERT(Size > 0);

	link *tmp = NULL;
	link *tmp1;
	link *pre = m_Last;
	unsigned int i = 1;

	tmp = new link[Size];
	if(tmp  ==  NULL)
		Debug("ZLink::alloc(%d) fail!",Size);

	tmp1 = &tmp[0];

	while(i<Size)
	{
		tmp1->pre = pre;
		tmp1->next = &tmp[i++];
		pre = tmp1;
		tmp1 = tmp1->next;
	}

	tmp1->pre = pre;

	m_Last = tmp1;

	m_uLen += Size;

	m_memory.push_back(tmp);

	return &tmp[0];
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
inline T &ZDLinkEx<T,SIZE,LINKSZ>::GetHeadObj()
{
	ZASSERT(m_Head);

	return m_Head->object;
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
inline T *ZDLinkEx<T,SIZE,LINKSZ>::GetHeadObjPoint()
{
	ZASSERT(m_Head);

	return &(m_Head->object);
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
inline T *ZDLinkEx<T,SIZE,LINKSZ>::GetNodeObj(void *Node)
{
	ZASSERT(Node);

	return &((link *)Node)->object;
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
inline void ZDLinkEx<T,SIZE,LINKSZ>::Clear()
{
	m_uUsed = 0;
	m_End = m_Head;
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
void ZDLinkEx<T,SIZE,LINKSZ>::GetData(T* &obj,void* &index)
{
	if(m_uUsed  ==  0)
	{
		obj = NULL;
		index = NULL;
	}
	else if(index  ==  m_End)
	{
		index = NULL;
		obj = NULL;
	}
	else if(index  ==  NULL)
	{
		obj = &(m_Head->object);
		index = m_Head->next;
	}
	else
	{
		obj = &(((link *)index)->object);
		index = ((link *)index)->next;
	}

	if(index == m_End)
		index = NULL;
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
inline T *ZDLinkEx<T,SIZE,LINKSZ>::GetEndObjPoint()
{
	ZASSERT(m_End);

	return &(m_End->object);
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
HRESULT ZDLinkEx<T,SIZE,LINKSZ>::Add()
{
	if(!m_End->next)
	{
		m_End->next=Alloc(LINKSZ);
		if(m_End->next  ==  NULL)
			return ZRet(ZEPHYR_RET_FAILED,"ZLink::Add()");
	}

	m_End = m_End->next;

	m_uUsed++;

	return S_OK;
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
HRESULT ZDLinkEx<T,SIZE,LINKSZ>::Add(T &obj)
{
	m_End->object=obj;

	if(!m_End->next)
	{
		m_End->next=Alloc(LINKSZ);
		if(m_End->next  ==  NULL)
			return ZRet(ZEPHYR_RET_FAILED,"ZLink::Add()");
	}

	m_End = m_End->next;

	m_uUsed++;

	return S_OK;
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
HRESULT ZDLinkEx<T,SIZE,LINKSZ>::MoveToNext(void *dst,void *src)
{
	ZASSERT(m_uUsed >= 2);
	ZASSERT(dst != src);

//	link *tmp;

	if(src  ==  NULL)
		return E_FAIL;

	if(dst  ==  NULL)
		dst = m_Head;

	if(((link *)dst)->next == src)
		return S_OK;

	if(((link *)src)->pre == NULL)	//if src is head
	{
		if(((link *)src)->next == ((link *)dst))
		{
			m_Head = ((link *)dst);
			m_Head->pre = NULL;

			((link *)dst)->next->pre = ((link *)src);
			((link *)src)->next = ((link *)dst)->next;

			((link *)dst)->next = ((link *)src);
			((link *)src)->pre = ((link *)dst);
		}
		else
		{
			m_Head = ((link *)src)->next;
			m_Head->pre = NULL;

			((link *)dst)->next->pre = ((link *)src);
			((link *)src)->next = ((link *)dst)->next;

			((link *)dst)->next = ((link *)src);
			((link *)src)->pre = ((link *)dst);
		}
	}
	else if(((link *)src)->next == ((link *)dst))
	{
		((link *)src)->pre->next = ((link *)dst);
		((link *)dst)->pre = ((link *)src)->pre;

		((link *)dst)->next->pre = ((link *)src);
		((link *)src)->next = ((link *)dst)->next;

		((link *)dst)->next = ((link *)src);
		((link *)src)->pre = ((link *)dst);
	}
	else
	{
		((link *)src)->pre->next = ((link *)src)->next;
		((link *)src)->next->pre = ((link *)src)->pre;

		((link *)dst)->next->pre = ((link *)src);
		((link *)src)->next = ((link *)dst)->next;

		((link *)dst)->next = ((link *)src);
		((link *)src)->pre = ((link *)dst);
	}

	return S_OK;
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
HRESULT ZDLinkEx<T,SIZE,LINKSZ>::MoveToPre(void *dst,void *src)
{
	ZASSERT(m_uUsed >= 2);
	ZASSERT(dst != src);

//	link *tmp;

	if(src == NULL)
		return E_FAIL;

	if(dst == NULL)
		dst = m_Head;

	if(((link *)src)->next == dst)
		return S_OK;

	if(((link *)src)->pre == NULL)	//if src is head
	{
		m_Head = ((link *)src)->next;
		m_Head->pre = NULL;

//		tmp = ((link *)dst)->pre;

		((link *)dst)->pre->next = ((link *)src);
		((link *)src)->pre = ((link *)dst)->pre;

		((link *)dst)->pre = ((link *)src);
		((link *)src)->next = ((link *)dst);
	}
	else if(((link *)dst)->pre == NULL)	//if dst is head
	{
		if(((link *)dst)->next == src)
		{
			m_Head = ((link *)src);
			m_Head->pre = NULL;

//			tmp = ((link *)src)->next;

			((link *)dst)->next = ((link *)src)->next;
			((link *)src)->next->pre = ((link *)dst);

			((link *)src)->next = ((link *)dst);
			((link *)dst)->pre = ((link *)src);
		}
		else
		{
//			tmp = ((link *)src)->pre;

			((link *)src)->pre->next = ((link *)src)->next;
			((link *)src)->next->pre = ((link *)src)->pre;

			((link *)src)->next = ((link *)dst);
			((link *)dst)->pre = ((link *)src);

			m_Head = ((link *)src);
			m_Head->pre = NULL;
		}
	}
	else if(((link *)dst)->next == src)
	{
		((link *)dst)->pre->next = ((link *)src);
		((link *)src)->pre = ((link *)dst)->pre;

		((link *)dst)->next = ((link *)src)->next;
		((link *)src)->next->pre = ((link *)dst);

		((link *)src)->next = ((link *)dst);
		((link *)dst)->pre = ((link *)src);
	}
	else
	{
		((link *)src)->pre->next = ((link *)src)->next;
		((link *)src)->next->pre = ((link *)src)->pre;

		((link *)dst)->pre->next = ((link *)src);
		((link *)src)->pre = ((link *)dst)->pre;

		((link *)dst)->pre = ((link *)src);
		((link *)src)->next = ((link *)dst);
	}

	return S_OK;
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
HRESULT ZDLinkEx<T,SIZE,LINKSZ>::Insert(void *node,T &obj)
{
	link *tmp=m_End;

	m_End->object=obj;

	if(Add() != S_OK)
		return E_FAIL;

	return MoveToNext(m_Head,tmp);
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
HRESULT ZDLinkEx<T,SIZE,LINKSZ>::Del(TYPENAME ZDLinkEx<T,SIZE,LINKSZ>::link *node)
{
	m_uUsed--;

	if(node->pre == NULL || node == m_Head)	//if del head
	{
		if(m_End == m_Head->next)	//if only a node
		{
			m_End = m_Head;
		}
		else
		{
			//move head to last
			m_Last->next = m_Head;
			m_Head->pre = m_Last;
			m_Last = m_Last->next;

			m_Head = m_Head->next;
			m_Head->pre = NULL;
			m_Last->next = NULL;
		}
	}
	else if(node->next == m_End)	//if del end node
	{
		m_End = node;
	}
	else	//if normal node
	{
		node->pre->next = node->next;
		node->next->pre = node->pre;

		m_Last->next = node;
		node->pre = m_Last;

		node->next = NULL;

		m_Last = m_Last->next;
	}

	return S_OK;
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
HRESULT ZDLinkEx<T,SIZE,LINKSZ>::Del(T *obj)
{
	link *tmp;

	ZASSERT(obj);

	if(m_uUsed == 0)
	{
#ifdef _ZEPHYR_LINK_DEBUG
		return ZRet(ZEPHYR_RET_FAILED,"ZLink::Del() Empty");
#else
		return E_FAIL;
#endif
	}

	for(tmp=m_Head;&(tmp->object) != obj && tmp != m_End;tmp=tmp->next);

	if(&(tmp->object) != obj)
	{
#ifdef _ZEPHYR_LINK_DEBUG
		return ZRet(ZEPHYR_RET_FAILED,"ZLink::Del() Can't find obj");
#else
		return E_FAIL;
#endif
	}

//	m_uUsed--;

	return Del(tmp);
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
HRESULT ZDLinkEx<T,SIZE,LINKSZ>::Del(T &obj)
{
	link *tmp;

	if(m_uUsed == 0)
	{
#ifdef _ZEPHYR_LINK_DEBUG
		return ZRet(ZEPHYR_RET_FAILED,"zlink::Del() empty");
#else
		return E_FAIL;
#endif
	}

	for(tmp=m_Head;tmp->object != obj&&tmp != m_End;tmp=tmp->next);

	if(tmp == m_End)
	{
#ifdef _ZEPHYR_LINK_DEBUG
		return ZRet(ZEPHYR_RET_FAILED,"zlink::Del() Can't find obj");
#else
		return E_FAIL;
#endif
	}

//	m_uUsed--;

	return Del(tmp);
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
void ZDLinkEx<T,SIZE,LINKSZ>::Release()
{
#ifdef _ZEPHYR_LINK_DEBUG
	Debug("ZDLinkEx 0x%.8x Release!",this);
	DebugLog();
#endif

	if(!m_Head)
		return ;

	m_Head = m_End = m_Last = NULL;

	m_uLen = 0;
	m_uUsed = 0;

	for(Array::size_type i = 0; i < m_memory.size(); i++)
	{
		if(m_memory[i] != NULL)
			delete[] m_memory[i];
	}

	m_memory.clear();
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
void ZDLinkEx<T,SIZE,LINKSZ>::DebugLog() const
{
#ifdef _ZEPHYR_LINK_DEBUG
	unsigned int i=0;
	link *tmp=m_Head,*pre=NULL;

	while(tmp)
	{
		pre=tmp;

		tmp=tmp->next;

		i++;
	}

	if(m_Last != pre)
		OutputLog("ZLink debug:check error!");

	OutputLog("ZLink debug:total size is %d(%d)",m_uLen,i);

	if(m_uUsed != 0)
	{
		i=0;
		tmp=m_Head;

		while(tmp != m_End)
		{
			tmp=tmp->next;
			i++;
		}

		OutputLog("ZLink debug:used size is %d(%d)",m_uUsed,i);
	}
#endif
}

template<class T,unsigned int SIZE,unsigned int LINKSZ>
inline HRESULT ZDLinkEx<T,SIZE,LINKSZ>::Del(void *index)
{
	ZASSERT(index);

	Del((ZDLinkEx<T,SIZE,LINKSZ>::link *)index);

	return S_OK;
}

//////////////////////////////////////////////////////////////////////
// ZLink_2
// 说明：单纯的链表，结点实际内存空间自己控制
//		链表长度可以根据实际使用程度自行调整

// 算法介绍
// 有3个结点指针，一个始终指向链表的头结点，一个指向已分配空间的整个链表的尾结点
// Last，另外一个指向现在可以使用的链表结点End

// 增加链表结点 直接给End结点赋值，End结点后移
// 删除链表结点 连接要删除结点前后的结点，然后将它移动到Last结点的位置，如果刚好删
// 除End结点前面的结点，则将End前移

// 外部遍历结点可以通过 GetData()

template<class T,unsigned int SIZE = 1024,unsigned int LINKSZ = 64>
class ZLink_2{
public:
	struct Node{
		T		*object;
		Node	*next;

		Node()
		{
			object = NULL;
			next = NULL;
		}
	};

	typedef Node*	LPNode;

	typedef std::vector<LPNode> Array;
private:
	LPNode			m_Head,m_End,m_Last;		// link head & used end & alloc end
	unsigned int	m_uLen;						// total length
	unsigned int	m_uUsed;					// used length
	Array			m_memory;
public:
	// 构造函数
	inline ZLink_2();
	// 析构函数
	~ZLink_2() { Release(); }

	// 资源释放
	void Release();

	// 获得链表大小
	unsigned int GetLen() const { return m_uLen; }
	// 获得链表使用度
	unsigned int GetUsed() const { return m_uUsed; }

	// 获得头结点Object
	inline T* GetHeadObj();
	// 获得头结点
	TYPENAME ZLink_2<T,SIZE,LINKSZ>::LPNode GetHead() { return m_Head; }

	// 获得结点的 Object
	T* GetNodeObj(void *Node);

	// GetData()
	// 参数 -	obj 为 Object指针，初始化为 NULL
	//			index 为结点指针，初始化为 NULL，可以循环执行，直到index == NULL
	void GetData(T* &obj,TYPENAME ZLink_2<T,SIZE,LINKSZ>::LPNode& index);

	// 清空链表
	inline void Clear();

	// 添加 Object
	TYPENAME ZLink_2<T,SIZE,LINKSZ>::LPNode Add(T *obj);

	// 删除 Object
	HRESULT Del(T *obj);
	// 删除 Object
	HRESULT Del(T &obj);
private:
	// 分配空间，返回的是一个排好顺序的 link
	TYPENAME ZLink_2<T,SIZE,LINKSZ>::LPNode Alloc(unsigned int Size);

	// 删除结点
	// 参数	-	pre 为前一个结点
	//			node 为待删除结点
	HRESULT Del(TYPENAME ZLink_2<T,SIZE,LINKSZ>::LPNode pre,TYPENAME ZLink_2<T,SIZE,LINKSZ>::LPNode node);

	// 调试输出
	void DebugLog()	const;
};

// 构造函数
template<class T,unsigned int SIZE,unsigned int LINKSZ>
inline ZLink_2<T,SIZE,LINKSZ>::ZLink_2()
{
	m_uLen = m_uUsed = 0;
	m_Last = NULL;

	m_End = m_Head = Alloc(SIZE);
	if(m_Head == NULL)
		Debug("ZLink<%d,%d>::ZLink fail!",SIZE,LINKSZ);
}

// 分配空间，返回的是一个排好顺序的 link
template<class T,unsigned int SIZE,unsigned int LINKSZ>
TYPENAME ZLink_2<T,SIZE,LINKSZ>::LPNode ZLink_2<T,SIZE,LINKSZ>::Alloc(unsigned int Size)
{
	ZASSERT(Size > 0);

	LPNode tmp = NULL;
	LPNode tmp1;
	unsigned int i = 1;

	tmp = new Node[Size];
	if(tmp == NULL)
	{
		Debug("ZLink::alloc(%d) fail!",Size);

		return NULL;
	}

	tmp1 = &tmp[0];

	while(i < Size)
	{
		tmp1->next = &tmp[i++];
		tmp1 = tmp1->next;
	}

	m_Last = tmp1;

	m_uLen += Size;

	m_memory.push_back(tmp);

	return &tmp[0];
}

// 获得头结点Object
template<class T,unsigned int SIZE,unsigned int LINKSZ>
inline T *ZLink_2<T,SIZE,LINKSZ>::GetHeadObj()
{
	ZASSERT(m_Head != NULL);

	return m_Head->object;
}

// 获得结点的 Object
template<class T,unsigned int SIZE,unsigned int LINKSZ>
inline T *ZLink_2<T,SIZE,LINKSZ>::GetNodeObj(void *Node)
{
	ZASSERT(Node != NULL);

	return ((link *)Node)->object;
}

// GetData()
// 参数 -	obj 为 Object指针，初始化为 NULL
//			index 为结点指针，初始化为 NULL，可以循环执行，直到index == NULL
template<class T,unsigned int SIZE,unsigned int LINKSZ>
void ZLink_2<T,SIZE,LINKSZ>::GetData(T* &obj,TYPENAME ZLink_2<T,SIZE,LINKSZ>::LPNode& index)
{
	if(m_uUsed == 0 || index == m_End)
	{
		index = NULL;
		obj = NULL;
	}
	else if(index == NULL)
	{
		obj = m_Head->object;
		index = m_Head->next;
	}
	else
	{
		obj = ((link *)index)->object;
		index = ((link *)index)->next;
	}
}

// 添加 Object
template<class T,unsigned int SIZE,unsigned int LINKSZ>
TYPENAME ZLink_2<T,SIZE,LINKSZ>::LPNode ZLink_2<T,SIZE,LINKSZ>::Add(T *obj)
{
	ZASSERT(obj != NULL);

	m_End->object = obj;

	if(m_End->next == NULL)
	{
		m_End->next = Alloc(LINKSZ);
		if(m_End->next == NULL)
		{
			ZRet(ZEPHYR_RET_FAILED,"ZLink::Add()");

			return NULL;
		}
	}

	LPNode tmp = m_End;

	m_End = m_End->next;

	m_uUsed++;

	return tmp;
}

// 删除结点
// 参数	-	pre 为前一个结点
//			node 为待删除结点
template<class T,unsigned int SIZE,unsigned int LINKSZ>
HRESULT ZLink_2<T,SIZE,LINKSZ>::Del(TYPENAME ZLink_2<T,SIZE,LINKSZ>::LPNode pre,TYPENAME ZLink_2<T,SIZE,LINKSZ>::LPNode node)
{
	m_uUsed--;

	if(pre == NULL||node == m_Head)	//if del head
	{
		node->object = NULL;

		if(m_End == m_Head->next)	//if only a node
			m_End = m_Head;
		else
		{
			//move head to last
			m_Last->next = m_Head;
			m_Last = m_Last->next;

			m_Head = m_Head->next;
			m_Last->next = NULL;
		}
	}
	else if(node->next == m_End)
	{
		node->object = NULL;

		m_End = node;
	}
	else
	{
		node->object = NULL;

		pre->next = node->next;
		m_Last->next = node;
		node->next = NULL;
		m_Last = m_Last->next;
	}

	return S_OK;
}

// 删除 Object
template<class T,unsigned int SIZE,unsigned int LINKSZ>
HRESULT ZLink_2<T,SIZE,LINKSZ>::Del(T *obj)
{
	ZASSERT(obj != NULL);

	LPNode tmp,pre = NULL;

	if(m_uUsed  ==  0)
	{
#ifdef _ZEPHYR_LINK_DEBUG
		return ZRet(ZEPHYR_RET_FAILED,"ZLink::Del() Empty");
#else
		return E_FAIL;
#endif
	}

	//m_uUsed--;

	for(tmp = m_Head; tmp->object != obj && tmp != m_End; pre = tmp,tmp = tmp->next);

	if(tmp->object != obj)
	{
#ifdef _ZEPHYR_LINK_DEBUG
		return ZRet(ZEPHYR_RET_FAILED,"ZLink::Del() Can't find obj");
#else
		return E_FAIL;
#endif
	}

	return Del(pre,tmp);
}

// 删除 Object
template<class T,unsigned int SIZE,unsigned int LINKSZ>
HRESULT ZLink_2<T,SIZE,LINKSZ>::Del(T &obj)
{
	Node *tmp,*pre = NULL;

	if(m_uUsed  ==  0)
	{
#ifdef _ZEPHYR_LINK_DEBUG
		return ZRet(ZEPHYR_RET_FAILED,"zlink::Del() empty");
#else
		return E_FAIL;
#endif
	}

	//m_uUsed--;

	for(tmp=m_Head;*(tmp->object) != obj&&tmp != m_End;pre=tmp,tmp=tmp->next);

	if(*(tmp->object) != obj)
	{
#ifdef _ZEPHYR_LINK_DEBUG
		return ZRet(ZEPHYR_RET_FAILED,"zlink::Del() Can't find obj");
#else
		return E_FAIL;
#endif
	}

	return Del(pre,tmp);
}

// 资源释放
template<class T,unsigned int SIZE,unsigned int LINKSZ>
void ZLink_2<T,SIZE,LINKSZ>::Release()
{
#ifdef _ZEPHYR_LINK_DEBUG
	DebugLog();
#endif

	if(m_Head == NULL)
		return ;

	m_Head = m_End = m_Last = NULL;

	m_uLen = 0;
	m_uUsed = 0;

	for(Array::size_type i = 0; i < m_memory.size(); i++)
	{
		if(m_memory[i] != NULL)
			delete[] m_memory[i];
	}

	m_memory.clear();
}

// 清空链表
template<class T,unsigned int SIZE,unsigned int LINKSZ>
inline void ZLink_2<T,SIZE,LINKSZ>::Clear()
{
	m_uUsed = 0;
	m_End = m_Head;
}

// 调试输出
template<class T,unsigned int SIZE,unsigned int LINKSZ>
void ZLink_2<T,SIZE,LINKSZ>::DebugLog() const
{
#ifdef _ZEPHYR_LINK_DEBUG
	unsigned int i = 0;
	link *tmp = m_Head,*pre = NULL;

	while(tmp != NULL)
	{
		pre = tmp;

		tmp = tmp->next;

		i++;
	}

	if(m_Last != pre)
		OutputLog("ZLink debug:check error!");

	OutputLog("ZLink debug:total size is %d(%d)",m_uLen,i);

	if(m_uUsed != 0)
	{
		i = 0;
		tmp = m_Head;

		while(tmp != m_End)
		{
			tmp = tmp->next;
			i++;
		}

		OutputLog("ZLink debug:used size is %d(%d)",m_uUsed,i);
	}
#endif
}

#endif//_ZEPHYR_LINK_H