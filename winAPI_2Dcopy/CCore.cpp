#include "framework.h"
#include "CCore.h"

CCore::CCore()
{
	m_hDC = 0;
	m_hMemDC = 0;
	m_hBitMap = 0;
}

// DC들 해제해야 함
CCore::~CCore()
{// 둘을 반납하는 함수가 다름
	// 해당 윈도우 DC 핸들 반납
	ReleaseDC(hWnd, m_hDC);
	// 메모리 DC, 비트맵 반납
	DeleteObject(m_hMemDC);
	DeleteObject(m_hBitMap);
}

// 게임 전체 업데이트 진행
void CCore::update()
{
	CTimeManager::getInst()->update();
	CKeyManager::getInst()->update();
	CSceneManager::getInst()->update();
}

// 게임 전체 그리기 진행
void CCore::render()												
{
	 //메모리 DC 전체를 덮어 버리기(리셋)
	Rectangle(m_hMemDC, -1, -1, WINSIZEX + 1, WINSIZEY + 1);

	// memDC에 그려야 한다.
	CSceneManager::getInst()->render(m_hMemDC);

	// FPS 출력하기
	WCHAR strFPS[6];
	swprintf_s(strFPS, L"%5d", CTimeManager::getInst()->getFPS());
	TextOutW(m_hMemDC, WINSIZEX - 50, 20, strFPS, 5);

	// 메모리 DC에서 원래 DC로 옮겨오는 함수
	BitBlt(m_hDC, 0, 0, WINSIZEX, WINSIZEY, m_hMemDC, 0, 0, SRCCOPY);
}

void CCore::init()
{
	CPathManager::getInst()->init();	// scene에서 obj들이 texture 쓰기전에 init 해야 함 (SceneMgr보다 위에)
	CTimeManager::getInst()->init();
	CKeyManager::getInst()->init();
	CSceneManager::getInst()->init();

	m_hDC = GetDC(hWnd);		// hWnd 전역변수로 선언할 필요성;

	// bitmap 생성과 메모리 DC 생성 및 호환
		// compatible : 호환
	m_hMemDC = CreateCompatibleDC(m_hDC);
	m_hBitMap = CreateCompatibleBitmap(m_hDC, WINSIZEX, WINSIZEY);

	HBITMAP hOldBitMap = (HBITMAP)SelectObject(m_hMemDC, m_hBitMap);
	DeleteObject(hOldBitMap);
}

HDC CCore::getMainDC()
{
	return m_hMemDC;
}
