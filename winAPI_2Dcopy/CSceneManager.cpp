#include "framework.h"
#include "CSceneManager.h"
#include "CScene.h"
#include "CScene_Title.h"

CSceneManager::CSceneManager()
{
	
}
CSceneManager::~CSceneManager()
{

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

void CSceneManager::init()
{
	CScene* pScene = new CScene_Title;
}

