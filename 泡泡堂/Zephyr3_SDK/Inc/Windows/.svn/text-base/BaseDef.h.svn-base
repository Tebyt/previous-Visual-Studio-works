/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2005


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Windows\BaseDef.h

							Describe:	UI基本定义

							Author:		赵洪松(xueren)

							CreateTime: 2005.01.06
							UpdateTime:
*/

#ifndef _ZEPHYR_WINDOWS_BASEDEF_H
#define _ZEPHYR_WINDOWS_BASEDEF_H

#include <Zephyr.h>

#include <Windows/WndCtl.h>
#include <Windows/WndBack.h>
#include <Windows/BtnEx.h>

namespace Zephyr3{

	HRESULT ZEPHYR_API LoadButton(ZWndButton& wndBtn, const char* filename, ZGraph* pGraph, DWORD flag, bool bColorKey, const char* btnName, DWORD wndStyle, const RECT& rect, HWND parentWnd, ZephyrWnd& zWnd, DWORD btnID, DWORD msgID);

	HRESULT ZEPHYR_API LoadButtonEx(ZWndBtnEx& wndBtn, const char* filename1, const char* filename2, ZGraph* pGraph, DWORD flag, bool bColorKey, const char* btnName, DWORD wndStyle, const RECT& rect, HWND parentWnd, ZephyrWnd& zWnd, DWORD btnID, DWORD msgID);

	void ZEPHYR_API DestroyChildWindow(HWND hWnd);
};

#endif // _ZEPHYR_WINDOWS_BASEDEF_H