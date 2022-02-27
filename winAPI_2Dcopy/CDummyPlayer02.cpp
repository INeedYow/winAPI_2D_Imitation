#include "framework.h"
#include "CDummyPlayer02.h"

CDummyPlayer02::CDummyPlayer02()
{
}

CDummyPlayer02::~CDummyPlayer02()
{
}

void CDummyPlayer02::update()
{
	if (KEY_OFF('D'))
		CSceneManager::getInst()->sceneChange(SCENE::STAGE_01);
	
	fPoint playerPos = getPlayerPos();
	if (KEY_OFF(VK_ESCAPE))
		CSceneManager::getInst()->sceneChange(SCENE::TITLE);

	if (KEY_HOLD(VK_UP) && (playerPos.y - getSize().y / 2.f) > 0.f)	
		playerPos.y -= m_fSpeed * DT;

	if (KEY_HOLD(VK_DOWN) && (playerPos.y + getSize().y / 2.f) < (float)WINSIZEY)
		playerPos.y += m_fSpeed * DT;

	if (KEY_HOLD(VK_LEFT) && (playerPos.x - getSize().x / 2.f) > 0.f)
		playerPos.x -= m_fSpeed * DT;

	if (KEY_HOLD(VK_RIGHT) && (playerPos.x + getSize().y / 2.f) < (float)WINSIZEX)
		playerPos.x += m_fSpeed * DT;

	if ((playerPos.x != m_fpPrevPos.x) || (playerPos.y != m_fpPrevPos.y))
	{
		m_fvDir.x = playerPos.x - m_fpPrevPos.x;
		m_fvDir.y = playerPos.y - m_fpPrevPos.y;
		setDir(m_fvDir);
	}

	if (KEY_ON('A') && m_uiBullet)
		createBullet();

	if (KEY_ON(VK_SPACE))
		isMode = true;
	if (KEY_OFF(VK_SPACE))
		isMode = false;

	m_fpPrevPos.x = playerPos.x;
	m_fpPrevPos.y = playerPos.y;

	setPlayerPos(playerPos);
}

void CDummyPlayer02::render(HDC hDC)
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

	// 보유한 총알 그림
	if (0 < m_uiBullet)
	{
		SetTextColor(hDC, RGB(52, 0, 0));
		LPCWSTR strMessage = L"........";

		if (m_uiBullet <= 8)
			TextOutW(hDC, pos.x - 15, pos.y + 20, strMessage, m_uiBullet);
		else if (8 < m_uiBullet && m_uiBullet <= 16)
		{
			TextOutW(hDC, pos.x - 15, pos.y + 20, strMessage, 8);
			TextOutW(hDC, pos.x - 15, pos.y + 24, strMessage, (m_uiBullet - 8));
		}
		else
		{
			TextOutW(hDC, pos.x - 15, pos.y + 20, strMessage, 8);
			TextOutW(hDC, pos.x - 15, pos.y + 24, strMessage, 8);
			TextOutW(hDC, pos.x - 15, pos.y + 28, strMessage, (m_uiBullet - 16));
		}
	}
}
