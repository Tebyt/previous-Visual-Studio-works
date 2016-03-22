/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2004


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Physics\ObjMgr.cpp

							Describe:	物体管理

							Author:		赵洪松(xueren)

							CreateTime: 2004.09.25
							UpdateTime:
*/

#include "stdafx.h"

#include <Physics\ObjMgr.h>

namespace ZPhysics{


	/////////////////////////////////////////////////////////////////////////////////////
	// 物体管理

	HRESULT ObjMgr::Init(DWORD refurbishTime)
	{
		if(SetTimer(refurbishTime,NULL) != S_OK)
			return Zephyr3::Ret(E_FAIL, "ZPhysics::Init(%d) fail!",refurbishTime);

		return S_OK;
	}

	void ObjMgr::Add(LPObject pObj)
	{
		Zephyr3::AutoLockEx lock(&m_lock);

		m_list.Add(pObj);
	}

	void ObjMgr::Del(LPObject pObj)
	{
		Zephyr3::AutoLockEx lock(&m_lock);

		m_list.Del(pObj);
	}

	// 线程主函数
	HRESULT ObjMgr::TimerFunc(LPVOID param)
	{
		Zephyr3::AutoLockEx lock(&m_lock);

		_List::LPNode pNode = NULL;
		LPObject* ppObj = NULL;

		do{
			m_list.GetData(ppObj,pNode);
			if(ppObj != NULL && *ppObj != NULL)
				(*ppObj)->Action(m_dwTimer);

		}while(pNode != NULL);

		return S_OK;
	}

	void ObjMgr::Release()
	{
		WaitForExitThread();

		Zephyr3::AutoLockEx lock(&m_lock);

		m_list.Clear();
	}
};