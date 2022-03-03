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

	// �����ڿ��� ȣ��
	// �׳� getCollider()�� �� �� �ִ� ������? -> CObject���� ������ �θ��� �Լ��̱� ����(collider�Լ� �ƴϾ���)
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

	if (isScan && scanTimer > 0.f)				// ��ĳ��
	{
		scanTimer -= fDT;
		if (0.f > scanTimer)
			isScan = false;
	}

	fPoint playerPos = getPlayerPos();
	if (KEY_OFF(VK_ESCAPE))
		CSceneManager::getInst()->sceneChange(SCENE::TITLE);

	if (KEY_HOLD(VK_UP) && (playerPos.y - getSize().y / 2.f) > 0.f)		// �� Ż�� ����
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
		
	
	// �� ���� ��ǥ�� ���� ��ǥ�� ���� ���⺤�� ����
		// ��ǥ �̵��� ���ٸ� �������� ����(���� ������ ���) <- �ǵ���� �� ��
	// TODO : ��ǥ �̵� ������ �ֱ� ������ ��� �ϰ� ������ �����¿�θ� ��
		// �밢������ �����̴ٰ� �� Ű�� ��Ȯ�� ���ÿ� ���� ��찡 ��� �׷��� -> �³�;
		// -> ���� �Է¿� ���� ó���� �ٸ��� �ϴ��� �ٸ� �����?..

	if ((playerPos.x != m_fpPrevPos.x) || (playerPos.y != m_fpPrevPos.y))
	{
		m_fvDir.x = playerPos.x - m_fpPrevPos.x;
		m_fvDir.y = playerPos.y - m_fpPrevPos.y;
		setDir(m_fvDir);
	}

	//// ���� �浹ó��
	//fPoint chkPos;
	//fPoint chkSize;
	//CScene* pCurScene = CSceneManager::getInst()->getCurScene();
	//vector<CObject*>* pVecArr = pCurScene->getVecArr();

	//for (int i = 0; i < pVecArr[(int)OBJ::ENEMY].size(); i++)
	//{	
	//	chkPos = pVecArr[(int)OBJ::ENEMY][i]->getPos();
	//	chkSize = pVecArr[(int)OBJ::ENEMY][i]->getSize();

	//	// enemy�� �浹
	//	if(playerPos.COLL_CC(playerPos, (int)O_HSIZE, chkPos, (int)chkSize.x / 2))
	//			death();
	//}

	if (KEY_ON('A') && uiBullet)
		createBullet();

	// ������ǥ ����
	m_fpPrevPos.x = playerPos.x;
	m_fpPrevPos.y = playerPos.y;

	setPlayerPos(playerPos);
	
	// TODO ���͸� �÷��̾ ������Ʈ�ϵ���
	// m_battery.update();
}

void CPlayer::render(HDC hDC)
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
		(int)(pos.y + size.y / 2) );

	// ������ �Ѿ� �׸�
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
