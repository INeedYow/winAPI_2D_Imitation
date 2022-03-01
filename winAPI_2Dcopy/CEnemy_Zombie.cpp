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

	if (pos.COLL_PC(pos, playerPos, sight))		// �þ� �ȿ� ������
	{
		if (fAttention <= 3.f)						
			fAttention += ISMODE ? 2 * DT : DT;		// ��׷� ����
		if (fAttention >= 2.f)
			isNotice = true;
	}
	else										// �þ� �ȿ� ������
	{
		if (fAttention > 0.f)
			fAttention -= DT;						// ��׷� ����
		if (fAttention <= 1.f)
			isNotice = false;
	}

	if (isNotice)								// ��׷� ������ �� ���⼳��
	{
		fvDir.x = playerPos.x - pos.x;
		fvDir.y = playerPos.y - pos.y;
	}
	else										// ��׷� �� ������ �� ���⼳��
	{
		fTimer -= DT;

		if (0.f > fTimer )							// Ÿ�̸� 0�Ǹ� 
		{
			if (isMove)									// ��� ����ٰ� �� �����̰�
			{
				isMove = false;
				fTimer = rand() % 4 + 1;
				return;
			}

			setRandDir();								// ����, Ÿ�̸� �缳��
			fTimer = rand() % 3 + 2;

			if (0 == fvDir.x && 0 == fvDir.y)
				isMove = false;
			else		
				isMove = true;
		}
		else										// Ÿ�̸� �����ְ�
		{
			if (!isMove)	return;						// ������ ������ return;
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

	HPEN hPen, hOriginalPen;
	HBRUSH hBrush, hOriginalBrush;

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
