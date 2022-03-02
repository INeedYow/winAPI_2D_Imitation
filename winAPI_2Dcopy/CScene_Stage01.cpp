#include "framework.h"
#include "CScene_Stage01.h"

#include "CPlayer.h"
#include "CItem_Bullet.h"
#include "CItem_Scanner.h"
#include "CBattery.h"
#include "CEnemy_Zombie.h"
#include "CEnemy_ZombieDog.h"
#include "CEnemy_Crawler.h"
#include "CEnemy_Worms.h"
#include "CSightCircle.h"

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
	g_resultTimer = 0.f;
	g_resultBullet = 0;
	g_resultKill = 0;
	SETSCANTIMER(0.f);
	SETBULLET(8);

	CPlayer* pPlayer = new CPlayer();
	CBattery* pBattery = new CBattery();
	CSightCircle* pSight = new CSightCircle();

	CEnemy_Zombie* pEnemy1 = new CEnemy_Zombie();
	pEnemy1->setPos(fPoint(400.f, 300.f));
	CEnemy_Zombie* pEnemy2 = new CEnemy_Zombie();
	pEnemy2->setPos(fPoint(200.f,250.f));
	CEnemy_Zombie* pEnemy3 = new CEnemy_Zombie();
	pEnemy3->setPos(fPoint(150.f, 400.f));
	CEnemy_Zombie* pEnemy4 = new CEnemy_Zombie();
	pEnemy4->setPos(fPoint(200.f, 550.f));
	CEnemy_Zombie* pEnemy5 = new CEnemy_Zombie();
	pEnemy5->setPos(fPoint(1100.f, 400.f));
	CEnemy_Zombie* pEnemy6 = new CEnemy_Zombie();
	pEnemy5->setPos(fPoint(1200.f, 100.f));

	CEnemy_ZombieDog* pDog1 = new CEnemy_ZombieDog();
	CEnemy_ZombieDog* pDog2 = new CEnemy_ZombieDog();

	CEnemy_Crawler* pCrawler1 = new CEnemy_Crawler();
	pCrawler1->setPos(fPoint(300.f,150.f));
	CEnemy_Crawler* pCrawler2 = new CEnemy_Crawler();
	pCrawler2->setPos(fPoint(900.f,600.f));

	CEnemy_Worms* pWorms1 = new CEnemy_Worms();
	pWorms1->setPos(fPoint(640.f, 600.f));

	CItem_Bullet* pItemBull1 = new CItem_Bullet();
	CItem_Bullet* pItemBull2 = new CItem_Bullet();
	CItem_Scanner* pItemScan1 = new CItem_Scanner();

	addObject(pPlayer, OBJ::PLAYER);
	addObject(pEnemy1, OBJ::ENEMY);
	addObject(pEnemy2, OBJ::ENEMY);
	addObject(pEnemy3, OBJ::ENEMY);
	addObject(pEnemy4, OBJ::ENEMY);
	addObject(pEnemy5, OBJ::ENEMY);
	addObject(pEnemy6, OBJ::ENEMY);
	addObject(pDog1, OBJ::ENEMY);
	addObject(pDog2, OBJ::ENEMY);
	addObject(pCrawler1, OBJ::ENEMY);
	addObject(pCrawler2, OBJ::ENEMY);
	addObject(pWorms1, OBJ::ENEMY);

	addObject(pItemBull1, OBJ::DROPITEM);
	addObject(pItemBull2, OBJ::DROPITEM);
	addObject(pItemScan1, OBJ::DROPITEM);
	addObject(pBattery, OBJ::BATTERY);
	addObject(pSight, OBJ::SIGHTCIRCLE);

	// 각 씬마다 오브젝트끼리 충돌 여부 설정가능
	CCollisionManager::getInst()->checkGroup(OBJ::PLAYER, OBJ::ENEMY);
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

	CCollisionManager::getInst()->resetGroup();
}