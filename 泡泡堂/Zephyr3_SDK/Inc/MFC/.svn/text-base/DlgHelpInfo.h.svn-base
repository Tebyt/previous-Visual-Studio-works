/*
							Zephyr 3.2

							by 赵洪松(zhs007)

							E-mail:		sssxueren@gmail.com

							FileName:	MFC\DlgHelpInfo.h

							Describe:	基础定义

							Author:		赵洪松(zhs007)

							CreateTime: 2007.06.12
							UpdateTime:
*/

#ifndef __ZEPHYR3_MFC_DLGHELPINFO_H__
#define __ZEPHYR3_MFC_DLGHELPINFO_H__

#include <MFC\CZDialog.h>

namespace Zephyr3{

	class ZEPHYR_MFC_API CDlgHelpInfo : public CZDialog
	{
		enum{
			_MAX_LEN	=	256
		};

		DECLARE_DYNAMIC(CDlgHelpInfo)

	public:
		// 构造函数，无模式对话框
		CDlgHelpInfo();
		// 析构函数
		virtual ~CDlgHelpInfo();

		// 初始化函数
		bool Create(DWORD dlgID);
		// 设置数据
		void SetInfoData(const char *data) {
			if(data != NULL)
				strcpy(m_strDat,data);
			else
				m_strDat[0] = '\0';
		}
		// 显示对话框
		void Show(HWND hWnd, int x, int y, const char *data);
		// 隐藏对话框
		void Hide();

		bool IsUsed() { return m_strDat[0] != '\0'; }
	protected:
		// OnCancel
		virtual void OnCancel();
		// OnOK
		virtual void OnOK();

		// DDX/DDV 支持
		virtual void DoDataExchange(CDataExchange* pDX);

		//消息映射
		afx_msg void OnClose();
		afx_msg void OnDestroy();
		afx_msg void OnPaint();

		DECLARE_MESSAGE_MAP()
	private:
		char		m_strDat[_MAX_LEN];
		bool		m_bExit;
	};

	typedef CDlgHelpInfo&	CDlgHelpInfoRef;

	CDlgHelpInfoRef ZEPHYR_MFC_API GetDlgHelpInfo();
}

#endif // __ZEPHYR3_MFC_DLGHELPINFO_H__
