#pragma once
#include "CEnemy.h"
class CEnemy_Crawler : public CEnemy
{
	bool	isNotice;
	float	fAttention;

	bool	isBoosting;			// ���� ����
	float	fAccel;				// ����
	float	fDecel;				// ����

public:
	CEnemy_Crawler();
	virtual ~CEnemy_Crawler();

	virtual void update();
	virtual void render(HDC hDC);
};

