#ifndef ZEPHYR_LOGINSERVER_MSG_H
#define ZEPHYR_LOGINSERVER_MSG_H

#include <Net\NetMsg.h>
#include <FlyingMagic\BaseDef.h>

const int	__LS_ID_LEN			=	20;
const int	__LS_PSW_LEN		=	20;
const int	__LS_EMAIL_LEN		=	32;
const int	__LS_IDNUMBER_LEN	=	20;
const int	__LS_COUNTRY_LEN	=	20;
const int	__LS_PROVINCE_LEN	=	12;
const int	__LS_CITY_LEN		=	16;
const int	__LS_QUESTION_LEN	=	40;
const int	__LS_ANSWER_LEN		=	20;
const int	__LS_MEMO_LEN		=	200;

///////////////////////////////////////////////////////////////////////////////////
//	User Info Struct

struct ZUserInfo{
	char	ID[__LS_ID_LEN];
	char	PSW[__LS_PSW_LEN];
	char	Name[USER_NAME_LEN];
	char	EMail[__LS_EMAIL_LEN];
	char	IDNumber[__LS_IDNUMBER_LEN];
	WORD	wYear;
	BYTE	bMonth;
	BYTE	bDay;
	char	Country[__LS_COUNTRY_LEN];
	char	Province[__LS_PROVINCE_LEN];
	char	City[__LS_CITY_LEN];
	char	Question[__LS_QUESTION_LEN];
	char	Answer[__LS_ANSWER_LEN];
	char	Memo[__LS_MEMO_LEN];
	BYTE	bLogo;
	BYTE	bSex;
	WORD	wReserve;

	void Fix(){
		ID[__LS_ID_LEN-1] = PSW[__LS_PSW_LEN-1] = Name[USER_NAME_LEN-1] = 
			EMail[__LS_EMAIL_LEN-1] = IDNumber[__LS_IDNUMBER_LEN-1] = 
			Country[__LS_COUNTRY_LEN-1] = Province[__LS_PROVINCE_LEN-1] = 
			City[__LS_CITY_LEN-1] = Question[__LS_QUESTION_LEN-1] = 
			Answer[__LS_ANSWER_LEN-1] = Memo[__LS_MEMO_LEN-1] = '\0';
	}
};

///////////////////////////////////////////////////////////////////////////////////
// Msg

//消息版本号
#define ZEPHYRLOGIN_MSG_VER	0x01

//---------------------------------------------------------------------------------
//辅助消息ID

//server
//用户登陆
#define ZEPHYRLOGIN_MSG_LOGIN		0x01
//用户注册
#define ZEPHYRLOGIN_MSG_REG			0x02

//client
//用户登陆的返回消息
#define ZEPHYRLOGIN_MSG_RETLOGIN	0x03
//用户注册的返回消息
#define ZEPHYRLOGIN_MSG_RETREG		0x04


///////////////////////////////////////////////////////////////////////////////////
//	Msg Data

//Login msg
struct _LoginServerLogin{
	char	ID[__LS_ID_LEN];
	char	PSW[__LS_PSW_LEN];

	void Fix(){
		ID[__LS_ID_LEN-1] = PSW[__LS_PSW_LEN-1] = '\0';
	}
};

typedef ZNetMsg<_LoginServerLogin> LoginServerLogin;

//Reg msg
typedef ZNetMsg<ZUserInfo> LoginServerReg;

#pragma pack (push)
#pragma pack (1)

struct _LoginServerRet{
	char	Name[USER_NAME_LEN];
	BYTE	bLogo;
	BYTE	bSex;
	BYTE	Ret;

	void Fix(){
		Name[USER_NAME_LEN-1] = '\0';
	}
};

typedef ZNetMsg<_LoginServerRet> LoginServerRet;

#pragma pack (pop)

//Login Ret
const BYTE	ZLOGINSERVER_LOGIN_OK		=	0;
const BYTE	ZLOGINSERVER_LOGIN_IDFAIL	=	0x01;
const BYTE	ZLOGINSERVER_LOGIN_PSWFAIL	=	0x02;
const BYTE	ZLOGINSERVER_LOGIN_FAIL		=	0xff;

//Reg Ret
const BYTE	ZLOGINSERVER_REG_OK			=	0;
const BYTE	ZLOGINSERVER_REG_IDFAIL		=	0x01;
const BYTE	ZLOGINSERVER_REG_NAMEFAIL	=	0x02;
const BYTE	ZLOGINSERVER_REG_ADDFAIL	=	0x03;
const BYTE	ZLOGINSERVER_REG_FAIL		=	0xff;

//////////////////////////////////////////////////////////////////////////////////
//	func

inline void _LoginServer_SetMsgHead(_MsgHead *pHead,WORD Size,BYTE State,DWORD ID,
	BYTE AssistantID)
{
	SetMsgHead(*pHead,Size,State,ID,ZEPHYRLOGIN_MSG,AssistantID,
		ZEPHYRLOGIN_MSG_VER);
}

#endif