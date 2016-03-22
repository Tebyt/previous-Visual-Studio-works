/*
							Zephyr Engine v3.0

							by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Net2\TCPClientList.h

							Describe:	TCPClientList

							Author:		赵洪松(xueren)

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
		// 构造函数
		TCPClientList(LPMsgWorker pMsgWorker) {
			m_lpMsgWorker = pMsgWorker;
		}

		// 析构函数
		virtual ~TCPClientList() { Release(); }

		// 资源释放
		void Release();

		// 初始化服务
		HRESULT Init();

		// SendMsg
		virtual int SendMsg(LPVOID pAddr, LPVOID pMsg, int msgLen) {
			return (reinterpret_cast<TCPClientList::LPAddr>(pAddr))->SendMsg(NULL, pMsg, msgLen);
		}

		// 广播
		void BroadCastMsg(LPVOID pAddr, LPVOID pMsg, int msgLen);

		// 出错输出
		virtual HRESULT Error(LPVOID pAddr, HRESULT hRet, const char* str) {
			return Error(pAddr, hRet, str);
		}

		// 获得连接地址私有数据
		virtual void SetData(LPVOID pAddr, LPVOID pData) {
			(reinterpret_cast<TCPClientList::LPAddr>(pAddr))->SetData(NULL, pData);
		}

		// 获得连接地址私有数据
		virtual LPVOID GetData(LPVOID pAddr) {
			return (reinterpret_cast<TCPClientList::LPAddr>(pAddr))->GetData(NULL);
		}

		// 切断所有连接
		void ShutDown();
	protected:
		// 消息线程启动时执行
		HRESULT MsgThreadBegin(LPVOID pThread) {

			ZASSERT(m_lpMsgWorker != NULL);

			return m_lpMsgWorker->MsgThreadBegin(pThread);
		}
		// 消息线程结束时执行
		void MsgThreadEnd(LPVOID pThread) {

			ZASSERT(m_lpMsgWorker != NULL);

			m_lpMsgWorker->MsgThreadEnd(pThread);
		}

		// 主线程
		// virtual from ZThread
		virtual HRESULT Run(LPVOID lpparam);

		// 消息处理函数
		HRESULT HandleMessage(LPVOID pMsg, int msgLen, LPVOID pAddr, LPVOID pThread) {
			ZASSERT(m_lpMsgWorker != NULL);

			return m_lpMsgWorker->HandleMessage(pMsg,msgLen,pAddr,pThread);
		}
	private:
		LPMsgWorker			m_lpMsgWorker;		// 消息工作者
	};
}

#endif // _ZEPHYR_NET_2_TCPCLIENTLIST_H