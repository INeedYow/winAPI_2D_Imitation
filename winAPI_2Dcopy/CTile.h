#pragma once
#include "CObject.h"
class CTile : public CObject
{
public:
	CTile();
	virtual ~CTile();

	virtual void update();
	virtual void render(HDC hDC);
};

