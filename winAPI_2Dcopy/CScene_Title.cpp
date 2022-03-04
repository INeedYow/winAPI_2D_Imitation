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
	{	// 이벤트매니저로 씬 전환구현할 때까지 stage01로 바로 넘어가도록
		CSceneManager::getInst()->sceneChange(SCENE::STAGE_01);
	}

	m_fCount += fDT;
	if (m_fCount >= 1.f)
	{
		m_isChange = !m_isChange; 
		m_fCount -= 1.f;
	}
	m_ucColorR++;
	m_ucColorG++;
	m_ucColorB++;
}

void CScene_Title::render(HDC hDC)
{
	LPCWSTR strTitle1 = L"AMaDo";
	LPCWSTR strTitle2 = L"Game";

	HFONT hFont = CreateFont(230, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Comic Sans MS"));
	HFONT hOriginFont = (HFONT)SelectObject(hDC, hFont);

	SetTextColor(hDC, RGB(m_ucColorR, m_ucColorG, m_ucColorB));
	SetBkMode(hDC, TRANSPARENT);

	TextOutW(hDC, 150, 70, strTitle1, (int)wcslen(strTitle1));
	TextOutW(hDC, 700, 220, strTitle2, (int)wcslen(strTitle2));

	SelectObject(hDC, hOriginFont);
	DeleteObject(hFont);

	if (m_isChange)
	{
		hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Comic Sans MS"));
		hOriginFont = (HFONT)SelectObject(hDC, hFont);
		SetTextColor(hDC, RGB(255,255,255));

		LPCWSTR strMessage = L"Press \'Space\' to Play";
		TextOutW(hDC, (int)WINSIZEX / 2 - 115, (int)WINSIZEY / 2 + 150, strMessage, (int)wcslen(strMessage));

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

}