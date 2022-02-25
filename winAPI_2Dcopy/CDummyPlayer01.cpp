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
	fPoint dummyPos = getPos();

	if (dummyPos.x )


	if (KEY_HOLD(VK_UP) && (dummyPos.y - getSize().y / 2.f) > 0.f)		// ∏  ≈ª√‚ πÊ¡ˆ
		dummyPos.y -= fSpeed * DT;

	if (KEY_HOLD(VK_DOWN) && (dummyPos.y + getSize().y / 2.f) < (float)WINSIZEY)
		dummyPos.y += fSpeed * DT;

	if (KEY_HOLD(VK_LEFT) && (dummyPos.x - getSize().x / 2.f) > 0.f)
		dummyPos.x -= fSpeed * DT;

	if (KEY_HOLD(VK_RIGHT) && (dummyPos.x + getSize().y / 2.f) < (float)WINSIZEX)
		dummyPos.x += fSpeed * DT;


	setPos(dummyPos);
}

void CDummyPlayer01::render(HDC hDC)
{
}
