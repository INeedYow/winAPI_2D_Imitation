#pragma once
#include "CObject.h"

class CEnemy : public CObject
{
protected:
	float	fSpeed;			
	fVec2	fvDir;
	float	fTimer;				// Ư�� ��� Ÿ�̸�

public:
	CEnemy();
	virtual ~CEnemy();

	void setRandPos(int size);	// zombie�� ���� �� �ۿ��� �����ϸ� �� �ż� �ڽĸ��� �ٸ��� ������

	void setDir(fVec2 vec);
	void chaseMe();				// Dir�� ���� ���� ����
	
	virtual void update() = 0;
	virtual void render(HDC hDC) = 0;
};