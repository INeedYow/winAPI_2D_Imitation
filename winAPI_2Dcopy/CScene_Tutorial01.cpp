#include "framework.h"
#include "CScene_Tutorial01.h"
#include "CPlayer.h"
#include "CTarget.h"
#include "CText.h"

CScene_Tutorial01::CScene_Tutorial01()
{
	setName(L"Tutorial01_Scene");
}

CScene_Tutorial01::~CScene_Tutorial01()
{
}


// 튜토리얼용 더미 오브젝트를 만들어서 쓰기?


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
