#pragma once
#include "CPlayer.h"
class CDummyPlayer02 : public CPlayer
{
	UINT	uiPrevBullet;
	LPCWSTR szText;
	UINT	uiCheck;

public:
	CDummyPlayer02();
	virtual ~CDummyPlayer02();

	virtual void update();
	virtual void render(HDC hDC);

	void createNext();
};

