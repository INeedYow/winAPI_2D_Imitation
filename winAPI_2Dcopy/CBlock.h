#pragma once
#include "CObject.h"
class CBlock : public CObject
{

public:
	CBlock();
	virtual ~CBlock();

	virtual void update();
	virtual void render(HDC hDC);
};

