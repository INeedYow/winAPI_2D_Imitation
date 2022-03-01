#pragma once
#include "CEnemy.h"

class CEnemy_Zombie :public CEnemy
{
protected:
	float	fAttention;		// �÷��̾� �þ߿� �����ð� ����Ǹ� �÷��̾� ���� ������ �� ����
	bool	isNotice;		// attention ���� �� �÷��̾� ���� �ٰ�����, '!' ���
	bool	isMove;			// ������ ���� ������

public:
	CEnemy_Zombie();
	CEnemy_Zombie(fPoint pos, fVec2 dir = fVec2(0.f, 0.f));
	virtual ~CEnemy_Zombie();

	
	void setRandSpeed();

	virtual void update();
	virtual void render(HDC hDC);
};