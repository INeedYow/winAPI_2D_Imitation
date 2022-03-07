#include "framework.h"
#include "CScene_Title.h"

#include "SelectGDI.h"


CScene_Title::CScene_Title()
{
	setName(L"Title_Scene");
	m_strMsg = L"Press \'Space\' to Play";
	m_fTimer = 0.f;
}

CScene_Title::~CScene_Title()
{ 
}

void CScene_Title::update()
{
	m_fTimer += fDT;

	if (KEY_ON(VK_SPACE))
	{
		changeScn(SCENE::STAGE_01);
	}
}

void CScene_Title::render(HDC hDC)
{
	if ((int)m_fTimer % 2) return;

	SelectGDI font(hDC, FONT::COMIC48);

	SetTextColor(hDC, RGB(255, 0, 255));
	SetBkMode(hDC, TRANSPARENT);

	TextOutW(hDC, (int)WINSIZEX / 2 - 115, (int)WINSIZEY / 2 + 150, m_strMsg, (int)wcslen(m_strMsg));
}

void CScene_Title::enter()
{

}

void CScene_Title::exit()
{
	m_fTimer = 0.f;
}