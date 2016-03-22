/*
							Zephyr Engine v3.0

							by 赵洪松(xueren) 2002 - 2006


							http://www.flyingmagic.net
							E-mail:sssxueren@gmail.com

							FileName:	Net2\RecvThread.h

							Describe:	TCP 接收线程

							Author:		赵洪松(xueren)

							CreateTime: 2006.02.15
							UpdateTime:
*/

#ifndef __ZEPHYR_NET_2_RECV_THREAD_H__
#define __ZEPHYR_NET_2_RECV_THREAD_H__

#include <ZThread.h>
#include <ZState.h>

#include <Net2\BaseDef.h>
#include <Net2\ZSocket.h>
#include <Net2\NetKernelPeer.h>

namespace ZNet2{

	////////////////////////////////////////////////////////////////////////////
	// RecvThread

	const DWORD RECVTHREAD_STATE_MAIN_THREAD		=	0x0001;

	class ZEPHYR_NET_API RecvThread : public ZThread, public NetKernelPeer{
	public:
		RecvThread() : m_pData(NULL) {}

		virtual ~RecvThread() { Release(); }

		//! virtual from ZThread
	public:
		//! 线程主运行函数
		virtual HRESULT Run(void* pParam);

		//! virtual from NetKernelPeer
	public:
		//! SendMsg
		virtual int SendMsg(LPVOID pMsg, int msgLen);

		//! 出错输出
		virtual HRESULT Error(HRESULT hRet, const char* str);

		//! 设置连接地址私有数据
		virtual void SetData(LPVOID pData) {
			m_pData = pData;
		}

		//! 获得连接地址私有数据
		virtual void* GetData() {
			return m_pData;
		}

		//! 清除，清除以后，可以放入缓存中，等待下一次初始化
		virtual void Clear();

		virtual void Release();

		virtual void Wait_Release();

		//! 初始化
		virtual HRESULT Init(NetKernel2* pNetKernel, SOCKET socket);

		//!
		bool IsInit() const { return m_socket.IsInit(); }

	public:
		HRESULT ThreadBegin(void* pThread);

		HRESULT ThreadEnd(void* pThread);

		int RecvMsg(BYTE* pBuff);
	private:
		ZSocket			m_socket;

		void*			m_pData;

		ZState_DWord	m_dwState;			// 属性
	};
}

#endif // __ZEPHYR_NET_2_RECV_THREAD_H__
