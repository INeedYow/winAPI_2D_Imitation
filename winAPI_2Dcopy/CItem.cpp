#include "framework.h"
#include "CItem.h"

CItem::CItem()
{
	setPos(fPoint(0.f, 0.f));
	setSize(fPoint((float)I_SIZE,(float)I_SIZE));
	fTimer = 0;
	uiDuration = 10;
}

CItem::~CItem()
{
}

void CItem::setTimer(float time)
{
	fTimer = time;
}

void CItem::setDuration(UINT dura)
{
	uiDuration = dura;
}

float CItem::getTimer()
{
	return fTimer;
}

UINT CItem::getDuration()
{
	return uiDuration;
}

void CItem::setRandPos()
{
	int x, y;
	fPoint playerPos = GETPOS;

	do
	{
		x = rand() % (WINSIZEX - 100) + 50;
		y = rand() % (WINSIZEY - 100) + 50;
	} while (playerPos.COLL_PC(fPoint(x,y),playerPos,O_SIZE + 20));
	
	// 플레이어 위치에 너무 가까이 생성되지 않도록

	setPos(fPoint((float)x, (float)y));
}
