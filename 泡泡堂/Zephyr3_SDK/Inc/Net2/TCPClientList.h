/*
							Zephyr Engine v3.0

							by �Ժ���(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Net2\TCPClientList.h

							Describe:	TCPClientList

							Author:		�Ժ���(xueren)

							CreateTime: 2005.05.01
							UpdateTime:
*/

#ifndef _ZEPHYR_NET_2_TCPCLIENTLIST_H
#define _ZEPHYR_NET_2_TCPCLIENTLIST_H

#include <ZDebug.h>
#include <ZState.h>
#include <ZLock2.h>
#include <Net2\BaseDef.h>
#include <Net2\ZSocket.h>
#include <Net2\NetStream.h>
#include <Net2\NetKernel.h>
#include <Net2\MsgProcessor.h>
#include <Net2\Packet.h>
#include <Net2\SendStream.h>
#include <Net2\TCP_Client_Socks5.h>

namespace ZNet2{

	class ZEPHYR_NET_API TCPClientList : public ServiceNetKernel{
	public:
		typedef TCPClient*	LPAddr;
	public:
		// ���캯��
		TCPClientList(LPMsgWorker pMsgWorker) {
			m_lpMsgWorker = pMsgWorker;
		}

		// ��������
		virtual ~TCPClientList() { Release(); }

		// ��Դ�ͷ�
		void Release();

		// ��ʼ������
		HRESULT Init();

		// SendMsg
		virtual int SendMsg(LPVOID pAddr, LPVOID pMsg, int msgLen) {
			return (reinterpret_cast<TCPClientList::LPAddr>(pAddr))->SendMsg(NULL, pMsg, msgLen);
		}

		// �㲥
		void BroadCastMsg(LPVOID pAddr, LPVOID pMsg, int msgLen);

		// �������
		virtual HRESULT Error(LPVOID pAddr, HRESULT hRet, const char* str) {
			return Error(pAddr, hRet, str);
		}

		// ������ӵ�ַ˽������
		virtual void SetData(LPVOID pAddr, LPVOID pData) {
			(reinterpret_cast<TCPClientList::LPAddr>(pAddr))->SetData(NULL, pData);
		}

		// ������ӵ�ַ˽������
		virtual LPVOID GetData(LPVOID pAddr) {
			return (reinterpret_cast<TCPClientList::LPAddr>(pAddr))->GetData(NULL);
		}

		// �ж���������
		void ShutDown();
	protected:
		// ��Ϣ�߳�����ʱִ��
		HRESULT MsgThreadBegin(LPVOID pThread) {

			ZASSERT(m_lpMsgWorker != NULL);

			return m_lpMsgWorker->MsgThreadBegin(pThread);
		}
		// ��Ϣ�߳̽���ʱִ��
		void MsgThreadEnd(LPVOID pThread) {

			ZASSERT(m_lpMsgWorker != NULL);

			m_lpMsgWorker->MsgThreadEnd(pThread);
		}

		// ���߳�
		// virtual from ZThread
		virtual HRESULT Run(LPVOID lpparam);

		// ��Ϣ������
		HRESULT HandleMessage(LPVOID pMsg, int msgLen, LPVOID pAddr, LPVOID pThread) {
			ZASSERT(m_lpMsgWorker != NULL);

			return m_lpMsgWorker->HandleMessage(pMsg,msgLen,pAddr,pThread);
		}
	private:
		LPMsgWorker			m_lpMsgWorker;		// ��Ϣ������
	};
}

#endif // _ZEPHYR_NET_2_TCPCLIENTLIST_H