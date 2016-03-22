/*
							Zephyr Engine v3.0

								by ÕÔºéËÉ(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Net2\BaseDef.h

							Describe:	ÍøÂçºËÐÄ¶¨Òå

							Author:		ÕÔºéËÉ(xueren)

							CreateTime: 2003.11.5
							UpdateTime:
*/

#ifndef _ZEPHYR_NET_2_BASEDEF_H
#define _ZEPHYR_NET_2_BASEDEF_H

#ifdef _ZEPHYR_NET_22__

#ifdef _ZEPHYR_NET_VER
#undef _ZEPHYR_NET_VER
#endif // 

#define _ZEPHYR_NET_VER	2200

#define _ZEPHYR_NET_21__

#else // _ZEPHYR_NET_22__

#ifdef _ZEPHYR_NET_VER
#undef _ZEPHYR_NET_VER
#endif // 

#ifdef _ZEPHYR_NET_21__
#define _ZEPHYR_NET_VER	2100
#else // 
#define _ZEPHYR_NET_VER	2000
#endif // 

#endif // _ZEPHYR_NET_22__

#if _ZEPHYR_NET_VER >= 2100
//////////////////////////////////////////////////////////////////////////////////////
// Lib & Dll
#ifdef __ZEPHYR3_STATIC
#define ZEPHYR_NET_API
#else//__ZEPHYR3_STATIC

#ifdef ZEPHYRNET_EXPORTS
#	define ZEPHYR_NET_API	__declspec(dllexport)
#else // ZGRAPH_3_EXPORTS
#	define ZEPHYR_NET_API	__declspec(dllimport)
/*
#if _ZEPHYR_NET_VER == 2100
#	if defined(_DEBUG)
#		ifdef _ZEPHYR_NET_SERVER__
#			pragma comment(lib, "ZephyrNet21D.lib")
#		else // not _ZEPHYR_NET_SERVER__
#			pragma comment(lib, "ZephyrNet21DC.lib")
#		endif // _ZEPHYR_NET_SERVER__
#	elif defined(NDEBUG)
#		ifdef _ZEPHYR_NET_SERVER__
#			pragma comment(lib, "ZephyrNet21.lib")
#		else // not _ZEPHYR_NET_SERVER__
#			pragma comment(lib, "ZephyrNet21C.lib")
#		endif // _ZEPHYR_NET_SERVER__
#	endif // 
#else _ZEPHYR_NET_VER == 2200
#	if defined(_DEBUG)
#		ifdef _ZEPHYR_NET_SERVER__
#			pragma comment(lib, "ZephyrNet22D.lib")
#		else // not _ZEPHYR_NET_SERVER__
#			pragma comment(lib, "ZephyrNet22DC.lib")
#		endif // _ZEPHYR_NET_SERVER__
#	elif defined(NDEBUG)
#		ifdef _ZEPHYR_NET_SERVER__
#			pragma comment(lib, "ZephyrNet22.lib")
#		else // not _ZEPHYR_NET_SERVER__
#			pragma comment(lib, "ZephyrNet22C.lib")
#		endif // _ZEPHYR_NET_SERVER__
#	endif // 
#endif
*/
#endif // ZEPHYRNET_EXPORTS
#endif//__ZEPHYR3_STATIC

#endif

////////////////////////////////////////////////////////////////////////////////
// ZNet2
namespace ZNet2{

	const int	MAX_PKG_SIZE	=	1440;

	// ¿Õ½á¹¹
	struct null_type{};
};

#endif//_ZEPHYR_NET_2_BASEDEF_H