#include "framework.h"
#include "CScene_Stage01.h"


CScene_Stage01::CScene_Stage01()
{
	setName(L"Stage01_Scene");
}

CScene_Stage01::~CScene_Stage01()
{
}

void CScene_Stage01::enter()
{
	// ���ھ� �ʱ�ȭ
	

	// �� ������ ������Ʈ���� �浹 ���� ��������
}

void CScene_Stage01::exit()
{
	deleteObjectAll();

	CCollisionManager::getInst()->resetGroup();
}