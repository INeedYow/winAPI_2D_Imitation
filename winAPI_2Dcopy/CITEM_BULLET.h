#pragma once
#include "CItem.h"
class CItem_Bullet : public CItem
{
	UINT uiEA;		// ������ �Ѿ� ���� (���� ����)

public:
	CItem_Bullet();
	virtual ~CItem_Bullet();

	void setRandEA();

	virtual void update();
	virtual void render(HDC hDC);
};

