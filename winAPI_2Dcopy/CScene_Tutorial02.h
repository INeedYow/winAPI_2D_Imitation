#pragma once
#include "CScene.h"
class CScene_Tutorial02 : public CScene
{
public:
	CScene_Tutorial02();
	virtual ~CScene_Tutorial02();

	virtual void update();
	virtual void render(HDC hDC);

	virtual void enter();
	virtual void exit();
};

