#pragma once
#include "CScene.h"
class CScene_Tool :public CScene
{
	HWND	m_hWnd;

public:
	CScene_Tool();
	virtual ~CScene_Tool();

	virtual void update();

	virtual void enter();
	virtual void exit();
};

