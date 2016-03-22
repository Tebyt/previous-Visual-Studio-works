/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	WTL\ZDialog.h

							Describe:	WTL 的ZDialog支持

							Author:		赵洪松(xueren)

							CreateTime: 2004.04.15
							UpdateTime:
*/

#ifndef _ZEPHYR_3_WTL_ZDIALOG_H
#define _ZEPHYR_3_WTL_ZDIALOG_H

#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>

#include <Graph\ZGraph_GDI.h>

namespace ZephyrWTL{

	template<typename T>
	class Dialog : public CDialogImpl<T> {
	public:
		// 构造函数
		Dialog(HINSTANCE hInst) {

			m_hInst = hInst;
			m_pGraph = NULL;
		}

		// 获得安全的Graph指针
		const ZGraph* GetSafeGraph() const { return m_pGraph; }

		void Release() {

		}
	protected:

		BEGIN_MSG_MAP(CMainDlg)
			MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
			MESSAGE_HANDLER(WM_PAINT, OnPaint)
			MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		END_MSG_MAP()


		// OnInitDialog
		LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
		{
			ZASSERT(m_pGraph == NULL);

			m_pGraph = new ZGraphGDI;

			m_pGraph->SetInstance(m_hInst);
			m_pGraph->SetHWND(m_hWnd);

			RECT rect;

			GetClientRect(&rect);

			if(m_pGraph->Init(true,rect.right,rect.bottom,ZCM_R5G6B5) != S_OK)
			{
				ZRet(E_FAIL,"图形模块初始化失败！");

				return FALSE;
			}

			m_pGraph->SetCutMode(false);
			m_pGraph->SetCutSpr(m_pGraph->GetBackScreenData());

			return TRUE;
		}

		// OnPaint
		LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
		{
			PAINTSTRUCT ps;

			BeginPaint(&ps);

			EndPaint(&ps);

			return 0;
		}

		// OnDestroy
		LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
		{
			if(m_pGraph != NULL)
			{
				delete m_pGraph;

				m_pGraph = NULL;
			}

			return 0;
		}
	protected:
		ZGraph*		m_pGraph;
		HINSTANCE	m_hInst;
	};
};

#endif // _ZEPHYR_3_WTL_ZDIALOG_H