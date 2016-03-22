/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Net2\RequestMsg.h

							Describe:	网络消息

							Author:		赵洪松(xueren)

							CreateTime: 2003.11.6
							UpdateTime:
*/

#ifndef _ZEPHYR_NET_2_REQUESTMSG_H
#define _ZEPHYR_NET_2_REQUESTMSG_H

#include <ZDebug.h>
#include <ZLink.h>
#include <ZLock2.h>
#include <MulData.h>
#include <Net2\BaseDef.h>
#include <Net2\NetMsg.h>

////////////////////////////////////////////////////////////////////////////////
// ZNet2
namespace ZNet2{

	////////////////////////////////////////////////////////////////////////////
	// RequestMsgManage
	// 请求消息 管理器

	template<class T,unsigned int SIZE>
	class RequestMsgManager{

		struct _Object{
			T				msg;
			unsigned long	time; 
			void			*pData;
		};

		typedef ZDLinkEx<_Object,SIZE,SIZE>	List;
	public:
		// 构造函数
		RequestMsgManager(unsigned long maxTime) { 

			m_MaxTime = maxTime; 
			m_dwID.SetVol(1);
		}

		inline T* Add(unsigned long time,LPVOID data);

		inline T* Find(DWORD ID,LPVOID& data,LPVOID& index);

		inline void Del(LPVOID index);

		inline HRESULT TimerFunc(unsigned long curTime,LPVOID &pData,LPVOID& pIndex);

		// 获得现在的请求ID号
		DWORD GetCurID() { return m_dwID.Inc(); }
	private:
		List							m_MsgList;
		ZCriticalSection				m_Lock;
		unsigned long					m_MaxTime;
		Zephyr3::MulLong				m_dwID;
	};

	template<class T,unsigned int SIZE>
	inline T* RequestMsgManager<T,SIZE>::Add(unsigned long time,LPVOID data)
	{
		Zephyr3::AutoLock lock(&m_Lock);

		_Object *Obj = m_MsgList.GetEndObjPoint();
		ZASSERT_R(Obj != NULL);

		m_MsgList.Add();

		Obj->time = time;
		Obj->pData = data;

		return &(Obj->msg);
	}

	template<class T,unsigned int SIZE>
	inline HRESULT RequestMsgManager<T,SIZE>::TimerFunc(unsigned long curTime,LPVOID &pData,LPVOID& pIndex)
	{
		Zephyr3::AutoLock lock(&m_Lock);

		if(m_MsgList.GetUsed())
		{
			_Object *obj = NULL;
			unsigned long time;
			LPVOID pre = pIndex == NULL ? m_MsgList.GetHead() : pIndex;

			do{
				m_MsgList.GetData(obj,pIndex);
				if(obj != NULL)
				{
					time = curTime - obj->time;
					if(time > m_MaxTime)
					{
						pData = obj->pData;

						Del(pre);

						return E_FAIL;
					}
				}

				pre = pIndex;
			}while(pIndex != NULL);
		}

		return S_OK;
	}

	template<class T,unsigned int SIZE>
	inline void RequestMsgManager<T,SIZE>::Del(LPVOID index)
	{
		ZASSERT(m_MsgList.GetUsed());
		ZASSERT(index != NULL);

		Zephyr3::AutoLock lock(&m_Lock);

		m_MsgList.Del((_Object *)index);
	}

	template<class T,unsigned int SIZE>
	inline T* RequestMsgManager<T,SIZE>::Find(DWORD ID,LPVOID& data,LPVOID& Obj)
	{
		if(m_MsgList.GetUsed() <= 0)
			return NULL;

		void *index = NULL;
		_Object *obj = NULL;

		Zephyr3::AutoLock lock(&m_Lock);

		do{
			m_MsgList.GetData(obj,index);
			if(obj != NULL)
			{
				if(obj->msg.GetID() == ID)
				{
					data = obj->pData;

					Obj = obj;

					return &(obj->msg);
				}
			}
		}while(index != NULL);

		return NULL;
	}
}

#endif//_ZEPHYR_NET_2_REQUESTMSG_H