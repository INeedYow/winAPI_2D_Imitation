#pragma once
#include "CObject.h"
class CShell : public CObject
{
	float	m_fSpeed;
	fVec2	m_fvDir;
	float	m_fGravity;
	bool	m_bAir;
	int		m_iBottomCnt;
	float	m_fDuration;

	CTexture* m_pTex;

public:
	CShell();
	virtual ~CShell();

	void setDir(fVec2 dir);

	virtual void update();
	virtual void render(HDC hDC);

	virtual void collisionEnter(CCollider* pOther);
	virtual void collisionExit(CCollider* pOther);
};

