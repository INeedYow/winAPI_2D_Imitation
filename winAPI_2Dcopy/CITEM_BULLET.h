#pragma once
#include "CItem.h"
class CItem_Bullet : public CItem
{
	UINT uiEA;		// 지급할 총알 개수 (또한 랜덤)

public:
	CItem_Bullet();
	virtual ~CItem_Bullet();

	void setRandEA();

	virtual void update();
	virtual void render(HDC hDC);
};

