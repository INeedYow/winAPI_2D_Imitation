#include "framework.h"
#include "CObject.h"
#include "CCollider.h"

CObject::CObject()
{
	m_fptPos = { 0.f, 0.f };
	m_fptSize = { 0.f, 0.f };
	m_pCollider = nullptr;
}

CObject::~CObject()
{
	if (nullptr != m_pCollider)
		delete m_pCollider;
}

void CObject::setPos(fPoint pos)
{
	m_fptPos = pos;
}

void CObject::setSize(fPoint size)
{
	m_fptSize = size;
}

fPoint CObject::getPos()
{
	return m_fptPos;
}

fPoint CObject::getSize()
{
	return m_fptSize;
}

void CObject::finalUpdate()
{
	if (nullptr != m_pCollider)
		m_pCollider->finalUpdate();
}

void CObject::render(HDC hDC)
{
}

CCollider* CObject::getCollider()
{
	return m_pCollider;
}

void CObject::createCollider()
{
	m_pCollider = new CCollider();
	m_pCollider->pOwner = this;				// Collider의 friend 선언 필요
}
