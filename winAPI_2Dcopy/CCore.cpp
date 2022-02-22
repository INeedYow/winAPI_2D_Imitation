#include "framework.h"
#include "CCore.h"

// 임시 테스트용
CObject obj;

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

	fPoint objPos = obj.getPos();
	fPoint objSize = obj.getSize();

	if (KEY(VK_UP))
	{
		objPos.y -= 333 * DT;
	}
	if (KEY(VK_DOWN))
	{
		objPos.y += 333 * DT;
	}
	if (KEY(VK_LEFT))
	{
		objPos.x -= 333 * DT;
	}
	if (KEY(VK_RIGHT))
	{
		objPos.x += 333 * DT;
	}

	if (KEYON('A'))
	{
		objSize.x -= 2;
	}
	if (KEYON('D'))
	{
		objSize.x += 2;
	}
	if (KEYON('W'))
	{
		objSize.y += 2;
	}
	if (KEYON('S'))
	{
		objSize.y -= 2;
	}

	if (KEYOFF('Q'))
	{
		objSize.x = 36;
		objSize.y = 36;
	}

	obj.setPos(objPos);
	obj.setSize(objSize);
}

// 게임 전체 그리기 진행
void CCore::render()												
{
	 //메모리 DC 전체를 덮어 버리기(리셋)
	Rectangle(m_hMemDC, -1, -1, WINSIZEX + 1, WINSIZEY + 1);

	HPEN hPen = CreatePen(PS_SOLID, 6, RGB(100, 255, 100));
	HBRUSH hBrush = CreateSolidBrush(RGB(175, 255, 150));

	HPEN hOldPen = (HPEN)SelectObject(m_hMemDC, hPen);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(m_hMemDC, hBrush);


	Rectangle(m_hMemDC,
		obj.getPos().x - obj.getSize().x / 2,
		obj.getPos().y - obj.getSize().y / 2, 
		obj.getPos().x + obj.getSize().x / 2, 
		obj.getPos().y + obj.getSize().y / 2);


	SelectObject(m_hMemDC, hOldPen);
	SelectObject(m_hMemDC, hOldBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);

	// FPS 출력하기
	WCHAR strFPS[6];
	swprintf_s(strFPS, L"%5d", CTimeManager::getInst()->getFPS());
	TextOutW(m_hMemDC, WINSIZEX - 50, 20, strFPS, 5);

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

	m_hDC = GetDC(hWnd);		// hWnd 전역변수로 선언할 필요성;

	// bitmap 생성과 메모리 DC 생성 및 호환
		// compatible : 호환
	m_hMemDC = CreateCompatibleDC(m_hDC);
	m_hBitMap = CreateCompatibleBitmap(m_hDC, WINSIZEX, WINSIZEY);

	HBITMAP hOldBitMap = (HBITMAP)SelectObject(m_hMemDC, m_hBitMap);
	DeleteObject(hOldBitMap);

	// 임시 테스트용
	obj.setPos(fPoint(640, 360));
	obj.setSize(fPoint(36, 36));
}