#include "framework.h"
#include "CEnemy.h"

CEnemy::CEnemy()
{
	fAttention = 0;
	setRandSpeed();
	fvDir = fVec2(0.f, 0.f);
	setPos(fPoint(470.f, 220.f));
	setSize(fPoint(O_SIZE, O_SIZE));
	fTimer = 4.f;
	isFever = false;
	fFeverCount = 0.f;
	isMove = false;
}

CEnemy::CEnemy(fPoint pos, fPoint size, float spd, fVec2 dir)
{
	setPos(pos);
	setSize(size);
	fAttention = 0.f;
	setRandSpeed();
	fTimer = 4.f;
	fvDir = dir;
	isFever = false;
	fFeverCount = 0.f;
	isMove = false;
}



CEnemy::~CEnemy()
{
}

void CEnemy::setDir(fVec2 vec)
{
	fvDir = vec.normalize();
}

void CEnemy::setRandSpeed()
{
	int spdMax = (int)E_SPEEDMAX + (int)g_resultTimer;
	int spdMin = (int)E_SPEEDMIN + (int)g_resultTimer;
	fSpeed = rand() % (spdMax - spdMin + 1) + spdMin;
}

void CEnemy::setRandDir()
{
	fvDir.x = rand() % 9 - 4;
	fvDir.y = rand() % 9 - 4;
}


void CEnemy::update()
{
	fPoint enemyPos = getPos();
	fPoint playerPos = GETPOS;

	int sight = ISMODE ? P_SIGHTON : P_SIGHTOFF;

	// 적이 시야 안에 있을 경우
	if (enemyPos.COLL_PC(enemyPos, playerPos, sight))
	{
		isMove = false;
		fvDir.x = playerPos.x - enemyPos.x;
		fvDir.y = playerPos.y - enemyPos.y;

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

		if (!isMove)							// 움직임 패턴 없으면
		{
			fTimer += DT;						
			if (fTimer >= 4.f)
			{
				
				setRandDir();						// 방향성 재설정
				if (0 == fvDir.x && 0 == fvDir.y)		// 방향성 없으면
					fTimer = 0;								// 다시 대기
				else									
				{
					setDir(fvDir);
					isMove = true;					
					fTimer = rand() % 3 + 3;		
				}
			}
		}
		else									// 움직임 패턴 있으면
		{
			if (fTimer > 0.f)	fTimer -= DT;

			if (0.f > fTimer) isMove = false;	

			enemyPos.x += E_SPEEDMIN * fvDir.x * DT; 
			enemyPos.y += E_SPEEDMIN * fvDir.y * DT;
			
			// 맵 벗어나려하면 해당 방향성만 반대로 뒤집어줌
			if (O_HSIZE > enemyPos.x || enemyPos.x > WINSIZEX - O_HSIZE)
				fvDir.x *= -1;
			if (O_HSIZE > enemyPos.y || enemyPos.y > WINSIZEY - O_HSIZE)
				fvDir.y *= -1;
		}
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

	// 덜 정확한 대신 속도나 계산 줄이려는 목적으로 COLL_PC함수
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

		HFONT hFont = CreateFont(24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Comic Sans MS"));
		HFONT hOriginFont = (HFONT)SelectObject(hDC, hFont);

		SetTextColor(hDC, RGB(200,150,50));
		TextOutW(hDC, pos.x, pos.y - 20, strMessage, wcslen(strMessage));

		SelectObject(hDC, hOriginFont);
		DeleteObject(hFont);
	}
}
