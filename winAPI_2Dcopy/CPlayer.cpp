#include "framework.h"
#include "CPlayer.h"
#include "CFireball.h"
#include "CAnimator.h"
#include "CAnimation.h"

UINT    CPlayer::s_uiCoin = 0;

CPlayer::CPlayer()
{
	setPos(fPoint(0.f, 0.f));
	setSize(fPoint((float)P_sizex, (float)P_sizey));
	setType(OBJ::PLAYER);
	m_fSpeedL	= 0.f;
	m_fSpeedR	= 0.f;
	m_fSpeedY	= 0.f;
	m_fGravity  = 0.f;
	m_fTimer	= 0.f;
	m_eMario	= MARIO::smMARIO;
	m_uiBottomCnt = 0;
	m_uiState	= 0;
	m_uiState |= S_JUMP;

	createCollider();
	getCollider()->setSize(fPoint((float)P_sizex - 8, (float)P_sizey - 6));
	getCollider()->setOffset(fPoint(0.f, 20.f));
	getCollider()->setShape(SHAPE::RECT);

	m_pTex = loadTex(KEY_RES::TEX_PLAYER, L"texture\\mario.bmp");

	createAnimator();
								//		lt,						slice,					step
	createAnim(L"smStand_L",	m_pTex, fPoint(0.f, 0.f),		fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.5f, 1);
	createAnim(L"smStand_R",	m_pTex, fPoint(0.f, 64.f),		fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.5f, 1);
	createAnim(L"bgStand_L",	m_pTex, fPoint(0.f, 128.f),		fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.5f, 1);
	createAnim(L"bgStand_R",	m_pTex, fPoint(0.f, 192.f),		fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.5f, 1);
	createAnim(L"frStand_L",	m_pTex, fPoint(0.f, 256.f),		fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.5f, 1);
	createAnim(L"frStand_R",	m_pTex, fPoint(0.f, 320.f),		fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.5f, 1);
	
	createAnim(L"smJump_L",		m_pTex, fPoint(64.f, 0.f),		fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 1);
	createAnim(L"smJump_R",		m_pTex, fPoint(64.f, 64.f),		fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 1);
	createAnim(L"bgJump_L",		m_pTex, fPoint(64.f, 128.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 1);
	createAnim(L"bgJump_R",		m_pTex, fPoint(64.f, 192.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 1);
	createAnim(L"frJump_L",		m_pTex, fPoint(64.f, 256.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 1);
	createAnim(L"frJump_R",		m_pTex, fPoint(64.f, 320.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 1);

	createAnim(L"smSlide_L",	m_pTex, fPoint(128.f, 0.f),		fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.2f, 1);
	createAnim(L"smSlide_R",	m_pTex, fPoint(128.f, 64.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.2f, 1);
	createAnim(L"bgSlide_L",	m_pTex, fPoint(128.f, 128.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.2f, 1);
	createAnim(L"bgSlide_R",	m_pTex, fPoint(128.f, 192.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.2f, 1);
	createAnim(L"frSlide_L",	m_pTex, fPoint(128.f, 256.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.2f, 1);
	createAnim(L"frSlide_R",	m_pTex, fPoint(128.f, 320.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.2f, 1);

	createAnim(L"smZig_L",		m_pTex, fPoint(192.f, 0.f),		fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.2f, 1);
	createAnim(L"smZig_R",		m_pTex, fPoint(192.f, 64.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.2f, 1);
	createAnim(L"bgZig_L",		m_pTex, fPoint(192.f, 128.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.2f, 1);
	createAnim(L"bgZig_R",		m_pTex, fPoint(192.f, 192.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.2f, 1);
	createAnim(L"frZig_L",		m_pTex, fPoint(192.f, 256.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.2f, 1);
	createAnim(L"frZig_R",		m_pTex, fPoint(192.f, 320.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.2f, 1);

	createAnim(L"smRun_L",		m_pTex, fPoint(256.f, 0.f),		fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.2f, 3);
	createAnim(L"smRun_R",		m_pTex, fPoint(256.f, 64.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.2f, 3);
	createAnim(L"bgRun_L",		m_pTex, fPoint(256.f, 128.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.2f, 3);
	createAnim(L"bgRun_R",		m_pTex, fPoint(256.f, 192.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.2f, 3);
	createAnim(L"frRun_L",		m_pTex, fPoint(256.f, 256.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.2f, 3);
	createAnim(L"frRun_R",		m_pTex, fPoint(256.f, 320.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.2f, 3);
	
	// ���� ���� �� �� -> player update()���� animator ������Ʈ �� ���༭ �׷���

	PLAY(L"smStand_R");

}

CPlayer::~CPlayer()
{
}

void CPlayer::update()
{
	fPoint pos = getPos();

	if (KEY_HOLD(VK_LEFT) && KEY_NONE(VK_RIGHT))		// ���� Ű �Է�
	{
		if (m_uiState & S_DIR)								// ������ ���� �־�����
		{	
			m_uiState &= ~(S_DIR);							// �������� �ٲ��ְ�
			m_fSpeedL = 0.f;									// ���� �ӵ� 0
		}

		if (m_fSpeedL < (float)P_ACCEL)
			m_fSpeedL += P_ACCEL * fDT;						// ���� �ӵ� ����

		if (m_fSpeedR > 60.f)
			drawMario(L"Zig");
	}
	else												// ���� Ű �� ������
	{
		if (m_fSpeedL > 0.f)
		{
			m_fSpeedL -= P_DECEL * fDT;						// ���� �ӵ� ����

		}
		if (m_fSpeedL < 0.f) m_fSpeedL = 0.f;

	}

	if (KEY_HOLD(VK_RIGHT) && KEY_NONE(VK_LEFT))		// ������ Ű �Է�
	{
		if (!(m_uiState & S_DIR))							// ���� ���� �־�����
		{
			m_uiState |= S_DIR;									// ���������� �ٲ��ְ�
			m_fSpeedR = 0.f;									// ���ۼӵ� 0
		}

		if (m_fSpeedR < (float)P_ACCEL)
			m_fSpeedR += P_ACCEL * fDT;						// ������ �ӵ� ����

		if (m_fSpeedL > 60.f)
			drawMario(L"Zig");
	}
	else												// ������ Ű �� ������
	{
		if (m_fSpeedR > 0.f)
			m_fSpeedR -= P_DECEL * fDT;						// ������ �ӵ� ����

		if (m_fSpeedR < 0.f) m_fSpeedR = 0.f;
	}

	pos.x += (m_fSpeedR - m_fSpeedL) * fDT;

	if (m_fSpeedR == 0 && m_fSpeedL == 0)
	{
		drawMario(L"Stand");
	}
	else
	{
		if (KEY_NONE(VK_RIGHT) && KEY_NONE(VK_LEFT) &&
			((0.f < m_fSpeedR && m_fSpeedR < 50.f) ||
			( 0.f < m_fSpeedL && m_fSpeedL < 50.f)))
			drawMario(L"Slide");

		else if (m_fSpeedR > 50.f && m_fSpeedL == 0.f ||
			m_fSpeedL > 50.f && m_fSpeedR == 0.f)
			drawMario(L"Run");
	}

	if (KEY_ON(VK_SPACE) && !(m_uiState & S_JUMP))		// ���߿� ���� �����鼭 �����̽� ������ ����
	{
		m_fGravity = 0.f;
		m_fSpeedY = P_JUMPSPD;
		m_uiState |= S_JUMP;
	}

	if (m_uiBottomCnt <= 0)
		m_uiState |= S_JUMP;

	if (m_uiState & S_JUMP)								// ���߿� �� ���¸� �߷� ����
	{
		pos.y -= ((m_fSpeedY - m_fGravity) * fDT);

		if (m_fGravity < (float)P_GRAVMAX)
			m_fGravity += P_GRAV * fDT;

		drawMario(L"Jump");
	}

	if (MARIO::frMARIO == m_eMario && KEY_ON('A'))		// fire ����, aŰ�� �Ҳ� �߻� 
		createFireball();

	if (KEY_ON('P'))
	{
		switch (m_eMario)
		{
		case MARIO::smMARIO:
			m_eMario = MARIO::bgMARIO;
			setBgMario();
			break;
		case MARIO::bgMARIO:
			m_eMario = MARIO::frMARIO;
			break;
		case MARIO::frMARIO:
			m_eMario = MARIO::smMARIO;
			setSmMario();
			break;
		}
	}

	// ���� ���
	if (KEY_ON('O'))
	{
		if (m_uiState & S_CAMERA)
		{
			setFocus(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
			CCameraManager::getInst()->setTraceObj(nullptr);
			m_uiState &= ~(S_CAMERA);
		}
		else
		{
			setTrace(this);
			m_uiState |= S_CAMERA;
		}
	}

	// bottomCnt ��¿�..
	wchar_t szBuffer[255] = {};
	swprintf_s(szBuffer, L"[Bobrio] BottomCnt : %d \t Coin : %d", m_uiBottomCnt, s_uiCoin);
	SetWindowText(hWnd, szBuffer);

	// �ӽ÷� ���� �ǵ����� Ű
	if (KEY_ON('R'))
	{
		pos = { 100.f, 500.f };
		m_uiBottomCnt = 0;
	}

	setPos(pos);
	getAnimator()->update();
}
// TODO �� ������ �������� Ʈ���� Ƚ�� 1 ������Ű�� (�� ��ȯ �� �ٽ� ����)


void CPlayer::render(HDC hDC)
{
	componentRender(hDC);
}

UINT CPlayer::getCoin()
{
	return s_uiCoin;
}

void CPlayer::setCoin(UINT coin)
{
	s_uiCoin = coin;
}

void CPlayer::createFireball()
{
	fPoint pos = getPos();
	fPoint size = getSize();
	CFireball* pFire = new CFireball();

	if (m_uiState & S_DIR)					// �߻�ü �߻����, ��ġ����
	{
		pFire->setDir(fVec2(1.f, 1.f));
		pFire->setPos(fPoint(pos.x + size.x / 2, pos.y));
		pFire->getAnimator()->play(L"Fireball_R");
	}
	else
	{
		pFire->setDir(fVec2(-1.f, 1.f));
		pFire->setPos(fPoint(pos.x - size.x / 2, pos.y));
		pFire->getAnimator()->play(L"Fireball_L");
	}

	createObj(pFire, OBJ::FIREBALL);
}

// TODO �浹 �������� ���װ� ��û ���� ��..
// �̴� �������� ��� m_uiBottomCnt�� ��� �����ϱ⵵ ��
// ���� ���� ���� ī��Ʈ �̻�����

void CPlayer::collisionKeep(CCollider* pOther)
{
	switch (pOther->getOwner()->getType())
	{
	case OBJ::BLOCK:
	case OBJ::TILE:
		switch (COLLRR(getCollider(), pOther))
		{
		case DIR::LEFT:
		{
			fPoint pos = getPos();
			pos.x = pOther->getPos().x + (pOther->getOffset().x - pOther->getSize().x - getCollider()->getSize().x) / 2;
			setPos(pos);
			m_fSpeedR = 0.f;
			break;
		}
		case DIR::RIGHT:
		{
			fPoint pos = getPos();
			pos.x = pOther->getPos().x + (pOther->getOffset().x + pOther->getSize().x + getCollider()->getSize().x) / 2;
			setPos(pos);
			m_fSpeedL = 0.f;
			break;
		}
		break;
		}
	}
}

// ���� �ٴ� �հ� �����ϴ� ����
void CPlayer::collisionEnter(CCollider* pOther)
{
	switch (pOther->getOwner()->getType())
	{
	case OBJ::BLOCK:
	case OBJ::TILE:
		switch (COLLRR(getCollider(), pOther))
		{
		case DIR::TOP:	// ����
			if (m_uiState & S_JUMP)
				m_uiState &= ~(S_JUMP);
			m_uiBottomCnt++;
			break;
		case DIR::LEFT:	// offset.x�� �˾Ƽ� ������ �����״� ������ +���ָ� �ɵ�, size�� ������� -+
		{
			fPoint pos = getPos();
			pos.x = pOther->getPos().x + (pOther->getOffset().x - pOther->getSize().x - getCollider()->getSize().x) / 2;
			setPos(pos);
			m_fSpeedR = 0.f;
			break;
		}
		case DIR::RIGHT:
		{
			fPoint pos = getPos();
			pos.x = pOther->getPos().x + (pOther->getOffset().x + pOther->getSize().x + getCollider()->getSize().x) / 2;
			setPos(pos);
			m_fSpeedL = 0.f;
			break;
		}
		break;
		}
		break;
		// TODO : ���� ������Ʈ �����Ϸ��� enum OBJ�� ���µ� ITEM�� ���� ������ �� ���־
		// �����ۿ� ���� Ű���� �� ����ų� �� ����ȭ�� enum���� ������ �ҵ�
	case OBJ::ITEM:	// �ӽ� �׽�Ʈ�� �׳� ITEM
		setCoin(getCoin() + 1);
		break;
	}
}

void CPlayer::collisionExit(CCollider* pOther)
{
	switch (pOther->getOwner()->getType())
	{
	case OBJ::BLOCK:
	case OBJ::TILE:
		switch (COLLRR(getCollider(), pOther))
		{
		case DIR::TOP:	// ����
			if (--m_uiBottomCnt <= 0)
				m_uiState |= S_JUMP;
			break;
		}
		break;
	}
}

// Ű����� ������ �׸���
void CPlayer::drawMario(const wstring& commonName)
{
	wstring str;

	switch (m_eMario)
	{
	case MARIO::smMARIO:
		str = L"sm";
		break;

	case MARIO::bgMARIO:
		str = L"bg";
		break;

	case MARIO::frMARIO:
		str = L"fr";
		break;
	}

	if (m_uiState & S_DIR)
		str += (commonName + L"_R");
	else
		str += (commonName + L"_L");

	PLAY(str);
}

void CPlayer::setSmMario()
{
	setSize(fPoint((float)P_sizex - 8, (float)P_sizey - 6));
	getCollider()->setOffset(fPoint(0.f, 20.f));
}
void CPlayer::setBgMario()
{
	setSize(fPoint((float)P_SIZEX - 8, (float)P_SIZEY - 6));
	getCollider()->setOffset(fPoint(0.f, 6.f));
}