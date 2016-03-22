/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Download\Download.h

							Describe:	下载文件

							Author:		赵洪松(xueren)

							CreateTime: 2004.03.14
							UpdateTime:
*/

#ifndef _ZEPHYR_3_DOWNLOAD_H
#define _ZEPHYR_3_DOWNLOAD_H

#include <wininet.h>

#include <ZDebug.h>
#include <ZThread.h>
#include <ZString.h>
#include <ZApps.h>

namespace Zephyr3{

	class ZEPHYR_API DownloadFile{
		// 下载函数
		friend DWORD WINAPI _downloadfunc(LPVOID lpParam);
	public:
		enum{
			OPENFILE_OK			=	0x01,
			OPENFILE_FAIL		=	0x02,

			DOWNLOAD_PER		=	0x10,

			DOWNLOAD_FINISHED	=	0x20,

			DOWNLOAD_BEGIN		=	0x40,

			DOWNLOAD_FAIL		=	0x80
		};
	public:
		// 构造函数
		DownloadFile(HWND hWnd,DWORD dwMsg,ZThreadSystem& threadSystem) {

			//ZASSERT_R(OpenSession() == S_OK);

			m_fileHandle = NULL;

		 	m_connectSession = NULL;
		 	m_httpConnect = NULL;
		 	m_httpRequest = NULL;

			m_dstWnd = hWnd;
			m_dstMsg = dwMsg;

			m_filePoint = 0;
			m_fileLength = 0;

			m_downloadThread.SetThreadSystem(&threadSystem);

			m_bReady = false;

			m_bRunning = false;
		}

		virtual ~DownloadFile() { Exit(); }

		// 开始下载
		void Run(const char* url,const char* local);

		void Run(const char* url, const char* local, int point);

		// 中断下载
		void Exit();

		//! 中断下载，但并不等待线程结束，调用该函数以后，将不能释放本对象
		void _Exit();

		bool IsRunning() const { return m_bRunning; }

		const char* GetLocalName() const { return m_localName; }

		DWORD GetFileLength() const { return m_fileLength; }

		HRESULT DownloadFile::GetFileLength();

		DWORD GetCurFileLength() const { return m_filePoint; }
		// 打开对话
		static HRESULT OpenSession();
		// 关闭对话
		static void CloseSession();
		// 打开http连接
		 HRESULT OpenHttpConnect();
		// 打开HTTP请求
		 HRESULT OpenHttpRequest();

		 void CloseHttpHandle();
	private:
		// 虚函数，下载状态改变
		virtual void ChangeState(DWORD wParam,DWORD lParam) {}

		// 打开远程文件
		HRESULT OpenFile(const char* url);

		HRESULT OpenFile_http(const char* url);
		// 关闭远程文件
		void CloseFile();

		// 是否
		bool IsReady() const { return m_bReady; }

		// 发送消息
		void PostMsg(DWORD wParam,DWORD lParam) {

			if(m_dstWnd != NULL && m_dstMsg != NULL)
				PostMessage(m_dstWnd,m_dstMsg,wParam,lParam);
		}

		// 是否已经打开对话
		static bool IsOpenSession() { return m_fileSession != NULL; }

		// 实际的下载过程
		void Download();

		void Download_http();

		// 下载
		bool Download(BYTE* buf,DWORD size, DWORD& read);

		bool Download_http(BYTE* buf, DWORD size, DWORD& read);

		HRESULT DownLoad_http(BYTE* buf, DWORD want, DWORD cur, DWORD& size);
		// 分析网址
		void analyseHttp(const char* str, char* com, char* local);
	private:
		static HINTERNET	m_fileSession;
		 HINTERNET	m_connectSession;
		 HINTERNET	m_httpConnect;
		 HINTERNET	m_httpRequest;

		static char*		m_ComName;
		static char*		m_StationName;

		int					m_iReConnect;

		HANDLE				m_fileHandle;

		DWORD				m_filePoint;
		DWORD				m_fileLength;

		HWND				m_dstWnd;
		DWORD				m_dstMsg;

		ZThread				m_downloadThread;

		bool				m_bReady;

		StringEx<256>		m_urlName;
		StringEx<256>		m_localName;

		//char				m_ComName[256];
		//char				m_StationName[256];

		bool				m_bRunning;
	};

	typedef DownloadFile*	LPDownloadFile;
};

#endif	// _ZEPHYR_3_DOWNLOAD_H