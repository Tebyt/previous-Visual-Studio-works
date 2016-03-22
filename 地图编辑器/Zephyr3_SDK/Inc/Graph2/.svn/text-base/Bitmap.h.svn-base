/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Graph2\Bitmap.h

							Describe:	Bitmap

							Author:		赵洪松(xueren)

							CreateTime: 2004.04.26
							UpdateTime:
*/

#ifndef _ZEPHYR_3_GRAPH_2_BITMAP_H
#define _ZEPHYR_3_GRAPH_2_BITMAP_H

#include <Base\Assert.h>
#include <Base\AutoPtr.h>

#include <Graph2\GraphImp.h>

namespace ZGraph2{

	//////////////////////////////////////////////////////////////////////////////////////////
	// Bitmap

	class ZEPHYR_GRAPH_2_API Bitmap{
	public:
		typedef GraphImp::_BitmapPtr	_Ptr;
	public:
		// 构造函数
		Bitmap(GraphImpPtr ptr,Bitmap::_Ptr dat) {
			m_pGraphImp = ptr;
			m_pDat = (GraphImp::_BitmapPtr)dat;
		}
		// 析构函数
		~Bitmap() {
			if(m_pDat != NULL)
				m_pGraphImp->ReleaseBitmap(m_pDat);
		}

		// 获得属性
		WORD GetFlag() const { 

			ZASSERT(IsInited());

			return m_pDat->wFlag; 
		}

		void AddFlag(WORD newFlag) {
			ZASSERT(IsInited());

			m_pDat->wFlag |= newFlag;
		}
		// 获得色彩模式
		WORD GetColorMode() const { 

			ZASSERT(IsInited());

			return m_pDat->zcm; 
		}

		// 获得图像高度
		DWORD GetHeight() const { 

			ZASSERT(IsInited());

			return m_pDat->dwHeight; 
		}

		// 获得图像宽度
		DWORD GetWidth() const { 

			ZASSERT(IsInited());

			return m_pDat->dwWidth; 
		}

		// 获得图像高度
		DWORD GetRectHeight() const { 

			ZASSERT(IsInited());

			return m_rect.bottom - m_rect.top;
		}

		// 获得图像宽度
		DWORD GetRectWidth() const { 

			ZASSERT(IsInited());

			return m_rect.right - m_rect.left; 
		}

		// 是否已经初始化
		bool IsInited() const { return m_pDat != NULL; }

		// 锁定
		void Lock(LPVOID& dat,DWORD& w,DWORD& h,DWORD& pitch) {

			ZASSERT(IsInited());

			m_pGraphImp->_Lock(m_pDat, dat, w, h, pitch);
		}
		// 解锁
		void Unlock() {

			ZASSERT(IsInited());

			m_pGraphImp->_Unlock(m_pDat);
		}

		// 设置为没有ColorKey
		void SetNoColorKey() {

			ZASSERT(IsInited());

			m_pGraphImp->_SetNoColorKey(m_pDat);
		}

		// 设置Rect
		void SetRect(int left,int top,int right,int bottom) {

			m_rect.left = left;
			m_rect.right = right;
			m_rect.top = top;
			m_rect.bottom = bottom;
		}

		// 获得Rect
		const RECT& GetRect() const { return m_rect; }

		// 画到背景缓冲
		void Draw(int x,int y);
		// 清空
		void Clear(int x,int y,int w,int h,DWORD color);

		// 画到背景缓冲
		void _Draw(int x,int y) {

			ZASSERT(!Zephyr3::_IsNull(m_pGraphImp));

			m_pGraphImp->_Blt(m_pGraphImp->GetBackScreen(),x,y,m_pDat,m_rect.left,m_rect.top,m_rect.right - m_rect.left,m_rect.bottom - m_rect.top);
		}
		// 清空
		void _Clear(int x,int y,int w,int h,DWORD color) {

			ZASSERT(!Zephyr3::_IsNull(m_pGraphImp));

			m_pGraphImp->_Clear(m_pDat,x,y,w,h,color);
		}
	private:
		_Ptr					m_pDat;
		GraphImpPtr				m_pGraphImp;

		RECT					m_rect;
	};

	typedef Bitmap*	LPBitmap;
//	typedef Zephyr3::AutoPtr<Bitmap>	BitmapPtr;

};

#endif // _ZEPHYR_3_GRAPH_2_BITMAP_H