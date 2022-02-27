#include "framework.h"
#include "CItem_Bullet.h"

CItem_Bullet::CItem_Bullet()
{
	setPos(fPoint(0.f, 0.f));
	setSize(fPoint((float)I_SIZE, (float)I_SIZE));
	setTimer(0.f);
	setDuration(I_B_DURA);
	setRandEA();
	setKey((UCHAR)IKEY::BULLET);
}

CItem_Bullet::~CItem_Bullet()
{
}

void CItem_Bullet::setRandEA()
{
	ucEA = rand() % (I_B_MAXEA - I_B_MINEA + 1) + I_B_MINEA;
}

UCHAR CItem_Bullet::getEA()
{
	return ucEA;
}

void CItem_Bullet::update()
{
	float   timeCnt = getTimer();
	UINT	duraCnt = getDuration();
	fPoint	itemPos = getPos();
	bool	isFlick = getIsFlick();
	fPoint	playerPos = GETPOS;

	timeCnt += DT;

	if (timeCnt >= 1.f)			// 1�� ���
	{
		timeCnt = 0.f;
		duraCnt--;				// ���ӽð� ����

		if (0 == duraCnt)		// ���ӽð� 0�̸�
		{
			setRandPos();		// ��ġ ����
			setRandEA();
			duraCnt = I_B_DURA;
		}
		if (6 >= duraCnt)
			isFlick = !isFlick;
	}

	// TODO (������ ����)
	// �������� �÷��̾�� �浹���� ��(����) �÷��̾�� �������� ���� ó���ؾ� �ϴ� ������ �ٸ��� �� ���� �ڱ� ������� ������ �� ���ݾƿ�..
	// ���� �浹�ߴ��� ����� �÷��̾� update()������ �ϰ� �ְ� item_bullet�� update()������ �ϰ� �ִµ���
	// ������ ��ó���� �Ϸ��� �̷��� �ϴ� �� �´µ� �� ���� ����� �� ���ؼ� ȿ�������� ������ ����� �����?
	RECT areaRect = { (int)itemPos.x - (int)I_HSIZE,
					  (int)itemPos.y - (int)I_HSIZE,
					  (int)itemPos.x + (int)I_HSIZE,
					  (int)itemPos.y + (int)I_HSIZE };

	if (itemPos.COLL_CR(playerPos, (int)O_HSIZE, areaRect))
	{	// �����ϸ� ��ġ �̵�
		int a = GETBULLET;
		SETBULLET(a + ucEA);
		setRandPos();
		setRandEA();		// �Ѿ� ���¥�� ���������� ������ ������ �ִٰ� �׸�ŭ �÷��̾� �Ѿ� ������Ű�� ������ ���ϴ� ��
		duraCnt = I_B_DURA;
	}

	// setPos(itemPos);		// setRandPos()�� ��ġ �ٲ����� �ٽ� itemPos�� ���������ϱ� ��ġ�� �� �ٲ���
	setTimer(timeCnt);
	setDuration(duraCnt);
	setIsFlick(isFlick);
}

void CItem_Bullet::render(HDC hDC)
{

	fPoint	pos = getPos();
	fPoint	playerPos = GETPOS;
	UINT	duraCnt = getDuration();

	HPEN hPen, hOriginalPen;
	HBRUSH hBrush, hOriginalBrush;

	int sight = ISMODE ? P_SIGHTON : P_SIGHTOFF;

	// �� ��Ȯ�� ��� ��� ���̷��� �������� COLL_PC�Լ�
	if (!pos.COLL_PC(pos, playerPos, sight))
	{
		if (ISSCAN)
		{	// ��ĳ��
			hPen = CreatePen(PS_SOLID, 1, RGB(200, 200, 50));
			hOriginalPen = (HPEN)SelectObject(hDC, hPen);
			Rectangle(hDC, pos.x - 1, pos.y - 1, pos.x + 1, pos.y + 1);
			SelectObject(hDC, hOriginalPen);
			DeleteObject(hPen);
		}
		return;
	}

	// ������ �����ð� �� �� �������� �����̰� �غ��� ����
	hPen = CreatePen(PS_SOLID, 1, RGB(51, 51, 0));
	hBrush = CreateSolidBrush(getIsFlick() ? RGB(051,102,0): RGB(153, 204, 0));
	
	hOriginalPen = (HPEN)SelectObject(hDC, hPen);
	hOriginalBrush = (HBRUSH)SelectObject(hDC, hBrush);

	Rectangle(hDC,
		(int)(pos.x - I_HSIZE),
		(int)(pos.y - I_HSIZE),
		(int)(pos.x + I_HSIZE),
		(int)(pos.y + I_HSIZE));

	SelectObject(hDC, hOriginalPen);
	SelectObject(hDC, hOriginalBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);

	HFONT hFont, hOriginalFont;
	hFont = CreateFont(18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Comic Sans MS"));
	hOriginalFont = (HFONT)SelectObject(hDC, hFont);

	SetTextColor(hDC, BLACK);
	LPCWSTR strMessage1 = L"�Ѿ�";
	TextOutW(hDC, pos.x - 12, pos.y, strMessage1, wcslen(strMessage1));

	SelectObject(hDC, hOriginalFont);
	DeleteObject(hFont);

	// ��������� ���ӽð� ǥ���ϴ� �ڵ�
	/*WCHAR szBuffer[255] = {};
	swprintf_s(szBuffer, L"%d", duraCnt);
	TextOutW(hDC, pos.x, pos.y, szBuffer, wcslen(szBuffer));*/
}
