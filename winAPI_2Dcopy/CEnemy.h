#pragma once
#include "CObject.h"

class CEnemy : public CObject
{	// 상하 패턴
	float	fSpeed;
	bool	isDirUp;
	fPoint	centerPoint;
	float	fDistance;

public:
	CEnemy();
	CEnemy(fPoint pos, fPoint size, float spd, 
			fPoint center, float dist, bool dir = 1);
	~CEnemy();

	virtual void update();
	virtual void render(HDC hDC);
};

