#pragma once
#include "CEnemy.h"
class CEnemy_Crawler : public CEnemy
{
	bool	isNotice;
	bool	isBoosting;			// ���� ����
	float	fAttention;
	float	fAccel;				// ����
	float	fDecel;				// ����

public:
	CEnemy_Crawler();
	virtual ~CEnemy_Crawler();

	virtual void update();
	virtual void render(HDC hDC);
};

