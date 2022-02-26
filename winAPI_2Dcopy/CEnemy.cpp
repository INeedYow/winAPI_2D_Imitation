#include "framework.h"
#include "CEnemy.h"

CEnemy::CEnemy()
{
	fAttention = 0;
	fSpeed	= E_SPEED;
	fvDir = fVec2(0.f, 0.f);
	setPos(fPoint(470.f, 220.f));
	setSize(fPoint(O_SIZE, O_SIZE));
	fMoveCycle = 0.f;
	isFever = false;
	fFeverCount = 0.f;
}

CEnemy::CEnemy(fPoint pos, fPoint size, float spd, fVec2 dir)
{
	setPos(pos);
	setSize(size);
	fAttention = 0.f;
	fSpeed = spd;
	fMoveCycle = 0.f;
	fvDir = dir;
	isFever = false;
	fFeverCount = 0.f;
}



CEnemy::~CEnemy()
{
}

void CEnemy::setDir(fVec2 vec)
{
	fvDir = vec.normalize();
}

void CEnemy::setRandDir()
{
}


void CEnemy::update()
{
	fPoint enemyPos = getPos();
	fPoint playerPos = GETPOS;

	int sight = ISMODE ? P_SIGHTON : P_SIGHTOFF;

	fvDir.x = playerPos.x - enemyPos.x;
	fvDir.y = playerPos.y - enemyPos.y;


	// 적이 시야 안에 있을 경우
	if (enemyPos.COLL_PC(enemyPos, playerPos, sight))
	{
		if (fAttention <= 3.f)
			fAttention += ISMODE ? 2 * DT : DT;
		if (fAttention >= 2.f && !isFever)
		{
			isFever = true;
			fFeverCount += 1.f;
		}
		if (isFever)
		{
			setDir(fvDir);
			enemyPos.x += fSpeed * fvDir.x * DT;
			enemyPos.y += fSpeed * fvDir.y * DT;
		}
	}
	else
	{
		if (isFever) isFever = false;

		if (fAttention > 0.f)
		{
			fAttention -= DT;

			if (fAttention < 0.f)
				fAttention = 0.f;
		}
		// TODO : 일정 시간마다 랜덤 움직임
	}

	if (fFeverCount > 0.f)
	{ 
		fFeverCount -= DT;

		if (fFeverCount <= 0.f && isFever)
		{
			fFeverCount = 0.f;
			isFever = false;
		}
	}
	setPos(enemyPos);
}

void CEnemy::render(HDC hDC)
{
	fPoint pos = getPos();
	fPoint playerPos = GETPOS;

	int sight = ISMODE ? P_SIGHTON : P_SIGHTOFF;

	if (!pos.COLL_PC(pos, playerPos, sight)) return;

	HPEN hPen, hOriginalPen;
	HBRUSH hBrush, hOriginalBrush;

	hPen = CreatePen(PS_SOLID, 1, RGB(200, 25, 25));
	hBrush = CreateSolidBrush(RGB(45, 45, 45));

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

	if (isFever)
	{
		LPCWSTR strMessage = L"!";

		HFONT hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Arial Black"));
		HFONT hOriginFont = (HFONT)SelectObject(hDC, hFont);

		SetTextColor(hDC, RGB(200,50,50));
		TextOutW(hDC, pos.x, pos.y - 20, strMessage, wcslen(strMessage));

		SelectObject(hDC, hOriginFont);
		DeleteObject(hFont);
	}
}
