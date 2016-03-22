#ifndef ZEPHYR_STATE_H
#define ZEPHYR_STATE_H

#include <Zephyr.h>

#pragma pack (push)
#pragma pack (1)

template<class TYPE = BYTE>
class ZState{
private:
	TYPE	m_State;
public:
	ZState()	{ m_State = 0; }
	ZState(TYPE t)	{ m_State = t; }
	~ZState() { m_State = 0; }

	void Clear() { m_State = 0; }
	void Set(TYPE State) { m_State = State; }
	TYPE Get() const { return m_State; }
	TYPE GetWithMask(TYPE Mask) const { return m_State & Mask; }
	void Add(TYPE State) { m_State |= State; }
	void Sub(TYPE State) { m_State &= ~State; }
	bool Is(TYPE State) const { return m_State == State; }
	bool Has(TYPE State) const { return m_State & State; }

	ZState & operator = (const ZState &State) 
	{ 
		this->m_State = State.m_State;

		return *this; 
	}

	ZState & operator = (const TYPE State) 
	{ 
		this->m_State = State;

		return *this; 
	}

	bool operator == (const ZState &State) const
	{
		return this->m_State == State.m_State;
	}

	bool operator == (const TYPE State) const
	{
		return this->m_State == State;
	}

	ZState & operator += (const ZState &State)
	{
		this->Add(State.m_State);

		return *this;
	}
	ZState & operator += (const TYPE State)
	{
		this->Add(State);

		return *this;
	}

	ZState & operator -= (const ZState &State)
	{
		this->Sub(State.m_State);

		return *this;
	}

	ZState & operator -= (const TYPE State)
	{
		this->Sub(State);

		return *this;
	}
};

typedef ZState<BYTE>	ZState_Byte;
typedef ZState<WORD>	ZState_Word;
typedef ZState<DWORD>	ZState_DWord;

#pragma pack (pop)

#endif