#ifndef ZEPHYR_GRAPH_DDRAW7_H
#define ZEPHYR_GRAPH_DDRAW7_H

#include <Graph\ZGraph.h>

class ZEPHYR_API ZGraphD7 : public ZGraph{
private:
	LPDIRECTDRAW7			lpdd7;
	LPDIRECTDRAWSURFACE7	lpdds7Primary;
	DDSURFACEDESC2			ddsd7;
	DDPIXELFORMAT			ddpf;
	ZEPHYR_COLOR_MODE		dd7_zcm;

public:
	inline ZGraphD7() { ; }
	virtual ~ZGraphD7() { Release(); }

	virtual void Release();

	virtual HRESULT Init(bool bWindow,DWORD W,DWORD H,ZEPHYR_COLOR_MODE zcm,bool bUsevm=true);
protected:
//render
	virtual void _beginrender();
	virtual void _endrender();
	virtual HRESULT _render(LPSPRITE_DATA backscreen,RECT &screen,RECT &viewport);

//sprite
	virtual LPSPRITE_DATA _createsprite(long w,long h,ZEPHYR_COLOR_MODE zcm,DWORD flag);
	virtual void _releasesprite(LPSPRITE_DATA &lps);

	virtual HRESULT _clearsprite(LPSPRITE_DATA lps,long x,long y,long r,long b,DWORD color);
	virtual HRESULT _bltsprite(LPSPRITE_DATA dst,long x,long y,LPSPRITE_DATA src,long x0,long y0,long x1,long y1);
	virtual HRESULT _bltsprite_ck(LPSPRITE_DATA dst,long x,long y,LPSPRITE_DATA src,long x0,long y0,long x1,long y1);
	virtual HRESULT _bltsprite_zoom(LPSPRITE_DATA dst,long x,long y,long w,long h,LPSPRITE_DATA src,long x0,long y0,long w0,long h0);
	virtual HRESULT _bltsprite_alpha(LPSPRITE_DATA dst,long x,long y,LPSPRITE_DATA src,long x0,long y0,long x1,long y1,BYTE alpha);
	virtual HRESULT _bltsprite_additive(LPSPRITE_DATA dst,long x,long y,LPSPRITE_DATA src,long x0,long y0,long x1,long y1,BYTE alpha);

	virtual HRESULT _locksprite(LPSPRITE_DATA lps,void **pvoid,DWORD &pitch,long &w,long &h);
	virtual HRESULT _unlocksprite(LPSPRITE_DATA lps);
	virtual HRESULT _locksprite_r(LPSPRITE_DATA lps,RECT *rect,void **pvoid,DWORD &pitch,long &w,long &h);

	virtual void _setcolorkey(void *lps);

//	virtual void _drawchar(LPSPRITE_DATA lps,long x,long y,DWORD color,LPZFONT_DATA dat);

//Í¼ÐÎº¯Êý
	virtual void _line(LPSPRITE_DATA lps,long x1,long y1,long x2,long y2,DWORD color);

//other
	virtual void _printanything();

private:
//ds
	HRESULT _lockds(void* surface,void **pvoid,DWORD &pitch,long &w,long &h);
	HRESULT _lockds_r(void* surface,RECT *rect,void **pvoid,DWORD &pitch,long &w,long &h);
	HRESULT _unlockds(void* surface);
	void _setcolorkey_ds(void *lpds);

	HRESULT _get_screen_colormode_dd7(ZEPHYR_COLOR_MODE &zcm);

	LPSPRITE_DATA _createbackscreen_dd7(long w,long h,ZEPHYR_COLOR_MODE zcm,bool usevm);

	HRESULT _getdsinfo_ds7(void* ds7,DWORD &pitch,long &w,long &h);

	HRESULT _createds7(LPDIRECTDRAWSURFACE7 &ds7,long w,long h,DWORD flag);
};

#endif