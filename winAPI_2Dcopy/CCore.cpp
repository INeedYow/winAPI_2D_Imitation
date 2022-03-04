#include "framework.h"
#include "CCore.h"
#include "SelectGDI.h"

CCore::CCore()
{
	m_hDC			= 0;
	m_hMemDC		= 0;
	m_hBitMap		= 0;
	m_arrBrush[0]	= {};
	m_arrPen[0]		= {};
	m_arrFont[0]	= {};
}

// DC�� �����ؾ� ��
CCore::~CCore()
{// ���� �ݳ��ϴ� �Լ��� �ٸ�
	// �ش� ������ DC �ڵ� �ݳ�
	ReleaseDC(hWnd, m_hDC);
	// �޸� DC, ��Ʈ�� �ݳ�
	DeleteObject(m_hMemDC);
	DeleteObject(m_hBitMap);

	for (int i = 0; i < (int)BRUSH::SIZE; i++)
	{	// hollow�� stock���� ������ �Ŷ� ����� �� ��
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

void CCore::update()
{	
	// ����ȭ
	CEventManager::getInst()->update();
	CTimeManager::getInst()->update();
	CKeyManager::getInst()->update();

	CSceneManager::getInst()->update();
	CCollisionManager::getInst()->update();
}

void CCore::render()												
{
	Rectangle(m_hMemDC, -1, -1, WINSIZEX + 1, WINSIZEY + 1);

	CSceneManager::getInst()->render(m_hMemDC);

	// FPS ����ϱ�
	wchar_t szBuffer[255] = {};
	swprintf_s(szBuffer, L"[Flatform Imitation] FPS : %d", CTimeManager::getInst()->getFPS());
	SetWindowText(hWnd, szBuffer);

	BitBlt(m_hDC, 0, 0, WINSIZEX, WINSIZEY, m_hMemDC, 0, 0, SRCCOPY);
}

// render() ���ؼ� DC�޾ƿ;�
// ���� ���۸� ���ؼ� bitmap ������ �ش� �޸� DC�ʿ�
void CCore::init()
{
	CreateBrushPenFont();

	CPathManager::getInst()->init();
	CTimeManager::getInst()->init();
	CKeyManager::getInst()->init();
	CSceneManager::getInst()->init();
	CCollisionManager::getInst()->init();


	m_hDC = GetDC(hWnd);		// hWnd ���������� ������ �ʿ伺;

	// bitmap ������ �޸� DC ���� �� ȣȯ
		// compatible : ȣȯ
	m_hMemDC = CreateCompatibleDC(m_hDC);
	m_hBitMap = CreateCompatibleBitmap(m_hDC, WINSIZEX, WINSIZEY);

	HBITMAP hOldBitMap = (HBITMAP)SelectObject(m_hMemDC, m_hBitMap);
	DeleteObject(hOldBitMap);
}

void CCore::CreateBrushPenFont()
{	// ���߿� �̹��� �ְ� �Ǹ� ��κ� ����� �͵�
	m_arrBrush[(UINT)TYPE_BRUSH::HOLLOW]		= (HBRUSH)GetStockObject(HOLLOW_BRUSH);	// �̹� ���� ���� �� ��Ƴ��� stock�� ����

	m_arrFont[(UINT)TYPE_FONT::COMIC24]			= CreateFont(24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Comic Sans MS"));
	m_arrFont[(UINT)TYPE_FONT::COMIC18]			= CreateFont(18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Comic Sans MS"));

	m_arrPen[(UINT)TYPE_PEN::RED]				= CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)TYPE_PEN::GREEN]				= CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)TYPE_PEN::BLUE]				= CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	
	m_arrPen[(UINT)TYPE_PEN::COLLIDER0]			= CreatePen(PS_SOLID, 1, RGB(0, 255, 255));
	m_arrPen[(UINT)TYPE_PEN::COLLIDER1]			= CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
	
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

HDC CCore::getMainDC()
{
	return m_hMemDC;
}
