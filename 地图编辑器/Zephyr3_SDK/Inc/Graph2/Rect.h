/*
							Zephyr Engine v3.0

								by �Ժ���(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Graph2\Rect.h

							Describe:	Rect

							Author:		�Ժ���(xueren)

							CreateTime: 2004.04.28
							UpdateTime:
*/

#ifndef _ZEPHYR_3_GRAPH_2_RECT_H
#define _ZEPHYR_3_GRAPH_2_RECT_H

#include <Base\List.h>
#include <Base\HashTable.h>

namespace ZGraph2{

	// ���Ƿ���RECT��
	inline bool IsIn(RECT& rect,int x,int y)
	{
		return x >= rect.left && x < rect.right && y >= rect.top && y < rect.bottom;
	}

	// Դ�����Ƿ���Ŀ�������
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