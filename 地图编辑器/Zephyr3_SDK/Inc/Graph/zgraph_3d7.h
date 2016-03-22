#ifndef ZEPHYR_GRAPH_3D7_H
#define ZEPHYR_GRAPH_3D7_H

#include <Graph\ZGraph.h>

//texture info
const DWORD ZTEXTUREINFO_POW2		=	1;	//2次幂
const DWORD ZTEXTUREINFO_SQUAREONLY	=	2;	//w == h
const DWORD ZTEXTUREINFO_HAL		= 	4;	//hardware device

struct ZTextureInfo{
	DWORD dwFlag;
	DWORD dwWidthMax;
	DWORD dwHeightMax;
};

class ZEPHYR_API ZGraph3D7 : public ZGraph{
	static HRESULT CALLBACK TextureSearchCallback(LPDDPIXELFORMAT pddpf,LPVOID pParam);

public:
	ZGraph3D7();
	virtual ~ZGraph3D7() { Release(); }

	virtual void Release();

	virtual HRESULT Init(bool bWindow,DWORD W,DWORD H,ZEPHYR_COLOR_MODE zcm,bool bUsevm=true);

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

private:
//enum texture
	void _Set_texture_ddpf(int i,DDPIXELFORMAT &dat);

	//ds
	HRESULT _lockds(void* surface,void **pvoid,DWORD &pitch,long &w,long &h);
	HRESULT _lockds_r(void* surface,RECT *rect,void **pvoid,DWORD &pitch,long &w,long &h);
	HRESULT _unlockds(void* surface);
	void _setcolorkey_ds(void *lpds);

private:
	HRESULT _get_screen_colormode_d3d7(ZEPHYR_COLOR_MODE &zcm);

	HRESULT _getdsinfo_ds7(void* ds7,DWORD &pitch,long &w,long &h);

	LPSPRITE_DATA _createbackscreen_d3d7(long w,long h,ZEPHYR_COLOR_MODE zcm,bool usevm);

	HRESULT _enumtexture_d3d7(void *pd3dDevice);

	void _setrenderdev(void *lpv);

	void _init_texture_ddpf();

	void _release_texture_ddpf();

	void _setd3ddev(LPDIRECT3DDEVICE7 &lpdev,DWORD w,DWORD h);

	HRESULT _created3ddev7(LPDIRECTDRAWSURFACE7 &ds7,LPDIRECT3DDEVICE7 &lpd3ddev7,DWORD w,DWORD h,DWORD flag);
	HRESULT _createtexture7(LPDIRECTDRAWSURFACE7 &ds7,long w,long h,DWORD flag,ZEPHYR_COLOR_MODE zcm);

	HRESULT _bltsprite_s(LPSPRITE_DATA dst,long x,long y,LPSPRITE_DATA src,long x0,long y0,long x1,long y1);
	HRESULT _bltsprite_ck_s(LPSPRITE_DATA dst,long x,long y,LPSPRITE_DATA src,long x0,long y0,long x1,long y1);

private:
	LPDIRECTDRAW7			lpdd7;
	LPDIRECTDRAWSURFACE7	lpdds7Primary;
	DDSURFACEDESC2			ddsd7;
	DDPIXELFORMAT			ddpf;

	LPDIRECT3D7				lpd3d7;
	LPDIRECT3DDEVICE7		lpd3ddev7;
	D3DTLVERTEX				tlv[4];

	ZTextureInfo			_ztextureinfo;
	static LPDDPIXELFORMAT	_pddpf[8];
};

#endif