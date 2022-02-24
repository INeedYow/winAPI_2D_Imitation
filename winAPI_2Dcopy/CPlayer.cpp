#include "framework.h"
#include "CPlayer.h"
#include "CMissile.h"
#include "CScene.h"

CPlayer::CPlayer()
{
	setPos(fPoint(100.f, WINSIZEY / 2.f));
	setSize(fPoint(75.f, 75.f));
	fSpeed = 200;
}

CPlayer::~CPlayer()
{
}

void CPlayer::update()
{
	fPoint playerPos = getPos();

	if (KEY_HOLD(VK_UP)		&& (playerPos.y - getSize().y / 2.f) > 0.f)		// 맵 탈출 방지
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
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(100, 150, 100));
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
	DeleteObject(hBrush);
}

// 모든 오브젝트를 벡터 배열로 관리하는 씬에 미사일을 동적할당해서 추가해주면 될 것이고
// 현재 씬에 추가하면 되고 현재 씬을 관리하는 건 씬 매니저
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