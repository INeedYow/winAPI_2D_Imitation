#pragma once
#include "CObject.h"

class CEnemy : public CObject
{
protected:
	float	fSpeed;			
	fVec2	fvDir;
	float	fTimer;				// 특수 기능 타이머

public:
	CEnemy();
	virtual ~CEnemy();

	void setRandPos(int size);	// zombie는 현재 맵 밖에서 생성하면 안 돼서 자식마다 다르게 쓰려고

	void setDir(fVec2 vec);
	void chaseMe();				// Dir을 내게 오게 설정
	
	virtual void update() = 0;
	virtual void render(HDC hDC) = 0;
};