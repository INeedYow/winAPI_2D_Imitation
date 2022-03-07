#pragma once
#include "CObject.h"
class CFireball : public CObject
{
	float	m_fSpeed;
	fVec2	m_fvDir;
	float	m_fDuration;
	float	m_fGravity;

public:
	CFireball();
	virtual ~CFireball();

	void setDir(fVec2 dir);

	virtual void update();
	virtual void render(HDC hDC);

	virtual void collisionEnter(CCollider* pOther);
};

