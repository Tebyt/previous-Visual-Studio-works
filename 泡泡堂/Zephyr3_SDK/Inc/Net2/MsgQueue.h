/*
							Zephyr Engine v3.0

							by ’‘∫ÈÀ…(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Net2\MsgQueue.h

							Describe:	Õ¯¬Á∫À–ƒ∂®“Â

							Author:		’‘∫ÈÀ…(xueren)

							CreateTime: 2006.02.22
							UpdateTime:
*/

#ifndef __NET_2_MSGQUEUE_H__
#define __NET_2_MSGQUEUE_H__

#include "BaseDef.h"

#include <queue>
#include <ZLock2.h>

namespace ZNet2{

	template<class TYPE>
	class MsgQueue{
		typedef std::queue<TYPE> _Queue;
	public:
		void Push(const TYPE& msg) {
			Zephyr3::AutoLock lock(&m_lock);

			m_queue.push(msg);
		}

		void Pop(TYPE& msg) {
			Zephyr3::AutoLock lock(&m_lock);

			msg = m_queue.front();

			m_queue.pop();
		}

		void Clear() {
			while(!m_queue.empty())
				m_queue.pop();
		}

		bool IsEmpty() const {
			return m_queue.empty();
		}
	protected:
		_Queue				m_queue;
		ZCriticalSection	m_lock;
	};
}

#endif // __NET_2_MSGQUEUE_H__
