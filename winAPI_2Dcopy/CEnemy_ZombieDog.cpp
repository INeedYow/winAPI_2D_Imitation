#include "framework.h"
#include "CEnemy_ZombieDog.h"

CEnemy_ZombieDog::CEnemy_ZombieDog()
{
	fSpeed = (float)EZD_SPEED;
	chaseMe();
	setRandPos((int)EZD_SIZE / 2);
	setSize(fPoint(EZD_SIZE, EZD_SIZE));
	fTimer = 0.f;
	wcGrrr = L"Grrr";
}

CEnemy_ZombieDog::~CEnemy_ZombieDog()
{
}


void CEnemy_ZombieDog::update()
{
	fPoint pos = getPos();

	// 맵 벗어나면 당시 플레이어 좌표로 방향 재설정
	if ((int)pos.x < 0 - (int)EZD_SIZE || (int)pos.x >(int)WINSIZEX + (int)EZD_SIZE ||
		(int)pos.y < 0 - (int)EZD_SIZE || (int)pos.y >(int)WINSIZEY + (int)EZD_SIZE)
	{
		chaseMe();
		fTimer = 0.f;								// 가속 초기화
	}

	pos.x += (EZD_SPEED + fTimer) * fvDir.x * DT;
	pos.y += (EZD_SPEED + fTimer) * fvDir.y * DT;

	fTimer += 20 * DT;			// 가속

	setPos(pos);
}

void CEnemy_ZombieDog::render(HDC hDC)
{
	fPoint pos = getPos();
	fPoint playerPos = GETPOS;

	int sight = ISMODE ? P_SIGHTON : P_SIGHTOFF;

	HPEN hPen, hOriginalPen;
	HBRUSH hBrush, hOriginalBrush;

	if (!pos.COLL_PC(pos, playerPos, sight))
	{
		if (ISSCAN)
		{	// 스캐너
			hPen = CreatePen(PS_SOLID, 1, RGB(200, 25, 25));
			hOriginalPen = (HPEN)SelectObject(hDC, hPen);
			Rectangle(hDC, pos.x - 1, pos.y - 1, pos.x + 1, pos.y + 1);
			SelectObject(hDC, hOriginalPen);
			DeleteObject(hPen);
		}
		return;
	}

	hPen = CreatePen(PS_SOLID, 1, RGB(200, 25, 25));
	hBrush = CreateSolidBrush(RGB(70, 10, 20));

	hOriginalPen = (HPEN)SelectObject(hDC, hPen);
	hOriginalBrush = (HBRUSH)SelectObject(hDC, hBrush);

	Ellipse(hDC,
		(int)(getPos().x - getSize().x / 2),
		(int)(getPos().y - getSize().y / 2),
		(int)(getPos().x + getSize().x / 2),
		(int)(getPos().y + getSize().y / 2));

	SelectObject(hDC, hOriginalPen);
	SelectObject(hDC, hOriginalBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);

	if ((int)fTimer % 60 < 20)
	{ // Grrr
		HFONT hFont = CreateFont(14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Comic Sans MS"));
		HFONT hOriginFont = (HFONT)SelectObject(hDC, hFont);

		SetTextColor(hDC, RGB(125, 25, 25));
		TextOutW(hDC, pos.x + 23, pos.y - 23, wcGrrr, wcslen(wcGrrr));

		SelectObject(hDC, hOriginFont);
		DeleteObject(hFont);
	}
}
