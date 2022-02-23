#pragma once
#include "CObject.h"
class CPlayer : public CObject
{
	float fSpeed;
public:
	CPlayer();
	~CPlayer();

	virtual void update();
	virtual void render(HDC hDC);
};

