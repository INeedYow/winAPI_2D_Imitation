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
{// 둘을 반납하는 함수가 다름	// 해제 함수 미흡..
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
	if (CPlayer::getMode())
	{
		HBRUSH hBrush = CreateSolidBrush(RGB(10, 10, 10));
		HBRUSH hOriginBrush = (HBRUSH)SelectObject(m_hMemDC, hBrush);

		Rectangle(m_hMemDC, -1, -1, WINSIZEX + 1, WINSIZEY + 1);

		SelectObject(m_hMemDC, hOriginBrush);
		DeleteObject(hBrush);
	}
	else
		Rectangle(m_hMemDC, -1, -1, WINSIZEX + 1, WINSIZEY + 1);

	// memDC에 그려야 한다.
	CSceneManager::getInst()->render(m_hMemDC);

	// FPS 출력하기
	//WCHAR strFPS[6];
	wchar_t szBuffer[255] = {};
	swprintf_s(szBuffer, L"[MyGame] FPS : %d", CTimeManager::getInst()->getFPS());
	SetWindowText(hWnd, szBuffer);
	//TextOutW(m_hMemDC, WINSIZEX - 50, 20, strFPS, 5);

	// 메모리 DC에서 원래 DC로 옮겨오는 함수
	BitBlt(m_hDC, 0, 0, WINSIZEX, WINSIZEY, m_hMemDC, 0, 0, SRCCOPY);
}

// render() 위해서 DC받아와야
// 더블 버퍼링 위해서 bitmap 생성과 해당 메모리 DC필요
	// 더블 버퍼링 구현 미흡
void CCore::init()
{
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