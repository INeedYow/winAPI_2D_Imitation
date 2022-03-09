#include "framework.h"
#include "CMonster.h"


CMonster::CMonster()
{
	m_ucState = 0;
	//m_fTimer = 0.f;
}

CMonster::~CMonster()
{
}

//void CMonster::setTimer(float time)
//{
//	m_fTimer = time;
//}
//
//float CMonster::getTimer()
//{
//	return m_fTimer;
//}

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
