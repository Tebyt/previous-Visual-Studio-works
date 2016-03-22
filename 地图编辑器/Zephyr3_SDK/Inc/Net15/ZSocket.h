#ifndef __ZEPHYR_SOCKET_H
#define __ZEPHYR_SOCKET_H

// π”√winsock 2.0
//#define ZEPHYR_USE_WS20

#ifndef ZEPHYR_USE_WS20
#include <winsock.h>
#else
#include <winsock2.h>
#endif

#include <zdebug.h>
#include <zlink.h>
#include <zthread.h>

void ZEPHYR_NET_API _getstring(char* &src,char *dst,char end);
long ZEPHYR_NET_API _getlong(char* &src,char end);

void ZEPHYR_NET_API IP2Str(char *Str,int strLen,DWORD IP);

bool ZEPHYR_NET_API ServerIsRuning_TCP(DWORD IP,WORD Port);

HRESULT ZEPHYR_NET_API SocketInit();
void ZEPHYR_NET_API SocketRelease();

int readn(SOCKET fd,char* bp,int len);
DWORD ZEPHYR_NET_API getlocalIP();
DWORD ZEPHYR_NET_API gethostIP();

inline int ZCloseSocket(SOCKET &s)
{
	ZASSERT(s != NULL);

	if(closesocket(s) != SOCKET_ERROR)
	{
		s = NULL;

		return 0;
	}

	return SOCKET_ERROR;
}

//////////////////////////////////////////////////////////////////////
//	ZSocket

class ZEPHYR_NET_API ZSocket{
public:
	ZSocket()
	{
		m_socket=NULL;
	}

	~ZSocket()
	{
		Release();
	}

	inline void Release();

	HRESULT Create(int nType = SOCK_STREAM);
	void Close();
	HRESULT Bind(sockaddr_in *addr);
	HRESULT Listen(int backlog);
	HRESULT Accept(ZSocket &connect,sockaddr_in *addr);
	HRESULT Connect(sockaddr_in *addr);
	int Send(const void* pch,int size,int secs);
	int Send(const void* pch,int size);
	int Write(const void* pch,int size,int secs);
	int Receive(void *pch,int size,int secs);
	int Receive(void *pch,int size);
	int Read(void *pch,int size,int secs);
	int SendTo(const void *pch,int size,sockaddr_in *psa,int secs);
	int ReceiveFrom(void *pch,int size,sockaddr_in *psa,int secs);
	HRESULT GetPeerAddr(sockaddr_in *psa);
	HRESULT GetSockAddr(sockaddr_in *psa);
	HRESULT GetHostByName(sockaddr_in &psa,const char* name,USHORT hort=0);
	char *GetHostByAddr(sockaddr_in *psa);
	HRESULT WSAAsyncSelect(HWND hWnd,u_int wMsg,long lEvent);

	inline int ShutDown(int how);

	inline void GetHostName(char *name,int len);

	DWORD GetLocalIP();

	SOCKET	m_socket;
private:
};

inline void ZSocket::Release()
{
	Close();
}

inline void ZSocket::GetHostName(char *name,int len)
{
	gethostname(name,len);
}

inline int ZSocket::ShutDown(int how)
{
	return shutdown(m_socket,how);
}
/*
//////////////////////////////////////////////////////////////////////
//	ZWndAsyncSocket

//wnd message
#define WM_ZEPHYR_SOCKETEVENT	WM_USER+1

//wnd message func
long OnSocketEvent(WPARAM wParam,LPARAM lParam);

class ZWndAsyncSocket;

//////////////////////////////////////////////////////////////////////
//	_ZWNDASYNCSOCKETDATA

struct _ZWNDASYNCSOCKETDATA{
	SOCKET				socket;
	ZWndAsyncSocket		*link;

	_ZWNDASYNCSOCKETDATA(){
		socket=0;
		link=NULL;
	}

	inline bool operator  ==  (const _ZWNDASYNCSOCKETDATA &s) const;

	inline bool operator != (const _ZWNDASYNCSOCKETDATA &s) const;
};

inline bool _ZWNDASYNCSOCKETDATA::operator  ==  (const _ZWNDASYNCSOCKETDATA &s) const
{
	return this->socket  ==  s.socket&&this->link  ==  s.link;
}

inline bool _ZWNDASYNCSOCKETDATA::operator != (const _ZWNDASYNCSOCKETDATA &s) const 
{ 
	return !((*this)  ==  s); 
}

//////////////////////////////////////////////////////////////////////
//	ZWndAsyncSocket

class ZWndAsyncSocket : public ZSocket{
protected:
	static zlink<_ZWNDASYNCSOCKETDATA,256,16>	m_Link;
	_ZWNDASYNCSOCKETDATA	*_data;

public:
	ZWndAsyncSocket()	{	_data=NULL;	}
	virtual ~ZWndAsyncSocket()	{	Release();	}

	HRESULT Create(int nType=SOCK_STREAM);
	void Release();

	static ZWndAsyncSocket *GetHandle(SOCKET socket);

//virtual
	virtual void OnReceive();
	virtual void OnSend();
	virtual void OnOutOfBandData();
	virtual void OnAccept();
	virtual void OnConnect();
	virtual void OnClose();
};
*/
#endif//__ZEPHYR_SOCKET_H