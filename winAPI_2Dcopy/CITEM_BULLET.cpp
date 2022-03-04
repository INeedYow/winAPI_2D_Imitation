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
	bool	isFlick = getIsFlick();

	timeCnt += fDT;

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

	if (!ISCOLLPC(pos, playerPos, sight))
	{
		if (ISSCAN)
		{	// ��ĳ��
			SelectGDI pen(hDC, PEN::I_SCAN);
			Rectangle(hDC, (int)pos.x - 1, (int)pos.y - 1, (int)pos.x + 1, (int)pos.y + 1);
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
	TextOutW(hDC, (int)pos.x - 12, (int)pos.y, getName(), (int)wcslen(getName()));


	componentRender(hDC);
	// ��������� ���ӽð� ǥ���ϴ� �ڵ�
	/*WCHAR szBuffer[255] = {};
	swprintf_s(szBuffer, L"%d", duraCnt);
	TextOutW(hDC, pos.x, pos.y, szBuffer, wcslen(szBuffer));*/
}
