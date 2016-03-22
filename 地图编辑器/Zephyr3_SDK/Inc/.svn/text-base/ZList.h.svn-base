//ZList.h
//列表
//write by zhs007			y2k3.4.11

#ifndef ZEPHYR_BASE_LIST_H
#define ZEPHYR_BASE_LIST_H

#include <Zephyr.h>

#include <ZArray.h>

///////////////////////////////////////////////////////////////////////////////
//	ZList

template<class T,unsigned int SIZE,unsigned int ADD_SIZE = SIZE>
class ZList{
private:
	ZArray<T,SIZE>	m_List;
	unsigned int	m_Used;
public:
	ZList() { m_Used = 0; }
	ZList(T *dat,unsigned int size,unsigned int used) : m_List(dat,size) { m_Used = used; }

	//在尾部增加列表单元
	inline HRESULT Add(T &obj);
	//增加一个单元
	void Add() { m_Used++; }
	//删除对象
	inline void Del(unsigned int index);
	//dst <---> src
	inline void Change(unsigned int dst,unsigned int src);

	//获得尾部单元指针
	inline T* GetEndObjPoint();

	//删除最后一个结点
	inline T* DelLastObj();

	//清空
	void Clear() { m_Used = 0; }

	//获得已经使用到的个数
	unsigned int GetUsed() const { return m_Used; }

	T& operator[](const unsigned int index) { return m_List[index]; }

	T* GetData() { return m_List.GetData(); }

	T& GetData(unsigned int index) { return m_List[index]; }

	unsigned int GetTotalSize()	const { return m_List.GetTotalSize(); }

	// 是否满了
	bool IsFull() { return m_Used >= m_List.GetTotalSize(); }
};

template<class T,unsigned int SIZE,unsigned int ADD_SIZE>
inline HRESULT ZList<T,SIZE,ADD_SIZE>::Add(T &obj)
{
	if(m_Used >= m_List.GetTotalSize())
	{
		if(m_List.Realloc(m_List.GetTotalSize()+ADD_SIZE) != S_OK)
			return ZRet(E_FAIL,"ZList::Add() fail!");
	}
	
	m_List[m_Used++] = obj;

	return S_OK;
}

//删除对象
template<class T,unsigned int SIZE,unsigned int ADD_SIZE>
inline void ZList<T,SIZE,ADD_SIZE>::Del(unsigned int index)
{
	ZASSERT(index < m_Used);

	for(;index<m_Used-1;index++)
		m_List[index] = m_List[index+1];

	m_Used--;
}

//dst <---> src
template<class T,unsigned int SIZE,unsigned int ADD_SIZE>
inline void ZList<T,SIZE,ADD_SIZE>::Change(unsigned int dst,unsigned int src)
{
	ZASSERT(dst < m_Used && src < m_Used);

	T t = m_List[dst];
	m_List[dst] = m_List[src];
	m_List[src] = t;
}

template<class T,unsigned int SIZE,unsigned int ADD_SIZE>
inline T* ZList<T,SIZE,ADD_SIZE>::GetEndObjPoint()
{
	if(m_Used >= m_List.GetTotalSize())
	{
		if(m_List.Realloc(m_List.GetTotalSize()+ADD_SIZE) != S_OK)
			return NULL;
	}

	return &m_List[m_Used];
}

//删除最后一个结点
template<class T,unsigned int SIZE,unsigned int ADD_SIZE>
inline T* ZList<T,SIZE,ADD_SIZE>::DelLastObj()
{
	return m_Used > 0 ? &m_List[--m_Used] : NULL;
}

#endif//ZEPHYR_BASE_LIST_H