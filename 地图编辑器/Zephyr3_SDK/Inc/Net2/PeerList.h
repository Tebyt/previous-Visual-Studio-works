/*
							Zephyr Engine v3.0

							by ’‘∫ÈÀ…(xueren) 2002 - 2006


							http://www.flyingmagic.net
							E-mail:sssxueren@gmail.com

							FileName:	Net2\PeerList.h

							Describe:	Õ¯¬Á∫À–ƒ

							Author:		’‘∫ÈÀ…(xueren)

							CreateTime: 2006.02.16
							UpdateTime:
*/

#ifndef __ZEPHYR_NET_2_PEERLIST_2_H__
#define __ZEPHYR_NET_2_PEERLIST_2_H__

#include <stack>

#include <ZLock2.h>

#include <Net2\BaseDef.h>
#include <Net2\NetKernelPeer.h>

namespace ZNet2{

	template<class TYPE>
	class PeerList{
		typedef std::stack<TYPE*>			Stack;
		typedef ZLinkEx<TYPE*, 32, 16>	List;
	public:
		TYPE* NewPeer() {
			TYPE* pPeer = NULL;

			Zephyr3::AutoLock lock(&m_lstLock);

			if(!m_stack.empty())
			{
				pPeer = m_stack.top();
				ZASSERT(pPeer != NULL);

				m_stack.pop();
			}
			else
			{
				pPeer = new TYPE;
				ZASSERT(pPeer != NULL);
			}

			m_lst.Add(pPeer);

			return pPeer;
		}

 		void ReleasePeer(TYPE* pPeer) {
			ZASSERT(pPeer != NULL);

			Zephyr3::AutoLock lock(&m_lstLock);

			m_stack.push(pPeer);

			m_lst.Del(pPeer);
		}

		void Release() {
			Zephyr3::AutoLock lock(&m_lstLock);

			if(m_lst.GetUsed() <= 0)
				return ;

			TYPE** ppPeer = NULL;
			void* index = NULL;

			do{
				m_lst.GetData(ppPeer, index);
				if(ppPeer != NULL && *ppPeer != NULL)
					(*ppPeer)->Release();

			}while(index != NULL);
		}

		void Wait_Release() {
			Zephyr3::AutoLock lock(&m_lstLock);

			if(m_lst.GetUsed() <= 0)
				return ;

			TYPE** ppPeer = NULL;
			void* index = NULL;

			do{
				m_lst.GetData(ppPeer, index);
				if(ppPeer != NULL && *ppPeer != NULL)
					(*ppPeer)->Wait_Release();

			}while(index != NULL);
		}

		void CleanUp() {
			Zephyr3::AutoLock lock(&m_lstLock);

			m_lst.Clear();
		}
	private:
		Stack				m_stack;

		List				m_lst;
		ZCriticalSection	m_lstLock;			//! lst Lock
	};
}

#endif // __ZEPHYR_NET_2_PEERLIST_2_H__
