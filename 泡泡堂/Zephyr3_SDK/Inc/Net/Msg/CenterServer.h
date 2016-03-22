#ifndef ZEPHYR_NET_MSG_CENTERSERVER_H
#define ZEPHYR_NET_MSG_CENTERSERVER_H

#include <Net\TCP_Server.h>

///////////////////////////////////////////////////////////////////////////////////
//	Msg

//��Ϣ�汾��
#define CENTERSERVER_MSG_VER	0x01

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

//const int __CS_NAME_LEN		=	64;
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

typedef ZNetMsg<_CenterServerServer>	CenterServerServer;

//reg server ret
struct _CenterServerRegRet{
	BYTE bState;
};

const BYTE	CENTERSERVER_REG_RET_OK			=	0;
const BYTE	CENTERSERVER_REG_RET_ALREADYRUN	=	0x01;	//�������Ѿ�����

typedef ZNetMsg<_CenterServerRegRet>	CenterServerRegRet;

//get server list
struct _CenterServerGetServerList{
	char	Memo[__CS_MEMO_LEN];
	int		Nums;
	WORD	NameID;

	void Fix(){
		Memo[__CS_MEMO_LEN-1] = '\0';
	}
};

typedef ZNetMsg<_CenterServerGetServerList>	CenterServerGetServerList;

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

inline void _CenterServer_SetMsgHead(_MsgHead *pHead,WORD Size,BYTE State,DWORD ID,
	BYTE AssistantID)
{
	SetMsgHead(*pHead,Size,State,ID,CENTERSERVER_MSG,AssistantID,
		CENTERSERVER_MSG_VER);
}

/////////////////////////////////////////////////////////////////////////////////
//	NameID

//Login Server
const WORD	__LOGIN_SERVER_NAME_ID			=	0x01;

//�������X ���ķ�����
const WORD __FINDX_CENTERSERVER_NAME_ID		=	0x02;

//��Ϸ���ķ����� �û�����
const WORD __GCS_USERSERVICE_NAME_ID		=	0x03;

//��Ϸ���ķ����� ����������
const WORD __GCS_GSSERVICE_NAME_ID			=	0x05;

//��������Ϸ������ ��������
const WORD __FIVE_GS_HALLSERVICE_NAME_ID	=	0x06;

//�ڰ�����Ϸ��������������
const WORD	__BW_GS_HALLSERVICE_NAME_ID		=	0x07;

//ɨ����Ϸ��������������
const WORD	__SL_GS_HALLSERVICE_NAME_ID		=	0x08;

//FindX ��Ϸ��������������
const WORD	__FINDX_GS_HALLSERVICE_NAME_ID	=	0x09;

//���� ��Ϸ��������������
const WORD	__CCHESS_GS_HALLSERVICE_NAME_ID	=	0x0a;

//������ ��Ϸ��������������
const WORD	__LAIRD_GS_HALLSERVICE_NAME_ID	=	0x0b;
#endif
