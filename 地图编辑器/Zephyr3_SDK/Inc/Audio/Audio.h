/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Audio\Audio.h

							Describe:	音频 底层

							Author:		赵洪松(xueren)

							CreateTime: 2003.08.22
							UpdateTime:
*/

#ifndef _ZEPHYR_AUDIO_AUDIO_H
#define _ZEPHYR_AUDIO_AUDIO_H

#include <ZState.h>

class ZAudio;

///////////////////////////////////////////////////////////////////////////////////////////////////
// ZAudioObject
// 说明：音频基类，可以向上派生出Wave、MIDI、MP3等

// Play Mode
const DWORD ZAUDIO_LOOP		=	0x01;	// 循环播放
const DWORD	ZAUDIO_ONCE		=	0x02;	// 播放一次
const DWORD	ZAUDIO_WAIT		=	0x10;	// 如果该声音播放中，等待前一个声音结束
const DWORD ZAUDIO_AUTOREL	=	0x20;	// 播放完自动释放

// Stop Mode
const DWORD ZAUDIO_FORCE	=	0x100;	// 强制结束
const DWORD ZAUDIO_FALSE	=	0x200;	// 结束，内部调用！

// Audio Object State
const DWORD ZAUDIOOBJECT_PLAYING	=	0x02;	//播放中

class ZEPHYR_MEDIA_API ZAudioObject{
protected:
	ZState_DWord			m_dwState;

	ZAudio					*m_Audio;
public:
	// 构造函数
	ZAudioObject() { m_Audio = NULL; }
	// 析构函数
	virtual ~ZAudioObject() { ; }

	// 释放资源
	virtual void Release() = 0;

	// 播放
	virtual void Play(DWORD mode) = 0;
	// 停止
	virtual void Stop(DWORD mode) = 0;

	// 设置音量
	virtual void SetVolume(long lVolume) = 0;

	// 克隆
	virtual ZAudioObject *Clone() = 0;

	// 是否正在播放
	bool IsPlaying() { return m_dwState.Has(ZAUDIOOBJECT_PLAYING); }
protected:
	//设置 Audio
	void SetAudio(ZAudio *audio) { m_Audio = audio; }
};

///////////////////////////////////////////////////////////////////////////////////////////////////
// ZAudio
// 说明：音频系统基类

class ZEPHYR_MEDIA_API ZAudio{
public:
	// 缺省构造函数
	ZAudio() { ; }
	// 析构函数
	virtual ~ZAudio() { ; }

	// 读取Wave
	virtual ZAudioObject *LoadWave(const char *filename) = 0;
	// 读取MP3
	virtual ZAudioObject *LoadMP3(const char *filename) = 0;
	// 读取MIDI
	virtual ZAudioObject *LoadMIDI(const char *filename) = 0;

	// 设置整体音量
	virtual void SetVolume(long lVolume) = 0;

	// 释放 Object 资源
	virtual void ReleaseObject(ZAudioObject* &obj) = 0;
};

#endif//_ZEPHYR_AUDIO_AUDIO_H