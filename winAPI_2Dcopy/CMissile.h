#pragma once
#include "CObject.h"
#include <stdlib.h>
class CMissile : public CObject
{
	float m_fSpeed;
	fVec2 m_fvDir;
	float m_gravity;
	
public:
	CMissile();
	CMissile(fPoint pos, fPoint size, float spd, fVec2 dir);
	~CMissile();

	virtual void update();
	virtual void render(HDC hDC);

	void setDir(fVec2 vec);
	void setDir(float theta);
};

// TODO 미사일 지우는 것 필요