/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	ZArray2.h

							Describe:	动态数组

							Author:		赵洪松(xueren)

							CreateTime: 2003.12.24
							UpdateTime:
*/

#ifndef _ZEPHYR_3_ARRAY_2_H
#define _ZEPHYR_3_ARRAY_2_H

#include <Zephyr.h>

#include <ZDebug.h>
#include <ZState.h>

namespace Zephyr3{

	//////////////////////////////////////////////////////////////////////////////
	// ZArray
	// 说明：模板动态数组类
	// 注意：不支持构造函数

	template<class T,unsigned int SIZE>
	class ZArray{
	public:
		// 缺省构造函数
		ZArray() {

			m_Array = NULL;
			m_Total = 0;

			if(SIZE != 0)
				Alloc(SIZE);

			m_bRelease = true;
		}

		// 给定分配空间的构造函数
		ZArray(T* pDat,unsigned int size) {

			ZASSERT(pDat != NULL && size >= 0)

			m_Array = pDat;
			m_Total = size;

			m_bRelease = false;
		}

		// 析构函数
		~ZArray() { Release(); }

		// 资源释放
		void Release() {

			if(m_Array != NULL && m_bRelease)
				free(m_Array);

			m_Array = NULL;

			m_Total = 0;
		}

		// 分配空间
		HRESULT Alloc(unsigned int size) {

			m_Array = (T *)malloc(size * sizeof(T));
			if(m_Array == NULL)
				return ZRet(E_FAIL,"ZArray::Alloc(%d) fail!",size);

			m_Total = size;

			return S_OK;
		}

		// 重新分配空间
		HRESULT Realloc(unsigned int size) {

			if(size == m_Total)
				return ZRet(E_FAIL,"ZArray::Realloc(%d) require size == cur size!",size);

			m_Array = (T *)::realloc(m_Array,size * sizeof(T));
			if(m_Array == NULL)
				return ZRet(E_FAIL,"ZArray::Realloc(%d) fail!",size);

			m_Total = size;

			return S_OK;
		}

		// 数组操作符
		T& operator[](const unsigned int index) {

			ZASSERT(index >= 0 && index < m_Total);

			return m_Array[index]; 
		}

		// 获得总容量
		unsigned int GetTotalSize()	const { return m_Total; }

		// 直接获得数组首地址
		T *GetData() { return m_Array; }

	private:
		T				*m_Array;		// 资源
		unsigned int	m_Total;		// 总容量
		bool			m_bRelease;		// 是否释放资源
	};
};

#endif	// _ZEPHYR_3_ARRAY_2_H