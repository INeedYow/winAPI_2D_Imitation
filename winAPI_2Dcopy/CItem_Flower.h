#pragma once
#include "CItem.h"

class CItem_Flower : public CItem
{

	CTexture*	m_pTex;

public:
	CItem_Flower();
	virtual ~CItem_Flower();

	virtual void update();
	virtual void render(HDC hDC);

	virtual void collisionEnter(CCollider* pOther);
};

