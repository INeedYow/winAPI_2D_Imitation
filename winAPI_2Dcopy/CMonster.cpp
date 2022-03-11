#include "framework.h"
#include "CMonster.h"


CMonster::CMonster()
{
	m_ucState = 0;
}

CMonster::~CMonster()
{
}

UCHAR CMonster::getState()
{
	return m_ucState;
}

void CMonster::setStateTrue(UCHAR state)
{
	m_ucState |= state;
}

void CMonster::setStateFalse(UCHAR state)
{
	m_ucState &= (~state);
}

bool CMonster::isState(UCHAR state)
{
	return m_ucState & state;
}
