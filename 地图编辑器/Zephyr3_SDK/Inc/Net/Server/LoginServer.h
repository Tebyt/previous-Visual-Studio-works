#ifndef ZEPHYR_NET_SERVER_LOGIN_H
#define ZEPHYR_NET_SERVER_LOGIN_H

#include <ZState.h>
#include <Net\TCP_Server.h>
#include <Net\Client\CenterServer.h>
#include <Net\Msg\LoginServer.h>
//#include <Database\ADO.h>
#include <Net\MsgThread.h>

//外部实现函数调用，将Msg变为String
void _ZLS_Msg2Str(char *Str,int strLen,DWORD IP,WORD Port,void *Msg,int msgLen);
//外部实现函数，负责将Msg，显示给用户
void _ZLS_Msg(DWORD IP,WORD Port,void *Msg,int megLen);

const char		ZLOGINSERVER_TABLE[]	=	"LoginUsers";

//ZLoginServer State
const	BYTE	LOGINSERVER_INIT			=	0x01;
const	BYTE	LOGINSERVER_REG				=	0x02;
const	BYTE	LOGINSERVER_OPENDB			=	0x04;
const	BYTE	LOGINSERVER_MSGTHREADPOOL	=	0x08;

class ZLoginServer : public ZNetServerModule{
private:
	ZDatabase			m_Database;
	ZCriticalSection	m_DatabaseLock;

	ServerData			m_Data;

	ZState_Byte			m_State;

	DWORD				m_dwCenterServerIP;
	WORD				m_wCenterServerPort;

	MsgThreadPool		m_MsgThreadPool;

	MsgPool<sizeof(LoginServerReg),256,128>		m_MsgPool;
public:
	inline ZLoginServer(DWORD wndMsg) : ZNetServerModule(wndMsg) { ; }

	HRESULT Init(WORD port,const char *strName,const char *strID,const char *strPSW);

	virtual HRESULT HandleMessage(ContextKey *pKey,void *buf,int len,bool bUseMsgPool = true);

	virtual HRESULT TimerFunc(void *lpParam);
	//Release
	void Release();
	//Logout
	inline void Logout();
private:
	//Login Msg
	HRESULT OnMsgLogin(ContextKey *pKey,LoginServerLogin &Msg);
	//Reg Msg
	HRESULT OnMsgReg(ContextKey *pKey,LoginServerReg &Msg);
	//Send Ret Msg
	void SendMsgRet(ContextKey *pKey,DWORD ID,BYTE MsgID,const char *strName,BYTE bLogo,BYTE Sex,BYTE Ret);
	//Get Password For ID
	HRESULT _GetPSWForID(char *strPSW,char *strName,BYTE &bLogo,BYTE &Sex,const char *ID);
	//Has ID
	bool HasID(const char *ID);
	//Has Name
	bool HasName(const char *Name);
};

//Logout
inline void ZLoginServer::Logout()
{
	KillServer(m_dwCenterServerIP,m_wCenterServerPort,m_Data);
}

#endif