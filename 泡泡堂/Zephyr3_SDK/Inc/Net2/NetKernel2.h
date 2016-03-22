/*
							Zephyr Engine v3.0

							by �Ժ���(xueren) 2002 - 2006


							http://www.flyingmagic.net
							E-mail:sssxueren@gmail.com

							FileName:	Net2\NetKernel2.h

							Describe:	�������

							Author:		�Ժ���(xueren)

							CreateTime: 2006.02.16
							UpdateTime:
*/

#ifndef __ZEPHYR_NET_2_NET_KERNEL2_H__
#define __ZEPHYR_NET_2_NET_KERNEL2_H__

#include <ZDebug.h>
#include <ZThread.h>

#include <Net2\BaseDef.h>
#include <Net2\NetKernelPeer.h>
#include <Net2\MsgProcessor.h>
#include <Net2\WndMsg.h>

namespace ZNet2{


	////////////////////////////////////////////////////////////////////////////
	// NetKernel
	// �������

	class ZEPHYR_NET_API NetKernel2 : public ZThread{
	protected:
		NetKernel2(LPMsgWorker lpMsgWorker) : m_lpMsgWorker(lpMsgWorker) {}
	public:
		//! destruct
		virtual ~NetKernel2() {}
	public:
		//! ��Ϣ����
		virtual HRESULT HandleMessage(void* pMsg, int msgLen, NetKernelPeer* pAddr, void* pThread) {
			ZASSERT(m_lpMsgWorker != NULL);

			return m_lpMsgWorker->HandleMessage(pMsg, msgLen, pAddr, pThread);
		}
	public:
		//! ��Ϣ�߳�����ʱִ��
		virtual HRESULT FuncMsgThreadBegin(void* pThread) {
			ZASSERT(m_lpMsgWorker != NULL);

			m_lpMsgWorker->PostMsg(TCP_CLIENT_THREAD_BEGIN, 0);

			return m_lpMsgWorker->MsgThreadBegin(pThread);
		}

		//! ��Ϣ�߳��˳�ʱִ��
		virtual HRESULT FuncMsgThreadEnd(void* pThread) {
			ZASSERT(m_lpMsgWorker != NULL);

			m_lpMsgWorker->MsgThreadEnd(pThread);

			m_lpMsgWorker->PostMsg(TCP_CLIENT_THREAD_END, 0);

			return S_OK;
		}

		//! �ڵ����Ӻ�ִ��
		virtual void FuncPeerConnect(NetKernelPeer* pAddr) = 0;

		//! �ڵ�Ͽ�ǰִ��
		virtual void FuncPeerDisconnect(NetKernelPeer* pAddr) = 0;

		virtual void CutClient(NetKernelPeer* pAddr) = 0;
	public:
		//! SendMsg
		int SendMsg(NetKernelPeer* pAddr, void* pMsg, int msgLen) {
			ZASSERT(pAddr != NULL);

			return pAddr->SendMsg(pMsg, msgLen);
		}

		//! �������
		HRESULT Error(NetKernelPeer* pAddr, HRESULT hRet, const char* str) {
			ZASSERT(pAddr != NULL);

			return pAddr->Error(hRet, str);
		}

		//! ������ӵ�ַ˽������
		void SetData(NetKernelPeer* pAddr, LPVOID pData) {
			ZASSERT(pAddr != NULL);

			pAddr->SetData(pData);
		}

		//! ������ӵ�ַ˽������
		void* GetData(NetKernelPeer* pAddr) {
			ZASSERT(pAddr != NULL);

			return pAddr->GetData();
		}
	protected:
		LPMsgWorker				m_lpMsgWorker;		// ��Ϣ������
	};

	typedef NetKernel2*	LPNetKernel2;
}

#endif // __ZEPHYR_NET_2_NET_KERNEL2_H__
