#include "framework.h"
#include "CCameraManager.h"
#include "CObject.h"

CCameraManager::CCameraManager()
{
	m_fpFocus		= {};
	m_fpPrevFocus	= {};
	m_pTraceObj		= nullptr;
	m_fpDiff		= {};
}

CCameraManager::~CCameraManager()
{

}

// 
void CCameraManager::update()
{
	if (m_pTraceObj)				// ���� ���� ��
	{
		if (m_pTraceObj->isDead())		// ���� �� ����ó��
			m_pTraceObj = nullptr;
		else
			setFocus(m_pTraceObj->getPos());
	}

	calculateDiff();
}

void CCameraManager::setFocusOn(fPoint focus)
{
	m_fpFocus = focus;
}

void CCameraManager::setTraceObj(CObject* targetObj)
{
	m_pTraceObj = targetObj;
}

fPoint CCameraManager::getRenderPos(fPoint pos)
{
	return pos - m_fpDiff;
}

void CCameraManager::calculateDiff()
{
	fPoint fpCenter = fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f);
	m_fpDiff = m_fpFocus - fpCenter;
}
