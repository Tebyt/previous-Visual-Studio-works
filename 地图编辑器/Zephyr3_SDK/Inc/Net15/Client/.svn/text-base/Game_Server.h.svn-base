#ifndef ZEPHYR_GAME_SERVER_CLIENT_H
#define ZEPHYR_GAME_SERVER_CLIENT_H

#include <ZState.h>
#include <ZList.h>
#include <Net15\TCP_Client.h>
#include <Net15\Client\CenterServer.h>
#include <Net15\Client\Game_CenterServer_User.h>
#include <Net15\Msg\Game_CenterServer.h>
#include <Net15\Msg\Game_Server.h>

/////////////////////////////////////////////////////////////////////////////////////
//	GS_Client_UserDataManage 

//UserData State
const	BYTE	GS_USERDATA_IAMREADY			=	0x80;	//Ready?
const	BYTE	GS_USERDATA_WATCH				=	0x40;	//Watch?
const	BYTE	GS_USERDATA_PLAYING				=	0x20;	//Playing?
const	BYTE	GS_USERDATA_NEEDPSW				=	0x10;	//Game PSW
const	BYTE	GS_USERDATA_ESTOPIP				=	0x08;	//是否不和相同IP的用户游戏
const	BYTE	GS_USERDATA_ALLOWWATCH			=	0x04;	//是否允许其他用户旁观

class FLYINGMAGIC_2_CORE_API GS_Client_UserDataManage{
public:
	struct _UserData{
		_BaseUserData	Base;
		WORD			RoomID;
		BYTE			RoomStation;
		ZState_Byte		bState;
	};
public:
	virtual ~GS_Client_UserDataManage() { ; }

	virtual HRESULT UpdateMyData(_BaseUserData *Base,void *Msg) = 0;

	virtual void *AddUser(void *Msg) = 0;

	virtual void DelUser(DWORD dwID) = 0;

	virtual void GetData(_BaseUserData* &Base,void* &Data,void* &index) = 0;

	virtual _BaseUserData *GetMyBaseData() = 0;

	virtual void *FindUser(DWORD dwID) = 0;

	virtual void *FindUser(const char *strID) = 0;

	virtual const char *GetName(DWORD dwID) = 0;

	virtual void *GetMyData() = 0;
private:
};

///////////////////////////////////////////////////////////////////////////////////
//	GS_Client_SimpleScore_UDM

class FLYINGMAGIC_2_CORE_API GS_Client_SimpleScore_UDM : public GS_Client_UserDataManage{
public:
	struct _UserData{
		_BaseUserData	Base;
		WORD			RoomID;
		BYTE			RoomStation;
		ZState_Byte		bState;

		long			lScore;
		long			lWin,lLose,lTotal,lRunAway;
		long			lMinScore,lMaxScore,lMaxRunAway;
	};
private:
	ZLinkEx<_UserData,512,128>	m_UserDataLink;
	ZCriticalSection			m_UserDataLock;

	_UserData					m_MyData;
public:
	//virtual from GS_Client_UserDataManage
	virtual HRESULT UpdateMyData(_BaseUserData *Base,void *Msg);
	//virtual from GS_Client_UserDataManage
	virtual void *AddUser(void *Msg);
	//virtual from GS_Client_UserDataManage
	virtual void DelUser(DWORD dwID);
	//virtual from GS_Client_UserDataManage
	virtual void GetData(_BaseUserData* &Base,void* &Data,void* &index);
	//virtual from GS_Client_UserDataManage
	virtual _BaseUserData *GetMyBaseData();
	//virtual from GS_Client_UserDataManage
	virtual void *FindUser(const char *strID);
	//virtual from GS_Client_UserDataManage
	virtual const char *GetName(DWORD dwID);
	//virtual from GS_Client_UserDataManage
	virtual void *FindUser(DWORD dwID);
	//virtual from GS_Client_UserDataManage
	virtual void *GetMyData();
private:
};

///////////////////////////////////////////////////////////////////////////////////
//	GS_HallService_Client

class GS_RoomService_Client;

//wmd msg
const DWORD	WM_GS_HALL_COMEINOK			=	0x0100;
const DWORD	WM_GS_HALL_UPDATEUSERLIST	=	0x0101;
const DWORD	WM_GS_HALL_CHATDATA			=	0x0102;
const DWORD WM_GS_HALL_SERVERCUT		=	0x0103;

class FLYINGMAGIC_2_CORE_API GS_HallService_Client : public ZNetClientModule{
public:
	struct _RoomData;
private:
	WORD						m_ServerID;
	GS_Client_UserDataManage	*m_pUserDataManage;

	ZCriticalSection			m_ChatDataLock;
	ZStream<BYTE>				m_ChatStream;

	GameServerInfo				*m_pServerInfo;

	_RoomData					*m_pRoomData;
	GS_RoomService_Client		*m_pRoomClient;
public:
	inline GS_HallService_Client(DWORD wndMsg);
	virtual ~GS_HallService_Client();

	HRESULT Init(GS_Client_UserDataManage *pUserDataManage,WORD ServerID,DWORD IP,WORD Port);

	//virtual from ZNetClientModule
	virtual HRESULT HandleMessage(void *buf,int len);
	//virtual from ZNetClientModule
	//服务器断开连接
	virtual void ServerCut();

	void ComeIn();

	inline void ComeInRoom(WORD RoomID,BYTE RoomStation,bool bWatch);

	inline void LeftRoom();

	inline void SetServerInfo(GameServerInfo *pServerInfo);

	inline void SetRoomClient(GS_RoomService_Client *pRoomClient);

	inline void GetUserData(_BaseUserData* &Base,void* &user,void* &index);

	GS_Hall_Chat *GetChatData();

	inline const char *GetUserName(DWORD dwID);

	void SendChat(DWORD dwTo,BYTE bState,BYTE bFace,DWORD dwColor,const char *Data);

	inline GS_HallService_Client::_RoomData *GetRoomData(int index);

	void LeftRoom(WORD RoomID,void *user);

	void ComeInRoom(WORD RoomID,void *user);

	inline int GetMaxRooms();

	bool CanComeIn(WORD RoomID,BYTE RoomStation);

	inline GS_RoomService_Client *GetRoomClient() { return m_pRoomClient; }

	bool InRoom();

	bool IsGameBegin(WORD RoomID);
private:
	//On Msg MyGameData
	inline HRESULT OnMsgMyGameData_SC(GS_Hall_YourGameData_SC &Msg);
	//On Msg UserList
//	HRESULT OnMsgUserList_SC(GS_Hall_UserList_SC &Msg);
	//On Msg UserComeIn
	HRESULT OnMsgUserComeIn_SC(GS_Hall_UserComeIn_SC &Msg);
	//On Msg UserLeft
	HRESULT OnMsgUserLeft(GS_Hall_UserLeft &Msg);
	//On Msg ChatData
	HRESULT OnMsgChatData(GS_Hall_Chat &Msg);
	//On Msg ServerInfo
	HRESULT OnMsgServerInfo(GS_Hall_ServerInfo &Msg);
	//On Msg RoomUserIn
	HRESULT OnMsgRoomUserIn(GS_Hall_Room_UserIn &Msg);
	//On Msg RoomUserOut
	HRESULT OnMsgRoomUserOut(GS_Hall_Room_UserOut &Msg);
	//On Msg UserReady
	HRESULT OnMsgUserReady(GS_Hall_UserReady &Msg);
	//On Msg UserComeOK
	HRESULT OnMsgUserComeOK();
	//On Msg UpdateUserScore
	HRESULT OnMsgUpdateUserScore(GS_Hall_GameData_SC &Msg);
	//On Msg Room GameEnd
	HRESULT OnMsgRoomGameEnd(GS_Hall_Room_GameEnd &Msg);


	BYTE FindUser(WORD RoomID,void *user);
};

const BYTE	GS_HS_CLIENT_ROOMDATA_STATE_PLAYING	=	0x01;

struct GS_HallService_Client::_RoomData{
	void					*pUser[GS_GAMEROOM_MAXUSERS];
	int						iUsers;
	ZLinkEx<void *,8,4>		UserLink;
	ZCriticalSection		Lock;
	ZState_Byte				m_bState;

	_RoomData(){
		memset(pUser,0,sizeof(void *)*GS_GAMEROOM_MAXUSERS);
		iUsers = 0;
	}

	void *GetUser(void** &user,void* &index){
		if(index == NULL)
			Lock.Lock();

		UserLink.GetData(user,index);

		if(index == NULL)
			Lock.Unlock();

		if(user)
			return *user;

		return NULL;
	}

	void GameBegin(){
		m_bState += GS_HS_CLIENT_ROOMDATA_STATE_PLAYING;
	}

	void GameEnd(){
		m_bState -= GS_HS_CLIENT_ROOMDATA_STATE_PLAYING;

		for(int i = 0; i < GS_GAMEROOM_MAXUSERS; i++)
		{
			if(pUser[i] != NULL && ((GS_Client_UserDataManage::_UserData *)pUser[i])->bState.Has(GS_USERDATA_IAMREADY))
				((GS_Client_UserDataManage::_UserData *)pUser[i])->bState -= GS_USERDATA_IAMREADY;
		}
	}

	bool IsPlaying(){
		return m_bState.Has(GS_HS_CLIENT_ROOMDATA_STATE_PLAYING);
	}

	bool UserReady(void *user,int iMinUser){
		((GS_Client_UserDataManage::_UserData *)user)->bState += GS_USERDATA_IAMREADY;

		int iReady = 0;
		for(int i = 0; i < GS_GAMEROOM_MAXUSERS; i++)
		{
			if(pUser[i] != NULL && ((GS_Client_UserDataManage::_UserData *)pUser[i])->bState.Has(GS_USERDATA_IAMREADY))
				iReady++;
		}

		if(iReady >= iMinUser)
		{
			GameBegin();

			return true;
		}

		return false;
	}
};

///////////////////////////////////////////////////////////////////////////////////
//	GS_RoomService_Client

const BYTE	GAMEEND_STATE_NORMAL		=	0;
const BYTE	GAMEEND_STATE_RUNAWAY		=	1;
const BYTE	GAMEEND_STATE_SURRENDER		=	2;

//wmd msg
const DWORD	WM_GS_ROOM_COMEINOK				=	0x0200;
const DWORD	WM_GS_ROOM_COMEINFAIL			=	0x0201;
const DWORD WM_GS_ROOM_SERVERCUT			=	0x0202;
const DWORD	WM_GS_ROOM_WATCHERCOMEINOK		=	0x0205;
const DWORD	WM_GS_ROOM_WATCHERCOMEINFAIL	=	0x0206;
const DWORD WM_GS_ROOM_CHATDATA				=	0x0207;
const DWORD WM_GS_ROOM_UPDATEUSERLIST		=	0x0208;
const DWORD WM_GS_ROOM_USERRUNAWAY			=	0x0209;
const DWORD WM_GS_ROOM_USERSURRENDER		=	0x020a;

class FLYINGMAGIC_2_CORE_API GS_RoomService_Client : public ZNetClientModule{
protected:
	GS_Client_UserDataManage			*m_pUserDataManage;

	GS_HallService_Client::_RoomData	*m_pRoomData;

	GameServerInfo						*m_pServerInfo;

	ZCriticalSection					m_ChatDataLock;
	ZStream<BYTE>						m_ChatStream;

	BYTE								m_MyStation;

	WORD								m_RoomID;
public:
	inline GS_RoomService_Client(DWORD wndMsg);
	virtual ~GS_RoomService_Client() { DEBUGMESSAGE("GS_RoomService_Client Release!"); }

	//virtual from ZNetClientModule
	virtual HRESULT HandleMessage(void *buf,int len);
	//virtual from ZNetClientModule
	//服务器断开连接
	virtual void ServerCut();

	GS_Room_ChatData *GetChatData();

	void Connect();

	void ComeIn(WORD RoomID,BYTE RoomStation,GS_HallService_Client::_RoomData *pRoomData);

	void Watch(WORD RoomID,BYTE RoomStation,GS_HallService_Client::_RoomData *pRoomData);

	inline bool IsWatcher();

	void SendChat(DWORD dwTo,BYTE bState,BYTE bFace,DWORD dwColor,const char *Data);

	inline void GetUserData(_BaseUserData* &Base,void* &user,void* &index);

	BYTE GetMyStation() { return m_MyStation; }

	inline const char *GetUserName(DWORD dwID);

	void Left();

	void IAmReady();

	void Surrender();

	void RunAway() { Left(); }

	inline void SetUserDataManage(GS_Client_UserDataManage *pUserDataManage);

	inline void SetServerInfo(GameServerInfo *pServerInfo);

	virtual void GameEnd(BYTE State,BYTE Station);

	virtual void TimeOutError(BYTE Station,DWORD dwTime) { ; }

	inline WORD GetRoomID();

	GS_HallService_Client::_RoomData *GetRoomData() { return m_pRoomData; }

	inline BYTE StationToLocal(BYTE Station);

	void SetMyStation(BYTE Station) { m_MyStation = Station; }

	bool InRoom() { return m_pRoomData != NULL; }

	//用户超时，参数为 超时用户 和 超时时间
	void UserTimeOut(BYTE Station,DWORD dwTime);

	int SendMsg(void *msg,int size,bool bWatcherCanSend = false);

	int _SendMsg(void *msg,int size) { return ZNetClientModule::SendMsg(msg,size); }
private:
	//On Msg ComeInOK
	inline HRESULT OnMsgComeInOK(GS_Room_ComeInOK &Msg);
	//On Msg ComeInFail
	inline HRESULT OnMsgComeInFail();
	//On Msg Watcher ComeInOK
	inline HRESULT OnMsgWatcherComeInOK(GS_Room_WatcherComeInOK &Msg);
	//On Msg Watcher ComeInFail
	inline HRESULT OnMsgWatcherComeInFail();
	//On Msg ChatData
	HRESULT OnMsgChatData(GS_Room_ChatData &Msg);
	// On Msg User Run Away
	HRESULT OnMsgUserRunAway(GS_Room_UserRunAway &Msg);
	// On Msg User Surrender
	HRESULT OnMsgUserSurrender(GS_Room_UserSurrender &Msg);
	// On Msg TimeOutError
	HRESULT OnMsgTimeOut_Error(GS_Room_User_TimeOutError &Msg);
};

inline GS_RoomService_Client::GS_RoomService_Client(DWORD wndMsg) : ZNetClientModule(wndMsg)
{
	m_pUserDataManage = NULL;

	m_pRoomData = NULL;

	m_pServerInfo = NULL;

	m_RoomID = 0;
	m_MyStation = 0;
}

inline void GS_RoomService_Client::SetUserDataManage(GS_Client_UserDataManage *pUserDataManage)
{
	ZASSERT(pUserDataManage);

	m_pUserDataManage = pUserDataManage;
}

//On Msg ComeInOK
inline HRESULT GS_RoomService_Client::OnMsgComeInOK(GS_Room_ComeInOK &Msg)
{
	m_MyStation = ((GS_Client_UserDataManage::_UserData *)m_pUserDataManage->GetMyData())->RoomStation = Msg.GetData()->RoomStation;
	((GS_Client_UserDataManage::_UserData *)m_pUserDataManage->GetMyData())->RoomID = Msg.GetData()->RoomID;

	PostMsg(WM_GS_ROOM_COMEINOK,0);

	return S_OK;
}

//On Msg ComeInFail
inline HRESULT GS_RoomService_Client::OnMsgComeInFail()
{
	PostMsg(WM_GS_ROOM_COMEINFAIL,0);

	m_MyStation = 0;

	m_pRoomData = NULL;

	return S_OK;
}

//On Msg Watcher ComeInOK
inline HRESULT GS_RoomService_Client::OnMsgWatcherComeInOK(GS_Room_WatcherComeInOK &Msg)
{
	m_MyStation = ((GS_Client_UserDataManage::_UserData *)m_pUserDataManage->GetMyData())->RoomStation = Msg.GetData()->RoomStation;
	((GS_Client_UserDataManage::_UserData *)m_pUserDataManage->GetMyData())->RoomID = Msg.GetData()->RoomID;
	((GS_Client_UserDataManage::_UserData *)m_pUserDataManage->GetMyData())->bState += GS_USERDATA_WATCH;

	PostMsg(WM_GS_ROOM_WATCHERCOMEINOK,0);

	return S_OK;
}

//On Msg Watcher ComeInFail
inline HRESULT GS_RoomService_Client::OnMsgWatcherComeInFail()
{
	PostMsg(WM_GS_ROOM_WATCHERCOMEINFAIL,0);

	m_MyStation = 0;

	return S_OK;
}

inline void GS_RoomService_Client::SetServerInfo(GameServerInfo *pServerInfo)
{
	ZASSERT(pServerInfo);

	m_pServerInfo = pServerInfo;
}

inline BYTE GS_RoomService_Client::StationToLocal(BYTE Station)
{
	return Station == m_MyStation ? 1 : (Station<=m_MyStation-1 ? Station+m_pServerInfo->Room.iMaxUsers-m_MyStation+1 : Station-m_MyStation+1);
}

inline bool GS_RoomService_Client::IsWatcher()
{
	ZASSERT(m_pUserDataManage);

	return ((GS_Client_UserDataManage::_UserData *)m_pUserDataManage->GetMyData())->bState.Has(GS_USERDATA_WATCH);
}

inline const char *GS_RoomService_Client::GetUserName(DWORD dwID)
{
	ZASSERT(m_pUserDataManage);

	return m_pUserDataManage->GetName(dwID);
}

inline void GS_RoomService_Client::GetUserData(_BaseUserData* &Base,void* &user,void* &index)
{
	ZASSERT(m_pRoomData);

	void **tmp = NULL;

	user = Base = (_BaseUserData *)m_pRoomData->GetUser(tmp,index);
}

inline WORD GS_RoomService_Client::GetRoomID()
{
	return m_RoomID;
}

///////////////////////////////////////////////////////////////////////////////////
//	Game_Server_Client

class FLYINGMAGIC_2_CORE_API Game_Server_Client{
protected:
	GS_Client_UserDataManage		*m_pUserDataManage;
	GS_HallService_Client			m_HallClient;
	GS_RoomService_Client			*m_pRoomClient;

	GameServerInfo					m_ServerInfo;

	DWORD							m_RoomWndMsg;
	HWND							m_RoomWnd;
	ZThreadSystem					*m_pThreadSystem;
public:
	inline Game_Server_Client(DWORD HallWndMsg,DWORD RoomWndMsg);
	~Game_Server_Client();

	HRESULT Init();

	void Release();

	inline HRESULT ComeIn(WORD ServerID,DWORD IP,WORD Port);

	inline void SetHWND(HWND HallClientWnd,HWND RoomClientWnd);

	inline void SetRoomWnd(HWND RoomClientWnd);

	inline void SetThreadSystem(ZThreadSystem *pThreadSystem);

	inline GS_HallService_Client *GetHallClient() { return &m_HallClient; }

	inline GS_RoomService_Client *GetRoomClient() { return m_pRoomClient; }

	inline void SetMyBaseData(_BaseUserData &user);

	inline void *GetMyData();

	inline BYTE GetMyStation();

	inline WORD GetRoomID();

	inline void GetData(_BaseUserData* &Base,void* &Data,void* &index);

	inline void SendHallChat(DWORD dwTo,BYTE bState,BYTE bFace,DWORD dwColor,const char *Data);

	inline GS_Hall_Chat *GetHallChatData();

	inline void *FindUser(DWORD UserID);

	GS_HallService_Client::_RoomData *GetRoomData(int index) { return m_HallClient.GetRoomData(index); }

	int GetMaxRooms() { return m_ServerInfo.iMaxRooms; }

	void ComeInRoom(WORD RoomID,BYTE RoomStation,bool bWatch) { m_HallClient.ComeInRoom(RoomID,RoomStation,bWatch); }

	bool CanComeIn(WORD RoomID,BYTE RoomStation) { return m_HallClient.CanComeIn(RoomID,RoomStation); }

	bool IsGameBegin(WORD RoomID) { return m_HallClient.IsGameBegin(RoomID); }

	inline void LeftRoom();

	inline void GetRoomUser(_BaseUserData* &Base,void* &Data,void* &index);

	inline GS_Room_ChatData *GetRoomChatData();

	inline void SendRoomChat(DWORD dwTo,BYTE bState,BYTE bFace,DWORD dwColor,const char *Data);

	inline bool IsWatcher();

	inline void IAmReady();

	inline GS_HallService_Client::_RoomData *GetRoomData();

	inline void RunAway();

	GameServerInfo *GetGameServerInfo() { return &m_ServerInfo; }

	inline BYTE StationToLocal(BYTE Station);

	inline bool InRoom_Room();

	inline bool InRoom_Hall();
private:	
	virtual GS_Client_UserDataManage *CreateUserDataManage() { return new GS_Client_SimpleScore_UDM; }

	virtual GS_RoomService_Client *CreateRoomClient(DWORD wndMsg) { return new GS_RoomService_Client(wndMsg); }
};

inline Game_Server_Client::Game_Server_Client(DWORD HallWndMsg,DWORD RoomWndMsg)
		: m_HallClient(HallWndMsg)
{
	m_pUserDataManage = NULL;
	m_pRoomClient = NULL;

	m_RoomWndMsg = RoomWndMsg;
}

inline void Game_Server_Client::SetHWND(HWND HallClientWnd,HWND RoomClientWnd)
{
	m_HallClient.SetHWND(HallClientWnd);

	m_RoomWnd = RoomClientWnd;
}

inline void Game_Server_Client::SetRoomWnd(HWND RoomClientWnd)
{
	ZASSERT(m_pRoomClient != NULL);

	m_pRoomClient->SetHWND(RoomClientWnd);
}

inline void Game_Server_Client::SetThreadSystem(ZThreadSystem *pThreadSystem)
{
	m_HallClient.SetThreadSystem(pThreadSystem);

	m_pThreadSystem = pThreadSystem;
}

inline HRESULT Game_Server_Client::ComeIn(WORD ServerID,DWORD IP,WORD Port)
{
	return m_HallClient.Init(m_pUserDataManage,ServerID,IP,Port);
}

inline void Game_Server_Client::SetMyBaseData(_BaseUserData &user)
{
	ZASSERT(m_pUserDataManage);

	_BaseUserData *tmp = m_pUserDataManage->GetMyBaseData();

	memcpy(tmp,&user,sizeof(_BaseUserData));
}

inline void Game_Server_Client::GetData(_BaseUserData* &Base,void* &Data,void* &index)
{
	ZASSERT(m_pUserDataManage);

	m_pUserDataManage->GetData(Base,Data,index);
}

inline void *Game_Server_Client::GetMyData()
{
	ZASSERT(m_pUserDataManage);

	return m_pUserDataManage->GetMyData();
}

inline void Game_Server_Client::SendHallChat(DWORD dwTo,BYTE bState,BYTE bFace,DWORD dwColor,const char *Data)
{
	m_HallClient.SendChat(dwTo,bState,bFace,dwColor,Data);
}

inline GS_Hall_Chat *Game_Server_Client::GetHallChatData()
{
	return m_HallClient.GetChatData();
}

inline void *Game_Server_Client::FindUser(DWORD UserID)
{
	ZASSERT(m_pUserDataManage);

	return m_pUserDataManage->FindUser(UserID);
}

inline void Game_Server_Client::LeftRoom() 
{ 
	ZASSERT(m_pRoomClient);

	m_pRoomClient->Left(); 
}

inline void Game_Server_Client::GetRoomUser(_BaseUserData* &Base,void* &Data,void* &index)
{
	ZASSERT(m_pRoomClient);

	m_pRoomClient->GetUserData(Base,Data,index);
}

inline GS_Room_ChatData *Game_Server_Client::GetRoomChatData()
{
	ZASSERT(m_pRoomClient);

	return m_pRoomClient->GetChatData();
}

inline void Game_Server_Client::SendRoomChat(DWORD dwTo,BYTE bState,BYTE bFace,DWORD dwColor,const char *Data)
{
	ZASSERT(m_pRoomClient);

	m_pRoomClient->SendChat(dwTo,bState,bFace,dwColor,Data);
}

inline bool Game_Server_Client::IsWatcher()
{
	ZASSERT(m_pRoomClient);

	return m_pRoomClient->IsWatcher();
}

inline void Game_Server_Client::IAmReady()
{
	ZASSERT(m_pRoomClient);

	m_pRoomClient->IAmReady();
}

inline GS_HallService_Client::_RoomData *Game_Server_Client::GetRoomData()
{
	ZASSERT(m_pRoomClient);

	return m_pRoomClient->GetRoomData();
}

inline void Game_Server_Client::RunAway()
{
	ZASSERT(m_pRoomClient);

	m_pRoomClient->RunAway();
}

inline BYTE Game_Server_Client::StationToLocal(BYTE Station)
{
	ZASSERT(m_pRoomClient != NULL);

	return m_pRoomClient->StationToLocal(Station);
}

inline BYTE Game_Server_Client::GetMyStation()
{
	ZASSERT(m_pRoomClient != NULL);

	return m_pRoomClient->GetMyStation();
}

inline WORD Game_Server_Client::GetRoomID()
{
	ZASSERT(m_pRoomClient != NULL);

	return m_pRoomClient->GetRoomID();
}

inline bool Game_Server_Client::InRoom_Hall()
{
	return m_HallClient.InRoom();
}

inline bool Game_Server_Client::InRoom_Room()
{
	ZASSERT(m_pRoomClient != NULL);

	return m_pRoomClient->InRoom();
}

///////////////////////////////////////////////////////////////////////////////////
//	GS_HallService_Client

inline GS_HallService_Client::GS_HallService_Client(DWORD wndMsg) : ZNetClientModule(wndMsg)
{
	m_ServerID = 0;
	m_pUserDataManage = NULL;
	m_pRoomData = NULL;
}

inline HRESULT GS_HallService_Client::OnMsgMyGameData_SC(GS_Hall_YourGameData_SC &Msg)
{
	ZASSERT(m_pUserDataManage);

	m_pUserDataManage->UpdateMyData(NULL,Msg.GetData());

//	PostMsg(WM_GS_HALL_COMEINOK,0);

	m_pRoomClient->Connect();

	return S_OK;
}

inline void GS_HallService_Client::GetUserData(_BaseUserData* &Base,void* &user,void* &index)
{
	ZASSERT(m_pUserDataManage);

	m_pUserDataManage->GetData(Base,user,index);
}

inline const char *GS_HallService_Client::GetUserName(DWORD dwID)
{
	ZASSERT(m_pUserDataManage);

	return m_pUserDataManage->GetName(dwID);
}

inline void GS_HallService_Client::SetServerInfo(GameServerInfo *pServerInfo)
{
	ZASSERT(pServerInfo);

	m_pServerInfo = pServerInfo;
}

inline GS_HallService_Client::_RoomData *GS_HallService_Client::GetRoomData(int index)
{
	ZASSERT(m_pServerInfo);
	ZASSERT(index >= 0 && index < m_pServerInfo->iMaxRooms);

	return &(m_pRoomData[index]);
}

inline int GS_HallService_Client::GetMaxRooms()
{
	ZASSERT(m_pServerInfo);

	return m_pServerInfo->iMaxRooms;
}

inline void GS_HallService_Client::SetRoomClient(GS_RoomService_Client *pRoomClient)
{
	ZASSERT(pRoomClient);

	m_pRoomClient = pRoomClient;
}

inline void GS_HallService_Client::ComeInRoom(WORD RoomID,BYTE RoomStation,bool bWatch)
{
	ZASSERT(m_pRoomClient);
	ZASSERT(RoomID);

	if(bWatch)
		m_pRoomClient->Watch(RoomID,RoomStation,GetRoomData(RoomID-1));
	else
		m_pRoomClient->ComeIn(RoomID,RoomStation,GetRoomData(RoomID-1));
}

inline void GS_HallService_Client::LeftRoom()
{
	ZASSERT(m_pRoomClient);

	m_pRoomClient->Left();
}

#endif