#include "framework.h"
#include "CPlayer.h"
#include "CMissile.h"
#include "CScene.h"
#include "CTexture.h"

CPlayer::CPlayer()
{	// �ؽ��� ������ ���� �߰�
	m_pTex = new CTexture;
	// �н��Ŵ��� ���ؼ� ��� �޾ƿͼ�
	wstring strFilepath = CPathManager::getInst()->getContentPath();
	// �ش� ���� ��� �߰��ϰ�
	strFilepath += L"texture\\Player.bmp";
	// ��η� Load()����
	m_pTex->load(strFilepath);

	setPos(fPoint(100.f, WINSIZEY / 2.f));
	setSize(fPoint(75.f, 75.f));
	fSpeed = 200;
}

CPlayer::~CPlayer()
{	// �ؽ��� �ִٸ� ����
	if (nullptr != m_pTex)
		delete m_pTex;
}

void CPlayer::update()
{
	fPoint playerPos = getPos();

	if (KEY_HOLD(VK_UP)		&& (playerPos.y - getSize().y / 2.f) > 0.f)		// �� Ż�� ����
		playerPos.y -= fSpeed * DT;

	if (KEY_HOLD(VK_DOWN)	&& (playerPos.y + getSize().y / 2.f) < (float)WINSIZEY)
		playerPos.y += fSpeed * DT;

	if (KEY_HOLD(VK_LEFT)	&& (playerPos.x - getSize().x / 2.f) > 0.f)
		playerPos.x -= fSpeed * DT;

	if (KEY_HOLD(VK_RIGHT)	&& (playerPos.x + getSize().y / 2.f) < (float)WINSIZEX)
		playerPos.x += fSpeed * DT;

	if (KEY_ON(VK_SPACE))
		createMissile();

	setPos(playerPos);
}

void CPlayer::render(HDC hDC)
{
	// texture ����
	int width = (int)(m_pTex->getBmpWidth());
	int height = (int)(m_pTex->getBmpHeight());

	fPoint pos = getPos();

	// hdc, ����� ��ǥx,y, ���� ����, ����, �̹��� hdc, ������ �̹��� ���� ��ǥx,y, ��Ÿ ���/���)
	BitBlt(hDC, 
		(int)(pos.x - (float)(width / 2)),
		(int)(pos.y - (float)(height / 2)),
		width, height,
		m_pTex->getDC(),
		0, 0, SRCCOPY);


	// texture ������ ��
	/*HPEN hPen = CreatePen(PS_SOLID, 1, RGB(100, 150, 100));
	HBRUSH hBrush = CreateSolidBrush(RGB(150, 200, 150));

	HPEN hOriginalPen = (HPEN)SelectObject(hDC, hPen);
	HBRUSH hOriginalBrush = (HBRUSH)SelectObject(hDC, hBrush);

	Rectangle(hDC,
		(int)(getPos().x - getSize().x / 2),
		(int)(getPos().y - getSize().y / 2),
		(int)(getPos().x + getSize().x / 2),
		(int)(getPos().y + getSize().y / 2) );

	SelectObject(hDC, hOriginalPen);
	SelectObject(hDC, hOriginalBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);*/
}

// ��� ������Ʈ�� ���� �迭�� �����ϴ� ���� �̻����� �����Ҵ��ؼ� �߰����ָ� �� ���̰�
// ���� ���� �߰��ϸ� �ǰ� ���� ���� �����ϴ� �� �� �Ŵ���
void CPlayer::createMissile()
{
	fPoint missilePos = getPos();
	missilePos.x += getSize().x / 2.f;

	CMissile* pMissile = new CMissile;
	pMissile->setDir(fVec2(1, -1));
	pMissile->setPos(missilePos);

	CMissile* pMissile2 = new CMissile;
	pMissile2->setDir(fVec2(1, 0));
	pMissile2->setPos(missilePos);

	CMissile* pMissile3 = new CMissile;
	pMissile3->setDir(fVec2(1, -2));
	pMissile3->setPos(missilePos);

	CMissile* pMissile4 = new CMissile;
	pMissile4->setDir(fVec2(0, -2));
	pMissile4->setPos(missilePos);

	CMissile* pMissile5 = new CMissile;
	pMissile5->setDir(fVec2(-1, -1));
	pMissile5->setPos(missilePos);

	CScene* pCurScene = CSceneManager::getInst()->getCurScene();
	pCurScene->addObject(pMissile, OBJ::MISSILE);
	pCurScene->addObject(pMissile2, OBJ::MISSILE);
	pCurScene->addObject(pMissile3, OBJ::MISSILE);
	pCurScene->addObject(pMissile4, OBJ::MISSILE);
	pCurScene->addObject(pMissile5, OBJ::MISSILE);
}