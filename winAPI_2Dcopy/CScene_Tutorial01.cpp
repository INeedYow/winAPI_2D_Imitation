#include "framework.h"
#include "CScene_Tutorial01.h"
#include "CPlayer.h"
#include "CDummyPlayer01.h"
#include "CDummyEnemy01.h"
#include "CText.h"

CScene_Tutorial01::CScene_Tutorial01()
{
	setName(L"Tutorial01_Scene");
}

CScene_Tutorial01::~CScene_Tutorial01()
{
}

// TODO : enemy도 더미로 생성하고 바꿔줄 것
	// 추가 예정 : 더미가 플레이어까지 오지않도록 하고
		// 튜토 2페이지에서 캐릭터 이동해서 총알 줍고 더미한테 쏘도록 유도할 생각
void CScene_Tutorial01::enter()
{
	CDummyPlayer01* pDumPlayer = new CDummyPlayer01();
	CText* pText1 = new CText(fPoint(590.f, 230.f), L"튜토리얼 1 / 3", 22);
	CText* pText2 = new CText(fPoint(540.f, 270.f), L"\'Space bar\'를 눌러보세요", 24);
	CText* pText3 = new CText(fPoint(560.f, 145.f), L"스킵하려면 \'D\'를 누르세요", 20);
	CDummyEnemy01* pDumEnemy = new CDummyEnemy01();

	addObject(pDumPlayer, OBJ::DUMMYPLAYER);
	addObject(pText1, OBJ::TEXT);
	addObject(pText2, OBJ::TEXT);
	addObject(pText3, OBJ::TEXT);
	addObject(pDumEnemy, OBJ::DUMMYENEMY);
}


void CScene_Tutorial01::exit()
{
	vector<CObject*>* pVec = getVecArr();

	for (int i = 0; i < (int)OBJ::SIZE; i++)
	{
		if (i == (int)OBJ::DUMMYENEMY) continue;

		for (int j = 0; j < pVec[i].size(); j++)
			delete pVec[i][j];

		while (pVec[i].size() > 0)
			pVec[i].pop_back();
	}
}
