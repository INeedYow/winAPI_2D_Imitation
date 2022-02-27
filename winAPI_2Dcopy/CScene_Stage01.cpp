#include "framework.h"
#include "CScene_Stage01.h"

#include "CEnemy.h"
#include "CPlayer.h"
#include "CItem_Bullet.h"
#include "CItem_Scanner.h"
#include "CBattery.h"

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
	CBattery* pBattery = new CBattery();

	CEnemy* pEnemy1 = new CEnemy();
	CEnemy* pEnemy2 = new CEnemy();
	pEnemy2->setPos(fPoint(200.f,250.f));
	CEnemy* pEnemy3 = new CEnemy();
	pEnemy3->setPos(fPoint(150.f, 400.f));
	CEnemy* pEnemy4 = new CEnemy();
	pEnemy4->setPos(fPoint(200.f, 550.f));
	CEnemy* pEnemy5 = new CEnemy();
	pEnemy5->setPos(fPoint(1100.f, 400.f));
	CItem_Bullet* pItemBull1 = new CItem_Bullet();
	CItem_Bullet* pItemBull2 = new CItem_Bullet();
	CItem_Scanner* pItemScan1 = new CItem_Scanner();


	addObject(pPlayer, OBJ::PLAYER);
	addObject(pEnemy1, OBJ::ENEMY);
	addObject(pEnemy2, OBJ::ENEMY);
	addObject(pEnemy3, OBJ::ENEMY);
	addObject(pEnemy4, OBJ::ENEMY);
	addObject(pEnemy5, OBJ::ENEMY);
	addObject(pItemBull1, OBJ::DROPITEM);
	addObject(pItemBull2, OBJ::DROPITEM);
	addObject(pItemScan1, OBJ::DROPITEM);
	addObject(pBattery, OBJ::BATTERY);
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