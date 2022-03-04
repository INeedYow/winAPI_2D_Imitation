#include "framework.h"
#include "CKeyManager.h"


CKeyManager::CKeyManager()
{
	for (int key = 0; key < VKEY_SIZE; key++)
	{
		m_arrPrevKey[key] = false;
		m_arrCurKey[key] = false;
	}
}

CKeyManager::~CKeyManager()
{
}

// 포커스 되고 있는 윈도우창이 현재 윈도우 핸들인지 GetFocus()로 비교
void CKeyManager::update()
{
	HWND hNowFocus = GetFocus();
	
	if (hWnd != hNowFocus)						// 다른 윈도우 보고 있으면 키입력 X
	{
		for (int key = 0; key < VKEY_SIZE; key++)
		{
			m_arrPrevKey[key] = m_arrCurKey[key];
			m_arrCurKey[key] = false;
		}
		return;
	}

	for (int key = 0; key < VKEY_SIZE; key++)
	{
		m_arrPrevKey[key] = m_arrCurKey[key];	// 지금 상태는 예전 키 상태로 넣어주고
		
		if (GetAsyncKeyState(key) & 0x8000)
	    	m_arrCurKey[key] = true;
		else
			m_arrCurKey[key] = false;
	}
}

void CKeyManager::init()
{
}

bool CKeyManager::getKeyHold(const int key)
{
	return (true == m_arrPrevKey[key] && true == m_arrCurKey[key]);
}

bool CKeyManager::getKeyOn(const int key)
{
	return (false == m_arrPrevKey[key] && true == m_arrCurKey[key]);
}

bool CKeyManager::getKeyOff(const int key)
{
	return (true == m_arrPrevKey[key] && false == m_arrCurKey[key]);
}

bool CKeyManager::getKeyNone(const int key)
{
	return (false == m_arrPrevKey[key] && false == m_arrCurKey[key]);
}
