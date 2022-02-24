#pragma once
#include "CObject.h"
class CTarget : public CObject
{
	// bool type;		// block이 될 target인지 enemy가 될 target인지
public:
	CTarget();
	CTarget(fPoint pos/*, bool type*/);
	virtual ~CTarget();

	virtual void update();
	virtual void render(HDC hDC);
};

// 먹지 않은 타겟은 그 위치의 벽이 되는데
// 몬스터가 되는 타겟도 만들지(만들 수 있을지) 고민 중