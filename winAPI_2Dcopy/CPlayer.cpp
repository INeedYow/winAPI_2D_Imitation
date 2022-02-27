#include "framework.h"
#include "CPlayer.h"
#include "CScene.h"
#include "CBullet.h"
#include "CItem_Bullet.h"

CPlayer::CPlayer()
{
	setPos(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
	setSize(fPoint(P_SIZE, P_SIZE));
	m_fSpeed = P_SPEED;
	uiBullet = 0;
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

	if (isScan && scanTimer > 0.f)				// 스캐너
	{
		scanTimer -= DT;
		if (0.f > scanTimer)
			isScan = false;
	}

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

	if (KEY_ON('O')) uiBullet = 24;		// dont cheat
	if (KEY_ON('I'))
	{
		isScan = true;
		scanTimer += 3.f;				// dont cheat
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

	// 몬스터 충돌처리
	fPoint chkPos;
	CScene* pCurScene = CSceneManager::getInst()->getCurScene();
	vector<CObject*>* pVecArr = pCurScene->getVecArr();
	
	//vector<CObject*>::iterator tmpIter;

	for (int i = 0; i < pVecArr[(int)OBJ::ENEMY].size(); i++)
	{	
		chkPos = pVecArr[(int)OBJ::ENEMY][i]->getPos();

		// enemy와 충돌
		if(playerPos.COLL_CC(playerPos, (int)O_HSIZE, chkPos, (int)O_HSIZE))
				death();
	}

	// 아이템 충돌처리 (아이템은 아이템쪽에서 하도록 했음)
	// TODO : 지우는 작업 필요...
	// iter로 충돌한 오브젝트 delete하고 iter가 가리키고 있는 인덱스가 (size - 1)끝 인덱스가 아니라면 당기기
	/*for(vector<CObject*>::iterator iter = pVecArr[(int)OBJ::DROPITEM].begin(); 
		iter != pVecArr[(int)OBJ::DROPITEM].end(); iter++)*/
	//for (int i = 0; i < pVecArr[(int)OBJ::DROPITEM].size(); i++)
	//{
	//	chkPos = pVecArr[(int)OBJ::DROPITEM][i]->getPos();

	//	RECT chkRt = { (int)chkPos.x - (int)I_HSIZE , (int)chkPos.y - (int)I_HSIZE,
	//				   (int)chkPos.x + (int)I_HSIZE , (int)chkPos.y + (int)I_HSIZE };
	//	// item 습득
	//	// pVecArr로 접근하면 CObject* 로 접근해서 getEA()함수를 호출할 수 없음
	//	// TODO : 일단 임의로 rand함수로 돌려놓음
	//	if (playerPos.COLL_CR(playerPos, (int)O_HSIZE, chkRt))
	//	{	// 먹은 아이템 key값으로 분류할랬는데 불가능?
	//		uiBullet += rand() % (I_B_MAXEA - I_B_MINEA + 1) + I_B_MINEA;
	//		if (uiBullet > 24)
	//			uiBullet = 24;
	//	}
	//}

	if (KEY_ON('A') && uiBullet)
		createBullet();

	
	//// 시야 ON OFF
	//// 왜 이렇게 하면 ON OFF 조건 제대로 작동 안 함?
	//if (KEY_ON(VK_SPACE) && m_battery.isEnough())
	//{
	//	SETMODE(true);
	//	float fBatt = m_battery.getBattery();
	//	fBatt -= BAT_INITCONSUME;
	//	m_battery.setBattery(fBatt);
	//}
	//else if (KEY_HOLD(VK_SPACE) && isMode && m_battery.getBattery() > 0)	SETMODE(true);
	//else																	SETMODE(false);

	// 이전좌표 갱신
	m_fpPrevPos.x = playerPos.x;
	m_fpPrevPos.y = playerPos.y;

	setPlayerPos(playerPos);
	
	// 소유 관계니까 Scene에서 업데이트 시키는 게 아니라 플레이어 업뎃할 때 배터리 업뎃 호출해주는 게 맞는듯해서 이렇게 바꾸려했는데
	// TODO (질문) 왜 심각한 오류.라고 에러 뜨는데 이유를 모르겠어요
	// m_battery.update();
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
	//m_battery.render(hDC);
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

void CPlayer::addScanTimer(float time)
{
	scanTimer += time;
}

void CPlayer::setMode(bool mode)
{
	isMode = mode;
}

void CPlayer::setScan(bool scan)
{
	isScan = scan;
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
