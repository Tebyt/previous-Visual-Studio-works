#ifndef ZEPHYR_GAME_CENTERSERVER_SERVER_H
#define ZEPHYR_GAME_CENTERSERVER_SERVER_H

#ifndef __ZEPHYR_GAME_CS_SERVER
#define __ZEPHYR_GAME_CS_SERVER
#endif

#include <ZState.h>
#include <ZList.h>
//#include <Database\ADO.h>
#include <Net15\TCP_Server.h>
#include <Net15\Client\CenterServer.h>
#include <Net15\Client\LoginServer.h>
#include <Net15\Msg\Game_CenterServer.h>
#include <Net15\Msg\LoginServer.h>

///////////////////////////////////////////////////////////////////////////////////
//	GCS_GameDatabaseManage

class FLYINGMAGIC_2_CORE_API GCS_GameDatabaseManage{
public:
	struct _Data{
		DWORD	NameID;
		DWORD	dwSQLIP;
		char	ID[DB_USER_ID_LEN];
		char	PSW[DB_USER_PSW_LEN];
		char	Table[DB_TABLENAME_LEN];
	};
private:
	ZCriticalSection			m_Lock;
	ZLinkEx<_Data,64,16>		m_DataLink;
public:
	GCS_GameDatabaseManage() { ; }

	void Load();

	void Save();

	void Add(DWORD NameID,DWORD IP,const char *ID,const char *PSW,const char *Tabel);

	void Del(DWORD index);

	GCS_GameDatabaseManage::_Data *Find(DWORD NameID);

	void GetData(GCS_GameDatabaseManage::_Data* &dat,void* &index);
private:
};

///////////////////////////////////////////////////////////////////////////////////
//	GCS_LoginClient

class GCS_UserService;

class FLYINGMAGIC_2_CORE_API GCS_LoginClient : public ZLoginServer_Client{
private:
	GCS_UserService	*m_pServer;
public:
	GCS_LoginClient() { m_pServer = NULL; }

	inline void SetServer(GCS_UserService *pServer);

	//virtual from ZNetClientModule
	//服务器断开连接
	virtual void ServerCut();
private:
	//virtual from ZLoginServer_Client
	//On Msg Ret Login
	virtual HRESULT OnMsgRetLogin(LoginServerRet &Msg);
	//virtual from ZLoginServer_Client
	//On Msg Ret Reg
	virtual HRESULT OnMsgRetReg(LoginServerRet &Msg);
};

inline void GCS_LoginClient::SetServer(GCS_UserService *pServer)
{
	ZASSERT(pServer);

	m_pServer = pServer;
}

///////////////////////////////////////////////////////////////////////////////////
//	GCS_UserManage

class FLYINGMAGIC_2_CORE_API GCS_UserManage{
public:
	struct _UserData{
		ContextKey		*pKey;
		void			*pServer;
		_BaseUserData	Base;
	};
private:
	ZCriticalSection			m_Lock;
	ZLinkEx<_UserData,256,256>	m_DataLink;

	ZList<DWORD,256,256>		m_IDList;

	DWORD						m_UserID;
public:
	GCS_UserManage() { m_UserID = 1; }

	HRESULT Init();

	void Release();

	GCS_UserManage::_UserData *FindUser(const char *strID);

	GCS_UserManage::_UserData *FindUser(DWORD UserID);

	GCS_UserManage::_UserData *UserComeIn(const char *strID,const char *strName,bool bSex,BYTE bLogo,ContextKey *pKey);

//	void UserLeft(const char *strID);

	void UserLeft(DWORD UserID);
private:
	inline void DelUser(GCS_UserManage::_UserData *User);
};

inline void GCS_UserManage::DelUser(GCS_UserManage::_UserData *User)
{
	m_Lock.Lock();
	m_IDList.Add(User->Base.dwID);
	m_DataLink.Del(User);
	m_Lock.Unlock();
}

///////////////////////////////////////////////////////////////////////////////////
//	GCS_UserService

class GCS_GSService;

class FLYINGMAGIC_2_CORE_API GCS_UserService : public ZNetServerModule{
	friend class GCS_LoginClient;
private:
	GCS_GSService		*m_pGSService;
	GCS_LoginClient		m_LoginClient;

	GCS_UserManage		m_UserManage;

	WORD				m_MyServerID;
	ServerData			m_Data;
	DWORD				m_dwCenterServerIP;
	WORD				m_wCenterServerPort;
public:
	inline GCS_UserService(WORD ServerID,DWORD wndMsg);

	HRESULT Init(GCS_GSService *pGSService,WORD port,const char *strName,const char *strID,const char *strPSW);

	void Release();

	//virtual from ZNetServerModule
	virtual HRESULT HandleMessage(ContextKey *pKey,void *buf,int len,bool bUseMsgPool = true);

	//virtual from ZNetServerModule
	virtual void ClientCut(ContextKey *pKey);

	GCS_UserManage *GetUserManage() { return &m_UserManage; }
private:
//Msg
	//Msg Reg
	HRESULT OnMsgReg(ContextKey *pKey,LoginServerReg &Msg);
	//Msg Login
	HRESULT OnMsgLogin(ContextKey *pKey,LoginServerLogin &Msg);
	//Msg GetServerList
	inline HRESULT OnMsgGetServerList(ContextKey *pKey,GCS_GetServerList &Msg);
	//Msg Logout
	HRESULT OnMsgLogout(ContextKey *pKey,GCS_Logout &Msg);

	//Logout
	void Logout() { KillServer(m_dwCenterServerIP,m_wCenterServerPort,m_Data); }
	//UserComeIn
	void UserComeIn(ContextKey *pKey,const char *ID,const char *Name,bool bSex,BYTE bLogo);
	//KickUser
	inline void KickUser(ContextKey *pKey);

	//ret Login fail
	void SendMsgRetLogin(ContextKey *pKey,BYTE State);
	//ret Reg fail
	void SendMsgRetReg(ContextKey *pKey,BYTE State);
	//ret Login ok
	void SendMsgUserData(ContextKey *pKey,DWORD dwID,const char *ID,const char *Name,bool bSex,BYTE bLogo);
	//Msg ServerList
	void SendMsgServerList(ContextKey *pKey,WORD NameID);
};

inline GCS_UserService::GCS_UserService(WORD ServerID,DWORD wndMsg) : ZNetServerModule(wndMsg)
{ 
	ZASSERT(ServerID);

	m_MyServerID = ServerID;

	m_pGSService = NULL;
}

//KickUser
inline void GCS_UserService::KickUser(ContextKey *pKey) 
{ 
	ZASSERT(pKey);

	ShutDown(pKey);
}

//Msg GetServerList
inline HRESULT GCS_UserService::OnMsgGetServerList(ContextKey *pKey,GCS_GetServerList &Msg)
{
	ZASSERT(m_pGSService);

	SendMsgServerList(pKey,Msg.GetData()->NameID);

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////
//	GCS_GSService

class FLYINGMAGIC_2_CORE_API GCS_GSService : public ZNetServerModule{
public:
	struct _ServerData{
		DWORD							dwID;
		DWORD							dwIP;
		WORD							wPort;
		WORD							NameID;
		char							Memo[__CS_MEMO_LEN];
		int								iUsers;
		GCS_GameDatabaseManage::_Data	*Database;
	};
private:
	WORD						m_MyServerID;
	ServerData					m_Data;
	DWORD						m_dwCenterServerIP;
	WORD						m_wCenterServerPort;

	DWORD						m_ServerID;

	ZCriticalSection			m_Lock;
	ZLinkEx<_ServerData,128,64> m_DataLink;

	GCS_GameDatabaseManage		*m_pDatabaseManage;
	GCS_UserManage				*m_pUserManage;
public:
	inline GCS_GSService(WORD ServerID,DWORD wndMsg);

	HRESULT Init(GCS_UserManage *pUserManage,WORD port,const char *Name);

	void Release();

	//virtual from ZNetServerModule
	virtual HRESULT HandleMessage(ContextKey *pKey,void *buf,int len,bool bUseMsgPool = true);

	//virtual from ZNetServerModule
	virtual void ClientCut(ContextKey *pKey);

	inline void SetDatabaseManage(GCS_GameDatabaseManage *pDatabaseManage);

	//获得服务器
	void GetServerData(GCS_GSService::_ServerData* &server,void* &index);
private:
	//Msg Login
	HRESULT OnMsgLogin(ContextKey *pKey,GCS_ServerLogin &Msg);
	//Msg ComeIn
	HRESULT OnMsgComeIn(ContextKey *pKey,GCS_ComeIn &Msg);

	//Send Msg RetLogin
	void SendMsgRetLogin(ContextKey *pKey,BYTE ret);
	//Send Msg ServerData
	void SendMsgServerData(ContextKey *pKey,GCS_GSService::_ServerData &Data);
	//Msg RetComeIn
	void SendMsgRetComeIn(ContextKey *pKey,DWORD ID);
	//Msg UserData
	void SendMsgUserData(ContextKey *pKey,DWORD ID,_BaseUserData &Data);

	//是否存在服务器
	bool CanFindServer(GCS_ServerLogin &Msg);
	//增加服务器
	GCS_GSService::_ServerData *AddServer(GCS_ServerLogin &Msg);
	//删除服务器
	void DelServer(GCS_GSService::_ServerData *server);

	//Logout
	void Logout() { KillServer(m_dwCenterServerIP,m_wCenterServerPort,m_Data); }
};

inline GCS_GSService::GCS_GSService(WORD ServerID,DWORD wndMsg) : ZNetServerModule(wndMsg)
{
	m_MyServerID = ServerID;

	m_ServerID = 1;

	m_pUserManage = NULL;
	m_pDatabaseManage = NULL;
}

inline void GCS_GSService::SetDatabaseManage(GCS_GameDatabaseManage *pDatabaseManage)
{
	ZASSERT(pDatabaseManage);

	m_pDatabaseManage = pDatabaseManage;
}

///////////////////////////////////////////////////////////////////////////////////
//	Game_CenterServer

//	WndMsg
const DWORD	WM_GCS_LCCUT		=	0x01;
const DWORD	WM_GCS_UPDATESERVER	=	0x02;

class FLYINGMAGIC_2_CORE_API Game_CenterServer{
protected:
	GCS_UserService			m_UserService;
	GCS_GSService			m_GSService;
	GCS_GameDatabaseManage	m_DBManage;
public:
	inline Game_CenterServer(WORD UserServiceID,WORD GSServiceID,DWORD wndMsg);

	//Init
	HRESULT Init(WORD port,const char *strName,const char *strID,const char *strPSW);
	//Release
	inline void Release();

	inline void SetThreadSystem(ZThreadSystem *pThreadSystem);

	inline void SetHWND(HWND hWnd);

	GCS_GameDatabaseManage *GetDBManage() { return &m_DBManage; }

	inline void GetServerData(GCS_GSService::_ServerData* &server,void* &index);
protected:
};

inline Game_CenterServer::Game_CenterServer(WORD UserServiceID,WORD GSServiceID,DWORD wndMsg)
			: m_UserService(UserServiceID,wndMsg),m_GSService(GSServiceID,wndMsg)
{ 
	m_DBManage.Load();

	m_GSService.SetDatabaseManage(&m_DBManage);
}

inline void Game_CenterServer::SetThreadSystem(ZThreadSystem *pThreadSystem)
{
	ZASSERT(pThreadSystem);

	m_UserService.SetThreadSystem(pThreadSystem);
	m_GSService.SetThreadSystem(pThreadSystem);
}

inline void Game_CenterServer::SetHWND(HWND hWnd)
{
	m_UserService.SetHWND(hWnd);
	m_GSService.SetHWND(hWnd);
}

//Release
inline void Game_CenterServer::Release()
{
	m_UserService.Release();
	m_GSService.Release();
}

inline void Game_CenterServer::GetServerData(GCS_GSService::_ServerData* &server,void* &index)
{
	m_GSService.GetServerData(server,index);
}

#endif