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
	getCollider()->setSize(fPoint((float)P_sizex - 5, (float)P_sizey - 5));
	getCollider()->setOffset(fPoint(0.f, 15.f));
	getCollider()->setShape(SHAPE::RECT);

	m_pTex = CResourceManager::getInst()->LoadTextrue(KEY_RES::TEX_PLAYER, L"texture\\mario.bmp");

	createAnimator();
								//		lt,						slice,					step
	createAnim(L"smStand_L",	m_pTex, fPoint(0.f, 0.f),		fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.5f, 1);
	createAnim(L"smStand_R",	m_pTex, fPoint(0.f, 65.f),		fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.5f, 1);
	createAnim(L"bgStand_L",	m_pTex, fPoint(0.f, 129.f),		fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.5f, 1);
	createAnim(L"bgStand_R",	m_pTex, fPoint(0.f, 193.f),		fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.5f, 1);
	createAnim(L"frStand_L",	m_pTex, fPoint(0.f, 257.f),		fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.5f, 1);
	createAnim(L"frStand_R",	m_pTex, fPoint(0.f, 321.f),		fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.5f, 1);
	
	createAnim(L"smJump_L",		m_pTex, fPoint(65.f, 0.f),		fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 1);
	createAnim(L"smJump_R",		m_pTex, fPoint(65.f, 65.f),		fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 1);
	createAnim(L"bgJump_L",		m_pTex, fPoint(65.f, 129.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 1);
	createAnim(L"bgJump_R",		m_pTex, fPoint(65.f, 193.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 1);
	createAnim(L"frJump_L",		m_pTex, fPoint(65.f, 257.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 1);
	createAnim(L"frJump_R",		m_pTex, fPoint(65.f, 321.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 1);

	createAnim(L"smSlide_L",	m_pTex, fPoint(129.f, 0.f),		fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 1);
	createAnim(L"smSlide_R",	m_pTex, fPoint(129.f, 65.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 1);
	createAnim(L"bgSlide_L",	m_pTex, fPoint(129.f, 129.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 1);
	createAnim(L"bgSlide_R",	m_pTex, fPoint(129.f, 193.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 1);
	createAnim(L"frSlide_L",	m_pTex, fPoint(129.f, 257.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 1);
	createAnim(L"frSlide_R",	m_pTex, fPoint(129.f, 321.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 1);

	createAnim(L"smZig_L",		m_pTex, fPoint(193.f, 0.f),		fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 1);
	createAnim(L"smZig_R",		m_pTex, fPoint(193.f, 65.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 1);
	createAnim(L"bgZig_L",		m_pTex, fPoint(193.f, 129.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 1);
	createAnim(L"bgZig_R",		m_pTex, fPoint(193.f, 193.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 1);
	createAnim(L"frZig_L",		m_pTex, fPoint(193.f, 257.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 1);
	createAnim(L"frZig_R",		m_pTex, fPoint(193.f, 321.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 1);

	createAnim(L"smRun_L",		m_pTex, fPoint(257.f, 0.f),		fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 2);
	createAnim(L"smRun_R",		m_pTex, fPoint(257.f, 65.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 2);
	createAnim(L"bgRun_L",		m_pTex, fPoint(257.f, 129.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 3);
	createAnim(L"bgRun_R",		m_pTex, fPoint(257.f, 193.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 3);
	createAnim(L"frRun_L",		m_pTex, fPoint(257.f, 257.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 3);
	createAnim(L"frRun_R",		m_pTex, fPoint(257.f, 321.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 3);
	
	// fr _R ���� �� ������ ��� �� �� ����
	// ���� ���۵� �� ��

	getAnimator()->play(L"smStand_R");

}

CPlayer::~CPlayer()
{
}

void CPlayer::update()
{
	fPoint pos = getPos();

	if (KEY_HOLD(VK_LEFT) && KEY_NONE(VK_RIGHT))	// ���� Ű �Է�
	{
		if (m_uiState & S_DIR)							// ������ ���� �־�����
		{
			m_uiState &= ~(S_DIR);							// �������� �ٲ��ְ�
			m_fSpeedL = 0.f;								// ���� �ӵ� 0
		}

		if (m_fSpeedL < (float)P_ACCEL)
			m_fSpeedL += P_ACCEL * fDT;					// ���� �ӵ� ����

		if (m_fSpeedR > 0.f)
			drawMario(L"Zig");
	}
	else											// ���� Ű �� ������
	{
		if (m_fSpeedL > 0.f)
		{
			m_fSpeedL -= P_DECEL * fDT;					// ���� �ӵ� ����

		}
		if (m_fSpeedL < 0.f) m_fSpeedL = 0.f;

	}

	if (KEY_HOLD(VK_RIGHT) && KEY_NONE(VK_LEFT))	// ������ Ű �Է�
	{
		if (!(m_uiState & S_DIR))						// ���� ���� �־�����
		{
			m_uiState |= S_DIR;								// ���������� �ٲ��ְ�
			m_fSpeedR = 0.f;								// ���ۼӵ� 0
		}

		if (m_fSpeedR < (float)P_ACCEL)
			m_fSpeedR += P_ACCEL * fDT;					// ������ �ӵ� ����

		if (m_fSpeedL > 0.f)
			drawMario(L"Zig");
	}
	else											// ������ Ű �� ������
	{
		if (m_fSpeedR > 0.f)
			m_fSpeedR -= P_DECEL * fDT;					// ������ �ӵ� ����

		if (m_fSpeedR < 0.f) m_fSpeedR = 0.f;
	}


	if (KEY_NONE(VK_RIGHT) && KEY_NONE(VK_LEFT) && (m_fSpeedR > 0.f || m_fSpeedL > 0.f))
		drawMario(L"Slide");

	pos.x += (m_fSpeedR - m_fSpeedL) * fDT;

	if (m_fSpeedR == 0 && m_fSpeedL == 0)
	{
		drawMario(L"Stand");
	}
	//else
	//{
	//	drawMario(L"Run");
	//}

	if (KEY_ON(VK_SPACE) && !(m_uiState & S_JUMP))	// ���߿� ���� �����鼭 �����̽� ������ ����
	{
		m_fGravity = 0.f;
		m_fSpeedY = P_JUMPSPD;
		m_uiState |= S_JUMP;
	}

	if (m_uiBottomCnt <= 0)
		m_uiState |= S_JUMP;

	if (m_uiState & S_JUMP)							// ���߿� �� ���¸� �߷� ����
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

	//
	wchar_t szBuffer[255] = {};
	swprintf_s(szBuffer, L"[Flatform Imitation] BottomCnt : %d", m_uiBottomCnt);
	SetWindowText(hWnd, szBuffer);

	// �ӽ÷� ���� �ǵ����� Ű
	if (KEY_ON('R'))
		pos = { 100.f, 500.f };

	setPos(pos);
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
	}
	else
	{
		pFire->setDir(fVec2(-1.f, 1.f));
		pFire->setPos(fPoint(pos.x - size.x / 2, pos.y));
	}

	createObj(pFire, OBJ::FIREBALL);
}


// TODO �浹�˻�� ���⵵ �� �� �־�� ��
void CPlayer::collisionKeep(CCollider* pOther)
{
}

// ���� �������� top�̳� bottom�̳Ĵ� ���..
// �浹�˻� �¿� ���� ���� �����ε�
// �÷��̾� �׷��� ���� �θ� �Ǳ� ������
void CPlayer::collisionEnter(CCollider* pOther)
{
	
}

// exit���� bottomCnt--�� �� �ż� �ô��� exit�� ȣ��� ���� ���� �����ӿ� �浹�߾��� �̹� �����ӿ� �浹 �� �� ����
// None���� ����, ������ none�� ���ۿ�
// ���� �浹 ���� �˰� �ϰų� �׻� �߷� �ۿ��ϰ� �ؾ�..
void CPlayer::collisionExit(CCollider* pOther)
{
	
}

// Ű���常���� ������ �׸���
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
	setSize(fPoint((float)P_sizex - 5, (float)P_sizey - 5));
	getCollider()->setOffset(fPoint(0.f, 15.f));
}
void CPlayer::setBgMario()
{
	setSize(fPoint((float)P_SIZEX - 5, (float)P_SIZEY - 5));
	getCollider()->setOffset(fPoint(0.f, 5.f));
}
// TODO �浹 ������ ������ ���� ��
// �ٴڿ� ���ְ� �ϴ� ���.. 
// �浹ü�� �浹 ī��Ʈ ���� �޾ƿ��� �浹���� �˸�
// �߹ٴڿ� tile �浹 ī��Ʈ 0�̸� ���߿� �� ���� �����ϰ� �߷� �����ϸ� �Ǵµ�
// �ٵ� ī��Ʈ�� ������ ī��Ʈ���� ��
// �ļ��� static ������ enter�� ++ exit�� -- �ؼ� 0�̸� �������� �Ҽ���? 