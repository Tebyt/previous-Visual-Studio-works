/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2004


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Physics\Object.h

							Describe:	物体

							Author:		赵洪松(xueren)

							CreateTime: 2004.09.25
							UpdateTime:
*/

#ifndef _ZEPHYR_3_PHYSICS_OBJECT_H
#define _ZEPHYR_3_PHYSICS_OBJECT_H

#include <Physics\BaseDef.h>
#include <Physics\Speed.h>
#include <Physics\Location.h>

namespace ZPhysics{

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// 物体

	class ZEPHYR_3_PHYSICS_API Object{
	public:
		Object() {}

		Object(const Location& location,const Speed& speed,const Acceleration& acc) 
			: m_location(location)
			, m_acc(acc)
			, m_speed(speed)
		{
		}

		void Action(DWORD refurbishTime);
	public:
		Location		m_location;
		Acceleration	m_acc;
		Speed			m_speed;
	};

	typedef Object*	LPObject;
};

#endif // _ZEPHYR_3_PHYSICS_OBJECT_H