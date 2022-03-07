#pragma once
#include "CScene.h"
class CScene_Stage01 :public CScene
{
	LPCWSTR		m_szText;
public:
	CScene_Stage01();
	virtual ~CScene_Stage01();
	
	virtual void render(HDC hDC);

	virtual void enter();
	virtual void exit();
};