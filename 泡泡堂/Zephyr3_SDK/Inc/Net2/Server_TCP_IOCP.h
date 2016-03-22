/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Net2\Server_TCP_IOCP.h

							Describe:	TCP服务器 - IOCP

							Author:		赵洪松(xueren)

							CreateTime: 2003.11.6
							UpdateTime:
*/

#ifndef _ZEPHYR_NET_2_SERVER_TCP_IOCP_H
#define _ZEPHYR_NET_2_SERVER_TCP_IOCP_H

#include <ZDebug.h>
#include <Net2\BaseDef.h>
#include <Net2\NetStream.h>
#include <Net2\ZSocket.h>

////////////////////////////////////////////////////////////////////////////////
// ZNet2
namespace ZNet2{

	////////////////////////////////////////////////////////////////////////////
	// TCPServer_IOCP
	// TCP服务器 － IOCP

	class TCPServer_IOCP{
	public:
		class ContextKey;

		typedef ZLinkEx<ContextKey,128,128>		ContextKeyList;
/*
	public:
		inline ZNetServerModule(DWORD wndMsg);
		virtual ~ZNetServerModule() { CleanUp(); }

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
	protected:
		ZState_Byte			m_bState;

		SOCKET				m_sockListen;		//listen socket
		WORD				m_portListen;		//listen port

		ContextKeyList		m_KeyList;
		ZCriticalSection	m_KeyListLock;

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
*/
	};

	////////////////////////////////////////////////////////////////////////////
	// TCPServer_IOCP::ContextKey

	class TCPServer_IOCP::ContextKey{
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
			if(m_Sock.IsInit())
				m_Sock.Close();

			if(m_ovIn.hEvent != NULL)
			{
				CloseHandle(m_ovIn.hEvent);

				m_ovIn.hEvent = NULL;
			}
		}

		// 关闭连接
		void ShutDown() {
			ZASSERT(m_Sock.IsInit());

			m_Sock.ShutDown(SD_SEND);
		}


	private:
		ZSocket				m_Sock;								//socket

		OVERLAPPED			m_ovIn;								//overlapped recv
		NetStream			m_recvStream;						//recv data
		WSABUF				m_recvBuf;							//recv param
		DWORD				m_dwWant;							//还需要读取的长度

		NetStream			m_sendStream;						//send data
		OVERLAPPED			m_ovOut;							//overlapped send

		LPVOID				m_pData;							//附属数据
	};
};

#endif//_ZEPHYR_NET_2_SERVER_TCP_IOCP_H