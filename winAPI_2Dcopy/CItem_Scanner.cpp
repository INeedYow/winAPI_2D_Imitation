#include "framework.h"
#include "CItem_Scanner.h"

CItem_Scanner::CItem_Scanner()
{
	setPos(fPoint(0.f, 0.f));
	setSize(fPoint((float)I_SIZE, (float)I_SIZE));
	setTimer(0.f);
	setDuration(I_B_DURA);
	setKey((UCHAR)IKEY::SCANNER);
}

CItem_Scanner::~CItem_Scanner()
{
}

void CItem_Scanner::update()
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
			duraCnt = I_B_DURA;
		}

		if (duraCnt <= 6)
			isFlick = !isFlick;	// ���ӽð� 6�� �����̸� 1�ʸ��� ��ȯ 
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
		SETSCAN(true);
		ADDTIMER(3.f);
		setRandPos();
		duraCnt = I_B_DURA;
	}

	setTimer(timeCnt);
	setDuration(duraCnt);
	setIsFlick(isFlick);
}

void CItem_Scanner::render(HDC hDC)
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

	hPen = CreatePen(PS_SOLID, 1, RGB(102, 153, 255));
	hBrush = CreateSolidBrush(getIsFlick() ? RGB(102, 255, 255) : RGB(0, 255, 255));

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

	// ���� �˴� �׸�� �����Ϸ��� ������ �̸����� ������ҵ��ؼ�
	HFONT hFont, hOriginalFont;
	hFont = CreateFont(18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Comic Sans MS"));
	hOriginalFont = (HFONT)SelectObject(hDC, hFont);

	SetTextColor(hDC, BLACK);
	LPCWSTR strMessage1 = L"��ĳ��";
	TextOutW(hDC, pos.x - 18, pos.y, strMessage1, wcslen(strMessage1));

	SelectObject(hDC, hOriginalFont);
	DeleteObject(hFont);
}
