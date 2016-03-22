/*
							Zephyr Engine v3.0

								by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	Ani.h

							Describe:	动画支持

							Author:		赵洪松(xueren)

							CreateTime: 2003.07.3
							UpdateTime: 2003.08.29 -	更改结构，可以设置每一帧的时间，可以支持多文件源动画
														取消全局生成函数
														增加注释
*/

#ifndef _ZEPHYR_GRAPH_ANI_H
#define _ZEPHYR_GRAPH_ANI_H

#include <Graph\ZGraphDef.h>

///////////////////////////////////////////////////////////////////////////////////
//	ZAni

// 返回值
const HRESULT ZANI_END	=	0x80000000;	// 动画播放结束

class ZEPHYR_API ZAni{
	friend class ZAniPlayer;
public:
	struct Frame{
		DWORD		id;		// 源文件ID，ANI文件支持
		LPZSprite	spr;	// ZSprite
		DWORD		time;	// 每一帧的时间

		// 构造函数
		Frame() { spr = NULL; }
	};
protected:
	Frame		*m_Frames;	// 帧

	DWORD		m_dwMaxFrame;	// 最大帧数
	DWORD		m_dwCurFrame;	// 当前帧

	DWORD		m_dwOldTime;	// 上一帧显示的时间

	bool		m_bColorKey;	// 是否携带ColorKey

	bool		m_bEnd;			// 是否显示完成
public:
	// 构造函数
	inline ZAni();
	// 构造函数
	inline ZAni(const char *name,ZGraph *pGraph);
	// 析构函数
	~ZAni() { Release(); }

	// 初始化
	// 注：不通过读取ani文件时应该调用初始化函数
	HRESULT Init(DWORD dwMaxFrame);

	// 读取文件
	HRESULT Load(const char *filename,ZGraph *pGraph);

	// 保存为ani文件
	// 参数 -	filename 为目标文件，应该是.ani结尾
	//			nums 为源文件数量
	//			zpc 为源文件指针，如果多个源文件，之间用'\0'分隔
	void Save(const char *filename,DWORD nums,const char *zpc);

	// 在(x,y)处显示动画，只支持普通方式和ColorKey方式
	HRESULT Draw(long x, long y);

	void DrawEnd(long x, long y);

	// 在(x,y)处显示动画
	HRESULT Draw_alpha(long x, long y);

	void DrawEnd_alpha(long x, long y);

	// 行动
	HRESULT Action();

	// 强制变换为下一帧
	// 返回 -	如果为 ZANI_END 则代表动画已经显示完，返回第一帧
	HRESULT NextFrame();

	// 设置当前帧
	void SetFrame(DWORD index,LPZSprite lps,RECT &rect,DWORD time,DWORD id);

	// 是否使用ColorKey
	void UseColorKey(bool bUse) { m_bColorKey = bUse; }

	// 获得动画宽度
	inline DWORD GetWidth();
	// 获得动画高度
	inline DWORD GetHeight();

	// 获得最大帧数
	DWORD GetMaxFrames() { return m_dwMaxFrame; }

	// 获得指定帧数的图像
	inline LPZSprite GetSprite(DWORD index);
	// 获得当前帧 图像
	inline LPZSprite GetCurSprite();

	// 释放资源
	void Release();

	// IsEnd
	bool IsEnd() { return m_bEnd; }
};

// 构造函数
inline ZAni::ZAni()
{
	m_Frames = NULL;

	m_dwMaxFrame = 0;
	m_dwCurFrame = 0;

	m_dwOldTime = 0;

	m_bColorKey = false;

	m_bEnd = false;
}

// 构造函数
inline ZAni::ZAni(const char *name,ZGraph *pGraph)
{
	m_Frames = NULL;

	m_dwMaxFrame = 0;
	m_dwCurFrame = 0;

	m_dwOldTime = 0;

	m_bColorKey = false;

	Load(name,pGraph);
}

// 获得当前帧 图像
inline LPZSprite ZAni::GetCurSprite()
{
	ZASSERT(m_dwCurFrame < m_dwMaxFrame);
	ZASSERT(m_Frames != NULL);

	return m_Frames[m_dwCurFrame].spr;
}

// 获得动画宽度
inline DWORD ZAni::GetWidth()
{
	ZASSERT(m_dwCurFrame < m_dwMaxFrame);
	ZASSERT(m_Frames != NULL && m_Frames[m_dwCurFrame].spr != NULL);

	return m_Frames[m_dwCurFrame].spr->GetRectWidth();
}

// 获得动画高度
inline DWORD ZAni::GetHeight()
{
	ZASSERT(m_dwCurFrame < m_dwMaxFrame);
	ZASSERT(m_Frames != NULL && m_Frames[m_dwCurFrame].spr != NULL);

	return m_Frames[m_dwCurFrame].spr->GetRectHeight();
}

// 获得指定帧数的图像
inline LPZSprite ZAni::GetSprite(DWORD index)
{
	ZASSERT(index < m_dwMaxFrame);
	ZASSERT(m_Frames != NULL && m_Frames[index].spr != NULL);

	return m_Frames[index].spr;
}

typedef ZAni *		LPZAni;

#endif