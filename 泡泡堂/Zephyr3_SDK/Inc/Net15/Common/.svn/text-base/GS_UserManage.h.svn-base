// \Net\Common\GS_UserManage.h
// 游戏服务器用户信息管理
// Write by zhs007			y2k3.5.9

#ifndef __ZNET_COMMON_GS_USERMANAGE_H
#define __ZNET_COMMON_GS_USERMANAGE_H

#include <ZState.h>
#include <ZStack.h>
#include <Database\ADO.h>
#include <FlyingMagic\BaseDef.h>
#include <Net\TCP_Server.h>
#include <Net\Msg\LoginServer.h>
#include <Net\Msg\Game_Server.h>
#include <Net\Client\CenterServer.h>
#include <Net\Client\Game_CenterServer.h>

///////////////////////////////////////////////////////////////////////////////////
//	GS_UserDataManage

const HRESULT ZGS_UMD_NODATA	=	0x80000777;

class GS_HallService;

//GS_UserDataManage State
const	BYTE	GS_USERDATAMANAGE_INIT			=	0x01;

class GS_UserDataManage{
public:
	struct _GameData;

	struct _UserData{
		_BaseUserData	Base;
		_GameData		*pGame;
		ContextKey		*pKey;
		DWORD			RoomID;
	};
protected:
	ZCriticalSection			m_DBLock;
	ZDatabase					m_Database;
	char						m_DB_ID[DB_USER_ID_LEN];
	char						m_DB_PSW[DB_USER_PSW_LEN];
	char						m_TableName[DB_TABLENAME_LEN];
	DWORD						m_dwDB_IP;

	ZState_Byte					m_bState;

	ZLinkEx<_UserData,512,128>	m_DataLink;
	ZCriticalSection			m_DataLock;

	GS_HallService				*m_pHallService;
public:
	inline GS_UserDataManage();

	HRESULT Init(DWORD IP,const char *strID,const char *strPSW,const char *TableName);

	void Release();
    
	HRESULT UserComeIn(_BaseUserData &Base,ContextKey *pKey);

	GS_UserDataManage::_UserData *Find(DWORD ID);

	inline void SetService(GS_HallService *pHallService);

	bool IsInit() { return m_bState.Has(GS_USERDATAMANAGE_INIT); }
protected:
	virtual HRESULT UpdateUserData(GS_UserDataManage::_UserData *pUser) = 0;

	virtual HRESULT UpdateGameData(GS_UserDataManage::_UserData *pUser) = 0;

	virtual HRESULT GetUserData(GS_UserDataManage::_UserData &User,GS_UserDataManage::_GameData *pGame) = 0;

	virtual GS_UserDataManage::_GameData *AddGameData() = 0;

	virtual void DefaultGameData(GS_UserDataManage::_GameData &game) = 0;
};

inline GS_UserDataManage::GS_UserDataManage()
{
	m_pHallService = NULL;
}

inline void GS_UserDataManage::SetService(GS_HallService *pHallService)
{
	ZASSERT(pHallService);

	m_pHallService = pHallService;
}

///////////////////////////////////////////////////////////////////////////////////
//	GS_SimpleScore_UDM

class GS_SimpleScore_UDM : public GS_UserDataManage{
public:
	struct GS_UserDataManage::_GameData{
		long lScore;
		long lWin,lLose,lTotal,lRunAway;
	};
private:
	ZLinkEx<_GameData,512,128>	m_GameDataLink;
	ZCriticalSection			m_GameDataLock;
public:
private:
	virtual HRESULT UpdateUserData(GS_UserDataManage::_UserData *pUser);

	virtual HRESULT UpdateGameData(GS_UserDataManage::_UserData *pUser);

	virtual HRESULT GetUserData(GS_UserDataManage::_UserData &User,GS_UserDataManage::_GameData *pGame);

	virtual GS_UserDataManage::_GameData *AddGameData();

	virtual void DefaultGameData(GS_UserDataManage::_GameData &game);
};

#endif//__ZNET_COMMON_GS_USERMANAGE_H