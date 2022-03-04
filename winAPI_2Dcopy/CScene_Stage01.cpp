#include "framework.h"
#include "CScene_Stage01.h"
#include "CPlayer.h"

CScene_Stage01::CScene_Stage01()
{
	setName(L"Stage01_Scene");
}

CScene_Stage01::~CScene_Stage01()
{
}

void CScene_Stage01::enter()
{
	// 스코어 초기화
	CPlayer::setCoin(0);
	

	// 각 씬마다 오브젝트끼리 충돌 여부 설정가능
}

void CScene_Stage01::exit()
{
	deleteObjectAll();

	CCollisionManager::getInst()->resetGroup();
}