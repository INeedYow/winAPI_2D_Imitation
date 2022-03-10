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
	switch (_event.eEvent)
	{
	case EVENT::CREATEOBJ:		// ���� ���� ������Ʈ Ÿ�Կ� �°� �߰����ָ� �� ��
		// lParam : obj ptr
		// wParam : obj eGroup (GROUP_OBJECT) / (OBJ)
	{
		CObject* pObj = (CObject*)_event.lParam;
		OBJ eGroup = (OBJ)_event.wParam;

		CSceneManager::getInst()->getCurScene()->addObject(pObj, eGroup);
	}
		break;

	case EVENT::DELETEOBJ:		// �ٷ� ����� �浹 ���� ���� ó���� �̷������ ���� -> 1������ ������
		// lParam : obj ptr
			// obj�� ���� ��⿭ ���Ϳ� �߰�
			// ����� �۾��� ���� ������ update����
	{
		CObject* pObj = (CObject*)_event.lParam;
		if (pObj->isDead())
			return;
		pObj->setDead();
		m_vecDead.push_back(pObj);
	}
		break;

	case EVENT::SCENECHANGE:
		// lParam : scn eGroup (GROUP_SCENE) / (SCENE)
	{
		CSceneManager::getInst()->sceneChange((SCENE)_event.lParam);
	}
		break;

	}
}

// �Ҳ����� ���� ���ߴٺ��� ����
// delete vecDead[i]���� nullptr ���� �ߴµ�
// �Ҳ� �ϳ��� ���ÿ� �� �̻��� ���Ϳ� �浹�ؼ� vecDead�� �� �� �߰��ż� �׷���
// �ذ� �����?
// isDead�� ������ �� ������ ������ ����Ǵϱ� �� �ǰ�
// bool�̳� ��Ʈ�������� �浹ó�� ���� 1ȸ�� ����ǰ� �ؾ߰ڴµ�
	// -> �ذ� �� ��?
void CEventManager::update()
{	
	// �� ������ �������� ó�� (���� ����)
	for (int i = 0; i < m_vecDead.size(); i++)
	{
		if (m_vecDead.size() > 20)
		{
			int a = 0;
		}
		delete m_vecDead[i];
	}
	
	m_vecDead.clear();

	// �� �����ӵ��� �߰��� �̺�Ʈ�� ó��
	for (int i = 0; i < m_vecEvent.size(); i++)
		execute(m_vecEvent[i]);

	m_vecEvent.clear();
}

void CEventManager::eventCreateObject(CObject* pObj, OBJ eGroup)
{
	tEvent newEvent = {};
	newEvent.eEvent = EVENT::CREATEOBJ;
	newEvent.lParam = (DWORD_PTR)pObj;				// ����ȯ
	newEvent.wParam = (DWORD_PTR)eGroup;

	addEvent(newEvent);
}

void CEventManager::eventDeleteObject(CObject* pObj)
{
	tEvent newEvent = {};
	newEvent.eEvent = EVENT::DELETEOBJ;
	newEvent.lParam = (DWORD_PTR)pObj;

	addEvent(newEvent);
}

void CEventManager::eventChangeScene(SCENE eScn)
{
	tEvent newEvent = {};
	newEvent.eEvent = EVENT::SCENECHANGE;
	newEvent.lParam = (DWORD_PTR)eScn;
	
	addEvent(newEvent);
}

void CEventManager::addEvent(const tEvent& _event)
{
	m_vecEvent.push_back(_event);
}
