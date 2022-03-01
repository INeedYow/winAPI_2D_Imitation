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
	setName(L"총알");
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

	if (timeCnt >= 1.f)			// 1초 경과
	{
		timeCnt = 0.f;
		duraCnt--;				// 지속시간 감소

		if (0 == duraCnt)		// 지속시간 0이면
		{
			setRandPos();		// 위치 변경
			setRandEA();
			duraCnt = IB_DURA;
		}
		if (6 >= duraCnt)
			isFlick = !isFlick;
	}

	// TODO (교수님 질문)
	// 아이템이 플레이어와 충돌했을 때(습득) 플레이어와 아이템이 각각 처리해야 하는 내용이 다른데 또 서로 자기 멤버에만 접근할 수 있잖아요..
	// 지금 충돌했는지 계산을 플레이어 update()에서도 하고 있고 item_bullet의 update()에서도 하고 있는데요
	// 각각의 후처리를 하려면 이렇게 하는 게 맞는데 또 같은 계산을 두 번해서 효율적이지 않은데 방법이 뭘까요?
	RECT areaRect = { (int)itemPos.x - (int)I_HSIZE,
					  (int)itemPos.y - (int)I_HSIZE,
					  (int)itemPos.x + (int)I_HSIZE,
					  (int)itemPos.y + (int)I_HSIZE };

	if (itemPos.COLL_CR(playerPos, (int)O_HSIZE, areaRect))
	{	// 습득하면 위치 이동
		int a = GETBULLET;
		SETBULLET(a + ucEA);
		setRandPos();
		setRandEA();		// 총알 몇발짜리 아이템인지 변수로 가지고 있다가 그만큼 플레이어 총알 증가시키고 싶은데 못하는 중
		duraCnt = IB_DURA;
	}

	// setPos(itemPos);		// setRandPos()로 위치 바꿔놓고는 다시 itemPos로 돌려놓으니까 위치가 안 바뀌지
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
		{	// 스캐너
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

	// 드랍아이템 지속시간 표시하는 코드
	/*WCHAR szBuffer[255] = {};
	swprintf_s(szBuffer, L"%d", duraCnt);
	TextOutW(hDC, pos.x, pos.y, szBuffer, wcslen(szBuffer));*/
}
