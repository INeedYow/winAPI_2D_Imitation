#include "framework.h"
#include "CScene_Stage01.h"
#include "CPlayer.h"
#include "CTile.h"

CScene_Stage01::CScene_Stage01()
{
	setName(L"Stage01_Scene");
}

CScene_Stage01::~CScene_Stage01()
{
}

void CScene_Stage01::enter()
{
	// 스코어 초기화
	CPlayer::setCoin(0);

	// 오브젝트 생성
	CPlayer* pPlayer = new CPlayer();
	pPlayer->setPos(fPoint(100.f, (float)(WINSIZEY - T_SIZE)));
	for (int i = 0; i < 20; i++)
	{
		CTile* pTile1 = new CTile();
		pTile1->setPos(fPoint((float)(T_SIZE / 2 + i * T_SIZE), (float)(WINSIZEY - T_SIZE / 2)));
		addObject(pTile1, OBJ::TILE);
	}
	CTile* pTile2 = new CTile();
	pTile2->setPos(fPoint((float)(700.f), (float)(WINSIZEY - T_SIZE / 2 - T_SIZE)));
	addObject(pTile2, OBJ::TILE);

	addObject(pPlayer, OBJ::PLAYER);
	

	// 각 씬마다 오브젝트끼리 충돌 여부 설정가능
	CCollisionManager::getInst()->checkGroup(OBJ::PLAYER, OBJ::TILE);
}

void CScene_Stage01::exit()
{
	deleteObjectAll();

	CCollisionManager::getInst()->resetGroup();
}