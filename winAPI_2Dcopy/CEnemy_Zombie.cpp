#include "framework.h"
#include "CEnemy_Zombie.h"
#include "CCollider.h"

#include "SelectGDI.h"

CEnemy_Zombie::CEnemy_Zombie()
{
	setPos(fPoint(0.f, 0.f));
	fvDir = fVec2(0.f, 0.f);
	fSpeed = EZ_SPEEDMAX;
	fAttention = 0;
	fTimer = 0.f;
	isNotice = false;
	setSize(fPoint(EZ_SIZE, EZ_SIZE));
	isMove = false;
	strMsg = L"!";

	createCollider();
	getCollider()->setSize(fPoint(EZ_SIZE, EZ_SIZE));
	getCollider()->setOffset(fPoint((float)0, (float)0));
	getCollider()->setShape(SHAPE::CIRCLE);
}

CEnemy_Zombie::CEnemy_Zombie(fPoint pos, fVec2 dir)
{
	setPos(pos);
	fvDir = dir;
	setRandSpeed();
	fAttention = 0.f;
	fTimer = 0.f;
	isNotice = false;
	setSize(fPoint(EZ_SIZE, EZ_SIZE));
	isMove = false;
	strMsg = L"!";
}

CEnemy_Zombie::~CEnemy_Zombie()
{
}

void CEnemy_Zombie::setRandSpeed()
{
	int a = (int)g_resultTimer * 2;
	if (a > 30) a = 30;

	int spdMax = (int)EZ_SPEEDMAX + a;
	int spdMin = (int)EZ_SPEEDMIN + a;

	fSpeed = rand() % (spdMax - spdMin + 1) + spdMin;
}

void CEnemy_Zombie::update()
{
	fPoint pos = getPos();
	fPoint playerPos = GETPOS;

	int sight = ISMODE ? P_SIGHTON : P_SIGHTOFF;

	if (ISCOLLPC(pos, playerPos, sight))		// 시야 안에 있으면
	{
		if (fAttention <= 3.f)						
			fAttention += ISMODE ? 2 * DT : DT;		// 어그로 관리
		if (fAttention >= 2.f)
			isNotice = true;
	}
	else										// 시야 안에 없으면
	{
		if (fAttention > 0.f)
			fAttention -= DT;						// 어그로 관리
		if (fAttention <= 1.f)
			isNotice = false;
	}

	if (isNotice)								// 어그로 끌렸을 때 방향설정
	{
		fvDir.x = playerPos.x - pos.x;
		fvDir.y = playerPos.y - pos.y;
	}
	else										// 어그로 안 끌렸을 때 방향설정
	{
		fTimer -= DT;

		if (0.f > fTimer )							// 타이머 0되면 
		{
			if (isMove)									// 잠시 멈췄다가 또 움직이게
			{
				isMove = false;
				fTimer = rand() % 4 + 1;
				return;
			}

			setRandDir();								// 방향, 타이머 재설정
			fTimer = rand() % 3 + 2;

			if (0 == fvDir.x && 0 == fvDir.y)
				isMove = false;
			else		
				isMove = true;
		}
		else										// 타이머 남아있고
		{
			if (!isMove)	return;						// 움직임 없으면 return;
		}
	}

	if (0 != fvDir.x || 0 != fvDir.y)
		setDir(fvDir);
	pos.x += EZ_SPEEDMIN * fvDir.x * DT;
	pos.y += EZ_SPEEDMIN * fvDir.y * DT;

	setPos(pos);
}

void CEnemy_Zombie::render(HDC hDC)
{
	fPoint pos = getPos();
	fPoint playerPos = GETPOS;

	int sight = ISMODE ? P_SIGHTON : P_SIGHTOFF;

	SelectGDI pen(hDC, PEN::E_EDGE);
	SelectGDI brush(hDC, BRUSH::EZ_BRU);

	if (!ISCOLLPC(pos, playerPos, sight))
	{
		if (ISSCAN)			// 스캐너
			Rectangle(hDC, pos.x - 1, pos.y - 1, pos.x + 1, pos.y + 1);
		return;
	}

	Ellipse(hDC,
		(int)(getPos().x - getSize().x / 2),
		(int)(getPos().y - getSize().y / 2),
		(int)(getPos().x + getSize().x / 2),
		(int)(getPos().y + getSize().y / 2));

	if (isNotice)
	{
		SelectGDI font(hDC, FONT::COMIC24);

		SetTextColor(hDC, RGB(200, 150, 50));
		TextOutW(hDC, pos.x, pos.y - 20, strMsg, wcslen(strMsg));
	}
}
