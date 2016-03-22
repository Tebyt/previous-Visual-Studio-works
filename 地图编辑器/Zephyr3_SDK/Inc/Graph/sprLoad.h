#ifndef ZEPHYR_SPRITE_LOAD_H
#define ZEPHYR_SPRITE_LOAD_H

#include <ZThread.h>
#include <ZFile.h>
#include <WndMsg.h>
#include <Graph\BaseDef.h>
#include <Graph\ZSprite.h>

class ZGraph;

//////////////////////////////////////////////////////////////////////
//	sprLoad

struct sprloadData{
	char filename[256];
	ZEPHYR_COLOR_MODE zcm;
	DWORD flag;
	LPSPRITE_DATA	lps;
	bool bLoad;
	long w,h;

	sprloadData()
	{
		lps=NULL;
		filename[0]='\0';
		bLoad=false;
		w=h=0;
	}

	inline bool operator==(const sprloadData &s) const;

	inline bool operator!=(const sprloadData &s) const;
};

inline bool sprloadData::operator==(const sprloadData &s) const
{
	return strcmp(filename,s.filename)==0&&zcm==s.zcm;
}

inline bool sprloadData::operator!=(const sprloadData &s) const 
{ 
	return !((*this)==s); 
}

class sprLoad : public ZThread{
private:
	ZCriticalSection	m_cacheLock;
	ZLinkEx<sprloadData,128,128>	m_cacheData;

	ZCriticalSection	m_runLock;
	sprloadData*	m_pWorking;
	void*			m_pCur;

//	memoryFileSystem	m_memfileSys;

	ZGraph*	m_Graph;

	HWND	m_dstWnd;
	HWND	m_viewWnd;

	ZFile	m_file;
	ZFile	m_netFile;

	DWORD	m_fileLength;
	DWORD	m_curLength;

	LPZSprite	m_spr;

	DWORD	m_workNums;
	DWORD	m_workCur;
	DWORD	m_MustFinish;
public:
	inline sprLoad();
	virtual ~sprLoad();

	void Release();

	void LoadToCache(const char* filename,ZEPHYR_COLOR_MODE zcm,DWORD flag,long w,long h);
	void DelInCache(const char* filename,ZEPHYR_COLOR_MODE zcm,DWORD flag);

	void Load(LPZSprite &lps,const char* filename,ZEPHYR_COLOR_MODE zcm,DWORD flag);

	inline void SetHWND(HWND hWnd);
	inline void SetView(HWND hWnd);
	inline void SetGraph(ZGraph* graph);

	void Work();

	inline void Finish();
	inline void WorkEnd();
	inline void CanRun();
	inline void LoadingMsg(DWORD len,DWORD max);

	void RequestSpr(long w,long h);
	void RequestBuff(DWORD len);

	inline void SetMustLoad(DWORD nums);

	inline void RequestFileSize(DWORD length);
	HRESULT LoadFile();
	HRESULT OpenFile();
	void CloseFile();

	// Õ∑≈cache
	void Cleanup();

	HRESULT Init();
//virtual from zthread
	HRESULT Run(void* lpParam);

protected:
	sprloadData* FindInCache(const char* filename,ZEPHYR_COLOR_MODE zcm,DWORD flag);

	void NextWork();
};

inline sprLoad::sprLoad()
{
	m_Graph=NULL;
	m_pWorking=NULL;
	m_pCur=NULL;

	m_spr=NULL;

	m_workNums=m_workCur=m_MustFinish=0;

	m_viewWnd=m_dstWnd=NULL;
}

inline void sprLoad::Finish()
{
	PostMessage(m_dstWnd,WM_ZEPHYR_LOAD_FINISH,0,0);
}

inline void sprLoad::WorkEnd()
{
	PostMessage(m_dstWnd,WM_ZEPHYR_LOAD_WORKEND,0,0);
}

inline void sprLoad::CanRun()
{
	PostMessage(m_dstWnd,WM_ZEPHYR_LOAD_CANRUN,0,0);
}

inline void sprLoad::LoadingMsg(DWORD len,DWORD max)
{
	PostMessage(m_viewWnd,WM_ZEPHYR_LOAD_LOADING,len,max);
}

inline void sprLoad::SetHWND(HWND hWnd)
{
	m_dstWnd=hWnd;
}

inline void sprLoad::SetView(HWND hWnd)
{
	m_viewWnd=hWnd;
}

inline void sprLoad::SetGraph(ZGraph* graph)
{
	m_Graph=graph;
}

inline void sprLoad::RequestFileSize(DWORD length)
{
//	m_file.RequestSize(length);
}

inline void sprLoad::SetMustLoad(DWORD nums)
{
	m_MustFinish=nums;
}

#endif