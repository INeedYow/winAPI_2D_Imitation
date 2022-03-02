#include "framework.h"
#include "CEnemy_ZombieDog.h"
#include "CCollider.h"

#include "SelectGDI.h"

CEnemy_ZombieDog::CEnemy_ZombieDog()
{
	fSpeed = (float)EZD_SPEED;
	chaseMe();
	setRandPos((int)EZD_SIZE / 2);
	setSize(fPoint(EZD_SIZE, EZD_SIZE));
	fTimer = 0.f;
	strMsg = L"Grrr";

	createCollider();
	getCollider()->setSize(fPoint(EZD_SIZE - 2, EZD_SIZE - 2));
	getCollider()->setOffset(fPoint((float)0, (float)0));
	getCollider()->setShape(SHAPE::CIRCLE);
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

	SelectGDI pen(hDC, PEN::E_EDGE);
	SelectGDI brush(hDC, BRUSH::EZD_BRU);

	if (!pos.COLL_PC(pos, playerPos, sight))
	{
		if (ISSCAN)
			Rectangle(hDC, pos.x - 1, pos.y - 1, pos.x + 1, pos.y + 1);
		return;
	}

	Ellipse(hDC,
		(int)(getPos().x - getSize().x / 2),
		(int)(getPos().y - getSize().y / 2),
		(int)(getPos().x + getSize().x / 2),
		(int)(getPos().y + getSize().y / 2));

	if ((int)fTimer % 60 < 20)
	{	 // Grrr
		SelectGDI font(hDC, FONT::COMIC18);

		SetTextColor(hDC, RGB(125, 25, 25));
		TextOutW(hDC, pos.x + 23, pos.y - 23, strMsg, wcslen(strMsg));
	}
}
