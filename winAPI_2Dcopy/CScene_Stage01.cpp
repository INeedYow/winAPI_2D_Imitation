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
	CPlayer* pPlayer = new CPlayer();
	CEnemy* pEnemy = new CEnemy();

	addObject(pPlayer, OBJ::PLAYER);
	addObject(pEnemy, OBJ::ENEMY);
}

void CScene_Stage01::exit()
{
	vector<CObject*>* pVec = getVecArr();

	for (int i = 0; i < (int)OBJ::SIZE; i++)
	{
		for (int j = 0; j < pVec[i].size(); j++)
			delete pVec[i][j];

		while (pVec[i].size() > 0)
			pVec[i].pop_back();
	}
}