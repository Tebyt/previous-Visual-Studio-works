/*
							Zephyr Engine v3.0

							by ’‘∫ÈÀ…(xueren) 2002 - 2006


							http://www.flyingmagic.net
							E-mail:sssxueren@gmail.com

							FileName:	Net2\ServiceNetKernel2.h

							Describe:	Õ¯¬Á∫À–ƒ

							Author:		’‘∫ÈÀ…(xueren)

							CreateTime: 2006.02.16
							UpdateTime:
*/

#ifndef __ZEPHYR_NET_2_NET_SERVICENETKERNEL_2_H__
#define __ZEPHYR_NET_2_NET_SERVICENETKERNEL_2_H__

#include <Net2\BaseDef.h>
#include <Net2\NetKernel2.h>

namespace ZNet2{

	////////////////////////////////////////////////////////////////////////////
	// ServiceNetKernel2

	class ZEPHYR_NET_API ServiceNetKernel2 : public NetKernel2{
	protected:
		ServiceNetKernel2(LPMsgWorker lpMsgWorker) : NetKernel2(lpMsgWorker) {}
	};
}

#endif // __ZEPHYR_NET_2_NET_SERVICENETKERNEL_2_H__
