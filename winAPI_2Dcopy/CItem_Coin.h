#pragma once
#include "CItem.h"

class CTexture;

class CItem_Coin : public CItem
{
	CTexture* m_pTex;

public:
	CItem_Coin();
	virtual ~CItem_Coin();

	virtual void update();
	virtual void render(HDC hDC);

	virtual void collisionEnter(CCollider* pOther);
};

