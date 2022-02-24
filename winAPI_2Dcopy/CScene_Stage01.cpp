#include "framework.h"
#include "CScene_Stage01.h"

#include "CEnemy.h"
#include "CPlayer.h"

CScene_Stage01::CScene_Stage01()
{
	setName(L"Stage01_Scene");
}

CScene_Stage01::~CScene_Stage01()
{
}

void CScene_Stage01::enter()
{
	CEnemy* pEnemy = new CEnemy();
	CPlayer* pPlayer = new CPlayer();

	addObject(pEnemy, OBJ::ENEMY);
	addObject(pPlayer, OBJ::PLAYER);
}

void CScene_Stage01::exit()
{
}

