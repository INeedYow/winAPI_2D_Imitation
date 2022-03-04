#include "framework.h"
#include "CPlayer.h"

UINT    CPlayer::s_uiCoin = 0;

CPlayer::CPlayer()
{
	setPos(fPoint(0.f, 0.f));
	setSize(fPoint(P_SSIZEX, P_SSIZEY));
	m_fSpeedL	= 0.f;
	m_fSpeedR	= 0.f;
	m_fSpeedY	= 0.f;
	m_fTimer	= 0.f;
	m_fGravity  = 0.f;

	setType(OBJ::PLAYER);

	m_uiState	= 0;

	createCollider();
	getCollider()->setSize(fPoint(P_SSIZEX - 5, P_SSIZEY - 5));
	getCollider()->setOffset(fPoint(0.f, 5.f));
	getCollider()->setShape(SHAPE::RECT);
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
	}
	else											// ���� Ű �� ������
	{
		if (m_fSpeedL > 0.f)
			m_fSpeedL -= P_DECEL * fDT;					// ���� �ӵ� ����

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
	}
	else											// ������ Ű �� ������
	{
		if (m_fSpeedR > 0.f)
			m_fSpeedR -= P_DECEL * fDT;					// ������ �ӵ� ����

		if (m_fSpeedR < 0.f) m_fSpeedR = 0.f;
	}

	pos.x += m_fSpeedR * fDT - m_fSpeedL * fDT;


	if (KEY_ON(VK_SPACE) && !(m_uiState & S_JUMP))	// ���߿� ���� �����鼭 �����̽� ������ ����
	{
		m_fGravity = 0.f;
		m_fSpeedY = P_JUMPSPD;
		m_uiState |= S_JUMP;
	}

	if (m_uiState & S_JUMP)							// ���߿� �� ���¸� �߷� ����
	{
		pos.y -= ((m_fSpeedY - m_fGravity) * fDT);

		if (m_fGravity < 1200.f)
			m_fGravity += 400 * fDT;
	}

	// TODO �Ҳɹ߻�
	if ((m_uiState & S_FIRE) && KEY_ON('A'))		// fire ����, aŰ�� �Ҳ� �߻� 
		createFireball();

	// �ӽ÷� ���� �ǵ����� Ű
	if (KEY_ON('R'))
		pos = { 100.f, 500.f };

	setPos(pos);
}
// TODO �� ������ �������� Ʈ���� Ƚ�� 1 ������Ű�� (�� ��ȯ �� �ٽ� ����)


void CPlayer::render(HDC hDC)
{

	Rectangle(hDC,
		(int)(getPos().x - getSize().x / 2),
		(int)(getPos().y - getSize().y / 2),
		(int)(getPos().x + getSize().x / 2),
		(int)(getPos().y + getSize().y / 2));

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
}


// TODO �浹�˻�� ���⵵ �� �� �־�� ��
void CPlayer::collisionKeep(CCollider* pOther)
{
}

void CPlayer::collisionEnter(CCollider* pOther)
{
	switch (pOther->getOwner()->getType())
	{
	case OBJ::TILE:
		if (m_uiState & S_JUMP)			// ���� ���¸� ���
			m_uiState &= ~(S_JUMP);

		m_fGravity = 0.f;
		break;
		
	case OBJ::ITEM:
		// TODO ������ ����, ��, ����, �� ITEM���� ������ �� �з��ؾ� �ҵ�
		// (obj�� type ���� �� ��ó��)
		// OBJ enum���� �з��ؼ� ���� �Ǳ� �ϴµ� �׷��� �� ��� item�ε� item���� �� ���̴µ�
		break;
	}
}

void CPlayer::collisionExit(CCollider* pOther)
{
	switch (pOther->getOwner()->getType())
	{
	//case OBJ::TILE:
	//	if (!(m_uiState & S_JUMP))		// ���߿� �� ���·� ���
	//	{
	//		m_uiState |= S_JUMP;
	//		m_fSpeedY = 0.f;
	//	}
	//	break;
	}
}
// TODO �浹 ������ ������ ���� ��
// �ٴڿ� ���ְ� �ϴ� ���.. 
// �浹ü�� �浹 ī��Ʈ ���� �޾ƿ��� �浹���� �˸�
// �߹ٴڿ� tile �浹 ī��Ʈ 0�̸� ���߿� �� ���� �����ϰ� �߷� �����ϸ� �Ǵµ�
// �ٵ� ī��Ʈ�� ������ ī��Ʈ���� ��
// �ļ��� static ������ enter�� ++ exit�� -- �ؼ� 0�̸� �������� �Ҽ���? 