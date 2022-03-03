#include "framework.h"
#include "CDummyPlayer02.h"
#include "CItem_Scanner.h"
#include "CScene.h"

#include "SelectGDI.h"

CDummyPlayer02::CDummyPlayer02()
{
	uiPrevBullet = GETBULLET;
	szText = L"����Ű( �� �� �� �� )�� ��������";
	uiCheck = 0;

	createCollider();
	getCollider()->setSize(fPoint(P_SIZE - 2, P_SIZE - 2));
	getCollider()->setOffset(fPoint((float)0, (float)0));
	getCollider()->setShape(SHAPE::CIRCLE);
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
		scanTimer -= fDT;
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
		g_resultTimer += fDT;
	if (g_resultTimer > 4.f)
		szText = L"���� \'D\'Ű�� ���� �����ؿ�";

	fPoint playerPos = getPlayerPos();

	if (KEY_HOLD(VK_UP) && (playerPos.y - getSize().y / 2.f) > 0.f)		// �� Ż�� ����
		playerPos.y -= m_fSpeed * fDT;

	if (KEY_HOLD(VK_DOWN) && (playerPos.y + getSize().y / 2.f) < (float)WINSIZEY)
		playerPos.y += m_fSpeed * fDT;

	if (KEY_HOLD(VK_LEFT) && (playerPos.x - getSize().x / 2.f) > 0.f)
		playerPos.x -= m_fSpeed * fDT;

	if (KEY_HOLD(VK_RIGHT) && (playerPos.x + getSize().y / 2.f) < (float)WINSIZEX)
		playerPos.x += m_fSpeed * fDT;

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
	fPoint pos = getPlayerPos();
	fPoint size = getSize();

	// mode�� ���� �����ϱ� good
	SelectGDI pen(hDC, PEN::P_EDGEON, PEN::P_EDGEOFF, isMode);
	SelectGDI brush(hDC, BRUSH::P_BRUON, BRUSH::P_BRUOFF, isMode);

	Ellipse(hDC,
		(int)(pos.x - size.x / 2),
		(int)(pos.y - size.y / 2),
		(int)(pos.x + size.x / 2),
		(int)(pos.y + size.y / 2));

	// ������ �Ѿ� �׸�
	if (0 < uiBullet)
	{
		SetTextColor(hDC, RGB(52, 0, 0));
		LPCWSTR strMessage = L"........";

		if (uiBullet <= 8)
			TextOutW(hDC, (int)pos.x - 15, (int)pos.y + 20, strMessage, uiBullet);
		else if (8 < uiBullet && uiBullet <= 16)
		{
			TextOutW(hDC, (int)pos.x - 15, (int)pos.y + 20, strMessage, 8);
			TextOutW(hDC, (int)pos.x - 15, (int)pos.y + 24, strMessage, (uiBullet - 8));
		}
		else
		{
			TextOutW(hDC, (int)pos.x - 15, (int)pos.y + 20, strMessage, 8);
			TextOutW(hDC, (int)pos.x - 15, (int)pos.y + 24, strMessage, 8);
			TextOutW(hDC, (int)pos.x - 15, (int)pos.y + 28, strMessage, (uiBullet - 16));
		}
	}

	SelectGDI font(hDC, FONT::COMIC18);

	SetTextColor(hDC, RGB(102, 51, 255));
	TextOutW(hDC, (int)pos.x - 95, (int)pos.y - 45, szText, (int)wcslen(szText));
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
