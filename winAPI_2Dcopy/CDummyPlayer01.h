#pragma once
#include "CPlayer.h"
class CDummyPlayer01 : public CPlayer
{
public:
	CDummyPlayer01();
	virtual ~CDummyPlayer01();

	virtual void update();
	virtual void render(HDC hDC);
};

