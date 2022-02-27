#include "framework.h"
#include "CItem_Bullet.h"

CItem_Bullet::CItem_Bullet()
{
	setPos(fPoint(0.f, 0.f));
	setSize(fPoint((float)I_SIZE, (float)I_SIZE));
	setTimer(0.f);
	setDuration(I_B_DURA);
	setRandEA();
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
	fPoint	itemPos = getPos();
	fPoint	playerPos = GETPOS;

	timeCnt += DT;

	if (timeCnt >= 1.f)			// 1�� ���
	{
		timeCnt = 0.f;
		duraCnt--;				// ���ӽð� ����

		if (0 == duraCnt)		// ���ӽð� 0�̸�
		{
			setRandPos();		// ��ġ ����
			setRandEA();
			duraCnt = I_B_DURA;
		}
	}

	// TODO (������ ����)
	// �������� �÷��̾�� �浹���� ��(����) �÷��̾�� �������� ���� ó���ؾ� �ϴ� ������ �ٸ��� �� ���� �ڱ� ������� ������ �� ���ݾƿ�..
	// ���� �浹�ߴ��� ����� �÷��̾� update()������ �ϰ� �ְ� item_bullet�� update()������ �ϰ� �ִµ���
	// ������ ��ó���� �Ϸ��� �̷��� �ϴ� �� ������ ���� ����� �� ���ؼ� ȿ�������� ������ ����� �����?
	RECT areaRect = { (int)itemPos.x - (int)I_HSIZE,
					  (int)itemPos.y - (int)I_HSIZE,
					  (int)itemPos.x + (int)I_HSIZE,
					  (int)itemPos.y + (int)I_HSIZE };

	if (itemPos.COLL_CR(playerPos, (int)O_HSIZE, areaRect))
	{	// �����ϸ� ��ġ �̵�
		setRandPos();
		setRandEA();
		duraCnt = I_B_DURA;
	}

	// setPos(itemPos);		//setRandPos()�� ��ġ �ٲ����� �ٽ� itemPos�� ���������ϱ� ��ġ�� �� �ٲ���
	setTimer(timeCnt);
	setDuration(duraCnt);
}

void CItem_Bullet::render(HDC hDC)
{

	fPoint	pos = getPos();
	fPoint	playerPos = GETPOS;
	UINT	duraCnt = getDuration();

	int sight = ISMODE ? P_SIGHTON : P_SIGHTOFF;

	// �� ��Ȯ�� ��� ��� ���̷��� �������� COLL_PC�Լ�
	if (!pos.COLL_PC(pos, playerPos, sight)) return;

	HPEN hPen, hOriginalPen;
	HBRUSH hBrush, hOriginalBrush;

	// ������ �����ð� �� �� �������� �����̰� �غ��� ����
	int iColor = 102;

	if (duraCnt <= 6 && duraCnt % 2)
		iColor = 153;

	hPen = CreatePen(PS_SOLID, 1, RGB(51, 51, 0));
	hBrush = CreateSolidBrush(RGB(iColor, iColor, 0));
	
	hOriginalPen = (HPEN)SelectObject(hDC, hPen);
	hOriginalBrush = (HBRUSH)SelectObject(hDC, hBrush);

	Rectangle(hDC,
		(int)(pos.x - I_HSIZE),
		(int)(pos.y - I_HSIZE),
		(int)(pos.x + I_HSIZE),
		(int)(pos.y + I_HSIZE));

	SelectObject(hDC, hOriginalPen);
	SelectObject(hDC, hOriginalBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);

	// ��������� ���ӽð� ǥ���ϴ� �ڵ�
	/*WCHAR szBuffer[255] = {};
	swprintf_s(szBuffer, L"%d", duraCnt);
	TextOutW(hDC, pos.x, pos.y, szBuffer, wcslen(szBuffer));*/
}
