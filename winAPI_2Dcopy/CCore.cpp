#include "framework.h"
#include "CCore.h"

CCore::CCore()
{
	m_hDC = 0;
	m_hMemDC = 0;
	m_hBitMap = 0;
}

// DC�� �����ؾ� ��
CCore::~CCore()
{// ���� �ݳ��ϴ� �Լ��� �ٸ�
	// �ش� ������ DC �ڵ� �ݳ�
	ReleaseDC(hWnd, m_hDC);
	// �޸� DC, ��Ʈ�� �ݳ�
	DeleteObject(m_hMemDC);
	DeleteObject(m_hBitMap);
}

// ���� ��ü ������Ʈ ����
void CCore::update()
{
	CTimeManager::getInst()->update();
	CKeyManager::getInst()->update();
	CSceneManager::getInst()->update();
}

// ���� ��ü �׸��� ����
void CCore::render()												
{
	 //�޸� DC ��ü�� ���� ������(����)
	Rectangle(m_hMemDC, -1, -1, WINSIZEX + 1, WINSIZEY + 1);

	// memDC�� �׷��� �Ѵ�.
	CSceneManager::getInst()->render(m_hMemDC);

	// FPS ����ϱ�
	WCHAR strFPS[6];
	swprintf_s(strFPS, L"%5d", CTimeManager::getInst()->getFPS());
	TextOutW(m_hMemDC, WINSIZEX - 50, 20, strFPS, 5);

	// �޸� DC���� ���� DC�� �Űܿ��� �Լ�
	BitBlt(m_hDC, 0, 0, WINSIZEX, WINSIZEY, m_hMemDC, 0, 0, SRCCOPY);
}

void CCore::init()
{
	CPathManager::getInst()->init();	// scene���� obj���� texture �������� init �ؾ� �� (SceneMgr���� ����)
	CTimeManager::getInst()->init();
	CKeyManager::getInst()->init();
	CSceneManager::getInst()->init();

	m_hDC = GetDC(hWnd);		// hWnd ���������� ������ �ʿ伺;

	// bitmap ������ �޸� DC ���� �� ȣȯ
		// compatible : ȣȯ
	m_hMemDC = CreateCompatibleDC(m_hDC);
	m_hBitMap = CreateCompatibleBitmap(m_hDC, WINSIZEX, WINSIZEY);

	HBITMAP hOldBitMap = (HBITMAP)SelectObject(m_hMemDC, m_hBitMap);
	DeleteObject(hOldBitMap);
}

HDC CCore::getMainDC()
{
	return m_hMemDC;
}
