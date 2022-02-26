#pragma once
#include "CObject.h"

class CEnemy : public CObject
{	
	float	fAttention;		// 플레이어 시야에 일정시간 노출되면 플레이어 향해 오도록 할 생각
	float	fMoveCycle;		// 일정시간마다 움직임 랜덤 재설정
	float	fSpeed;	
	fVec2	fvDir;
	bool	isFever;		// attention 누적 시 플레이어 향해 다가오게, '!' 출력
	float	fFeverCount;	// '!' 출력 시간

public:
	CEnemy();
	CEnemy(fPoint pos, fPoint size, float spd, fVec2 dir = fVec2(0.f,0.f));
	~CEnemy();

	void setDir(fVec2 vec);
	void setRandDir();

	virtual void update();
	virtual void render(HDC hDC);
};