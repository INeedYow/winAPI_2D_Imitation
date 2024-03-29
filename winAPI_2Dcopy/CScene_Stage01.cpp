#include "framework.h"
#include "CScene_Stage01.h"
#include "CPlayer.h"
#include "CTile.h"
#include "CBlock.h"
#include "CItem_Coin.h"
#include "CItem_Mushroom.h"
#include "CItem_Flower.h"
#include "CItem_Star.h"
#include "CMonster_Turtle.h"

#include "CDanceMario.h"

#include "SelectGDI.h"

CScene_Stage01::CScene_Stage01()
{
	setName(L"Stage01_Scene");
	m_fTimer = 0.f;
	// 임시
	m_szText = L"마리오 변경(P) 자살(R) 발사(A)";
}

CScene_Stage01::~CScene_Stage01()
{
}

void CScene_Stage01::update()
{
	CScene::update();

	if (KEY_ON(VK_ESCAPE))
		changeScn(SCENE::TITLE);

	m_fTimer += fDT;

	if (m_fTimer > 1.4f)
	{
		switch (int a = rand() % 20)
		{
		case 0:
		case 1:
		{			
			CItem_Mushroom* pItMush = new CItem_Mushroom();
			pItMush->setPos(fPoint((float)(a = rand() % 2 ? 1400 : 1600), 200.f));
			pItMush->setDir(fVec2((float)(a = rand() % 2 ? 1 : -1), 0.f));
			createObj(pItMush, OBJ::ITEM);
			break;
		}
		case 3:
		case 4:
		case 5:
		case 6:
		case 10:
		case 11:
		{
			CMonster_Turtle* pMsTurtle = new CMonster_Turtle();
			pMsTurtle->setPos(fPoint((float)(a = rand() % 2 ? 1400 : 1600), 200.f));
			pMsTurtle->setDir(fVec2((float)(a = rand() % 2 ? 1 : -1), 0.f));
			createObj(pMsTurtle, OBJ::MONSTER);

			CMonster_Turtle* pMsTurtle2 = new CMonster_Turtle();
			pMsTurtle2->setPos(fPoint((float)(a = rand() % 2 ? 1400 : 1600), 200.f));
			pMsTurtle2->setDir(fVec2((float)(a = rand() % 2 ? 1 : -1), 0.f));
			createObj(pMsTurtle2, OBJ::MONSTER);

			//CMonster_Turtle* pMsTurtle3 = new CMonster_Turtle();
			//pMsTurtle3->setPos(fPoint((float)(a = rand() % 2 ? 1400 : 1600), 200.f));
			//pMsTurtle3->setDir(fVec2((float)(a = rand() % 2 ? 1 : -1), 0.f));
			//createObj(pMsTurtle3, OBJ::MONSTER);

			break;
		}
		case 7:
		{
			CItem_Coin* pCoin = new CItem_Coin();
			pCoin->setPos(fPoint((float)(a = rand() % 2 ? 1450 : 1750), (float)(WINSIZEY - T_SIZE / 2 - T_SIZE - IT_SIZE * 3)));
			createObj(pCoin, OBJ::ITEM);
			break;
		}
		case 8:
		{
		/*	CItem_Star * pStar = new CItem_Star();
			pStar->setPos(fPoint((float)(a = rand() % 2 ? 1400 : 1600), 200.f));
			pStar->setDir(fVec2((float)(a = rand() % 2 ? 1 : -1), 0.f));
			createObj(pStar, OBJ::ITEM);
			break;*/
		}
		case 19:
		{
			CItem_Flower* pFlower = new CItem_Flower();
			pFlower->setPos(fPoint((float)(a = rand() % 2 ? 1400 : 1700), (float)(WINSIZEY - T_SIZE / 2 - T_SIZE - IT_SIZE - 6)));
			createObj(pFlower, OBJ::ITEM);
			break;
		}
		
		}

		m_fTimer = 0.f;
	}
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
		CBlock* pBlock = new CBlock();
		pBlock->setPos(fPoint((float)(T_SIZE / 2 + i * T_SIZE), (float)(WINSIZEY - T_SIZE / 2)));
		addObject(pBlock, OBJ::BLOCK);
	}

	CBlock* pBlock2 = new CBlock();
	pBlock2->setPos(fPoint((float)(700.f), (float)(WINSIZEY - T_SIZE / 2 - T_SIZE)));
	addObject(pBlock2, OBJ::BLOCK);

	addObject(pPlayer, OBJ::PLAYER);
	

	CItem_Coin* pCoin = new CItem_Coin();
	pCoin->setPos(fPoint(-50.f, 650.f));
	addObject(pCoin, OBJ::ITEM);

	for (int i = 0; i < 8; i++)
	{
		pCoin = new CItem_Coin();
		pCoin->setPos(fPoint(300.f + 50.f * i, 570.f));
		addObject(pCoin, OBJ::ITEM);
	}

	CItem_Mushroom* pItemMush = new CItem_Mushroom();
	pItemMush->setPos(fPoint(420.f, 650.f));
	pItemMush->setDir(fVec2(1.f, 0.f));
	addObject(pItemMush, OBJ::ITEM);

	for (int i = 0; i < 8; i++)
	{
		pCoin = new CItem_Coin();
		pCoin->setPos(fPoint(700.f + 50.f * i, 540.f));
		addObject(pCoin, OBJ::ITEM);
	}

	for (int i = 0; i < 20; i++)
	{
		CBlock* pBlock = new CBlock();
		pBlock->setPos(fPoint(1100.f + (float)(T_SIZE / 2 + i * T_SIZE), (float)(WINSIZEY - T_SIZE / 2)));
		addObject(pBlock, OBJ::BLOCK);
	}

	for (int i = 0; i < 4; i++)
	{
		CBlock* pBlock = new CBlock();
		pBlock->setPos(fPoint((float)(1100.f) + (i * 6 * T_SIZE), (float)(WINSIZEY - T_SIZE / 2 - T_SIZE)));
		addObject(pBlock, OBJ::BLOCK);
	}
	for (int i = 0; i < 3; i++)
	{
		CBlock* pBlock = new CBlock();
		pBlock->setPos(fPoint((float)(1300.f) + (i * 5 * T_SIZE), (float)(WINSIZEY - T_SIZE / 2 - 3 * T_SIZE)));
		addObject(pBlock, OBJ::BLOCK);
	}
	for (int i = 0; i < 2; i++)
	{
		CBlock* pBlock = new CBlock();
		pBlock->setPos(fPoint(1400.f + 200 * i, (float)(WINSIZEY / 2.f) - 50));
		addObject(pBlock, OBJ::BLOCK);
	}
	
	






	// 각 씬마다 오브젝트끼리 충돌 여부 설정가능
	CCollisionManager::getInst()->checkGroup(OBJ::PLAYER, OBJ::TILE);
	CCollisionManager::getInst()->checkGroup(OBJ::PLAYER, OBJ::ITEM);
	CCollisionManager::getInst()->checkGroup(OBJ::PLAYER, OBJ::BLOCK);
	CCollisionManager::getInst()->checkGroup(OBJ::PLAYER, OBJ::MONSTER);

	CCollisionManager::getInst()->checkGroup(OBJ::MONSTER, OBJ::SHELL);
	CCollisionManager::getInst()->checkGroup(OBJ::MONSTER, OBJ::TILE);
	CCollisionManager::getInst()->checkGroup(OBJ::MONSTER, OBJ::BLOCK);

	CCollisionManager::getInst()->checkGroup(OBJ::FIREBALL, OBJ::MONSTER);
	CCollisionManager::getInst()->checkGroup(OBJ::FIREBALL, OBJ::TILE);
	CCollisionManager::getInst()->checkGroup(OBJ::FIREBALL, OBJ::BLOCK);

	CCollisionManager::getInst()->checkGroup(OBJ::ITEM, OBJ::TILE);
	CCollisionManager::getInst()->checkGroup(OBJ::ITEM, OBJ::BLOCK);

	CCollisionManager::getInst()->checkGroup(OBJ::SHELL, OBJ::TILE);
	CCollisionManager::getInst()->checkGroup(OBJ::SHELL, OBJ::BLOCK);

	setFocus(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
	//setTrace(pPlayer);
}

void CScene_Stage01::exit()
{
	deleteObjectAll();

	CCollisionManager::getInst()->resetGroup();
}