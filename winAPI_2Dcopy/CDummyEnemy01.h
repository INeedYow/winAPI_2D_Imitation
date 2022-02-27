#pragma once
#include "CEnemy_Zombie.h"

class CDummyEnemy01 : public CEnemy_Zombie
{
	bool isComing;
public:
	CDummyEnemy01();
	virtual ~CDummyEnemy01();

	virtual void update();
	virtual void render(HDC hDC);
};

