#include "framework.h"
#include "CEnemy_Crawler.h"

CEnemy_Crawler::CEnemy_Crawler()
{
	fSpeed = 10.f;
	chaseMe();
	setRandPos((int)EC_SIZE / 2);
	setSize(fPoint(EC_SIZE, EC_SIZE));
	fTimer = 0.f;
	isBoosting = true;

	isNotice = 0;
	fAttention = 0;
	fAccel = 0;
	fDecel = 0;
}

CEnemy_Crawler::~CEnemy_Crawler()
{
}


void CEnemy_Crawler::update()
{
	fPoint pos = getPos();
	fPoint playerPos = GETPOS;

	int sight = ISMODE ? P_SIGHTON : P_SIGHTOFF;
	
	if (pos.COLL_PC(pos, playerPos, sight))	// �þ� �ȿ� ������
	{
		if (fAttention <= 3.f)					// ��׷� ����
			fAttention += ISMODE ? 2 * DT : DT;
		if (fAttention >= 2.f)
			isNotice = true;
	}
	else									// �þ� �ȿ� ������
	{
		if (fAttention > 0.f)
			fAttention -= DT;					// ��׷� ����
		isNotice = false;
	}

	if (fTimer > 0.f)						// ��ġ �߿� (��ĩ�� ���� ��׷� ������ ���ְ� return)
	{
		fTimer -= DT;
		return;
	}

	if (isNotice)							// ��׷� ������ �� ���⼳��
	{
		fvDir.x = playerPos.x - pos.x;
		fvDir.y = playerPos.y - pos.y;
	}
	else									// ��׷� �� ������ �� ���⼳��
	{
		if(0 == (int)g_resultTimer % 4)			// �缳�� �ֱ�
			setRandDir();
	}

	if (0 != fvDir.x || 0 != fvDir.y)		// �밢�̵� ����
		setDir(fvDir);

	if (isBoosting)							// �ӵ� ��ȭ
	{
		fDecel += 10000 * DT;
		fSpeed -= (5000 + fDecel) * DT;
		if (fSpeed < (float)EC_SPEEDMIN)
		{
			fSpeed = (float)EC_SPEEDMIN;
			isBoosting = false;
			fAccel = 0.f;
			fTimer += 0.9f;						// ��ĩ�ϴ� �ð�
		}
	}
	else
	{
		fAccel += 4000 * DT;
		fSpeed += (2000 + fAccel) * DT;
		if (fSpeed > (float)EC_SPEEDMAX)
		{
			fSpeed = (float)EC_SPEEDMAX;
			isBoosting = true;
			fDecel = 0.f;
			fTimer += 0.1f;						// ��ĩ�ϴ� �ð�
		}
	}

	pos.x += fSpeed * fvDir.x * DT;
	pos.y += fSpeed * fvDir.y * DT;

	setPos(pos);
}

void CEnemy_Crawler::render(HDC hDC)
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
	hBrush = CreateSolidBrush(RGB(75, 25, 50));

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
