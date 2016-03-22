/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	GameClient.h

							Describe:	游戏 客户端

							Author:		赵洪松(xueren)

							CreateTime: 2003.10.08
							UpdateTime:
*/

#ifndef _FLYINGMAGIC_2_CLIENT_CORE_GAMECLIENT_H
#define _FLYINGMAGIC_2_CLIENT_CORE_GAMECLIENT_H

#include <Net\Client\Game_Server.h>

///////////////////////////////////////////////////////////////////////////////////
//	Game_Client

class FLYINGMAGIC_2_CORE_API Game_Client{
protected:
	GS_Client_UserDataManage			*m_UserDataManage;

	GS_HallService_Client::_RoomData	m_RoomData;

	GameServerInfo						m_ServerInfo;

	GS_RoomService_Client				*m_RoomClient;

	ZThreadSystem						*m_pThreadSystem;

	DWORD								m_RoomWndMsg;
	HWND								m_hWnd;
public:
	Game_Client(int users,GS_Client_SimpleScore_UDM::_UserData *user,ZThreadSystem *pThreadSystem,HWND hWnd,DWORD RoomWndMsg);
	~Game_Client() { Release(); }

	// 设置服务器信息
	void SetServerInfo(int minUsers,int maxUsers);

	// 资源释放函数
	void Release();

	// 初始化
	void Init();

	// 连接
	void Connect(DWORD dwIP,WORD wPort);
protected:
	virtual GS_Client_UserDataManage *CreateUserDataManage() { return new GS_Client_SimpleScore_UDM; }

	virtual GS_RoomService_Client *CreateRoomClient(DWORD wndMsg) = 0;

	void UpdateUserData(int users,GS_Client_SimpleScore_UDM::_UserData *user);
};

#endif//_FLYINGMAGIC_2_CLIENT_CORE_GAMECLIENT_H