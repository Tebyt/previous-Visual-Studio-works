/*
							Zephyr Engine v3.0

								by �Ժ���(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Net2\SNK_TCP_IOCP.h

							Describe:	TCP���������� - IOCP

							Author:		�Ժ���(xueren)

							CreateTime: 2003.11.06
							UpdateTime: 2003.12.05	-	���� �ӿ�
										2003.12.22	-	�޸� Send�������߳�����ȥ���� SendMsg_Head��SendMsg_Data �Ƚӿ�

								zhs007 @ 2005.11.07
									�� contextKey ���� IsInit �ӿ�
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
	// TCP������ �� IOCP

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
		// ���캯��
		SNK_TCP_IOCP(LPMsgWorker pMsgWorker) {

			SetThreads(1,2);

			m_recvEvent = m_sendEvent = NULL;

			m_lpMsgWorker = pMsgWorker;
		}

		// ��������
		virtual ~SNK_TCP_IOCP() { Release(); }

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
		inline int SendMsg(SNK_TCP_IOCP::LPContextKey pKey,LPVOID pMsg,int msgLen);

		// SendMsg
		virtual int SendMsg(LPVOID pAddr,LPVOID pMsg,int msgLen);

		// ��������
		inline int Send(LPVOID pAddr,LPVOID pMsg,int msgLen);

		// �㲥
		void BroadCastMsg(SNK_TCP_IOCP::LPContextKey pAddr,LPVOID pMsg,int msgLen);

		// ������Ϣ���
		HRESULT Error(SNK_TCP_IOCP::LPContextKey pKey,HRESULT hRet,const char* str);

		// �������
		virtual HRESULT Error(LPVOID pAddr,HRESULT hRet,const char* str) {
			return Error((ZNet2::SNK_TCP_IOCP::LPContextKey)pAddr,hRet,str);
		}

		// ������ӵ�ַ˽������
		virtual void SetData(LPVOID pAddr,LPVOID pData) {

			SetData((SNK_TCP_IOCP::LPContextKey)pAddr,pData);
		}

		// ������ӵ�ַ˽������
		inline void SetData(SNK_TCP_IOCP::LPContextKey pAddr,LPVOID pData);

		// ������ӵ�ַ˽������
		virtual LPVOID GetData(LPVOID pAddr) {
			return GetData((SNK_TCP_IOCP::LPContextKey)pAddr);
		}

		// ������ӵ�ַ˽������
		inline LPVOID GetData(SNK_TCP_IOCP::LPContextKey pAddr);

		// �Ͽ��ͻ�������
		void CutClient(SNK_TCP_IOCP::LPContextKey& pAddr) {

			EndConnect(pAddr);

//			Recv(pAddr);
////			ClientCut(pAddr);
		}

		// ����KeyList
		void Lock_KeyList() { m_KeyLock.Lock(); }
		// ����KeyList
		void Unlock_KeyList() { m_KeyLock.Unlock(); }
		// ����Addr
		SNK_TCP_IOCP::LPContextKey FindAddr_dw(DWORD dwData);

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

		// Recv
		void Recv(SNK_TCP_IOCP::LPContextKey pKey);

		// �����ɶ˿ھ��
		HANDLE GetCompletionPort() {
			return m_CompletionPort;
		}

		// Delete Key
		// ע�⣺�����������Ϊ��
		void DeleteKey(SNK_TCP_IOCP::LPContextKey &pKey);

		// �����ж�
		inline void EndConnect(SNK_TCP_IOCP::LPContextKey pKey);

		// �ͻ��˶Ͽ�����
		void ClientCut(SNK_TCP_IOCP::LPContextKey &pKey);

		// �ͻ�������
		void ClientConnect(SNK_TCP_IOCP::LPContextKey &pKey) {

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

		// ��Դ�ͷ�
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

		// �ر�����
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

		// ����SOCKET
		void SetSocket(SOCKET sock) {
			m_Sock.SetSocket(sock);

#ifdef _ZEPHYR_NET_21__
			BuildInfo();
#endif // _ZEPHYR_NET_21__
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
#ifdef _ZEPHYR_NET_21__TMP

		// ������Ϣ
		// ������pMsg Ϊ��Ϣָ�룬����Ϣͷ
		//		 dwSize Ϊ��Ϣ����
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

		// ������Ϣ
		// ������pMsg Ϊ��Ϣָ�룬����Ϣͷ
		//		 dwSize Ϊ��Ϣ����
		int SendMsg(void* pMsg,DWORD dwSize) {
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
#endif // _ZEPHYR_NET_21__
	private:
#ifdef _ZEPHYR_NET_21__
		char				m_strInfo[_INFO_LEN];	// �����Ϣ
#endif // _ZEPHYR_NET_21__
		ZSocket				m_Sock;			// socket

		OVERLAPPED			m_ovIn;			// overlapped recv
		NetStream			m_recvStream;	// recv stream
		WSABUF				m_recvBuf;		// recv param
		DWORD				m_dwWant;		// ����Ҫ���յĳ���
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

		LPVOID				m_pData;		// ��������
	public:
		ZCriticalSection	m_lock;
		ZCriticalSection	m_sendLock;
	};

	////////////////////////////////////////////////////////////////////////////
	// SNK_TCP_IOCP
	// TCP������ �� IOCP
	// �������� ʵ��

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

	// ������ӵ�ַ˽������
	inline void SNK_TCP_IOCP::SetData(SNK_TCP_IOCP::LPContextKey pAddr,LPVOID pData)
	{
		ZASSERT(pAddr != NULL);

		pAddr->SetData(pData);
	}

	// ������ӵ�ַ˽������
	inline LPVOID SNK_TCP_IOCP::GetData(SNK_TCP_IOCP::LPContextKey pAddr)
	{
		ZASSERT(pAddr != NULL);

		return pAddr->GetData();
	}

	// ��������
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

	// �����ж�
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