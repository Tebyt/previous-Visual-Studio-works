/*
							Zephyr Engine v3.0

							by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Net2\TCP_Client_Proxy.h

							Describe:	底层TCP客户端 代理

							Author:		赵洪松(xueren)

							CreateTime: 2010.05.17
							UpdateTime: 2010.05.17
*/

#ifndef _ZEPHYR_NET_2_TCP_CLIENT_PROXY_H
#define _ZEPHYR_NET_2_TCP_CLIENT_PROXY_H

#include <Net2\TCP_Client.h>
#include <Net2\WndMsg.h>
#include <wininet.h>

namespace ZNet2{

	const int SOCKS5_ID_LEN		=	256;
	const int SOCKS5_PSW_LEN	=	256;

	class ZEPHYR_NET_API TCPClient_Proxy : public TCPClient{

		struct RecvData{
			BYTE*	pDat;
			int		iSize;
			int		iPos;

			RecvData() {
				pDat = NULL;
				iSize = iPos = 0;
			}

			~RecvData() {

				Release();
			}

			void Clear() {

				iPos = 0;
			}

			void Alloc(int size) {

				if(iSize < size && pDat != NULL)
				{
					delete[] pDat;

					pDat = NULL;

					iSize = 0;
				}

				if(pDat == NULL)
				{
					pDat = new BYTE[size];

					iSize = size;
				}

				iPos = 0;
			}

			bool IsUsed() {

				return iPos != 0;
			}

			void Release() {
				if(pDat != NULL)
				{
					delete[] pDat;

					pDat = NULL;
				}

				iPos = iSize = 0;
			}
		};
	public:
		enum _SOCKS_TYPE{
			_SOCKS_4	=	1,
			_SOCKS_5	=	2,
			_SOCKS_HTTP	=	3,
			_SOCKS_IE	=	4,
			_SOCKS_NONE	=	0
		};
	public:
		// 构造函数
		TCPClient_Proxy(LPMsgWorker pMsgWorker) 
			: TCPClient(pMsgWorker) 
			, m_socksType(_SOCKS_NONE)
		{

			m_userID[0] = '\0';
			m_userPSW[0] = '\0';

			m_socks5_State = 0;
		}
		// 析构函数
		virtual ~TCPClient_Proxy() {
			Release();
		}

		// 初始化客户端
		HRESULT Init(ZSocketAddr& addr,_SOCKS_TYPE type = _SOCKS_NONE,const LPZSocketAddr pHost = NULL,const char* userID = NULL,const char* userPsw = NULL);

		// virtual from ZThread
		// 核心线程
		virtual HRESULT Run(void *lpparam);

		// 接受Socks5消息
		int RecvSocks5Msg();
		// 是否是Socks5消息
		bool IsSocks5Msg();

		// 接受HTTP消息
		int RecvHTTPMsg();
		// 是否是HTTP消息
		bool IsHTTPMsg();

		HRESULT FindAddr(const char* strbase, const char* des, char* local, char* prot);

		bool IsIP(const char* str);
	private:
		ZSocketAddr		m_addrHost;
		ZSocketAddr		m_addrDest;
		char			m_userID[SOCKS5_ID_LEN];
		char			m_userPSW[SOCKS5_PSW_LEN];

		RecvData		m_recvDat;
		int				m_recvDatLen;
		int				m_socks5_State;

		_SOCKS_TYPE		m_socksType;
	};
};

#endif//_ZEPHYR_NET_2_TCP_CLIENT_PROXY_H