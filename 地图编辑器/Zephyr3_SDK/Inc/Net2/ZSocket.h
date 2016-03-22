/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Net2\ZSocket.h

							Describe:	底层Socket

							Author:		赵洪松(xueren)

							CreateTime: 2003.11.25
							UpdateTime:
*/

#ifndef _ZEPHYR_NET_2_SOCKET_H
#define _ZEPHYR_NET_2_SOCKET_H

#include <ZDebug.h>
#include <WinSock2.h>
#include <Net2\BaseDef.h>

namespace ZNet2{


	////////////////////////////////////////////////////////////////////////////
	// WinSocket

	// WinSock Init
	HRESULT ZEPHYR_NET_API SocketInit();
	// WinSock Release
	void ZEPHYR_NET_API SocketRelease();

	////////////////////////////////////////////////////////////////////////////
	// 地址
	// Socket Addr

	typedef sockaddr_in		ZSocketAddr;
	typedef ZSocketAddr*	LPZSocketAddr;

	// 字符串 to IP
	DWORD ZEPHYR_NET_API Str2IP(const char* str);

	// IP to 字符串
	// 注意：字符串必须要可以放下IP地址！也就是 >= 16
	void ZEPHYR_NET_API IP2Str(char str[],int strLen,DWORD IP);

	// 字符串 to addr
	void ZEPHYR_NET_API Str2Addr(ZSocketAddr& addr, const char* str);

	// addr to 字符串
	// 注意：字符串必须要可以放下Addr！也就是 >= 24
	void ZEPHYR_NET_API Addr2Str(char str[],int strLen,ZSocketAddr& addr);

	// 判断ip是否是本地局域网ip
	bool ZEPHYR_NET_API IsLocalIP(DWORD myIP, DWORD ip);

	////////////////////////////////////////////////////////////////////////////
	// ZSocket
	// 底层 Socket

	class ZEPHYR_NET_API ZSocket{
	public:
		// 构造函数
		ZSocket(int af,int type,int protocol) {

			m_Socket = socket(af,type,protocol);
			assert(m_Socket != INVALID_SOCKET);
		}

		// 构造函数
		ZSocket(SOCKET socket) {

			m_Socket = socket;
			assert(m_Socket != INVALID_SOCKET);
		}

		// 缺省构造函数
		ZSocket() { m_Socket = INVALID_SOCKET; }

		// 析构函数
		~ZSocket() { Close(); }

		// 初始化 Socket
		HRESULT Init(int af,int type,int protocol) {
			ZASSERT(!IsInit());

			m_Socket = socket(af, type, protocol);
			if(m_Socket == INVALID_SOCKET)
			{
				int iErr = WSAGetLastError();

				Debug("socket(%d, %d, %d) fail! err is 0x%x", af, type, protocol, iErr);
			}

			assert(m_Socket != INVALID_SOCKET);

			return S_OK;
		}

		// 初始化 Socket
		HRESULT Init(int af,int type,int protocol,LPWSAPROTOCOL_INFO lpProtocolInfo,GROUP g,DWORD dwFlags) {

			ZASSERT(!IsInit());

			m_Socket = WSASocket(af,type,protocol,lpProtocolInfo,g,dwFlags);
			assert(m_Socket != INVALID_SOCKET);

			return S_OK;
		}

		// closesocket
		void Close() {

			if(IsInit())
			{
				closesocket(m_Socket);

				m_Socket = INVALID_SOCKET;
			}
		}

		// bind
		int Bind(const LPZSocketAddr name,int namelen = sizeof(ZSocketAddr)) {

			ZASSERT(IsInit());

			return bind(m_Socket,(sockaddr *)name,namelen);
		}

		// accept
		SOCKET Accept(LPZSocketAddr addr,int* addrlen) {

			ZASSERT(IsInit());

			return accept(m_Socket,(sockaddr*)addr,addrlen);
		}

		// WSAAccept
		SOCKET Accept(LPZSocketAddr addr,LPINT addrlen,LPCONDITIONPROC lpfnCondition,DWORD dwCallbackData) {
			ZASSERT(IsInit());

			return WSAAccept(m_Socket,(sockaddr*)addr,addrlen,lpfnCondition,dwCallbackData);
		}

		// connect
		int Connect(const LPZSocketAddr name,int namelen = sizeof(ZSocketAddr)) {

			ZASSERT(IsInit());

			return connect(m_Socket,(sockaddr*)name,namelen);
		}

		// listen
		int Listen(int backlog) {

			ZASSERT(IsInit());

			return listen(m_Socket,backlog);
		}

		// recv
		int Recv(LPVOID buf,int len,int flags = 0) {

//			ZASSERT_RET_V(IsInit(),0);

			return recv(m_Socket,(char*)buf,len,flags);
		}

		// recv
		int RecvLen(LPVOID buf,int len,int flags = 0) {

//			ZASSERT_RET_V(IsInit(),0);

			int cur = 0;
			int ret;

			do{
				ret = Recv((BYTE *)buf + cur,len - cur,flags);
				if(ret == SOCKET_ERROR)
				{
					Debug("Zephyr3::ZSocket::RecvLen(%d) error!( 0x%x)",len,WSAGetLastError());

					return SOCKET_ERROR;
				}
				else if(ret == 0)
					return cur;

				cur += ret;

			}while(cur < len);

			return len;
		}

		// WSARecv
		int Recv(LPWSABUF lpBuffers,DWORD dwBufferCount,LPDWORD lpNumberOfBytesRecvd,LPDWORD lpFlags,LPWSAOVERLAPPED lpOverlapped,LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine) {

//			ZASSERT_RET_V(IsInit(),0);

			return WSARecv(m_Socket,lpBuffers,dwBufferCount,lpNumberOfBytesRecvd,lpFlags,lpOverlapped,lpCompletionRoutine);
		}

		// recvfrom
		int RecvFrom(LPVOID buf,int len,int flags,LPZSocketAddr from,int* fromlen) {
//			ZASSERT_RET_V(IsInit(),0);

			return recvfrom(m_Socket,(char*)buf,len,flags,(sockaddr*)from,fromlen);
		}

		// WSARecvFrom
		int RecvFrom(LPWSABUF lpBuffers,DWORD dwBufferCount,LPDWORD lpNumberOfBytesRecvd,LPDWORD lpFlags,LPZSocketAddr pFrom,LPINT lpFromlen,LPWSAOVERLAPPED lpOverlapped,LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine) {
//			ZASSERT_RET_V(IsInit(),0);

			return WSARecvFrom(m_Socket,lpBuffers,dwBufferCount,lpNumberOfBytesRecvd,lpFlags,(sockaddr*)pFrom,lpFromlen,lpOverlapped,lpCompletionRoutine);
		}

		// Send
		int Send(LPVOID buf,int len,int flags = 0) {

//			ZASSERT(IsInit());

			return send(m_Socket,(char*)buf,len,flags);
		}

		// WSASend
		int Send(LPWSABUF lpBuffers,DWORD dwBufferCount,LPDWORD lpNumberOfBytesSent,DWORD dwFlags,LPWSAOVERLAPPED lpOverlapped,LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine) {

//			ZASSERT(IsInit());

			return WSASend(m_Socket,lpBuffers,dwBufferCount,lpNumberOfBytesSent,dwFlags,lpOverlapped,lpCompletionRoutine);
		}

		// SendTo
		int SendTo(LPVOID buf,int len,int flags,LPZSocketAddr to,int tolen = sizeof(ZSocketAddr)) {

//			ZASSERT(IsInit());

			return sendto(m_Socket,(char*)buf,len,flags,(sockaddr*)to,tolen);
		}

		// WSASendTo
		int SendTo(LPWSABUF lpBuffers,DWORD dwBufferCount,LPDWORD lpNumberOfBytesSent,DWORD dwFlags,LPZSocketAddr pTo,int iToLen,LPWSAOVERLAPPED lpOverlapped,LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine) {

//			ZASSERT(IsInit());

			return WSASendTo(m_Socket,lpBuffers,dwBufferCount,lpNumberOfBytesSent,dwFlags,(sockaddr*)pTo,iToLen,lpOverlapped,lpCompletionRoutine);
		}


		// shutdown
		int ShutDown(int how) {
#ifdef _DEBUG
			if(!IsInit())
			{
				Debug("ZNet2::ZSocket::ShutDown() socket not inited!");

				return SOCKET_ERROR;
			}

			Debug("ZNet2::ZSocket::ShutDown() 0x%x %d", m_Socket, how);
#endif
//			ZASSERT(IsInit());

			return shutdown(m_Socket, how);
		}

		// setsockopt
		int SetSockOpt(int level,int optname,const char* optval,int optlen) {

			ZASSERT(IsInit());

			return setsockopt(m_Socket,level,optname,optval,optlen);
		}

		// getpeername
		int GetPeerName(LPZSocketAddr name,int* namelen) {

			ZASSERT(IsInit());

			return getpeername(m_Socket,(sockaddr*)name,namelen);
		}

		// 是否初始化
		bool IsInit() const { return m_Socket != INVALID_SOCKET; }

		// SetSocket
		void SetSocket(const SOCKET socket) {
			m_Socket = socket;
		}

		SOCKET GetSocket() const {
			return m_Socket;
		}

		// 赋值
		ZSocket& operator = (const SOCKET socket) {
			m_Socket = socket;

			return *this;
		}

		// 获得本地IP
		DWORD GetLocalIP() {

			ZSocketAddr addr;
			int len = sizeof(addr);

			if(getsockname(m_Socket,(sockaddr*)&addr,&len)  ==  SOCKET_ERROR)
				return 0;

			return addr.sin_addr.S_un.S_addr;
		}
	private:
		SOCKET	m_Socket;
	};
};

#endif//_ZEPHYR_NET_2_SOCKET_H