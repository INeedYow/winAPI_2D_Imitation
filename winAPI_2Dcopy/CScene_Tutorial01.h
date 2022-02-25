#pragma once
#include "CScene.h"
class CScene_Tutorial01 : public CScene
{

public:
	CScene_Tutorial01();
	virtual ~CScene_Tutorial01();

	//virtual void update();

	virtual void enter();
	virtual void exit();
};

// update()랑 render()는 virtual로 받아쓰면 
// 부모의 해당 씬 모든 옵젝 update, render 함수 돌려주는 기능 잃음