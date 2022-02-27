#pragma once
#include "CEnemy.h"

class CEnemy_ZombieDog :public CEnemy
{
	LPCWSTR		wcGrrr;

public:
	CEnemy_ZombieDog();
	virtual ~CEnemy_ZombieDog();

	virtual void update();
	virtual void render(HDC hDC);
};