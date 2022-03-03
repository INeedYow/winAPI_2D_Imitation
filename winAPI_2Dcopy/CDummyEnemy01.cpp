#include "framework.h"
#include "CDummyEnemy01.h"

CDummyEnemy01::CDummyEnemy01()
{
	fAttention = 0;
	fSpeed = EZ_SPEEDMAX;
	fvDir = fVec2(0.f, 0.f);
	setPos(fPoint(440.f, 360.f));
	setSize(fPoint(O_SIZE, O_SIZE));
	fTimer = 0.f;
	isNotice = false;
	isComing = false;
}


CDummyEnemy01::~CDummyEnemy01()
{
}

void CDummyEnemy01::update()
{
	fPoint enemyPos = getPos();
	if (isComing && KEY_ON('A'))
		CSceneManager::getInst()->sceneChange(SCENE::TUTORIAL_02);

	if (enemyPos.x < 550.f)
	{
		fPoint playerPos = GETPOS;
		int sight = ISMODE ? P_SIGHTON : P_SIGHTOFF;

		if (ISCOLLPC(enemyPos, playerPos, sight))
		{
			if (fAttention <= 2.f)
				fAttention += (float)DT;
			if (fAttention >= 1.f && !isNotice)
			{
				isNotice = true;
			}
			if (isNotice)
			{
				enemyPos.x += (float)(fSpeed * DT);
			}
		}
		else
		{
			if (isNotice) isNotice = false;

			if (fAttention > 0.f)
			{
				fAttention -= (float)DT;

				if (fAttention < 0.f)
					fAttention = 0.f;
			}
		}
		setPos(enemyPos);
	}
	else isComing = true;
}

void CDummyEnemy01::render(HDC hDC)
{
	fPoint pos = getPos();
	fPoint playerPos = GETPOS;

	int sight = ISMODE ? P_SIGHTON : P_SIGHTOFF;

	if (!ISCOLLPC(pos, playerPos, sight)) return;

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

	if (isNotice)
	{
		LPCWSTR strMessage = L"!";
		HFONT hFont = CreateFont(24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Comic Sans MS"));
		HFONT hOriginFont = (HFONT)SelectObject(hDC, hFont);

		SetTextColor(hDC, RGB(200, 150, 50));
		TextOutW(hDC, (int)pos.x, (int)pos.y - 20, strMessage, (int)wcslen(strMessage));

		SelectObject(hDC, hOriginFont);
		DeleteObject(hFont);
	}
	if (isComing)
	{
		LPCWSTR strMessage = L"계속하려면 \'A\'를 누르세요";
		HFONT hFont = CreateFont(28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Comic Sans MS"));
		HFONT hOriginFont = (HFONT)SelectObject(hDC, hFont);

		SetTextColor(hDC, RGB(25, 25, 153));
		TextOutW(hDC, (int)pos.x - 25, (int)pos.y + 105, strMessage, (int)wcslen(strMessage));

		SelectObject(hDC, hOriginFont);
		DeleteObject(hFont);
	}
}