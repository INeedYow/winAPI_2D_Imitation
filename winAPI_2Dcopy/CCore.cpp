#include "framework.h"
#include "CCore.h"

CCore::CCore()
{
	m_hDC			= 0;
	m_hMemDC		= 0;
	m_hBitMap		= 0;
	m_arrBrush[0]	= {};
	m_arrPen[0]		= {};
	m_arrFont[0]	= {};
}

// DC들 해제해야 함
CCore::~CCore()
{// 둘을 반납하는 함수가 다름	// 해제 함수 미흡..
	// 해당 윈도우 DC 핸들 반납
	ReleaseDC(hWnd, m_hDC);
	// 메모리 DC, 비트맵 반납
	DeleteObject(m_hMemDC);
	DeleteObject(m_hBitMap);

	for (int i = 0; i < (int)BRUSH::SIZE; i++)
	{	// hollow는 stock에서 빌려온 거라서 지우면 안 됨
		if ((int)BRUSH::HOLLOW == i) continue;
		DeleteObject(m_arrBrush[i]);
	}
	for (int i = 0; i < (int)PEN::SIZE; i++)
	{
		DeleteObject(m_arrPen[i]);
	}
	for (int i = 0; i < (int)FONT::SIZE; i++)
	{
		DeleteObject(m_arrFont[i]);
	}
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
	HBRUSH hBrush = CreateSolidBrush(ISMODE ? RGB(30,30,30) : RGB(15, 15, 15));
	HBRUSH hOriginBrush = (HBRUSH)SelectObject(m_hMemDC, hBrush);
	
	Rectangle(m_hMemDC, -1, -1, WINSIZEX + 1, WINSIZEY + 1);

	SelectObject(m_hMemDC, hOriginBrush);
	DeleteObject(hBrush);

	// memDC에 그려야 한다.
	CSceneManager::getInst()->render(m_hMemDC);

	// FPS 출력하기
	wchar_t szBuffer[255] = {};
	swprintf_s(szBuffer, L"[MyGame] FPS : %d", CTimeManager::getInst()->getFPS());
	SetWindowText(hWnd, szBuffer);

	// 메모리 DC에서 원래 DC로 옮겨오는 함수
	BitBlt(m_hDC, 0, 0, WINSIZEX, WINSIZEY, m_hMemDC, 0, 0, SRCCOPY);
}

// render() 위해서 DC받아와야
// 더블 버퍼링 위해서 bitmap 생성과 해당 메모리 DC필요
	// 더블 버퍼링 구현 미흡
void CCore::init()
{
	CreateBrushPenFont();

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

void CCore::CreateBrushPenFont()
{
	m_arrBrush[(UINT)TYPE_BRUSH::HOLLOW]		= (HBRUSH)GetStockObject(HOLLOW_BRUSH);	// 이미 자주 쓰는 거 모아놓은 stock이 있음
			
	m_arrBrush[(UINT)TYPE_BRUSH::BLACK15]		= CreateSolidBrush(RGB(15, 15, 15));
	m_arrBrush[(UINT)TYPE_BRUSH::BLACK30]		= CreateSolidBrush(RGB(30, 30, 30));
	m_arrBrush[(UINT)TYPE_BRUSH::WHITE200]		= CreateSolidBrush(RGB(200, 200, 200));
				
	m_arrBrush[(UINT)TYPE_BRUSH::EZ_BRU]		= CreateSolidBrush(RGB(45, 45, 45));
	m_arrBrush[(UINT)TYPE_BRUSH::EZD_BRU]		= CreateSolidBrush(RGB(70, 0, 70));
	m_arrBrush[(UINT)TYPE_BRUSH::EC_BRU]		= CreateSolidBrush(RGB(20, 70, 50));
	m_arrBrush[(UINT)TYPE_BRUSH::EW_BRU]		= CreateSolidBrush(RGB(90, 40, 10));
	m_arrBrush[(UINT)TYPE_BRUSH::P_BRUON]		= CreateSolidBrush(RGB(150, 200, 100));
	m_arrBrush[(UINT)TYPE_BRUSH::P_BRUOFF]		= CreateSolidBrush(RGB(100, 125, 75));
	m_arrBrush[(UINT)TYPE_BRUSH::I_BRUFLICK]	= CreateSolidBrush(RGB(240, 240, 180));
	m_arrBrush[(UINT)TYPE_BRUSH::I_BRUNORMAL]	= CreateSolidBrush(RGB(160, 160, 120));

	m_arrFont[(UINT)TYPE_FONT::COMIC24]			= CreateFont(24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Comic Sans MS"));
	m_arrFont[(UINT)TYPE_FONT::COMIC18]			= CreateFont(18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Comic Sans MS"));

	m_arrPen[(UINT)TYPE_PEN::RED]				= CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)TYPE_PEN::GREEN]				= CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)TYPE_PEN::BLUE]				= CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

	m_arrPen[(UINT)TYPE_PEN::E_EDGE]			= CreatePen(PS_SOLID, 1, RGB(200, 25, 25));
	m_arrPen[(UINT)TYPE_PEN::P_EDGEON]			= CreatePen(PS_SOLID, P_PEN, RGB(125, 150, 100));
	m_arrPen[(UINT)TYPE_PEN::P_EDGEOFF]			= CreatePen(PS_SOLID, P_PEN, RGB(75, 100, 50));
	m_arrPen[(UINT)TYPE_PEN::I_SCAN]			= CreatePen(PS_SOLID, 1, RGB(240, 240, 100));
	m_arrPen[(UINT)TYPE_PEN::I_EDGE]			= CreatePen(PS_SOLID, 1, RGB(75, 100, 50));
	
}

HBRUSH CCore::getBrush(BRUSH type)
{
	return m_arrBrush[(UINT)type];
}

HPEN CCore::getPen(PEN type)
{
	return m_arrPen[(UINT)type];
}

HFONT CCore::getFont(FONT type)
{
	return m_arrFont[(UINT)type];
}
