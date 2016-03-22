/*
							Zephyr Engine v3.0

								by ’‘∫ÈÀ…(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	ZAlloc.h

							Describe:	ƒ⁄¥Ê∑÷≈‰

							Author:		’‘∫ÈÀ…(xueren)

							CreateTime: 2004.03.05
							UpdateTime:
*/

#ifndef _ZEPHYR_3_ALLOC_H
#define _ZEPHYR_3_ALLOC_H

#include <Zephyr.h>

namespace Zephyr3{

	/////////////////////////////////////////////////////////////////////////////////////////
	// ZAlloc


	/////////////////////////////////////////////////////////////////////////////////////////
	// ZAlloc_Pool

	template<class T,unsigned int SIZE,unsigned int ADD_SIZE>
	class ZAlloc_Pool<T,SIZE,ADD_SIZE> {
	};
};

#endif//_ZEPHYR_3_ALLOC_H