#include "framework.h"
#include "CEnemy_Worms.h"

#include "SelectGDI.h"

CEnemy_Worms::CEnemy_Worms()
{
	setPos(fPoint(0.f, 0.f));
	setSize(fPoint((float)EW_SIZE, (float)EW_SIZE));
	fvDir = {};
	fTimer = 0.f;
	isNotice = false;
	fAttention = 0.f;
	isWiggle = false;
	fAccel = 0.f;
	isFinish = true;
	fSpeed = EW_SPEED;

	fPosVariance = 0.f;
	fSizeVariance = 0.f;
	isMoveX = true;
}

CEnemy_Worms::~CEnemy_Worms()
{
}

void CEnemy_Worms::setRandDir()
{
	fPoint pos = getPos();
	fPoint size = getSize();
	UINT random = 0;

	if ((int)pos.x <= (int)size.x / 2)							// 위치 : 좌 -> xDir : 우
	{
		fvDir = { 1.f, 0.f };
		isMoveX = true;
		fPosVariance = fSpeed * fvDir.x * DT;
	}
	else if ((int)pos.x >= (int)WINSIZEX - (int)size.x / 2)		// 위치 : 우 -> xDir : 좌
	{
		fvDir = { -1.f, 0.f };
		isMoveX = true;
		fPosVariance = fSpeed * fvDir.x * DT;
	}
	else if ((int)pos.y <= (int)size.x / 2)						// 위치 : 상 -> yDir : 하
	{
		fvDir = { 0.f, 1.f };
		isMoveX = false;
		fPosVariance = fSpeed * fvDir.y * DT;
	}
	else if ((int)pos.y >= (int)WINSIZEY - (int)size.x / 2)		// 위치 : 하 -> yDir : 상
	{
		fvDir = { 0.f, -1.f };
		isMoveX = false;
		fPosVariance = fSpeed * fvDir.y * DT;
	}
	else
	{
		random = rand() % 4;

		switch (random)
		{
		case 0:
			fvDir = { 1.f, 0.f };
			isMoveX = true;
			fPosVariance = fSpeed * fvDir.x * DT;
			break;
		case 1:
			fvDir = { -1.f, 0.f };
			isMoveX = true;
			fPosVariance = fSpeed * fvDir.x * DT;
			break;
		case 2:
			fvDir = { 0.f, 1.f };
			isMoveX = false;
			fPosVariance = fSpeed * fvDir.y * DT;
			break;
		case 3:
			fvDir = { 0.f, -1.f };
			isMoveX = false;
			fPosVariance = fSpeed * fvDir.y * DT;
			break;
		}
	}
}

void CEnemy_Worms::update()
{
	fPoint pos = getPos();
	fPoint size = getSize();
	fPoint playerPos = GETPOS;

	int sight = ISMODE ? P_SIGHTON : P_SIGHTOFF;
	float xDist, yDist;

	if (pos.COLL_PC(pos, playerPos, sight))			// 시야 안에 있으면
	{
		if (fAttention <= 3.f)
			fAttention += ISMODE ? 2 * DT : DT;	
		if (fAttention >= 2.f)
			isNotice = true;
	}
	else											// 시야 안에 없으면
	{
		if (fAttention > 0.f)
			fAttention -= DT;	
		if (fAttention <= 1.f)
			isNotice = false;
	}

	fTimer -= DT;
	if (fTimer > 0.f)
		return;
	
	if (isFinish)									// 움직임 한 싸이클 끝났으면
	{	
		if (isNotice)									// 어그로 끌린 상태면
		{	// x,y거리 중 긴 거리 방향으로 이동
			xDist = abs(playerPos.x - pos.x);
			yDist = abs(playerPos.y - pos.y);

			if (xDist >= yDist)
			{	// x거리가 더 멀면 x로 이동
				if (pos.x > playerPos.x)
					fvDir = {-1.f, 0.f};
				else
					fvDir = { 1.f, 0.f };
				fPosVariance = fSpeed * fvDir.x * DT;
				isMoveX = true;
			}
			else
			{	// y가 더 멂
				if (pos.y > playerPos.y)
					fvDir = { 0.f, -1.f };
				else
					fvDir = { 0.f, 1.f };

				fPosVariance = fSpeed * fvDir.y * DT;
				isMoveX = false;
			}
			
		}
		else											// 어그로 안 끌린 상태면
		{	// 랜덤 방향 설정
			setRandDir();
		}
		fSizeVariance = abs(fPosVariance);
		isWiggle = true;
		isFinish = false;
	}
	else											// 움직임 싸이클 진행 중
	{	// 움직임 구현
		if (isMoveX)				// x
		{
			if (isWiggle)			// 늘어남
			{
				pos.x += 2 * fPosVariance;
				size.x += 4 * fSizeVariance;
			}
			else					// 줄어듦
			{
				pos.x += fPosVariance;
				size.x -= 2 * fSizeVariance;
			}
		}
		else						// y
		{
			if (isWiggle)			// 늘어남
			{
				pos.y += 2 * fPosVariance;
				size.y += 4 * fSizeVariance;
			}
			else					// 줄어듦
			{
				pos.y += fPosVariance;
				size.y -= 2 * fSizeVariance;
			}
		}

		// 최대 변화량만큼 늘어났으면 줄어들게 
		// TODO : 또는 xDist,yDist만큼 이동했을 경우도 추가해야 함
		if ((float)EW_LENMAX <= size.x || (float)EW_LENMAX <= size.y)
		{
			isWiggle = false;
			fTimer = 0.8f;
		}

		// 원래 크기만큼 줄어들었으면 움직임 한 사이클 종료
		if ((float)EW_SIZE > size.x)
		{
			isFinish = true;
			size.x = (float)EW_SIZE;
			fTimer = 0.4f;
		}
		if ((float)EW_SIZE > size.y)
		{
			isFinish = true;
			size.y = (float)EW_SIZE;
			fTimer = 0.4f;
		}
	}
	
	setPos(pos);
	setSize(size);
	// TODO : 적은 모두 원으로 할 생각으로 원으로 충돌검사했는데 얘는 네모인데도 원으로 충돌검사하는 중임.. 해결방법은?
}

void CEnemy_Worms::render(HDC hDC)
{
	fPoint pos = getPos();
	fPoint playerPos = GETPOS;

	int sight = ISMODE ? P_SIGHTON : P_SIGHTOFF;

	SelectGDI pen(hDC, PEN::E_EDGE);
	SelectGDI brush(hDC, BRUSH::EW_BRU);

	/*if (!pos.COLL_PC(pos, playerPos, sight))
	{
		if (ISSCAN)
			Rectangle(hDC, pos.x - 1, pos.y - 1, pos.x + 1, pos.y + 1);
		return;
	}*/

	Rectangle(hDC,
		(int)(getPos().x - getSize().x / 2),
		(int)(getPos().y - getSize().y / 2),
		(int)(getPos().x + getSize().x / 2),
		(int)(getPos().y + getSize().y / 2));

	if (isNotice)
	{
		SelectGDI font(hDC, FONT::COMIC24);

		SetTextColor(hDC, RGB(200, 150, 50));
		TextOutW(hDC, pos.x, pos.y - 20, strMsg, wcslen(strMsg));
	}
}
