#ifndef ZEPHYR_GAME_CENTERSERVER_CLIENT_H
#define ZEPHYR_GAME_CENTERSERVER_CLIENT_H

#ifndef __ZEPHYR_GAME_CS_SERVER
#define __ZEPHYR_GAME_CS_SERVER
#endif

//#include <Database\ADO.h>
#include <ZState.h>
#include <Net15\TCP_Client.h>
#include <Net15\Client\CenterServer.h>
#include <Net15\Msg\Game_CenterServer.h>
#include <Net2\RequestMsg.h>

class GS_HallService;
class GS_UserDataManage;
class GS_RoomService;

///////////////////////////////////////////////////////////////////////////////////
//	GCS_GSService_Client

class FLYINGMAGIC_2_CORE_API GCS_GSService_Client : public ZNetClientModule{
	typedef ZNet2::RequestMsgManager<GCS_ComeIn,64>	RMM_ComeIn;
private:
	RMM_ComeIn					m_ComeInMsg;
	DWORD						m_dwComeInRequestID;

	GS_HallService				*m_pHallService;
	GS_UserDataManage			*m_pUserDataManage;

	ZState_Byte					m_State;

	WORD						m_ServerID;
public:
	inline GCS_GSService_Client(WORD ServerID,DWORD wndMsg);

	HRESULT Init(GS_HallService *pHallService,GS_UserDataManage *pUserDataManage,DWORD CS_IP,WORD CS_Port);

	//virtual from ZNetClientModule
	virtual HRESULT HandleMessage(void *buf,int len);
	//virtual from ZNetClientModule
	//服务器断开连接
	virtual void ServerCut();

	void Login();

	void ComeIn(DWORD dwID,const char *strID,void *pData);

	inline DWORD GetComeInRequestID();
private:
	//Msg RetLogin
	HRESULT OnMsgRetLogin(GCS_Ret &Msg);
	//Msg ServerData
	HRESULT OnMsgServerData(GCS_ServerData &Msg);
	//Msg RetComeIn
	HRESULT OnMsgRetComeIn(GCS_RetComeIn &Msg);
	//Msg UserData
	HRESULT OnMsgUserData(GCS_UserData &Msg);
};

inline GCS_GSService_Client::GCS_GSService_Client(WORD ServerID,DWORD wndMsg) 
		: ZNetClientModule(wndMsg)
		, m_ComeInMsg(30)
{
	m_ServerID = ServerID;

	m_pHallService = NULL;
	m_pUserDataManage = NULL;

	m_dwComeInRequestID = 0;
}

inline DWORD GCS_GSService_Client::GetComeInRequestID()
{
	return m_dwComeInRequestID++;
}

#endif