#include "framework.h"
#include "CItem_Coin.h"

CItem_Coin::CItem_Coin()
{
	setPos(fPoint(0.f, 0.f));
	setSize(fPoint((float)IT_SIZE, (float)IT_SIZE));
	setName(OBJNAME::ITEM_COIN);

	m_pTex = loadTex(KEY_RES::TEX_ITEM_FB, L"texture\\subObject.bmp");

	createCollider();
	getCollider()->setSize(fPoint((float)IT_SIZE - 1, (float)IT_SIZE - 1));
	getCollider()->setOffset(fPoint(0.f, 0.f));
	getCollider()->setShape(SHAPE::RECT);

	createAnimator();

	createAnim(L"Item_Coin", m_pTex, fPoint(0.f, 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.2f, 5);
	PLAY(L"Item_Coin");
}

CItem_Coin::~CItem_Coin()
{
}

void CItem_Coin::update()
{
	getAnimator()->update();
}

void CItem_Coin::render(HDC hDC)
{
	componentRender(hDC);
}

void CItem_Coin::collisionEnter(CCollider* pOther)
{
	if (pOther->getOwner()->getName() == OBJNAME::MARIO)
		deleteObj(this);
}