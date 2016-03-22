#ifndef ZEPHYR_NET_CLIENT_CENTERSERVER_H
#define ZEPHYR_NET_CLIENT_CENTERSERVER_H

#include <Net\ZSocket.h>
#include <Net\Msg\CenterServer.h>

void FLYINGMAGIC_2_CORE_API GetAddr(DWORD &ip,WORD &port,const char *dat);

HRESULT GetCenterServerAddr(DWORD &ip,WORD &port);

HRESULT RegServer(DWORD ip,WORD port,ServerData &data);

HRESULT KillServer(DWORD ip,WORD port,ServerData &data);

int GetServerList(DWORD ip,WORD port,WORD NameID,const char *strMemo,
	ServerData *lpdata,int len);

#endif