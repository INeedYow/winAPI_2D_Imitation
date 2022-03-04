#include "framework.h"
#include "CObject.h"
#include "CCollider.h"

void CObject::setDead()
{
	m_bDead = true;
}

CObject::CObject()
{
	m_bDead = false;
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

bool CObject::isDead()
{
	return m_bDead;
}

void CObject::finalUpdate()
{
	if (nullptr != m_pCollider)
		m_pCollider->finalUpdate();
}

void CObject::render(HDC hDC)
{
}

void CObject::componentRender(HDC hDC)
{
	if (nullptr != m_pCollider)
		m_pCollider->render(hDC);
}

CCollider* CObject::getCollider()
{
	return m_pCollider;
}

void CObject::createCollider()
{
	m_pCollider = new CCollider();
	m_pCollider->m_pOwner = this;				// Collider의 friend 선언 필요
}
