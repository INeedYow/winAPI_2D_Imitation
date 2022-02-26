#pragma once
#include "CObject.h"
class CITEM_BULLET : public CObject
{
public:
	CITEM_BULLET();
	virtual ~CITEM_BULLET();

	virtual void update();
	virtual void render(HDC hDC);
};

