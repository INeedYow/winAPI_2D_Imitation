#pragma once
#include "CScene.h"
class CScene_Ending : public CScene
{

public:
	virtual void update();
	virtual void render(HDC hDC);

	virtual void enter();
	virtual void exit();
};

