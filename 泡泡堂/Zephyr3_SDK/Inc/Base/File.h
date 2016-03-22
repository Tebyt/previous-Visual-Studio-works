/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Base\File.h

							Describe:	文件操作

							Author:		赵洪松(xueren)

							CreateTime: 2003.04.16
							UpdateTime:
*/

#ifndef _ZEPHYR_3_BASE_FILE_H
#define _ZEPHYR_3_BASE_FILE_H

#include <Base\Assert.h>

namespace Zephyr3{

	///////////////////////////////////////////////////////////////////////
	// File

	// 检查文件是否存在
	bool ZEPHYR_3_API HasFile(const char* name);
	// 删除文件
	void ZEPHYR_3_API DelFile(const char* name);
	// 删除文件，支持通配符
	void ZEPHYR_3_API DelFileEx(const char* name);
	// 文件改名
	void ZEPHYR_3_API RenameFile(const char* src,const char* dst);

	///////////////////////////////////////////////////////////////////////
	// LocalFileImp

	class ZEPHYR_3_API LocalFileImp{
	public:
		enum{
			_READ		=	1,
			_WRITE		=	2,
			_READWRITE	=	3
		};

		enum{
			_SEEK_BEGIN	= 1,
			_SEEK_CUR	= 2,
			_SEEK_END	= 3
		};
	public:
		// 构造函数
		LocalFileImp() { m_hFile = NULL; }
		// 构造函数
		LocalFileImp(const char* name,DWORD mode) {

			m_hFile = NULL;

			ZASSERT_R(Open(name,mode) == S_OK);
		}
		// 析构函数
		~LocalFileImp() { Close(); }

		// 打开文件
		HRESULT Open(const char *filename,DWORD mode);
		// 关闭文件
		void Close();

		// 跳转
		ULONG Seek(long lOffset,int from) {

			ZASSERT(from == _SEEK_BEGIN || from == _SEEK_CUR || from == _SEEK_END);
			ZASSERT(IsOpen());

			return ::SetFilePointer(m_hFile,lOffset,NULL,(from == _SEEK_BEGIN ? FILE_BEGIN : (from == _SEEK_END ? FILE_END : FILE_CURRENT)));
		}

		// 获得现在的指针位置
		ULONG GetFilePointer() {
			ZASSERT(IsOpen());

			return ::SetFilePointer(m_hFile,0,NULL,FILE_CURRENT);
		}

		// 获得文件大小
		ULONG GetSize() {
			ZASSERT(IsOpen());

			return ::GetFileSize(m_hFile,NULL);
		}

		// 读
		ULONG Read(void *dst,ULONG length);
		// 写
		ULONG Write(const void *src,ULONG length);

		// 判断文件是否已经打开
		bool IsOpen() const { return m_hFile != NULL; }
	private:
		HANDLE		m_hFile;
	};


	typedef LocalFileImp	File;

	struct FileHead{
		DWORD	flag;		//标志
		DWORD	size;		//文件头大小
	};
};

#endif // _ZEPHYR_3_BASE_FILE_H