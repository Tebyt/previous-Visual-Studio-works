/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Net2\MsgProcessor.h

							Describe:	消息处理器

							Author:		赵洪松(xueren)

							CreateTime: 2003.11.25
							UpdateTime:
*/

#ifndef _ZEPHYR_NET_2_MSG_PROCESSOR_H
#define _ZEPHYR_NET_2_MSG_PROCESSOR_H

#include <ZDebug.h>
#include <ZThread.h>
#include <Net2\BaseDef.h>
#include <Net2\NetStream.h>
#include <Net2\ZSocket.h>

////////////////////////////////////////////////////////////////////////////////
// ZNet2
namespace ZNet2{

	////////////////////////////////////////////////////////////////////////////
	// MsgWorker
	// 消息处理器

	// 主消息ID未定义
	const HRESULT	MSG_ERROR_MAINID_NOTDEF	=	0x80000001;
	// 辅助消息ID未定义
	const HRESULT	MSG_ERROR_ASSID_NOTDEF	=	0x80000002;

	class ZEPHYR_NET_API MsgWorker{
	public:
		// 构造函数
		MsgWorker(HWND hWnd, DWORD wndMsg) {
			m_hWnd = hWnd;
			m_wndMsg = wndMsg;
		}

		// 消息处理
		virtual HRESULT HandleMessage(LPVOID pMsg, int msgLen, LPVOID pAddr, LPVOID pThread) = 0;

		// 连接中断
		virtual void PeerCut(LPVOID pAddr) = 0;

		// 连接
		virtual void PeerConnect(LPVOID pAddr) = 0;

		// 消息线程开始时执行
		virtual HRESULT MsgThreadBegin(LPVOID pThread) { return S_OK; }
		// 消息线程结束时执行
		virtual void MsgThreadEnd(LPVOID pThread) {}
		// 向目标窗口发送消息
		virtual void PostMsg(DWORD wParam,DWORD lParam) {

			if(m_hWnd != NULL)
				PostMessage(m_hWnd,m_wndMsg,wParam,lParam);
		}	
	protected:

		// 向目标窗口发送消息
		virtual void SendMsg(DWORD wParam,DWORD lParam) {

			if(m_hWnd != NULL)
				SendMessage(m_hWnd,m_wndMsg,wParam,lParam);
		}
	protected:
		HWND	m_hWnd;
		DWORD	m_wndMsg;
	};

	typedef MsgWorker*	LPMsgWorker;
};

#endif//_ZEPHYR_NET_2_MSG_PROCESSOR_H