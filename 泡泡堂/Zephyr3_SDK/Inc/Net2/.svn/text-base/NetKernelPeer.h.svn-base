/*
							Zephyr Engine v3.0

							by 赵洪松(xueren) 2002 - 2006


							http://www.flyingmagic.net
							E-mail:sssxueren@gmail.com

							FileName:	Net2\NetKernelPeer.h

							Describe:	网络核心节点

							Author:		赵洪松(xueren)

							CreateTime: 2006.02.16
							UpdateTime:
*/

#ifndef __ZEPHYR_NET_2_NET_KERNELPEER_H__
#define __ZEPHYR_NET_2_NET_KERNELPEER_H__

#include <ZDebug.h>

#include <Net2\BaseDef.h>

namespace ZNet2{

	class NetKernel2;

	////////////////////////////////////////////////////////////////////////////
	// NetKernelPeer

	class ZEPHYR_NET_API NetKernelPeer{
	public:
		NetKernelPeer() : m_pNetKernel(NULL) {}

		//! destruct
		virtual ~NetKernelPeer() {}

		//! SendMsg
		virtual int SendMsg(LPVOID pMsg, int msgLen) = 0;

		//! 出错输出
		virtual HRESULT Error(HRESULT hRet, const char* str) = 0;

		//! 设置连接地址私有数据
		virtual void SetData(LPVOID pData) = 0;

		//! 获得连接地址私有数据
		virtual void* GetData() = 0;

		//! 清除，清除以后，可以放入缓存中，等待下一次初始化
		virtual void Clear() = 0;

		virtual void Release() = 0;

		//! 断开
		virtual void PeerCut() {}
		//! 连接
		virtual void PeerConnect() {}

		//!
		virtual void CutMe();

		//! 初始化
		virtual HRESULT Init(NetKernel2* pNetKernel, SOCKET socket) {
			m_pNetKernel = pNetKernel;

			return S_OK;
		}

		// 消息处理函数
		virtual HRESULT HandleMessage(void* pMsg, int msgLen, void* pThread);
	protected:
		NetKernel2*		m_pNetKernel;
	};

	typedef NetKernelPeer*	LPNetKernelPeer;
}

#endif // __ZEPHYR_NET_2_NET_KERNELPEER_H__
