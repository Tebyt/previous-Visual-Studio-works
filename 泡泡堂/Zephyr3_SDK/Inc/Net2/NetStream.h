/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Net2\NetStream.h

							Describe:	网络流

							Author:		赵洪松(xueren)

							CreateTime: 2003.11.5
							UpdateTime: 2003.12.11	-	修正 NetStream 处理消息 标志量 的 bug
										2003.12.12	-	修正 NetStream 处理 分析消息 和 丢弃消息 的 bug
*/

#ifndef _ZEPHYR_NET_2_NETSTREAM_H
#define _ZEPHYR_NET_2_NETSTREAM_H

#include <ZDebug.h>
#include <ZLink.h>
#include <ZLock.h>
#include <MulData.h>
#include <Net2\BaseDef.h>
#include <Net2\NetMsg.h>

////////////////////////////////////////////////////////////////////////////////
// ZNet2
namespace ZNet2{

	class _block;
	class _buff;
/*
	struct NetStream_Data{
		void*	pNode;
		_block*	pData;
	};

	typedef NetStream_Data*	LPNetStream_Data;
*/
	////////////////////////////////////////////////////////////////////////////
	// NetStream
	class ZEPHYR_NET_API NetStream{
	public:
		typedef ZLink_2<_block,4,4>	_link;

	public:
		// 构造函数
		NetStream() {
			m_bMsgNotEnd = false;
		}

		// 析构函数
		~NetStream() {
		}

	// ------------------------------------------------------------------------
	// 操作

	// Recv专用
		// 请求内存
		_block* Request(_block* pDat,DWORD dwWant);

		// 分析输入数据
		// 返回值为已经接收的消息数量
		int Analyse_InData(DWORD recvLen,_block* pDat,DWORD& dwWant);

		// 处理消息
		LPZNetMsgHead Process_InData();

		// 丢弃 一个消息
		bool BrushMsg();

		// 连接中断
		void EndConnect() {
			m_bEndConnect.Set(true);
		}

	// Send专用

	// 公用
		// 获得起始结点
		_block* GetFirstNode();

		// 清空
		void Clear();

		bool IsProcess() {
			return m_bProcess.Get();
		}
	private:
		static _buff		m_Buff;

		_link				m_Link;
		ZCriticalSection	m_Lock;

		int					m_recvLen;	// 已经接收到，但没有完全接收完的消息，已经接收到的消息长度
		BYTE*				m_recvDat;	// 已经接收到，但没有完全接收完的消息，起始位置

		bool				m_bMsgNotEnd;
		Zephyr3::MulBool	m_bProcess;
		Zephyr3::MulBool	m_bEndConnect;

		static EndConnectMsg	m_EndConnectMsg;
	};

	typedef NetStream*	LPNetStream;
};

#endif//_ZEPHYR_NET_2_NETSTREAM_H