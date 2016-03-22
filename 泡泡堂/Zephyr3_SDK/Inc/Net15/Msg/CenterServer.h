#ifndef ZEPHYR_NET_MSG_CENTERSERVER_H
#define ZEPHYR_NET_MSG_CENTERSERVER_H

#include <Net15\TCP_Server.h>
#include <Net2\NetMsg.h>

///////////////////////////////////////////////////////////////////////////////////
//	Msg

//reg server
#define CENTERSERVER_MSG_REGSERVER		0x01
//get server list
#define CENTERSERVER_MSG_GETSERVERLIST	0x02
//kill server
#define CENTERSERVER_MSG_KILLSERVER		0x03

//reg server return
#define CENTERSERVER_MSG_REGRET			0x10
//send server list
#define CENTERSERVER_MSG_SERVERLIST		0x11


///////////////////////////////////////////////////////////////////////////////////
//	Msg Data

const int __CS_MEMO_LEN		=	64;

#pragma pack (push)
#pragma pack (1)

//reg server or ret get server list or kill server
struct _CenterServerServer{
	DWORD	dwIP;
	WORD	wPort;
	WORD	NameID;
	char	Memo[__CS_MEMO_LEN];

	void Fix(){
		Memo[__CS_MEMO_LEN-1] = '\0';
	}
};

typedef ZNet2::ZNetMsg<_CenterServerServer>	CenterServerServer;

//reg server ret
struct _CenterServerRegRet{
	BYTE bState;
};

const BYTE	CENTERSERVER_REG_RET_OK			=	0;
const BYTE	CENTERSERVER_REG_RET_ALREADYRUN	=	0x01;	//服务器已经存在

typedef ZNet2::ZNetMsg<_CenterServerRegRet>	CenterServerRegRet;

//get server list
struct _CenterServerGetServerList{
	char	Memo[__CS_MEMO_LEN];
	int		Nums;
	WORD	NameID;

	void Fix(){
		Memo[__CS_MEMO_LEN-1] = '\0';
	}
};

typedef ZNet2::ZNetMsg<_CenterServerGetServerList>	CenterServerGetServerList;

#pragma pack (pop)

//////////////////////////////////////////////////////////////////////
//	ServerData

#pragma pack (push)
#pragma pack (1)

//server data
struct ServerData{
	DWORD	dwIP;
	WORD	wPort;
	WORD	NameID;
	char	Memo[__CS_MEMO_LEN];

	ServerData()
	{
		Memo[0]='\0';
	}

	inline bool operator  ==  (const ServerData &s) const;

	inline bool operator != (const ServerData &s) const;
};

inline bool ServerData::operator  ==  (const ServerData &s) const
{
	return this->dwIP  ==  s.dwIP && 
		this->wPort  ==  s.wPort && 
		NameID == s.NameID && 
		strcmp(this->Memo,s.Memo)  ==  0;
}

inline bool ServerData::operator != (const ServerData &s) const 
{ 
	return !((*this)  ==  s); 
}

#pragma pack (pop)

//////////////////////////////////////////////////////////////////////////////////
//	func
/*
inline void _CenterServer_SetMsgHead(ZNet2::ZNetMsgHead* pHead,WORD Size,BYTE AssistantID)
{
	pHead->SetHead(Size,CENTERSERVER_MSG,AssistantID);
}
*/
/////////////////////////////////////////////////////////////////////////////////
//	NameID

//Login Server
const WORD	__LOGIN_SERVER_NAME_ID			=	0x01;

//大家来找X 中心服务器
const WORD __FINDX_CENTERSERVER_NAME_ID		=	0x02;

//游戏中心服务器 用户服务
const WORD __GCS_USERSERVICE_NAME_ID		=	0x03;

//游戏中心服务器 服务器服务
const WORD __GCS_GSSERVICE_NAME_ID			=	0x05;

//五子棋游戏服务器 大厅服务
const WORD __FIVE_GS_HALLSERVICE_NAME_ID	=	0x06;

//黑白棋游戏服务器大厅服务
const WORD	__BW_GS_HALLSERVICE_NAME_ID		=	0x07;

//扫雷游戏服务器大厅服务
const WORD	__SL_GS_HALLSERVICE_NAME_ID		=	0x08;

//FindX 游戏服务器大厅服务
const WORD	__FINDX_GS_HALLSERVICE_NAME_ID	=	0x09;

//象棋 游戏服务器大厅服务
const WORD	__CCHESS_GS_HALLSERVICE_NAME_ID	=	0x0a;

//斗地主 游戏服务器大厅服务
const WORD	__LAIRD_GS_HALLSERVICE_NAME_ID	=	0x0b;

#endif
