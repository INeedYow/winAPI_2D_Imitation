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
//	// Ʃ�丮�� ĳ���Ͱ� ��ǥ �� �ϳ��� �����ϸ� Ʃ�� 2�������� �� ��ȯ
//}

// Ʃ�丮��� ���� ������Ʈ�� ���� ����?

// �ڽ��� render�� �������ϴϱ� �θ��� render�� �� �ż� ������ ������ �� ��
// text�� �������� �߰��ϰ� �����ǰ� �ϸ� �� ��

void CScene_Tutorial01::enter()
{
	CPlayer* pPlayer = new CPlayer();
	CTarget* pTargetL = new CTarget(fPoint(150.f, 360.f));
	CTarget* pTargetR = new CTarget(fPoint(1130.f, 360.f));
	CText* pText1 = new CText(fPoint(510, 130), L"����Ű(�� �� �� ��)�� ��������", 28, false);
	CText* pText2 = new CText(fPoint(130, 420), L"��ǥ", 20, false);
	CText* pText3 = new CText(fPoint(1110, 420), L"��ǥ", 20, false);
	CText* pText4 = new CText(fPoint(540, 310), L"��ǥ �� �ϳ��� �̵��ؾ� �ؿ�", 22, true);
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

// enter()���� ��ü�� �����Ҵ��ؼ� ������ �� �����ص� �Ǳ� �ѵ�
// �׳� ������ ��Ģ�� ������ �Ŷ� ���� ��ü�� �������� �ʰ� ��������