#ifndef ZEPHYR_GRAPH_BASEDEF_H
#define ZEPHYR_GRAPH_BASEDEF_H

#ifdef __ZEPHYR3_USE_ZEPHYRGRAPH__
#include <ZephyrGraph/Core/ZephyrGraph.h>
#endif // __ZEPHYR3_USE_ZEPHYRGRAPH__

#include <Zephyr.h>

#include <windows.h>

#ifndef ZEPHYR_COUNT_FPS
#define ZEPHYR_COUNT_FPS
#endif

#ifndef __ZEPHYR3_USE_ZEPHYRGRAPH__

//颜色
enum ZEPHYR_COLOR_MODE{
	ZCM_NODEFINE	= 0,

	ZCM_R8G8B8		= 0x1,	//24bit

	ZCM_A8R8G8B8	= 0x2,	//32bit
	ZCM_X8R8G8B8	= 0x3,

	ZCM_R5G6B5		= 0x4,	//16bit 565
	ZCM_X1R5G5B5	= 0x5,	//16bit 555
	ZCM_A1R5G5B5	= 0x6,
	ZCM_A4R4G4B4	= 0x7,

	ZCM_P8			= 0x8,	//8bit
	ZCM_GRAY		= 0x9	//灰度
};

#else // __ZEPHYR3_USE_ZEPHYRGRAPH__

typedef ZGLColorMode	ZEPHYR_COLOR_MODE;

#endif // __ZEPHYR3_USE_ZEPHYRGRAPH__

inline unsigned ColorBits(ZEPHYR_COLOR_MODE zcm)
{
	return zcm&0x8?8:(zcm&0x4?16:(zcm&0x2?32:24));
}

//typedef const char * LPCSTR;

LPCSTR ZEPHYR_API GetColorBitsString(ZEPHYR_COLOR_MODE zcm);

//color
inline WORD _color16b_555(int r,int g,int b)
{
	return (WORD)(((WORD)(r<<7)&0x7c00)|((WORD)(g<<2)&0x03e0)|((WORD)(b>>3)&0x001f));
}

inline WORD _color16b_565(int r,int g,int b)
{
	return (WORD)(((WORD)(r<<8)&0xf800)|((WORD)(g<<3)&0x07e0)|((WORD)(b>>3)&0x001f));
}

inline unsigned long _color24b_555(WORD c)
{
	return (unsigned long)((((unsigned long)(c<<9)&0xf80000)|(((unsigned long)(c<<6)&0xf800)|((unsigned long)(c<<3)&0xf8))));
}

inline unsigned long _color24b_565(WORD c)
{
	return (unsigned long)((((unsigned long)(c<<8)&0xf80000)|(((unsigned long)(c<<5)&0xfc00)|((unsigned long)(c<<3)&0xf8))));
}

inline WORD c555to565(WORD c555)
{
	return (WORD)((WORD)((c555&0x7fe0)<<1)|(c555&0x001f));
}

inline WORD c565to555(WORD c565)
{
	return (WORD)((WORD)((c565&0xffc0)>>1)|(c565&0x001f));
}

inline DWORD rgb_555(BYTE r,BYTE g,BYTE b)
{
	return (DWORD)((((WORD)(r<<7))&0x7c00)|(((WORD)(g<<2))&0x3e0)|(((WORD)(b>>3))&0x1f));
}

inline DWORD rgb_565(BYTE r,BYTE g,BYTE b)
{
	return (DWORD)((((WORD)(r<<8))&0xf100)|(((WORD)(g<<3))&0x7e0)|(((WORD)(b>>3))&0x1f));
}

inline DWORD rgb_888(BYTE r,BYTE g,BYTE b)
{
	return (DWORD)((((DWORD)(r<<16))&0xff0000)|(((DWORD)(g<<8))&0xff00)|(((DWORD)b)&0xff));
}

extern ZEPHYR_API WORD		(*color16b)(int r,int g,int b);
extern ZEPHYR_API DWORD		(*color24b)(WORD c);
extern ZEPHYR_API DWORD		(*rgb)(BYTE r,BYTE g,BYTE b);

void ZEPHYR_API RegisterColorFunc(bool bIs555);
void ZEPHYR_API RegisterColorFunc(ZEPHYR_COLOR_MODE zcm);

struct SPRITE_DATA;

typedef SPRITE_DATA*	LPSPRITE_DATA;

//ds sprite
#define ZEPHYRSPRITE_VMDS			0		//video mem ds
#define ZEPHYRSPRITE_SMDS			1		//system mem ds

//sprite flag
#define ZEPHYRSPRITE_VMEM			0x1		//video memory
#define ZEPHYRSPRITE_RLECOLORKEY	0x2		//rle colorkey
#define ZEPHYRSPRITE_3DDEVICE7		0x4		//3d device
#define ZEPHYRSPRITE_TEXTURE7		0x8		//texture
#define ZEPHYRSPRITE_COLORKEY		0x10	//colorkey
#define ZEPHYRSPRITE_ALPHA			0x20	//simple alpha 4bits
#define ZEPHYRSPRITE_COMPLEXCOLOR	0x40	//complex color 32bits

#ifdef __ZEPHYR3_USE_ZEPHYRGRAPH__
#define ZEPHYRSPRITE_BACKSCREEN		0x100	//! backscreen
#endif // __ZEPHYR3_USE_ZEPHYRGRAPH__

#define ZEPHYRSPRITE_DRAWLIST		0x1000	// in draw list
#define ZEPHYRSPRITE_RELEASE		0x2000	// release

#define ZEPHYRSPRITE_FILE_BMP		0x80000000
#define ZEPHYRSPRITE_FILE_JPG		0x40000000
#define ZEPHYRSPRITE_FILE_ZPC		0x20000000

//渲染模式
enum ZEPHYR_RENDER_MODE{
	ZRM_GDI=1,
	ZRM_DD7,
	ZRM_D3D7
};

void ZEPHYR_API RegisterRenderEngineFunc(ZEPHYR_RENDER_MODE zrm);

//rect
inline bool IsInRect(long x,long y,const RECT &rect)
{
	return ((x>=rect.left&&x<rect.right)&&(y>=rect.top&&y<rect.bottom));
}

//ZAlpha
struct ZAlpha{
	DWORD w,h;
	DWORD dwPitch;
	BYTE *date[1];
};

//class
class ZGraph;
class ZRenderEngine;
class ZSprite;

typedef ZSprite*	LPZSprite;

//#define _ZEPHYR_LOADJPG_JPEG_LIB
#ifdef _ZEPHYR_LOADJPG_JPEG_LIB
	int init_jpeg(bool is555,bool isMMX);
#endif 

//#define _ZEPHYR_LOADJPG_IJL
//#define _ZEPHYR_LOADJPG_IJL_DLL

//#define _ZEPHYR_LOADJPG_IPICTURE

#endif