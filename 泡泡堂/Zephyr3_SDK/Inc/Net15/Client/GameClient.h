/*
							Zephyr Engine v3.0

								by �Ժ���(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	GameClient.h

							Describe:	��Ϸ �ͻ���

							Author:		�Ժ���(xueren)

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

	// ���÷�������Ϣ
	void SetServerInfo(int minUsers,int maxUsers);

	// ��Դ�ͷź���
	void Release();

	// ��ʼ��
	void Init();

	// ����
	void Connect(DWORD dwIP,WORD wPort);
protected:
	virtual GS_Client_UserDataManage *CreateUserDataManage() { return new GS_Client_SimpleScore_UDM; }

	virtual GS_RoomService_Client *CreateRoomClient(DWORD wndMsg) = 0;

	void UpdateUserData(int users,GS_Client_SimpleScore_UDM::_UserData *user);
};

#endif//_FLYINGMAGIC_2_CLIENT_CORE_GAMECLIENT_H