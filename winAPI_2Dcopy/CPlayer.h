#pragma once
#include "CObject.h"
class CPlayer : public CObject
{
	float fSpeed;
	
	//static bool isDarkMode;

public:
	CPlayer();
	~CPlayer();

	virtual void update();
	virtual void render(HDC hDC);

	//bool getIsMode();
};

// ������Ģ ������ �� ���µ�
// ���ӵ� ���� �����ұ�

// isDarkMode�� �÷��̾ ������ �� �����鼭 
// �ٸ� ������Ʈ���� bool ���� ���� ������ �ް� �ϰ� �;
// ���� ��� ������ ������ �ߴµ� Ȯ���� �� ���� �ܺα�ȣ��� ��ũ ������ ��