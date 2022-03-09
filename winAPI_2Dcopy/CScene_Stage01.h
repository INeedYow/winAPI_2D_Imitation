#pragma once
#include "CScene.h"
class CScene_Stage01 :public CScene
{
	LPCWSTR		m_szText;
	float		m_fTimer;

public:
	CScene_Stage01();
	virtual ~CScene_Stage01();
	
	virtual void update();
	virtual void render(HDC hDC);

	virtual void enter();
	virtual void exit();
};