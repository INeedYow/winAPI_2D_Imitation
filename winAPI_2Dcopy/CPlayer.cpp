#include "framework.h"
#include "CPlayer.h"
#include "CFireball.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CMonster_Turtle.h"

UINT	CPlayer::s_uiCoin		= 0;
UINT	CPlayer::s_uiScore		= 0;
UINT	CPlayer::s_uiTryCnt		= 0;
bool	CPlayer::s_bTransform	= false;
float	CPlayer::s_fCamPosX = WINSIZEX * 0.65f;

CPlayer::CPlayer()
{
	setPos(fPoint(0.f, 0.f));
	setSize(fPoint((float)P_sizex, (float)P_sizey));
	setName(OBJNAME::MARIO);
	s_fCamPosX	= WINSIZEX / 2.f;
	m_fSpeedL	= 0.f;
	m_fSpeedR	= 0.f;
	m_fSpeedY	= 0.f;
	m_fGravity	= 0.f;
	m_fTransformTimer	= 0.f;
	m_fInvincibleTimer	= 0.f;
	m_eMario	= TYPE_MARIO::smMARIO;
	m_iBottomCnt = 0;
	m_uiState	= 0;
	m_uiState |= S_AIR;
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

	createAnim(L"sp_smStand_L", m_pTex, fPoint(0.f, 384.f),		fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.5f, 1);
	createAnim(L"sp_smStand_R", m_pTex, fPoint(0.f, 448.f),		fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.5f, 1);
	createAnim(L"sp_bgStand_L", m_pTex, fPoint(0.f, 512.f),		fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.5f, 1);
	createAnim(L"sp_bgStand_R", m_pTex, fPoint(0.f, 576.f),		fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.5f, 1);
	
	createAnim(L"sp_smJump_L", m_pTex,	fPoint(64.f, 384.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 1);
	createAnim(L"sp_smJump_R", m_pTex,	fPoint(64.f, 448.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 1);
	createAnim(L"sp_bgJump_L", m_pTex,	fPoint(64.f, 512.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 1);
	createAnim(L"sp_bgJump_R", m_pTex,	fPoint(64.f, 576.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.3f, 1);

	createAnim(L"sp_smSlide_L", m_pTex, fPoint(128.f, 384.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.2f, 1);
	createAnim(L"sp_smSlide_R", m_pTex, fPoint(128.f, 448.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.2f, 1);
	createAnim(L"sp_bgSlide_L", m_pTex, fPoint(128.f, 512.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.2f, 1);
	createAnim(L"sp_bgSlide_R", m_pTex, fPoint(128.f, 576.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.2f, 1);

	createAnim(L"sp_smZig_L", m_pTex,	fPoint(192.f, 384.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.2f, 1);
	createAnim(L"sp_smZig_R", m_pTex,	fPoint(192.f, 448.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.2f, 1);
	createAnim(L"sp_bgZig_L", m_pTex,	fPoint(192.f, 512.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.2f, 1);
	createAnim(L"sp_bgZig_R", m_pTex,	fPoint(192.f, 576.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.2f, 1);

	createAnim(L"sp_smRun_L", m_pTex,	fPoint(256.f, 384.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.2f, 3);
	createAnim(L"sp_smRun_R", m_pTex,	fPoint(256.f, 448.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.2f, 3);
	createAnim(L"sp_bgRun_L", m_pTex,	fPoint(256.f, 512.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.2f, 3);
	createAnim(L"sp_bgRun_R", m_pTex,	fPoint(256.f, 576.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.2f, 3);


	createAnim(L"Death",		m_pTex, fPoint(512.f, 128.f),	fPoint(64.f, 64.f),		fPoint(64.f, 0.f),		0.5f, 1);

	PLAY(L"smStand_R");

}

CPlayer::~CPlayer()
{
}

void CPlayer::update()
{
	if (m_uiState & S_DEATH)
	{
		m_fInvincibleTimer -= fDT;

		fPoint pos = getPos();

		pos.y -= (m_fSpeedY - m_fGravity) * fDT;

		m_fGravity += 600.f * fDT;

		if (m_fInvincibleTimer < 0.f)
		{
			changeScn(SCENE::RESULT);
		}

		setPos(pos);
		getAnimator()->update();
		return;
	}

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
			if (m_uiState & S_DIR) 
				PLAY(L"bgFromSmall_R");
			else PLAY(L"bgFromSmall_L");
			break;
		case TYPE_MARIO::smMARIO:		// big->small
			if (m_uiState & S_DIR)
				PLAY(L"smFromBig_R");
			else PLAY(L"smFromBig_L");
			break;
		case TYPE_MARIO::frMARIO:		// small->fire
			if (m_uiState & S_DIR)
				PLAY(L"frFromSmall_R");
			else PLAY(L"frFromSmall_L");
			break;
		}
		getAnimator()->update();
		return;							// 변신하는 동안 변신 모습만 보여주고 리턴
	}

	// 아이템 무적, 피격 시 잠시 무적
		// 둘 애니메이션 구분하려 했는데 리소스에 너무 시간 쓰는 것 같아서 그냥 같은 리소스 씀
		// 다만 아이템 무적일 때는 닿는 몬스터 다 죽게 하려하는데
		// 충돌 상대가 내 상태값을 받을 수가 없으니 CObject에 상태값 변수를 만들던가
		// 아니면 name으로 구분하는 수 밖에? -> name 으로 구분 시도 중
	if (m_uiState & S_INVINCIBLE || 
		m_uiState & S_SUPER)			
	{	
		m_fInvincibleTimer -= fDT;

		if (m_fInvincibleTimer < 0.f)
		{
			m_fInvincibleTimer = 0.f;
			m_uiState &= ~(S_INVINCIBLE);
			m_uiState &= ~(S_SUPER);
			setName(OBJNAME::MARIO);
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

		if (m_fSpeedR > 50.f)
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

		if (m_fSpeedL > 50.f)
			drawMario(L"Zig");
	}
	else												// 오른쪽 키 안 누르면
	{
		if (m_fSpeedR > 0.f)
			m_fSpeedR -= P_DECEL * fDT;						// 오른쪽 속도 감소

		if (m_fSpeedR < 0.f) m_fSpeedR = 0.f;
	}

	pos.x += (m_fSpeedR - m_fSpeedL) * fDT;
	
	// 카메라
	if (pos.x > s_fCamPosX)
	{
		s_fCamPosX += 130 * fDT;
		setFocus(fPoint(s_fCamPosX, WINSIZEY / 2.f));
	}

	// 맵 탈출방지
	if (pos.x < s_fCamPosX - WINSIZEX / 2.f)
		pos.x = s_fCamPosX - WINSIZEX / 2.f;

	if (m_fSpeedR == 0 && m_fSpeedL == 0)
		drawMario(L"Stand");

	else if (KEY_NONE(VK_RIGHT) && KEY_NONE(VK_LEFT)&&
			(m_fSpeedR < 50.f || m_fSpeedL < 50.f))
		drawMario(L"Slide");

	else if ((m_fSpeedR > 70.f && m_fSpeedL < 50.f) || 
			 (m_fSpeedL > 70.f && m_fSpeedR < 50.f))
		drawMario(L"Run");

	if (KEY_ON(VK_SPACE) && !(m_uiState & S_AIR))		// 공중에 있지 않으면서 스페이스 누르면 점프
	{
		m_fGravity = 0.f;
		pos.y--;										// 지면과 충돌 시 1픽셀 겹쳐있게 했더니 점프가 제대로 안 돼서 점프할 때 1픽셀 올려줌
		m_fSpeedY = P_JUMPSPD;
		m_uiState |= S_AIR;
	}

	if (m_iBottomCnt <= 0)
		m_uiState |= S_AIR;

	if (m_uiState & S_AIR)								// 공중에 뜬 상태면 중력 적용
	{
		pos.y -= ((m_fSpeedY - m_fGravity) * fDT);

		if (m_fGravity < (float)P_GRAVMAX)
			m_fGravity += P_GRAV * fDT;

		if ((m_fSpeedY - m_fGravity) < 0.f)				// 점프 동작 중 올라가는 중인지(내려오는 중일 때에만 바닥에 착지하도록 충돌 설정)
			m_uiState &= ~(S_GOUP);
		else
			m_uiState |= S_GOUP;

		drawMario(L"Jump");
	}

	if (pos.y > WINSIZEY) death();

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

	// 출력용..
	wchar_t szBuffer[255] = {};
	swprintf_s(szBuffer, L"[Bobrio] BottomCnt : %d \t Coin : %d \t Score : %d", m_iBottomCnt, s_uiCoin, s_uiScore);
	SetWindowText(hWnd, szBuffer);

	if (KEY_ON('R'))
	{
		death();
		m_iBottomCnt = 0;
	}

	setPos(pos);
	getAnimator()->update();
}


void CPlayer::render(HDC hDC)
{
	componentRender(hDC);
}

UINT CPlayer::getCoin()
{
	return s_uiCoin;
}

UINT CPlayer::getScore()
{
	return 0;
}

void CPlayer::setCoin(UINT coin)
{
	s_uiCoin = coin;
}

void CPlayer::setScore(UINT score)
{
}

void CPlayer::setTryCnt(UINT cnt)
{
	s_uiTryCnt = cnt;
}

void CPlayer::setCamPos(float posX)
{
	s_fCamPosX = posX;
}

bool CPlayer::isTransform()
{
	return s_bTransform;
}

float CPlayer::getCamPos()
{
	return s_fCamPosX;
}

UINT CPlayer::getTryCnt()
{
	return s_uiTryCnt;
}

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

// 점프하다가 벽 꼭지점에 걸치면 벽 윗면 타고 직선이동하다가 벽 끝나면 점프하는 버그있음
void CPlayer::collisionEnter(CCollider* pOther)
{
	switch (pOther->getOwner()->getName())
	{
		//벽 충돌
	case OBJNAME::BLOCK:
	case OBJNAME::TILE:
		switch (COLLRR(getCollider(), pOther))
		{
		case DIR::TOP:
		{	// 지면과 1픽셀 겹치게 위치시켜서 exit말고 keep 호출되도록, 
			if (!(m_uiState & S_GOUP))
			{	// 점프 동작 중 내려오는 동안에 충돌 시 착지
				fPoint pos = getPos();
				pos.y = pOther->getPos().y - getCollider()->getOffset().y + pOther->getOffset().y
					- (pOther->getSize().y + getCollider()->getSize().y) / 2 + 1;
				setPos(pos);
				if (m_uiState & S_AIR)
					m_uiState &= ~(S_AIR);
				m_iBottomCnt++;
			}
			break;
		}
		case DIR::LEFT:
		{
			fPoint pos = getPos();
			pos.x = pOther->getPos().x + (getCollider()->getOffset().x + pOther->getOffset().x 
				- pOther->getSize().x - getCollider()->getSize().x) / 2;
			setPos(pos);
			m_fSpeedR = 0.f;
			break;
		}
		case DIR::RIGHT:
		{
			fPoint pos = getPos();
			pos.x = pOther->getPos().x + (getCollider()->getOffset().x + pOther->getOffset().x 
				+ pOther->getSize().x + getCollider()->getSize().x) / 2;
			setPos(pos);
			m_fSpeedL = 0.f;
			break;
		}
		case DIR::BOTTOM:	//
			m_fSpeedY = 0.f;
			break;
		}
		break;

		// 아이템 충돌
	case OBJNAME::ITEM_COIN:
		setCoin(getCoin() + 1);
		s_uiScore += 200;
		break;
	case OBJNAME::ITEM_MUSHROOM:
		if (TYPE_MARIO::smMARIO == m_eMario)
		{
			s_bTransform = true;
			setBgMario();
			m_fTransformTimer = 2.f;
		}
		s_uiScore += 3000;
		break;
	case OBJNAME::ITEM_FLOWER:
		if (TYPE_MARIO::smMARIO == m_eMario)
		{
			s_bTransform = true;
			setBgMario();
			m_eMario = TYPE_MARIO::frMARIO;
			m_fTransformTimer = 2.f;
		}
		else if (TYPE_MARIO::bgMARIO == m_eMario)
		{
			m_eMario = TYPE_MARIO::frMARIO;
		}
		s_uiScore += 4000;
		break;
	case OBJNAME::ITEM_STAR:
		m_uiState |= S_SUPER;
		m_fInvincibleTimer = 10.f;
		s_uiScore += 5000;
		setName(OBJNAME::SUPERMARIO);
		break;

		// 몬스터 충돌
	case OBJNAME::MONS_TURTLE:
		// 무적 아이템(별) 먹었을 때 제외, 이미 피해입어서 무적일 때 제외
		if (!(m_uiState & S_SUPER) && !(m_uiState & S_INVINCIBLE))	
		{	
			if (pOther->getOwner()->getName() == OBJNAME::MONS_TURTLE)
			{	// 거북이 상태일 때
				switch (COLLRR(getCollider(), pOther))
				{	// 약하게 다시 점프
				case DIR::TOP:
					m_fGravity = 0.f;
					m_fSpeedY = (float)P_BOUNCESPD;
					s_uiScore += 1000;
					break;
				default:
					getDamage();
					break;
				}
			}
			
		}
		break;
	}
}

// 벽에 비비면서 점프하면 bottomCnt -1되는 게
// 처음 enter할 때는 left로 진입해서 bottomCnt++된 적이 없고
// keep상태에서 점프하다가 exit할 때에는 top판정으로 충돌 탈출 해버리니까
// --만 1회 더 진행돼서 -1이 나온다고 생각됨
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
				m_uiState |= S_AIR;
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

	if (m_uiState & S_SUPER || m_uiState & S_INVINCIBLE)
	{
		if (m_eMario == TYPE_MARIO::smMARIO)
			str = L"sp_sm";
		else
			str = L"sp_bg";
	}
	else
	{
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
	}

	if (m_uiState & S_DIR)
		str += (commonName + L"_R");
	else
		str += (commonName + L"_L");
	
	PLAY(str);
}

void CPlayer::death()
{
	m_uiState |= S_DEATH;
	m_fSpeedY = P_JUMPSPD;
	m_fGravity = 0.f;
	m_fInvincibleTimer = 2.7f;
	PLAY(L"Death");
	CCollisionManager::getInst()->unCheckGroup(OBJ::PLAYER, OBJ::TILE);
	CCollisionManager::getInst()->unCheckGroup(OBJ::PLAYER, OBJ::BLOCK);
	CCollisionManager::getInst()->unCheckGroup(OBJ::PLAYER, OBJ::ITEM);
	CCollisionManager::getInst()->unCheckGroup(OBJ::PLAYER, OBJ::MONSTER);
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

void CPlayer::getDamage()
{
	switch (m_eMario)
	{
	case TYPE_MARIO::smMARIO:
		death();
		break;
	case TYPE_MARIO::bgMARIO:
		setSmMario();
		m_uiState |= S_INVINCIBLE;
		m_fInvincibleTimer = 2.5f;
		break;
	case TYPE_MARIO::frMARIO:
		setBgMario();
		m_uiState |= S_INVINCIBLE;
		m_fInvincibleTimer = 2.5f;
		break;
	}
}
