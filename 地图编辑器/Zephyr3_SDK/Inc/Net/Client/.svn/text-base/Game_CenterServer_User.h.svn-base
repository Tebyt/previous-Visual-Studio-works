#ifndef ZEPHYR_GAME_CENTERSERVER_CLIENT_USER_H
#define ZEPHYR_GAME_CENTERSERVER_CLIENT_USER_H

#include <Net\ZSocket.h>
#include <Net\TCP_Client.h>
#include <Net\Client\CenterServer.h>
#include <Net\Msg\Game_CenterServer.h>

/////////////////////////////////////////////////////////////////////////////////////
//	GCS_UserService_Client 

//Wnd Msg
const DWORD	WM_GCS_LOGINFAIL	=	0x01;
const DWORD	WM_GCS_REGFAIL		=	0x02;
const DWORD	WM_GCS_USERDATA		=	0x03;
const DWORD	WM_GCS_SERVERCUT	=	0x04;
const DWORD WM_GCS_SERVERLIST	=	0x05;

//State
const BYTE GCS_US_CLIENT_INIT	=	0x10;
const BYTE GCS_US_CLIENT_LOGIN	=	0x20;

class FLYINGMAGIC_2_CORE_API GCS_UserService_Client : public ZNetClientModule{
public:
	struct _ServerData{
		DWORD	NameID;
		int		iUsers;
		char	Memo[__CS_MEMO_LEN];
		DWORD	dwIP;
		WORD	wPort;
	};
private:
	WORD						m_ServerID;

	ZLinkEx<_ServerData,128,16>	m_ServerLink;
	ZCriticalSection			m_ServerLock;

	_BaseUserData				m_MyData;
public:
	inline GCS_UserService_Client(WORD ServerID,DWORD wndMsg);
	virtual ~GCS_UserService_Client() { DEBUGMESSAGE("GCS_UserService_Client Release!"); }

	//virtual from ZNetClientModule
	virtual HRESULT HandleMessage(void *buf,int len);
	//virtual from ZNetClientModule
	//服务器断开连接
	virtual void ServerCut();

	HRESULT Init(DWORD CS_IP,WORD CS_Port);

	void Release();

//用户操作
	void Login(const char *ID,const char *PSW);

	void Reg(ZUserInfo &UserInfo);

	void Logout();

	void GetServerList(WORD NameID);



	bool IsLogin() { return m_bState.Has(GCS_US_CLIENT_LOGIN); }

	void GetServer(GCS_UserService_Client::_ServerData* &dat,void* &index);

	_BaseUserData *GetMyBaseUserData() { return &m_MyData; }
private:
	//Msg RetLogin
	HRESULT OnMsgRetLogin(GCS_Ret &Msg);
	//Msg RetReg
	HRESULT OnMsgRetReg(GCS_Ret &Msg);
	//Msg UserData
	HRESULT OnMsgUserData(GCS_UserData &Msg);
	//Msg ServerList
	HRESULT OnMsgServerList(GCS_ServerList &Msg);
	//Msg ServerData
	inline HRESULT OnMsgServerData(GCS_US_ServerData &Msg);
	//Msg ServerList End
	inline HRESULT OnMsgServerListEnd();

	//Add Server
	void AddServer(_GCS_US_ServerData &Msg);
	//Clear ServerLink
	inline void ClearServerLink();
};

inline GCS_UserService_Client::GCS_UserService_Client(WORD ServerID,DWORD wndMsg)
		: ZNetClientModule(wndMsg)
{ 
	m_ServerID = ServerID; 
}

inline void GCS_UserService_Client::ClearServerLink()
{
	m_ServerLock.Lock();

	m_ServerLink.Clear();

	m_ServerLock.Unlock();
}

//Msg ServerData
inline HRESULT GCS_UserService_Client::OnMsgServerData(GCS_US_ServerData &Msg)
{
	AddServer(*(Msg.GetData()));

	return S_OK;
}

//Msg ServerList End
inline HRESULT GCS_UserService_Client::OnMsgServerListEnd()
{
	PostMsg(WM_GCS_SERVERLIST,0);

	return S_OK;
}

#endif