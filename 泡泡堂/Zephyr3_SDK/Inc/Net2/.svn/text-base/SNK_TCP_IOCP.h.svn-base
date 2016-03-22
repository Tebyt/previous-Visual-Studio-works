/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Net2\SNK_TCP_IOCP.h

							Describe:	TCP服务器核心 - IOCP

							Author:		赵洪松(xueren)

							CreateTime: 2003.11.06
							UpdateTime: 2003.12.05	-	完善 接口
										2003.12.22	-	修改 Send，增加线程锁，去掉了 SendMsg_Head、SendMsg_Data 等接口

								zhs007 @ 2005.11.07
									对 contextKey 增加 IsInit 接口
*/

#ifndef _ZEPHYR_NET_2_NETKERNEL_SERVER_TCP_IOCP_H
#define _ZEPHYR_NET_2_NETKERNEL_SERVER_TCP_IOCP_H

#ifdef _ZEPHYR_NET_SERVER__

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

////////////////////////////////////////////////////////////////////////////////
// ZNet2
namespace ZNet2{

	////////////////////////////////////////////////////////////////////////////
	// SNK_TCP_IOCP
	// TCP服务器 － IOCP

	class ZEPHYR_NET_API SNK_TCP_IOCP : public ServiceNetKernel{
		friend DWORD WINAPI _recvfunc(LPVOID lpParam);
	public:
		// IOCP Param
		class ContextKey;

		typedef ContextKey*		LPContextKey;

		typedef ZLinkEx<ContextKey,128,128>		ContextKeyList;

		struct RecvThreadParam{
			SNK_TCP_IOCP*		lpModule;
			ZThread*			lpThread;
		};

		typedef RecvThreadParam*	LPRecvThreadParam;

	public:
		// 构造函数
		SNK_TCP_IOCP(LPMsgWorker pMsgWorker) {

			SetThreads(1,2);

			m_recvEvent = m_sendEvent = NULL;

			m_lpMsgWorker = pMsgWorker;
		}

		// 析构函数
		virtual ~SNK_TCP_IOCP() { Release(); }

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
		inline int SendMsg(SNK_TCP_IOCP::LPContextKey pKey,LPVOID pMsg,int msgLen);

		// SendMsg
		virtual int SendMsg(LPVOID pAddr,LPVOID pMsg,int msgLen);

		// 发送数据
		inline int Send(LPVOID pAddr,LPVOID pMsg,int msgLen);

		// 广播
		void BroadCastMsg(SNK_TCP_IOCP::LPContextKey pAddr,LPVOID pMsg,int msgLen);

		// 错误消息输出
		HRESULT Error(SNK_TCP_IOCP::LPContextKey pKey,HRESULT hRet,const char* str);

		// 出错输出
		virtual HRESULT Error(LPVOID pAddr,HRESULT hRet,const char* str) {
			return Error((ZNet2::SNK_TCP_IOCP::LPContextKey)pAddr,hRet,str);
		}

		// 获得连接地址私有数据
		virtual void SetData(LPVOID pAddr,LPVOID pData) {

			SetData((SNK_TCP_IOCP::LPContextKey)pAddr,pData);
		}

		// 获得连接地址私有数据
		inline void SetData(SNK_TCP_IOCP::LPContextKey pAddr,LPVOID pData);

		// 获得连接地址私有数据
		virtual LPVOID GetData(LPVOID pAddr) {
			return GetData((SNK_TCP_IOCP::LPContextKey)pAddr);
		}

		// 获得连接地址私有数据
		inline LPVOID GetData(SNK_TCP_IOCP::LPContextKey pAddr);

		// 断开客户端连接
		void CutClient(SNK_TCP_IOCP::LPContextKey& pAddr) {

			EndConnect(pAddr);

//			Recv(pAddr);
////			ClientCut(pAddr);
		}

		// 锁定KeyList
		void Lock_KeyList() { m_KeyLock.Lock(); }
		// 解锁KeyList
		void Unlock_KeyList() { m_KeyLock.Unlock(); }
		// 查找Addr
		SNK_TCP_IOCP::LPContextKey FindAddr_dw(DWORD dwData);

		// 切断所有客户端连接
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

		// 创建消息接收线程
		HRESULT CreateRecvThreads();

		// 结束消息接收线程
		void EndRecvThreads();

		// 主线程 － Listen Thread
		// virtual from ZThread
		virtual HRESULT Run(LPVOID lpparam);

		// Recv
		void Recv(SNK_TCP_IOCP::LPContextKey pKey);

		// 获得完成端口句柄
		HANDLE GetCompletionPort() {
			return m_CompletionPort;
		}

		// Delete Key
		// 注意：输入参数不能为空
		void DeleteKey(SNK_TCP_IOCP::LPContextKey &pKey);

		// 连接中断
		inline void EndConnect(SNK_TCP_IOCP::LPContextKey pKey);

		// 客户端断开连接
		void ClientCut(SNK_TCP_IOCP::LPContextKey &pKey);

		// 客户端连接
		void ClientConnect(SNK_TCP_IOCP::LPContextKey &pKey) {

			ZASSERT(m_lpMsgWorker != NULL);

			m_lpMsgWorker->PeerConnect(pKey);
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
	public:
		ZCriticalSection& GetKeyLock() {
			return m_KeyLock;
		}

		ContextKeyList& GetKeyList() {
			return m_KeyList;
		}
	public:
		inline SOCKET GetSocket(SNK_TCP_IOCP::LPContextKey pKey);
	private:
		ContextKeyList		m_KeyList;	// KeyList
		ZCriticalSection	m_KeyLock;	// KeyList Lock

		ZSocket				m_sockListen;	// 监听Socket
		ZSocketAddr			m_addrListen;	// 监听Socket地址

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
	// TCPServer_IOCP::ContextKey

	class SNK_TCP_IOCP::ContextKey{
#ifdef _ZEPHYR_NET_21__
	public:
		enum{
			_INFO_LEN	=	64
		};
#endif // _ZEPHYR_NET_21__
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
			m_recvStream.Clear();

#ifdef _ZEPHYR_NET_21__TMP
			m_sendStream.Clear();
			m_ovOut.hEvent = NULL;
			m_bSend.Set(false);
#else // _ZEPHYR_NET_21__TMP
			m_sendStream.Clear();
			m_ovOut.hEvent = NULL;
#endif // _ZEPHYR_NET_21__TMP

			m_bRelease.Set(false);
			m_bHasData.Set(false);
			m_bEndConnect.Set(false);

			m_recvData = NULL;

			m_Sock = NULL;

			memset(&m_ovIn, 0, sizeof(m_ovIn));			// overlapped recv
			memset(&m_ovOut, 0, sizeof(m_ovOut));		// overlapped send

			memset(&m_recvBuf, 0, sizeof(m_recvBuf));	// recv param

#ifdef _ZEPHYR_NET_21__
			m_strInfo[0] = '\0';
#endif // _ZEPHYR_NET_21__
//			m_bPeerCut = false;
		}

//		bool IsInit() {
//			return m_bRelease.Get() == false;
//		}

		// 资源释放
		void Release() {

//			if(m_bRelease.Set(true))
//				return ;

			if(m_Sock.IsInit())
			{
				ShutDown();

				m_Sock.Close();
			}
		}

		void EndConnect() {

			m_bEndConnect.Set(true);

			m_recvStream.EndConnect();

			ShutDown();
		}

		bool IsEndConnect() {

			return m_bEndConnect.Get();
		}

		// 关闭连接
		void ShutDown() {
			if(m_Sock.IsInit())
			{
				if(m_Sock.ShutDown(SD_BOTH) != 0)
				{
					DEBUGMESSAGE2("SNK_TCP_IOCP::ContextKey ShutDown failed. %d", WSAGetLastError());

					m_Sock.Close();
				}
			}
		}

		// 设置SOCKET
		void SetSocket(SOCKET sock) {
			m_Sock.SetSocket(sock);

#ifdef _ZEPHYR_NET_21__
			BuildInfo();
#endif // _ZEPHYR_NET_21__
		}

		SOCKET GetSocket() {
			return m_Sock.GetSocket();
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
		int Recv();

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
		void GetAddr(ZSocketAddr& addr) {
			int len = sizeof(ZSocketAddr);

			if(m_Sock.IsInit())
			{
				m_Sock.GetPeerName(&addr,&len);
				ZASSERT(len == sizeof(ZSocketAddr));
			}
		}
#ifdef _ZEPHYR_NET_21__TMP

		// 发送消息
		// 参数：pMsg 为消息指针，带消息头
		//		 dwSize 为消息长度
		int SendMsg(void* pMsg, DWORD dwSize, bool bEncode) {
			ZASSERT(pMsg != NULL);
			ZASSERT(dwSize > 0);
			ZASSERT(dwSize <= MAX_PKG_SIZE);

			if(bEncode)
			{
				BYTE key = 0x7b;

				if(dwSize > 4)
					ZNet2::Encode((BYTE*)pMsg + 4,dwSize - 4,key);
			}

//			Debug("SendMsg() - %s -", GetInfo());

			m_sendStream.SendMsg(pMsg, dwSize, bEncode);

			return Send(dwSize);
		}

		int Send(DWORD dwSize) {
			if(!m_bSend.SetIf(false, true))
			{
//				Debug("Send() - %s -", GetInfo());

				unsigned int size;
				LPVOID pDat = m_sendStream.GetSendData(size);

				WSABUF buf = {size, (char *)pDat};
				DWORD sendLen, totalLen = 0;

				HANDLE hSend = m_ovOut.hEvent;
				memset(&m_ovOut, 0, sizeof(m_ovOut));
				m_ovOut.hEvent = hSend;

				do{
					if(m_Sock.Send(&buf, 1, &sendLen, 0, &m_ovOut, NULL) != SOCKET_ERROR)
					{
						if(sendLen == 0)
							return 0;

						totalLen += sendLen;
					}
					else
					{
						DWORD ret = WSAGetLastError();

						if(ret == 0 || ret == 997)
							return size;

						if(ret != WSAEWOULDBLOCK && ret != WSA_IO_PENDING)
						{
							ZRet(E_FAIL,"SNK_TCP_IOCP::ContextKey::Send(DWORD) 0x%x fail! - %s -", ret, GetInfo());

							if(ret == 0x2745 || ret == 0x2746 || ret == 0x274a || ret == 0x2747)
								ShutDown();

							return SOCKET_ERROR;
						}

						return SOCKET_ERROR;
					}

				}while(totalLen < size);

				return totalLen;
			}

			return dwSize;
		}

		int EndSend(DWORD dwSize) {
			unsigned int size;
			LPVOID pDat = m_sendStream.GetHeadData(size);
			if(size > dwSize)
			{
//				Debug("EndSend() %d %d - %s -", size, dwSize, GetInfo());

				size -= dwSize;

				WSABUF buf = {size, static_cast<char *>(pDat) + dwSize};
				DWORD sendLen, totalLen = 0;

				HANDLE hSend = m_ovOut.hEvent;
				memset(&m_ovOut, 0, sizeof(m_ovOut));
				m_ovOut.hEvent = hSend;

				do{
					if(m_Sock.Send(&buf, 1, &sendLen, 0, &m_ovOut, NULL) != SOCKET_ERROR)
					{
						if(sendLen == 0)
							return 0;

						totalLen += sendLen;
					}
					else
					{
						DWORD ret = WSAGetLastError();

						if(ret == 0 || ret == 997)
							return size;

						if(ret != WSAEWOULDBLOCK && ret != WSA_IO_PENDING)
						{
							ZRet(E_FAIL,"SNK_TCP_IOCP::EndSend() 0x%x fail!", ret);

							if(ret == 0x2745 || ret == 0x2746 || ret == 0x274a || ret == 0x2747)
								ShutDown();

							return SOCKET_ERROR;
						}

						return SOCKET_ERROR;
					}

				}while(totalLen < size);

				return totalLen;
			}
			else if(size < dwSize)
//			{
				Debug("ContextKey::EndSend() size fail! %s", GetInfo());

//				return dwSize;
//			}

			m_sendStream.Next();

			return Send();
		}

		int Send() {
			unsigned int size;
			LPVOID pDat = m_sendStream.GetSendData(size);
			if(pDat != NULL)
			{
				WSABUF buf = {size, (char *)pDat};
				DWORD sendLen, totalLen = 0;

				HANDLE hSend = m_ovOut.hEvent;
				memset(&m_ovOut, 0, sizeof(m_ovOut));
				m_ovOut.hEvent = hSend;

				do{
					if(m_Sock.Send(&buf, 1, &sendLen, 0, &m_ovOut, NULL) != SOCKET_ERROR)
					{
						if(sendLen == 0)
							return 0;

						totalLen += sendLen;
					}
					else
					{
						DWORD ret = WSAGetLastError();

						if(ret == 0 || ret == 997)
							return size;

						if(ret != WSAEWOULDBLOCK && ret != WSA_IO_PENDING)
						{
							ZRet(E_FAIL,"SNK_TCP_IOCP::Send() 0x%x fail!", ret);

							if(ret == 0x2745 || ret == 0x2746 || ret == 0x274a || ret == 0x2747)
								ShutDown();

							return SOCKET_ERROR;
						}

						return SOCKET_ERROR;
					}

				}while(totalLen < size);

				return totalLen;
			}

			m_bSend.Set(false);

			return 1;
		}

#else // _ZEPHYR_NET_21__TMP

		// 发送消息
		// 参数：pMsg 为消息指针，带消息头
		//		 dwSize 为消息长度
		int SendMsg(void* pMsg,DWORD dwSize) {
			ZASSERT(pMsg != NULL);
			ZASSERT(dwSize > 0);
			ZASSERT(dwSize <= MAX_PKG_SIZE);

			BYTE key = 0x7b;

			if(dwSize > 4)
				ZNet2::Encode((BYTE*)pMsg + 4,dwSize - 4,key);

			return Send(pMsg,dwSize);
		}

		// 请求发送缓冲
		// 注意：缓冲大小在 0 - MAX_PKG_SIZE 之间
		LPVOID RequestSendBuff(DWORD dwSize = MAX_PKG_SIZE) {
			ZASSERT(dwSize > 0 && dwSize <= MAX_PKG_SIZE);
		}

		// 消息发送
		int Send(const void* pMsg,DWORD dwSize) {
			ZASSERT(pMsg);
			ZASSERT(dwSize > 0);
			ZASSERT(dwSize <= MAX_PKG_SIZE);
/*
			if(m_bPeerCut)
				return 0;
*/
/*
			if(m_bEndConnect.Get())
			{
				Debug("ContextKey::Send() end connect!");

				return 0;
			}
*/
			if(m_bEndConnect.Get())
			{
				Debug("ContextKey::Send() is end connect!");

				return SOCKET_ERROR;
			}

			if(!m_Sock.IsInit())
			{
				Debug("ContextKey::Send() sock is not init!");

				return SOCKET_ERROR;
			}

			Zephyr3::AutoLock lock(&m_sendLock);

			DWORD sendLen,totalLen = 0;

			HANDLE hSend = m_ovOut.hEvent;
			memset(&m_ovOut, 0, sizeof(m_ovOut));
			m_ovOut.hEvent = hSend;

			do{
				WSABUF buf = {dwSize - totalLen, (char *)pMsg + totalLen};
				if(m_Sock.Send(&buf,1,&sendLen,0,&m_ovOut,NULL) != SOCKET_ERROR)
					totalLen += sendLen;
				else
				{
					DWORD ret = WSAGetLastError();

					if(ret != WSAEWOULDBLOCK && ret != WSA_IO_PENDING)
					{
						ZRet(E_FAIL,"SNK_TCP_IOCP::Send() 0x%x fail!(0x%x)", ret, m_Sock.GetSocket());

						if(ret == 0x2745 || ret == 0x2746 || ret == 0x274a || ret == 0x2747)
							ShutDown();

						return SOCKET_ERROR;
					}

					return 0;
				}

			}while(totalLen < dwSize);

			return dwSize;
		}
#endif // _ZEPHYR_NET_21__TMP

		void RecvData() {
			m_bHasData.Set(true);
		}

		bool HasRecvData() {
			return m_bHasData.Get();
		}

		bool IsInit() {
			return m_Sock.IsInit();
		}
/*
		void PeerCut() {

			m_bPeerCut = true;
		}

		bool IsPeerCut() {

			return m_bPeerCut;
		}
*/
#ifdef _ZEPHYR_NET_21__
		// 构造输出信息
		void BuildInfo() {
			char strIP[16];
			ZSocketAddr addr;

			GetAddr(addr);

			IP2Str(strIP, 16, addr.sin_addr.S_un.S_addr);

			_format_str(m_strInfo, "0x%x(%x %s:%d )", this, m_Sock.GetSocket(), strIP, addr.sin_port);
		}

		// 返回输出信息
		const char* GetInfo() const {
			return m_strInfo;
		}
#endif // _ZEPHYR_NET_21__
	private:
#ifdef _ZEPHYR_NET_21__
		char				m_strInfo[_INFO_LEN];	// 输出信息
#endif // _ZEPHYR_NET_21__
		ZSocket				m_Sock;			// socket

		OVERLAPPED			m_ovIn;			// overlapped recv
		NetStream			m_recvStream;	// recv stream
		WSABUF				m_recvBuf;		// recv param
		DWORD				m_dwWant;		// 还需要接收的长度
		_block*				m_recvData;		// recv data

#ifdef _ZEPHYR_NET_21__TMP
		SendStream			m_sendStream;	// Send Stream
		OVERLAPPED			m_ovOut;		// overlapped send
		Zephyr3::MulBool	m_bSend;		// Is Sending
#else // _ZEPHYR_NET_21__TMP
		NetStream			m_sendStream;	// send stream
		OVERLAPPED			m_ovOut;		// overlapped send
#endif // _ZEPHYR_NET_21__TMP

		Zephyr3::MulBool	m_bRelease;
		Zephyr3::MulBool	m_bHasData;
		Zephyr3::MulBool	m_bEndConnect;

//		bool				m_bPeerCut;

		LPVOID				m_pData;		// 附属数据
	public:
		ZCriticalSection	m_lock;
		ZCriticalSection	m_sendLock;
	};

	////////////////////////////////////////////////////////////////////////////
	// SNK_TCP_IOCP
	// TCP服务器 － IOCP
	// 内联函数 实现

	// SendMsg
	inline int SNK_TCP_IOCP::SendMsg(SNK_TCP_IOCP::LPContextKey pKey,LPVOID pMsg,int msgLen) 
	{
		ZASSERT(pKey != NULL);

		DWORD sendLen = 0;

#ifdef _ZEPHYR_NET_21__TMP
		sendLen = pKey->SendMsg(pMsg, msgLen, true);
#else // _ZEPHYR_NET_21__TMP
		sendLen = pKey->SendMsg(pMsg, msgLen);
#endif // _ZEPHYR_NET_21__TMP

		if(sendLen == SOCKET_ERROR)
		{
			pKey->EndConnect();

			DEBUGMESSAGE("SNK_TCP_IOCP::SendMsg() failed.");
		}

		return sendLen;
	}

	// 获得连接地址私有数据
	inline void SNK_TCP_IOCP::SetData(SNK_TCP_IOCP::LPContextKey pAddr,LPVOID pData)
	{
		ZASSERT(pAddr != NULL);

		pAddr->SetData(pData);
	}

	// 获得连接地址私有数据
	inline LPVOID SNK_TCP_IOCP::GetData(SNK_TCP_IOCP::LPContextKey pAddr)
	{
		ZASSERT(pAddr != NULL);

		return pAddr->GetData();
	}

	// 发送数据
	inline int SNK_TCP_IOCP::Send(LPVOID pAddr,LPVOID pMsg,int msgLen)
	{
		ZASSERT(pAddr != NULL);

		DWORD sendLen = 0;

		SNK_TCP_IOCP::LPContextKey pKey = (SNK_TCP_IOCP::LPContextKey)pAddr;

#ifdef _ZEPHYR_NET_21__TMP
		sendLen = pKey->SendMsg(pMsg, msgLen, false);
#else // _ZEPHYR_NET_21__TMP
		sendLen = pKey->Send(pMsg, msgLen);
#endif // _ZEPHYR_NET_21__TMP

		if(sendLen == SOCKET_ERROR)
		{
			pKey->EndConnect();

			DEBUGMESSAGE("SNK_TCP_IOCP::SendMsg() pAddr failed.");
		}

		return sendLen;
	}

	// 连接中断
	inline void SNK_TCP_IOCP::EndConnect(SNK_TCP_IOCP::LPContextKey pKey) {

		ZASSERT(pKey != NULL);

		pKey->EndConnect();

//		if(!pKey->GetRecvStream()->IsProcess())
//			ClientCut(pKey);
	}

	inline SOCKET SNK_TCP_IOCP::GetSocket(SNK_TCP_IOCP::LPContextKey pKey) 
	{
		return pKey->GetSocket();
	}
};
#endif // _ZEPHYR_NET_SERVER__

#endif//_ZEPHYR_NET_2_NETKERNEL_SERVER_TCP_IOCP_H