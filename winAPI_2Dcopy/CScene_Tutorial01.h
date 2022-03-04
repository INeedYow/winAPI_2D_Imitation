#pragma once
#include "CScene.h"
class CScene_Tutorial01 : public CScene
{
public:
	CScene_Tutorial01();
	virtual ~CScene_Tutorial01();

	//virtual void update();		// 부모꺼 쓰면서 CScene::update() 해주면 됨

	virtual void enter();
	virtual void exit();
};
