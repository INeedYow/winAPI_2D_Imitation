#include "framework.h"
#include "CEventManager.h"
#include "CObject.h"
#include "CScene.h"

CEventManager::CEventManager()
{

}
CEventManager::~CEventManager()
{

}

void CEventManager::execute(const tEvent& _event)
{	// �̺�Ʈ ������ ���� ó�� ( Param ����ȯ ����, Param�� ���� �ּ����� ���� ��)
	switch(_event.eEvent)
	{
	case EVENT::CREATEOBJ:		// ���� ���� ������Ʈ Ÿ�Կ� �°� �߰����ָ� �� ��
		// lParam : obj ptr
		// wParam : obj group (GROUP_OBJECT) / (OBJ)
	{
		CObject* pObj	= (CObject*)_event.lParam;
		OBJ eGroup		= (OBJ)_event.wParam;

		CSceneManager::getInst()->getCurScene()->addObject(pObj, eGroup);
	}
		break;

	case EVENT::DELETEOBJ:		// �ٷ� ����� �浹 ���� ���� ó���� �̷������ ���� -> 1������ ������
		// lParam : obj ptr
			// obj�� ���� ��⿭ ���Ϳ� �߰�
			// ����� �۾��� ���� ������ update����
	{
		CObject* pObj = (CObject*)_event.lParam;
		pObj->setDead();
		m_vecDead.push_back(pObj);
	}
		break;

	case EVENT::SCENECHANGE:
		break;

	}
}

void CEventManager::update()
{	
	// �� ������ �������� ó�� (���� ����)
	for (int i = 0; i < m_vecDead.size(); i++)
		delete m_vecDead[i];
	
	// �� �����ӵ��� �߰��� �̺�Ʈ�� ó��
	for (int i = 0; i < m_vecEvent.size(); i++)
		execute(m_vecEvent[i]);

	m_vecDead.clear();
	m_vecEvent.clear();
}

void CEventManager::eventCreateObject(CObject* pObj, OBJ group)
{
	tEvent newEvent;
	newEvent.eEvent = EVENT::CREATEOBJ;
	newEvent.lParam = (DWORD_PTR)pObj;				// ����ȯ
	newEvent.wParam = (DWORD_PTR)group;

	addEvent(newEvent);
}

void CEventManager::enentDeleteObject(CObject* pObj)
{
	tEvent newEvent;
	newEvent.eEvent = EVENT::DELETEOBJ;
	newEvent.lParam = (DWORD_PTR)pObj;

	addEvent(newEvent);
}

void CEventManager::addEvent(const tEvent& _event)
{
	m_vecEvent.push_back(_event);
}
