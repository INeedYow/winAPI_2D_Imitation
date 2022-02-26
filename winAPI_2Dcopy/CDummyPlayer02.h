#pragma once
#include "CPlayer.h"
class CDummyPlayer02 : public CPlayer
{
	
public:
	CDummyPlayer02();
	virtual ~CDummyPlayer02();

	virtual void update();
	virtual void render(HDC hDC);
};

