#include "framework.h"
#include "CScene_Result.h"
#include "CPlayer.h"
#include "CDanceMario.h"

#include "SelectGDI.h"

CScene_Result::CScene_Result()
{
	setName(L"Result_Scene");

	m_szText = L"다시하기(R)";
	m_wcTry[0] = {};
	m_iShakeX = 580;
	m_iShakeY = 280;
	m_ucColor = 0;
	m_bFlick = true;

}

CScene_Result::~CScene_Result()
{
}

void CScene_Result::update()
{
	CScene::update();

	if (m_bFlick)
	{
		m_iShakeX = rand() % 7 + 577;
		m_iShakeY = rand() % 7 + 277;

		if (++m_ucColor >= 255)
		{
			m_bFlick = false;
			CPlayer::setTryCnt(CPlayer::getTryCnt() + 1);
			swprintf_s(m_wcTry, L"Try : %d", CPlayer::getTryCnt());
		}
	}
	else
	{
		if (m_ucColor == 0)
		{
			m_iShakeX = 580;
			m_iShakeY = 280;
		}
		if (m_ucColor == 1)
		{
			CDanceMario* cDancer = new CDanceMario();
			createObj(cDancer, OBJ::ETC);
			m_ucColor--;
		}
		if (m_ucColor >= 2)
		{
			m_iShakeX = rand() % 7 + 577;
			m_iShakeY = rand() % 7 + 277;
			m_ucColor--;
		}
		
	}

	if (KEY_ON('R'))
		changeScn(SCENE::STAGE_01);
}

void CScene_Result::render(HDC hDC)
{
	CScene::render(hDC);

	SelectGDI font1(hDC, FONT::COMIC48);

	TextOutW(hDC, 560, 580, m_szText, (int)wcslen(m_szText));

	SelectGDI font2(hDC, FONT::COMIC72);
	SetTextColor(hDC, RGB(m_ucColor, m_ucColor, m_ucColor));

	TextOutW(hDC, m_iShakeX, m_iShakeY, m_wcTry, (int)wcslen(m_wcTry));

	SetTextColor(hDC, RGB(0, 0, 0));
}

void CScene_Result::enter()
{
	swprintf_s(m_wcTry, L"Try : %d", CPlayer::getTryCnt());
}

void CScene_Result::exit()
{
	m_iShakeX = 580;
	m_iShakeY = 280;
	m_ucColor = 0;
	m_bFlick = true;

	deleteObjectAll();

	CCollisionManager::getInst()->resetGroup();
}
