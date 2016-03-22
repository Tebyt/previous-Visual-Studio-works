/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Graph2\Rect.h

							Describe:	Rect

							Author:		赵洪松(xueren)

							CreateTime: 2004.04.28
							UpdateTime:
*/

#ifndef _ZEPHYR_3_GRAPH_2_RECT_H
#define _ZEPHYR_3_GRAPH_2_RECT_H

#include <Base\List.h>
#include <Base\HashTable.h>

namespace ZGraph2{

	// 点是否在RECT内
	inline bool IsIn(RECT& rect,int x,int y)
	{
		return x >= rect.left && x < rect.right && y >= rect.top && y < rect.bottom;
	}

	// 源矩形是否在目标矩形内
	inline bool IsIn(RECT& dst,RECT& src)
	{
		return (src.left < dst.right || src.right > dst.left) && (src.bottom > dst.top || src.top < dst.bottom);
	}

	/////////////////////////////////////////////////////////////////////////////////////
	// AreaData

	struct AreaData{
		RECT rect;
	};

	/////////////////////////////////////////////////////////////////////////////////////
	// Area

	template<typename T>
	class Area{
	public:
		typedef Zephyr3::Link<T,32,64>	List;
	public:

	private:
		List	m_list;
	};
}

#endif // _ZEPHYR_3_GRAPH_2_RECT_H