/*
							Zephyr Engine v3.0

								by ’‘∫ÈÀ…(xueren) 2002 - 2004


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Physics\Location.h

							Describe:	Œª÷√

							Author:		’‘∫ÈÀ…(xueren)

							CreateTime: 2004.09.25
							UpdateTime:
*/

#ifndef _ZEPHYR_3_PHYSICS_LOCATION_H
#define _ZEPHYR_3_PHYSICS_LOCATION_H

#include <Physics\BaseDef.h>

namespace ZPhysics{

	//////////////////////////////////////////////////////////////////////////
	// Œª÷√

	class Location{
	public:
		Location() {
			m_x = 0.0f;
			m_y = 0.0f;
		}

		Location(float x,float y) {
			m_x = x;
			m_y = y;
		}

		Location(const Location& location) {
			m_x = location.m_x;
			m_y = location.m_y;
		}
	public:
		float	m_x;
		float	m_y;
	};
};

#endif // _ZEPHYR_3_PHYSICS_LOCATION_H