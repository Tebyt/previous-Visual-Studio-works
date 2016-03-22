/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Net2\TCP_Client.h

							Describe:	TCP客户端核心

							Author:		赵洪松(xueren)

							CreateTime: 2003.12.03
							UpdateTime: 2003.12.11	-	修正 TCPClient 消息接受函数 RecvMsg 的bug
*/

#ifndef _ZEPHYR_NET_2_TCP_CLIENT_H
#define _ZEPHYR_NET_2_TCP_CLIENT_H

#include <ZDebug.h>
#include <ZState.h>
#include <Net2\BaseDef.h>
#include <Net2\ZSocket.h>
#include <Net2\NetStream.h>
#include <Net2\NetKernel.h>
#include <Net2\MsgProcessor.h>
#include <Net2\Packet.h>
#include <Net2\WndMsg.h>

namespace ZNet2{

	////////////////////////////////////////////////////////////////////////////
	// TCPClient

	class ZEPHYR_NET_API TCPClient : public ClientNetKernel{
	public:
		// 构造函数
		TCPClient(LPMsgWorker pMsgWorker) : m_pData(NULL) {
			m_lpMsgWorker = pMsgWorker;
		}
		// 析构函数
		virtual ~TCPClient() {
			Release();
		}

		// 初始化客户端
		HRESULT Init(ZSocketAddr& addr);

		// 自动重新连接
		HRESULT Reconnect();

		// 断开连接
		void Disconnect();

		// 资源释放
		void Release();
		// 等待，直到资源释放才返回
		void Wait_Release();

		// virtual from ZThread
		// 核心线程
		virtual HRESULT Run(void *lpparam);

		// 服务器断开连接
		void ServerCut() {
			Debug("TCPClient::ServerCut");

			ZASSERT(m_lpMsgWorker != NULL);

			m_lpMsgWorker->PeerCut(NULL);

			Disconnect();
		}

		// 消息处理
		virtual HRESULT HandleMessage(LPVOID pMsg,int msgLen) {

			ZASSERT(m_lpMsgWorker != NULL);

			return m_lpMsgWorker->HandleMessage(pMsg,msgLen,NULL,this);
		}

		// SendMsg
		virtual int SendMsg(LPVOID pAddr,LPVOID pMsg,int msgLen);

		// 发送消息
		int Send(LPVOID pMsg,int msgLen);

		// 出错输出
		virtual HRESULT Error(LPVOID pAddr,HRESULT hRet,const char* str) {

			return ZRet(hRet,(char *)str);
		}

		// 获得连接地址私有数据
		virtual void SetData(LPVOID pAddr,LPVOID pData) { 
			m_pData = pData;
		}

		// 获得连接地址私有数据
		virtual LPVOID GetData(LPVOID pAddr) { 

			return m_pData;
		}

		bool IsConnect();

		DWORD GetLocalIP() { return m_Sock.GetLocalIP(); }
	protected:
		// 消息线程启动时执行
		HRESULT MsgThreadBegin(LPVOID pThread) {

			ZASSERT(m_lpMsgWorker != NULL);

			m_lpMsgWorker->PostMsg(TCP_CLIENT_THREAD_BEGIN,0);

			return m_lpMsgWorker->MsgThreadBegin(pThread);
		}

		// 消息线程退出时执行
		void MsgThreadEnd(LPVOID pThread) {

			ZASSERT(m_lpMsgWorker != NULL);

			m_lpMsgWorker->MsgThreadEnd(pThread);

			m_lpMsgWorker->PostMsg(TCP_CLIENT_THREAD_END,0);
		}

		// 接收消息
		int RecvMsg(BYTE* pBuff);

		// 是否初始化
		bool IsInited() { return m_dwState.Get() != 0; }
	protected:
		ZSocket				m_Sock;

		ZState_DWord		m_dwState;			// 属性

		LPMsgWorker			m_lpMsgWorker;		// 消息工作者

		ZSocketAddr			m_addr;

		LPVOID				m_pData;
	};

	typedef TCPClient*	LPTCPClient;
};

#endif//_ZEPHYR_NET_2_TCP_CLIENT_H