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

	if (timeCnt >= 1.f)			// 1초 경과
	{
		timeCnt -= 1.f;
		duraCnt--;				// 지속시간 감소

		if (0 == duraCnt)		// 지속시간 0이면
		{
			setRandPos();		// 위치 변경 (맵에 아이템 1개는 계속 존재하게 할 생각)
			setRandEA();
			duraCnt = I_B_DURA;
		}
	}

	// TODO (교수님 질문)
	// 총알 아이템이 플레이어와 충돌했을 때(습득) 플레이어와 아이템이 각각 처리해야 하는 내용이 다른데 또 서로 자기 멤버에만 접근할 수 있잖아요..
	// 지금 충돌했는지 계산을 플레이어 update()에서도 하고 있고 item_bullet의 update()에서도 하고 있는데요
	// 각각의 후처리를 하려면 이렇게 하는 게 맞지만 같은 계산을 두 번해서 효율적이지 않은데 방법이 뭘까요?
	RECT areaRect = { bullPos.x - I_SIZE / 2,
					  bullPos.y - I_SIZE / 2,
					  bullPos.x + I_SIZE / 2,
					  bullPos.y + I_SIZE / 2 };

	if (bullPos.COLL_CR(playerPos, O_SIZE, areaRect))
	{	// 습득하면 위치 이동
		setRandPos();
		setRandEA();
		duraCnt = I_B_DURA;
		// TODO 플레이어 탄창 개수 증가
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
