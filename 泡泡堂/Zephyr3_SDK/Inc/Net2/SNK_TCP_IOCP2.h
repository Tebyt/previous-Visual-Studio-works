/*
							Zephyr Engine v3.0

							by �Ժ���(xueren) 2005


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Net2\SNK_TCP_IOCP2.h

							Describe:	TCP���������� - IOCP

							Author:		�Ժ���(xueren)

							CreateTime: 2005.10.29
							UpdateTime: 
*/
#ifndef __ZEPHYR_3_NET_2_SNK_TCP_IOCP_2_H__
#define __ZEPHYR_3_NET_2_SNK_TCP_IOCP_2_H__

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

namespace ZNet2{
/*
	class ZEPHYR_NET_API SNK_TCP_IOCP2 : public ServiceNetKernel{
		friend DWORD WINAPI _recvfunc(LPVOID lpParam);
	public:
		class ContextKey;
		typedef ContextKey*	LPContextKey;

		typedef ZLinkEx<ContextKey,128,128>		ContextKeyList;

		struct RecvThreadParam{
			SNK_TCP_IOCP2*		lpModule;
			ZThread*			lpThread;
		};

		typedef RecvThreadParam*	LPRecvThreadParam;
	public:
		// ���캯��
		SNK_TCP_IOCP2(LPMsgWorker pMsgWorker);

		// ��������
		virtual ~SNK_TCP_IOCP2() { Release(); }

		// ��Դ�ͷ�
		void Release();

		// ��ʼ������
		HRESULT Init(ZSocketAddr& addr);

		// �����߳���
		// ������cpuThreads		-	һ��cpuͬʱ�����е��߳�����һ�������Ϊ 1
		//		 spareThreads	-	���õ��߳�����һ�������Ϊ 2
		// ע�⣺�����ڳ�ʼ����ǰ����
		void SetThreads(int cpuThreads,int spareThreads);

		// SendMsg
		inline int SendMsg(SNK_TCP_IOCP2::LPContextKey pAddr, LPVOID pMsg, int msgLen);

		// SendMsg
		virtual int SendMsg(LPVOID pAddr, LPVOID pMsg, int msgLen);

		// ��������
		inline int Send(LPVOID pAddr, LPVOID pMsg, int msgLen);

		// �㲥
		void BroadCastMsg(SNK_TCP_IOCP2::LPContextKey pAddr, LPVOID pMsg, int msgLen);

		// ������Ϣ���
		HRESULT Error(SNK_TCP_IOCP2::LPContextKey pKey, HRESULT hRet, const char* str);

		// �������
		virtual HRESULT Error(LPVOID pAddr, HRESULT hRet, const char* str) {
			return Error((SNK_TCP_IOCP2::LPContextKey)pAddr, hRet, str);
		}

		// ������ӵ�ַ˽������
		virtual void SetData(LPVOID pAddr, LPVOID pData) {
			SetData((SNK_TCP_IOCP2::LPContextKey)pAddr, pData);
		}

		// ������ӵ�ַ˽������
		inline void SetData(SNK_TCP_IOCP2::LPContextKey pAddr, LPVOID pData);

		// ������ӵ�ַ˽������
		virtual LPVOID GetData(LPVOID pAddr) {
			return GetData((SNK_TCP_IOCP2::LPContextKey)pAddr);
		}

		// ������ӵ�ַ˽������
		inline LPVOID GetData(SNK_TCP_IOCP2::LPContextKey pAddr);

		// �Ͽ��ͻ�������
		void CutClient(SNK_TCP_IOCP2::LPContextKey& pAddr);

		// �ж����пͻ�������
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

		// ������Ϣ�����߳�
		HRESULT CreateRecvThreads();

		// ������Ϣ�����߳�
		void EndRecvThreads();

		// ���߳� �� Listen Thread
		// virtual from ZThread
		virtual HRESULT Run(LPVOID lpparam);

		// �����ɶ˿ھ��
		HANDLE GetCompletionPort() {
			return m_CompletionPort;
		}

		// Delete Key
		// ע�⣺�����������Ϊ��
		void DeleteKey(SNK_TCP_IOCP2::LPContextKey &pKey);

		// �����ж�
		inline void EndConnect(SNK_TCP_IOCP2::LPContextKey pKey);

		// �ͻ��˶Ͽ�����
		void ClientCut(SNK_TCP_IOCP2::LPContextKey &pKey);

		// �ͻ�������
		void ClientConnect(SNK_TCP_IOCP2::LPContextKey &pKey) {

			ZASSERT(m_lpMsgWorker != NULL);

			m_lpMsgWorker->PeerConnect(pKey);
		}

		// ��Ϣ������
		HRESULT HandleMessage(LPVOID pMsg,int msgLen,LPVOID pAddr,LPVOID pThread) {

			ZASSERT(m_lpMsgWorker != NULL);

			return m_lpMsgWorker->HandleMessage(pMsg,msgLen,pAddr,pThread);
		}

		// ��÷����¼����
		HANDLE GetSendEvent() {
			return m_sendEvent;
		}

		// ��ý����¼����
		HANDLE GetRecvEvent() {
			return m_recvEvent;
		}

		// Recv
		void Recv(SNK_TCP_IOCP2::LPContextKey pKey);
	private:
		ContextKeyList		m_KeyList;	// KeyList
		ZCriticalSection	m_KeyLock;	// KeyList Lock

		ZSocket				m_sockListen;	// ����Socket
		ZSocketAddr			m_addrListen;	// ����Socket��ַ

		HANDLE				m_CompletionPort;	// ��ɶ˿ھ��
		int					m_cpuThreads;		// ��ɶ˿� cpu �߳���
		int					m_spareThreads;		// ��ɶ˿� �����߳���

		int					m_recvThreads;		// ʵ�ʽ����߳���
		ZThread*			m_lpRecvThread;		// �����߳�
		RecvThreadParam*	m_lpRecvParam;		// �����̲߳���

		ZState_DWord		m_dwState;			// ����

		HANDLE				m_recvEvent;
		HANDLE				m_sendEvent;

		LPMsgWorker			m_lpMsgWorker;		// ��Ϣ������
	};



	class ZEPHYR_NET_API SNK_TCP_IOCP2::ContextKey{
	public:
		enum{
			_INFO_LEN	=	64
		};
	public:
		// ���캯��
		ContextKey() { Init(); }
		// ��������
		~ContextKey() { Release(); }

		// ��ʼ��
		void Init() {
			m_dwWant = 0;

			m_pData = NULL;

			m_ovIn.hEvent = NULL;
			m_recvStream.Clear();

			m_sendStream.Clear();
			m_ovOut.hEvent = NULL;

			m_bRelease.Set(false);
			m_bHasData.Set(false);
			m_bEndConnect.Set(false);

			m_recvData = NULL;

			m_Sock = NULL;

			memset(&m_ovIn, 0, sizeof(m_ovIn));			// overlapped recv
			memset(&m_ovOut, 0, sizeof(m_recvBuf));		// overlapped send

			memset(&m_recvBuf, 0, sizeof(m_recvBuf));	// recv param

			m_strInfo[0] = '\0';
		}

		// ��Դ�ͷ�
		void Release() {

			if(m_bRelease.Set(true))
				return ;

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

		// �ر�����
		void ShutDown() {

			if(m_Sock.IsInit())
				m_Sock.ShutDown(SD_BOTH);
		}

		// ����SOCKET
		void SetSocket(SOCKET sock) {
			m_Sock.SetSocket(sock);

			BuildInfo();
		}

		SOCKET GetSocket() {
			return m_Sock.GetSocket();
		}

		// ��� ������
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

		// ������������
		int Analyse_RecvData(DWORD recvLen,_block* block) {
			return m_recvStream.Analyse_InData(recvLen,block,m_dwWant);
		}

		// ��õ�ַ
		void GetAddr(ZSocketAddr& addr) {
			int len = sizeof(ZSocketAddr);

			if(m_Sock.IsInit())
			{
				m_Sock.GetPeerName(&addr,&len);
				ZASSERT(len == sizeof(ZSocketAddr));
			}
		}

		// ������Ϣ
		// ������pMsg Ϊ��Ϣָ�룬����Ϣͷ
		//		 dwSize Ϊ��Ϣ����
		DWORD SendMsg(void* pMsg,DWORD dwSize) {
			ZASSERT(pMsg != NULL);
			ZASSERT(dwSize > 0);
			ZASSERT(dwSize <= MAX_PKG_SIZE);

			BYTE key = 0x7b;

			if(dwSize > 4)
				ZNet2::Encode((BYTE*)pMsg + 4,dwSize - 4,key);

			return Send(pMsg,dwSize);
		}

		// �����ͻ���
		// ע�⣺�����С�� 0 - MAX_PKG_SIZE ֮��
		LPVOID RequestSendBuff(DWORD dwSize = MAX_PKG_SIZE) {
			ZASSERT(dwSize > 0 && dwSize <= MAX_PKG_SIZE);
		}

		// ��Ϣ����
		DWORD Send(const void* pMsg,DWORD dwSize) {
			ZASSERT(pMsg);
			ZASSERT(dwSize > 0);
			ZASSERT(dwSize <= MAX_PKG_SIZE);

			if(m_bEndConnect.Get())
			{
				Debug("ContextKey::Send() end connect!");

				return 0;
			}

			if(!m_Sock.IsInit())
			{
				Debug("ContextKey::Send() sock is not init!");

				return 0;
			}

			Zephyr3::AutoLock lock(&m_sendLock);

			WSABUF buf = {dwSize,(char *)pMsg};
			DWORD sendLen,totalLen = 0;

			do{
				if(m_Sock.Send(&buf,1,&sendLen,0,&m_ovOut,NULL) != SOCKET_ERROR)
					totalLen += sendLen;
				else
				{
					DWORD ret = WSAGetLastError();

					if(ret != WSAEWOULDBLOCK && ret != WSA_IO_PENDING)
					{
						ZRet(E_FAIL,"SNK_TCP_IOCP::Send() 0x%x fail!",WSAGetLastError());

						if(ret == 0x2745 && ret == 0x2746)
							ShutDown();

						return SOCKET_ERROR;
					}

					return SOCKET_ERROR;
				}

			}while(totalLen < dwSize);

			return dwSize;
		}

		void RecvData() {
			m_bHasData.Set(true);
		}

		bool HasRecvData() {
			return m_bHasData.Get();
		}

		bool IsInit() {
			return m_Sock.IsInit();
		}

		// ���������Ϣ
		void BuildInfo() {
			char strIP[16];
			ZSocketAddr addr;

			GetAddr(addr);

			IP2Str(strIP, 16, addr.sin_addr.S_un.S_addr);

			_format_str(m_strInfo, "0x%x(%x %s:%d )", this, m_Sock.GetSocket(), strIP, addr.sin_port);
		}

		// ���������Ϣ
		const char* GetInfo() const {
			return m_strInfo;
		}
	private:
		char				m_strInfo[_INFO_LEN];	// �����Ϣ
		ZSocket				m_Sock;					// socket

		OVERLAPPED			m_ovIn;					// overlapped recv
		NetStream			m_recvStream;			// recv stream
		WSABUF				m_recvBuf;				// recv param
		DWORD				m_dwWant;				// ����Ҫ���յĳ���
		_block*				m_recvData;				// recv data

		NetStream			m_sendStream;			// send stream
		OVERLAPPED			m_ovOut;				// overlapped send

		Zephyr3::MulBool	m_bRelease;
		Zephyr3::MulBool	m_bHasData;
		Zephyr3::MulBool	m_bEndConnect;

		LPVOID				m_pData;				// ��������
	public:
		ZCriticalSection	m_lock;
		ZCriticalSection	m_sendLock;
	};

*/
}

#endif // _ZEPHYR_NET_SERVER__

#endif // __ZEPHYR_3_NET_2_SNK_TCP_IOCP_2_H__