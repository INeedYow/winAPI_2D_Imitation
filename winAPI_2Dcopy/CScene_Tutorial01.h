#pragma once
#include "CScene.h"
class CScene_Tutorial01 : public CScene
{
	//unsigned int m_uiPage;

public:
	CScene_Tutorial01();
	virtual ~CScene_Tutorial01();

	//virtual void update();

	virtual void enter();
	virtual void exit();
};

// Ʃ�丮���� ���� �ܰ�� �������� �;��µ� �� ���
// 1) ������ ������ �ΰ� �� Ŭ���� ������ ó���ϴ� �� ������
// 2) ���� Ʃ�丮�� Ŭ������ ����� �� ��ȯ�ϰ� ����� �� ������
// ����ε� �ϴ� 2������ ����

// update()�� render()�� virtual�� �޾ƾ��� 
// �θ��� �ش� �� ��� ���� update, render �Լ� �����ִ� ��� ����