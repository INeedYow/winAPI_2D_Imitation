#include "framework.h"
#include "CCore.h"

// �ӽ� �׽�Ʈ��
CObject obj;

CCore::CCore()
{
	m_hDC = 0;
	m_hMemDC = 0;
	m_hBitMap = 0;
}

// DC�� �����ؾ� ��
CCore::~CCore()
{// ���� �ݳ��ϴ� �Լ��� �ٸ�	// ���� �Լ� ����..
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

// ���� ��ü �׸��� ����
void CCore::render()												
{
	 //�޸� DC ��ü�� ���� ������(����)
	Rectangle(m_hMemDC, -1, -1, WINSIZEX + 1, WINSIZEY + 1);		////// Q. �� �̷��� �����Ÿ���?

	//HPEN hPen = CreatePen(PS_SOLID, 10, RGB(255, 255, 0));
	//HBRUSH hBrush = CreateSolidBrush(RGB(0, 250, 0));				////// Q. �� ���� �ƴ϶� ���̰� ������?

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

	// �޸� DC���� ���� DC�� �Űܿ��� �Լ�
	BitBlt(m_hDC, 0, 0, WINSIZEX, WINSIZEY, m_hMemDC, 0, 0, SRCCOPY);
}

// render() ���ؼ� DC�޾ƿ;�
// ���� ���۸� ���ؼ� bitmap ������ �ش� �޸� DC�ʿ�
	// ���� ���۸� ���� ����
void CCore::init()
{
	CTimeManager::getInst()->init();

	m_hDC = GetDC(hWnd);		// hWnd ���������� ������ �ʿ伺;

	// bitmap ������ �޸� DC ���� �� ȣȯ
		// compatible : ȣȯ
	m_hMemDC = CreateCompatibleDC(m_hDC);
	m_hBitMap = CreateCompatibleBitmap(m_hDC, WINSIZEX, WINSIZEY);

	HBITMAP hOldBitMap = (HBITMAP)SelectObject(m_hMemDC, m_hBitMap);
	DeleteObject(hOldBitMap);

	// �ӽ� �׽�Ʈ��
	obj.setPos(fPoint(100, 100));
	obj.setSize(fPoint(100, 100));
}