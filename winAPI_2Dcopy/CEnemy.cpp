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
{	// 맵 밖에서 소환할 때 위치 설정용
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

void CEnemy::setRandDir()
{
	fPoint pos = getPos();
	fPoint size = getSize();

	if ((int)pos.x <= (int)size.x / 2)							// 위치 : 좌 -> xDir : 우
		fvDir.x = rand() % 5;
	else if ((int)pos.x >= (int)WINSIZEX - (int)size.x / 2)		// 위치 : 우 -> xDir : 좌
		fvDir.x = rand() % 5 - 4;
	else
		fvDir.x = rand() % 9 - 4;

	if ((int)pos.y <= (int)size.x / 2)							// 위치 : 상 -> yDir : 하
		fvDir.y = rand() % 5;
	else if ((int)pos.y >= (int)WINSIZEY - (int)size.x / 2)		// 위치 : 하 -> yDir : 상
		fvDir.y = rand() % 5 - 4;
	else
		fvDir.y = rand() % 9 - 4;
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
