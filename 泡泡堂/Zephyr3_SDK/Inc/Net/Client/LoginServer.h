#ifndef ZEPHYR_LOGINSERVER_CLIENT_H
#define ZEPHYR_LOGINSERVER_CLIENT_H

#include <ZStack.h>
#include <Net\ZSocket.h>
#include <Net\Msg\LoginServer.h>
#include <Net\TCP_Client.h>

//获得login server的地址
HRESULT ZLS_GetAddr(DWORD &dwIP,WORD &wPort);
//登陆
HRESULT ZLS_Login(DWORD dwIP,WORD wPort,const char *strID,const char *strPSW,char *strName,BYTE &Logo,BYTE &Sex,BYTE &State);
//注册
HRESULT ZLS_Reg(DWORD dwIP,WORD wPort,ZUserInfo &UserInfo,BYTE &State);

////////////////////////////////////////////////////////////////////////
//	ZLoginServer_Client

const DWORD _ZLS_CLIENT_REQUESTMSG_NUMBER	=	64;

class FLYINGMAGIC_2_CORE_API ZLoginServer_Client : public ZNetClientModule{
protected:
	RequestMsg<LoginServerReg,_ZLS_CLIENT_REQUESTMSG_NUMBER>	m_RegMsg;
	RequestMsg<LoginServerLogin,_ZLS_CLIENT_REQUESTMSG_NUMBER>	m_LoginMsg;

	DWORD					m_dwRegRequestID;
	DWORD					m_dwLoginRequestID;
public:
	inline ZLoginServer_Client();

	virtual HRESULT HandleMessage(void *buf,int len);
	//服务器断开连接
	virtual void ServerCut() { Release(); }

	//注册
	HRESULT Reg(ZUserInfo &UserInfo,void *pData = NULL);
	//登陆
	HRESULT Login(const char *strID,const char *strPSW,void *pData = NULL);
protected:
	//On Msg Ret Login
	virtual HRESULT OnMsgRetLogin(LoginServerRet &Msg);
	//On Msg Ret Reg
	virtual HRESULT OnMsgRetReg(LoginServerRet &Msg);

	inline DWORD GetRegRequestID();
	inline DWORD GetLoginRequestID();
};

inline ZLoginServer_Client::ZLoginServer_Client() : ZNetClientModule(0)
{ 		
	m_dwRegRequestID = m_dwLoginRequestID = 0;
}

inline DWORD ZLoginServer_Client::GetRegRequestID()
{
	return m_dwRegRequestID++;
}

inline DWORD ZLoginServer_Client::GetLoginRequestID()
{
	return m_dwLoginRequestID++;
}

#endif