#pragma once
#include "CObject.h"
class CItem : public CObject
{
	
public:
	CItem();
	virtual ~CItem();

	virtual void update() = 0;
	virtual void render(HDC hDC);

	virtual void collisionKeep(CCollider* pOther) {}
	virtual void collisionEnter(CCollider* pOther) {}
	virtual void collisionExit(CCollider* pOther) {}
};

