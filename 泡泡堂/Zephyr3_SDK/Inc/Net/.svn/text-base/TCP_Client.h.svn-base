#ifndef ZEPHYR_TCP_CLIENT_MODULE_H
#define ZEPHYR_TCP_CLIENT_MODULE_H

#include <ZThread.h>
#include <ZLock.h>
#include <ZState.h>
#include <Net\zsocket.h>
#include <Net\netmsg.h>

//////////////////////////////////////////////////////////////////////
//	ZNetClientModule

class ZEPHYR_NET_API ZNetClientModule : public ZThread{
private:
protected:
	ZState_Byte			m_bState;

	SOCKET				m_Socket;

	DWORD				m_ServerIP;
	WORD				m_ServerPort;

	ZNetStream			m_recvStream;

	HWND				m_dstWnd;
	DWORD				m_wndMsg;
public:
	inline ZNetClientModule(DWORD wndMsg);
	virtual ~ZNetClientModule() { DEBUGMESSAGE2("Client 0x%.8x Release!",this); }

	HRESULT Init(DWORD dwIP,WORD wPort);

	virtual HRESULT HandleMessage(void *buf,int len) = 0;

	virtual HRESULT Run(void *lpparam);
	//服务器断开连接
	virtual void ServerCut();

	//Send
	inline int SendMsg(void *buf,int len);
	//Release
	void Release();

	void SetHWND(HWND hWnd) { m_dstWnd = hWnd; }

	void SetWndMsg(DWORD wndMsg) { m_wndMsg = wndMsg; }
protected:
	//Post Msg
	void PostMsg(DWORD wParam,DWORD lParam);
};

inline ZNetClientModule::ZNetClientModule(DWORD wndMsg)
{
	m_Socket = NULL;
	m_ServerIP = 0;
	m_ServerPort = 0;
	m_dstWnd = NULL;

	m_wndMsg = wndMsg;
}

inline int ZNetClientModule::SendMsg(void *buf,int len)
{
	ZASSERT(buf != NULL && len != 0);
	ZASSERT(m_Socket != NULL);

	int sendLen = 0;

	do{
#ifdef _DEBUG
		if(sendLen != 0)
			Debug("Send not once! %d",len);
#endif
		sendLen += ::send(m_Socket,(char *)buf,len,0);
		if(sendLen < 0)
		{
			WSARet(E_FAIL,"SendMsg() fail!");

			sendLen = 0;
		}

	}while(sendLen < len);

	return sendLen;
}

//Post Msg
inline void ZNetClientModule::PostMsg(DWORD wParam,DWORD lParam) 
{ 
	ZASSERT(m_dstWnd);

	PostMessage(m_dstWnd,m_wndMsg,wParam,lParam); 
}

#endif