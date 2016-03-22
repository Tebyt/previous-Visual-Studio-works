/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	ZArray.h

							Describe:	动态数组

							Author:		赵洪松(xueren)

							CreateTime: 2003.04.11
							UpdateTime: 2003.08.20
*/

#ifndef _ZEPHYR_BASE_ARRAY_H
#define _ZEPHYR_BASE_ARRAY_H

#include <Zephyr.h>

#include <ZDebug.h>
#include <ZState.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////
// ZArray
// 说明：模板动态数组类

// 内部标志位
const DWORD	ZARRAY_STATE_RELEASE		=	0x01;	// 是否释放资源

template<class T,unsigned int SIZE>
class ZArray{
private:
	T				*m_Array;		// 资源
	unsigned int	m_Total;		// 总容量
	ZState_DWord	m_dwState;		// 内部标志位
public:
	// 缺省构造函数
	inline ZArray();
	// 给定分配空间的构造函数
	inline ZArray(T *dat,unsigned int size);
	// 析构函数
	~ZArray() { Release(); }

	// 资源释放
	inline void Release();

	// 分配空间
	inline HRESULT Alloc(unsigned int size);
	// 重新分配空间
	inline HRESULT Realloc(unsigned int size);

	// 数组操作符
	inline T &operator[](const unsigned int index);

	// 获得总容量
	unsigned int GetTotalSize()	const { return m_Total; }

	// 直接获得数组首地址
	T *GetData() { return m_Array; }
};

// 缺省构造函数
template<class T,unsigned int SIZE>
inline ZArray<T,SIZE>::ZArray()
{
	m_dwState += ZARRAY_STATE_RELEASE;

	m_Array = NULL;
	m_Total = 0;

	if(SIZE != 0)
		Alloc(SIZE);
}

// 给定分配空间的构造函数
template<class T,unsigned int SIZE>
inline ZArray<T,SIZE>::ZArray(T *dat,unsigned int size)
{
	ZASSERT(dat != NULL && size >= 0)

	m_Array = dat;
	m_Total = size;
}

// 分配空间
template<class T,unsigned int SIZE>
inline HRESULT ZArray<T,SIZE>::Alloc(unsigned int size)
{
	m_Array = (T *)malloc(size * sizeof(T));
	if(m_Array == NULL)
		return ZRet(E_FAIL,"ZArray::Alloc(%d) fail!",size);
/*
	for(unsigned int i = 0; i < size; i++)
	{
		new((void *)((BYTE *)m_Array + i * sizeof(T))) T;
	}
*/
	m_Total = size;

	return S_OK;
}

// 重新分配空间
template<class T,unsigned int SIZE>
inline HRESULT ZArray<T,SIZE>::Realloc(unsigned int size)
{
	if(size == m_Total)
		return ZRet(E_FAIL,"ZArray::Realloc(%d) require size == cur size!",size);

	m_Array = (T *)::realloc(m_Array,size * sizeof(T));
	if(m_Array == NULL)
		return ZRet(E_FAIL,"ZArray::Realloc(%d) fail!",size);

	m_Total = size;

	return S_OK;
}

// 资源释放
template<class T,unsigned int SIZE>
inline void ZArray<T,SIZE>::Release()
{
	if(m_Array != NULL && m_dwState.Has(ZARRAY_STATE_RELEASE))
		free(m_Array);

	m_Array = NULL;

	m_Total = 0;
}

// 数组操作符
template<class T,unsigned int SIZE>
inline T& ZArray<T,SIZE>::operator[](const unsigned int index) 
{
	ZASSERT(index >= 0 && index < m_Total);

	return m_Array[index]; 
}

#endif//_ZEPHYR_BASE_ARRAY_H