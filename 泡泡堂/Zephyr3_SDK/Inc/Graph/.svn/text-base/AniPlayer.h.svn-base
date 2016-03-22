/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	AniPlayer.h

							Describe:	动画 播放支持

							Author:		赵洪松(xueren)

							CreateTime: 2003.08.29
							UpdateTime:
*/

#ifndef _ZEPHYR_GRAPH_ANI_PLAYER_H
#define _ZEPHYR_GRAPH_ANI_PLAYER_H

#include <Graph\Ani.h>

#include <ZLink.h>

///////////////////////////////////////////////////////////////////////////////////////////////////
// ZAniPlayer
// 说明：通过 ZAni 帧信息 来显示动画

class ZEPHYR_API ZAniPlayer{
protected:
	ZAni	*m_Data;		// ZAni
	
	DWORD	m_dwCurFrame;	// 当前帧

	DWORD	m_dwOldTime;	// 上一帧显示的时间

	long	m_x,m_y;
public:
	// 构造函数
	inline ZAniPlayer();
	// 析构函数
	~ZAniPlayer() { Release(); }

	// 在(m_x,m_y)处显示动画，只支持普通方式和ColorKey方式
	HRESULT Draw();

	// 行动
	HRESULT Action();

	// 强制变换为下一帧
	// 返回 -	如果为 ZANI_END 则代表动画已经显示完，返回第一帧
	HRESULT NextFrame();

	// 获得动画宽度
	inline DWORD GetWidth();
	// 获得动画高度
	inline DWORD GetHeight();

	// 获得最大帧数
	inline DWORD GetMaxFrames();

	// 获得当前帧 图像
	inline LPZSprite GetCurSprite();

	// 清空
	void Release();
};

// 构造函数
inline ZAniPlayer::ZAniPlayer()
{
	m_Data = NULL;

	m_dwCurFrame = m_dwOldTime = 0;
}

// 获得动画宽度
inline DWORD ZAniPlayer::GetWidth()
{
	ZASSERT(m_Data != NULL);

	return m_Data->GetWidth();
}

// 获得动画高度
inline DWORD ZAniPlayer::GetHeight()
{
	ZASSERT(m_Data != NULL);

	return m_Data->GetHeight();
}

// 获得最大帧数
inline DWORD ZAniPlayer::GetMaxFrames()
{
	ZASSERT(m_Data != NULL);

	return m_Data->GetMaxFrames();
}

// 获得当前帧 图像
inline LPZSprite ZAniPlayer::GetCurSprite()
{
	ZASSERT(m_Data != NULL);

	return m_Data->GetCurSprite();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// ZAniPlayerManager

class ZAniPlayerManager{
private:
	ZLinkEx<ZAniPlayer,64,32>	m_listLoop;	// 循环播放列表
	ZLinkEx<ZAniPlayer,64,32>	m_listOnce; // 普通播放列表
public:
	// 构造函数
	ZAniPlayerManager() { ; }
	// 虚构函数
	~ZAniPlayerManager() { Release(); }

	// 资源释放
	void Release();

	void PlayAni(long x,long y);
};

#endif//_ZEPHYR_GRAPH_ANI_PLAYER_H