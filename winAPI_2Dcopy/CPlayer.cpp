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
	
	// fr _R 불일 때 오른쪽 모습 다 안 나옴
	// 연속 동작도 안 됨

	getAnimator()->play(L"smStand_R");

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

		if (m_fSpeedR > 0.f)
			drawMario(L"Zig");
	}
	else											// 왼쪽 키 안 누르면
	{
		if (m_fSpeedL > 0.f)
		{
			m_fSpeedL -= P_DECEL * fDT;					// 왼쪽 속도 감소

		}
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

		if (m_fSpeedL > 0.f)
			drawMario(L"Zig");
	}
	else											// 오른쪽 키 안 누르면
	{
		if (m_fSpeedR > 0.f)
			m_fSpeedR -= P_DECEL * fDT;					// 오른쪽 속도 감소

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

	if (KEY_ON(VK_SPACE) && !(m_uiState & S_JUMP))	// 공중에 있지 않으면서 스페이스 누르면 점프
	{
		m_fGravity = 0.f;
		m_fSpeedY = P_JUMPSPD;
		m_uiState |= S_JUMP;
	}

	if (m_uiBottomCnt <= 0)
		m_uiState |= S_JUMP;

	if (m_uiState & S_JUMP)							// 공중에 뜬 상태면 중력 적용
	{
		pos.y -= ((m_fSpeedY - m_fGravity) * fDT);

		if (m_fGravity < (float)P_GRAVMAX)
			m_fGravity += P_GRAV * fDT;

		drawMario(L"Jump");
	}

	if (MARIO::frMARIO == m_eMario && KEY_ON('A'))		// fire 상태, a키로 불꽃 발사 
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

	// 임시로 만든 되돌리는 키
	if (KEY_ON('R'))
		pos = { 100.f, 500.f };

	setPos(pos);
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

void CPlayer::createFireball()
{
	fPoint pos = getPos();
	fPoint size = getSize();
	CFireball* pFire = new CFireball();

	if (m_uiState & S_DIR)					// 발사체 발사방향, 위치조정
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


// TODO 충돌검사로 방향도 알 수 있어야 함
void CPlayer::collisionKeep(CCollider* pOther)
{
}

// 누구 기준으로 top이나 bottom이냐는 어떻게..
// 충돌검사 좌우 들어가는 순서 기준인데
// 플레이어 그룹을 위에 두면 되긴 하지만
void CPlayer::collisionEnter(CCollider* pOther)
{
	
}

// exit에서 bottomCnt--가 안 돼서 봤더니 exit이 호출될 때는 이전 프레임에 충돌했었고 이번 프레임엔 충돌 안 한 경우라서
// None으로 들어옴, 무조건 none일 수밖에
// 이전 충돌 방향 알게 하거나 항상 중력 작용하게 해야..
void CPlayer::collisionExit(CCollider* pOther)
{
	
}

// 키워드만으로 마리오 그리기
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
// TODO 충돌 방향의 구분이 들어가야 함
// 바닥에 서있게 하는 방법.. 
// 충돌체의 충돌 카운트 변수 받아오고 충돌방향 알면
// 발바닥에 tile 충돌 카운트 0이면 공중에 뜸 상태 적용하고 중력 적용하면 되는데
// 근데 카운트가 누구랑 카운트인지 모름
// 꼼수로 static 변수로 enter에 ++ exit에 -- 해서 0이면 떨어지게 할수도? 