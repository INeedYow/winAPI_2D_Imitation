#include "framework.h"
#include "CItem_Mushroom.h"

CItem_Mushroom::CItem_Mushroom()
{
	setPos(fPoint(0.f, 0.f));
	setSize(fPoint((float)IT_SIZE, (float)IT_SIZE));
	setName(OBJNAME::ITEM_MUSHROOM);

	m_fSpeed = (float)ITM_SPD;
	m_fvDir = {};

	m_pTex = loadTex(KEY_RES::TEX_ITEM_FB, L"texture\\subObject.bmp");

	createCollider();
	getCollider()->setSize(fPoint((float)IT_SIZE - 1, (float)IT_SIZE - 1));
	getCollider()->setOffset(fPoint(0.f, 0.f));
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

// TODO 버섯 생성해서 테스트
void CItem_Mushroom::update()
{
	fPoint pos = getPos();

	pos.x += m_fSpeed * m_fvDir.x * fDT;

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
