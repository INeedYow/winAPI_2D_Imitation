#pragma once
#include "CItem.h"
class CItem_Bullet : public CItem
{
	UCHAR ucEA;		// 지급할 총알 개수

public:
	CItem_Bullet();
	virtual ~CItem_Bullet();

	void setRandEA();

	UCHAR getEA();

	virtual void update();
	virtual void render(HDC hDC);
};

