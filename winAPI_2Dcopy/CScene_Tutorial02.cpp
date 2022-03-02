#include "framework.h"
#include "CScene_Tutorial02.h"
#include "CText.h"
#include "CDummyPlayer02.h"
#include "CItem_Bullet.h"
#include "CBattery.h"
#include "CSightCircle.h"


CScene_Tutorial02::CScene_Tutorial02()
{
	setName(L"Tutorial02_Scene");
}

CScene_Tutorial02::~CScene_Tutorial02()
{
}

// 더미 1,2 모두 더미 배열에
/////////////////////////////////////////////////////////////////////////////////////////
// 뭔가 튜토리얼에서 오래 끌다가 stage로 들어가면 아무것도 출력 안되는 버그가 있는데 왜인지 모르겠음
////////////////////////////////////////////////////////////////////////////////////////
void CScene_Tutorial02::enter()
{


	CDummyPlayer02* pDumPlayer = new CDummyPlayer02();
	CText* pText1 = new CText(fPoint(590.f, 230.f), L"튜토리얼 2 / 2", 22);
	CText* pText2 = new CText(fPoint(560.f, 145.f), L"스킵하고 게임시작 : \'D\'", 20);
	CItem_Bullet* pItemBullet1 = new CItem_Bullet;
	CItem_Bullet* pItemBullet2 = new CItem_Bullet;
	pItemBullet1->setPos(fPoint(500.f,360.f));
	pItemBullet2->setPos(fPoint(800.f,410.f));
	CBattery* pBattery = new CBattery();
	CSightCircle* pSight = new CSightCircle();

	addObject(pSight, OBJ::SIGHTCIRCLE);
	addObject(pDumPlayer, OBJ::DUMMYPLAYER);
	addObject(pText1, OBJ::TEXT);
	addObject(pText2, OBJ::TEXT);
	addObject(pItemBullet1, OBJ::DROPITEM);
	addObject(pItemBullet2, OBJ::DROPITEM);
	addObject(pBattery, OBJ::BATTERY);
}

void CScene_Tutorial02::exit()
{
	g_resultTimer = 0.f;
	g_resultKill = 0;
	g_resultBullet = 0;
	SETSCANTIMER(0.f);
	SETBULLET(0);
	
	vector<CObject*>* pVec = getVecArr();

	for (int i = 0; i < (int)OBJ::SIZE; i++)
	{
		for (int j = 0; j < pVec[i].size(); j++)
			delete pVec[i][j];

		while (pVec[i].size() > 0)
			pVec[i].pop_back();
	}
}
