#pragma once
#include "CScene.h"
class CScene_Tutorial01 : public CScene
{
public:
	CScene_Tutorial01();
	virtual ~CScene_Tutorial01();

	//virtual void update();		// �θ� ���鼭 CScene::update() ���ָ� ��

	virtual void enter();
	virtual void exit();
};
