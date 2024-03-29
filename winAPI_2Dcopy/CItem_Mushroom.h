#pragma once
#include "CItem.h"

class CItem_Mushroom : public CItem
{
	float	m_fSpeed;
	fVec2	m_fvDir;
	int		m_iBottomCnt;
	float	m_fGravity;
	bool	m_bAir;

	CTexture* m_pTex;

public:
	CItem_Mushroom();
	virtual ~CItem_Mushroom();

	void setDir(fVec2 dir);

	virtual void update();
	virtual void render(HDC hDC);

	virtual void collisionEnter(CCollider* pOther);
	virtual void collisionExit(CCollider* pOther);
};

