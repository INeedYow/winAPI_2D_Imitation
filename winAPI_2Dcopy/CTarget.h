#pragma once
#include "CObject.h"
class CTarget : public CObject
{
	// bool type;		// block�� �� target���� enemy�� �� target����
public:
	CTarget();
	CTarget(fPoint pos/*, bool type*/);
	virtual ~CTarget();

	virtual void update();
	virtual void render(HDC hDC);
};

// ���� ���� Ÿ���� �� ��ġ�� ���� �Ǵµ�
// ���Ͱ� �Ǵ� Ÿ�ٵ� ������(���� �� ������) ��� ��