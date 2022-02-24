#pragma once
#include "CObject.h"

// �غ��� ����
/////////////////////////////////////////////////////////////////////
//class CEnemy : public CObject
//{
//	float	fSpeed;
//	fPoint	startPoint;			// ~ ����
//	fPoint	turnPoint;			// ~ ���� �պ�
//	fVec2	fVector;			// ���⼺
//	bool	isDir;				// ���� ������ ���ƿ��� ������
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

// ���� ����ó��
class CEnemy : public CObject
{	// ���� ����
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

