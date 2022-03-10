#pragma once
#include "CObject.h"


class CEffect :  public CObject
{
	float		m_fGravity;
	fVec2		m_fvDir;
	
	CTexture*	 m_pTex;

	void (*vFunc)(OBJNAME, wstring);

public:
	CEffect();
	virtual ~CEffect();

	virtual void update();
	virtual void render(HDC hDC);
};

