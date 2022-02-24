#include "framework.h"
#include "CEnemy.h"

CEnemy::CEnemy()
{
	fSpeed		= E_SPEED;
	isPattern	= false;
	isDir		= false;
	setPos(fPoint(0,0));
	setSize(fPoint(O_SIZE, O_SIZE));
}

CEnemy::CEnemy(bool pattern, bool dir, float spd)
{
	isPattern = pattern;
	isDir = dir;
	fSpeed = spd;
}



CEnemy::~CEnemy()
{
}


void CEnemy::update()
{
	
}

void CEnemy::render(HDC hDC)
{
	/*HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HBRUSH hBrush = CreateSolidBrush(RGB(50, 50, 50));

	HPEN hOriginalPen = (HPEN)SelectObject(hDC, hPen);
	HBRUSH hOriginalBrush = (HBRUSH)SelectObject(hDC, hBrush);

	Rectangle(hDC,
		(int)(getPos().x - getSize().x / 2),
		(int)(getPos().y - getSize().y / 2),
		(int)(getPos().x + getSize().x / 2),
		(int)(getPos().y + getSize().y / 2));

	SelectObject(hDC, hOriginalPen);
	SelectObject(hDC, hOriginalBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);*/
}
