/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Net2\NetKernel.h

							Describe:	服务器

							Author:		赵洪松(xueren)

							CreateTime: 2003.11.25
							UpdateTime:
*/

#ifndef _ZEPHYR_NET_2_BASE_SERVER_H
#define _ZEPHYR_NET_2_BASE_SERVER_H

#include <ZDebug.h>
#include <ZThread.h>
#include <Net2\BaseDef.h>
#include <Net2\NetStream.h>
#include <Net2\ZSocket.h>

////////////////////////////////////////////////////////////////////////////////
// ZNet2
namespace ZNet2{

	////////////////////////////////////////////////////////////////////////////
	// NetKernel
	// 网络核心

	class ZEPHYR_NET_API NetKernel : public ZThread{
	public:
		// SendMsg
		virtual int SendMsg(LPVOID pAddr,LPVOID pMsg,int msgLen) = 0;

		// 出错输出
		virtual HRESULT Error(LPVOID pAddr,HRESULT hRet,const char* str) = 0;

		// 获得连接地址私有数据
		virtual void SetData(LPVOID pAddr,LPVOID pData) = 0;

		// 获得连接地址私有数据
		virtual LPVOID GetData(LPVOID pAddr) = 0;
	};

	typedef NetKernel*	LPNetKernel;

	////////////////////////////////////////////////////////////////////////////
	// ServiceNetKernel
	// 网络核心

	class ZEPHYR_NET_API ServiceNetKernel : public NetKernel{
	public:
	};

	////////////////////////////////////////////////////////////////////////////
	// ClientNetKernel
	// 网络核心

	class ZEPHYR_NET_API ClientNetKernel : public NetKernel{
	public:
	};
};

#endif//_ZEPHYR_NET_2_BASE_SERVER_H