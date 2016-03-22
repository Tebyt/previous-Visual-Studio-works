/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	ZFile.h

							Describe:	底层文件系统

							Author:		赵洪松(xueren)

							CreateTime: 2002.3
							UpdateTime: 2003.08.21
*/

#ifndef _ZEPHYR_FILE_H
#define _ZEPHYR_FILE_H

#include <Zephyr.h>

#include <windows.h>
#include <wininet.h>

#include <zdebug.h>
#include <zlink.h>

//统一的文件头
struct ZephyrFileHead{
	DWORD	flag;		//标志
	DWORD	size;		//文件头大小
};

enum ZFILE_SEEKFROM{
	ZFILE_SEEK_BEGIN = 1,
	ZFILE_SEEK_CUR,
	ZFILE_SEEK_END
};

//////////////////////////////////////////////////////////////////////
// ZFileImp
// 说明：实际的文件操作接口
//		桥接 模式

class ZFileImp{
public:
	ZFileImp() { ; }
	virtual ~ZFileImp() { ; }

	virtual HRESULT Open(const char *filename,DWORD mode) = 0;
	virtual void Close() = 0;

	virtual ULONG Seek(long lOffset,ZFILE_SEEKFROM from) = 0;

	virtual ULONG GetFilePointer() = 0;

	virtual ULONG GetSize() = 0;

	virtual ULONG Read(void *dst,ULONG length) = 0;
	virtual ULONG Write(const void *src,ULONG length) = 0;

	virtual bool IsOpen() = 0;
};

//////////////////////////////////////////////////////////////////////
// ZLocalFileImp
// 说明：实际的文件操作接口
//		桥接 模式

class ZLocalFileImp : public ZFileImp{
private:
	HANDLE		m_hFile;
public:
	ZLocalFileImp() { m_hFile = NULL; }
	virtual ~ZLocalFileImp() { Close(); }

	virtual HRESULT Open(const char *filename,DWORD mode);
	virtual void Close();

	virtual ULONG Seek(long lOffset,ZFILE_SEEKFROM from);

	virtual ULONG GetFilePointer();

	virtual ULONG GetSize();

	virtual ULONG Read(void *dst,ULONG length);
	virtual ULONG Write(const void *src,ULONG length);

	virtual bool IsOpen();
};

//////////////////////////////////////////////////////////////////////
//	ZFile

//open mode
const DWORD	ZFILE_READ		=	1;
const DWORD	ZFILE_WRITE		=	2;
const DWORD	ZFILE_READWRITE	=	3;

class ZEPHYR_API ZFile{
private:
	ZFileImp	*m_File;
public:
	ZFile() { m_File = NULL; }
	~ZFile() { Close(); }

	HRESULT	Open(const char* filename,DWORD mode);
	void Close();

	inline ULONG Seek(long lOffset,ZFILE_SEEKFROM From);

	inline ULONG GetFilePointer();

	inline ULONG GetSize();

	inline ULONG Read(void *dst,ULONG length);
	inline ULONG Write(const void *src,ULONG length);

	bool IsOpen() const { return m_File == NULL ? false : m_File->IsOpen(); }
};

inline ULONG ZFile::Seek(long lOffset,ZFILE_SEEKFROM From)
{
	ZASSERT(m_File != NULL);

	return m_File->Seek(lOffset,From);
}

inline ULONG ZFile::GetFilePointer()
{
	ZASSERT(m_File != NULL);

	return m_File->GetFilePointer();
}

inline ULONG ZFile::GetSize()
{
	ZASSERT(m_File != NULL);

	return m_File->GetSize();
}

inline ULONG ZFile::Read(void *dst,ULONG length)
{
	ZASSERT(m_File != NULL);

	return m_File->Read(dst,length);
}

inline ULONG ZFile::Write(const void *src,ULONG length)
{
	ZASSERT(m_File != NULL);

	return m_File->Write(src,length);
}

/*
//////////////////////////////////////////////////////////////////////
//	memoryFile

class ZEPHYR_API memoryFile{
private:
	char* m_fileName;
	DWORD m_nameLen;
	DWORD m_dataLen;
	void* m_data;
	DWORD m_off;
	DWORD m_buffLen;
public:
	inline memoryFile();
	inline ~memoryFile();

	void Release();

	inline void SetLength(DWORD len);
	inline DWORD GetLength() const;

	inline void Read(void* dst,DWORD &len);
	inline void Write(void* src,DWORD &len);

	inline void SetOffset(DWORD off);
	inline DWORD GetOffset() const;

	void SetName(const char* name);
	inline const char* GetName() const;

	void RequestNameBuff(DWORD len);
	HRESULT CreateBuff(DWORD len);

	DWORD Seek(long off,enum ZFILE_SEEKFROM seek);

	inline void Clear();

	inline void* GetData() const;
};

inline memoryFile::memoryFile()
{
	m_fileName=NULL;
	m_data=NULL;
	m_nameLen=m_dataLen=m_off=m_buffLen=0;

	RequestNameBuff(256);
}

inline memoryFile::~memoryFile()
{
	Release();
}

inline void memoryFile::Clear()
{
	m_dataLen=m_off=0;
}

inline void memoryFile::SetLength(DWORD len)
{
	m_dataLen=len;
}

inline DWORD memoryFile::GetLength() const
{
	return m_dataLen;
}

inline void memoryFile::SetOffset(DWORD off)
{
	m_off=off;
}

inline DWORD memoryFile::GetOffset() const
{
	return m_off;
}

inline void memoryFile::Read(void* dst,DWORD &len)
{
	if(len+m_off>m_dataLen)
		len=m_dataLen-m_off;

	memcpy(dst,(char*)m_data+m_off,len);

	m_off+=len;
}

inline void memoryFile::Write(void* src,DWORD &len)
{
	if(len+m_off>m_buffLen)
		len=m_buffLen-m_off;

	memcpy((char*)m_data+m_off,src,len);

	m_off+=len;

	m_dataLen+=len;
}

inline const char* memoryFile::GetName() const
{
	return m_fileName;
}

inline void* memoryFile::GetData() const
{
	return ((char*)m_data)+m_off;
}

//////////////////////////////////////////////////////////////////////
//	memoryFileSystem

class ZEPHYR_API memoryFileSystem{
private:
	ZLinkEx<memoryFile,32,4> m_link;
public:
	inline memoryFileSystem();
	inline ~memoryFileSystem();

	void Release();

	memoryFile* GetMemoryFile(const char* name);
	memoryFile* NewMemoryFile(const char* name,DWORD length);

	inline void Delete(memoryFile* file);
};

inline memoryFileSystem::memoryFileSystem()
{
}

inline memoryFileSystem::~memoryFileSystem()
{
	Release();
}

inline void memoryFileSystem::Delete(memoryFile* file)
{
	file->Clear();
	m_link.Del(file);
}
//////////////////////////////////////////////////////////////////////
//	ZFile

//zfile state

//	    低8位(BYTE)表示目前读取情况，通常可以switch((BYTE)state)来分开处
//	理，而不用一个一个的&判断。

const DWORD ZFILE_STATE_INTERNETOPEN	=0x01;	//internet open file
const DWORD ZFILE_STATE_MEMORYOPEN		=0x02;	//memory open file


//open mode
#define	ZFILE_READ		1
#define	ZFILE_WRITE		2
#define	ZFILE_READWRITE	3

class ZEPHYR_API ZFile{
public:
	static HRESULT OpenSession();
	static void CloseSession();

	static HRESULT _http_connect(const char* server);
	static void _disconnect();

	static void SetMemoryFile(memoryFile *file);
private:
	static DWORD		_curState;
	static HINTERNET	_fileSession;
	static HINTERNET	_connectSession;
	static memoryFile	*_file;
//	static BYTE*		_fileBuff;
//	static DWORD		_fileBuffSize;

	void*	m_fileHandle;
	ULONG	m_filePointer;
	DWORD	m_dwState;
public:
	inline ZFile();
	inline ~ZFile();

	HRESULT	Open(const char* filename,DWORD mode,DWORD flag=_curState);
	void Close();

	ULONG Seek(long lOffset,ZFILE_SEEKFROM From);

	inline ULONG GetFilePointer();

	ULONG GetFileSize();

	ULONG Read(void *dst,ULONG length);
	ULONG Write(void *src,ULONG length);

	void RequestSize(DWORD size);

	inline bool	IsOpen() const;

	inline void SetState(DWORD state);
	inline DWORD GetState() const;

	inline memoryFile* GetMemoryFile() const;
//	inline memoryFileSystem* GetMemoryFileSystem() const;

//	inline void CreateMemoryFileSystem();
private:
	HRESULT _http_openfile(const char* filename);
};

inline ZFile::ZFile()
{
	m_fileHandle=0;
	m_filePointer=0;
	m_dwState=0;
}

inline ZFile::~ZFile()	
{
	Close();
}

inline bool ZFile::IsOpen()	const
{	
	return m_fileHandle!=NULL;
}

inline ULONG ZFile::GetFilePointer()	
{	
	ZASSERT(IsOpen());

	Seek(0,ZFILE_SEEK_CUR);

	return m_filePointer;	
}

inline void ZFile::SetState(DWORD state)
{
	_curState=state;
}

inline DWORD ZFile::GetState() const
{
	return _curState;
}

inline memoryFile* ZFile::GetMemoryFile() const
{
	if(m_dwState&ZFILE_STATE_MEMORYOPEN)
		return (memoryFile*)m_fileHandle;

	return NULL;
}
*/
#endif//_ZEPHYR_FILE_H