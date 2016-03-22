/*
							Zephyr Engine v3.0

							by 赵洪松(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	GameEngine\WndBackEx.h

							Describe:	窗口背景

							Author:		赵洪松(xueren)

							CreateTime: 2006.05.20
							UpdateTime:
*/

#ifndef _ZEPHYR_WINDOWS_WNDBACKEX_H
#define _ZEPHYR_WINDOWS_WNDBACKEX_H

#include <Windows/WndBack.h>

/////////////////////////////////////////////////////////////////////////////////////////
// ZWndBack_Ex_MHZ
//! 9块背景，中间3块纵方向拉伸

class ZEPHYR_API ZWndBack_Ex_MHZ : public ZWndBack_Ex{
public:
	// 构造函数
	ZWndBack_Ex_MHZ(ZGraph *pGraph, const char *name) : ZWndBack_Ex(pGraph, name), m_sprMid(NULL) {}
	// 析构函数
	virtual ~ZWndBack_Ex_MHZ() { Release(); }

	// 更新
	virtual void Update(long w, long h);

	// 资源释放
	virtual void Release();
protected:
	//! 横向拼图
	void Build_H3(LPZSprite pDst, int x, int y, int w, int h, int iBegin);

	int GetMidHeight() const {
		if(m_sprSrc[3] != NULL)
			return m_sprSrc[3]->GetRectHeight();
		if(m_sprSrc[4] != NULL)
			return m_sprSrc[4]->GetRectHeight();
		if(m_sprSrc[5] != NULL)
			return m_sprSrc[5]->GetRectHeight();

		return 0;
	}
protected:
//	LPZSprite	m_sprSrc[9];
	LPZSprite	m_sprMid;
};

#endif // _ZEPHYR_WINDOWS_WNDBACKEX_H
