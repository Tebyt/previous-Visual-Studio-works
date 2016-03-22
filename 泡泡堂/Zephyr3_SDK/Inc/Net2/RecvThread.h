/*
							Zephyr Engine v3.0

							by �Ժ���(xueren) 2002 - 2006


							http://www.flyingmagic.net
							E-mail:sssxueren@gmail.com

							FileName:	Net2\RecvThread.h

							Describe:	TCP �����߳�

							Author:		�Ժ���(xueren)

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
		//! �߳������к���
		virtual HRESULT Run(void* pParam);

		//! virtual from NetKernelPeer
	public:
		//! SendMsg
		virtual int SendMsg(LPVOID pMsg, int msgLen);

		//! �������
		virtual HRESULT Error(HRESULT hRet, const char* str);

		//! �������ӵ�ַ˽������
		virtual void SetData(LPVOID pData) {
			m_pData = pData;
		}

		//! ������ӵ�ַ˽������
		virtual void* GetData() {
			return m_pData;
		}

		//! ���������Ժ󣬿��Է��뻺���У��ȴ���һ�γ�ʼ��
		virtual void Clear();

		virtual void Release();

		virtual void Wait_Release();

		//! ��ʼ��
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

		ZState_DWord	m_dwState;			// ����
	};
}

#endif // __ZEPHYR_NET_2_RECV_THREAD_H__
