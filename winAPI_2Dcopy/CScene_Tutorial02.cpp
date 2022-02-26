#include "framework.h"
#include "CScene_Tutorial02.h"
#include "CText.h"
#include "CDummyPlayer02.h"

CScene_Tutorial02::CScene_Tutorial02()
{
	setName(L"Tutorial02_Scene");
}

CScene_Tutorial02::~CScene_Tutorial02()
{
}

// 더미 1,2 모두 더미 배열에
void CScene_Tutorial02::enter()
{
	// TODO : 구현
	CDummyPlayer02* pDumPlayer = new CDummyPlayer02();
	CText* pText1 = new CText(fPoint(590.f, 230.f), L"튜토리얼 2 / 2", 22);
	CText* pText2 = new CText(fPoint(560.f, 145.f), L"스킵하려면 \'D\'를 누르세요", 20);

	addObject(pDumPlayer, OBJ::DUMMYPLAYER);
	addObject(pText1, OBJ::TEXT);
	addObject(pText2, OBJ::TEXT);
}

void CScene_Tutorial02::exit()
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
