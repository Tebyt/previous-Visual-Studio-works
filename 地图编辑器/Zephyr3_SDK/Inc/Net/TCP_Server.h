#ifndef ZEPHYR_TCP_SERVER_MODULE_H
#define ZEPHYR_TCP_SERVER_MODULE_H

#include <zthread.h>
#include <zlock.h>
#include <Net\zsocket.h>
#include <Net\netmsg.h>

//--------------------------------------------------------------------
//contexkey

//ContextKey state
#define ZEPHYR_CONTEXKEY_CLOSEHANDLE	0x01
#define ZEPHYR_CONTEXKEY_RECVDATA		0x02

struct ZEPHYR_NET_API ContextKey{
	SOCKET				sock;								//socket
	OVERLAPPED			ovIn;								//overlapped recv
	ZNetStream			recvStream;							//recv data
	WSABUF				recvBuf;
	ZCriticalSection	sendStreamLock;
	ZNetStream			sendStream;
	DWORD				dwWant;								//还需要读取的长度
	OVERLAPPED			ovOut;								//overlapped send
	DWORD				dwRequestID;						//请求ID号
	void				*Data;								//附属数据

	void _init()
	{
		sock = NULL;
		dwWant = 0;
		Data = NULL;
		dwRequestID = 0;
		ovIn.hEvent = NULL;
		recvStream.Clear();
		sendStream.Clear();
	}

	void _release()
	{
		if(sock)
			ZCloseSocket(sock);

		if(ovIn.hEvent)
		{
			CloseHandle(ovIn.hEvent);

			ovIn.hEvent = NULL;
		}
	}

	void _shutdown()
	{
		ZASSERT(sock);

		shutdown(sock,SD_SEND);
	}

	void *_getmsgdata(unsigned int msgLen)
	{
		ZASSERT(msgLen);

		sendStreamLock.Lock();
		void *dat = sendStream.AddData(NULL,msgLen);
		sendStreamLock.Unlock();

		return dat;
	}
};

DWORD SendMsg(ContextKey *pKey,void *Msg,DWORD Size);

DWORD SendData(ContextKey *pKey,void *Data,DWORD Size);

//////////////////////////////////////////////////////////////////////
//	ZNetServerModule

class ZNetServerModule;

struct __recv_param{
	ZNetServerModule	*lpModule;
	ZThread				*lpThread;
};

DWORD WINAPI _recvfunc(void *lpParam);
DWORD WINAPI __nsm_timerfunc(void *lpParam);

typedef ZLinkEx<ContextKey,128,128>	contextkey_list;

//ZNetServerModule State
const BYTE	ZNETSERVER_STATE_MAINTHREAD	=	0x01;
const BYTE	ZNETSERVER_STATE_RECV		=	0x02;
const BYTE	ZNETSERVER_STATE_TIMER		=	0x04;

class ZEPHYR_NET_API ZNetServerModule : public ZThread{
	friend DWORD WINAPI _recvfunc(void *lpParam);
	friend DWORD WINAPI __nsm_timerfunc(void *lpParam);
protected:
	ZState_Byte			m_bState;

	ZSocket				m_listen;		//listen socket
	WORD				m_listenPort;	//listen port

	contextkey_list		m_Link;
	ZCriticalSection	m_linkLock;

	ZThread				*m_lpRecvThread;
	DWORD				m_dwRecvThreads;
	__recv_param		*m_lpRecvParam;

	HANDLE				m_CompletionPort;

	ZThread				m_TimerThread;
	DWORD				m_dwTimer;
	ZCriticalSection	m_TimerLock;

	HWND				m_dstWnd;
	DWORD				m_wndMsg;

	ZNetStream			m_BroadCastStream;
	ZCriticalSection	m_BroadCastLock;
public:
	inline ZNetServerModule(DWORD wndMsg);
	virtual ~ZNetServerModule() { CleanUp(); }

//	DWORD GetSocketList(SOCKET *list,int len);

	HRESULT Init(WORD port);

	virtual HRESULT HandleMessage(ContextKey *pKey,void *buf,int len,bool bUseMsgPool = true) = 0;

	virtual HRESULT TimerFunc(void *lpParam) { return S_OK; }

	virtual HRESULT Run(void *lpparam);

	virtual void ClientCut(ContextKey *pKey);

	void Release();

	DWORD SendMsg(ContextKey *pKey,void *msg,DWORD msg_len) { return ::SendMsg(pKey,msg,msg_len); }

	void _BroadCast(void *msg,DWORD msg_len);

	void BroadCast(void *msg,DWORD msg_len);

	void _BroadCast();

	inline void SetTimer(DWORD dwTimer);

	inline DWORD GetTimer();

	HRESULT CreateTimer(DWORD dwTimer);

	void SetHWND(HWND hWnd) { m_dstWnd = hWnd; }

	//删除一key
	inline void DeleteKey(ContextKey* &key);

	void GetKey(ContextKey* &key,void* &index);
protected:
	//时钟线程休眠
	void TimerFuncSleep(DWORD dwTimer) { m_TimerThread.Sleep(dwTimer); }
	//结束工作线程
	void EndRecvThread();
	//创建工作线程
	HRESULT CreateThreads();
	//recv
	void IssueRecv(ContextKey *pkey);
	//获得完成端口
	HANDLE GetCompletionPort() { return m_CompletionPort; }
	//断开所有连接
	bool CutAll();
	//服务器错误
	inline HRESULT Error(ContextKey *pkey,HRESULT hRet,char *text);
	//ShutDown Client
	inline void ShutDown(ContextKey *pKey);

	//Post Msg
	inline void PostMsg(DWORD wParam,DWORD lParam);
private:
	//释放资源
	void CleanUp();
};

inline ZNetServerModule::ZNetServerModule(DWORD wndMsg)	
{
	m_CompletionPort = NULL;
	m_lpRecvThread = NULL;
	m_dwRecvThreads = 0;
	m_lpRecvParam = NULL;
	m_dwTimer = 0;
	m_dstWnd = NULL;

	m_wndMsg = wndMsg;
}

inline void ZNetServerModule::DeleteKey(ContextKey* &pKey)
{
	pKey->_release();

	m_linkLock.Lock();
	m_Link.Del(pKey);
	m_linkLock.Unlock();

	pKey = NULL;
}

inline void ZNetServerModule::SetTimer(DWORD dwTimer)
{
	m_TimerLock.Lock();

	m_dwTimer = dwTimer;

	m_TimerLock.Unlock();
}

inline DWORD ZNetServerModule::GetTimer()
{
	m_TimerLock.Lock();

	DWORD dwTimer = m_dwTimer;

	m_TimerLock.Unlock();

	return dwTimer;
}

//服务器错误
inline HRESULT ZNetServerModule::Error(ContextKey *pkey,HRESULT hRet,char *text)
{
//	DeleteKey(pkey);
	return ZRet(hRet,"0x%x --- %s",pkey,text);
}

//ShutDown Client
inline void ZNetServerModule::ShutDown(ContextKey *pKey) 
{ 
	ZASSERT(pKey);

	shutdown(pKey->sock,SD_SEND); 
}

//Post Msg
inline void ZNetServerModule::PostMsg(DWORD wParam,DWORD lParam) 
{ 
	ZASSERT(m_dstWnd);

	PostMessage(m_dstWnd,m_wndMsg,wParam,lParam); 
}

#endif