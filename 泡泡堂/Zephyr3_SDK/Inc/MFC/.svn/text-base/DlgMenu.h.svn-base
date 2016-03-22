/*
							FlyingMagic 2.8

							by 赵洪松(zhs007)

							E-mail:		sssxueren@gmail.com

							FileName:	MFC\DlgMenu.h

							Describe:	Dlg Menu

							Author:		赵洪松(zhs007)

							CreateTime: 2007.07.02
							UpdateTime:
*/

#ifndef __ZEPHYR_3_MFC_DLGMENU_H__
#define __ZEPHYR_3_MFC_DLGMENU_H__

#include <Zephyr.h>

#include <MFC\CZDialog.h>

#include <vector>
#include <string>

namespace Zephyr3{

	class ZEPHYR_API CDlgMenu : public CZDialog
	{
		DECLARE_DYNAMIC(CDlgMenu)
	public:
		struct _MenuNode{
			int				x, y;
			std::string		str;
			bool			bCanClick;

			WPARAM			wParam;
			LPARAM			lParam;
		};

		typedef std::vector<_MenuNode>	_MenuList;
	public:
		// 构造函数，无模式对话框
		CDlgMenu();
		// 析构函数
		virtual ~CDlgMenu();

		// 窗口绘制函数
		virtual void Draw(RECT* pRect);

		// 初始化函数
		bool Create(DWORD dlgID);
		// 显示对话框
		void Show(HWND hWnd, DWORD dwMsg, int x, int y, const CDlgMenu::_MenuList& menu);
		// 隐藏对话框
		void Hide();

		void Exit();
	protected:
		void LoadRes();

		void ReleaseRes();

//		void RebuildMenu();

		void ChgXY(int& x, int& y);
	protected:
		// OnCancel
		virtual void OnCancel();
		// OnOK
		virtual void OnOK();

		virtual BOOL OnInitDialog();
		// DDX/DDV 支持
		virtual void DoDataExchange(CDataExchange* pDX);

		//消息映射
		//afx_msg void OnClose();
		afx_msg void OnDestroy();
		afx_msg void OnTimer(UINT nIDEvent);
		afx_msg void OnMouseMove(UINT nFlags, CPoint point);
		afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
		//afx_msg void OnPaint();

		DECLARE_MESSAGE_MAP()
	private:
		bool						m_bExit;

		HWND						m_hDestWnd;
		DWORD						m_dwDestMsg;

		LPZSprite					m_sprBack;
		LPZSprite					m_sprMenuBack;

		int							m_iCurIndex;

		_MenuList					m_lstMenu;
	};
}

#endif // __ZEPHYR_3_MFC_DLGMENU_H__
