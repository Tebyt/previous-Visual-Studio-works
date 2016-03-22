#ifndef ZEPHYR_GRAPH_GDI_H
#define ZEPHYR_GRAPH_GDI_H

#include <Graph\ZGraph.h>

#ifndef __ZEPHYR3_USE_ZEPHYRGRAPH__

class ZEPHYR_API ZGraphGDI : public ZGraph{
private:
	ZEPHYR_COLOR_MODE		gdi_zcm;

public:
	inline ZGraphGDI()	{ ; }
	virtual ~ZGraphGDI() { Release(); }

	//Release
	virtual void Release();
	//Init
	virtual HRESULT Init(bool bWindow,DWORD W,DWORD H,ZEPHYR_COLOR_MODE zcm,bool bUsevm = true);

	virtual ZFont *CreateSmoothFont(HFONT hFont);
	virtual ZFont *CreateFont(HFONT hFont);

	virtual void ReSizeBackScreen(long w,long h,ZEPHYR_COLOR_MODE zcm,bool bUsevm = true);
protected:
	// 创建 spr 管理器
	virtual HRESULT CreateSpriteManager();
//render
	virtual void _beginrender();
	virtual void _endrender();
	virtual HRESULT _render(LPSPRITE_DATA backscreen,RECT &screen,RECT &viewport);

//sprite
	virtual LPSPRITE_DATA _createsprite(long w,long h,ZEPHYR_COLOR_MODE zcm,DWORD flag);
	virtual void _releasesprite(LPSPRITE_DATA &lps);

	virtual HRESULT _clearsprite_alpha(LPSPRITE_DATA lps, long x, long y, long r, long b, DWORD color, BYTE alpha);
	virtual HRESULT _clearsprite(LPSPRITE_DATA lps,long x,long y,long r,long b,DWORD color);
	virtual HRESULT _bltsprite(LPSPRITE_DATA dst,long x,long y,LPSPRITE_DATA src,long x0,long y0,long x1,long y1);
	virtual HRESULT _bltsprite_ck(LPSPRITE_DATA dst,long x,long y,LPSPRITE_DATA src,long x0,long y0,long x1,long y1);
	virtual HRESULT _bltsprite_zoom(LPSPRITE_DATA dst,long x,long y,long w,long h,LPSPRITE_DATA src,long x0,long y0,long w0,long h0);
	virtual HRESULT _bltsprite_zoom_alpha(LPSPRITE_DATA dst,long x,long y,long w,long h,LPSPRITE_DATA src,long x0,long y0,long w0,long h0,BYTE alpha);
	virtual HRESULT _bltsprite_alpha(LPSPRITE_DATA dst,long x,long y,LPSPRITE_DATA src,long x0,long y0,long x1,long y1,BYTE alpha);
	virtual HRESULT _bltsprite_alpha_ck(LPSPRITE_DATA dst,long x,long y,LPSPRITE_DATA src,long x0,long y0,long x1,long y1,BYTE alpha);
	virtual HRESULT _bltsprite_alpha(LPSPRITE_DATA dst,long x,long y,LPSPRITE_DATA src,long x0,long y0,long x1,long y1,LPSPRITE_DATA alpha,long x2,long y2);
	virtual HRESULT _bltsprite_alpha(LPSPRITE_DATA dst,long x,long y,DWORD color,long x0,long y0,long x1,long y1,LPSPRITE_DATA alpha,long x2,long y2);
	virtual HRESULT _bltsprite_additive(LPSPRITE_DATA dst,long x,long y,LPSPRITE_DATA src,long x0,long y0,long x1,long y1,BYTE alpha);

	virtual HRESULT _locksprite(LPSPRITE_DATA lps,void **pvoid,DWORD &pitch,long &w,long &h);
	virtual HRESULT _unlocksprite(LPSPRITE_DATA lps);
	virtual HRESULT _locksprite_r(LPSPRITE_DATA lps,RECT *rect,void **pvoid,DWORD &pitch,long &w,long &h);

	virtual void _setcolorkey(void *lps);

//	virtual void _drawchar(LPSPRITE_DATA lps,long x,long y,DWORD color,LPZFONT_DATA dat);

//图形函数
	virtual void _line(LPSPRITE_DATA lps,long x1,long y1,long x2,long y2,DWORD color);

//other
	virtual void _printanything();

	virtual LPSPRITE_DATA Clone(LPSPRITE_DATA pSrc);

private:

	HRESULT _get_screen_colormode_gdi(ZEPHYR_COLOR_MODE &zcm);

	LPSPRITE_DATA _createbackscreen_gdi(long w,long h,ZEPHYR_COLOR_MODE zcm,bool usevm);

	HRESULT _getdsinfo_gdi(void* ds);
};
#endif // __ZEPHYR3_USE_ZEPHYRGRAPH__

#endif