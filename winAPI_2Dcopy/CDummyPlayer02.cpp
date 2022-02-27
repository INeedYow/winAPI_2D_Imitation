#include "framework.h"
#include "CDummyPlayer02.h"
#include "CItem_Scanner.h"
#include "CScene.h"

CDummyPlayer02::CDummyPlayer02()
{
	uiPrevBullet = GETBULLET;
	szText = L"����Ű( �� �� �� �� )�� ��������";
	uiCheck = 0;
}

CDummyPlayer02::~CDummyPlayer02()
{
}

void CDummyPlayer02::update()
{
	if (KEY_OFF('D'))
		CSceneManager::getInst()->sceneChange(SCENE::STAGE_01);
	if (KEY_OFF(VK_ESCAPE))
		CSceneManager::getInst()->sceneChange(SCENE::TITLE);

	UINT bulletCnt = GETBULLET;

	if (isScan && scanTimer > 0.f)				// ��ĳ��
	{
		if (1 == uiCheck )
		{
			szText = L"��ĳ�ʴ� �Ȱ� �� ��ġ�� �巯����";
			uiCheck++;
		}
		scanTimer -= DT;
		if (0.f > scanTimer)
			isScan = false;
	}
	if (bulletCnt > uiPrevBullet && 0 == uiCheck)
	{
		szText = L"\'A\'Ű�� �Ѿ��� �߻��� �� �־��";
		createNext();
		uiCheck++;
	}
	if (2 <= uiCheck)
		g_resultTimer += DT;
	if (g_resultTimer > 4.f)
		szText = L"���� \'D\'Ű�� ���� �����ؿ�";

	fPoint playerPos = getPlayerPos();

	if (KEY_HOLD(VK_UP) && (playerPos.y - getSize().y / 2.f) > 0.f)		// �� Ż�� ����
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

	if (KEY_ON('A') && uiBullet)
		createBullet();

	m_fpPrevPos.x = playerPos.x;
	m_fpPrevPos.y = playerPos.y;
	
	uiPrevBullet = bulletCnt;
	setPlayerPos(playerPos);
}

void CDummyPlayer02::render(HDC hDC)
{
	int sight = isMode ? P_SIGHTON : P_SIGHTOFF;
	fPoint pos = getPlayerPos();
	fPoint size = getSize();

	HPEN hPen, hOriginalPen;
	HBRUSH hBrush, hOriginalBrush;
	HFONT hFont, hOriginalFont;

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

	// ������ �Ѿ� �׸�
	if (0 < uiBullet)
	{
		SetTextColor(hDC, RGB(52, 0, 0));
		LPCWSTR strMessage = L"........";

		if (uiBullet <= 8)
			TextOutW(hDC, pos.x - 15, pos.y + 20, strMessage, uiBullet);
		else if (8 < uiBullet && uiBullet <= 16)
		{
			TextOutW(hDC, pos.x - 15, pos.y + 20, strMessage, 8);
			TextOutW(hDC, pos.x - 15, pos.y + 24, strMessage, (uiBullet - 8));
		}
		else
		{
			TextOutW(hDC, pos.x - 15, pos.y + 20, strMessage, 8);
			TextOutW(hDC, pos.x - 15, pos.y + 24, strMessage, 8);
			TextOutW(hDC, pos.x - 15, pos.y + 28, strMessage, (uiBullet - 16));
		}
	}

	
	hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Comic Sans MS"));
	hOriginalFont = (HFONT)SelectObject(hDC, hFont);

	SetTextColor(hDC, RGB(102, 51, 255));
	TextOutW(hDC, pos.x - 100, pos.y - 40, szText, wcslen(szText));

	SelectObject(hDC, hOriginalFont);
	DeleteObject(hFont);

}

void CDummyPlayer02::createNext()
{
	CScene* pCurScene = CSceneManager::getInst()->getCurScene();

	CItem_Scanner* pItemScanner1 = new CItem_Scanner;
	CItem_Scanner* pItemScanner2 = new CItem_Scanner;
	pItemScanner1->setPos(fPoint(640.f, 300.f));
	pItemScanner2->setPos(fPoint(640.f, 360.f));
	pCurScene->addObject(pItemScanner1, OBJ::DROPITEM);
	pCurScene->addObject(pItemScanner2, OBJ::DROPITEM);
}
