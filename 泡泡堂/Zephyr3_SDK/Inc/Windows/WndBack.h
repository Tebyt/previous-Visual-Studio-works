/*
							Zephyr Engine v3.0

								by �Ժ���(xueren) 2002 - 2003


							http://www.FlyingMagic.com
							E-mail:sssxueren@sina.com

							FileName:	GameEngine\WndBack.h

							Describe:	���ڱ���

							Author:		�Ժ���(xueren)

							CreateTime: 2003.09.24
							UpdateTime:
*/

#ifndef _ZEPHYR_WINDOWS_WNDBACK_H
#define _ZEPHYR_WINDOWS_WNDBACK_H

#include <Graph\ZGraph.h>

/////////////////////////////////////////////////////////////////////////////////////////
// ZWndBack

class ZEPHYR_API ZWndBack{
protected:
	LPZSprite	m_sprBack;
	ZGraph		*m_Graph;
public:
	// ���캯��
	inline ZWndBack(ZGraph *pGraph);
	// ��������
	virtual ~ZWndBack() { Release(); }

	// ��ȡ�ⲿ���ýű�
	virtual void Load(const char *name) = 0;

	// ����
	void Create(long w,long h,ZEPHYR_COLOR_MODE zcm,DWORD flag);
	// ����
	virtual void Update(long w,long h) = 0;
	// �������
	LPZSprite GetData() { return m_sprBack; }

	// ��� ������ �߶�
	virtual long GetTitleHeight() { return 0; }
	// ��� ��߿� ���
	virtual long GetLBorderWidth() { return 0; }
	// ��� �ұ߿� ���
	virtual long GetRBorderWidth() { return 0; }
	// ��� �±߿� �߶�
	virtual long GetDBorderHeight() { return 0; }

	// ��� ������ �߶�
	virtual long GetTitleHeight_noColorKey() { return 0; }
	// ��� ��߿� ���
	virtual long GetLBorderWidth_noColorKey() { return 0; }
	// ��� �ұ߿� ���
	virtual long GetRBorderWidth_noColorKey() { return 0; }
	// ��� �±߿� �߶�
	virtual long GetDBorderHeight_noColorKey() { return 0; }
	// ��Դ�ͷ�
	virtual void Release();
protected:
	// ���´�С
	void Resize(long w,long h);
};

// ���캯��
inline ZWndBack::ZWndBack(ZGraph *pGraph) 
{ 
	ZASSERT(pGraph != NULL);

	m_sprBack = NULL; 

	m_Graph = pGraph;
}

/////////////////////////////////////////////////////////////////////////////////////////
// ZWndBack_Ex

class ZEPHYR_API ZWndBack_Ex : public ZWndBack{
protected:
	LPZSprite	m_sprSrc[9];
public:
	// ���캯��
	inline ZWndBack_Ex(ZGraph *pGraph,const char *name);
	// ��������
	virtual ~ZWndBack_Ex() { Release(); }

	// ��ȡ�ⲿ���ýű�
	virtual void Load(const char *name);
	// ����
	virtual void Update(long w,long h);
	// ��� ������ �߶�
	virtual long GetTitleHeight();
	// ��� ��߿� ���
	virtual long GetLBorderWidth();
	// ��� �ұ߿� ���
	virtual long GetRBorderWidth();
	// ��� �±߿� �߶�
	virtual long GetDBorderHeight();

	// ��� ������ �߶�
	virtual long GetTitleHeight_noColorKey();
	// ��� ��߿� ���
	virtual long GetLBorderWidth_noColorKey();
	// ��� �ұ߿� ���
	virtual long GetRBorderWidth_noColorKey();
	// ��� �±߿� �߶�
	virtual long GetDBorderHeight_noColorKey();

	// ��Դ�ͷ�
	virtual void Release();
};

inline ZWndBack_Ex::ZWndBack_Ex(ZGraph *pGraph,const char *name) : ZWndBack(pGraph)
{
	for(int i = 0; i < 9; i++)
		m_sprSrc[i] = NULL;

	Load(name);
}

/////////////////////////////////////////////////////////////////////////////////////////
// ZWndBack_Ex2

class ZEPHYR_API ZWndBack_Ex2 :public ZWndBack{
protected:
	LPZSprite	m_sprSrc;
public:
	// ���캯��
	inline ZWndBack_Ex2(ZGraph *pGraph,const char *name);
	// ��������
	virtual ~ZWndBack_Ex2() { Release(); }

	// ��ȡ�ⲿ���ýű�
	virtual void Load(const char *name);
	// ����
	virtual void Update(long w,long h);

	// ��Դ�ͷ�
	virtual void Release();
};

// ���캯��
inline ZWndBack_Ex2::ZWndBack_Ex2(ZGraph *pGraph,const char *name) : ZWndBack(pGraph)
{ 
	ZASSERT(pGraph != NULL);
	ZASSERT(name != NULL);

	m_sprSrc = NULL;

	Load(name);
}

#endif//_ZEPHYR_WINDOWS_WNDBACK_H