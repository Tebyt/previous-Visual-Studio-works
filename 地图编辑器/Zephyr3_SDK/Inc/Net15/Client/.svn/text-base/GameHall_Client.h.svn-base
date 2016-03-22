/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	GameHall_Client.h

							Describe:	游戏大厅 客户端

							Author:		赵洪松(xueren)

							CreateTime: 2003.10.07
							UpdateTime:
*/

#ifndef _FLYINGMAGIC_2_CLIENT_CORE_GAMEHALL_H
#define _FLYINGMAGIC_2_CLIENT_CORE_GAMEHALL_H

#include <Net\Client\Game_Server.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GameHall_Client

class FLYINGMAGIC_2_CORE_API GameHall_Client{
protected:
	GS_Client_UserDataManage		*m_pUserDataManage;
	GS_HallService_Client			m_HallClient;

	GameServerInfo					m_ServerInfo;
public:
	// 构造函数
	GameHall_Client(_BaseUserData &userData,ZThreadSystem *pThreadSystem,HWND hWnd,DWORD HallWndMsg);
	// 析构函数
	~GameHall_Client() { Release(); }

	// 设置服务器信息
	void SetServerInfo(int minUsers,int maxUsers);
	// 进入大厅
	void ComeIn(WORD ServerID,DWORD IP,WORD Port) { m_HallClient.Init(m_pUserDataManage,ServerID,IP,Port); }

	// 资源释放函数
	void Release();
protected:
	// 创建 用户数据管理 实例
	virtual GS_Client_UserDataManage *CreateUserDataManage() { return new GS_Client_SimpleScore_UDM; }
};

#endif//_FLYINGMAGIC_2_CLIENT_CORE_GAMEHALL_H