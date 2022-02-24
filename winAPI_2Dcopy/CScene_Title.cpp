#include "framework.h"
#include "CScene_Title.h"

#include "CEnemy.h"
#include "CPlayer.h"

//class CEnemy;		// 전방선언 해봤는데 new CEnemy;에서 오류 생김

CScene_Title::CScene_Title()
{
	setName(L"Title_Scene");
}

CScene_Title::~CScene_Title()
{ 
}

void CScene_Title::update()
{
	if (KEY_ON(VK_SPACE))	// space bar누르면 stage씬으로 넘어가도록
	{
		CSceneManager::getInst()->sceneChange(SCENE::STAGE_01);
	}
}

void CScene_Title::render(HDC hDC)
{
	TextOutW(hDC, WINSIZEX / 2 - 150, WINSIZEY / 2 - 50, L"방향키로 조작, 스페이스 키로 발사합니다", 22);
	TextOutW(hDC, WINSIZEX / 2 - 100, WINSIZEY / 2, L"Press \'Space Bar \' to Start", 27);
}

void CScene_Title::enter()
{
}

void CScene_Title::exit()
{
}