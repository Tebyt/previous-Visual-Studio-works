#ifndef ZEPHYR_NET_SERVER_CENTERSERVER_H
#define ZEPHYR_NET_SERVER_CENTERSERVER_H

#include <Net\TCP_Server.h>
#include <Net\Client\CenterServer.h>

void _CenterServerMsg(DWORD IP,WORD Port,void *Msg,int megLen);

void _CenterServerMsg2Str(char *Str,int strLen,DWORD IP,WORD Port,void *Msg,int msgLen);

void _RefurbishServerList();

//////////////////////////////////////////////////////////////////////
//	ZCenterServer

class ZCenterServer : public ZNetServerModule{
protected:
	ZLinkEx<ServerData,16,4>	m_ServerLink;
	ZCriticalSection			m_ServerLinkLock;
public:
	inline ZCenterServer(DWORD wndMsg);

	virtual HRESULT Init(WORD port);

	virtual HRESULT HandleMessage(ContextKey *pKey,void *buf,int len,bool bUseMsgPool = true);

	virtual HRESULT TimerFunc(void *lpParam);

	void Release();

	inline HRESULT BeginList();

	inline void GetList(void* &index,ServerData* &Data);

	inline void EndList();

	inline int GetServerNums();

	void KillServer(int index);

	bool ServerIsRuning(int index);

	//注册到web服务器
	HRESULT LoginServer(const char *server);
protected:
	//判断服务是否已经被注册
	bool CheckServer(ServerData *server);

//handle message
	//get server list
	HRESULT OnGetServerList(ContextKey *pKey,CenterServerGetServerList &msg);
	//reg server
	HRESULT OnRegServer(ContextKey *pKey,CenterServerServer &msg);
	//kill server
	HRESULT OnKillServer(CenterServerServer &msg);
};

inline ZCenterServer::ZCenterServer(DWORD wndMsg) : ZNetServerModule(wndMsg)
{	
	m_listenPort = 1024;
}

inline int ZCenterServer::GetServerNums()
{
	return m_ServerLink.GetUsed();
}

inline HRESULT ZCenterServer::BeginList()
{
	if(m_ServerLink.GetUsed()  ==  0)
		return E_FAIL;

	m_ServerLinkLock.Lock();

	return S_OK;
}

inline void ZCenterServer::GetList(void* &index,ServerData* &Data)
{
	m_ServerLink.GetData(Data,index);
}

inline void ZCenterServer::EndList()
{
	m_ServerLinkLock.Unlock();
}

#endif