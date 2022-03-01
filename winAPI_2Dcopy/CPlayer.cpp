#include "framework.h"
#include "CPlayer.h"
#include "CMissile.h"
#include "CScene.h"
#include "CTexture.h"

CPlayer::CPlayer()
{	// 텍스쳐 입히는 내용 추가
	m_pTex = new CTexture;
	// 패스매니저 통해서 경로 받아와서
	wstring strFilepath = CPathManager::getInst()->getContentPath();
	// 해당 옵젝 경로 추가하고
	strFilepath += L"texture\\Player.bmp";
	// 경로로 Load()실행
	m_pTex->load(strFilepath);

	setPos(fPoint(100.f, WINSIZEY / 2.f));
	setSize(fPoint(75.f, 75.f));
	fSpeed = 200;
}

CPlayer::~CPlayer()
{	// 텍스쳐 있다면 해제
	if (nullptr != m_pTex)
		delete m_pTex;
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
	// texture 적용
	int width = (int)(m_pTex->getBmpWidth());
	int height = (int)(m_pTex->getBmpHeight());

	fPoint pos = getPos();

	// hdc, 출력할 좌표x,y, 원본 넓이, 높이, 이미지 hdc, 가져올 이미지 시작 좌표x,y, 기타 기능/방법)
	BitBlt(hDC, 
		(int)(pos.x - (float)(width / 2)),
		(int)(pos.y - (float)(height / 2)),
		width, height,
		m_pTex->getDC(),
		0, 0, SRCCOPY);


	// texture 입히기 전
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