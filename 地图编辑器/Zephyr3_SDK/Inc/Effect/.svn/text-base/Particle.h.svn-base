// Effect\Particle.h
// СЃзг
// Write by zhs007			y2k3-6-27

#include <ZDebug.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	ZParticle

class ZParticle{
protected:
	BYTE	m_Life;
	BYTE	m_Size;
	BYTE	m_Light;

	long	m_x,m_y;
public:
	inline ZParticle();
	virtual ~ZParticle() { ; }

	inline void Init(BYTE life,BYTE size,BYTE light,long x,long y);

	virtual void Action() = 0;

	BYTE GetSize() { return m_Size; }
	BYTE GetLight() { return m_Light; }
	BYTE GetLife() { return m_Life; }

	long GetX() { return m_x; }
	long GetY() { return m_y; }

	void SetXY(long x,long y) { m_x = x, m_y = y; }
};

inline ZParticle::ZParticle()
{
	m_Life = m_Size = m_Light = 0;

	m_x = m_y = 0;
}

inline void ZParticle::Init(BYTE life,BYTE size,BYTE light,long x,long y)
{
	m_Life= life;
	m_Size = size;
	m_Light = light;

	m_x = x;
	m_y = y;
}