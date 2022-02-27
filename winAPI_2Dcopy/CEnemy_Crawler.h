#pragma once
#include "CEnemy.h"
class CEnemy_Crawler : public CEnemy
{
	bool	isNotice;
	bool	isBoosting;			// 증감 구분
	float	fAttention;
	float	fAccel;				// 가속
	float	fDecel;				// 감속

public:
	CEnemy_Crawler();
	virtual ~CEnemy_Crawler();

	virtual void update();
	virtual void render(HDC hDC);
};

