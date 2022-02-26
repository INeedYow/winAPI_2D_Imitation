#include "framework.h"
#include "CItem_Bullet.h"

CItem_Bullet::CItem_Bullet()
{
	setPos(fPoint(0.f, 0.f));
	setSize(fPoint((float)I_SIZE, (float)I_SIZE));
	setTimer(0.f);
	setDuration(0);
	
}

CItem_Bullet::~CItem_Bullet()
{
}

void CItem_Bullet::setRandEA()
{
	ucEA = rand() % (I_B_MAXEA - I_B_MINEA + 1) + I_B_MINEA;
}

UCHAR CItem_Bullet::getEA()
{
	return ucEA;
}

void CItem_Bullet::update()
{
	float   timeCnt = getTimer();
	UINT	duraCnt = getDuration();
	fPoint	bullPos = getPos();
	fPoint	playerPos = GETPOS;

	timeCnt += DT;

	if (timeCnt >= 1.f)			// 1�� ���
	{
		timeCnt -= 1.f;
		duraCnt--;				// ���ӽð� ����

		if (0 == duraCnt)		// ���ӽð� 0�̸�
		{
			setRandPos();		// ��ġ ���� (�ʿ� ������ 1���� ��� �����ϰ� �� ����)
			setRandEA();
			duraCnt = I_B_DURA;
		}
	}

	// TODO (������ ����)
	// �Ѿ� �������� �÷��̾�� �浹���� ��(����) �÷��̾�� �������� ���� ó���ؾ� �ϴ� ������ �ٸ��� �� ���� �ڱ� ������� ������ �� ���ݾƿ�..
	// ���� �浹�ߴ��� ����� �÷��̾� update()������ �ϰ� �ְ� item_bullet�� update()������ �ϰ� �ִµ���
	// ������ ��ó���� �Ϸ��� �̷��� �ϴ� �� ������ ���� ����� �� ���ؼ� ȿ�������� ������ ����� �����?
	RECT areaRect = { bullPos.x - I_SIZE / 2,
					  bullPos.y - I_SIZE / 2,
					  bullPos.x + I_SIZE / 2,
					  bullPos.y + I_SIZE / 2 };

	if (bullPos.COLL_CR(playerPos, O_SIZE, areaRect))
	{	// �����ϸ� ��ġ �̵�
		setRandPos();
		setRandEA();
		duraCnt = I_B_DURA;
		// TODO �÷��̾� źâ ���� ����
	}

	setPos(bullPos);
	setTimer(timeCnt);
	setDuration(duraCnt);
}

void CItem_Bullet::render(HDC hDC)
{

	fPoint pos = getPos();
	fPoint playerPos = GETPOS;

	int sight = ISMODE ? P_SIGHTON : P_SIGHTOFF;


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

}
