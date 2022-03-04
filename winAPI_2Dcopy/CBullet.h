#pragma once
#include "CObject.h"
class CBullet : public CObject
{
	fVec2	m_fvDir;
	float	m_fSpeed;

public:
	CBullet();
	CBullet(fPoint pos, fVec2 vec, float spd = (float)B_SPEED);
	virtual ~CBullet();

	virtual void update();
	virtual void render(HDC hDC);
};