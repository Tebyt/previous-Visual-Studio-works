/*
							Zephyr Engine v3.0

							by �Ժ���(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Net2\TCP_Client_Proxy.h

							Describe:	�ײ�TCP�ͻ��� ����

							Author:		�Ժ���(xueren)

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
		// ���캯��
		TCPClient_Proxy(LPMsgWorker pMsgWorker) 
			: TCPClient(pMsgWorker) 
			, m_socksType(_SOCKS_NONE)
		{

			m_userID[0] = '\0';
			m_userPSW[0] = '\0';

			m_socks5_State = 0;
		}
		// ��������
		virtual ~TCPClient_Proxy() {
			Release();
		}

		// ��ʼ���ͻ���
		HRESULT Init(ZSocketAddr& addr,_SOCKS_TYPE type = _SOCKS_NONE,const LPZSocketAddr pHost = NULL,const char* userID = NULL,const char* userPsw = NULL);

		// virtual from ZThread
		// �����߳�
		virtual HRESULT Run(void *lpparam);

		// ����Socks5��Ϣ
		int RecvSocks5Msg();
		// �Ƿ���Socks5��Ϣ
		bool IsSocks5Msg();

		// ����HTTP��Ϣ
		int RecvHTTPMsg();
		// �Ƿ���HTTP��Ϣ
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