#include "framework.h"
#include "CEnemy.h"

CEnemy::CEnemy()
{
	fSpeed		= 150;
	isDirUp		= true;
	centerPoint = fPoint((float)(WINSIZEX - 150), WINSIZEY / 2.f);
	fDistance	= 300.f;
	setPos(centerPoint);
	setSize(fPoint(200.f, 200.f));
}

CEnemy::CEnemy(fPoint pos, fPoint size, float spd, fPoint center, float dist, bool dir)
{
	setPos(pos);
	setSize(size);
	fSpeed = spd;
	centerPoint = center;
	fDistance = dist;
	isDirUp = dir;
}

CEnemy::~CEnemy()
{
}

void CEnemy::update()
{
	fPoint enemyPos = getPos();

	if (isDirUp)	// 위로 이동하는데
	{	// enemy 위쪽 y좌표가 이동범위 벗어나면
		if (enemyPos.y - (getSize().y / 2) <= centerPoint.y - fDistance)
			isDirUp = false;
		else
			enemyPos.y -= fSpeed * DT;
	}
	else			// 아래로 이동하는데
	{	// enemy 아래쪽 y좌표가 이동범위 벗어나면
		if (enemyPos.y + (getSize().y / 2) >= centerPoint.y + fDistance)
			isDirUp = true;
		else
			enemyPos.y += fSpeed * DT;
	}

	setPos(enemyPos);
}

void CEnemy::render(HDC hDC)
{
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
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
	DeleteObject(hBrush);
}
