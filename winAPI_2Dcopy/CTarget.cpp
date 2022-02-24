#include "framework.h"
#include "CTarget.h"

CTarget::CTarget()
{
	setPos(fPoint(-1, -1));
	setSize(fPoint(0, 0));
}

CTarget::CTarget(fPoint pos)
{
	setPos(pos);
	setSize(fPoint((float)O_SIZE, (float)O_SIZE));
}

CTarget::~CTarget()
{
}

void CTarget::update()
{
}

void CTarget::render(HDC hDC)
{
	// 아마도 노란색 rect
	HPEN hPen = CreatePen(PS_SOLID, P_PEN, RGB(0, 0, 0));
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 50));

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
