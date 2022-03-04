#pragma once
#include "CScene.h"
class CScene_Title : public CScene
{
	LPCWSTR		m_strMsg;
	float		m_fTimer;

public:
	CScene_Title();
	virtual ~CScene_Title();

	virtual void update();
	virtual void render(HDC hDC);

	virtual void enter();
	virtual void exit();

};

