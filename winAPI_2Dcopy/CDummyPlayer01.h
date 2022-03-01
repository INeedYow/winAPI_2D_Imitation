#pragma once
#include "CPlayer.h"
class CDummyPlayer01 : public CPlayer
{
	LPCWSTR strMsg1;
	LPCWSTR strMsg2;
public:
	CDummyPlayer01();
	virtual ~CDummyPlayer01();

	virtual void update();
	virtual void render(HDC hDC);
};

