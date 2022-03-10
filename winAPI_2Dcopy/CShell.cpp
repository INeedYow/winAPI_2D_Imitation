#include "framework.h"
#include "CShell.h"

CShell::CShell()
{
	setName(OBJNAME::SHELL);
	setSize(fPoint(MT_SIZEX - 6, MT_SIZEY - 4));
	m_fSpeed = (float)SH_SPD;
	m_fvDir = {};
	m_bAir = true;
	m_fGravity = 0.f;
	m_iBottomCnt = 0;
	m_fDuration = 5.f;

	m_pTex = loadTex(KEY_RES::TEX_KOOPA, L"texture\\koopa.bmp");

	createCollider();
	getCollider()->setSize(fPoint((float)MT_SIZEX - 18, (float)MT_SIZEY - 8));
	getCollider()->setOffset(fPoint(0.f, 6.f));
	getCollider()->setShape(SHAPE::RECT);

	createAnimator();

	createAnim(L"shell", m_pTex, fPoint(0.f, 88.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.5f, 1);
	
	PLAY(L"shell");
}

CShell::~CShell()
{
}

void CShell::setDir(fVec2 dir)
{
	m_fvDir = dir;
}

// TODO
void CShell::update()
{
	m_fDuration -= fDT;

	if (m_fDuration < 0.f)
		deleteObj(this);

	fPoint pos = getPos();

	pos.x += m_fSpeed * m_fvDir.x * fDT;

	if (m_bAir)
	{
		pos.y += m_fGravity * m_fvDir.y * fDT;

		if (m_fGravity < (float)P_GRAVMAX)
			m_fGravity += P_GRAV * fDT;
	}

	setPos(pos);
	getAnimator()->update();
}

void CShell::render(HDC hDC)
{
	componentRender(hDC);
}

void CShell::collisionEnter(CCollider* pOther)
{
	switch (pOther->getOwner()->getName())
	{
		//º® Ãæµ¹
	case OBJNAME::BLOCK:
	case OBJNAME::TILE:
		switch (COLLRR(getCollider(), pOther))
		{
		case DIR::TOP:	// ÂøÁö
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
		{
			fPoint pos = getPos();
			pos.x = pOther->getPos().x + (getCollider()->getOffset().x + pOther->getOffset().x 
				- pOther->getSize().x - getCollider()->getSize().x) / 2;
			setPos(pos);
			m_fvDir.x = -1.f;
			break;
		}
		case DIR::RIGHT:
		{
			fPoint pos = getPos();
			pos.x = pOther->getPos().x + (getCollider()->getOffset().x + pOther->getOffset().x 
				+ pOther->getSize().x + getCollider()->getSize().x) / 2;
			setPos(pos);
			m_fvDir.x = 1.f;
			break;
		}
		}
		break;
	}
}

void CShell::collisionExit(CCollider* pOther)
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
