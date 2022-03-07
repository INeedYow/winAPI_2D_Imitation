#include "framework.h"
#include "CObject.h"
#include "CCollider.h"
#include "CAnimator.h"

CObject::CObject()
{
	m_fptPos	= {};
	m_fptSize	= {};
	m_pCollider = nullptr;
	m_pAnimator = nullptr;
	m_bDead		= false;
	m_eType		= OBJ::DEFAULT;
}


CObject::CObject(const CObject& other)
{
	m_fptPos	= other.m_fptPos;
	m_fptSize	= other.m_fptSize;
	m_eType		= other.m_eType;
	m_bDead		= false;

	// 컨포넌트 복사생성자 관리 (other에 있는 경우)
	if (nullptr != other.m_pCollider)
	{
		m_pCollider = new CCollider(*other.m_pCollider);
		m_pCollider->m_pOwner = this;
	}
	else
		m_pCollider = nullptr;

	if (nullptr != other.m_pAnimator)
	{
		m_pAnimator = new CAnimator(*other.m_pAnimator);
		m_pAnimator->m_pOwner = this;
	}
	else
		m_pAnimator = nullptr;
}


CObject::~CObject()
{
	if (nullptr != m_pCollider)
		delete m_pCollider;
	if (nullptr != m_pAnimator)
		delete m_pAnimator;
}

void CObject::setPos(fPoint pos)
{
	m_fptPos = pos;
}

void CObject::setSize(fPoint size)
{
	m_fptSize = size;
}

void CObject::setType(OBJ type)
{
	m_eType = type;
}

fPoint CObject::getPos()
{
	return m_fptPos;
}

fPoint CObject::getSize()
{
	return m_fptSize;
}

OBJ CObject::getType()
{
	return m_eType;
}

void CObject::setDead()
{
	m_bDead = true;
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
	componentRender(hDC);
}

void CObject::componentRender(HDC hDC)
{
	if (nullptr != m_pCollider)
		m_pCollider->render(hDC);
	if (nullptr != m_pAnimator)
		m_pAnimator->render(hDC);
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

CAnimator* CObject::getAnimator()
{
	return m_pAnimator;
}

void CObject::createAnimator()
{
	m_pAnimator = new CAnimator();
	m_pAnimator->m_pOwner = this;
}
