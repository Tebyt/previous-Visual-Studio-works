/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	ZDebug.h

							Describe:	调试输出

							Author:		赵洪松(xueren)

							CreateTime: 2002
							UpdateTime: 2003.08.20
*/

#ifndef _ZEPHYR_DEBUG_H
#define _ZEPHYR_DEBUG_H

#include <Zephyr.h>

#ifndef _DEBUG
#define DEBUGMESSAGE(msg)	((void)0)
#define DEBUGMESSAGE2(msg,param)	((void)0)
#define DEBUGMESSAGE3(msg,param1,param2)	((void)0)
#define DEBUGMESSAGE4(msg,param1,param2,param3)	((void)0)
#define DEBUGMESSAGE5(msg,param1,param2,param3,param4)	((void)0)
#define DEBUGMESSAGE7(msg,param1,param2,param3,param4,param5,param6)	((void)0)
#else
#define DEBUGMESSAGE(msg)	OutputLog(msg)
#define DEBUGMESSAGE2(msg,param)	OutputLog(msg,param)
#define DEBUGMESSAGE3(msg,param1,param2)	OutputLog(msg,param1,param2)
#define DEBUGMESSAGE4(msg,param1,param2,param3)	OutputLog(msg,param1,param2,param3)
#define DEBUGMESSAGE5(msg,param1,param2,param3,param4)	OutputLog(msg,param1,param2,param3,param4)
#define DEBUGMESSAGE7(msg,param1,param2,param3,param4,param5,param6)	OutputLog(msg,param1,param2,param3,param4,param5,param6)
#endif

#include <windows.h>
#include <stdio.h>
//#include <ddraw.h>
//#include <dsound.h>
//#include <d3d.h>

#ifndef ZEPHYR_USE_WS20
#include <winsock.h>
#else
#include <winsock2.h>
#endif

// 定义 _ZEPHYR_MUL_DEBUG 就是多程序分别调试输出 Debug???.log
// 不定义就是输出到一个文件 Debug.log
//#define _ZEPHYR_MUL_DEBUG

// 定义 _ZEPHYR_GDI_DEBUG 就是GDI输出，弹出一个MessageBox
//#define _ZEPHYR_GDI_DEBUG

#define	DEBUGFILENAME	"debug.log"

// 检查文件是否存在
bool ZEPHYR_API HasFile(const char *name);
// 格式化字符串
void ZEPHYR_API _format_str(char *buf,char *text,...);
// 限定字符串长度
inline void debugString(char *str,unsigned int len) { str[len-1] = '\0'; }

// 强制输出Log
void ZEPHYR_API OutputLog(char *text,...);
// Debug输出
void ZEPHYR_API Debug(char *text,...);

// DirectX返回值处理
HRESULT	ZEPHYR_API DXRet(HRESULT hret,char *text,...);
// Zephyr返回值处理
HRESULT	ZEPHYR_API ZRet(HRESULT hret,char *text,...);
// WinSock返回值处理
HRESULT ZEPHYR_API WSARet(HRESULT hret,char *text,...);

const HRESULT	ZEPHYR_RET_INVALIDPOINT			=	0x01;
const HRESULT	ZEPHYR_RET_INVALIDPARAM			=	0x02;
const HRESULT	ZEPHYR_RET_OUTOFMEMORY			=	0x03;
const HRESULT	ZEPHYR_RET_OUTOFVMEMORY			=	0x04;
const HRESULT	ZEPHYR_RET_FILEREADERROR		=	0x05;
const HRESULT	ZEPHYR_RET_FILEWRITEERROR		=	0x06;
const HRESULT	ZEPHYR_RET_FILEOPENERROR		=	0x07;
const HRESULT	ZEPHYR_RET_FILEERROR			=	0x08;
const HRESULT	ZEPHYR_RET_LOADJPEGERROR		=	0x09;
const HRESULT	ZEPHYR_RET_SOCKETERROR			=	0x0a;

const HRESULT	ZEPHYR_RET_USER					=	0x10000;

const HRESULT	ZEPHYR_RET_FAILED				=	-1;

#include <ZAssert.h>

#endif//_ZEPHYR_DEBUG_H