/*
							Zephyr Engine v3.0

							by ’‘∫ÈÀ…(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@21cn.com

							FileName:	Net2\SendStream.h

							Describe:	Õ¯¬Á¡˜

							Author:		’‘∫ÈÀ…(xueren)

							CreateTime: 2005.02.19
							UpdateTime:
*/

#ifndef _ZEPHYR_NET_2_SENDSTREAM_H
#define _ZEPHYR_NET_2_SENDSTREAM_H

#include <ZDebug.h>
#include <ZLink.h>
#include <ZLock.h>
#include <MulData.h>
#include <Net2\BaseDef.h>
#include <Net2\NetMsg.h>

namespace ZNet2{

#ifdef _ZEPHYR_NET_21__
	class _Block_2;
	class _BlockPool;
	class _BlockQueue;

	class ZEPHYR_NET_API SendStream{
	public:
		SendStream();
		~SendStream();

		long SendMsg(const void* pMsg, unsigned int size, bool bEncode);

		void Clear();

		LPVOID GetSendData(unsigned int& size);
		LPVOID GetHeadData(unsigned int& size);

		void Next();
	private:
//		static _BlockPool	m_pool;

		_BlockQueue*		m_pQueue;
		Zephyr3::MulLong	m_curDat;
	};
#endif // _ZEPHYR_NET_21__

}

#endif // _ZEPHYR_NET_2_SENDSTREAM_H