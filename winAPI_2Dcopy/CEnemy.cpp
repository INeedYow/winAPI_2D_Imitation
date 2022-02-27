#include "framework.h"
#include "CEnemy.h"

CEnemy::CEnemy()
{
	fSpeed = 30.f;
	fvDir = fVec2(0.f, 0.f);
	setPos(fPoint(470.f, 220.f));
	setSize(fPoint(O_SIZE, O_SIZE));
	fTimer = 0.f;
}

CEnemy::~CEnemy()
{
}


void CEnemy::setRandPos(int hSize)
{	// �� �ۿ��� ��ȯ�� �� ��ġ ������
	int quat = rand() % 4;
	int x = 0;
	int y = 0;
	switch (quat)
	{
	case 0:
		x = -hSize;
		y = rand() % (int)WINSIZEY;
		break;
	case 1:
		x = hSize;
		y = rand() % (int)WINSIZEY;
		break;
	case 2:
		x = rand() % (int)WINSIZEX;
		y = -hSize;
		break;
	case 3:
		x = rand() % (int)WINSIZEX;
		y = hSize;
		break;
	}
	setPos(fPoint(x, y));
}

void CEnemy::setDir(fVec2 vec)
{
	fvDir = vec.normalize();
}

void CEnemy::chaseMe()
{
	fPoint pos = getPos();
	fPoint playerPos = GETPOS;

	fvDir.x = playerPos.x - pos.x;
	fvDir.y = playerPos.y - pos.y;
	if (0 != fvDir.x || 0 != fvDir.y)
		setDir(fvDir);
}
