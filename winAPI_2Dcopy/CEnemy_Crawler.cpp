#include "framework.h"
#include "CEnemy_Crawler.h"
#include "CCollider.h"

#include "SelectGDI.h"
//#include "CSightCircle.h"

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
	strMsg = L"!";

	createCollider();
	getCollider()->setSize(fPoint(EC_SIZE - 2, EC_SIZE - 2));
	getCollider()->setOffset(fPoint((float)0, (float)0));
	getCollider()->setShape(SHAPE::CIRCLE);
}

CEnemy_Crawler::~CEnemy_Crawler()
{
}


void CEnemy_Crawler::update()
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

	if (fTimer > 0.f)							// ��ġ �߿� (��ĩ�� ���� ��׷� ������ ���ְ� return)
	{
		fTimer -= DT;
		return;
	}

	if (isNotice)								// ��׷� ������ �� ���⼳��
	{
		fvDir.x = playerPos.x - pos.x;
		fvDir.y = playerPos.y - pos.y;
	}
	else										// ��׷� �� ������ �� ���⼳��
	{
		if(0 == (int)g_resultTimer % 4)				// �缳�� �ֱ�
			setRandDir();
	}

	if (0 != fvDir.x || 0 != fvDir.y)
		setDir(fvDir);

	if (isBoosting)								// �ӵ� ��ȭ
	{
		fDecel += 10000 * DT;
		fSpeed -= (5000 + fDecel) * DT;
		if (fSpeed < (float)EC_SPEEDMIN)
		{
			fSpeed = (float)EC_SPEEDMIN;
			isBoosting = false;
			fAccel = 0.f;
			fTimer += 0.9f;							// ��ĩ�ϴ� �ð�
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
			fTimer += 0.1f;							// ��ĩ�ϴ� �ð�
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
	
	// �̷������� �ٸ� ��ü�� ������ �� �����µ� ��ü �̰� ��� �ϳ�???
	// �˴� static���� �������ϳ�
	//int range = CSightCircle::getRange(ISMODE);

	SelectGDI pen(hDC, PEN::E_EDGE);
	SelectGDI brush(hDC, BRUSH::EC_BRU);

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

	if (isNotice)
	{
		SelectGDI font(hDC, FONT::COMIC24);

		SetTextColor(hDC, RGB(200, 150, 50));
		TextOutW(hDC, pos.x, pos.y - 20, strMsg, wcslen(strMsg));
	}
}
