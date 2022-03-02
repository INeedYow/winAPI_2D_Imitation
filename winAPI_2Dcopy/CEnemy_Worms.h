#pragma once
#include "CEnemy.h"
class CEnemy_Worms :   public CEnemy
{
	bool	isNotice;
	float	fAttention;

	bool	isFinish;		// 한 번의 이동 주기 끝났는지
	bool	isWiggle;		// 늘어나는 중인지
	bool	isMoveX;		// 움직이는 축
	float	fAccel;			// 가속

	float	fPosVariance;	// 좌표 변화량
	float	fSizeVariance;	// 크기 변화량


public:
	CEnemy_Worms();
	virtual ~CEnemy_Worms();

	virtual void setRandDir();

	virtual void update();
	virtual void render(HDC hDC);
};

