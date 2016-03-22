/*
							FlyingMagic 2.8

							by ’‘∫ÈÀ…(zhs007)

							E-mail:		sssxueren@gmail.com

							FileName:	Windows\BtnEx.h

							Describe:	Btn Ex

							Author:		’‘∫ÈÀ…(zhs007)

							CreateTime: 2007.07.02
							UpdateTime:
*/

#ifndef __ZEPHYR_3_WINDOWS_BTNEX_H__
#define __ZEPHYR_3_WINDOWS_BTNEX_H__

#include <Zephyr.h>

#include <Windows/ZWnd.h>
#include <Windows/wndctl.h>
#include <string>

namespace Zephyr3{

	class ZEPHYR_API ZWndBtnEx : public ZephyrWnd
	{
	public:
		ZWndBtnEx();
		virtual ~ZWndBtnEx();

		//¥¥Ω®¥∞ø⁄
		HRESULT Create(const char *name, DWORD style, int x, int y, int w, int h, ZephyrWnd *parent, UINT nID);
		//¥¥Ω®¥∞ø⁄
		HRESULT Create(const char *name, DWORD style, int x, int y, int w, int h, HWND parent, UINT nID);

		void SetSprite(LPZSprite lps, bool bState, int index, RECT &rect, bool bColorKey);

		long GetWidth() const {
			if(m_Sprite[0][0] != NULL)
				return m_Sprite[0][0]->GetRectWidth();
			else
				return m_Rect.right - m_Rect.left;
		}

		long GetHeight()	const {
			if(m_Sprite[0][0] != NULL)
				return m_Sprite[0][0]->GetRectHeight();
			else
				return m_Rect.bottom-m_Rect.top;
		}

		void Release();

		//virtual from ZephyrWnd
		virtual void DrawWndItem(RECT* pRect = NULL);
		virtual bool IsIn(long x,long y);

		void SetMessage(DWORD msg) { m_Msg = msg; }

		bool GetBtnExState() const { return m_bState; }

		void ChgBtnExState(bool bState) { m_bState = bState; }

		void SetHelpInfo(const char* str1, const char* str2) {
			m_strInfo[0] = str1;
			m_strInfo[1] = str2;
		}
	protected:
		int OnLButtonDown(DWORD wParam,DWORD lParam);
		int OnLButtonUp(DWORD wParam,DWORD lParam);
		int OnRButtonDown(DWORD wParam,DWORD lParam);
		int OnRButtonUp(DWORD wParam,DWORD lParam);
		int OnLButtonDblClk(DWORD wParam,DWORD lParam);
		int OnMouseMove(DWORD wParam,DWORD lParam);
		int OnMouseLeave(DWORD wParam,DWORD lParam);
		int OnTimer(DWORD wParam,DWORD lParam);
		int OnDestroy(DWORD wParam,DWORD lParam);

		ZDECLARE_MESSAGE_MAP()
	private:
		LPZSprite	m_Sprite[2][4];

		DWORD		m_Msg;

		DWORD		m_dwShowTime;

		bool		m_bState;		//! ◊¥Ã¨£¨false°¢true

		std::string	m_strInfo[2];
	};
}

#endif // __ZEPHYR_3_WINDOWS_BTNEX_H__
