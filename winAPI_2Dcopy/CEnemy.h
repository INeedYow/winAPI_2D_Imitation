#pragma once
#include "CObject.h"

class CEnemy : public CObject
{	
	float	fAttention;		// �÷��̾� �þ߿� �����ð� ����Ǹ� �÷��̾� ���� ������ �� ����
	float	fMoveCycle;		// �����ð����� ������ ���� �缳��
	float	fSpeed;	
	fVec2	fvDir;
	bool	isFever;		// attention ���� �� �÷��̾� ���� �ٰ�����, '!' ���
	float	fFeverCount;	// '!' ��� �ð�

public:
	CEnemy();
	CEnemy(fPoint pos, fPoint size, float spd, fVec2 dir = fVec2(0.f,0.f));
	~CEnemy();

	void setDir(fVec2 vec);
	void setRandDir();

	virtual void update();
	virtual void render(HDC hDC);
};