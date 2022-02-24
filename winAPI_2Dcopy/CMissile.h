#pragma once
#include "CObject.h"
class CMissile : public CObject
{
	float fSpeed;
	unsigned int dir;

public:
	CMissile();
	CMissile(fPoint pos, fPoint size, float spd, unsigned int _dir);
	~CMissile();

	virtual void update();
	virtual void render(HDC hDC);

	void setDir(unsigned int _dir);
};

// TODO 미사일 지우는 것 필요