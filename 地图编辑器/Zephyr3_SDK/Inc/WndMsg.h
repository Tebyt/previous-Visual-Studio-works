/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	WndMsg.h

							Describe:	窗口消息定义

							Author:		赵洪松(xueren)

							CreateTime: 2002.7
							UpdateTime: 2003.08.20
*/

#ifndef _ZEPHYR_WNDMSG_H
#define _ZEPHYR_WNDMSG_H

#include <Zephyr.h>

//windows message
#define WM_ZEPHYR_USER_BEGIN	WM_USER

#define WM_ZEPHYR_FOCUS			WM_ZEPHYR_USER_BEGIN+1
#define WM_ZEPHYR_KILLFOCUS		WM_ZEPHYR_USER_BEGIN+2
#define WM_ZEPHYR_MOUSELEAVE	WM_ZEPHYR_USER_BEGIN+3
#define WM_ZEPHYR_MOUSEHOVER	WM_ZEPHYR_USER_BEGIN+4
//user client module used
#define WM_ZEPHYR_ADDUSER		WM_ZEPHYR_USER_BEGIN+5
#define WM_ZEPHYR_DELUSER		WM_ZEPHYR_USER_BEGIN+6
//char client module used
#define WM_ZEPHYR_ADDCHAT		WM_ZEPHYR_USER_BEGIN+7


//load finish
#define WM_ZEPHYR_LOAD_FINISH	WM_ZEPHYR_USER_BEGIN+9
//load a file end
#define WM_ZEPHYR_LOAD_WORKEND	WM_ZEPHYR_USER_BEGIN+10
//must load file finished
#define WM_ZEPHYR_LOAD_CANRUN	WM_ZEPHYR_USER_BEGIN+11
//loading
#define WM_ZEPHYR_LOAD_LOADING	WM_ZEPHYR_USER_BEGIN+12
//zephyr timer
#define WM_ZEPHYR_TIMER			WM_ZEPHYR_USER_BEGIN+13
//connect
#define WM_ZEPHYR_CONNECT		WM_ZEPHYR_USER_BEGIN+14

#define WM_ZEPHYR_USER			WM_ZEPHYR_USER_BEGIN+15

#endif//_ZEPHYR_WNDMSG_H