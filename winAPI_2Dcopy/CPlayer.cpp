#include "framework.h"
#include "CPlayer.h"
#include "CScene.h"
#include "CBullet.h"

CPlayer::CPlayer()
{
	setPos(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
	setSize(fPoint(P_SIZE, P_SIZE));
	m_fSpeed = P_SPEED;
	m_uiBullet = 0;
	m_fpPrevPos = fPoint(1.f, 1.f);
	m_fvDir = fVec2(1.f, 1.f);
	fpPos.x = WINSIZEX / 2.f;
	fpPos.y = WINSIZEY / 2.f;
}

CPlayer::~CPlayer()
{
	isMode = false;
}

void CPlayer::update()
{
	g_resultTimer += DT;

	fPoint playerPos = getPlayerPos();
	if (KEY_OFF(VK_ESCAPE))
		CSceneManager::getInst()->sceneChange(SCENE::TITLE);

	if (KEY_HOLD(VK_UP) && (playerPos.y - getSize().y / 2.f) > 0.f)		// 맵 탈출 방지
		playerPos.y -= m_fSpeed * DT;

	if (KEY_HOLD(VK_DOWN) && (playerPos.y + getSize().y / 2.f) < (float)WINSIZEY)
		playerPos.y += m_fSpeed * DT;

	if (KEY_HOLD(VK_LEFT) && (playerPos.x - getSize().x / 2.f) > 0.f)
		playerPos.x -= m_fSpeed * DT;

	if (KEY_HOLD(VK_RIGHT) && (playerPos.x + getSize().y / 2.f) < (float)WINSIZEX)
		playerPos.x += m_fSpeed * DT;

	if (KEY_ON('R') && m_uiBullet < 24)			// 치트키
		m_uiBullet++;

	// 내 이전 좌표와 현재 좌표로 현재 방향벡터 구함
		// 좌표 이동이 없다면 갱신하지 않음(이전 방향대로 쏘도록) <- 의도대로 안 됨
	// TODO : 좌표 이동 없으면 최근 방향대로 쏘도록 하고 싶은데 상하좌우로만 쏨

	if ((playerPos.x != m_fpPrevPos.x) || (playerPos.y != m_fpPrevPos.y))
	{
		m_fvDir.x = playerPos.x - m_fpPrevPos.x;
		m_fvDir.y = playerPos.y - m_fpPrevPos.y;
		setDir(m_fvDir);
	}

	// 몬스터, 아이템 충돌처리(아이템 충돌은 아이템에서 했는데 플레이어 총알 증가시키려면 플레이어 업데이트 함수에서 해야하니까 여기서 해야하나)
	fPoint chkPos;
	CScene* pCurScene = CSceneManager::getInst()->getCurScene();
	vector<CObject*>* pVecArr = pCurScene->getVecArr();

	for (int i = 0; i < pVecArr[(int)OBJ::ENEMY].size(); i++)
	{	
		chkPos = pVecArr[(int)OBJ::ENEMY][i]->getPos();

		// enemy와 충돌
		if(playerPos.COLL_CC(playerPos, (int)O_HSIZE, chkPos, (int)O_HSIZE))
				death();
	}

	if (KEY_ON('A') && m_uiBullet)
		createBullet();

	// space 누르는 동안만 시야모드 전환
	if (KEY_ON(VK_SPACE))
		isMode = true;
	if (KEY_OFF(VK_SPACE))
		isMode = false;
	
	// 이전좌표 갱신
	m_fpPrevPos.x = playerPos.x;
	m_fpPrevPos.y = playerPos.y;

	setPlayerPos(playerPos);
}

void CPlayer::render(HDC hDC)
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

	hPen = CreatePen(PS_SOLID, P_PEN, isMode ? RGB(125,150,100) : RGB(75, 100, 50));
	hBrush = CreateSolidBrush(isMode ? RGB(150, 200, 100) : RGB(100, 125, 75));

	hOriginalPen = (HPEN)SelectObject(hDC, hPen);
	hOriginalBrush = (HBRUSH)SelectObject(hDC, hBrush);

	Ellipse(hDC,
		(int)(pos.x - size.x / 2),
		(int)(pos.y - size.y / 2),
		(int)(pos.x + size.x / 2),
		(int)(pos.y + size.y / 2) );

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

void CPlayer::setDir(fVec2 vec)
{
	m_fvDir = vec.normalize();
}

bool CPlayer::getMode()
{
	return isMode;
}

fPoint CPlayer::getPlayerPos()
{
	return fpPos;
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

	m_uiBullet--;
	g_resultBullet++;
}

void CPlayer::setBullet(UINT ea)
{
	m_uiBullet = ea;
}

void CPlayer::death()
{
	CSceneManager::getInst()->sceneChange(SCENE::RESULT);
}
