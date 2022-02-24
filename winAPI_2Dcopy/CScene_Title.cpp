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
	if (KEY_ON(VK_SPACE))	// space bar ������ �� �Ѿ����
	{
		CSceneManager::getInst()->sceneChange(SCENE::TUTORIAL_01);
	}
}

void CScene_Title::render(HDC hDC)
{
	LPCWSTR strTitle = L"AMaDo Game";
	LPCWSTR strMessage = L"Press \'Space\' to Play";

	HFONT hFont = CreateFont(200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Cascadia Code"));
	HFONT hOriginFont = (HFONT)SelectObject(hDC, hFont);

	TextOutW(hDC, 200, 60, strTitle, wcslen(strTitle));

	SelectObject(hDC, hOriginFont);
	DeleteObject(hFont);

	TextOutW(hDC, WINSIZEX / 2 - 100, WINSIZEY / 2 + 100, strMessage, wcslen(strMessage));

}

void CScene_Title::enter()
{
}

void CScene_Title::exit()
{
}