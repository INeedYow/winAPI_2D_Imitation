#include "framework.h"
#include "CMonster_Turtle.h"
#include "CPlayer.h"
#include "CShell.h"

CMonster_Turtle::CMonster_Turtle()
{
	setName(OBJNAME::MONS_TURTLE);
	setSize(fPoint(MT_SIZEX, MT_SIZEY));
	m_fSpeed = (float)MT_SPD;
	m_fvDir.x = rand() % 2 ? -1.f : 1.f;
	m_fvDir.y = 0.f;
	m_iBottomCnt = 0;
	m_fGravity = 0.f;

	setStateTrue(S_AIR);

	m_pTex = loadTex(KEY_RES::TEX_KOOPA, L"texture\\koopa.bmp");

	createCollider();

	getCollider()->setSize(fPoint((float)MT_SIZEX - 18, (float)MT_SIZEY - 8));
	getCollider()->setOffset(fPoint(0.f, 6.f));
	getCollider()->setShape(SHAPE::RECT);

	createAnimator();
	
	createAnim(L"move_L",	m_pTex, fPoint(0.f, 0.f),		fPoint(40.f, 44.f),		fPoint(40.f, 0.f),	0.2f, 4);
	createAnim(L"move_R",	m_pTex, fPoint(0.f, 44.f),		fPoint(40.f, 44.f),		fPoint(40.f, 0.f),	0.2f, 4);
	createAnim(L"death",	m_pTex, fPoint(128.f, 88.f),	fPoint(32.f, 32.f),		fPoint(32.f, 0.f),	0.5f, 1);

	m_fvDir.x > 0.f ? PLAY(L"move_R") : PLAY(L"move_L");
}

CMonster_Turtle::~CMonster_Turtle()
{
}

void CMonster_Turtle::setDir(fVec2 dir)
{
	m_fvDir = dir;
}

void CMonster_Turtle::update()
{
	fPoint pos = getPos();

	if (isState(S_DIR))
		PLAY(L"move_R");
	else
		PLAY(L"move_L");

	if (isState(S_AIR))
	{
		pos.y += m_fGravity * fDT;

		if (m_fGravity < M_GRAVMAX)
			m_fGravity += M_GRAV * fDT;
	}
	else
	{
		pos.x += m_fvDir.x * m_fSpeed * fDT;
	}

	// 화면 밖에 나가면 삭제
	if (pos.x + getSize().x / 2.f < CPlayer::getCamPos() - WINSIZEX / 2.f ||
		pos.y - getSize().y / 2.f > WINSIZEY)
		deleteObj(this);

	setPos(pos);
	getAnimator()->update();
}

void CMonster_Turtle::render(HDC hDC)
{
	componentRender(hDC);
}

void CMonster_Turtle::collisionEnter(CCollider* pOther)
{
	switch (pOther->getOwner()->getName())
	{
	case OBJNAME::BLOCK:
	case OBJNAME::TILE:
		switch (COLLRR(getCollider(), pOther))
		{
		case DIR::TOP:
		{
			fPoint pos = getPos();
			pos.y = pOther->getPos().y - getCollider()->getOffset().y + pOther->getOffset().y
				- (pOther->getSize().y + getCollider()->getSize().y) / 2 + 1;
			setPos(pos);
			if (isState(S_AIR))
				setStateFalse(S_AIR);
			m_iBottomCnt++;
			break;
		}
		case DIR::LEFT:
			m_fvDir.x = -1.f;
			setStateFalse(S_DIR);
			break;
		case DIR::RIGHT:
			m_fvDir.x = 1.f;
			setStateTrue(S_DIR);
			break;
		}
		// TODO 마리오한테 위에서 밟히면 껍데기로 바뀌게
	case OBJNAME::MARIO:
		if (DIR::BOTTOM == COLLRR(getCollider(), pOther))
			becomeShell();
		break;
		// TODO 마리오가 밀어서 움직이는 SHELL일 때만 죽게 하는 방법 고민
	case OBJNAME::FIREBALL:
	case OBJNAME::SHELL:
		death();
		break;
	}
}

void CMonster_Turtle::collisionExit(CCollider* pOther)
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
				setStateTrue(S_AIR);
			}
			break;
		}
		break;
	}
}

// 쉘을 상태값으로 부여할지 새로 오브젝트 만들어서 줘야할지 아직 고민 중
// 플레이어에서 쉘인지 상태값을 알 방법이 있나
void CMonster_Turtle::becomeShell()
{
}

// 죽는 이펙트 보여주는 클래스는 따로 만들어야 충돌 설정도 다르게 할 수 있고
// 플레이어랑 부딪혀도 플레이어 안 죽을 듯
void CMonster_Turtle::death()
{
	// TODO 임시
	PLAY(L"death");
	deleteObj(this);
}
