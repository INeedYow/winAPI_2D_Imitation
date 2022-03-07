#include "framework.h"
#include "CItem.h"

CItem::CItem()
{
	setPos(fPoint(0.f, 0.f));
	setSize(fPoint(1.f, 1.f));
	setType(OBJ::ITEM);
}

CItem::~CItem()
{
}

void CItem::render(HDC hDC)
{
	componentRender(hDC);
}
