#pragma once

class CScene;

class CSceneManager
{
	SINGLETON(CSceneManager);

private:
	CScene* m_pArrScene[(int)SCENE::SIZE];
	CScene* m_pCurScene;

public:
	void sceneChange(SCENE scene);

	void update();
	void render(HDC hDC);
	void init();

	CScene* getCurScene();
};