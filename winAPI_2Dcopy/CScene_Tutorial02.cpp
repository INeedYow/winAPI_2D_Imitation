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

// ���� 1,2 ��� ���� �迭��
/////////////////////////////////////////////////////////////////////////////////////////
// ���� Ʃ�丮�󿡼� ���� ���ٰ� stage�� ���� �ƹ��͵� ��� �ȵǴ� ���װ� �ִµ� ������ �𸣰���
////////////////////////////////////////////////////////////////////////////////////////
void CScene_Tutorial02::enter()
{


	CDummyPlayer02* pDumPlayer = new CDummyPlayer02();
	CText* pText1 = new CText(fPoint(590.f, 230.f), L"Ʃ�丮�� 2 / 2", 22);
	CText* pText2 = new CText(fPoint(560.f, 145.f), L"��ŵ�ϰ� ���ӽ��� : \'D\'", 20);
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
