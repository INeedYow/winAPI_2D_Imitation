#include "framework.h"
#include "CPlayer.h"
#include "CFireball.h"
#include "CAnimator.h"
#include "CAnimation.h"

UINT    CPlayer::s_uiCoin = 0;
bool	CPlayer::s_bTransform = false;

CPlayer::CPlayer()
{
	setPos(fPoint(0.f, 0.f));
	setSize(fPoint((float)P_sizex, (float)P_sizey));
	setName(OBJNAME::MARIO);
	m_fSpeedL	= 0.f;
	m_fSpeedR	= 0.f;
	m_fSpeedY	= 0.f;
	m_fGravity	= 0.f;
	m_fTransformTimer	= 0.f;
	m_fInvincibleTimer	= 0.f;
	m_eMario	= TYPE_MARIO::smMARIO;
	m_iBottomCnt = 0;
	m_uiState	= 0;
	m_uiState |= S_JUMP;
	s_bTransform = false;

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
	
	createAnim(L"bgFromSmall_L",m_pTex, fPoint(384.f, 0.f),		fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 2);
	createAnim(L"bgFromSmall_R",m_pTex, fPoint(384.f, 64.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 2);
	createAnim(L"smFromBig_L",	m_pTex, fPoint(448.f, 0.f),		fPoint(64.f, 64.f),		fPoint(-64.f, 0.f),		0.3f, 2);
	createAnim(L"smFromBig_R",	m_pTex, fPoint(448.f, 64.f),	fPoint(64.f, 64.f),		fPoint(-64.f, 0.f),		0.3f, 2);
	createAnim(L"frFromSmall_L",m_pTex, fPoint(512.f, 0.f),		fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 2);
	createAnim(L"frFromSmall_R",m_pTex, fPoint(512.f, 64.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 2);

	createAnim(L"smDeath",		m_pTex, fPoint(512.f, 64.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.5f, 1);

	PLAY(L"smStand_R");

}

CPlayer::~CPlayer()
{
}

void CPlayer::update()
{
	if (s_bTransform)
	{
		m_fTransformTimer -= fDT;

		if (m_fTransformTimer <= 0.f)
		{
			s_bTransform = false;
			m_fTransformTimer = 0.f;
		}

		switch (m_eMario)
		{
		case TYPE_MARIO::bgMARIO:		// small->big
			drawMario(L"FromSmall");
			break;
		case TYPE_MARIO::smMARIO:		// big->small
			drawMario(L"FromBig");
			break;
		case TYPE_MARIO::frMARIO:		// small->fire
			drawMario(L"FromSmall");
			break;
		}
		getAnimator()->update();
		return;							// 변신하는 동안 변신 모습만 보여주고 리턴
	}

	if (m_uiState & S_INVINCIBLE)
	{	// TODO 무적일 때 타이머랑 상태값 설정은 했는데 무적 효과 설정은 안 했음(충돌에서 하면될듯)
		m_fInvincibleTimer -= fDT;

		if (m_fInvincibleTimer < 0.f)
		{
			m_fInvincibleTimer = 0.f;
			m_uiState &= ~(S_INVINCIBLE);
		}
	}
	fPoint pos = getPos();

	if (KEY_HOLD(VK_LEFT) && KEY_NONE(VK_RIGHT))		// 왼쪽 키 입력
	{
		if (m_uiState & S_DIR)								// 오른쪽 보고 있었으면
		{	
			m_uiState &= ~(S_DIR);							// 왼쪽으로 바꿔주고
			m_fSpeedL = 0.f;									// 시작 속도 0
		}

		if (m_fSpeedL < (float)P_ACCEL)
			m_fSpeedL += P_ACCEL * fDT;						// 왼쪽 속도 증가

		if (m_fSpeedR > 60.f)
			drawMario(L"Zig");
	}
	else												// 왼쪽 키 안 누르면
	{
		if (m_fSpeedL > 0.f)
		{
			m_fSpeedL -= P_DECEL * fDT;						// 왼쪽 속도 감소

		}
		if (m_fSpeedL < 0.f) m_fSpeedL = 0.f;

	}

	if (KEY_HOLD(VK_RIGHT) && KEY_NONE(VK_LEFT))		// 오른쪽 키 입력
	{
		if (!(m_uiState & S_DIR))							// 왼쪽 보고 있었으면
		{
			m_uiState |= S_DIR;									// 오른쪽으로 바꿔주고
			m_fSpeedR = 0.f;									// 시작속도 0
		}

		if (m_fSpeedR < (float)P_ACCEL)
			m_fSpeedR += P_ACCEL * fDT;						// 오른쪽 속도 증가

		if (m_fSpeedL > 60.f)
			drawMario(L"Zig");
	}
	else												// 오른쪽 키 안 누르면
	{
		if (m_fSpeedR > 0.f)
			m_fSpeedR -= P_DECEL * fDT;						// 오른쪽 속도 감소

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

	if (KEY_ON(VK_SPACE) && !(m_uiState & S_JUMP))		// 공중에 있지 않으면서 스페이스 누르면 점프
	{
		m_fGravity = 0.f;
		pos.y--;										// 지면과 충돌 시 1픽셀 겹쳐있게 했더니 점프가 제대로 안 돼서 점프할 때 1픽셀 올려줌
		m_fSpeedY = P_JUMPSPD;
		m_uiState |= S_JUMP;
	}

	if (m_iBottomCnt <= 0)
		m_uiState |= S_JUMP;

	if (m_uiState & S_JUMP)								// 공중에 뜬 상태면 중력 적용
	{
		pos.y -= ((m_fSpeedY - m_fGravity) * fDT);
		//m_uiBottomCnt = 0;

		if (m_fGravity < (float)P_GRAVMAX)
			m_fGravity += P_GRAV * fDT;

		drawMario(L"Jump");
	}

	if (TYPE_MARIO::frMARIO == m_eMario && KEY_ON('A'))		// fire 상태, a키로 불꽃 발사 
		createFireball();

	if (KEY_ON('P'))
	{
		switch (m_eMario)
		{
		case TYPE_MARIO::smMARIO:
			m_eMario = TYPE_MARIO::bgMARIO;
			setBgMario();
			break;
		case TYPE_MARIO::bgMARIO:
			m_eMario = TYPE_MARIO::frMARIO;
			break;
		case TYPE_MARIO::frMARIO:
			m_eMario = TYPE_MARIO::smMARIO;
			setSmMario();
			break;
		}
	}

	// 시점 토글
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

	// bottomCnt 출력용..
	wchar_t szBuffer[255] = {};
	swprintf_s(szBuffer, L"[Bobrio] BottomCnt : %d \t Coin : %d", m_iBottomCnt, s_uiCoin);
	SetWindowText(hWnd, szBuffer);

	// 임시로 만든 되돌리는 키
	if (KEY_ON('R'))
	{
		pos = { 100.f, 500.f };
		m_iBottomCnt = 0;
	}

	setPos(pos);
	getAnimator()->update();
}
// TODO 맵 밖으로 떨어지면 트라이 횟수 1 증가시키고 (씬 전환 후 다시 복귀)


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

bool CPlayer::getTransformMode()
{
	return s_bTransform;
}

// 벽에 딱 붙어서 쏘면 벽 뚫고 쏘는 버그...
void CPlayer::createFireball()
{
	fPoint pos = getPos();
	fPoint size = getSize();
	CFireball* pFire = new CFireball();

	if (m_uiState & S_DIR)					// 발사체 발사방향, 위치조정
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

// TODO 충돌 판정에서 버그가 엄청 많이 남..
// 미니 마리오의 경우 m_uiBottomCnt가 계속 증가하기도 함
// 벽에 비비다 보면 카운트 이상해짐

void CPlayer::collisionKeep(CCollider* pOther)
{
	switch (pOther->getOwner()->getName())
	{
	case OBJNAME::BLOCK:
	case OBJNAME::TILE:
		switch (COLLRR(getCollider(), pOther))
		{
		case DIR::TOP:
			if (m_uiState & S_JUMP)
				m_uiState &= ~(S_JUMP);
			break;
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

// 현재 바닥 뚫고 낙하하는 버그
	// -> 아마 벽이랑 비비면서 BottomCnt가 이상해져서 중력 작용해버려서 그런거같은데)
	// 결국 충돌이 문제인듯?
void CPlayer::collisionEnter(CCollider* pOther)
{
	switch (pOther->getOwner()->getName())
	{
		//벽 충돌 관련
	case OBJNAME::BLOCK:
	case OBJNAME::TILE:
		switch (COLLRR(getCollider(), pOther))
		{
		case DIR::TOP:	// 착지
		{	// 지면과 1픽셀 겹치게 위치시켜서 exit말고 keep 호출되도록, 
			fPoint pos = getPos();
			pos.y = pOther->getPos().y - getCollider()->getOffset().y + pOther->getOffset().y 
				- (pOther->getSize().y + getCollider()->getSize().y) / 2 + 1;
			setPos(pos);
			if (m_uiState & S_JUMP)
				m_uiState &= ~(S_JUMP);
			m_iBottomCnt++;
			break;
		}
		case DIR::LEFT:
		{
			fPoint pos = getPos();
			pos.x = pOther->getPos().x + (getCollider()->getOffset().x + pOther->getOffset().x - pOther->getSize().x - getCollider()->getSize().x) / 2;
			setPos(pos);
			m_fSpeedR = 0.f;
			break;
		}
		case DIR::RIGHT:
		{
			fPoint pos = getPos();
			pos.x = pOther->getPos().x + (getCollider()->getOffset().x + pOther->getOffset().x + pOther->getSize().x + getCollider()->getSize().x) / 2;
			setPos(pos);
			m_fSpeedL = 0.f;
			break;
		}
		break;
		}
		break;

		// 아이템 충돌 관련
	case OBJNAME::ITEM_COIN:
		setCoin(getCoin() + 1);
		break;
	case OBJNAME::ITEM_MUSHROOM:
		if (TYPE_MARIO::smMARIO == m_eMario)
		{
			s_bTransform = true;
			setBgMario();
			m_fTransformTimer = 2.f;
		}
		break;
	}
}

// 벽에 비비면서 점프하면 bottomCnt -1되는 게
// 처음 enter할 때는 left로 진입해서 bottomCnt++된 적이 없고
// keep상태에서 점프하다가 exit할 때에는 top판정으로 충돌 탈출 해버리니까
// --만 1회 더 진행돼서 -1이 나온다고 생각됨
// 해결 방법은?
// 그냥 카운트 음수되면 0으로 바꿔주면 해결되긴 한데 꼼수인 느낌이라
void CPlayer::collisionExit(CCollider* pOther)
{
	switch (pOther->getOwner()->getName())
	{
	case OBJNAME::BLOCK:
	case OBJNAME::TILE:
		switch (COLLRR(getCollider(), pOther))
		{
		case DIR::TOP:
			if (--m_iBottomCnt <= 0)
			{
				if (m_iBottomCnt < 0)
					m_iBottomCnt = 0;
				m_uiState |= S_JUMP;
			}
			break;
		}
		break;
	}
}

// 키워드로 마리오 그리기
void CPlayer::drawMario(const wstring& commonName)
{
	wstring str;

	switch (m_eMario)
	{
	case TYPE_MARIO::smMARIO:
		str = L"sm";
		break;

	case TYPE_MARIO::bgMARIO:
		str = L"bg";
		break;

	case TYPE_MARIO::frMARIO:
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
	m_eMario = TYPE_MARIO::smMARIO;
}
void CPlayer::setBgMario()
{
	setSize(fPoint((float)P_SIZEX - 8, (float)P_SIZEY - 6));
	getCollider()->setOffset(fPoint(0.f, 6.f));
	m_eMario = TYPE_MARIO::bgMARIO;
}