#ifndef ZEPHYR_GAME_CENTERSERVER_MSG_H
#define ZEPHYR_GAME_CENTERSERVER_MSG_H

#include <Database\ADO.h>
#include <Net\NetMsg.h>
#include <FlyingMagic\BaseDef.h>

#include <Net\Msg\CenterServer.h>
#include <Net\Msg\LoginServer.h>

struct _BaseUserData{
	DWORD		dwID;
	char		strID[__LS_ID_LEN];
	char		strName[USER_NAME_LEN];
	bool		bSex;
	BYTE		bLogo;
};

///////////////////////////////////////////////////////////////////////////////////
// Msg

//消息版本号
const BYTE GAME_CENTERSERVER_MSG_VER	=	0x01;

//---------------------------------------------------------------------------------
//辅助消息ID

///////////////////////////////////////////////////////////////////////////////////
//	GCS_UserService

//接收 由 客户端 发来的消息
//Login
const BYTE GCS_US_MSG_LOGIN				=	0x01;
//Reg
const BYTE GCS_US_MSG_REG				=	0x02;
//Get Server List
const BYTE GCS_US_MSG_GETSERVERLIST		=	0x03;
//Logout
const BYTE GCS_US_MSG_LOGOUT			=	0x04;

//发送 到 客户端 的消息
//Login OK
const BYTE GCS_US_MSG_USERDATA			=	0x10;
//Login fail
const BYTE GCS_US_MSG_RETLOGIN			=	0x11;
//Reg fail
const BYTE GCS_US_MSG_RETREG			=	0x12;
//Ret Server List
const BYTE GCS_US_MSG_SERVERLIST		=	0x13;
//Ret Server Data
const BYTE GCS_US_MSG_SERVERDATA		=	0x15;
//Ret Server List End
const BYTE GCS_US_MSG_SERVERLISTEND		=	0x16;


#pragma pack (push)
#pragma pack (1)

//GCS_US_MSG_LOGOUT
struct _GCS_Logout{
	DWORD	dwID;
};

typedef ZNetMsg<_GCS_Logout>	GCS_Logout;

//GCS_US_MSG_GETSERVERLIST
struct _GCS_GetServerList{
	WORD	NameID;
};

typedef ZNetMsg<_GCS_GetServerList>	GCS_GetServerList;

//ret
struct _GCS_Ret{
	BYTE	bRet;
};

typedef ZNetMsg<_GCS_Ret>	GCS_Ret;

//GCS_US_MSG_USERDATA
struct _GCS_UserData{
	DWORD	dwID;
	char	ID[__LS_ID_LEN];
	char	Name[USER_NAME_LEN];
	bool	bSex;
	BYTE	bLogo;

	void Fix()
	{
		ID[__LS_ID_LEN-1] = Name[USER_NAME_LEN-1] = '\0';
	}
};

typedef ZNetMsg<_GCS_UserData>	GCS_UserData;

//GCS_US_MSG_SERVERLIST
struct _GCS_US_ServerData{
	DWORD	NameID;
	int		iUsers;
	char	Memo[__CS_MEMO_LEN];
	DWORD	dwIP;
	WORD	wPort;

	void Fix(){
		Memo[__CS_MEMO_LEN-1] = '\0';
	}
};

typedef ZNetMsg_MulData<_GCS_US_ServerData>	GCS_ServerList;

//GCS_US_MSG_SERVERDATA
typedef ZNetMsg<_GCS_US_ServerData>	GCS_US_ServerData;

//GCS_US_MSG_SERVERLISTEND
typedef ZNetMsg<null_type>	GCS_ServerListEnd;

#pragma pack (pop)

///////////////////////////////////////////////////////////////////////////////////
//	GCS_GSService
#ifdef __ZEPHYR_GAME_CS_SERVER

//接收 由 客户端 发来的消息
//Login
const BYTE GCS_GSS_MSG_LOGIN			=	0x50;
//ComeIn
const BYTE GCS_GSS_MSG_COMEIN			=	0x51;

//发送 到 客户端 的消息
//Login fail
const BYTE GCS_GSS_MSG_RETLOGIN			=	0x60;
//Login OK
const BYTE GCS_GSS_MSG_SERVERDATA		=	0x61;
//ComeIn fail
const BYTE GCS_GSS_MSG_RETCOMEIN		=	0x62;
//ComeIn OK
const BYTE GCS_GSS_MSG_USERDATA			=	0x63;


#pragma pack (push)
#pragma pack (1)

//GCS_GSS_MSG_LOGIN
struct _GCS_ServerLogin{
	DWORD	dwIP;
	WORD	wPort;
	WORD	NameID;
	char	Memo[__CS_MEMO_LEN];
	int		iUsers;

	void Fix(){
		Memo[__CS_MEMO_LEN-1] = '\0';
	}
};

typedef ZNetMsg<_GCS_ServerLogin> GCS_ServerLogin;

//GCS_GSS_MSG_COMEIN
struct _GCS_ComeIn{
	DWORD		dwID;
	char		strID[__LS_ID_LEN];

	void Fix(){
		strID[__LS_ID_LEN-1] = '\0';
	}
};

typedef ZNetMsg<_GCS_ComeIn>	GCS_ComeIn;

//GCS_GSS_MSG_RETLOGIN
const BYTE GCS_GSS_LOGIN_RET_ALREADYLOGIN	=	0x01;
const BYTE GCS_GSS_LOGIN_RET_NODATABASE		=	0x02;

//GCS_GSS_MSG_SERVERDATA
struct _GCS_ServerData{
	DWORD	dwID;
	DWORD	dwSQLIP;
	char	ID[DB_USER_ID_LEN];
	char	PSW[DB_USER_PSW_LEN];
	char	Table[DB_TABLENAME_LEN];

	void Fix(){
		ID[DB_USER_ID_LEN-1] = PSW[DB_USER_PSW_LEN-1] = Table[DB_TABLENAME_LEN-1] = '\0';
	}
};

typedef ZNetMsg<_GCS_ServerData> GCS_ServerData;

//GCS_GSS_MSG_RETCOMEIN
typedef ZNetMsg<null_type> GCS_RetComeIn;

#pragma pack (pop)

#endif//__ZEPHYR_GAME_CS_SERVER

//////////////////////////////////////////////////////////////////////////////////
//	func

inline void _GCS_SetMsgHead(_MsgHead *pHead,WORD Size,BYTE State,DWORD ID,
	BYTE AssistantID)
{
	SetMsgHead(*pHead,Size,State,ID,GAME_CENTERSERVER_MSG,AssistantID,
		GAME_CENTERSERVER_MSG_VER);
}

#endif