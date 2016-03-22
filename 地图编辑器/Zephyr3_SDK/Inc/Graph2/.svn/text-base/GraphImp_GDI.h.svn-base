/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Graph2\GraphImp_GDI.h

							Describe:	GraphImp_GDI

							Author:		赵洪松(xueren)

							CreateTime: 2004.04.24
							UpdateTime:
*/

#ifndef _ZEPHYR_GRAPH_2_GRAPHIMP_GDI_H
#define _ZEPHYR_GRAPH_2_GRAPHIMP_GDI_H

#include <Base\Assert.h>

#include <Graph2\BaseDef.h>
#include <Graph2\GraphImp.h>

namespace ZGraph2{

	//////////////////////////////////////////////////////////////////////////////////////////////////
	// GraphImp

	class ZEPHYR_GRAPH_2_API GraphImp_GDI : public GraphImp{
	public:
		struct _Bitmap : public GraphImp::_Bitmap{
			void				*dat[1];			// 数据
		};

		typedef _Bitmap*	_BitmapPtr;
	public:
		// 构造函数
		GraphImp_GDI() { m_pBackScreen = NULL; }
		// 析构函数
		virtual ~GraphImp_GDI() {}
	public:

	// 虚函数 from GraphImp --->

		// 初始化
		virtual HRESULT Init(HWND hWnd,DWORD w,DWORD h,ZEPHYR_COLOR_MODE zcm,DWORD flag);

		// 改变屏幕大小
		virtual void ResizeScreen(DWORD w,DWORD h);

		// 创建 Bitmap
		virtual GraphImp::_BitmapPtr CreateBitmap(DWORD w,DWORD h,ZEPHYR_COLOR_MODE zcm,WORD flag);
		// 释放 Bitmap
		virtual void ReleaseBitmap(GraphImp::_BitmapPtr& bitmap);

		// Blt
		virtual void _Blt(GraphImp::_BitmapPtr dst,int dx,int dy,GraphImp::_BitmapPtr src,int sx,int sy,int w,int h);
		// clear
		virtual void _Clear(GraphImp::_BitmapPtr dst,int x,int y,int w,int h,DWORD color);

		// 锁定
		virtual void _Lock(GraphImp::_BitmapPtr dst,LPVOID& dat,DWORD& w,DWORD& h,DWORD& pitch) {

			ZASSERT(dst != NULL);

			dat = _ChangePtr(dst)->dat[0];
			w = _ChangePtr(dst)->dwWidth;
			h = _ChangePtr(dst)->dwHeight;
			pitch = _ChangePtr(dst)->dwPitch;
		}
		// 解锁
		virtual void _Unlock(GraphImp::_BitmapPtr dst) {

			ZASSERT(dst != NULL);
		}

		// 得到象素信息
		virtual DWORD __GetPixel(GraphImp::_BitmapPtr dst,int x,int y);
		// 得到象素信息
		virtual void __SetPixel(GraphImp::_BitmapPtr dst,int x,int y,DWORD pixel);
		// 画线
		virtual void _Line(GraphImp::_BitmapPtr dst,int x1,int y1,int x2,int y2,DWORD color);

		// 设置为没有透明色
		virtual void _SetNoColorKey(GraphImp::_BitmapPtr dst);


		// 渲染
		virtual void Render(RECT rect);

		// 渲染全部
		virtual void Render();

	// <--- 

		// 创建背景缓冲
		HRESULT CreateBackScreen(DWORD w,DWORD h);
		// 释放背景缓冲
		void ReleaseBackScreen();
		// 改变背景缓冲大小
		HRESULT ResizeBackScreen(DWORD w,DWORD h);

		// 得到象素信息－灰度位图
		BYTE __GetPixel_Gray(GraphImp::_BitmapPtr dst,int x,int y) {

			ZASSERT(dst != NULL);
			ZASSERT(((_BitmapPtr)dst)->IsValid(x,y));

			return ((BYTE *)(((_BitmapPtr)dst)->dat[y]))[x];
		}

		// 得到象素信息－R5G6B5位图
		WORD __GetPixel_R5G6B5(GraphImp::_BitmapPtr dst,int x,int y) {

			ZASSERT(dst != NULL);
			ZASSERT(((_BitmapPtr)dst)->IsValid(x,y));

			return ((WORD *)(((_BitmapPtr)dst)->dat[y]))[x];
		}

		// 得到象素信息－灰度位图
		void __SetPixel_Gray(GraphImp::_BitmapPtr dst,int x,int y,BYTE pixel) {

			ZASSERT(dst != NULL);
			ZASSERT(((_BitmapPtr)dst)->IsValid(x,y));

			((BYTE *)(((_BitmapPtr)dst)->dat[y]))[x] = pixel;
		}

		// 得到象素信息－R5G6B5位图
		void __SetPixel_R5G6B5(GraphImp::_BitmapPtr dst,int x,int y,WORD pixel) {

			ZASSERT(dst != NULL);
			ZASSERT(((_BitmapPtr)dst)->IsValid(x,y));

			((WORD *)(((_BitmapPtr)dst)->dat[y]))[x] = pixel;
		}

		_BitmapPtr _ChangePtr(GraphImp::_BitmapPtr ptr) const { return (_BitmapPtr)ptr; }
	};
};

#endif // _ZEPHYR_GRAPH_2_GRAPHIMP_GDI_H