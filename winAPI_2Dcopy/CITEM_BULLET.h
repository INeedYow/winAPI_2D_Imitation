#pragma once
#include "CItem.h"
class CItem_Bullet : public CItem
{
	UCHAR ucEA;		// ������ �Ѿ� ����

public:
	CItem_Bullet();
	virtual ~CItem_Bullet();

	void setRandEA();

	UCHAR getEA();

	virtual void update();
	virtual void render(HDC hDC);
};

