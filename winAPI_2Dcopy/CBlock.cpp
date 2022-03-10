#include "framework.h"
#include "CBlock.h"

CBlock::CBlock()
{
	setPos(fPoint(0.f, 0.f));
	setSize(fPoint(T_SIZE, T_SIZE));
	setName(OBJNAME::TILE);

	createCollider();
	getCollider()->setSize(fPoint(T_SIZE - 1, T_SIZE - 1));
	getCollider()->setShape(SHAPE::RECT);
}

CBlock::~CBlock()
{
}

void CBlock::update()
{
}

void CBlock::render(HDC hDC)
{

	componentRender(hDC);
}
