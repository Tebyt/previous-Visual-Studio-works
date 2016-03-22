#ifndef ZEPHYR_SPRITEDATA_H
#define ZEPHYR_SPRITEDATA_H

#include <ZDebug.h>
#include <Graph\BaseDef.h>

#ifdef __ZEPHYR3_USE_ZEPHYRGRAPH__

typedef struct SPRITE_DATA{
	DWORD	dwFlag;				//flag
	long	dwWidth,dwHeight;	//width、height
//	long	_w,_h;				//实际大小，主要用于d3d渲染
//	DWORD	dwPitch;			//pitch
	DWORD	dwTimes;			//use times
	DWORD	dwDrawTimes;		// Draw Times
	ZEPHYR_COLOR_MODE	zcm;	//color mode
	void*	pDat;
}SPRITESTRUCT;

#else // __ZEPHYR3_USE_ZEPHYRGRAPH__

typedef struct SPRITE_DATA{
	DWORD	dwFlag;				//flag
	long	dwWidth,dwHeight;	//width、height
	long	_w,_h;				//实际大小，主要用于d3d渲染
	DWORD	dwPitch;			//pitch
	DWORD	dwTimes;			//use times
	DWORD	dwDrawTimes;		// Draw Times
	ZEPHYR_COLOR_MODE	zcm;	//color mode
	void	*lpds;				//lpds,maybe
	void	*lpdd;				//lpd3ddevice,maybe
	void	*Date[1];			//数据
}SPRITESTRUCT;

#endif // __ZEPHYR3_USE_ZEPHYRGRAPH__

inline void __SpriteDraw(SPRITE_DATA& spr)
{
//	spr.dwFlag |= ZEPHYRSPRITE_DRAWLIST;
	++spr.dwDrawTimes;

//	Debug("__SpriteDraw 0x%x %d", &spr, spr.dwDrawTimes);
}

inline DWORD __SpriteUnDraw(SPRITE_DATA& spr)
{
	return 1;

#ifdef _DEBUG

	if(spr.dwDrawTimes == 0)
		Debug("__SpriteUnDraw fail!!!");

#endif // _DEBUG
/*
	if(spr.dwDrawTimes == 1)
		spr.dwFlag &= ~ZEPHYRSPRITE_DRAWLIST;
*/
//	Debug("__SpriteUnDraw 0x%x %d", &spr, spr.dwDrawTimes);

	return --spr.dwDrawTimes;
}

inline void __SpriteRelease(SPRITE_DATA& spr)
{
//	spr.dwFlag |= ZEPHYRSPRITE_RELEASE;
}

inline bool __IsSpriteDraw(SPRITE_DATA& spr)
{
	return false;
//	return (spr.dwFlag & ZEPHYRSPRITE_DRAWLIST) && spr.dwDrawTimes != 0;
//	return spr.dwDrawTimes > 0;
}

inline bool __IsSpriteRelease(SPRITE_DATA& spr)
{
	return false;
//	return spr.dwFlag & ZEPHYRSPRITE_RELEASE;
}

#endif