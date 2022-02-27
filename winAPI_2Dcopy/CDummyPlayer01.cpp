#include "framework.h"
#include "CDummyPlayer01.h"

CDummyPlayer01::CDummyPlayer01()
{
}

CDummyPlayer01::~CDummyPlayer01()
{
}


void CDummyPlayer01::update()
{
	if (KEY_ON(VK_SPACE))
		isMode = true;
	if (KEY_OFF(VK_SPACE))
		isMode = false;

	if (KEY_ON('D'))
		CSceneManager::getInst()->sceneChange(SCENE::STAGE_01);
}

void CDummyPlayer01::render(HDC hDC)
{
	int sight = isMode ? P_SIGHTON : P_SIGHTOFF;
	fPoint pos = getPlayerPos();
	fPoint size = getSize();

	HPEN hPen, hOriginalPen;
	HBRUSH hBrush, hOriginalBrush;

	hBrush = CreateSolidBrush(RGB(200, 200, 200));
	hOriginalBrush = (HBRUSH)SelectObject(hDC, hBrush);

	Ellipse(hDC,
		(int)(pos.x - sight),
		(int)(pos.y - sight),
		(int)(pos.x + sight),
		(int)(pos.y + sight));

	SelectObject(hDC, hOriginalBrush);
	DeleteObject(hBrush);

	hPen = CreatePen(PS_SOLID, P_PEN, isMode ? RGB(125, 150, 100) : RGB(75, 100, 50));
	hBrush = CreateSolidBrush(isMode ? RGB(150, 200, 100) : RGB(100, 125, 75));

	hOriginalPen = (HPEN)SelectObject(hDC, hPen);
	hOriginalBrush = (HBRUSH)SelectObject(hDC, hBrush);

	Ellipse(hDC,
		(int)(pos.x - size.x / 2),
		(int)(pos.y - size.y / 2),
		(int)(pos.x + size.x / 2),
		(int)(pos.y + size.y / 2));

	SelectObject(hDC, hOriginalPen);
	SelectObject(hDC, hOriginalBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);

	if (isMode)
	{
		HFONT hFont, hOriginalFont;
		hFont = CreateFont(24, 0,0,0,0,0,0,0,0,0,0,0,0, _T("Comic Sans MS"));
		hOriginalFont = (HFONT)SelectObject(hDC, hFont);

		SetTextColor(hDC, BLACK);
		LPCWSTR strMessage1 = L"시야가 넓어지는 대신 적이 나를 더 빨리 찾게 됩니다";
		LPCWSTR strMessage2 = L"노란색 막대는 배터리입니다";
		TextOutW(hDC, pos.x - 200, pos.y + 70, strMessage1, wcslen(strMessage1));
		TextOutW(hDC, pos.x - 90, pos.y + 40, strMessage2, wcslen(strMessage2));

		SelectObject(hDC, hOriginalFont);
		DeleteObject(hFont);
	}
}
