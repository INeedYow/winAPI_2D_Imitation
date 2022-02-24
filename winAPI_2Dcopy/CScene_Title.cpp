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

void CScene_Title::update()
{
	if (KEY_ON(VK_SPACE))	// space bar������ stage������ �Ѿ����
	{
		CSceneManager::getInst()->sceneChange(SCENE::STAGE_01);
	}
}

void CScene_Title::render(HDC hDC)
{
	TextOutW(hDC, WINSIZEX / 2 - 150, WINSIZEY / 2 - 50, L"����Ű�� ����, �����̽� Ű�� �߻��մϴ�", 22);
	TextOutW(hDC, WINSIZEX / 2 - 100, WINSIZEY / 2, L"Press \'Space Bar \' to Start", 27);
}

void CScene_Title::enter()
{
}

void CScene_Title::exit()
{
}