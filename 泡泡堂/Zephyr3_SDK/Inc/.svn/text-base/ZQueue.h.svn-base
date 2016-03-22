/*
							Zephyr Engine v3.0

								by ’‘∫ÈÀ…(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	ZQueue.h

							Describe:	∂”¡–

							Author:		’‘∫ÈÀ…(xueren)

							CreateTime: 2004.02.18
							UpdateTime:
*/

#ifndef _ZEPHYR_QUEUE_H
#define _ZEPHYR_QUEUE_H

#include <Zephyr.h>

#include <ZLink.h>

template<class T,int SIZE,int ADD_SIZE>
class ZQueue_ZLinkEx{
	typedef ZLinkEx<T,SIZE,ADD_SIZE>	Queue;
public:

	HRESULT GetData(T& dat) {
		if(m_queue.GetUsed() <= 0)
			return E_FAIL;

		T* head = m_queue.GetHeadObjPoint();

		dat = *head;

		m_queue.Del(head);

		return S_OK;
	}

	void Add(T& dat) {
		T* pDat = m_queue.GetEndObjPoint();

		*pDat = dat;

		m_queue.Add();
	}
private:
	Queue	m_queue;
};

#endif//_ZEPHYR_QUEUE_H