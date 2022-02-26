#include "framework.h"
#include "CScene_Result.h"

CScene_Result::CScene_Result()
{
	setName(L"Result_Scene");
	uiCount = 0;
	fTimer = 0.f;
	szTextArr[0] = {L"G a m e  O v e r"};
	szTextArr[1] = {L"생존한 시간"};
	szTextArr[2] = {L"처치한 적들"};
	szTextArr[3] = {L"낭비한 총알"};
	szTextArr[4] = {L"\'Q\r 키 : 다시하기 \t \'E\'키 : 처음으로"};
	szTextArr[5] = {L"A"};
}

CScene_Result::~CScene_Result()
{
}

void CScene_Result::update()
{
	if (KEY_ON('Q'))
		CSceneManager::getInst()->sceneChange(SCENE::STAGE_01);
	if (KEY_ON('E'))
		CSceneManager::getInst()->sceneChange(SCENE::TITLE);
	if (uiCount < 4)
	fTimer += DT;

	if (fTimer > 1.f)
	{
		fTimer -= 1.f;
		uiCount++;
	}
}

void CScene_Result::render(HDC hDC)
{
	HPEN	hPen, hPen2, hOriginalPen;
	HBRUSH	hBrush, hBrush2, hOriginalBrush;
	HFONT	hFont, hOriginalFont;

	WCHAR strTime[8], strBullet[8], strKill[8];
	swprintf_s(strTime, L"%7d", (int)g_resultTimer);
	swprintf_s(strKill, L"%7d", g_resultKill);
	swprintf_s(strBullet, L"%7d", g_resultBullet);

	hPen = CreatePen(PS_SOLID, 10, RGB(10, 10, 10));
	hPen2 = CreatePen(PS_SOLID, 10, RGB(150, 200, 250));
	hBrush = CreateSolidBrush(RGB(30, 30, 30));
	hBrush2 = CreateSolidBrush(RGB(150, 200, 250));

	hOriginalPen = (HPEN)SelectObject(hDC,hPen);
	hOriginalBrush = (HBRUSH)SelectObject(hDC, hBrush);

	Rectangle(hDC, 10, 10, WINSIZEX - 10, 190);

	SelectObject(hDC, hPen2);
	SelectObject(hDC, hBrush2);

	Rectangle(hDC, 10, 210, WINSIZEX - 10, WINSIZEY - 10);

	SelectObject(hDC, hOriginalPen);
	SelectObject(hDC, hOriginalBrush);
	DeleteObject(hPen);
	DeleteObject(hPen2);
	DeleteObject(hBrush);
	DeleteObject(hBrush2);

	//

	SetTextColor(hDC, RGB(255,255,102));
	SetBkMode(hDC, TRANSPARENT);

	hFont = CreateFont(100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Comic Sans MS"));
	hOriginalFont = (HFONT)SelectObject(hDC, hFont);

	TextOutW(hDC, 150, 50, szTextArr[0], (int)wcslen(szTextArr[0]));

	SelectObject(hDC, hOriginalFont);
	DeleteObject(hFont);

	if (uiCount < 1) return;

	SetTextColor(hDC, RGB(50, 75, 0));
	hFont = CreateFont(48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Comic Sans MS"));
	hOriginalFont = (HFONT)SelectObject(hDC, hFont);

	TextOutW(hDC, 600, 330, szTextArr[1], (int)wcslen(szTextArr[1]));
	TextOutW(hDC, 900, 330, strTime, (int)wcslen(strTime));

	SelectObject(hDC, hOriginalFont);
	DeleteObject(hFont);

	if (uiCount < 2) return;

	SetTextColor(hDC, RGB(75, 100, 25));
	hFont = CreateFont(48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Comic Sans MS"));
	hOriginalFont = (HFONT)SelectObject(hDC, hFont);

	TextOutW(hDC, 650, 405, szTextArr[2], (int)wcslen(szTextArr[2]));
	TextOutW(hDC, 950, 405, strKill, (int)wcslen(strKill));

	SelectObject(hDC, hOriginalFont);
	DeleteObject(hFont);

	if (uiCount < 3) return;

	SetTextColor(hDC, RGB(100, 125, 50));
	hFont = CreateFont(48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Comic Sans MS"));
	hOriginalFont = (HFONT)SelectObject(hDC, hFont);

	TextOutW(hDC, 700, 480, szTextArr[3], (int)wcslen(szTextArr[3]));
	TextOutW(hDC, 1000, 480, strBullet, (int)wcslen(strBullet));

	SelectObject(hDC, hOriginalFont);
	DeleteObject(hFont);

	if (uiCount < 4) return;

	SetTextColor(hDC, RGB(0, 0, 0));
	hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Comic Sans MS"));
	hOriginalFont = (HFONT)SelectObject(hDC, hFont);

	TextOutW(hDC, 430, 650, szTextArr[4], (int)wcslen(szTextArr[4]));

	SelectObject(hDC, hOriginalFont);
	DeleteObject(hFont);

	// 등급 알파벳
	SetTextColor(hDC, RGB(200, 50, 200));
	hFont = CreateFont(300, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Comic Sans MS"));
	hOriginalFont = (HFONT)SelectObject(hDC, hFont);

	TextOutW(hDC, 160, 290, szTextArr[5], (int)wcslen(szTextArr[5]));

	SelectObject(hDC, hOriginalFont);
	DeleteObject(hFont);
}

void CScene_Result::enter()
{	// 랭크
	uiTotalScore = g_resultBullet + g_resultKill + g_resultTimer;

	if		(uiTotalScore < SCORE_RANK)												szTextArr[5] = L"C";
	else if (SCORE_RANK		<= uiTotalScore && uiTotalScore < SCORE_RANK * 2)		szTextArr[5] = L"B";
	else if (SCORE_RANK * 2 <= uiTotalScore && uiTotalScore < SCORE_RANK * 3)		szTextArr[5] = L"A";
	else if (SCORE_RANK * 3	<= uiTotalScore && uiTotalScore < SCORE_RANK * 4)		szTextArr[5] = L"S";
	else																			szTextArr[5] = L"SS";
}

void CScene_Result::exit()
{
	uiCount = 0;
	fTimer = 0;
	g_resultTimer = 0;
	g_resultBullet = 0;
	g_resultKill = 0;
}
