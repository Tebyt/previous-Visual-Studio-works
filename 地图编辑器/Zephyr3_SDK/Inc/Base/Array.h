/*
							Zephyr Engine v3.0

								by ’‘∫ÈÀ…(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Base\Array.h

							Describe:	 ˝◊È

							Author:		’‘∫ÈÀ…(xueren)

							CreateTime: 2003.05.08
							UpdateTime:
*/

#ifndef _ZEPHYR_3_BASE_ARRAY_H
#define _ZEPHYR_3_BASE_ARRAY_H

#include <Base\Assert.h>
#include <Base\Debug.h>

namespace Zephyr3{

	template<class T,unsigned int SIZE>
	class Array{
	public:
		Array() {
			m_pDat = NULL;

			ZASSERT_R(Alloc(SIZE) != NULL);
//			Clear();
		}

		~Array() {
			Release();
		}
/*
		void Clear() {
			m_Used = 0;
		}
*/
		void Release() {

//			Clear();

			if(m_pDat != NULL)
			{
				free(m_pDat);

				m_pDat = NULL;
				m_Size = 0;
			}
		}

		T& operator[] (unsigned int index) {
			ZASSERT(index >= 0 && index < m_Size);

			return m_pDat[index];
		}

		const T& operator[] (unsigned int index) const {
			ZASSERT(index >= 0 && index < m_Size);

			return m_pDat[index];
		}
/*
		void Add(T& dat) {
			ZASSERT(m_Used >= 0 && m_Used < m_Size);

			m_pDat[m_Used++] = dat;

			if(m_Used == m_Size)
				ZASSERT_R(Alloc(m_Size + ADD_SIZE) != NULL);
		}

		T* Add() {
			ZASSERT(m_Used >= 0 && m_Used < m_Size);

			m_Used++;

			if(m_Used == m_Size)
				ZASSERT_R(Alloc(m_Size + ADD_SIZE) != NULL);

			return &m_pDat[m_Used - 1];
		}
*/
		unsigned int GetSize() const { return m_Size; }

//		unsigned int GetUsed() const { return m_Used; }

		void Request(unsigned int size) {

			if(GetSize() < size)
			{
				ZASSERT_R(Alloc(size) != NULL);
			}
		}

		T* Alloc(unsigned int size) {
			m_pDat = (T*)realloc(m_pDat,size);

			if(m_pDat == NULL)
				return NULL;

			m_Size = size;

			return m_pDat;
		}
	private:
		T*				m_pDat;
		unsigned int	m_Size;
//		unsigned int	m_Used;
	};
};

#endif // _ZEPHYR_3_BASE_ARRAY_H