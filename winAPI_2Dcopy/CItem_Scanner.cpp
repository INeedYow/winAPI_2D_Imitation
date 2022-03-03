#include "framework.h"
#include "CItem_Scanner.h"

#include "SelectGDI.h"

CItem_Scanner::CItem_Scanner()
{
	setPos(fPoint(0.f, 0.f));
	setSize(fPoint((float)I_SIZE, (float)I_SIZE));
	setTimer(0.f);
	setDuration(IB_DURA);
	setKey((UCHAR)IKEY::SCANNER);
	setName(L"��ĳ��");
}

CItem_Scanner::~CItem_Scanner()
{
}

void CItem_Scanner::update()
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
			duraCnt = IB_DURA;
		}

		if (duraCnt <= 6)
			isFlick = !isFlick;	// ���ӽð� 6�� �����̸� 1�ʸ��� ��ȯ 
	}

	
	//RECT areaRect = { (int)itemPos.x - (int)I_HSIZE,
	//				  (int)itemPos.y - (int)I_HSIZE,
	//				  (int)itemPos.x + (int)I_HSIZE,
	//				  (int)itemPos.y + (int)I_HSIZE };

	//if (itemPos.COLL_CR(playerPos, (int)O_HSIZE, areaRect))
	//{	// �����ϸ� ��ġ �̵�
	//	SETSCANTIMER(3.f);
	//	setRandPos();
	//	duraCnt = IB_DURA;
	//}

	setTimer(timeCnt);
	setDuration(duraCnt);
	setIsFlick(isFlick);
}

void CItem_Scanner::render(HDC hDC)
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
	TextOutW(hDC, pos.x - 18, pos.y, getName(), wcslen(getName()));
}
