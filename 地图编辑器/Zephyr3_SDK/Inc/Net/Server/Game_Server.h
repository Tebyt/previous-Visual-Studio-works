#ifndef ZEPHYR_GAME_SERVER_H
#define ZEPHYR_GAME_SERVER_H

#include <ZState.h>
#include <ZStack.h>
#include <Zlist.h>

#define __ZEPHYR_DATABASE_USE_ADO_H
#include <Database\ADO.h>

#include <FlyingMagic\BaseDef.h>
#include <Net\TCP_Server.h>
#include <Net\Msg\LoginServer.h>
#include <Net\Msg\Game_Server.h>
#include <Net\Client\CenterServer.h>
#include <Net\Client\Game_CenterServer.h>

///////////////////////////////////////////////////////////////////////////////////
//	GS_UserDataManage

const HRESULT	ZGS_UMD_NODATA					=	0x80000777;

const int		ZGS_UDM_GAMEPSW_LEN				=	16;

class GS_HallService;

//GS_UserDataManage State
const	BYTE	GS_USERDATAMANAGE_INIT			=	0x01;

//UserData State
const	BYTE	GS_USERDATA_IAMREADY			=	0x80;	//Ready?
const	BYTE	GS_USERDATA_WATCH				=	0x40;	//Watch?
const	BYTE	GS_USERDATA_PLAYING				=	0x20;	//Playing?
const	BYTE	GS_USERDATA_NEEDPSW				=	0x10;	//Game PSW
const	BYTE	GS_USERDATA_ESTOPIP				=	0x08;	//是否不和相同IP的用户游戏
const	BYTE	GS_USERDATA_ALLOWWATCH			=	0x04;	//是否允许其他用户旁观

class FLYINGMAGIC_2_CORE_API GS_UserDataManage{
public:
	struct _UserData{
		_BaseUserData	Base;
		WORD			RoomID;
		BYTE			RoomStation;
		ZState_Byte		bState;
		ContextKey		*pKey;
		char			GamePSW[ZGS_UDM_GAMEPSW_LEN];

		bool IsWatcher() {
			return bState.Has(GS_USERDATA_WATCH);
		}
	};
protected:
	ZCriticalSection			m_DBLock;
	ZDatabase					m_Database;
	char						m_DB_ID[DB_USER_ID_LEN];
	char						m_DB_PSW[DB_USER_PSW_LEN];
	char						m_TableName[DB_TABLENAME_LEN];
	DWORD						m_dwDB_IP;

	ZState_Byte					m_bState;

	GS_HallService				*m_pHallService;
public:
	inline GS_UserDataManage();

	HRESULT Init();

	inline void Set(DWORD IP,const char *strID,const char *strPSW,const char *TableName);

	void Release();
    
	virtual void *UserComeIn(_BaseUserData &Base,ContextKey *pKey) = 0;

	virtual void *FindUser(DWORD UserID) = 0;

	virtual void SendUserGameDataMsg(void *dat) = 0;
	
	virtual void SendUserList(void *dat) = 0;
	
	virtual void UserLeft(void *user) = 0;
	
	virtual void BroadCastUserComeIn(void *user) = 0;

	virtual void GetUser(GS_UserDataManage::_UserData* &user,void* &index) = 0;

	inline void SetService(GS_HallService *pHallService);

	bool IsInit() { return m_bState.Has(GS_USERDATAMANAGE_INIT); }

	inline void UserReady(void *user);
protected:
};

inline GS_UserDataManage::GS_UserDataManage()
{
	m_pHallService = NULL;
}

inline void GS_UserDataManage::SetService(GS_HallService *pHallService)
{
	ZASSERT(pHallService);

	m_pHallService = pHallService;
}

inline void GS_UserDataManage::Set(DWORD IP,const char *strID,const char *strPSW,const char *TableName)
{
	ZASSERT(strID && strPSW && TableName);

	m_dwDB_IP = IP;
	strcpy(m_DB_ID,strID);
	strcpy(m_DB_PSW,strPSW);
	strcpy(m_TableName,TableName);
}

inline void GS_UserDataManage::UserReady(void *user)
{
	ZASSERT(user);

	((_UserData *)user)->bState.Add(GS_USERDATA_IAMREADY);
}

///////////////////////////////////////////////////////////////////////////////////
//	GS_SimpleScore_UDM

//UserData State
const	BYTE	GS_SS_USERDATA_MAXSCORE			=	0x02;
const	BYTE	GS_SS_USERDATA_MINSCORE			=	0x01;

class FLYINGMAGIC_2_CORE_API GS_SimpleScore_UDM : public GS_UserDataManage{
public:
	struct _UserData : public GS_UserDataManage::_UserData{
		long			lScore;
		long			lWin,lLose,lTotal,lRunAway;
		long			lMinScore,lMaxScore,lMaxRunAway;

		void Init(){
			RoomID = 0;
			RoomStation = 0;
			pKey = NULL;
			bState = 0;
		}
	};
private:
	ZLinkEx<_UserData,512,128>	m_UserDataLink;
	ZCriticalSection			m_UserDataLock;
public:
	//virtual from GS_UserDataManage
	virtual void *UserComeIn(_BaseUserData &Base,ContextKey *pKey);
	//virtual from GS_UserDataManage
	virtual void *FindUser(DWORD UserID);
	//virtual from GS_UserDataManage
	//dat是从UserComeIn返回的参数
	virtual void SendUserGameDataMsg(void *dat);
	//virtual from GS_UserDataManage
	//dat是从UserComeIn返回的参数
	virtual void SendUserList(void *dat);
	//virtual from GS_UserDataManage
	//dat是从UserComeIn返回的参数
	virtual void UserLeft(void *user);
	//virtual from GS_UserDataManage
	//dat是从UserComeIn返回的参数
	virtual void BroadCastUserComeIn(void *user);
	//virtual from GS_UserDataManage
	virtual void GetUser(GS_UserDataManage::_UserData* &user,void* &index);

	HRESULT UpdateGameData(GS_SimpleScore_UDM::_UserData *pUser);
private:
	HRESULT UpdateUserData(GS_SimpleScore_UDM::_UserData *pUser);

	HRESULT GetUserData(GS_SimpleScore_UDM::_UserData &User);

	void DefaultGameData(GS_SimpleScore_UDM::_UserData &User);
};

///////////////////////////////////////////////////////////////////////////////////
//	GS_HallService

class GS_RoomService;

class FLYINGMAGIC_2_CORE_API GS_HallService : public ZNetServerModule{
private:
	int						m_iUsers;

	WORD					m_MyServerID;
	ServerData				m_Data;
	DWORD					m_dwCenterServerIP;
	WORD					m_wCenterServerPort;

	GCS_GSService_Client	*m_pGCSClient;
	GS_UserDataManage		*m_pUserDataManage;
	GameServerInfo			*m_pServerInfo;

	int						m_iTotalBroadCastTime;
public:
	inline GS_HallService(WORD ServerID,DWORD wndMsg);

	HRESULT Init(GCS_GSService_Client *pGCSClient,GS_UserDataManage *pUserDataManage,GameServerInfo *pServerInfo,WORD port,const char *Name);

	void Release();

	//virtual from ZNetServerModule
	virtual HRESULT HandleMessage(ContextKey *pKey,void *buf,int len,bool bUseMsgPool = true);

	//virtual from ZNetServerModule
	virtual void ClientCut(ContextKey *pKey);

	//virtual from ZNetServerModule
	virtual HRESULT TimerFunc(void *lpParam);

	inline void KickUser(ContextKey *pKey);

	ServerData *GetServerData() { return &m_Data; }

	int GetUsers() { return m_iUsers; }

	WORD GetServerID() { return m_MyServerID; }

	void UserComeIn(ContextKey *pKey,_BaseUserData &dat);

	//Room UserIn
	void Room_UserIn(ContextKey *pKey,DWORD UserID,WORD RoomID,BYTE RoomStation);
	//Room UserOut
	void Room_UserOut(ContextKey *pKey,DWORD UserID);

	void UserReady(ContextKey *pKey,DWORD UserID);

	void GameEnd(WORD RoomID);

	void BroadCast_UserGameData(GS_SimpleScore_UDM::_UserData *user,long lScore,BYTE bState);

	inline void GetUser(GS_UserDataManage::_UserData* &user,void* &index);
private:
	//Msg ComeIn
	HRESULT OnMsgComeIn(ContextKey *pKey,GS_Hall_ComeIn &Msg);
	//Msg Chat
	HRESULT OnMsgChat(ContextKey *pKey,GS_Hall_Chat &Msg);

	//Send Msg YourGamerData
	inline void SendMsgYourGameData(ContextKey *pKey,void *dat);
	//Send Msg UserList
	inline void SendMsgUserList(ContextKey *pKey,void *dat);
	//Send Msg ServerInfo
	void SendMsgServerInfo(ContextKey *pKey);
	//Send Msg UserComeOK
	void SendMsgServerComeOK(ContextKey *pKey);

	//BroadCast Msg UserComeIn
	inline void BroadCastUserComeIn(ContextKey *pKey,void *dat);
	//BroadCast Msg UserLeft
	void BroadCastUserLeft(ContextKey *pKey,void *dat);

	//Logout
	void Logout() { KillServer(m_dwCenterServerIP,m_wCenterServerPort,m_Data); }
};

inline GS_HallService::GS_HallService(WORD ServerID,DWORD wndMsg) : ZNetServerModule(wndMsg)
{
	m_MyServerID = ServerID;

	m_iUsers = 0;
	m_pGCSClient = NULL;
	m_pUserDataManage = NULL;
	m_iTotalBroadCastTime = 0;
}

//KickUser
inline void GS_HallService::KickUser(ContextKey *pKey) 
{ 
	ZASSERT(pKey);

	ShutDown(pKey);
}

//Send Msg YourGamerData
inline void GS_HallService::SendMsgYourGameData(ContextKey *pKey,void *dat)
{
	ZASSERT(pKey);
	ZASSERT(dat);
	ZASSERT(m_pUserDataManage);

	m_pUserDataManage->SendUserGameDataMsg(dat);
}

//Send Msg UserList
inline void GS_HallService::SendMsgUserList(ContextKey *pKey,void *dat)
{
	ZASSERT(pKey);
	ZASSERT(dat);
	ZASSERT(m_pUserDataManage);

	m_pUserDataManage->SendUserList(dat);
}

//BroadCast Msg UserComeIn
inline void GS_HallService::BroadCastUserComeIn(ContextKey *pKey,void *dat)
{
	ZASSERT(pKey);
	ZASSERT(dat);
	ZASSERT(m_pUserDataManage);

	m_pUserDataManage->BroadCastUserComeIn(dat);
}

inline void GS_HallService::GetUser(GS_UserDataManage::_UserData* &user,void* &index)
{
	ZASSERT(m_pUserDataManage);

	m_pUserDataManage->GetUser(user,index);
}

///////////////////////////////////////////////////////////////////////////////////
//	GS_RoomService

class ZGameRoom;

class FLYINGMAGIC_2_CORE_API GS_RoomService : public ZNetServerModule{
	friend class ZGameRoom;
private:
	GS_UserDataManage		*m_pUserDataManage;
	ZGameRoom				**m_pGameRoom;
	GameServerInfo			*m_pServerInfo;
	GS_HallService			*m_pHallService;

	int						m_RoomTime;
public:
	inline GS_RoomService(DWORD wndMsg);

	HRESULT Init(GS_HallService *pHallService,GS_UserDataManage *pUserDataManage,GameServerInfo *pServerInfo,WORD port);

	void Release();

	//virtual from ZNetServerModule
	virtual HRESULT HandleMessage(ContextKey *pKey,void *buf,int len,bool bUseMsgPool = true);

	//virtual from ZNetServerModule
	virtual void ClientCut(ContextKey *pKey);

	//virtual from ZNetServerModule
	virtual HRESULT TimerFunc(void *lpParam);

	inline void KickUser(ContextKey *pKey);

	inline int GetRoomMinUsers();

	inline int GetRoomMaxUsers();

	inline void UserReady(ContextKey *pKey,DWORD UserID);
private:
	virtual ZGameRoom *CreateGameRoom() = 0;

	//On Msg Connect
	HRESULT OnMsgConnect(ContextKey *pKey,GS_Room_Connect &Msg);
	//On Msg ComeIn
	HRESULT OnMsgComeIn(ContextKey *pKey,GS_Room_ComeIn &Msg);
	//On Msg Left
	HRESULT OnMsgLeft(ContextKey *pKey,GS_Room_Left &Msg);
	//On Msg Watcher ComeIn
	HRESULT OnMsgWatcherComeIn(ContextKey *pKey,GS_Room_WatcherComeIn &Msg);
};

inline GS_RoomService::GS_RoomService(DWORD wndMsg) : ZNetServerModule(wndMsg)
{
	m_pUserDataManage = NULL;
	m_pGameRoom = NULL;
	m_pHallService = NULL;
	m_pServerInfo = NULL;
	m_RoomTime = 0;
}

//KickUser
inline void GS_RoomService::KickUser(ContextKey *pKey) 
{ 
	ZASSERT(pKey);

	ShutDown(pKey);
}

inline int GS_RoomService::GetRoomMinUsers()
{
	ZASSERT(m_pServerInfo);

	return m_pServerInfo->Room.iMinUsers;
}

inline int GS_RoomService::GetRoomMaxUsers()
{
	ZASSERT(m_pServerInfo);

	return m_pServerInfo->Room.iMinUsers;
}

inline void GS_RoomService::UserReady(ContextKey *pKey,DWORD UserID)
{
	ZASSERT(m_pHallService);

	m_pHallService->UserReady(((GS_UserDataManage::_UserData *)(pKey->Data))->pKey,UserID);
}

///////////////////////////////////////////////////////////////////////////////////
//	ZGameRoom

// GameEnd State
const BYTE GAMEEND_STATE_NORMAL		=	0;
const BYTE GAMEEND_STATE_RUNAWAY	=	1;
const BYTE GAMEEND_STATE_SURRENDER	=	2;

// _UserData State
const DWORD	ZGAMEROOM_USERTIME_BEGIN	=	0x0001;
const DWORD	ZGAMEROOM_USERTIME_TIMEOUT	=	0x0002;

class FLYINGMAGIC_2_CORE_API ZGameRoom{
public:
	struct _UserData{
		void			*pData;
		ContextKey		*pKey;		

		_UserData(){
			pData = NULL;
			pKey = NULL;
		}
	};

	struct _UserTime{
		DWORD			dwBegin;
		ZState_DWord	dwState;

		_UserTime(){
			dwBegin = 0;
		}
	};
protected:
//User
	_UserData				m_User[GS_GAMEROOM_MAXUSERS];
	int						m_iMyWatchers[GS_GAMEROOM_MAXUSERS];
	ZCriticalSection		m_UserLock;
	int						m_iUsers;
	int						m_iReadyUsers;
//User Time
	_UserTime				m_UserTime[GS_GAMEROOM_MAXUSERS];
//Watcher
	_UserData				*m_Watchers;
	ZCriticalSection		m_WatcherLock;
	int						m_iWatcherNums;

	WORD					m_RoomID;		//My RoomID

	bool					m_bPlaying;		//Is Playing?

	GS_RoomService			*m_pService;
	GameServerInfo			*m_pServerInfo;
public:
	inline ZGameRoom();
	virtual ~ZGameRoom() { ; }
	//消息处理
	virtual HRESULT HandleMessage(ContextKey *pKey,void *buf,int len);

	void UpdateUserData(BYTE Station,long lScore,BYTE bState);
//User
	//用户进入房间
	void UserComeIn(BYTE Station,void *pData,ContextKey *pKey);
	//用户离开房间
	void UserLeft(BYTE Station);
	//用户逃跑
	void UserRunAway(BYTE Station);

//UserTime
	// 用户计时开始
	void UserTimeBegin(BYTE Station);
	// 用户是否开始计时
	inline bool UserIsBeginTimer(BYTE Station);
	// 用户是否已经超时
	inline bool UserIsTimeOut(BYTE Station);
	// 获得用户时间
	inline DWORD GetUserTime(BYTE Station);
	// 用户超时
	inline void UserTimeOut(BYTE Station);

//Game
	//游戏开始
	virtual void GameBegin();
	//旁观用户获得游戏状态信息
	virtual void SendGameData(ContextKey *pKey) = 0;
	//游戏结束
	virtual void GameEnd(BYTE State,BYTE Station);

//Watcher
	bool CanWatch(BYTE Station) const;

	void WatcherComeIn(BYTE Station,void *pData,ContextKey *pKey);

	void WatcherLeft(void *pData,ContextKey *pKey);

//Setting
	inline void SetRoomID(WORD RoomID);

	inline void SetRoomService(GS_RoomService *pRoomService);

	inline void SetServerInfo(GameServerInfo *pServerInfo);

//Get State
	inline bool IsPlaying() const { return m_bPlaying; }

	//Left Room
	HRESULT LeftRoom(ContextKey *pKey);
	//Timer Func
	virtual void TimerFunc() = 0;
	//超时函数，参数为超时用户座位号
	virtual void TimeOutFunc(BYTE Station);

protected:

	inline BYTE GetMyStation(ContextKey *pKey);

//Send & BroadCast
	//发送给pKey
	inline DWORD _SendMsg(ContextKey *pKey,void *msg,DWORD msg_len);
	//发送给Station位置上的用户，包括旁观者
	void SendMsg(BYTE Station,void *msg,DWORD msg_len);
	//广播
	void BroadCast(ContextKey *pKey,void *Msg,DWORD len);
	//广播
	void BroadCast(void *Msg,DWORD len);

private:

//On Msg
	//On Msg IAmReady
	HRESULT OnMsgIAmReady(ContextKey *pKey);
	//On Msg Chat
	HRESULT OnMsgChat(ContextKey *pKey,GS_Room_Chat &Msg);
	//On Msg Surrender
	HRESULT OnMsgSurrender(ContextKey *pKey);
	//On Msg UserTimeOut
	HRESULT OnMsgUserTimeOut(ContextKey *pKey,GS_Room_User_TimeOut &Msg);

//Send Msg
	//Send Msg ComeIn OK
	void SendMsgComeInOK(ContextKey *pKey,WORD RoomID,BYTE RoomStation);
	//Send Msg ComeIn Fail
	void SendMsgComeInFail(ContextKey *pKey);
	//Send Msg Watcher ComeIn OK
	void SendMsgWatcherComeInOK(ContextKey *pKey,WORD RoomID,BYTE RoomStation);
	//Send Msg Watcher ComeIn OK
	void SendMsgWatcherComeInFail(ContextKey *pKey);
	//BroadCast User Surrender
	void BroadCast_UserSurrender(BYTE Station);
	//BroadCast User RunAway
	void BroadCast_UserRunAway(BYTE Station);
	// 发送超时错误消息，参数为，时间差
	void SendMsg_TimeOutError(ContextKey *pKey,BYTE Station,DWORD dwTime);
};

inline ZGameRoom::ZGameRoom()
{
	m_pService = NULL;
	m_pServerInfo = NULL;
	m_RoomID = 0;
	m_iUsers = 0;
	m_iReadyUsers = 0;
	m_Watchers = NULL;
	m_iWatcherNums = 0;
	m_bPlaying = false;

	for(int i = 0;i < GS_GAMEROOM_MAXUSERS;i++)
		m_iMyWatchers[i] = 0;
}

inline DWORD ZGameRoom::_SendMsg(ContextKey *pKey,void *msg,DWORD msg_len)
{
	ZASSERT(m_pService);

	return m_pService->SendMsg(pKey,msg,msg_len);
}

inline void ZGameRoom::SetRoomID(WORD RoomID)
{
	ZASSERT(RoomID);

	m_RoomID = RoomID;
}

inline void ZGameRoom::SetRoomService(GS_RoomService *pRoomService)
{
	ZASSERT(pRoomService);

	m_pService = pRoomService;
}

inline void ZGameRoom::SetServerInfo(GameServerInfo *pServerInfo)
{
	ZASSERT(pServerInfo);
	ZASSERT(m_Watchers == NULL);

	m_pServerInfo = pServerInfo;

	m_Watchers = new _UserData[m_pServerInfo->iMaxWatchers];
	ZASSERT(m_Watchers);
}

inline BYTE ZGameRoom::GetMyStation(ContextKey *pKey)
{
	ZASSERT(pKey);

	return ((GS_UserDataManage::_UserData *)(pKey->Data))->RoomStation;
}

// 用户是否开始计时
inline bool ZGameRoom::UserIsBeginTimer(BYTE Station)
{
	ZASSERT(Station > 0 && Station <= GS_GAMEROOM_MAXUSERS);

	return m_UserTime[Station - 1].dwState.Has(ZGAMEROOM_USERTIME_BEGIN);
}

// 用户是否已经超时
inline bool ZGameRoom::UserIsTimeOut(BYTE Station)
{
	ZASSERT(Station > 0 && Station <= GS_GAMEROOM_MAXUSERS);

	return m_UserTime[Station - 1].dwState.Has(ZGAMEROOM_USERTIME_TIMEOUT);
}

// 获得用户时间
inline DWORD ZGameRoom::GetUserTime(BYTE Station)
{
	ZASSERT(Station > 0 && Station <= GS_GAMEROOM_MAXUSERS);

	return m_UserTime[Station - 1].dwBegin;
}

// 用户超时
inline void ZGameRoom::UserTimeOut(BYTE Station)
{
	ZASSERT(Station > 0 && Station <= GS_GAMEROOM_MAXUSERS);

	m_UserTime[Station - 1].dwState += ZGAMEROOM_USERTIME_TIMEOUT;
}

///////////////////////////////////////////////////////////////////////////////////
//	Game_Server

const DWORD GS_WNDMSG_LOGINFAIL		=	0x01;
const DWORD	GS_WNDMSG_LOGINOK		=	0x02;

class FLYINGMAGIC_2_CORE_API Game_Server{
protected:
	GCS_GSService_Client	m_Client;
	GS_HallService			m_HallService;
	GS_RoomService			*m_pRoomService;
	GS_UserDataManage		*m_pUserDataManage;

	GameServerInfo			m_ServerInfo;

	DWORD					m_wndMsg;
	ZThreadSystem			*m_pThreadSystem;
public:
	inline Game_Server(WORD GCS_ServerID,WORD HallID,DWORD wndMsg);
	~Game_Server();

	HRESULT Init(WORD Port,const char *Name,int iMaxUsers,int iMaxRooms);

	void Release();

	inline void SetThreadSystem(ZThreadSystem *pThreadSystem);

	inline void SetHWND(HWND hWnd);

	inline void InitUserDataManage();

	inline void SetServerInfo(int iMaxUsers,int iMaxRooms);

	inline void GetUser_Hall(GS_UserDataManage::_UserData* &user,void* &index);

	inline void GetSocket_Hall(ContextKey* &key,void* &index);
protected:
	virtual GS_UserDataManage *CreateUserDataManage() { return new GS_SimpleScore_UDM; }
	virtual GS_RoomService *CreateRoomService(DWORD wndMsg) = 0;
};

inline Game_Server::Game_Server(WORD GCS_ServerID,WORD HallID,DWORD wndMsg)
	: m_Client(GCS_ServerID,wndMsg)
	, m_HallService(HallID,wndMsg)
{ 
	m_pUserDataManage = NULL;
	m_pRoomService = NULL;
	m_pThreadSystem = NULL;

	m_wndMsg = wndMsg;
}

inline void Game_Server::SetThreadSystem(ZThreadSystem *pThreadSystem)
{
	ZASSERT(pThreadSystem);

	m_Client.SetThreadSystem(pThreadSystem);
	m_HallService.SetThreadSystem(pThreadSystem);

	m_pThreadSystem = pThreadSystem;
}

inline void Game_Server::SetHWND(HWND hWnd)
{
	m_Client.SetHWND(hWnd);
	m_HallService.SetHWND(hWnd);
}

inline void Game_Server::InitUserDataManage()
{
	ZASSERT(m_pUserDataManage);

	m_pUserDataManage->Init();
}

inline void Game_Server::SetServerInfo(int iMaxUsers,int iMaxRooms)
{
	ZASSERT(iMaxUsers > 0 && iMaxRooms > 0);

	m_ServerInfo.iMaxUsers = iMaxUsers;
	m_ServerInfo.iMaxRooms = iMaxRooms;
}

inline void Game_Server::GetUser_Hall(GS_UserDataManage::_UserData* &user,void* &index)
{
	m_HallService.GetUser(user,index);
}

inline void Game_Server::GetSocket_Hall(ContextKey* &key,void* &index)
{
	m_HallService.GetKey(key,index);
}

#endif