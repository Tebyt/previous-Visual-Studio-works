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
	//�ж��Ƿ�Ҫrender��һ֡����֡����
	bool CheckRender();
	//��֡
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