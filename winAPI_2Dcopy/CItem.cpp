#include "framework.h"
#include "CItem.h"

CItem::CItem()
{
	setSize(fPoint((float)IT_SIZE, (float)IT_SIZE));
}

CItem::~CItem()
{
}

void CItem::render(HDC hDC)
{
	componentRender(hDC);
}
