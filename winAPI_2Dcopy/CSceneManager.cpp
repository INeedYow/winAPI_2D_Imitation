#include "framework.h"
#include "CSceneManager.h"
#include "CScene.h"
#include "CScene_Title.h"

CSceneManager::CSceneManager()
{
	for (int i = 0; i < (int)SCENE::SIZE; i++)
		m_pArrScene[i] = nullptr;
	m_pCurScene = nullptr;
}
CSceneManager::~CSceneManager()
{
	for (int i = 0; i < (int)SCENE::SIZE; i++)
	{
		if (nullptr != m_pArrScene[i])
			delete m_pArrScene[i];
	}
}

void CSceneManager::sceneChange(SCENE scene)
{
	m_pCurScene->exit();
	m_pCurScene = m_pArrScene[(int)scene];
	m_pCurScene->enter();
}


void CSceneManager::update()
{
	m_pCurScene->update();
}

void CSceneManager::render(HDC hDC)
{
	m_pCurScene->render(hDC);
}

// �迭�� ���ҿ� �ٷ� �����Ҵ��ϸ� ��
void CSceneManager::init()
{
	m_pArrScene[(int)SCENE::TITLE] = new CScene_Title;

	m_pCurScene = m_pArrScene[(int)SCENE::TITLE];
	m_pCurScene->enter();
}

