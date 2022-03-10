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
{	// 이벤트 종류에 따라 처리 ( Param 형변환 주의, Param들 내용 주석으로 남길 것)
	switch (_event.eEvent)
	{
	case EVENT::CREATEOBJ:		// 현재 씬에 오브젝트 타입에 맞게 추가해주면 될 듯
		// lParam : obj ptr
		// wParam : obj eGroup (GROUP_OBJECT) / (OBJ)
	{
		CObject* pObj = (CObject*)_event.lParam;
		OBJ eGroup = (OBJ)_event.wParam;

		CSceneManager::getInst()->getCurScene()->addObject(pObj, eGroup);
	}
		break;

	case EVENT::DELETEOBJ:		// 바로 지우면 충돌 해제 등의 처리가 이루어지지 않음 -> 1프레임 유예함
		// lParam : obj ptr
			// obj를 삭제 대기열 벡터에 추가
			// 지우는 작업은 다음 프레임 update에서
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

// 불꽃으로 몬스터 맞추다보면 오류
// delete vecDead[i]에서 nullptr 오류 뜨는데
// 불꽃 하나가 동시에 둘 이상의 몬스터와 충돌해서 vecDead에 두 번 추가돼서 그런듯
// 해결 방법은?
// isDead는 어차피 그 프레임 끝나야 적용되니까 안 되고
// bool이나 비트연산으로 충돌처리 최초 1회만 적용되게 해야겠는데
	// -> 해결 된 듯?
void CEventManager::update()
{	
	// 전 프레임 집행유예 처리 (순서 주의)
	for (int i = 0; i < m_vecDead.size(); i++)
	{
		if (m_vecDead.size() > 20)
		{
			int a = 0;
		}
		delete m_vecDead[i];
	}
	
	m_vecDead.clear();

	// 전 프레임동안 추가된 이벤트들 처리
	for (int i = 0; i < m_vecEvent.size(); i++)
		execute(m_vecEvent[i]);

	m_vecEvent.clear();
}

void CEventManager::eventCreateObject(CObject* pObj, OBJ eGroup)
{
	tEvent newEvent = {};
	newEvent.eEvent = EVENT::CREATEOBJ;
	newEvent.lParam = (DWORD_PTR)pObj;				// 형변환
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
