#pragma once
#include "CObject.h"

// 좌우 혹은 상하로만 움직이며 벽에 부딪히면 방향전환
class CEnemy : public CObject
{	
	bool	isPattern;	// 상하 패턴, 좌우 패턴
	bool	isDir;		// 가는 중인지 오는 중인지
	float	fSpeed;

public:
	CEnemy();
	CEnemy(bool pattern, bool dir, float spd);
	~CEnemy();

	virtual void update();
	virtual void render(HDC hDC);
};

// 입사각 반사각 튀기는 공처럼 가능?