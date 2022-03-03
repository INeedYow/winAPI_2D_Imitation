#include "framework.h"
#include "CCollider.h"

#include "CObject.h"

#include "SelectGDI.h"

CCollider::CCollider()
{
	m_pOwner	= nullptr;
	m_fpPos		= {};
	m_fpSize	= {};
	m_fpOffset	= {};
	m_uiCollCnt = 0;
	m_eShape	= SHAPE::END;

	m_uiID		= s_uiID++;
}

// 복사 생성자
CCollider::CCollider(const CCollider& other)
{
	m_pOwner	= nullptr;
	m_fpPos		= other.m_fpPos;
	m_fpSize	= other.m_fpSize;
	m_fpOffset	= other.m_fpOffset;
	m_uiCollCnt = other.m_uiCollCnt;
	m_eShape	= other.m_eShape;

	m_uiID = s_uiID++;
}

CCollider::~CCollider()
{
	if (nullptr != m_pOwner)
		delete m_pOwner;
}

void CCollider::setPos(fPoint pos)
{
	m_fpPos = pos;
}

void CCollider::setSize(fPoint size)
{
	m_fpSize = size;
}

void CCollider::setOffset(fPoint offset)
{
	m_fpOffset = offset;
}

void CCollider::setShape(SHAPE shape)
{
	m_eShape = shape;
}

fPoint CCollider::getPos()
{
	return m_fpPos;
}

fPoint CCollider::getSize()
{
	return m_fpSize;
}

fPoint CCollider::getOffset()
{
	return m_fpOffset;
}

CObject* CCollider::getOwner()
{
	return m_pOwner;
}

SHAPE CCollider::getShape()
{
	return m_eShape;
}

UINT CCollider::getID()
{
	return 0;
}

void CCollider::finalUpdate()
{
	m_fpPos = m_pOwner->getPos() + m_fpOffset;
}

void CCollider::render(HDC hDC)
{
	
}

void CCollider::collisionKeep(CCollider* pOther)
{
}

void CCollider::collisionEnter(CCollider* pOther)
{
}

void CCollider::collisionExit(CCollider* pOther)
{
}
