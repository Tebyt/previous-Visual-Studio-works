#ifndef ZEPHYR_GAME_SERVER_MSG_H
#define ZEPHYR_GAME_SERVER_MSG_H

#include <ZTime.h>
#include <Net\NetMsg.h>
#include <Net\Msg\LoginServer.h>
#include <FlyingMagic\BaseDef.h>

const int	GS_GAMEROOM_MAXUSERS	=	8;
const int	GS_GAMEROOM_WATCHERS	=	32;

const int	GS_INFO_FORCE			=	2;

const DWORD	GS_INFO_STATE_FORCEEQU	=	0x01;	//势力均衡

struct GameServerInfo{
	struct _RoomInfo{
		int		iMaxUsers;
		int		iMinUsers;
	};

	int				iMaxUsers;
	int				iMaxRooms;
	int				iMaxWatchers;
	int				iMaxForce;
	_RoomInfo		Room;
	ZState_DWord	dwState;

	GameServerInfo() {
		iMaxForce = GS_INFO_FORCE;
		iMaxUsers = iMaxRooms = 0;
		iMaxWatchers = GS_GAMEROOM_WATCHERS;
		Room.iMaxUsers = Room.iMinUsers = 0;
	}
};

const int	GAME_SERVER_CHATDATA_LEN	=	256;

///////////////////////////////////////////////////////////////////////////////////
// Msg

//消息版本号
#define GAME_SERVER_MSG_VER			0x01

//---------------------------------------------------------------------------------
//辅助消息ID

///////////////////////////////////////////////////////////////////////////////////
// HallService

//由 客户端 发来的消息
//User Come In
const BYTE	GS_HALL_MSG_COMEIN			=	0x01;
//User Chat
const BYTE	GS_HALL_MSG_CHAT			=	0x02;


//由 服务器 发出的消息
//User GameData
const BYTE	GS_HALL_MSG_YOUGAMEDATA_SC	=	0x10;
//User List
const BYTE	GS_HALL_MSG_USERLIST_SC		=	0x11;
//User ComeIn
const BYTE	GS_HALL_MSG_USERCOMEIN_SC	=	0x12;
//User Left
const BYTE	GS_HALL_MSG_USERLEFT		=	0x13;
//User ChatData
const BYTE	GS_HALL_MSG_CHATDATA		=	0x15;
//ServerInfo
const BYTE	GS_HALL_MSG_SERVERINFO		=	0x16;
//User In Room
const BYTE	GS_HALL_MSG_ROOM_USERIN		=	0x17;
//User Out Room
const BYTE	GS_HALL_MSG_ROOM_USEROUT	=	0x18;
//User Ready
const BYTE	GS_HALL_MSG_USERREADY		=	0x19;
//User ComeOK
const BYTE	GS_HALL_MSG_USERCOMEOK		=	0x1a;
//Update User Score
const BYTE	GS_HALL_MSG_UPDATEUSERSCORE	=	0x1b;
//Game End
const BYTE	GS_HALL_MSG_ROOM_GAMEEND	=	0x1c;

///////////////////////////////////////////////////////////////////////////////////
//	Msg Data

#pragma pack (push)
#pragma pack (1)

//GS_HALL_MSG_COMEIN
struct _GS_Hall_ComeIn{
	DWORD		dwID;
	char		strID[__LS_ID_LEN];

	void Fix(){
		strID[__LS_ID_LEN-1] = '\0';
	}
};

typedef ZNetMsg<_GS_Hall_ComeIn>	GS_Hall_ComeIn;

//GS_HALL_MSG_YOUGAMEDATA_SC
struct _GS_Hall_YourGameData_SC{
	long			lScore;
	long			lWin,lLose,lTotal,lRunAway;
};

typedef ZNetMsg<_GS_Hall_YourGameData_SC>	GS_Hall_YourGameData_SC;

//GS_HALL_MSG_USERLIST_SC
struct _GS_Hall_UserList_SC{
	long		lScore;
	long		lWin,lLose,lTotal,lRunAway;
	WORD		RoomID;
	BYTE		RoomStation;
	BYTE		bState;
	DWORD		dwID;
	char		strID[__LS_ID_LEN];
	char		strName[USER_NAME_LEN];
	bool		bSex;
	BYTE		bLogo;

	void Fix(){
		strID[__LS_ID_LEN-1] = strName[USER_NAME_LEN-1] = '\0';
	}
};

typedef ZNetMsg_MulData<_GS_Hall_UserList_SC>	GS_Hall_UserList_SC;

//GS_HALL_MSG_UPDATEUSERSCORE

const BYTE	UPDATE_USER_SCORE_STATE_WIN		=	1;
const BYTE	UPDATE_USER_SCORE_STATE_LOSE	=	2;
const BYTE	UPDATE_USER_SCORE_STATE_DEUCE	=	3;
const BYTE	UPDATE_USER_SCORE_STATE_RUNAWAY	=	5;

struct _GS_Hall_GameData_SC{
	DWORD			UserID;
	long			lScore;
	BYTE			bState;
};

typedef ZNetMsg<_GS_Hall_GameData_SC>	GS_Hall_GameData_SC;

//GS_HALL_MSG_USERCOMEIN_SC
typedef ZNetMsg<_GS_Hall_UserList_SC>	GS_Hall_UserComeIn_SC;

//GS_HALL_MSG_USERLEFT
struct _GS_Hall_UserLeft{
	DWORD dwID;
};

typedef ZNetMsg<_GS_Hall_UserLeft>	GS_Hall_UserLeft;

//GS_HALL_MSG_CHAT
struct _GS_Hall_Chat{
	DWORD		IDFrom;		//说话人
	DWORD		IDTo;		//被说话人
	BYTE		bState;		//对话状态
	BYTE		bFace;		//表情
	DWORD		dwColor;	//颜色 
	char		Data[GAME_SERVER_CHATDATA_LEN];	//聊天内容

	void Fix(){
		Data[GAME_SERVER_CHATDATA_LEN-1] = '\0';
	}
};

typedef ZNetMsg<_GS_Hall_Chat>	GS_Hall_Chat;

//GS_HALL_MSG_SERVERINFO
struct _GS_Hall_ServerInfo{
	int	iMaxRooms;
};

typedef ZNetMsg<_GS_Hall_ServerInfo>	GS_Hall_ServerInfo;

//GS_HALL_MSG_ROOM_USERIN
struct _GS_Hall_Room_UserIn{
	DWORD	UserID;
	WORD	RoomID;
	BYTE	RoomStation;
	BYTE	State;
};

typedef ZNetMsg<_GS_Hall_Room_UserIn>	GS_Hall_Room_UserIn;

//GS_HALL_MSG_ROOM_USEROUT
struct _GS_Hall_Room_UserOut{
	DWORD	UserID;
};

typedef ZNetMsg<_GS_Hall_Room_UserOut>	GS_Hall_Room_UserOut;

//GS_HALL_MSG_USERREADY
struct _GS_Hall_UserReady{
	DWORD	UserID;
};

typedef ZNetMsg<_GS_Hall_UserReady>	GS_Hall_UserReady;

//GS_HALL_MSG_ROOM_GAMEEND
struct _GS_Hall_Room_GameEnd{
	WORD	RoomID;
};

typedef ZNetMsg<_GS_Hall_Room_GameEnd>	GS_Hall_Room_GameEnd;

//GS_HALL_MSG_USERCOMEOK
typedef ZNetMsg<null_type>	GS_Hall_UserComeOK;

#pragma pack (pop)

///////////////////////////////////////////////////////////////////////////////////
// RoomService

//由 客户端 发来的消息
//User Connect
const BYTE	GS_ROOM_MSG_CONNECT			=	0x50;
//User Come In
const BYTE	GS_ROOM_MSG_COMEIN			=	0x51;
//User Chat
const BYTE	GS_ROOM_MSG_CHAT			=	0x52;
//User Left
const BYTE	GS_ROOM_MSG_LEFT			=	0x53;
//User Ready
const BYTE	GS_ROOM_MSG_IAMREADY		=	0x55;
//Watcher ComeIn
const BYTE	GS_ROOM_MSG_WATCHERCOMEIN	=	0x56;
//Surrender
const BYTE	GS_ROOM_MSG_SURRENDER		=	0x57;
//TimeOut
const BYTE	GS_ROOM_MSG_USER_TIMEOUT	=	0x58;

//由 服务器 发出的消息
//Chat Data
const BYTE	GS_ROOM_MSG_CHATDATA		=	0x60;
//ComeIn OK
const BYTE	GS_ROOM_MSG_COMEINOK		=	0x61;
//ComeIn Fail
const BYTE	GS_ROOM_MSG_COMEINFAIL		=	0x62;
//Watcher ComeIn OK
const BYTE	GS_ROOM_MSG_WATCHOK			=	0x63;
//Watcher ComeIn Fail
const BYTE	GS_ROOM_MSG_WATCHFAIL		=	0x64;
// User RunAway
const BYTE	GS_ROOM_MSG_USER_RUNAWAY	=	0x65;
// User Surrender
const BYTE	GS_ROOM_MSG_USER_SURRENDER	=	0x66;
// User TimeOut Error
const BYTE	GS_ROOM_MSG_TIMEOUT_ERROR	=	0x67;

///////////////////////////////////////////////////////////////////////////////////
//	Msg Data

#pragma pack (push)
#pragma pack (1)

template<class T>
struct GS_RoomMsg{
	WORD	RoomID;
	T		Data;
};

template<>
struct GS_RoomMsg<null_type>{
	WORD	RoomID;
};

typedef GS_RoomMsg<null_type>	_GS_RoomMsg_Base;
typedef ZNetMsg<_GS_RoomMsg_Base>	GS_RoomMsg_Base;

#pragma pack (pop)

#pragma pack (push)
#pragma pack (1)

//GS_ROOM_MSG_CONNECT
struct _GS_Room_Connect{
	DWORD	dwID;	//User ID
};

typedef ZNetMsg<_GS_Room_Connect>	GS_Room_Connect;

//GS_ROOM_MSG_COMEIN
struct _GS_Room_ComeIn{
	WORD	RoomID;
	BYTE	RoomStation;
};

typedef ZNetMsg<_GS_Room_ComeIn>	GS_Room_ComeIn;

//GS_ROOM_MSG_WATCHERCOMEIN
typedef ZNetMsg<_GS_Room_ComeIn>	GS_Room_WatcherComeIn;

//GS_ROOM_MSG_LEFT
typedef ZNetMsg<_GS_RoomMsg_Base>	GS_Room_Left;

//GS_ROOM_MSG_IAMREADY
typedef ZNetMsg<_GS_RoomMsg_Base>	GS_Room_IAmReady;

//GS_ROOM_MSG_SURRENDER
typedef ZNetMsg<_GS_RoomMsg_Base>	GS_Room_Surrender;

//GS_ROOM_MSG_USER_TIMEOUT
struct __GS_Room_User_TimeOut{
	DWORD	dwTime;
	BYTE	RoomStation;
};

typedef GS_RoomMsg<__GS_Room_User_TimeOut>	_GS_Room_User_TimeOut;
typedef ZNetMsg<_GS_Room_User_TimeOut>	GS_Room_User_TimeOut;

//GS_ROOM_MSG_TIMEOUT_ERROR
typedef ZNetMsg<__GS_Room_User_TimeOut>	GS_Room_User_TimeOutError;

//GS_ROOM_MSG_COMEINOK
typedef ZNetMsg<_GS_Room_ComeIn>	GS_Room_ComeInOK;

//GS_ROOM_MSG_COMEINFAIL
typedef ZNetMsg<null_type>	GS_Room_ComeInFail;

//GS_ROOM_MSG_WATCHOK
typedef ZNetMsg<_GS_Room_ComeIn>	GS_Room_WatcherComeInOK;

//GS_ROOM_MSG_WATCHFAIL
typedef ZNetMsg<null_type>	GS_Room_WatcherComeInFail;

//GS_ROOM_MSG_CHAT
typedef GS_RoomMsg<_GS_Hall_Chat>	_GS_Room_Chat;
typedef ZNetMsg<_GS_Room_Chat>	GS_Room_Chat;

//GS_ROOM_MSG_CHATDATA
typedef ZNetMsg<_GS_Hall_Chat>	GS_Room_ChatData;

//GS_ROOM_MSG_USER_RUNAWAY
struct _GS_Room_UserRunAway{
	BYTE	RoomStation;
};

typedef ZNetMsg<_GS_Room_UserRunAway>		GS_Room_UserRunAway;

//GS_ROOM_MSG_USER_SURRENDER
typedef GS_Room_UserRunAway		GS_Room_UserSurrender;

#pragma pack (pop)

//////////////////////////////////////////////////////////////////////////////////
//	func

inline void _GameServer_SetMsgHead(_MsgHead *pHead,WORD Size,BYTE State,BYTE ID,
	BYTE AssistantID)
{
	SetMsgHead(*pHead,Size,State,ID,GAME_SERVER_MSG,AssistantID,
		GAME_SERVER_MSG_VER);
}

#endif