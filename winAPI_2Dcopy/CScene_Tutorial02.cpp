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

// dummy 2는 어떻게 ?
// 더미1,2 모두 더미배열에 같이?
void CScene_Tutorial02::enter()
{
	// TODO : 구현
	CDummyPlayer02* pDumPlayer = new CDummyPlayer02();
	CText* pText1 = new CText(fPoint(470, 350), L"[미구현]\'E\' : 다음 단계로", 28);
	CText* pText2 = new CText(fPoint(590.f, 230.f), L"튜토리얼 2 / 3", 22);
	CText* pText3 = new CText(fPoint(550.f, 150.f), L"스킵하려면 \'D\'를 누르세요", 20);
	
	addObject(pDumPlayer, OBJ::DUMMYPLAYER);
	addObject(pText1, OBJ::TEXT);
	addObject(pText2, OBJ::TEXT);
	addObject(pText3, OBJ::TEXT);
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
