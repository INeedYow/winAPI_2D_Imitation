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

// update()�� render()�� virtual�� �޾ƾ��� 
// �θ��� �ش� �� ��� ���� update, render �Լ� �����ִ� ��� ����