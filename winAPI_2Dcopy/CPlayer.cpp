#include "framework.h"
#include "CPlayer.h"
#include "CScene.h"
#include "CBullet.h"
#include "CItem_Bullet.h"

#include "SelectGDI.h"

CPlayer::CPlayer()
{
	setPlayerPos(fPoint((float)WINSIZEX / 2, (float)WINSIZEY / 2));
	setSize(fPoint((float)P_SIZE, (float)P_SIZE));
	m_fSpeed = P_SPEED;
	m_fpPrevPos = fPoint(1.f, 1.f);
	m_fvDir = fVec2(1.f, 1.f);
	strMsg = L"........";
}

CPlayer::~CPlayer()
{
	isMode = false;
}

void CPlayer::update()
{
	g_resultTimer += DT;

	if (isScan && scanTimer > 0.f)				// ��ĳ��
	{
		scanTimer -= DT;
		if (0.f > scanTimer)
			isScan = false;
	}

	fPoint playerPos = getPlayerPos();
	if (KEY_OFF(VK_ESCAPE))
		CSceneManager::getInst()->sceneChange(SCENE::TITLE);

	if (KEY_HOLD(VK_UP) && (playerPos.y - getSize().y / 2.f) > 0.f)		// �� Ż�� ����
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

	// ���� �浹ó��
	fPoint chkPos;
	fPoint chkSize;
	CScene* pCurScene = CSceneManager::getInst()->getCurScene();
	vector<CObject*>* pVecArr = pCurScene->getVecArr();
	
	//vector<CObject*>::iterator tmpIter;

	for (int i = 0; i < pVecArr[(int)OBJ::ENEMY].size(); i++)
	{	
		chkPos = pVecArr[(int)OBJ::ENEMY][i]->getPos();
		chkSize = pVecArr[(int)OBJ::ENEMY][i]->getSize();

		// enemy�� �浹
		if(playerPos.COLL_CC(playerPos, (int)O_HSIZE, chkPos, (int)chkSize.x / 2))
				death();
	}

	////������ �浹ó�� (�������� �������ʿ��� �ϵ��� ����)
	////TODO : ����� �۾� �ʿ�...
	//// iter�� �浹�� ������Ʈ delete�ϰ� iter�� ����Ű�� �ִ� �ε����� (size - 1)�� �ε����� �ƴ϶�� ����
	///*for(vector<CObject*>::iterator iter = pVecArr[(int)OBJ::DROPITEM].begin(); 
	//	iter != pVecArr[(int)OBJ::DROPITEM].end(); iter++)*/
	//for (int i = 0; i < pVecArr[(int)OBJ::DROPITEM].size(); i++)
	//{
	//	chkPos = pVecArr[(int)OBJ::DROPITEM][i]->getPos();

	//	RECT chkRt = { (int)chkPos.x - (int)I_HSIZE , (int)chkPos.y - (int)I_HSIZE,
	//				   (int)chkPos.x + (int)I_HSIZE , (int)chkPos.y + (int)I_HSIZE };
	//	// item ����
	//	// pVecArr�� �����ϸ� CObject* �� �����ؼ� getEA()�Լ��� ȣ���� �� ����
	//	// TODO : �ϴ� ���Ƿ� rand�Լ��� ��������
	//	if (playerPos.COLL_CR(playerPos, (int)O_HSIZE, chkRt))
	//	{	// ���� ������ key������ �з��ҷ��µ� �Ұ���?
	//		UCHAR bullet = (CItem_Bullet*)(pVecArr[(int)OBJ::DROPITEM][i])->getEA();
	//		uiBullet += rand() % (IB_MAXEA - IB_MINEA + 1) + IB_MINEA;
	//		if (uiBullet > 24)
	//			uiBullet = 24;
	//	}
	//}

	if (KEY_ON('A') && uiBullet)
		createBullet();

	
	//// �þ� ON OFF
	//// �� �̷��� �ϸ� ON OFF ���� ����� �۵� �� ��?
	//if (KEY_ON(VK_SPACE) && m_battery.isEnough())
	//{
	//	SETMODE(true);
	//	float fBatt = m_battery.getBattery();
	//	fBatt -= BAT_INITCONSUME;
	//	m_battery.setBattery(fBatt);
	//}
	//else if (KEY_HOLD(VK_SPACE) && isMode && m_battery.getBattery() > 0)	SETMODE(true);
	//else																	SETMODE(false);

	// ������ǥ ����
	m_fpPrevPos.x = playerPos.x;
	m_fpPrevPos.y = playerPos.y;

	setPlayerPos(playerPos);
	
	// ���� ����ϱ� Scene���� ������Ʈ ��Ű�� �� �ƴ϶� �÷��̾� ������ �� ���͸� ���� ȣ�����ִ� �� �´µ��ؼ� �̷��� �ٲٷ��ߴµ�
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
			TextOutW(hDC, pos.x - 15, pos.y + 20, strMsg, uiBullet);
		else if (8 < uiBullet && uiBullet <= 16)
		{
			TextOutW(hDC, pos.x - 15, pos.y + 20, strMsg, 8);
			TextOutW(hDC, pos.x - 15, pos.y + 24, strMsg, (uiBullet - 8));
		}
		else
		{
			TextOutW(hDC, pos.x - 15, pos.y + 20, strMsg, 8);
			TextOutW(hDC, pos.x - 15, pos.y + 24, strMsg, 8);
			TextOutW(hDC, pos.x - 15, pos.y + 28, strMsg, (uiBullet - 16));
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
