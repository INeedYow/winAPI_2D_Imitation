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

// TODO : enemy�� ���̷� �����ϰ� �ٲ��� ��
	// �߰� ���� : ���̰� �÷��̾���� �����ʵ��� �ϰ�
		// Ʃ�� 2���������� ĳ���� �̵��ؼ� �Ѿ� �ݰ� �������� ��� ������ ����
void CScene_Tutorial01::enter()
{
	CDummyPlayer01* pDumPlayer = new CDummyPlayer01();
	CText* pText1 = new CText(fPoint(590.f, 230.f), L"Ʃ�丮�� 1 / 3", 22);
	CText* pText2 = new CText(fPoint(540.f, 270.f), L"\'Space bar\'�� ����������", 24);
	CText* pText3 = new CText(fPoint(560.f, 145.f), L"��ŵ�Ϸ��� \'D\'�� ��������", 20);
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
