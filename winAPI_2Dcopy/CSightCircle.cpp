#include "framework.h"
#include "CSightCircle.h"

#include "SelectGDI.h"

CSightCircle::CSightCircle()
{
	setPos(fPoint(0.f, 0.f));
	setSize(fPoint((float)P_SIGHTON, (float)P_SIGHTOFF));
	
	/*minRange = P_SIGHTON;
	maxRange = P_SIGHTOFF;*/
}

CSightCircle::~CSightCircle()
{
}

void CSightCircle::update()
{
	setPos(GETPOS);
}

void CSightCircle::render(HDC hDC)
{
	fPoint pos = GETPOS;
	fPoint size = getSize();
	
	int sight = ISMODE ? (int)size.x : (int)size.y;

	SelectGDI brush(hDC, BRUSH::WHITE200);

	Ellipse(hDC,
		(int)(pos.x - sight),
		(int)(pos.y - sight),
		(int)(pos.x + sight),
		(int)(pos.y + sight));
}

//UINT CSightCircle::getRange(bool mode)
//{
//	if (mode)	return maxRange;
//	else		return minRange;
//}
