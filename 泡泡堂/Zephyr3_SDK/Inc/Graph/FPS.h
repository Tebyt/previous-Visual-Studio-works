#ifndef ZEPHYR_TIME_FPS_H
#define ZEPHYR_TIME_FPS_H

#include <windows.h>
#include <mmsystem.h>

class ZEPHYR_API ZephyrFPS{
private:
	int m_FrameTime;
	int m_PreTime;
	int m_Time;
public:
	inline ZephyrFPS();
	inline ~ZephyrFPS();

	void SetFPS(int fps);
	//判断是否要render这一帧，跳帧处理
	bool CheckRender();
	//限帧
	void Wait();
};

inline ZephyrFPS::ZephyrFPS()
{
	m_FrameTime=0;
	m_PreTime=0;
}

inline ZephyrFPS::~ZephyrFPS()
{
}

#endif