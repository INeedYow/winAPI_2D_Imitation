#pragma once
#include "CItem.h"
class CItem_Scanner : public CItem
{
public:
	CItem_Scanner();
	virtual ~CItem_Scanner();

	virtual void update();
	virtual void render(HDC hDC);
};

