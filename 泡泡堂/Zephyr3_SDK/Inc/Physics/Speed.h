/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2004


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Physics\Speed.h

							Describe:	速度

							Author:		赵洪松(xueren)

							CreateTime: 2004.09.25
							UpdateTime:
*/

#ifndef _ZEPHYR_3_PHYSICS_SPEED_H
#define _ZEPHYR_3_PHYSICS_SPEED_H

#include <Physics\BaseDef.h>

namespace ZPhysics{

	//////////////////////////////////////////////////////////////////////////
	// 速度

	class Speed{
	public:
		Speed() {
			m_xSpeed = 0.0f;
			m_ySpeed = 0.0f;
		}

		Speed(float xSpeed,float ySpeed) {
			m_xSpeed = xSpeed;
			m_ySpeed = ySpeed;
		}

		Speed(const Speed& speed) {
			m_xSpeed = speed.m_xSpeed;
			m_ySpeed = speed.m_ySpeed;
		}
	public:
		float	m_xSpeed;
		float	m_ySpeed;
	};


	//////////////////////////////////////////////////////////////////////////
	// 加速度

	class Acceleration{
	public:
		Acceleration() {
			m_xAcceleration = 0.0f;
			m_yAcceleration = 0.0f;
		}

		Acceleration(float xAcceleration,float yAcceleration) {
			m_xAcceleration = xAcceleration;
			m_yAcceleration = yAcceleration;
		}

		Acceleration(const Acceleration& acceleration) {
			m_xAcceleration = acceleration.m_xAcceleration;
			m_yAcceleration = acceleration.m_yAcceleration;
		}
	public:
		float	m_xAcceleration;
		float	m_yAcceleration;
	};
};

#endif // _ZEPHYR_3_PHYSICS_SPEED_H