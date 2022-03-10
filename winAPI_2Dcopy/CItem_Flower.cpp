#include "framework.h"
#include "CItem_Flower.h"
#include "CPlayer.h"

CItem_Flower::CItem_Flower()
{
	setName(OBJNAME::ITEM_FLOWER);

	m_pTex = loadTex(KEY_RES::TEX_ITEM_FB, L"texture\\subObject.bmp");

	createCollider();
	getCollider()->setSize(fPoint((float)IT_SIZE - 1, (float)IT_SIZE - 1));
	getCollider()->setOffset(fPoint(0.f, 2.f));
	getCollider()->setShape(SHAPE::RECT);

	createAnimator();

	createAnim(L"Item_Flower", m_pTex, fPoint(160.f, 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.5f, 1);
	PLAY(L"Item_Flower");
}

CItem_Flower::~CItem_Flower()
{
}

void CItem_Flower::update()
{
	fPoint pos = getPos();

	if (pos.x + IT_SIZE < CPlayer::getCamPos() - WINSIZEX / 2.f)
		deleteObj(this);

	getAnimator()->update();
}

void CItem_Flower::render(HDC hDC)
{
	componentRender(hDC);
}

void CItem_Flower::collisionEnter(CCollider* pOther)
{
	switch (pOther->getOwner()->getName())
	{
	case OBJNAME::MARIO:
	case OBJNAME::SUPERMARIO:
		deleteObj(this);
		break;
	}
}
