#include "framework.h"
#include "CEnemy.h"

CEnemy::CEnemy()
{
	fAttention = 0;
	fSpeed	= E_SPEED;
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
	fSpeed = spd;
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

void CEnemy::setRandDir()
{
}

// �����̱��ϴµ� �ӵ� �ڱ� �ڴ����

void CEnemy::update()
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
		// TODO : ���� �ð����� ���� ������
		if (!isMove)							// �������� ���� ���¸�
		{
			fTimer += DT;						// Ÿ�̸� ����
			if (fTimer >= 4.f)					//
			{
				fTimer = 0;
				while (true)					// ���⼺ ���� �̱�
				{
					int x = rand() % 9 - 4;
					int y = rand() % 9 - 4;
					if (0 == x && 0 == y)	break;								// ���⼺ 0, 0������ 4�� ���� �� ������ �ֵ���
					if (0 > enemyPos.x + x || enemyPos.x + x > WINSIZEX ||		// �� Ż������ �ʵ���
						0 > enemyPos.y + y || enemyPos.y + y > WINSIZEY) continue;
					fvDir.x = x;
					fvDir.y = y;
					isMove = true;				// ������ �̾����� ���� ������Ʈ���� ������ �����ϸ� ��
					fTimer = rand() % 3 + 3;				// ������ �ð� ����
					break;
				}
			}
		}
		else
		{
			if (fTimer > 0.f)
				fTimer -= DT;

			if (0.f > fTimer) isMove = false;	// ������ ���� ����

			if (0 != fvDir.x && 0 != fvDir.y)	setDir(fvDir);
			enemyPos.x += E_MINSPEED * fvDir.x * DT;
			enemyPos.y += E_MINSPEED * fvDir.y * DT;
			if (O_HSIZE > enemyPos.x || enemyPos.x > WINSIZEX - O_HSIZE ||
				O_HSIZE > enemyPos.y || enemyPos.y > WINSIZEY - O_HSIZE)
			{
				isMove = false;
			}
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

	// �� ��Ȯ�� ��� �ӵ��� ��� ���̷��� �������� COLL_PC�Լ�
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
