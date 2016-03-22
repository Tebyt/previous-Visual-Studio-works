/*
							Zephyr Engine v3.0

								by ’‘∫ÈÀ…(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Base\Queue.h

							Describe:	∂”¡–

							Author:		’‘∫ÈÀ…(xueren)

							CreateTime: 2003.05.08
							UpdateTime:
*/

#ifndef _ZEPHYR_3_BASE_QUEUE_H
#define _ZEPHYR_3_BASE_QUEUE_H

#include <Base\Array.h>

namespace Zephyr3{

	template<class T,unsigned int SIZE,unsigned int ADD_SIZE>
	class Queue{
	public:
		typedef Array<T,SIZE>	_Array;
	public:
		Queue() {

			Clear();
		}

		~Queue() {

			Release();
		}

		void Clear() {

			m_Head = m_End = 0;
		}

		void Release() {

			Clear();

			m_dat.Release();
		}

		void Put(T& dat) {
			m_dat[m_End++] = dat;

			if(m_End > m_dat.GetSize())
				m_dat.Alloc(m_dat.GetSize() + ADD_SIZE);
		}

		T* Put() {

			if(m_End >= m_dat.GetSize())
				m_dat.Alloc(m_dat.GetSize() + ADD_SIZE);

			return &m_dat[m_End++];
		}

		T& Get() {
			return m_dat[m_Head++];
		}

		unsigned int GetSize() const { return m_dat.GetSize(); }

		unsigned int GetUsed() const { return m_End - m_Head; }
	private:
		_Array			m_dat;
		unsigned int	m_Head;
		unsigned int	m_End;
	};
};

#endif // _ZEPHYR_3_BASE_QUEUE_H