#include "framework.h"
#include "CTile.h"

CTile::CTile()
{
	setPos(fPoint(0.f, 0.f));
	setSize(fPoint(T_SIZE, T_SIZE));
	setName(OBJNAME::TILE);

	createCollider();
	getCollider()->setSize(fPoint(T_SIZE - 1, T_SIZE - 1));
	getCollider()->setShape(SHAPE::RECT);
}

CTile::~CTile()
{
}

void CTile::update()
{
}

void CTile::render(HDC hDC)
{


	componentRender(hDC);
}
