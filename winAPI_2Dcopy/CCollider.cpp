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
	m_eShape	= SHAPE::POINT;

	m_uiID		= s_uiID++;
}

// ���� ������
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
	return m_uiID;
}

void CCollider::finalUpdate()
{
	m_fpPos = m_pOwner->getPos() + m_fpOffset;
	m_fpSize = m_pOwner->getSize();
}

void CCollider::render(HDC hDC)
{
	fPoint fpRendPos = getRendPos(m_fpPos);

	SelectGDI pen(hDC, PEN::COLLIDER1, PEN::COLLIDER0, m_uiCollCnt);
	SelectGDI brush(hDC, BRUSH::HOLLOW);

	switch (m_eShape)
	{
	case SHAPE::CIRCLE:
		Ellipse(hDC,
			(int)(fpRendPos.x - m_fpSize.x / 2.f),
			(int)(fpRendPos.y - m_fpSize.y / 2.f),
			(int)(fpRendPos.x + m_fpSize.x / 2.f),
			(int)(fpRendPos.y + m_fpSize.y / 2.f));
		break;
	case SHAPE::RECT:
		Rectangle(hDC,
			(int)(fpRendPos.x - m_fpSize.x / 2.f),
			(int)(fpRendPos.y - m_fpSize.y / 2.f),
			(int)(fpRendPos.x + m_fpSize.x / 2.f),
			(int)(fpRendPos.y + m_fpSize.y / 2.f));
		break;
	}

	WCHAR szBuffer[255] = {};
	swprintf_s(szBuffer, L"%d", m_uiCollCnt);
	TextOutW(hDC, (int)fpRendPos.x, (int)fpRendPos.y, szBuffer, (int)wcslen(szBuffer));

}

void CCollider::collisionKeep(CCollider* pOther)
{
	m_pOwner->collisionKeep(pOther);
}

void CCollider::collisionEnter(CCollider* pOther)
{
	m_pOwner->collisionEnter(pOther);
	m_uiCollCnt++;
}

void CCollider::collisionExit(CCollider* pOther)
{
	m_pOwner->collisionExit(pOther);
	m_uiCollCnt--;
}
