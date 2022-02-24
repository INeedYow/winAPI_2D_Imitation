#include "framework.h"
#include "CMissile.h"

CMissile::CMissile()
{
	setPos(fPoint(0, 0));
	setSize(fPoint(25.f, 25.f));
	m_fSpeed = 250.f;
	setDir(fVec2(1.f, 1.f));
	m_gravity = 0.f;
}

CMissile::CMissile(fPoint pos, fPoint size, float spd, fVec2 dir)
{
	setPos(pos);
	setSize(size);
	m_fSpeed = spd;
	setDir(dir);
	m_gravity = 0.f;
}

CMissile::~CMissile()
{
}

void CMissile::update()
{
	fPoint missilePos = getPos();

	missilePos.x += m_fSpeed * m_fvDir.x * DT;
	missilePos.y += m_fSpeed * m_fvDir.y * DT + m_gravity * DT;
	if (m_gravity <= 2000)
		m_gravity += 200 * DT;
	setPos(missilePos);
}

void CMissile::render(HDC hDC)
{
	HPEN hPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
	HBRUSH hBrush = CreateSolidBrush(RGB(150, 150, 255));

	HPEN hOriginalPen = (HPEN)SelectObject(hDC, hPen);
	HBRUSH hOriginalBrush = (HBRUSH)SelectObject(hDC, hBrush);

	Ellipse(hDC,
		(int)(getPos().x - getSize().x / 2),
		(int)(getPos().y - getSize().y / 2),
		(int)(getPos().x + getSize().x / 2),
		(int)(getPos().y + getSize().y / 2));

	SelectObject(hDC, hOriginalPen);
	SelectObject(hDC, hOriginalBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);
}

void CMissile::setDir(fVec2 vec)
{
	m_fvDir = vec.normalize();
}
