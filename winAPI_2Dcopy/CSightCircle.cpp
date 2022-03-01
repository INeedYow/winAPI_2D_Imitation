#include "framework.h"
#include "CSightCircle.h"

CSightCircle::CSightCircle()
{
	setPos(fPoint(0.f, 0.f));
	setSize(fPoint(10.f, 10.f));
	
	minRange = P_SIGHTON;
	maxRange = P_SIGHTOFF;
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
}
