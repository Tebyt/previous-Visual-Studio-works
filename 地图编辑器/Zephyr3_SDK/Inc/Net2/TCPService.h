/*
							Zephyr Engine v3.0

							by 赵洪松(xueren) 2002 - 2006


							http://www.flyingmagic.net
							E-mail:sssxueren@gmail.com

							FileName:	Net2\TCPService.h

							Describe:	TCP服务器核心

							Author:		赵洪松(xueren)

							CreateTime: 2006.02.15
							UpdateTime:
*/

#ifndef __ZEPHYR_NET_2_TCP_SERVICE_H__
#define __ZEPHYR_NET_2_TCP_SERVICE_H__

#include <ZDebug.h>
#include <ZState.h>

#include <Net2\BaseDef.h>
#include <Net2\RecvThread.h>
#include <Net2\ServiceNetKernel2.h>
#include <Net2\MsgProcessor.h>
#include <Net2\WndMsg.h>
#include <Net2\PeerList.h>
/*
#include <Net2\ZSocket.h>
#include <Net2\NetStream.h>
#include <Net2\Packet.h>
*/
namespace ZNet2{

	////////////////////////////////////////////////////////////////////////////
	// TCPService

	const DWORD	TCPSERVICE_STATE_LISTEN_SOCKET	=	0x0001;
	const DWORD	TCPSERVICE_STATE_LISTEN_THREAD	=	0x0002;

	const HRESULT TCPSERVICE_INIT_BINDFAIL	=	0x81230010;

	class ZEPHYR_NET_API TCPService : public ServiceNetKernel2{
	public:
	public:
		//! 构造函数
		TCPService(LPMsgWorker pMsgWorker) : ServiceNetKernel2(pMsgWorker) {}
		//! 析构函数
		virtual ~TCPService() {
			Release();
		}

		//! 初始化
		HRESULT Init(ZSocketAddr& addr);

		//! 资源释放
		void Release();
		//! 等待，直到资源释放才返回
		void Wait_Release();

		bool IsInit();

		// virtual from ZThread
		//! 核心线程
		virtual HRESULT Run(void *lpparam);

		virtual void CutClient(NetKernelPeer* pAddr);

	public:
	protected:
		//! 节点连接后执行
		virtual void FuncPeerConnect(NetKernelPeer* pAddr) {
			ZASSERT(pAddr != NULL);

			m_lpMsgWorker->PeerConnect(pAddr);
		}

		//! 节点断开前执行
		virtual void FuncPeerDisconnect(NetKernelPeer* pAddr) {
			ZASSERT(pAddr != NULL);

			m_lpMsgWorker->PeerCut(pAddr);
		}

	protected:

		//! 是否初始化
		bool IsInited() { return m_dwState.Get() != 0; }

		//! 中断所有连接
		void ShutDown();
	protected:
		ZSocket					m_sockListen;		//! listen socket
		ZSocketAddr				m_addrListen;		//! listen addr

		PeerList<RecvThread>	m_lstPeer;			//! lstPeer

		ZState_DWord			m_dwState;			// 属性
	};

	typedef TCPService*	LPTCPService;
}

#endif // __ZEPHYR_NET_2_TCP_SERVICE_H__
