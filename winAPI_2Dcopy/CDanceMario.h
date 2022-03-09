#pragma once
#include "CObject.h"
class CDanceMario :  public CObject
{
	float	m_fTimer;
	UCHAR	m_ucStep;

	CTexture* m_pTex;

public:
	CDanceMario();
	virtual ~CDanceMario();

	virtual void update();
	virtual void render(HDC hDC);

	void setRandPos();
	void setRandPlay();
};

