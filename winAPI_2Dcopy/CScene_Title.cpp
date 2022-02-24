#include "framework.h"
#include "CScene_Title.h"

#include "CEnemy.h"
#include "CPlayer.h"
//class CEnemy;		// ���漱�� �غôµ� new CEnemy;���� ���� ����

CScene_Title::CScene_Title()
{
	setName(L"Title_Scene");
}

CScene_Title::~CScene_Title()
{
}

void CScene_Title::enter()
{
	CEnemy* pEnemy = new CEnemy();
	CPlayer* pPlayer = new CPlayer();

	addObject(pEnemy, OBJ::ENEMY);
	addObject(pPlayer, OBJ::PLAYER);
}

void CScene_Title::exit()
{
}