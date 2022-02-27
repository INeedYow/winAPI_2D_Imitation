#include "framework.h"
#include "CObject.h"


CObject::CObject()
{
	m_fptPos = { 0.f, 0.f };
	m_fptSize = { 0.f, 0.f };
}

CObject::CObject(fPoint pos, fPoint size)
{
	m_fptPos = pos;
	m_fptSize = size;
}

CObject::~CObject()
{

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

void CObject::render(HDC hDC)
{
}
