#pragma once
#include "CObject.h"

// �¿� Ȥ�� ���Ϸθ� �����̸� ���� �ε����� ������ȯ
class CEnemy : public CObject
{	
	bool	isPattern;	// ���� ����, �¿� ����
	bool	isDir;		// ���� ������ ���� ������
	float	fSpeed;

public:
	CEnemy();
	CEnemy(bool pattern, bool dir, float spd);
	~CEnemy();

	virtual void update();
	virtual void render(HDC hDC);
};

// �Ի簢 �ݻ簢 Ƣ��� ��ó�� ����?