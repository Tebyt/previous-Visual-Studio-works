// Hexagon.h
// 六边形数组 头文件
// write by ssscomic			y2k5.7.26

//! zhs007 @ 2005.08.09
//!		修正因为 ZASSERT 调整引起的编译错误

#ifndef _ZEPHYR_3_HEXAGON_H
#define _ZEPHYR_3_HEXAGON_H

namespace Zephyr3{

	//////////////////////////////////////////////////////////////////////
	//	Hexagon

	/*

	  *   *   *
	*   *   *
	  *   *   *
	*   *   *
	  *   *   *
	*   *   *

	*/

	const int	_HEXAGON_T		=	0;		//上
	const int	_HEXAGON_RT		=	1;		//右上
	const int	_HEXAGON_RB		=	2;		//右下
	const int	_HEXAGON_B		=	3;		//下
	const int	_HEXAGON_LB		=	4;		//左下
	const int	_HEXAGON_LT		=	5;		//左上

	const int	_HEXAGON_BX[]	=	{0, 1, 1, 0, -1, -1};
	const int	_HEXAGON_BY[]	=	{-2, -1, 1, 2, 1, -1};

	template<class T, unsigned int w, unsigned int h>
	class Hexagon{
	private:
		T	m_Data[h][w];
	public:
		//Hexagon[i][j]
		T& GetData(int i, int j)
		{
			ZASSERT(i >= 0 && j >= 0);
			ZASSERT(j < w);
			ZASSERT(i < h * 2);

			//EVEN
			if(j % 2 == 0)
			{
				ZASSERT(i % 2 != 0);
			}
			else
			{
				ZASSERT(i % 2 == 0);
			}

			return m_Data[i / 2][j];
		}

		bool HasData(int i, int j)
		{
			if(i < 0 || i >= h * 2 || j < 0 || j >= w)
				return false;

			if(j % 2 == 0)
			{
				if(i % 2 == 0)
					return false;
			}
			else
			{
				if(i % 2 != 0)
					return false;
			}

			return true;
		}

		void Clear()
		{
			memset(m_Data, 0, sizeof(T) * h * w);
		}
	};
};

#endif //_ZEPHYR_3_HEXAGON_H