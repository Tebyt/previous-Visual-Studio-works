/*
							Zephyr Engine v3.0

							by 赵洪松(xueren) 2002 - 2006


							http://www.flyingmagic.net
							E-mail:sssxueren@gmail.com

							FileName:	Net2\NetKernel2.h

							Describe:	网络核心

							Author:		赵洪松(xueren)

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
	// 网络核心

	class ZEPHYR_NET_API NetKernel2 : public ZThread{
	protected:
		NetKernel2(LPMsgWorker lpMsgWorker) : m_lpMsgWorker(lpMsgWorker) {}
	public:
		//! destruct
		virtual ~NetKernel2() {}
	public:
		//! 消息处理
		virtual HRESULT HandleMessage(void* pMsg, int msgLen, NetKernelPeer* pAddr, void* pThread) {
			ZASSERT(m_lpMsgWorker != NULL);

			return m_lpMsgWorker->HandleMessage(pMsg, msgLen, pAddr, pThread);
		}
	public:
		//! 消息线程启动时执行
		virtual HRESULT FuncMsgThreadBegin(void* pThread) {
			ZASSERT(m_lpMsgWorker != NULL);

			m_lpMsgWorker->PostMsg(TCP_CLIENT_THREAD_BEGIN, 0);

			return m_lpMsgWorker->MsgThreadBegin(pThread);
		}

		//! 消息线程退出时执行
		virtual HRESULT FuncMsgThreadEnd(void* pThread) {
			ZASSERT(m_lpMsgWorker != NULL);

			m_lpMsgWorker->MsgThreadEnd(pThread);

			m_lpMsgWorker->PostMsg(TCP_CLIENT_THREAD_END, 0);

			return S_OK;
		}

		//! 节点连接后执行
		virtual void FuncPeerConnect(NetKernelPeer* pAddr) = 0;

		//! 节点断开前执行
		virtual void FuncPeerDisconnect(NetKernelPeer* pAddr) = 0;

		virtual void CutClient(NetKernelPeer* pAddr) = 0;
	public:
		//! SendMsg
		int SendMsg(NetKernelPeer* pAddr, void* pMsg, int msgLen) {
			ZASSERT(pAddr != NULL);

			return pAddr->SendMsg(pMsg, msgLen);
		}

		//! 出错输出
		HRESULT Error(NetKernelPeer* pAddr, HRESULT hRet, const char* str) {
			ZASSERT(pAddr != NULL);

			return pAddr->Error(hRet, str);
		}

		//! 获得连接地址私有数据
		void SetData(NetKernelPeer* pAddr, LPVOID pData) {
			ZASSERT(pAddr != NULL);

			pAddr->SetData(pData);
		}

		//! 获得连接地址私有数据
		void* GetData(NetKernelPeer* pAddr) {
			ZASSERT(pAddr != NULL);

			return pAddr->GetData();
		}
	protected:
		LPMsgWorker				m_lpMsgWorker;		// 消息工作者
	};

	typedef NetKernel2*	LPNetKernel2;
}

#endif // __ZEPHYR_NET_2_NET_KERNEL2_H__
