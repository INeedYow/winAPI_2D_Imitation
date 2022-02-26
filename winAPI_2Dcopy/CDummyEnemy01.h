#pragma once
#include "CEnemy.h"
class CDummyEnemy01 : public CEnemy
{
	bool isComing;
public:
	CDummyEnemy01();
	virtual ~CDummyEnemy01();

	virtual void update();
	virtual void render(HDC hDC);
};

