/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2004


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Physics\ObjMgr.h

							Describe:	物体管理

							Author:		赵洪松(xueren)

							CreateTime: 2004.09.25
							UpdateTime:
*/

#ifndef _ZEPHYR_3_PHYSICS_OBJMGR_H
#define _ZEPHYR_3_PHYSICS_OBJMGR_H

#include <Base\Timer.h>
#include <Base\List.h>
#include <Base\Lock.h>

#include <Physics\Object.h>

namespace ZPhysics{


	/////////////////////////////////////////////////////////////////////////////////////
	// 物体管理

	class ZEPHYR_3_PHYSICS_API ObjMgr : public Zephyr3::Timer{
	public:
		typedef Zephyr3::Link<LPObject,128,64>	_List;
		typedef Zephyr3::LockImp	_Lock;
	public:
		ObjMgr() {}
		virtual ~ObjMgr() { Release(); }

		HRESULT Init(DWORD refurbishTime);

		void Add(LPObject pObj);

		void Del(LPObject pObj);

		void Release();
	private:
		// 线程主函数
		virtual HRESULT TimerFunc(LPVOID param);
	public:
		_List		m_list;
		_Lock		m_lock;
	};
};

#endif // _ZEPHYR_3_PHYSICS_OBJMGR_H