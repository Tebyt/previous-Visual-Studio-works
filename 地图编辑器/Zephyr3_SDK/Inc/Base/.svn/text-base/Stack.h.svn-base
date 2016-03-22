/*
							Zephyr Engine v3.0

								by ’‘∫ÈÀ…(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Base\Stack.h

							Describe:	∂—’ª

							Author:		’‘∫ÈÀ…(xueren)

							CreateTime: 2003.05.08
							UpdateTime:
*/

#ifndef _ZEPHYR_3_BASE_STACK_H
#define _ZEPHYR_3_BASE_STACK_H

#include <Base\Array.h>

namespace Zephyr3{

	template<class T,unsigned int SIZE,unsigned int ADD_SIZE>
	class Stack{
	public:
		typedef Array<T,SIZE>	_Array;
	public:
		Stack() {
			Clear();
		}

		void Clear() {

			m_End = 0;
//			m_dat.Clear();
		}

		void Push(T& dat) {

			if(m_End >= m_dat.GetSize())
				m_dat.Alloc(m_dat.GetSize() + ADD_SIZE);

			m_dat[m_End++] = dat;
		}

		T* Push() {

			if(m_End >= m_dat.GetSize())
				m_dat.Alloc(m_dat.GetSize() + ADD_SIZE);

			return &(m_dat[m_End++]);
		}

		void Push(T* pDat,unsigned int size) {

			if(m_End + size >= m_dat.GetSize())
				m_dat.Alloc(size > ADD_SIZE ? m_dat.GetSize() + size : m_dat.GetSize() + ADD_SIZE);

			memcpy(&(m_dat[m_End]),pDat,sizeof(T) * size);

			m_End += size;
		}

		T* Pop(unsigned int size) {

			m_End -= size;

			return &(m_dat[m_End]);
		}

		T& Pop() {

			ZASSERT(m_End > 0);

			return m_dat[m_End--];
		}

	private:
		_Array			m_dat;
		unsigned int	m_End;
	};
};

#endif // _ZEPHYR_3_BASE_STACK_H