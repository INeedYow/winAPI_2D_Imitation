#include "framework.h"
#include "CPlayer.h"
#include "CScene.h"

CPlayer::CPlayer()
{
	setPos(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
	setSize(fPoint(P_SIZE, P_SIZE));
	fSpeed = P_SPEED;
	//isDarkMode = false;
}

CPlayer::~CPlayer()
{
}

void CPlayer::update()
{
	fPoint playerPos = getPos();

	if (KEY_HOLD(VK_UP)		&& (playerPos.y - getSize().y / 2.f) > 0.f)		// 맵 탈출 방지
		playerPos.y -= fSpeed * DT;

	if (KEY_HOLD(VK_DOWN)	&& (playerPos.y + getSize().y / 2.f) < (float)WINSIZEY)
		playerPos.y += fSpeed * DT;

	if (KEY_HOLD(VK_LEFT)	&& (playerPos.x - getSize().x / 2.f) > 0.f)
		playerPos.x -= fSpeed * DT;

	if (KEY_HOLD(VK_RIGHT)	&& (playerPos.x + getSize().y / 2.f) < (float)WINSIZEX)
		playerPos.x += fSpeed * DT;

	// space 누르는 동안만 모드 전환
	if (KEY_ON(VK_SPACE))
		isDarkMode = true;
	if (KEY_OFF(VK_SPACE))
		isDarkMode = false;

	setPos(playerPos);
}

void CPlayer::render(HDC hDC)
{
	HPEN hPen = CreatePen(PS_SOLID, P_PEN, isDarkMode ? RGB(75, 125, 50) : RGB(125,150,100));
	HBRUSH hBrush = CreateSolidBrush(isDarkMode ? RGB(125, 200, 75) : RGB(150, 255, 100));

	HPEN hOriginalPen = (HPEN)SelectObject(hDC, hPen);
	HBRUSH hOriginalBrush = (HBRUSH)SelectObject(hDC, hBrush);

	Ellipse(hDC,
		(int)(getPos().x - getSize().x / 2),
		(int)(getPos().y - getSize().y / 2),
		(int)(getPos().x + getSize().x / 2),
		(int)(getPos().y + getSize().y / 2) );

	SelectObject(hDC, hOriginalPen);
	SelectObject(hDC, hOriginalBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);
}

//bool CPlayer::getIsMode()
//{
//	return isDarkMode;
//}
