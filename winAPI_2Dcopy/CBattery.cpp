#include "framework.h"
#include "CBattery.h"

CBattery::CBattery()
{
	m_fBattery = BAT_MAX;
	m_fAccel = 0.f;
	m_fDecel = 0.f;
	m_fBar = 0.f;
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
}

void CBattery::update()
{
	if (!ISMODE)
	{	// �þ� �� ���� 
 		if (m_fBattery < BAT_MAX)			// ���͸� Ǯ �ƴ� ����
		{
			m_fDecel = 0.f;
			m_fBattery += ((float)BAT_RECOVER * DT + m_fAccel * DT);

			if (m_fAccel < (float)BAT_ACCELMAX)	m_fAccel += 1.f * DT;				// ���ӵ� ����
			if (m_fAccel > (float)BAT_ACCELMAX)	m_fAccel = (float)BAT_ACCELMAX;		// ���ӵ� �ִ�ġ
		}
	}
	else 
	{	// �þ� �� ���� 
		if (m_fBattery > 0.f)				// ���͸� �ִ� ����
		{
			m_fAccel = 0.f;
			m_fBattery -= ((float)BAT_CONSUME * DT - m_fDecel * DT);				// ���� �Ӽ��� �Ҹ� �۾�����

      		if (m_fDecel < (float)BAT_DECELMAX)	m_fDecel += 1.f * DT;				// ���� ���
			if (m_fDecel > (float)BAT_DECELMAX)	m_fDecel = (float)BAT_DECELMAX;		// �ִ�ġ
		}
	}

	// �þ� ON OFF
	if (KEY_ON(VK_SPACE) && isEnough())
	{
		SETMODE(true);
		m_fBattery -= BAT_INITCONSUME;
	}
	else if (KEY_HOLD(VK_SPACE) && m_fBattery > 0 && ISMODE)	SETMODE(true);
	else														SETMODE(false);

	m_fBar = m_fBattery * BATBAR_MAX / BAT_MAX;			// ���͸� ��¹�
}

void CBattery::render(HDC hDC)
{
	// ���͸� ���ų� �ִ�� �� �׸�����
	if (1.f > m_fBar || m_fBar >= (float)BATBAR_MAX) return;

	fPoint pos = GETPOS;

	HPEN hPen, hOriginalPen;
	hPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 0));
	hOriginalPen = (HPEN)SelectObject(hDC, hPen);

	// ������ ���͸�
	MoveToEx(hDC, (int)pos.x - (int)O_HSIZE + 10, (int)pos.y + 27, nullptr);
	LineTo(hDC, (int)pos.x - (int)O_HSIZE + 10 + (int)m_fBar, (int)pos.y + 27);

	SelectObject(hDC, hOriginalPen);
	DeleteObject(hPen);
}

