#pragma once
#include "CObject.h"

// 해보다 막힘
/////////////////////////////////////////////////////////////////////
//class CEnemy : public CObject
//{
//	float	fSpeed;
//	fPoint	startPoint;			// ~ 에서
//	fPoint	turnPoint;			// ~ 까지 왕복
//	fVec2	fVector;			// 방향성
//	bool	isDir;				// 가는 중인지 돌아오는 중인지
//
//public:
//	CEnemy();
//	CEnemy(fPoint pos, fPoint size, float spd, /*fVec2 fVec,*/
//			 fPoint start, fPoint turn, bool dir = true);
//	~CEnemy();
//
//	virtual void update();
//	virtual void render(HDC hDC);
//
//};
////////////////////////////////////////////////////////////////////

// 수업 예제처럼
class CEnemy : public CObject
{	// 상하 패턴
	float	fSpeed;
	bool	isDirUp;
	fPoint	centerPoint;
	float	fDistance;

public:
	CEnemy();
	CEnemy(fPoint pos, fPoint size, float spd, 
			fPoint center, float dist, bool dir = 1);
	~CEnemy();

	virtual void update();
	virtual void render(HDC hDC);
};

