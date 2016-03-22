/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Graph2\GraphImp.h

							Describe:	GraphImp

							Author:		赵洪松(xueren)

							CreateTime: 2004.04.24
							UpdateTime:
*/

#ifndef _ZEPHYR_GRAPH_2_GRAPHIMP_H
#define _ZEPHYR_GRAPH_2_GRAPHIMP_H

#include <Base\AutoPtr.h>
#include <Base\Queue.h>
#include <Base\Stack.h>

#include <Graph2\BaseDef.h>

namespace ZGraph2{

	class Command;
	typedef Command*	LPCommand;

	//////////////////////////////////////////////////////////////////////////////////////////////////
	// GraphImp
	// 内部不会支持多线程，仅对显存Bitmap，提供 锁定/解锁 功能
	// 如果需要多线程互斥，需要自行处理

	class ZEPHYR_GRAPH_2_API GraphImp{
		friend class Graph;

		friend class Bitmap;
		friend class BitmapManager;

		friend class RenderEngine;

		friend class Command;
		friend class ClearBitmap;
		friend class BltBitmap;
	public:
		struct _Bitmap{
			WORD				wFlag;				// flag
			WORD				zcm;				// color mode
			DWORD				dwWidth,dwHeight;	// width、height
			DWORD				dwPitch;			// pitch
			DWORD				dwNums;				// dwNums

			bool IsValid(int x,int y) {
				return x >= 0 && x < dwWidth && y >= 0 && y < dwHeight;
			}
		};

		typedef _Bitmap*	_BitmapPtr;

		enum{
			STATE_WINDOW				=	0x01,
			STATE_BACKSCREEN_VMEM		=	0x02,
			STATE_RENDERENGINE_NORMAL	=	0x04,
		};

		typedef Zephyr3::Queue<LPCommand,128,64>	_Queue;

		typedef Zephyr3::Stack<BYTE,256,256>	_Stack;
	public:
		// 构造函数
		GraphImp() { 

			m_pBackScreen = NULL; 
			m_pRenderEngine = NULL;
		}
		// 析构函数
		virtual ~GraphImp() {}

	protected:
		// 初始化
		virtual HRESULT Init(HWND hWnd,DWORD w,DWORD h,ZEPHYR_COLOR_MODE zcm,DWORD flag) {

			m_hWnd = hWnd;

			m_dwScreenWidth = w;
			m_dwScreenHeight = h;

			return CreateRenderEngine(flag);
		}

		// 创建渲染引擎
		HRESULT CreateRenderEngine(DWORD flag);

		// 改变屏幕大小
		virtual void ResizeScreen(DWORD w,DWORD h) {
			m_dwScreenWidth = w;
			m_dwScreenHeight = h;
		}

		// 渲染到背景缓冲
		void RenderToBackScreen(RECT rect);

		// 渲染到背景缓冲
		void RenderToBackScreen();

		// 渲染
		void RenderToScreen(RECT rect);

		// 渲染
		void RenderToScreen();

		// 获取背景缓冲
		GraphImp::_BitmapPtr GetBackScreen() { return m_pBackScreen; }

		// 获得屏幕Width
		DWORD GetScreenWidth() const { return m_dwScreenWidth; }
		// 获得屏幕Height
		DWORD GetScreenHeight() const { return m_dwScreenHeight; }

		// Clear BackScreen
		void ClearBackScreen(int x,int y,int w,int h,DWORD color) {
			Clear(m_pBackScreen,x,y,w,h,color);
		}

		// Clear BackScreen
		void _ClearBackScreen(int x,int y,int w,int h,DWORD color) {
			_Clear(m_pBackScreen,x,y,w,h,color);
		}

		// Clear Command
		void ClearCmd() {
			m_queue.Clear();
			m_stack.Clear();
		}
	protected:
		// 渲染
		virtual void Render(RECT rect) {}

		// 渲染全部
		virtual void Render() {}


		// 创建 Bitmap
		virtual GraphImp::_BitmapPtr CreateBitmap(DWORD w,DWORD h,ZEPHYR_COLOR_MODE zcm,WORD flag) { return NULL; }
		// 释放 Bitmap
		virtual void ReleaseBitmap(GraphImp::_BitmapPtr& bitmap) {}

		// Blt
		virtual void _Blt(GraphImp::_BitmapPtr dst,int dx,int dy,GraphImp::_BitmapPtr src,int sx,int sy,int w,int h) {}
		// clear
		virtual void _Clear(GraphImp::_BitmapPtr dst,int x,int y,int w,int h,DWORD color) {}

		// 锁定
		virtual void _Lock(GraphImp::_BitmapPtr dst,LPVOID& dat,DWORD& w,DWORD& h,DWORD& pitch) {}
		// 解锁
		virtual void _Unlock(GraphImp::_BitmapPtr dst) {}

		// 得到象素信息
		virtual DWORD __GetPixel(GraphImp::_BitmapPtr dst,int x,int y) { return 0; }
		// 得到象素信息
		virtual void __SetPixel(GraphImp::_BitmapPtr dst,int x,int y,DWORD pixel) {}

		// 画线
		virtual void _Line(GraphImp::_BitmapPtr dst,int x1,int y1,int x2,int y2,DWORD color) {}

		// 设置为没有透明色
		virtual void _SetNoColorKey(GraphImp::_BitmapPtr dst) {}


		// Blt
		inline void Blt(GraphImp::_BitmapPtr dst,int dx,int dy,GraphImp::_BitmapPtr src,int sx,int sy,int w,int h);
		// clear
		inline void Clear(GraphImp::_BitmapPtr dst,int x,int y,int w,int h,DWORD color);
	protected:
		_BitmapPtr	m_pBackScreen;
		DWORD		m_dwScreenWidth;
		DWORD		m_dwScreenHeight;
		HWND		m_hWnd;

		_Queue		m_queue;
		_Stack		m_stack;

		RenderEngine*		m_pRenderEngine;

		static ClearBitmap	m_cmdClear;
		static BltBitmap	m_cmdBlt;
	private:
	};

	typedef Zephyr3::AutoPtr<GraphImp>	GraphImpPtr;


	//////////////////////////////////////////////////////////////////////////////////////////
	// Command

	class Command{
	public:
		Command(unsigned int size) {
			m_paramSize = size;
		}

		virtual ~Command() {}

		virtual void operator() (GraphImp* pGraphImp,LPVOID pParam) = 0;

		virtual void GetDstRect(RECT& rect,LPVOID pParam) = 0;
	public:
		unsigned int	m_paramSize;
	};

	class ClearBitmap : public Command{
	public:
		struct _Param{
			GraphImp::_BitmapPtr	bmp;
			int						x,y,w,h;
			DWORD					color;
		};
	public:
		ClearBitmap() : Command(sizeof(_Param)) {}

		virtual void operator() (GraphImp* pGraphImp,LPVOID pParam) {
			ZASSERT(pParam != NULL);

			pGraphImp->_Clear(((_Param*)pParam)->bmp,((_Param*)pParam)->x,((_Param*)pParam)->y,((_Param*)pParam)->w,((_Param*)pParam)->h,((_Param*)pParam)->color);
		}

		virtual void GetDstRect(RECT& rect,LPVOID pParam) {
			ZASSERT(pParam != NULL);

			rect.left = ((_Param*)pParam)->x;
			rect.right = ((_Param*)pParam)->x + ((_Param*)pParam)->w;
			rect.top = ((_Param*)pParam)->y;
			rect.bottom = ((_Param*)pParam)->y + ((_Param*)pParam)->h;
		}
	};

	class BltBitmap : public Command{
	public:
		struct _Param{
			GraphImp::_BitmapPtr	dst;
			int						dx,dy;
			GraphImp::_BitmapPtr	src;
			int						sx,sy,w,h;
		};
	public:
		BltBitmap() : Command(sizeof(_Param)) {}

		virtual void operator() (GraphImp* pGraphImp,LPVOID pParam) {
			ZASSERT(pParam != NULL);

			pGraphImp->_Blt(((_Param*)pParam)->dst,((_Param*)pParam)->dx,((_Param*)pParam)->dy,((_Param*)pParam)->src,((_Param*)pParam)->sx,((_Param*)pParam)->sy,((_Param*)pParam)->w,((_Param*)pParam)->h);
		}

		virtual void GetDstRect(RECT& rect,LPVOID pParam) {
			ZASSERT(pParam != NULL);

			rect.left = ((_Param*)pParam)->dx;
			rect.right = ((_Param*)pParam)->dx + ((_Param*)pParam)->w;
			rect.top = ((_Param*)pParam)->dy;
			rect.bottom = ((_Param*)pParam)->dy + ((_Param*)pParam)->h;
		}
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////
	// GraphImp

	// Blt
	inline void GraphImp::Blt(GraphImp::_BitmapPtr dst,int dx,int dy,GraphImp::_BitmapPtr src,int sx,int sy,int w,int h)
	{
		LPCommand pCmd = &m_cmdBlt;

		BltBitmap::_Param param;

		param.dst = dst;
		param.dx = dx;
		param.dy = dy;
		param.src = src;
		param.sx = sx;
		param.sy = sy;
		param.w = w;
		param.h = h;

		m_queue.Put(pCmd);
		m_stack.Push((BYTE*)&param,sizeof(param));
	}

	// clear
	inline void GraphImp::Clear(GraphImp::_BitmapPtr dst,int x,int y,int w,int h,DWORD color)
	{
		LPCommand pCmd = &m_cmdClear;

		ClearBitmap::_Param param;

		param.bmp = dst;
		param.x = x;
		param.y = y;
		param.w = w;
		param.h = h;
		param.color = color;

		m_queue.Put(pCmd);
		m_stack.Push((BYTE*)&param,sizeof(param));
	}
};

#endif // _ZEPHYR_GRAPH_2_GRAPHIMP_H