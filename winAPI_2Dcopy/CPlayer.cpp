#include "framework.h"
#include "CPlayer.h"

CPlayer::CPlayer()
{
	setPos(fPoint(200.f, 200.f));
	setSize(fPoint(P_SSIZEX, P_SSIZEY));
	m_fSpeed = P_SPD;
	m_fAccel = 0.f;
	m_fTimer = 0.f;

	m_ucState = 0;

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
}

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
