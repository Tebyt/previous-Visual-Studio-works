/*
							Zephyr Engine v3.0

								by �Ժ���(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	ZArray.h

							Describe:	��̬����

							Author:		�Ժ���(xueren)

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
// ˵����ģ�嶯̬������

// �ڲ���־λ
const DWORD	ZARRAY_STATE_RELEASE		=	0x01;	// �Ƿ��ͷ���Դ

template<class T,unsigned int SIZE>
class ZArray{
private:
	T				*m_Array;		// ��Դ
	unsigned int	m_Total;		// ������
	ZState_DWord	m_dwState;		// �ڲ���־λ
public:
	// ȱʡ���캯��
	inline ZArray();
	// ��������ռ�Ĺ��캯��
	inline ZArray(T *dat,unsigned int size);
	// ��������
	~ZArray() { Release(); }

	// ��Դ�ͷ�
	inline void Release();

	// ����ռ�
	inline HRESULT Alloc(unsigned int size);
	// ���·���ռ�
	inline HRESULT Realloc(unsigned int size);

	// ���������
	inline T &operator[](const unsigned int index);

	// ���������
	unsigned int GetTotalSize()	const { return m_Total; }

	// ֱ�ӻ�������׵�ַ
	T *GetData() { return m_Array; }
};

// ȱʡ���캯��
template<class T,unsigned int SIZE>
inline ZArray<T,SIZE>::ZArray()
{
	m_dwState += ZARRAY_STATE_RELEASE;

	m_Array = NULL;
	m_Total = 0;

	if(SIZE != 0)
		Alloc(SIZE);
}

// ��������ռ�Ĺ��캯��
template<class T,unsigned int SIZE>
inline ZArray<T,SIZE>::ZArray(T *dat,unsigned int size)
{
	ZASSERT(dat != NULL && size >= 0)

	m_Array = dat;
	m_Total = size;
}

// ����ռ�
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

// ���·���ռ�
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

// ��Դ�ͷ�
template<class T,unsigned int SIZE>
inline void ZArray<T,SIZE>::Release()
{
	if(m_Array != NULL && m_dwState.Has(ZARRAY_STATE_RELEASE))
		free(m_Array);

	m_Array = NULL;

	m_Total = 0;
}

// ���������
template<class T,unsigned int SIZE>
inline T& ZArray<T,SIZE>::operator[](const unsigned int index) 
{
	ZASSERT(index >= 0 && index < m_Total);

	return m_Array[index]; 
}

#endif//_ZEPHYR_BASE_ARRAY_H