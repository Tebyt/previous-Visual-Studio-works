#ifndef ZEPHYR_SPRITE_H
#define ZEPHYR_SPRITE_H

#include <Graph\ZSpriteData.h>
#include <Graph\BaseDef.h>
#include <Graph\ZFont_2.h>

#define ZEPHYRSPRITE_BLT_COLORKEY	0x1
#define ZEPHYRSPRITE_BLT_ALPHA		0x2

class ZEPHYR_API ZSprite{
public:
	LPSPRITE_DATA	m_lps;
	LPSPRITE_DATA	m_pAlpha;
	RECT			m_Rect;
	ZRenderEngine	*m_RenderEngine;
public:
	ZSprite() 
		: m_lps(NULL)
		, m_RenderEngine(NULL)
		, m_pAlpha(NULL)
	{ 
	}

	ZSprite(ZSprite &spr,RECT &rect);
	inline ~ZSprite() { Release(); }

	ZSprite& operator=(const ZSprite& spr);

	//Release
	void Release();
	//IsInited ?
	inline bool IsInited() const;

//�ļ����� save
	inline void Save(const char *filename) const;
	inline void SaveBmp(const char *filename) const;
	inline void SaveZpc(const char *filename,const char *jpgfile) const;
	inline void SaveZpc(const char* filename,DWORD format) const;

//ͼ������������»��ߵ�Ϊ�첽����
//���»��ߵģ�������ɡ����ޱ�Ҫ����ò�Ҫʹ��
	// ���ߺ���
	inline void Line(long x1,long y1,long x2,long y2,DWORD color);
	// �����ο�
	inline void Rect(long x1,long y1,long x2,long y2,DWORD color);

	// λͼ����
	inline void Blt(long x1,long y1,ZSprite *lpsrc,long x2,long y2,long x3,long y3);
	// ��͸��ɫ��λͼ����
	inline void Blt_ck(long x1,long y1,ZSprite *src,long x2,long y2,long x3,long y3);

	// ����
	inline void Blt_zoom(long x1,long y1,long w1,long h1,ZSprite *src,long x2,long y2,long w2,long h2);
	// ��͸��ɫ��λͼ����
	inline void Blt_zoom_alpha(long x1,long y1,long w1,long h1,ZSprite *src,long x2,long y2,long w2,long h2,BYTE alpha);

	// ��alphaͨ���ĺ���
	inline void Blt_alpha(long x,long y,ZSprite *src,long x0,long y0,long x1,long y1,BYTE alpha);
	inline void Blt_alpha(long x,long y,ZSprite *src,long x0,long y0,long x1,long y1);
	inline void Blt_alpha_ck(long x,long y,ZSprite *src,long x0,long y0,long x1,long y1,BYTE alpha);
	inline void Blt_alpha(long x,long y,ZSprite *src,long x0,long y0,long x1,long y1,ZSprite *alpha);
	inline void Blt_alpha(long x,long y,DWORD color,long x0,long y0,long x1,long y1,ZSprite *alpha);

	// additive�ں�
	inline void Blt_additive(long x,long y,ZSprite *src,long x0,long y0,long x1,long y1,BYTE alpha);

	// ���к����������blt����һ��������Ա�������
	inline void Draw(long x,long y,DWORD flag);
	inline void Draw(long x,long y);
	inline void Draw_ck(long x,long y);
	inline void Draw_zoom(long x,long y,long w,long h);
	inline void Draw_alpha(long x,long y,BYTE alpha);
	inline void Draw_alpha_ck(long x,long y,BYTE alpha);
	inline void Draw_alpha(long x,long y);
	inline void Draw_alpha(long x,long y,ZSprite *alpha);
	inline void Draw_additive(long x,long y,BYTE alpha);

	void Printf(ZFont* zfont,long x,long y,DWORD color,const char* s,...);
	void Printf(int fontheight,long x,long y,DWORD color,const char* s,...);

	void Printf(ZFont* zfont,long x,long y,DWORD color,long x_max,const char* s,...);
	void Printf(int fontheight,long x,long y,DWORD color,long x_max,const char* s,...);

	inline void Clear(long x,long y,long w,long h,DWORD color);
	inline void Clear(const RECT &rect,DWORD color);
	inline void Clear(DWORD color);
	inline void Clear_alpha(long x, long y, long w, long h, DWORD color, BYTE alpha);

	inline void Updata();

	inline void _blt(long x1,long y1,ZSprite *lpsrc,long x2,long y2,long x3,long y3);
	inline void _blt_ck(long x1,long y1,ZSprite *src,long x2,long y2,long x3,long y3);
	inline void _blt_zoom(long x1,long y1,long w1,long h1,ZSprite *src,long x2,long y2,long w2,long h2);
	inline void _blt_alpha(long x,long y,ZSprite *src,long x0,long y0,long x1,long y1,BYTE alpha);
	inline void _blt_alpha_ck(long x,long y,ZSprite *src,long x0,long y0,long x1,long y1,BYTE alpha);
	inline void _blt_alpha(long x,long y,ZSprite *src,long x0,long y0,long x1,long y1,ZSprite *alpha);
	inline void _blt_alpha(long x,long y,DWORD color,long x0,long y0,long x1,long y1,ZSprite *alpha);
	inline void _blt_alpha(long x,long y,ZSprite *src,long x0,long y0,long x1,long y1);
	inline void _blt_additive(long x,long y,ZSprite *src,long x0,long y0,long x1,long y1,BYTE alpha);

	inline HRESULT _clear(long x,long y,long w,long h,DWORD color);
	inline HRESULT _clear(const RECT &rect,DWORD color);
	inline HRESULT _clear(DWORD color);

	HRESULT _printf(ZFont* zfont,long x,long y,DWORD color,const char* s,...);
	HRESULT _printf(int fontheight,long x,long y,DWORD color,const char* s,...);

	inline void _line(long x1,long y1,long x2,long y2,DWORD color);
	inline void _rect(long x1,long y1,long x2,long y2,DWORD color);

	LPZSprite ChangeToMask();

	LPZSprite ChangeToMaskEx();

	void BuildAlpha(ZSprite* pAlpha, BYTE alpha);

	void _BuildAlpha(LPSPRITE_DATA pAlpha, BYTE alpha);

//Color Key
	void SetColorKey(DWORD color);
	void SetColorKey(long x,long y);
	void SetNoColorKey();

	bool IsColorKey(long x,long y);

//Lock & Unlock
	inline HRESULT Lock(void **pdata,DWORD &pitch,long &w,long &h);
	inline void Unlock();

//����
	inline DWORD GetWidth() const;
	inline DWORD GetHeight() const;
	inline DWORD GetRectWidth() const;
	inline DWORD GetRectHeight() const;
	inline const LPSPRITE_DATA GetData() const;

	inline void SetRect(long l,long t,long r,long b);
	inline void SetRect();
	inline void SetRect(const RECT &r);

	inline void SetRenderEngine(ZRenderEngine *renderengine);
};

#endif