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
	m_ucColorR = 0;
	m_ucColorG = 0;
	m_ucColorB = 0;
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
	m_ucColorR++;
	m_ucColorG++;
	m_ucColorB++;
}

// FPS 도둑...
void CScene_Title::render(HDC hDC)
{
	LPCWSTR strTitle1 = L"AMaDo";
	LPCWSTR strTitle2 = L"Game";

	HFONT hFont = CreateFont(230, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Comic Sans MS"));
	HFONT hOriginFont = (HFONT)SelectObject(hDC, hFont);

	SetTextColor(hDC, RGB(m_ucColorR, m_ucColorG, m_ucColorB));
	SetBkMode(hDC, TRANSPARENT);

	TextOutW(hDC, 150, 70, strTitle1, wcslen(strTitle1));
	TextOutW(hDC, 700, 220, strTitle2, wcslen(strTitle2));

	SelectObject(hDC, hOriginFont);
	DeleteObject(hFont);

	if (m_isChange)
	{
		hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Comic Sans MS"));
		hOriginFont = (HFONT)SelectObject(hDC, hFont);
		SetTextColor(hDC, WHITE);

		LPCWSTR strMessage = L"Press \'Space\' to Play";
		TextOutW(hDC, WINSIZEX / 2 - 115, WINSIZEY / 2 + 150, strMessage, wcslen(strMessage));

		SelectObject(hDC, hOriginFont);
		DeleteObject(hFont);
	}
}

void CScene_Title::enter()
{
	do
	{
		m_ucColorR = rand() % 256;
		m_ucColorG = rand() % 256;
		m_ucColorB = rand() % 256;
	} while (m_ucColorR == m_ucColorG == m_ucColorB);
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