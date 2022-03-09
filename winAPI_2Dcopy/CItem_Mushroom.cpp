#include "framework.h"
#include "CItem_Mushroom.h"
#include "CPlayer.h"

CItem_Mushroom::CItem_Mushroom()
{
	setName(OBJNAME::ITEM_MUSHROOM);
	m_fSpeed = (float)ITM_SPD;
	m_fvDir = {};
	m_iBottomCnt = 0;
	m_fGravity = 0.f;
	m_bAir = true;

	m_pTex = loadTex(KEY_RES::TEX_ITEM_FB, L"texture\\subObject.bmp");

	createCollider();
	getCollider()->setSize(fPoint((float)IT_SIZE - 2, (float)IT_SIZE - 2));
	getCollider()->setOffset(fPoint(0.f, 2.f));
	getCollider()->setShape(SHAPE::RECT);

	createAnimator();

	createAnim(L"Item_Mush", m_pTex, fPoint(128.f, 32.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.5f, 1);
	PLAY(L"Item_Mush");
}

CItem_Mushroom::~CItem_Mushroom()
{
}

void CItem_Mushroom::setDir(fVec2 dir)
{
	m_fvDir = dir;
}

void CItem_Mushroom::update()
{
	fPoint pos = getPos();

	
	if (m_bAir)
	{
		pos.y += m_fGravity * fDT;

		if (m_fGravity < IT_GRAVMAX)
			m_fGravity += IT_GRAV * fDT;
	}
	else
	{
		pos.x += m_fSpeed * m_fvDir.x * fDT;
	}

	// 화면 밖에 나가면 삭제
	if (pos.x + getSize().x / 2.f < CPlayer::getCamPos() - WINSIZEX / 2.f ||
		pos.y - getSize().y / 2.f > WINSIZEY)
		deleteObj(this);

	setPos(pos);
	getAnimator()->update();
}

void CItem_Mushroom::render(HDC hDC)
{
	componentRender(hDC);
}

void CItem_Mushroom::collisionEnter(CCollider* pOther)
{
	switch (pOther->getOwner()->getName())
	{
	case OBJNAME::MARIO:
		deleteObj(this);
		break;
	case OBJNAME::TILE:
	case OBJNAME::BLOCK:
		switch (COLLRR(getCollider(), pOther))
		{
		case DIR::TOP:
		{
			fPoint pos = getPos();
			pos.y = pOther->getPos().y - getCollider()->getOffset().y + pOther->getOffset().y
				- (pOther->getSize().y + getCollider()->getSize().y) / 2 + 1;
			setPos(pos);
			if (m_bAir)
				m_bAir = false;
			m_iBottomCnt++;
			break;
		}
		case DIR::LEFT:
			m_fvDir.x = -1.f;
			break;
		case DIR::RIGHT:
			m_fvDir.x = 1.f;
			break;
		
		}
		break;
	}
		
}

void CItem_Mushroom::collisionExit(CCollider* pOther)
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
				m_bAir = true;
			}
			break;
		}
		break;
	}
}
