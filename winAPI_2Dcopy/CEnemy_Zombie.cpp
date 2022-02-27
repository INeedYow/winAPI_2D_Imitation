#include "framework.h"
#include "CEnemy_Zombie.h"

CEnemy_Zombie::CEnemy_Zombie()
{
	setPos(fPoint(0.f, 0.f));
	fvDir = fVec2(0.f, 0.f);
	fSpeed = EZ_SPEEDMAX;
	fAttention = 0;
	fTimer = 4.f;
	isNotice = false;
	fFeverCount = 0.f;
	setSize(fPoint(EZ_SIZE, EZ_SIZE));
	isMove = false;
}

CEnemy_Zombie::CEnemy_Zombie(fPoint pos, fVec2 dir)
{
	setPos(pos);
	fvDir = dir;
	setRandSpeed();
	fAttention = 0.f;
	fTimer = 4.f;
	isNotice = false;
	fFeverCount = 0.f;
	setSize(fPoint(EZ_SIZE, EZ_SIZE));
	isMove = false;
}

CEnemy_Zombie::~CEnemy_Zombie()
{
}

void CEnemy_Zombie::setRandDir()
{
	fvDir.x = rand() % 9 - 4;
	fvDir.y = rand() % 9 - 4;
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
	fPoint enemyPos = getPos();
	fPoint playerPos = GETPOS;

	int sight = ISMODE ? P_SIGHTON : P_SIGHTOFF;

	// ���� �þ� �ȿ� ���� ���
	if (enemyPos.COLL_PC(enemyPos, playerPos, sight))
	{
		isMove = false;
		fvDir.x = playerPos.x - enemyPos.x;
		fvDir.y = playerPos.y - enemyPos.y;

		if (fAttention <= 3.f)
			fAttention += ISMODE ? 2 * DT : DT;
		if (fAttention >= 2.f && !isNotice)
		{
			isNotice = true;
			fFeverCount += 1.f;
		}
		if (isNotice)
		{
			setDir(fvDir);
			enemyPos.x += fSpeed * fvDir.x * DT;
			enemyPos.y += fSpeed * fvDir.y * DT;
		}
	}
	else
	{
		if (isNotice) isNotice = false;

		if (fAttention > 0.f)
		{
			fAttention -= DT;

			if (fAttention < 0.f)
				fAttention = 0.f;
		}

		if (!isMove)							// ������ ���� ������
		{
			fTimer += DT;
			if (fTimer >= 4.f)
			{

				setRandDir();						// ���⼺ �缳��
				if (0 == fvDir.x && 0 == fvDir.y)		// ���⼺ ������
					fTimer = 0;								// �ٽ� ���
				else
				{
					setDir(fvDir);
					isMove = true;
					fTimer = rand() % 3 + 3;
				}
			}
		}
		else									// ������ ���� ������
		{
			if (fTimer > 0.f)	fTimer -= DT;

			if (0.f > fTimer) isMove = false;

			enemyPos.x += EZ_SPEEDMIN * fvDir.x * DT;
			enemyPos.y += EZ_SPEEDMIN * fvDir.y * DT;

			// �� ������ϸ� �ش� ���⼺�� �ݴ�� ��������
			if (O_HSIZE > enemyPos.x || enemyPos.x > WINSIZEX - O_HSIZE)
				fvDir.x *= -1;
			if (O_HSIZE > enemyPos.y || enemyPos.y > WINSIZEY - O_HSIZE)
				fvDir.y *= -1;
		}
	}

	if (fFeverCount > 0.f)
	{
		fFeverCount -= DT;

		if (fFeverCount <= 0.f && isNotice)
		{
			fFeverCount = 0.f;
			isNotice = false;
		}
	}
	setPos(enemyPos);
}

void CEnemy_Zombie::render(HDC hDC)
{
	fPoint pos = getPos();
	fPoint playerPos = GETPOS;

	int sight = ISMODE ? P_SIGHTON : P_SIGHTOFF;

	HPEN hPen, hOriginalPen;
	HBRUSH hBrush, hOriginalBrush;

	// �� ��Ȯ�� ��� ��� ���̷��� �������� COLL_PC�Լ�
	if (!pos.COLL_PC(pos, playerPos, sight))
	{
		if (ISSCAN)
		{	// ��ĳ��
			hPen = CreatePen(PS_SOLID, 1, RGB(200, 25, 25));
			hOriginalPen = (HPEN)SelectObject(hDC, hPen);
			Rectangle(hDC, pos.x - 1, pos.y - 1, pos.x + 1, pos.y + 1);
			SelectObject(hDC, hOriginalPen);
			DeleteObject(hPen);
		}
		return;
	}

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
		TextOutW(hDC, pos.x, pos.y - 20, strMessage, wcslen(strMessage));

		SelectObject(hDC, hOriginFont);
		DeleteObject(hFont);
	}
}
