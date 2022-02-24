#include "framework.h"
#include "CScene_Tutorial01.h"
#include "CPlayer.h"
#include "CTarget.h"
#include "CText.h"

CScene_Tutorial01::CScene_Tutorial01()
{
	setName(L"Tutorial01_Scene");
	//m_uiPage = 1;
}

CScene_Tutorial01::~CScene_Tutorial01()
{
}
//
//void CScene_Tutorial01::update()
//{
//	if (KEY_OFF(VK_ESCAPE))
//		CSceneManager::getInst()->sceneChange(SCENE::STAGE_01);
//	// 튜토리얼 캐릭터가 목표 중 하나에 도달하면 튜토 2페이지로 씬 전환
//}

// 튜토리얼용 더미 오브젝트를 만들어서 쓰기?

// 자식의 render를 재정의하니까 부모의 render가 안 돼서 옵젝들 렌더가 안 됨
// text도 옵젝으로 추가하고 렌더되게 하면 될 듯

void CScene_Tutorial01::enter()
{
	CPlayer* pPlayer = new CPlayer();
	CTarget* pTargetL = new CTarget(fPoint(150.f, 360.f));
	CTarget* pTargetR = new CTarget(fPoint(1130.f, 360.f));
	CText* pText1 = new CText(fPoint(510, 130), L"방향키(↑ ↓ ← →)로 움직여요", 28, false);
	CText* pText2 = new CText(fPoint(130, 420), L"목표", 20, false);
	CText* pText3 = new CText(fPoint(1110, 420), L"목표", 20, false);
	CText* pText4 = new CText(fPoint(540, 310), L"목표 중 하나로 이동해야 해요", 22, true);
	CText* pText5 = new CText(fPoint(640, 660), L"1 / 3", 13, false);

	addObject(pPlayer, OBJ::PLAYER);
	addObject(pTargetL, OBJ::TARGET);
	addObject(pTargetR, OBJ::TARGET);
	addObject(pText1, OBJ::TEXT);
	addObject(pText2, OBJ::TEXT);
	addObject(pText3, OBJ::TEXT);
	addObject(pText4, OBJ::TEXT);
	addObject(pText5, OBJ::TEXT);
}

void CScene_Tutorial01::exit()
{
}

// enter()에서 객체들 동적할당해서 실제로 룰 설명해도 되긴 한데
// 그냥 정해진 규칙만 설명할 거라서 따로 객체들 생성하지 않고 진행했음