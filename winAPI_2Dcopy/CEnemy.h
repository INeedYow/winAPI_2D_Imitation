#pragma once
#include "CObject.h"

class CEnemy : public CObject
{	
protected:
	float	fAttention;		// �÷��̾� �þ߿� �����ð� ����Ǹ� �÷��̾� ���� ������ �� ����
	bool	isFever;		// attention ���� �� �÷��̾� ���� �ٰ�����, '!' ���
	float	fFeverCount;	// '!' ��� �ð�
	float	fSpeed;
	float	fTimer;			// �����ð����� ������ ���� �缳��
	bool	isMove;
	fVec2	fvDir;

public:
	CEnemy();
	CEnemy(fPoint pos, fPoint size, float spd, fVec2 dir = fVec2(0.f,0.f));
	virtual ~CEnemy();

	void setDir(fVec2 vec);
	void setRandSpeed();
	void setRandDir();

	virtual void update();
	virtual void render(HDC hDC);
};