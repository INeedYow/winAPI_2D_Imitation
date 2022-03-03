#include "framework.h"
#include "CPlayer.h"
#include "CScene.h"
#include "CBullet.h"
#include "CItem_Bullet.h"
#include "CCollider.h"

#include "SelectGDI.h"

CPlayer::CPlayer()
{
	setPlayerPos(fPoint((float)WINSIZEX / 2, (float)WINSIZEY / 2));
	setSize(fPoint((float)P_SIZE, (float)P_SIZE));
	m_fSpeed = P_SPEED;
	m_fpPrevPos = fPoint(1.f, 1.f);
	m_fvDir = fVec2(1.f, 1.f);
	strMsg = L"........";

	// 생성자에서 호출
	// 그냥 getCollider()를 쓸 수 있는 이유는? -> CObject에서 구현된 부모의 함수이기 때문(collider함수 아니었음)
	createCollider();
	getCollider()->setSize(fPoint((float)P_SIZE - 2, (float)P_SIZE - 2));
	getCollider()->setOffset(fPoint((float)0, (float)0));
	getCollider()->setShape(SHAPE::CIRCLE);
}

CPlayer::~CPlayer()
{
	isMode = false;
}

void CPlayer::update()
{
	g_resultTimer += fDT;

	if (isScan && scanTimer > 0.f)				// 스캐너
	{
		scanTimer -= fDT;
		if (0.f > scanTimer)
			isScan = false;
	}

	fPoint playerPos = getPlayerPos();
	if (KEY_OFF(VK_ESCAPE))
		CSceneManager::getInst()->sceneChange(SCENE::TITLE);

	if (KEY_HOLD(VK_UP) && (playerPos.y - getSize().y / 2.f) > 0.f)		// 맵 탈출 방지
		playerPos.y -= m_fSpeed * fDT;

	if (KEY_HOLD(VK_DOWN) && (playerPos.y + getSize().y / 2.f) < (float)WINSIZEY)
		playerPos.y += m_fSpeed * fDT;

	if (KEY_HOLD(VK_LEFT) && (playerPos.x - getSize().x / 2.f) > 0.f)
		playerPos.x -= m_fSpeed * fDT;

	if (KEY_HOLD(VK_RIGHT) && (playerPos.x + getSize().y / 2.f) < (float)WINSIZEX)
		playerPos.x += m_fSpeed * fDT;

	if (KEY_ON('O')) uiBullet = 24;		// dont cheat
	if (KEY_ON('I'))
	{
		isScan = true;
		scanTimer += 5.f;				// dont cheat
	}
		
	
	// 내 이전 좌표와 현재 좌표로 현재 방향벡터 구함
		// 좌표 이동이 없다면 갱신하지 않음(이전 방향대로 쏘도록) <- 의도대로 안 됨
	// TODO : 좌표 이동 없으면 최근 방향대로 쏘도록 하고 싶은데 상하좌우로만 쏨
		// 대각선으로 움직이다가 두 키를 정확히 동시에 떼는 경우가 없어서 그런가 -> 맞네;
		// -> 복수 입력에 대한 처리를 다르게 하던가 다른 방법은?..

	if ((playerPos.x != m_fpPrevPos.x) || (playerPos.y != m_fpPrevPos.y))
	{
		m_fvDir.x = playerPos.x - m_fpPrevPos.x;
		m_fvDir.y = playerPos.y - m_fpPrevPos.y;
		setDir(m_fvDir);
	}

	//// 몬스터 충돌처리
	//fPoint chkPos;
	//fPoint chkSize;
	//CScene* pCurScene = CSceneManager::getInst()->getCurScene();
	//vector<CObject*>* pVecArr = pCurScene->getVecArr();

	//for (int i = 0; i < pVecArr[(int)OBJ::ENEMY].size(); i++)
	//{	
	//	chkPos = pVecArr[(int)OBJ::ENEMY][i]->getPos();
	//	chkSize = pVecArr[(int)OBJ::ENEMY][i]->getSize();

	//	// enemy와 충돌
	//	if(playerPos.COLL_CC(playerPos, (int)O_HSIZE, chkPos, (int)chkSize.x / 2))
	//			death();
	//}

	if (KEY_ON('A') && uiBullet)
		createBullet();

	// 이전좌표 갱신
	m_fpPrevPos.x = playerPos.x;
	m_fpPrevPos.y = playerPos.y;

	setPlayerPos(playerPos);
	
	// TODO 배터리 플레이어가 업데이트하도록
	// m_battery.update();
}

void CPlayer::render(HDC hDC)
{
	fPoint pos = getPlayerPos();
	fPoint size = getSize();

	// mode에 따라 구분하기 good
	SelectGDI pen(hDC, PEN::P_EDGEON, PEN::P_EDGEOFF, isMode);
	SelectGDI brush(hDC, BRUSH::P_BRUON, BRUSH::P_BRUOFF, isMode);

	Ellipse(hDC,
		(int)(pos.x - size.x / 2),
		(int)(pos.y - size.y / 2),
		(int)(pos.x + size.x / 2),
		(int)(pos.y + size.y / 2) );

	// 보유한 총알 그림
	if (0 < uiBullet)
	{
		SetTextColor(hDC, RGB(52, 0, 0));

		if (uiBullet <= 8)
			TextOutW(hDC, (int)pos.x - 15, (int)pos.y + 20, strMsg, uiBullet);
		else if (8 < uiBullet && uiBullet <= 16)
		{
			TextOutW(hDC, (int)pos.x - 15, (int)pos.y + 20, strMsg, 8);
			TextOutW(hDC, (int)pos.x - 15, (int)pos.y + 24, strMsg, (uiBullet - 8));
		}
		else
		{
			TextOutW(hDC, (int)pos.x - 15, (int)pos.y + 20, strMsg, 8);
			TextOutW(hDC, (int)pos.x - 15, (int)pos.y + 24, strMsg, 8);
			TextOutW(hDC, (int)pos.x - 15, (int)pos.y + 28, strMsg, (uiBullet - 16));
		}
	}
	//m_battery.render(hDC);
	componentRender(hDC);
}

void CPlayer::setDir(fVec2 vec)
{
	m_fvDir = vec.normalize();
}

bool CPlayer::getMode()
{
	return isMode;
}

bool CPlayer::getScan()
{
	return isScan;
}

float CPlayer::getScanTimer()
{
	return scanTimer;
}

void CPlayer::setScanTimer(float time)
{
	scanTimer = time;

	isScan = time <= 0.f ? false : true;
}

void CPlayer::setMode(bool mode)
{
	isMode = mode;
}

fPoint CPlayer::getPlayerPos()
{
	return fpPos;
}

UINT CPlayer::getBullet()
{
	return uiBullet;
}

void CPlayer::setPlayerPos(fPoint pos)
{
	fpPos = pos;
}

void CPlayer::createBullet()
{
	CBullet* pBullet = new CBullet(getPlayerPos(), m_fvDir);

	CScene* pCurScene = CSceneManager::getInst()->getCurScene();
	pCurScene->addObject(pBullet, OBJ::BULLET);

	uiBullet--;
	g_resultBullet++;
}

void CPlayer::setBullet(UINT bullet)
{
	uiBullet = bullet;
	if (uiBullet > 24)
		uiBullet = 24;
}

void CPlayer::death()
{
	CSceneManager::getInst()->sceneChange(SCENE::RESULT);
}
