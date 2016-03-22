/*
							Zephyr Engine v3.0

							by ’‘∫ÈÀ…(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Base\Queue_Link.h

							Describe:	∂”¡–

							Author:		’‘∫ÈÀ…(xueren)

							CreateTime: 2005.02.19
							UpdateTime:
*/

#ifndef _ZEPHYR_3_BASE_QUEUE_LINK_H
#define _ZEPHYR_3_BASE_QUEUE_LINK_H

#include <Zephyr.h>

#include <ZLink.h>
#include <ZLock.h>
#include <ZLock2.h>
#include <MulData.h>
#include <RW_Lock.h>

#include <vector>

namespace Zephyr3{

	template<class T, unsigned int SIZE, unsigned int ADD_SIZE>
	class Queue_Link{
		typedef ZDLinkEx<T*, SIZE, ADD_SIZE>	_Link;
		typedef std::vector<T*>					_Buff;
	public:
		Queue_Link() {
//			Alloc(SIZE);
		}

		~Queue_Link() {
			Release();
		}

		T* Pop() {
			AutoLock lock(&m_lock);

			if(m_link.GetUsed() <= 0)
				return NULL;

			T* tmp = m_link.GetHeadObj();
			void* pIndex = m_link.GetHead();

			m_link.Del(pIndex);

			return tmp;
		}

		void Push(T* pObj) {
			AutoLock lock(&m_lock);

			T** ppTmp = m_link.GetEndObjPoint();
			*ppTmp = pObj;

			m_link.Add();
		}

		T* Head() {
			AutoLock lock(&m_lock);

			if(m_link.GetUsed() > 0)
				return m_link.GetHeadObj();
			else
				return NULL;
		}

		T* Last() {
			AutoLock lock(&m_lock);

			void* pEnd = m_link.GetEnd();
			void* pLast = m_link.Pre(pEnd);
			if(pLast != NULL)
				return *(m_link.GetNodeObj(pLast));

			return NULL;
		}

		void Fill(unsigned int size) {
			Alloc(size);
		}

		unsigned int GetSize() const {
			return m_link.GetUsed();
		}
	private:
		void Alloc(unsigned int size) {
//			AutoWriteLock lock(&m_lock);
			AutoLock lock(&m_lock);

			T* pTmp = NULL;
			pTmp = new T[size];
			ZASSERT_R(pTmp != NULL);

			m_buf.push_back(pTmp);

			for(unsigned int i = 0; i < size; ++i)
			{
				T** ppObj = m_link.GetEndObjPoint();
				*ppObj = &(pTmp[i]);
				m_link.Add();
			}
		}

		void Release() {
			for(_Buff::size_type i = 0; i < m_buf.size(); ++i)
			{
				if(m_buf[i] != NULL)
					delete[] m_buf[i];

				m_buf[i] = NULL;
			}
		}
	private:
		_Link				m_link;
		_Buff				m_buf;
//		RWLock				m_lock;
		ZCriticalSection	m_lock;
	};
}

#endif // _ZEPHYR_3_BASE_QUEUE_LINK_H