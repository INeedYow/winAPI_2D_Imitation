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

	if (KEY_HOLD(VK_LEFT) && KEY_NONE(VK_RIGHT))	// 왼쪽 키 입력
	{
		if (m_uiState & S_DIR)							// 오른쪽 보고 있었으면
		{
			m_uiState &= ~(S_DIR);							// 왼쪽으로 바꿔주고
			m_fSpeedL = 0.f;								// 시작 속도 0
		}

		if (m_fSpeedL < (float)P_ACCEL)
			m_fSpeedL += P_ACCEL * fDT;					// 왼쪽 속도 증가
	}
	else											// 왼쪽 키 안 누르면
	{
		if (m_fSpeedL > 0.f)
			m_fSpeedL -= P_DECEL * fDT;					// 왼쪽 속도 감소

		if (m_fSpeedL < 0.f) m_fSpeedL = 0.f;
	}

	if (KEY_HOLD(VK_RIGHT) && KEY_NONE(VK_LEFT))	// 오른쪽 키 입력
	{
		if (!(m_uiState & S_DIR))						// 왼쪽 보고 있었으면
		{
			m_uiState |= S_DIR;								// 오른쪽으로 바꿔주고
			m_fSpeedR = 0.f;								// 시작속도 0
		}

		if (m_fSpeedR < (float)P_ACCEL)
			m_fSpeedR += P_ACCEL * fDT;					// 오른쪽 속도 증가
	}
	else											// 오른쪽 키 안 누르면
	{
		if (m_fSpeedR > 0.f)
			m_fSpeedR -= P_DECEL * fDT;					// 오른쪽 속도 감소

		if (m_fSpeedR < 0.f) m_fSpeedR = 0.f;
	}

	pos.x += m_fSpeedR * fDT - m_fSpeedL * fDT;


	if (KEY_ON(VK_SPACE) && !(m_uiState & S_JUMP))	// 공중에 있지 않으면서 스페이스 누르면 점프
	{
		m_fGravity = 0.f;
		m_fSpeedY = P_JUMPSPD;
		m_uiState |= S_JUMP;
	}

	if (m_uiState & S_JUMP)							// 공중에 뜬 상태면 중력 적용
	{
		pos.y -= ((m_fSpeedY - m_fGravity) * fDT);

		if (m_fGravity < 1200.f)
			m_fGravity += 400 * fDT;
	}

	// TODO 불꽃발사
	if ((m_uiState & S_FIRE) && KEY_ON('A'))		// fire 상태, a키로 불꽃 발사 
		createFireball();

	// 임시로 만든 되돌리는 키
	if (KEY_ON('R'))
		pos = { 100.f, 500.f };

	setPos(pos);
}
// TODO 맵 밖으로 떨어지면 트라이 횟수 1 증가시키고 (씬 전환 후 다시 복귀)


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


// TODO 충돌검사로 방향도 알 수 있어야 함
void CPlayer::collisionKeep(CCollider* pOther)
{
}

void CPlayer::collisionEnter(CCollider* pOther)
{
	switch (pOther->getOwner()->getType())
	{
	case OBJ::TILE:
		if (m_uiState & S_JUMP)			// 점프 상태면 토글
			m_uiState &= ~(S_JUMP);

		m_fGravity = 0.f;
		break;
		
	case OBJ::ITEM:
		// TODO 아이템 동전, 꽃, 버섯, 별 ITEM으로 묶으면 또 분류해야 할듯
		// (obj에 type 변수 쓴 것처럼)
		// OBJ enum에서 분류해서 쓰면 되긴 하는데 그러면 또 모두 item인데 item으로 안 묶이는데
		break;
	}
}

void CPlayer::collisionExit(CCollider* pOther)
{
	switch (pOther->getOwner()->getType())
	{
	//case OBJ::TILE:
	//	if (!(m_uiState & S_JUMP))		// 공중에 뜬 상태로 토글
	//	{
	//		m_uiState |= S_JUMP;
	//		m_fSpeedY = 0.f;
	//	}
	//	break;
	}
}
// TODO 충돌 방향의 구분이 들어가야 함
// 바닥에 서있게 하는 방법.. 
// 충돌체의 충돌 카운트 변수 받아오고 충돌방향 알면
// 발바닥에 tile 충돌 카운트 0이면 공중에 뜸 상태 적용하고 중력 적용하면 되는데
// 근데 카운트가 누구랑 카운트인지 모름
// 꼼수로 static 변수로 enter에 ++ exit에 -- 해서 0이면 떨어지게 할수도? 