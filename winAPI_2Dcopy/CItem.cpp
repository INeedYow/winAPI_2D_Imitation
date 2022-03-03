#include "framework.h"
#include "CItem.h"

CItem::CItem()
{
	setPos(fPoint(0.f, 0.f));
	setSize(fPoint((float)I_SIZE,(float)I_SIZE));
	fTimer = 0;
	uiDuration = 12;
	isFlick = false;
	ucKey = (UCHAR)IKEY::NONE;
	strName = L"";

	createCollider();
	getCollider()->setSize(fPoint(I_SIZE - 2, I_SIZE - 2));
	getCollider()->setOffset(fPoint((float)0, (float)0));
	getCollider()->setShape(SHAPE::RECT);
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

void CItem::setIsFlick(bool flick)
{
	isFlick = flick;
}

void CItem::setKey(UCHAR key)
{
	ucKey = key;
}

void CItem::setName(LPCWSTR name)
{
	strName = name;
}

float CItem::getTimer()
{
	return fTimer;
}

UINT CItem::getDuration()
{
	return uiDuration;
}

UCHAR CItem::getKey()
{
	return ucKey;
}

LPCWSTR CItem::getName()
{
	return strName;
}

bool CItem::getIsFlick()
{
	return isFlick;
}

void CItem::setRandPos()
{
	int x, y;
	fPoint playerPos = GETPOS;

	do
	{
		x = rand() % (WINSIZEX - 120) + 60;
		y = rand() % (WINSIZEY - 70) + 40;
	} while (ISCOLLPC(fPoint((float)x, (float)y), playerPos, (int)O_SIZE));
	
	// 플레이어 위치에 너무 가까이 생성되지 않도록

	setIsFlick(false);
	setPos(fPoint((float)x, (float)y));
}
