#pragma once
#include "CObject.h"
class CSightCircle : public CObject
{
	UINT	minRange;		// �þ߹���
	UINT	maxRange;
public:
	CSightCircle();
	virtual ~CSightCircle();

	virtual void update();
	virtual void render(HDC hDC);
	
};

