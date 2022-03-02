#include "framework.h"
#include "CCollider.h"

#include "CObject.h"

CCollider::CCollider()
{
	pOwner = nullptr;
	fpPos = { 0.f, 0.f };
	fpSize = { 0.f, 0.f };
	fpOffset = { 0.f, 0.f };
}

CCollider::~CCollider()
{
	if (nullptr != pOwner)
		delete pOwner;
}

void CCollider::setPos(fPoint pos)
{
	fpPos = pos;
}

void CCollider::setSize(fPoint size)
{
	fpSize = size;
}

void CCollider::setOffset(fPoint offset)
{
	fpOffset = offset;
}

fPoint CCollider::getPos()
{
	return fpPos;
}

fPoint CCollider::getSize()
{
	return fpSize;
}

fPoint CCollider::getOffset()
{
	return fpOffset;
}

CObject* CCollider::getOwner()
{
	return pOwner;
}

void CCollider::finalUpdate()
{
	fpPos = pOwner->getPos() + fpOffset;
}

void CCollider::render(HDC hDC)
{
}