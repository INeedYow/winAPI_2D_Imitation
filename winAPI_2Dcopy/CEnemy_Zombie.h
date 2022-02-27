#pragma once
#include "CEnemy.h"

class CEnemy_Zombie :public CEnemy
{
protected:
	float	fAttention;		// 플레이어 시야에 일정시간 노출되면 플레이어 향해 오도록 할 생각
	bool	isNotice;		// attention 누적 시 플레이어 향해 다가오게, '!' 출력
	float	fFeverCount;	// '!' 출력 시간
	bool	isMove;			// 움직임 패턴 중인지

public:
	CEnemy_Zombie();
	CEnemy_Zombie(fPoint pos, fVec2 dir = fVec2(0.f, 0.f));
	virtual ~CEnemy_Zombie();

	void setRandDir();
	void setRandSpeed();

	virtual void update();
	virtual void render(HDC hDC);
};

