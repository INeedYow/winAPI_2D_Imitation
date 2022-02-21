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

	fPoint objPos = obj.getPos();

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		objPos.y -= 150 * DT;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		objPos.y += 150 * DT;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		objPos.x -= 150 * DT;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		objPos.x += 150 * DT;
	}

	obj.setPos(objPos);
}

// 게임 전체 그리기 진행
void CCore::render()												
{
	 //메모리 DC 전체를 덮어 버리기(리셋)
	Rectangle(m_hMemDC, -1, -1, WINSIZEX + 1, WINSIZEY + 1);		////// Q. 왜 이렇게 깜빡거리지?

	//HPEN hPen = CreatePen(PS_SOLID, 10, RGB(255, 255, 0));
	//HBRUSH hBrush = CreateSolidBrush(RGB(0, 250, 0));				////// Q. 왜 색이 아니라 무늬가 나오지?

	//HPEN hOldPen = (HPEN)SelectObject(m_hMemDC, hPen);
	//HBRUSH hOldBrush = (HBRUSH)SelectObject(m_hMemDC, hBrush);


	Rectangle(m_hDC,
		obj.getPos().x - obj.getSize().x / 2,
		obj.getPos().y - obj.getSize().y / 2, 
		obj.getPos().x + obj.getSize().x / 2, 
		obj.getPos().y + obj.getSize().y / 2);


	//SelectObject(m_hMemDC, hOldPen);
	//SelectObject(m_hMemDC, hOldBrush);
	//DeleteObject(hPen);
	//DeleteObject(hBrush);

	// 메모리 DC에서 원래 DC로 옮겨오는 함수
	BitBlt(m_hDC, 0, 0, WINSIZEX, WINSIZEY, m_hMemDC, 0, 0, SRCCOPY);
}

// render() 위해서 DC받아와야
// 더블 버퍼링 위해서 bitmap 생성과 해당 메모리 DC필요
	// 이중 버퍼링 구현 미흡
void CCore::init()
{
	CTimeManager::getInst()->init();

	m_hDC = GetDC(hWnd);		// hWnd 전역변수로 선언할 필요성;

	// bitmap 생성과 메모리 DC 생성 및 호환
		// compatible : 호환
	m_hMemDC = CreateCompatibleDC(m_hDC);
	m_hBitMap = CreateCompatibleBitmap(m_hDC, WINSIZEX, WINSIZEY);

	HBITMAP hOldBitMap = (HBITMAP)SelectObject(m_hMemDC, m_hBitMap);
	DeleteObject(hOldBitMap);

	// 임시 테스트용
	obj.setPos(fPoint(100, 100));
	obj.setSize(fPoint(100, 100));
}