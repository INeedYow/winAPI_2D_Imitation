#pragma once
#include "CMonster.h"

class CMonster_Turtle : public CMonster
{
	float	m_fSpeed;
	fVec2	m_fvDir;
	int		m_iBottomCnt;
	float	m_fGravity;

	CTexture* m_pTex;
	
public:
	CMonster_Turtle();
	virtual ~CMonster_Turtle();
	virtual CMonster_Turtle* clone();

	void setDir(fVec2 dir);

	virtual void update();
	virtual void render(HDC hDC);

	virtual void collisionEnter(CCollider* pOther);
	virtual void collisionExit(CCollider* pOther);

	void becomeShell();
	void death();
};

