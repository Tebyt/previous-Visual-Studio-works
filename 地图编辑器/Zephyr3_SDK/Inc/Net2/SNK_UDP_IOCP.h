/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Net2\SNK_UDP_IOCP.h

							Describe:	UDP服务器核心 - IOCP

							Author:		赵洪松(xueren)

							CreateTime: 2003.12.16
							UpdateTime:
*/

#ifndef _ZEPHYR_NET_2_NETKERNEL_SERVER_UDP_IOCP_H
#define _ZEPHYR_NET_2_NETKERNEL_SERVER_UDP_IOCP_H

#ifdef _ZEPHYR_NET_SERVER__

#include <ZDebug.h>
#include <ZState.h>
#include <Net2\BaseDef.h>
#include <Net2\ZSocket.h>
#include <Net2\NetStream.h>
#include <Net2\NetKernel.h>
#include <Net2\MsgProcessor.h>
#include <Net2\Packet.h>

namespace ZNet2{

	////////////////////////////////////////////////////////////////////////////
	// SNK_UDP_IOCP
	// UDP服务器 － IOCP

	class ZEPHYR_NET_API SNK_UDP_IOCP : public ServiceNetKernel{
		friend DWORD WINAPI _udp_iocp_recvfunc(LPVOID lpParam);
	public:
		// IOCP Param
		class ContextKey;

		typedef ContextKey*		LPContextKey;

		struct RecvThreadParam{
			SNK_UDP_IOCP*		lpModule;
			ZThread*			lpThread;
			LPContextKey		lpKey;
		};

		typedef RecvThreadParam*	LPRecvThreadParam;
	public:
		// 构造函数
		SNK_UDP_IOCP(LPMsgWorker pMsgWorker) {

			SetThreads(1,2);

			m_recvEvent = m_sendEvent = NULL;

			m_lpMsgWorker = pMsgWorker;

			m_KeyList = NULL;

			m_lpRecvThread = NULL;
			m_lpRecvParam = NULL;
		}

		// 析构函数
		virtual ~SNK_UDP_IOCP() { Release(); }

		// 资源释放
		void Release();

		// 初始化服务
		HRESULT Init(ZSocketAddr& addr);

		// 设置线程数
		// 参数：cpuThreads		-	一个cpu同时可运行的线程数，一般情况下为 1
		//		 spareThreads	-	备用的线程数，一般情况下为 2
		// 注意：必须在初始化以前调用
		void SetThreads(int cpuThreads,int spareThreads);

		// SendMsg
		inline int SendMsg(SNK_UDP_IOCP::LPContextKey pAddr,LPVOID pMsg,int msgLen);

		// SendMsg
		virtual int SendMsg(LPVOID pAddr,LPVOID pMsg,int msgLen) {

			return SendMsg((SNK_UDP_IOCP::LPContextKey)pAddr,pMsg,msgLen);
		}

		// 错误消息输出
		HRESULT Error(SNK_UDP_IOCP::LPContextKey pKey,HRESULT hRet,const char* str);

		// 出错输出
		virtual HRESULT Error(LPVOID pAddr,HRESULT hRet,const char* str) {

			return Error((SNK_UDP_IOCP::LPContextKey)pAddr,hRet,str);
		}

		// 获得连接地址私有数据
		virtual void SetData(LPVOID pAddr,LPVOID pData) {

			SetData((SNK_UDP_IOCP::LPContextKey)pAddr,pData);
		}

		// 获得连接地址私有数据
		inline void SetData(SNK_UDP_IOCP::LPContextKey pAddr,LPVOID pData);

		// 获得连接地址私有数据
		virtual LPVOID GetData(LPVOID pAddr) {
			return GetData((SNK_UDP_IOCP::LPContextKey)pAddr);
		}

		// 获得连接地址私有数据
		inline LPVOID GetData(SNK_UDP_IOCP::LPContextKey pAddr);
	protected:
		// 创建消息接收线程
		HRESULT CreateRecvThreads();

		// 结束消息接收线程
		void EndRecvThreads();

		// Recv
		void Recv(SNK_UDP_IOCP::LPContextKey pKey);

		// 获得完成端口句柄
		HANDLE GetCompletionPort() {
			return m_CompletionPort;
		}

		// 消息处理函数
		HRESULT HandleMessage(LPVOID pMsg,int msgLen,LPVOID pAddr,LPVOID pThread) {

			ZASSERT(m_lpMsgWorker != NULL);

			return m_lpMsgWorker->HandleMessage(pMsg,msgLen,pAddr,pThread);
		}

		// 获得发送事件句柄
		HANDLE GetSendEvent() {
			return m_sendEvent;
		}

		// 获得接收事件句柄
		HANDLE GetRecvEvent() {
			return m_recvEvent;
		}
	protected:
		LPContextKey		m_KeyList;	// KeyList

		ZSocket				m_sock;		// 监听Socket
		ZSocketAddr			m_addr;		// 监听Socket地址

		HANDLE				m_CompletionPort;	// 完成端口句柄
		int					m_cpuThreads;		// 完成端口 cpu 线程数
		int					m_spareThreads;		// 完成端口 备用线程数

		int					m_recvThreads;		// 实际接收线程数
		ZThread*			m_lpRecvThread;		// 接收线程
		RecvThreadParam*	m_lpRecvParam;		// 接收线程参数

		ZState_DWord		m_dwState;			// 属性

		HANDLE				m_recvEvent;
		HANDLE				m_sendEvent;

		LPMsgWorker			m_lpMsgWorker;		// 消息工作者
	};



	////////////////////////////////////////////////////////////////////////////
	// SNK_UDP_IOCP::ContextKey

	class SNK_UDP_IOCP::ContextKey{
	public:
		// 构造函数
		ContextKey() { Init(); }
		// 析构函数
		~ContextKey() { Release(); }

		// 初始化
		void Init() {
			m_dwWant = 0;

			m_pData = NULL;

			m_ovIn.hEvent = NULL;
			m_ovOut.hEvent = NULL;

			m_recvStream.Clear();
			m_sendStream.Clear();
		}

		// 资源释放
		void Release() {
		}

		// 获得 接收流
		LPNetStream GetRecvStream() {
			return &m_recvStream;
		}

		// SetData
		void SetData(LPVOID pData) {
			m_pData = pData;
		}

		// GetData
		LPVOID GetData() {
			return m_pData;
		}

		// Recv
		int Recv(ZSocket& sock);

		// SetEvent
		void SetEvent(HANDLE sendEvent,HANDLE recvEvent) {
			m_ovIn.hEvent = recvEvent;
			m_ovOut.hEvent = sendEvent;
		}

		// GetRecvData
		_block* GetRecvData() {
			return m_recvData;
		}

		// 分析接收数据
		int Analyse_RecvData(DWORD recvLen,_block* block) {
			return m_recvStream.Analyse_InData(recvLen,block,m_dwWant);
		}

		// 获得地址
		LPZSocketAddr GetAddr() {
			return &m_addr;
		}

		// 发送消息
		// 参数：pMsg 为消息指针，带消息头
		//		 dwSize 为消息长度
		DWORD SendMsg(ZSocket& sock,void* pMsg,DWORD dwSize) {
			ZASSERT(pMsg != NULL);
			ZASSERT(dwSize > 0);
			ZASSERT(dwSize <= MAX_PKG_SIZE);

			BYTE key = 0x7b;

			if(dwSize > 4)
				ZNet2::Encode((BYTE*)pMsg + 4,dwSize - 4,key);

			return Send(sock,pMsg,dwSize);
		}

	private:

		// 消息发送
		DWORD Send(ZSocket& sock,const void* pMsg,DWORD dwSize) {
			ZASSERT(pMsg);
			ZASSERT(dwSize > 0);
			ZASSERT(dwSize <= MAX_PKG_SIZE);

			WSABUF buf = {dwSize,(char *)pMsg};
			DWORD sendLen,totalLen = 0;

			do{
				if(sock.SendTo(&buf,1,&sendLen,0,&m_addr,sizeof(m_addr),&m_ovOut,NULL) != SOCKET_ERROR)
					totalLen += sendLen;
				else
					ZRet(E_FAIL,"SNK_TCP_IOCP::Send() 0x%x fail!",WSAGetLastError());

			}while(totalLen < dwSize);

			return dwSize;
		}
	private:
		ZSocketAddr			m_addr;
		int					m_addrLen;

		OVERLAPPED			m_ovIn;			// overlapped recv
		NetStream			m_recvStream;	// recv stream
		WSABUF				m_recvBuf;		// recv param
		DWORD				m_dwWant;		// 还需要接收的长度
		_block*				m_recvData;		// recv data

		NetStream			m_sendStream;	// send stream
		OVERLAPPED			m_ovOut;		// overlapped send

		LPVOID				m_pData;		// 附属数据
	};

	////////////////////////////////////////////////////////////////////////////
	// SNK_UDP_IOCP
	// UDP服务器 － IOCP
	// 内联函数 实现

	// SendMsg
	inline int SNK_UDP_IOCP::SendMsg(SNK_UDP_IOCP::LPContextKey pAddr,LPVOID pMsg,int msgLen) 
	{
		ZASSERT(pAddr != NULL);

		return pAddr->SendMsg(m_sock,pMsg,msgLen);
	}

	// 获得连接地址私有数据
	inline void SNK_UDP_IOCP::SetData(SNK_UDP_IOCP::LPContextKey pAddr,LPVOID pData)
	{
		ZASSERT(pAddr != NULL);

		pAddr->SetData(pData);
	}

	// 获得连接地址私有数据
	inline LPVOID SNK_UDP_IOCP::GetData(SNK_UDP_IOCP::LPContextKey pAddr)
	{
		ZASSERT(pAddr != NULL);

		return pAddr->GetData();
	}
};

#endif // _ZEPHYR_NET_SERVER__

#endif//_ZEPHYR_NET_2_NETKERNEL_SERVER_UDP_IOCP_H