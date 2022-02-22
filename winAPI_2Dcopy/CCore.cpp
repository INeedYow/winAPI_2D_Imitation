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

// ���� ��ü �׸��� ����
void CCore::render()												
{
	 //�޸� DC ��ü�� ���� ������(����)
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

	// FPS ����ϱ�
	WCHAR strFPS[6];
	swprintf_s(strFPS, L"%5d", CTimeManager::getInst()->getFPS());
	TextOutW(m_hMemDC, WINSIZEX - 50, 20, strFPS, 5);

	// �޸� DC���� ���� DC�� �Űܿ��� �Լ�
	BitBlt(m_hDC, 0, 0, WINSIZEX, WINSIZEY, m_hMemDC, 0, 0, SRCCOPY);
}

// render() ���ؼ� DC�޾ƿ;�
// ���� ���۸� ���ؼ� bitmap ������ �ش� �޸� DC�ʿ�
	// ���� ���۸� ���� ����
void CCore::init()
{
	CTimeManager::getInst()->init();
	CKeyManager::getInst()->init();

	m_hDC = GetDC(hWnd);		// hWnd ���������� ������ �ʿ伺;

	// bitmap ������ �޸� DC ���� �� ȣȯ
		// compatible : ȣȯ
	m_hMemDC = CreateCompatibleDC(m_hDC);
	m_hBitMap = CreateCompatibleBitmap(m_hDC, WINSIZEX, WINSIZEY);

	HBITMAP hOldBitMap = (HBITMAP)SelectObject(m_hMemDC, m_hBitMap);
	DeleteObject(hOldBitMap);

	// �ӽ� �׽�Ʈ��
	obj.setPos(fPoint(640, 360));
	obj.setSize(fPoint(36, 36));
}