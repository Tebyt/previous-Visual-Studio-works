/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Audio\DSWave.h

							Describe:	使用 DirectSound 播放 Wave

							Author:		赵洪松(xueren)

							CreateTime: 2003.08.22
							UpdateTime:
*/

#ifndef _ZEPHYR_AUDIO_DSWAVE_H
#define _ZEPHYR_AUDIO_DSWAVE_H

#include <Audio\Audio.h>

#include <stdarg.h>
#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <dsound.h>

#include <ZLink.h>
#include <ZThread.h>
#include <ZState.h>

///////////////////////////////////////////////////////////////////////////////////////////////////
// ZAudioWave_DS
// 说明：Direct Sound 支持的 Wave

// ZAudioWave_DS 特有的 State
const DWORD	ZAUDIOWAVE_DS_TEMP		=	0x00100000;	//临时音频，播放完一次就释放掉

class ZEPHYR_MEDIA_API ZAudioWave_DS : public ZAudioObject{
	friend class ZAudio_DS;
	friend DWORD WINAPI _dsound_func(void *param);
private:
	LPDIRECTSOUNDBUFFER	m_Buf;
	LPDIRECTSOUNDNOTIFY	m_Notify;
	HANDLE					m_hEvent;
	int						m_iNums;
public:
	// 构造函数
	inline ZAudioWave_DS();
	// 析构函数
	virtual ~ZAudioWave_DS() { Release(); }

	// 释放资源
	virtual void Release();

	// 播放
	virtual void Play(DWORD mode);
	// 停止
	virtual void Stop(DWORD mode);

	// 设置音量
	virtual void SetVolume(long lVolume);

	// 克隆
	virtual ZAudioObject *Clone();
private:
	// 是否是临时音频
	bool IsTemp() { return m_dwState.Has(ZAUDIOWAVE_DS_TEMP); }

	// Get Event
	HANDLE GetEvent() { return m_hEvent; }

	// 获得播放次数
	DWORD GetNums() { return m_iNums; }
};

// 构造函数
inline ZAudioWave_DS::ZAudioWave_DS()
{
	m_Buf = NULL;
	m_Notify = NULL;
	m_hEvent = NULL;
	m_iNums = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// ZAudio_DS
// 说明：使用 DirectSound 来构建 ZAudio，只支持 Wave

class ZEPHYR_MEDIA_API ZAudio_DS : public ZAudio{
	friend class ZAudioWave_DS;
	friend DWORD WINAPI _dsound_func(void *param);
private:
	HWND							m_hWnd;			// 主窗口

	LPDIRECTSOUND8					m_lpDS;			// DS
	LPDIRECTSOUNDBUFFER				m_lpDSBPrimary;	// 主缓冲

	ZThread							m_Thread;		// 后台线程

	ZLinkEx<ZAudioWave_DS,256,16>	m_linkBuf;		// ZAudioWave_DS 列表
	ZCriticalSection				m_linkLock;		// 列表锁
public:
	// 缺省构造函数
	ZAudio_DS() { 
		m_lpDS = NULL;
		m_lpDSBPrimary = NULL;
	}
	// 析构函数
	virtual ~ZAudio_DS() { Release(); }

	// 初始化
	HRESULT Init(HWND hWnd,ZThreadSystem *pThreadSystem);

	// 读取Wave
	virtual ZAudioObject *LoadWave(const char *filename);
	// 读取MP3
	virtual ZAudioObject *LoadMP3(const char *filename) { return NULL; }
	// 读取MIDI
	virtual ZAudioObject *LoadMIDI(const char *filename) { return NULL; }

	// 设置整体音量
	virtual void SetVolume(long lVolume);

	// 释放 Object 资源
	virtual void ReleaseObject(ZAudioObject* &obj);

	// 资源释放
	void Release();
private:
	// 锁定
	void Lock() { m_linkLock.Lock(); }
	// 解锁
	void Unlock() {m_linkLock.Unlock(); }

	// 获得Event
	int GetEvents(HANDLE *event);
	// 获得线程
	ZThread *GetThread() { return &m_Thread; }
	// 查找 Wave
	ZAudioWave_DS *FindBuff(HANDLE event);

	// 释放 ZAudioWave_DS 链表资源
	void CleanUp();

	// 创建 DirectSound Buffer
	LPDIRECTSOUNDBUFFER CreateBuff(DWORD size,WAVEFORMATEX &wf);
	// 写数据到 SirectSound Buffer
	HRESULT WriteDataToBuffer(LPDIRECTSOUNDBUFFER lpDSB,DWORD dwOffset,BYTE *lpbSoundData,DWORD dwSoundBytes);

	// 复制生成Obj
	ZAudioWave_DS *Clone(ZAudioWave_DS *src);
	// 复制生成 DirectSound Buffer
	LPDIRECTSOUNDBUFFER Clone(LPDIRECTSOUNDBUFFER src);
};

#endif//_ZEPHYR_AUDIO_DSWAVE_H