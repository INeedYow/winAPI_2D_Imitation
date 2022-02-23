#include "framework.h"
#include "CEnemy.h"
///////////////////////////////////////////////////////////////////////////
//CEnemy::CEnemy()
//{
//	setPos(fPoint(0, 0));
//	setSize(fPoint(1, 1));
//	isDir = true;
//	fSpeed = 150;
//	startPoint = fPoint(1, 1);
//	turnPoint = fPoint(1, 2);
//	fVector = fVec2(0, 0);
//}


//CEnemy::CEnemy(fPoint pos, fPoint size, float spd, /*fVec2 fVec,*/
//	fPoint start, fPoint turn, bool dir = true)
//{
//	setPos(pos);
//	setSize(size);
//	fSpeed = spd;
//	startPoint = start;
//	turnPoint = turn;
//	fVector = fVec2(turn.x - start.x, turn.y - start.y);
//	isDir = dir;
//}
////////////////////////////////////////////////////////////////////////////

CEnemy::CEnemy()
{
	fSpeed		= 150;
	isDirUp		= true;
	centerPoint = fPoint((float)(WINSIZEX - 150), WINSIZEY / 2.f);
	fDistance	= 200.f;
	setPos(centerPoint);
	setSize(fPoint(200.f, 200.f));
}

CEnemy::~CEnemy()
{
}

////////////////////////////////////////////////////////////////////////////
//void CEnemy::update()
//{
//	fPoint enemyPos = getPos();
//
//	// ������, ������ ��⸸�ϰ� ���ƿ��� �Ϸ��� �����̴� ���⿡ ���� �ش� ���� ��ǥ�� ���ؾ� �� ��
//		// -> �߽�(Pos) �������� �պ��ϵ��� ����
//
//	if (isDir)
//	{
//		if (enemyPos == turnPoint)
//			isDir = false;
//		else
//			enemyPos.
//	}
//	else
//	{
//
//	}
//}
////////////////////////////////////////////////////////////////////////////

void CEnemy::update()
{
	fPoint enemyPos = getPos();

	if (isDirUp)	// ���� �̵��ϴµ�
	{	// enemy ���� y��ǥ�� �̵����� �����
		if (enemyPos.y - (getSize().y / 2) <= centerPoint.y - fDistance)
			isDirUp = false;
		else
			enemyPos.y -= fSpeed * DT;
	}
	else			// �Ʒ��� �̵��ϴµ�
	{	// enemy �Ʒ��� y��ǥ�� �̵����� �����
		if (enemyPos.y + (getSize().y / 2) >= centerPoint.y + fDistance)
			isDirUp = true;
		else
			enemyPos.y += fSpeed * DT;
	}

	setPos(enemyPos);
}

void CEnemy::render(HDC hDC)
{
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HBRUSH hBrush = CreateSolidBrush(RGB(50, 50, 50));

	HPEN hOriginalPen = (HPEN)SelectObject(hDC, hPen);
	HBRUSH hOriginalBrush = (HBRUSH)SelectObject(hDC, hBrush);

	Rectangle(hDC,
		(int)(getPos().x - getSize().x / 2),
		(int)(getPos().y - getSize().y / 2),
		(int)(getPos().x + getSize().x / 2),
		(int)(getPos().y + getSize().y / 2));

	SelectObject(hDC, hOriginalPen);
	SelectObject(hDC, hOriginalBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);
}
