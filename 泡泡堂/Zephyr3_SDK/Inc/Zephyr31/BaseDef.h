/*
							Zephyr v3.1

							by ’‘∫ÈÀ…(xueren) 2005

							E-mail:sssxueren@21cn.com

							FileName:	Zephyr31\BaseDef.h

							Describe:	Zephyr v3.1 ª˘¥°∂®“Â

							Author:		’‘∫ÈÀ…(xueren)

							CreateTime: 2005.08.01
							UpdateTime: 
*/
#ifndef __ZEPHYR_31_BASEDEF_H__

#ifdef ZEPHYR_31_EXPORTS
#	define ZEPHYR_31_API	__declspec(dllexport)
#else // ZEPHYR_31_EXPORTS
#	define ZEPHYR_31_API	__declspec(dllimport)

#	if defined(_DEBUG)
#		pragma comment(lib, "Zephyr31D.lib")
#	elif defined(NDEBUG)
#		pragma comment(lib, "Zephyr31.lib")
#	endif // 
#endif // ZEPHYR_31_EXPORTS

#endif // __ZEPHYR_31_BASEDEF_H__