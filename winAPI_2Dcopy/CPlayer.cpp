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

	if (KEY_HOLD(VK_UP) && (playerPos.y - getSize().y / 2.f) > 0.f)		// �� Ż�� ����
		playerPos.y -= m_fSpeed * DT;

	if (KEY_HOLD(VK_DOWN) && (playerPos.y + getSize().y / 2.f) < (float)WINSIZEY)
		playerPos.y += m_fSpeed * DT;

	if (KEY_HOLD(VK_LEFT) && (playerPos.x - getSize().x / 2.f) > 0.f)
		playerPos.x -= m_fSpeed * DT;

	if (KEY_HOLD(VK_RIGHT) && (playerPos.x + getSize().y / 2.f) < (float)WINSIZEX)
		playerPos.x += m_fSpeed * DT;

	if (KEY_ON('R')) m_uiBullet = 24;		// dont cheat
		

	// �� ���� ��ǥ�� ���� ��ǥ�� ���� ���⺤�� ����
		// ��ǥ �̵��� ���ٸ� �������� ����(���� ������ ���) <- �ǵ���� �� ��
	// TODO : ��ǥ �̵� ������ �ֱ� ������ ��� �ϰ� ������ �����¿�θ� ��

	if ((playerPos.x != m_fpPrevPos.x) || (playerPos.y != m_fpPrevPos.y))
	{
		m_fvDir.x = playerPos.x - m_fpPrevPos.x;
		m_fvDir.y = playerPos.y - m_fpPrevPos.y;
		setDir(m_fvDir);
	}

	// ����, ������ �浹ó��(������ �浹�� �����ۿ��� �ߴµ� �÷��̾� �Ѿ� ������Ű���� �÷��̾� ������Ʈ �Լ����� �ؾ��ϴϱ� ���⼭ �ؾ��ϳ�)
	fPoint chkPos;
	CScene* pCurScene = CSceneManager::getInst()->getCurScene();
	vector<CObject*>* pVecArr = pCurScene->getVecArr();
	
	//vector<CObject*>::iterator tmpIter;

	for (int i = 0; i < pVecArr[(int)OBJ::ENEMY].size(); i++)
	{	
		chkPos = pVecArr[(int)OBJ::ENEMY][i]->getPos();

		// enemy�� �浹
		if(playerPos.COLL_CC(playerPos, (int)O_HSIZE, chkPos, (int)O_HSIZE))
				death();
	}

	// ����� �۾� �ʿ�...
	// iter�� �浹�� ������Ʈ delete�ϰ� iter�� ����Ű�� �ִ� �ε����� (size - 1)�� �ε����� �ƴ϶�� ����
	/*for(vector<CObject*>::iterator iter = pVecArr[(int)OBJ::DROPITEM].begin(); 
		iter != pVecArr[(int)OBJ::DROPITEM].end(); iter++)*/
	for (int i = 0; i < pVecArr[(int)OBJ::DROPITEM].size(); i++)
	{
		chkPos = pVecArr[(int)OBJ::DROPITEM][i]->getPos();

		RECT chkRt = { (int)chkPos.x - (int)I_HSIZE , (int)chkPos.y - (int)I_HSIZE,
					   (int)chkPos.x + (int)I_HSIZE , (int)chkPos.y + (int)I_HSIZE };
		// item ����
		// pVecArr�� �����ϸ� CObject* �� �����ؼ� getEA()�Լ��� ȣ���� �� ����
		// TODO : �ϴ� ���Ƿ� rand�Լ��� ��������
		if (playerPos.COLL_CR(playerPos, (int)O_HSIZE, chkRt))
		{
			m_uiBullet += rand() % (I_B_MAXEA - I_B_MINEA + 1) + I_B_MINEA;
			if (m_uiBullet > 24) 
				m_uiBullet = 24;
		}
	}

	if (KEY_ON('A') && m_uiBullet)
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
	// TODO (����) �� �ɰ��� ����.��� ���� �ߴµ� ������ �𸣰ھ��
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

	// ������ �Ѿ� �׸�
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
	// TODO �׾��� �� ó�� �߰� ����
	CSceneManager::getInst()->sceneChange(SCENE::RESULT);
}
