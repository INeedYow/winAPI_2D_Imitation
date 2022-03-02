#include "framework.h"
#include "CItem_Bullet.h"

#include "SelectGDI.h"

CItem_Bullet::CItem_Bullet()
{
	setPos(fPoint(0.f, 0.f));
	setSize(fPoint((float)I_SIZE, (float)I_SIZE));
	setTimer(0.f);
	setDuration(IB_DURA);
	setRandEA();
	setKey((UCHAR)IKEY::BULLET);
	setName(L"�Ѿ�");
}

CItem_Bullet::~CItem_Bullet()
{
}

void CItem_Bullet::setRandEA()
{
	ucEA = rand() % (IB_MAXEA - IB_MINEA + 1) + IB_MINEA;
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
	bool	isFlick = getIsFlick();
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
			duraCnt = IB_DURA;
		}
		if (6 >= duraCnt)
			isFlick = !isFlick;
	}

	//RECT areaRect = { (int)itemPos.x - (int)I_HSIZE,
	//				  (int)itemPos.y - (int)I_HSIZE,
	//				  (int)itemPos.x + (int)I_HSIZE,
	//				  (int)itemPos.y + (int)I_HSIZE };

	//if (itemPos.COLL_CR(playerPos, (int)O_HSIZE, areaRect))
	//{	// �����ϸ� ��ġ �̵�
	//	int a = GETBULLET;
	//	SETBULLET(a + ucEA);
	//	setRandPos();
	//	setRandEA();		// �Ѿ� ���¥�� ���������� ������ ������ �ִٰ� �׸�ŭ �÷��̾� �Ѿ� ������Ű�� ������ ���ϴ� ��
	//	duraCnt = IB_DURA;
	//}

	// setPos(itemPos);		// setRandPos()�� ��ġ �ٲ����� �ٽ� itemPos�� ���������ϱ� ��ġ�� �� �ٲ���
	setTimer(timeCnt);
	setDuration(duraCnt);
	setIsFlick(isFlick);
}

void CItem_Bullet::render(HDC hDC)
{

	fPoint	pos = getPos();
	fPoint	playerPos = GETPOS;
	UINT	duraCnt = getDuration();

	int sight = ISMODE ? P_SIGHTON : P_SIGHTOFF;

	if (!pos.COLL_PC(pos, playerPos, sight))
	{
		if (ISSCAN)
		{	// ��ĳ��
			SelectGDI pen(hDC, PEN::I_SCAN);
			Rectangle(hDC, pos.x - 1, pos.y - 1, pos.x + 1, pos.y + 1);
		}
		return;
	}

	SelectGDI pen(hDC, PEN::I_EDGE);
	SelectGDI brush(hDC, BRUSH::I_BRUFLICK, BRUSH::I_BRUNORMAL, getIsFlick());
	SelectGDI font(hDC, FONT::COMIC18);

	Rectangle(hDC,
		(int)(pos.x - I_HSIZE),
		(int)(pos.y - I_HSIZE),
		(int)(pos.x + I_HSIZE),
		(int)(pos.y + I_HSIZE));
	//
	SetTextColor(hDC, RGB(0,0,0));
	TextOutW(hDC, pos.x - 12, pos.y, getName(), wcslen(getName()));

	// ��������� ���ӽð� ǥ���ϴ� �ڵ�
	/*WCHAR szBuffer[255] = {};
	swprintf_s(szBuffer, L"%d", duraCnt);
	TextOutW(hDC, pos.x, pos.y, szBuffer, wcslen(szBuffer));*/
}
