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

void CScene_Tutorial02::enter()
{
	// TODO : 구현
	CDummyPlayer02* pDumPlayer = new CDummyPlayer02();
	CText* pText1 = new CText(fPoint(470, 350), L"[미구현]\'Q\' : 이전 단계로  \t \'E\' : 다음 단계로", 28);
	addObject(pText1, OBJ::TEXT);
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
