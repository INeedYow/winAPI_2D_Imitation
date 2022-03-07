#include "framework.h"
#include "CScene_Stage01.h"
#include "CPlayer.h"
#include "CTile.h"

#include "SelectGDI.h"

CScene_Stage01::CScene_Stage01()
{
	setName(L"Stage01_Scene");
	
	// 임시
	m_szText = L"시점 변경(O) 마리오 변경(P) 리셋(R) 발사(A)";
}

CScene_Stage01::~CScene_Stage01()
{
}

void CScene_Stage01::render(HDC hDC)
{
	CScene::render(hDC);

	SelectGDI font(hDC, FONT::COMIC24);
	fPoint pos = { 400.f, 300.f };
	pos = getRendPos(pos);

	TextOutW(hDC, (int)pos.x, (int)pos.y, m_szText, (int)wcslen(m_szText));
}

void CScene_Stage01::enter()
{
	// 스코어 초기화
	CPlayer::setCoin(0);

	// 오브젝트 생성
	CPlayer* pPlayer = new CPlayer();
	pPlayer->setPos(fPoint(100.f, WINSIZEY - 100.f));

	for (int i = 0; i < 20; i++)
	{
		CTile* pTile1 = new CTile();
		pTile1->setPos(fPoint((float)(T_SIZE / 2 + i * T_SIZE), (float)(WINSIZEY - T_SIZE / 2)));
		addObject(pTile1, OBJ::TILE);
	}
	CTile* pTile2 = new CTile();
	pTile2->setPos(fPoint((float)(700.f), (float)(WINSIZEY - T_SIZE / 2 - T_SIZE)));
	addObject(pTile2, OBJ::TILE);

	addObject(pPlayer, OBJ::PLAYER);
	

	// 각 씬마다 오브젝트끼리 충돌 여부 설정가능
	CCollisionManager::getInst()->checkGroup(OBJ::PLAYER, OBJ::TILE);
	CCollisionManager::getInst()->checkGroup(OBJ::FIREBALL, OBJ::MONSTER);
	CCollisionManager::getInst()->checkGroup(OBJ::FIREBALL, OBJ::TILE);
	CCollisionManager::getInst()->checkGroup(OBJ::FIREBALL, OBJ::BLOCK);

	setFocus(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
	//setTrace(pPlayer);
}

void CScene_Stage01::exit()
{
	deleteObjectAll();

	CCollisionManager::getInst()->resetGroup();
}