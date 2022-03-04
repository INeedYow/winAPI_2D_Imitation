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

// ��Ŀ�� �ǰ� �ִ� ������â�� ���� ������ �ڵ����� GetFocus()�� ��
void CKeyManager::update()
{
	HWND hNowFocus = GetFocus();
	
	if (hWnd != hNowFocus)						// �ٸ� ������ ���� ������ Ű�Է� X
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
		m_arrPrevKey[key] = m_arrCurKey[key];	// ���� ���´� ���� Ű ���·� �־��ְ�
		
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
