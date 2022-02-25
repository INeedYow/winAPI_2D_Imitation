#include "framework.h"
#include "CDummyPlayer01.h"

CDummyPlayer01::CDummyPlayer01()
{
}

CDummyPlayer01::~CDummyPlayer01()
{
}


// target �� rectangle�� �׸� �������� area ��Ÿ �� rect ������� �����ؼ� �װɷ� ���ϴ� �� ����
// �Ź� rect ���� �Լ��� ������ �ϳ�?
void CDummyPlayer01::update()
{
	fPoint dummyPos = getPos();

	RECT rt1 = { 150 - 24, 360 - 24, 150 + 24, 360 - 24 };
	RECT rt2 = { 1130 - 24, 360 - 24, 1130 + 24, 360 - 24 };

	if (dummyPos.isCollisionCircleToRect(dummyPos, O_SIZE / 2, rt1) ||
		dummyPos.isCollisionCircleToRect(dummyPos, O_SIZE / 2, rt2))
		CSceneManager::getInst()->sceneChange(SCENE::TUTORIAL_02);

	if (KEY_HOLD(VK_UP) && (dummyPos.y - getSize().y / 2.f) > 0.f)		// �� Ż�� ����
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
	HPEN hPen = CreatePen(PS_SOLID, P_PEN, ISMODE ? RGB(75, 125, 50) : RGB(125, 150, 100));
	HBRUSH hBrush = CreateSolidBrush(ISMODE ? RGB(125, 200, 75) : RGB(150, 255, 100));

	HPEN hOriginalPen = (HPEN)SelectObject(hDC, hPen);
	HBRUSH hOriginalBrush = (HBRUSH)SelectObject(hDC, hBrush);

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
