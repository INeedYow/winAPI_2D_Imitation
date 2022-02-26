#include "framework.h"
#include "CScene_Title.h"

#include "CEnemy.h"
#include "CPlayer.h"

//class CEnemy;		// 전방선언 해봤는데 new CEnemy;에서 오류 생김

CScene_Title::CScene_Title()
{
	setName(L"Title_Scene");
	m_fCount = 0.f;
	m_isChange = false;
	m_uiColor = 0;
}

CScene_Title::~CScene_Title()
{ 
}

void CScene_Title::update()
{
	if (KEY_ON(VK_SPACE))	// space bar 누르면 씬 넘어가도록
	{
		CSceneManager::getInst()->sceneChange(SCENE::TUTORIAL_01);
	}

	m_fCount += DT;
	if (m_fCount >= 1.f)
	{
		m_isChange = !m_isChange; 
		m_fCount -= 1.f;
	}
	m_uiColor++;
}

void CScene_Title::render(HDC hDC)
{
	LPCWSTR strTitle = L"AMaDo Game";

	HFONT hFont = CreateFont(200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Cascadia Code"));
	HFONT hOriginFont = (HFONT)SelectObject(hDC, hFont);

	SetTextColor(hDC, RGB(m_uiColor, m_uiColor, m_uiColor));
	SetBkMode(hDC, TRANSPARENT);

	TextOutW(hDC, 200, 60, strTitle, wcslen(strTitle));

	SelectObject(hDC, hOriginFont);
	DeleteObject(hFont);

	if (m_isChange)
	{
		SetTextColor(hDC, WHITE);
		LPCWSTR strMessage = L"Press \'Space\' to Play";
		TextOutW(hDC, WINSIZEX / 2 - 100, WINSIZEY / 2 + 100, strMessage, wcslen(strMessage));
	}
}

void CScene_Title::enter()
{
}

void CScene_Title::exit()
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