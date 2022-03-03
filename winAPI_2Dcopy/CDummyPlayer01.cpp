#include "framework.h"
#include "CDummyPlayer01.h"

#include "SelectGDI.h"

CDummyPlayer01::CDummyPlayer01()
{
	strMsg1 = L"시야가 넓어지는 대신 적이 나를 더 빨리 찾게 됩니다";
	strMsg2 = L"노란색 막대는 배터리입니다";
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
	fPoint pos = getPlayerPos();
	fPoint size = getSize();
	
	SelectGDI pen(hDC, PEN::P_EDGEON, PEN::P_EDGEOFF, isMode);
	SelectGDI brush(hDC, BRUSH::P_BRUON, BRUSH::P_BRUOFF, isMode);

	Ellipse(hDC,
		(int)(pos.x - size.x / 2),
		(int)(pos.y - size.y / 2),
		(int)(pos.x + size.x / 2),
		(int)(pos.y + size.y / 2));

	if (isMode)
	{
		SelectGDI font(hDC, FONT::COMIC24);

		SetTextColor(hDC, RGB(0,0,0));
		
		TextOutW(hDC, (int)pos.x - 200, (int)pos.y + 70, strMsg1, (int)wcslen(strMsg1));
		TextOutW(hDC, (int)pos.x - 90, (int)pos.y + 40, strMsg2, (int)wcslen(strMsg2));
	}
}
