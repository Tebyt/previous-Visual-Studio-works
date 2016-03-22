#ifndef _ZEPHYR_NET_MESSAGE_H
#define _ZEPHYR_NET_MESSAGE_H

#include <Net15\ZMsgData.h>

//////////////////////////////////////////////////////////////////////
//	Center Server

//主消息ID
const BYTE	CENTERSERVER_MSG			=	0x01;

//////////////////////////////////////////////////////////////////////
//	login module
//		by y2k3.2.21 zhs007

//主消息ID
const BYTE	ZEPHYRLOGIN_MSG				=	0x02;

//////////////////////////////////////////////////////////////////////
//	Game CenterServer
//		by y2k3.2.28 zhs007

//主消息ID
const BYTE	GAME_CENTERSERVER_MSG		=	0x03;

//////////////////////////////////////////////////////////////////////
//	Game Server
//		by y2k3.3.4 zhs007

//主消息ID
const BYTE	GAME_SERVER_MSG				=	0x05;


//用户可以使用的主消息ID
const BYTE	ZEPHYRUSER_MSG				=	0x06;

#endif