#include "framework.h"
#include "CDummyPlayer02.h"

CDummyPlayer02::CDummyPlayer02()
{
}

CDummyPlayer02::~CDummyPlayer02()
{
}

void CDummyPlayer02::update()
{
	if (KEY_OFF('Q'))
		CSceneManager::getInst()->sceneChange(SCENE::TUTORIAL_01);
	if (KEY_OFF('E'))
		CSceneManager::getInst()->sceneChange(SCENE::STAGE_01);




	if (KEY_ON(VK_SPACE))
		isMode = true;
	if (KEY_OFF(VK_SPACE))
		isMode = false;

}

void CDummyPlayer02::render(HDC hDC)
{
}
