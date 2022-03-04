#include "framework.h"
#include "CBattery.h"
#include "SelectGDI.h"

CBattery::CBattery()
{
	m_fBattery = (float)BAT_MAX;
	m_fAccel = 0.f;
	m_fDecel = 0.f;
	m_fBar = (UINT)BATBAR_MAX;
}

CBattery::~CBattery()
{
}

bool CBattery::isEnough()
{
	return (BAT_INITCONSUME <= m_fBattery);
}

float CBattery::getBattery()
{
	return m_fBattery;
}


void CBattery::setBattery(float batt)
{
	m_fBattery = batt;

	if (m_fBattery > (float)BAT_MAX)
		m_fBattery = (float)BAT_MAX;
	if (m_fBattery < 0.f)
		m_fBattery = 0.f;
}

void CBattery::update()
{
	if (!ISMODE)
	{	// 시야 끈 상태 
 		if (m_fBattery < BAT_MAX)			// 배터리 풀 아닌 상태
		{
			m_fDecel = 0.f;
			m_fBattery += BAT_RECOVER * fDT + m_fAccel * fDT;

			if (m_fAccel < (float)BAT_ACCELMAX)	m_fAccel += fDT;		// 가속도 증가
			if (m_fAccel > (float)BAT_ACCELMAX)	m_fAccel = (float)BAT_ACCELMAX;		// 가속도 최대치
		}
	}
	else 
	{	// 시야 켠 상태 
		if (m_fBattery > 0.f)				// 배터리 있는 상태
		{
			m_fAccel = 0.f;
			m_fBattery -= BAT_CONSUME * fDT - m_fDecel * fDT;				// 오래 켤수록 소모량 작아지게

      		if (m_fDecel < (float)BAT_DECELMAX)	m_fDecel += 2 * fDT;		// 연비 상승
			if (m_fDecel > (float)BAT_DECELMAX)	m_fDecel = BAT_DECELMAX;		// 최대치
		}
	}

	// 시야 ON OFF
	if (KEY_ON(VK_SPACE) && isEnough())
	{
		SETMODE(true);
		m_fBattery -= BAT_INITCONSUME;
	}
	else if (KEY_HOLD(VK_SPACE) && m_fBattery > 0 && ISMODE)	SETMODE(true);
	else														SETMODE(false);

	m_fBar = (UINT)(m_fBattery * BATBAR_MAX / BAT_MAX);			// 배터리 출력바
}

void CBattery::render(HDC hDC)
{
	// 배터리 없거나 최대면 안 그리도록
	if (0 == m_fBar || m_fBar >= (UINT)BATBAR_MAX) return;

	fPoint pos = GETPOS;

	SelectGDI pen(hDC, PEN::BAT_YELLOW);

	MoveToEx(hDC, (int)pos.x - (int)O_HSIZE + 10, (int)pos.y + 27, nullptr);
	LineTo(hDC, (int)pos.x - (int)O_HSIZE + 10 + (int)m_fBar, (int)pos.y + 27);

}

