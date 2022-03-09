#pragma once
#include "CScene.h"
class CScene_Result :  public CScene
{
	LPCWSTR		m_szText;
	WCHAR		m_wcTry[10];

	int			m_iShakeX;
	int			m_iShakeY;
	UCHAR		m_ucColor;
	bool		m_bFlick;

public :
	CScene_Result();
	virtual ~CScene_Result();

	virtual void update();
	virtual void render(HDC hDC);

	virtual void enter();
	virtual void exit();
};

