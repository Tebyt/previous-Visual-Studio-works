// Net\MsgThread.h
// 消息线程池
// Write by zhs007			y2k3-5-29

#ifndef _ZEPHYR_NET_MSGTHREAD_H
#define _ZEPHYR_NET_MSGTHREAD_H

#include <ZThread.h>
#include <Net\TCP_Server.h>

class _MsgPool;

///////////////////////////////////////////////////////////////////////////////////////////////
//	MsgThreadPool

const MSG_THREADPOOL_INIT				=	0x01;

class ZEPHYR_NET_API MsgThreadPool{
public:
	struct _Key{
		ContextKey			*pKey;
		int					iMsgLen;
		void				*pDelPoint;
		ZNetServerModule	*pModule;
		_MsgPool			*pMsgPool;
		BYTE				*pMsg;
	};

	struct _ThreadParam{
		MsgThreadPool		*lpModule;
		ZThread				*lpThread;
	};
private:
	int								m_iMaxThreads;

	HANDLE							m_CompletionPort;

	ZState_Byte						m_bState;

	ZThread							*m_MsgThread;
	_ThreadParam					*m_ThreadParam;

	ZThreadSystem					*m_pThreadSystem;
public:
	inline MsgThreadPool();
	virtual ~MsgThreadPool() { Release(); }

	HRESULT Init(int iMaxThreads);

	inline void AddMsg(MsgThreadPool::_Key *pKey);

	inline void SetThreadSystem(ZThreadSystem *pThreadSystem);

	HANDLE GetCompletionPort() { return m_CompletionPort; }

	inline HRESULT HandleMessage(MsgThreadPool::_Key *pKey);

	void Release();
private:
	HRESULT CreateThreads();

	void EndRecvThread();
};

inline MsgThreadPool::MsgThreadPool()
{
	m_iMaxThreads = 0;

	m_CompletionPort = NULL;

	m_pThreadSystem = NULL;

	m_MsgThread = NULL;
	m_ThreadParam = NULL;
}

inline void MsgThreadPool::SetThreadSystem(ZThreadSystem *pThreadSystem)
{
	ZASSERT(pThreadSystem);

	m_pThreadSystem = pThreadSystem;
}

HRESULT MsgThreadPool::HandleMessage(MsgThreadPool::_Key *pKey)
{
	ZASSERT(pKey && pKey->pModule);

	return pKey->pModule->HandleMessage(pKey->pKey,pKey->pMsg,pKey->iMsgLen,false);
}

inline void MsgThreadPool::AddMsg(MsgThreadPool::_Key *pKey)
{
	ZASSERT(pKey);
	ZASSERT(pKey->iMsgLen > 0);

	PostQueuedCompletionStatus(m_CompletionPort,pKey->iMsgLen,(ULONG_PTR)pKey,NULL);
}

///////////////////////////////////////////////////////////////////////////////////////////////
//	_MsgPool

class ZEPHYR_NET_API _MsgPool{
public:
	_MsgPool() { ; }
	virtual ~_MsgPool() { ; }

	virtual MsgThreadPool::_Key *AddNode(ZNetServerModule *pModule,ContextKey *pKey,_MsgHead *pMsg,int iMsgLen) = 0;

	virtual void DelNode(MsgThreadPool::_Key *Node) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////
//	MsgPool

template<int MSG_SIZE,int LINK_SIZE,int LINK_ADD_SIZE>
class MsgPool : public _MsgPool{
public:
	struct _Key : public MsgThreadPool::_Key{
		BYTE	MsgData[MSG_SIZE];
	};
private:
	ZDLinkEx<_Key,LINK_SIZE,LINK_ADD_SIZE>		m_KeyLink;
	ZCriticalSection							m_KeyLock;
public:
	MsgPool() { ; }
	~MsgPool() { ; }

	virtual MsgThreadPool::_Key *AddNode(ZNetServerModule *pModule,ContextKey *pKey,_MsgHead *pMsg,int iMsgLen);

	virtual void DelNode(MsgThreadPool::_Key *Node);
};

template<int MSG_SIZE,int LINK_SIZE,int LINK_ADD_SIZE>
MsgThreadPool::_Key *MsgPool<MSG_SIZE,LINK_SIZE,LINK_ADD_SIZE>::AddNode(ZNetServerModule *pModule,ContextKey *pKey,_MsgHead *pMsg,int iMsgLen)
{
	ZASSERT(pModule && pKey && pMsg && iMsgLen > 0);

	if(iMsgLen > MSG_SIZE)
	{
		ZRet(E_FAIL,"MsgPool::AddNode(%d) fail!",iMsgLen);

		return NULL;
	}

	m_KeyLock.Lock();
	_Key *cur = m_KeyLink.GetEndObjPoint();
	cur->pDelPoint = m_KeyLink.GetEnd();
	m_KeyLink.Add();
	m_KeyLock.Unlock();

	cur->pKey = pKey;
	cur->iMsgLen = iMsgLen;
	cur->pModule = pModule;
	cur->pMsg = &(cur->MsgData[0]);
	cur->pMsgPool = this;
	memcpy(cur->MsgData,pMsg,iMsgLen);

	return cur;
}

template<int MSG_SIZE,int LINK_SIZE,int LINK_ADD_SIZE>
void MsgPool<MSG_SIZE,LINK_SIZE,LINK_ADD_SIZE>::DelNode(MsgThreadPool::_Key *Node)
{
	ZASSERT(Node);

	m_KeyLock.Lock();

	m_KeyLink.Del(Node->pDelPoint);

	m_KeyLock.Unlock();
}

#endif//_ZEPHYR_NET_MSGTHREAD_H