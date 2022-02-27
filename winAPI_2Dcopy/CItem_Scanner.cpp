#include "framework.h"
#include "CItem_Scanner.h"

CItem_Scanner::CItem_Scanner()
{
	setPos(fPoint(0.f, 0.f));
	setSize(fPoint((float)I_SIZE, (float)I_SIZE));
	setTimer(0.f);
	setDuration(I_B_DURA);
	setKey((UCHAR)IKEY::SCANNER);
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

	if (timeCnt >= 1.f)			// 1초 경과
	{
		timeCnt = 0.f;
		duraCnt--;				// 지속시간 감소

		if (0 == duraCnt)		// 지속시간 0이면
		{
			setRandPos();		// 위치 변경
			duraCnt = I_B_DURA;
		}

		if (duraCnt <= 6)
			isFlick = !isFlick;	// 지속시간 6초 이하이면 1초마다 전환 
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
		SETSCAN(true);
		ADDTIMER(3.f);
		setRandPos();
		duraCnt = I_B_DURA;
	}

	setTimer(timeCnt);
	setDuration(duraCnt);
	setIsFlick(isFlick);
}

void CItem_Scanner::render(HDC hDC)
{
	fPoint	pos = getPos();
	fPoint	playerPos = GETPOS;
	UINT	duraCnt = getDuration();

	HPEN hPen, hOriginalPen;
	HBRUSH hBrush, hOriginalBrush;

	int sight = ISMODE ? P_SIGHTON : P_SIGHTOFF;

	// 덜 정확한 대신 계산 줄이려는 목적으로 COLL_PC함수
	if (!pos.COLL_PC(pos, playerPos, sight))
	{
		if (ISSCAN)
		{	// 스캐너
			hPen = CreatePen(PS_SOLID, 1, RGB(200, 200, 50));
			hOriginalPen = (HPEN)SelectObject(hDC, hPen);
			Rectangle(hDC, pos.x - 1, pos.y - 1, pos.x + 1, pos.y + 1);
			SelectObject(hDC, hOriginalPen);
			DeleteObject(hPen);
		}
		return;
	}

	hPen = CreatePen(PS_SOLID, 1, RGB(102, 153, 255));
	hBrush = CreateSolidBrush(getIsFlick() ? RGB(102, 255, 255) : RGB(0, 255, 255));

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

	// 현재 죄다 네모라서 구분하려면 아이템 이름정돈 적어야할듯해서
	HFONT hFont, hOriginalFont;
	hFont = CreateFont(18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Comic Sans MS"));
	hOriginalFont = (HFONT)SelectObject(hDC, hFont);

	SetTextColor(hDC, BLACK);
	LPCWSTR strMessage1 = L"스캐너";
	TextOutW(hDC, pos.x - 18, pos.y, strMessage1, wcslen(strMessage1));

	SelectObject(hDC, hOriginalFont);
	DeleteObject(hFont);
}
