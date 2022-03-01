#pragma once
#include "CEnemy.h"

class CEnemy_ZombieDog :public CEnemy
{
public:
	CEnemy_ZombieDog();
	virtual ~CEnemy_ZombieDog();

	virtual void update();
	virtual void render(HDC hDC);
};