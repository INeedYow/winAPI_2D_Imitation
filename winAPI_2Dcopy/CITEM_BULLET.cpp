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

	if (timeCnt >= 1.f)			// 1초 경과
	{
		timeCnt = 0.f;
		duraCnt--;				// 지속시간 감소

		if (0 == duraCnt)		// 지속시간 0이면
		{
			setRandPos();		// 위치 변경
			setRandEA();
			duraCnt = I_B_DURA;
		}
	}

	// TODO (교수님 질문)
	// 아이템이 플레이어와 충돌했을 때(습득) 플레이어와 아이템이 각각 처리해야 하는 내용이 다른데 또 서로 자기 멤버에만 접근할 수 있잖아요..
	// 지금 충돌했는지 계산을 플레이어 update()에서도 하고 있고 item_bullet의 update()에서도 하고 있는데요
	// 각각의 후처리를 하려면 이렇게 하는 게 맞지만 같은 계산을 두 번해서 효율적이지 않은데 방법이 뭘까요?
	RECT areaRect = { (int)itemPos.x - (int)I_HSIZE,
					  (int)itemPos.y - (int)I_HSIZE,
					  (int)itemPos.x + (int)I_HSIZE,
					  (int)itemPos.y + (int)I_HSIZE };

	if (itemPos.COLL_CR(playerPos, (int)O_HSIZE, areaRect))
	{	// 습득하면 위치 이동
		setRandPos();
		setRandEA();
		duraCnt = I_B_DURA;
	}

	// setPos(itemPos);		//setRandPos()로 위치 바꿔놓고는 다시 itemPos로 돌려놓으니까 위치가 안 바뀌지
	setTimer(timeCnt);
	setDuration(duraCnt);
}

void CItem_Bullet::render(HDC hDC)
{

	fPoint	pos = getPos();
	fPoint	playerPos = GETPOS;
	UINT	duraCnt = getDuration();

	int sight = ISMODE ? P_SIGHTON : P_SIGHTOFF;

	// 덜 정확한 대신 계산 줄이려는 목적으로 COLL_PC함수
	if (!pos.COLL_PC(pos, playerPos, sight)) return;

	HPEN hPen, hOriginalPen;
	HBRUSH hBrush, hOriginalBrush;

	// 아이템 유지시간 얼마 안 남았으면 깜빡이게 해보고 싶음
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

	// 드랍아이템 지속시간 표시하는 코드
	/*WCHAR szBuffer[255] = {};
	swprintf_s(szBuffer, L"%d", duraCnt);
	TextOutW(hDC, pos.x, pos.y, szBuffer, wcslen(szBuffer));*/
}
