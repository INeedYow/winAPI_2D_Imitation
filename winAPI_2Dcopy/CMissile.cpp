#include "framework.h"
#include "CMissile.h"

CMissile::CMissile()
{
	setPos(fPoint(0, 0));
	setSize(fPoint(0, 0));
	fSpeed = 1.f;
	dir = DIR::NONE;
}

CMissile::CMissile(fPoint pos, fPoint size, float spd, unsigned int _dir)
{
	setPos(pos);
	setSize(size);
	fSpeed = spd;
	dir = _dir;
}

CMissile::~CMissile()
{
}

void CMissile::update()
{
	fPoint missilePos = getPos();

	switch (dir)
	{
	case DIR::UP:
		missilePos.y -= fSpeed * DT;
		break;
	case DIR::DOWN:
		missilePos.y += fSpeed * DT;
		break;
	case DIR::LEFT:
		missilePos.x -= fSpeed * DT;
		break;
	case DIR::RIGHT:
		missilePos.x += fSpeed * DT;
		break;
	case DIR::LEFTUP:
		missilePos.y -= fSpeed * DT;
		missilePos.x -= fSpeed * DT;
		break;
	case DIR::RIGHTUP:
		missilePos.y -= fSpeed * DT;
		missilePos.x += fSpeed * DT;
		break;
	case DIR::RIGHTDOWN:
		missilePos.y += fSpeed * DT;
		missilePos.x += fSpeed * DT;
		break;
	case DIR::LEFTDOWN:
		missilePos.y += fSpeed * DT;
		missilePos.x -= fSpeed * DT;
		break;
	}

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

void CMissile::setDir(unsigned int _dir)
{
	dir = _dir;
}
