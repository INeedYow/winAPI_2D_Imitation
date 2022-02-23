#include "framework.h"
#include "CPlayer.h"

CPlayer::CPlayer()
{
	setPos(fPoint(100.f, WINSIZEY / 2.f));
	setSize(fPoint(75.f, 75.f));
	fSpeed = 200;
}

CPlayer::~CPlayer()
{
}

void CPlayer::update()
{
	fPoint playerPos = getPos();

	if (KEY_HOLD(VK_UP)		&& playerPos.y > 0.f)	// ∏  ≈ª√‚ πÊ¡ˆ
		playerPos.y -= fSpeed * DT;

	if (KEY_HOLD(VK_DOWN)	&& playerPos.y < (float)WINSIZEY)
		playerPos.y += fSpeed * DT;

	if (KEY_HOLD(VK_LEFT)	&& playerPos.x > 0.f)
		playerPos.x -= fSpeed * DT;

	if (KEY_HOLD(VK_RIGHT)	&& playerPos.x < (float)WINSIZEX)
		playerPos.x += fSpeed * DT;

	setPos(playerPos);
}

void CPlayer::render(HDC hDC)
{
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(100, 150, 100));
	HBRUSH hBrush = CreateSolidBrush(RGB(150, 200, 150));

	HPEN hOriginalPen = (HPEN)SelectObject(hDC, hPen);
	HBRUSH hOriginalBrush = (HBRUSH)SelectObject(hDC, hBrush);

	Rectangle(hDC,
		(int)(getPos().x - getSize().x / 2),
		(int)(getPos().y - getSize().y / 2),
		(int)(getPos().x + getSize().x / 2),
		(int)(getPos().y + getSize().y / 2) );

	SelectObject(hDC, hOriginalPen);
	SelectObject(hDC, hOriginalBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);
}
