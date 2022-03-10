#include "framework.h"
#include "CScene_Tool.h"
#include "resource.h"		// CreateDialog() 함수가 IDD_TILEBOX를 알기 위해 필요


// 이게 다 뭐하는 건지

INT_PTR CALLBACK TileWinProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);


CScene_Tool::CScene_Tool()
{
	m_hWnd = 0;
}

CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::update()
{
	if (KEY_ON(VK_TAB))
		changeScn(SCENE::TITLE);
}

void CScene_Tool::enter()
{
	CTexture* pTileTex = loadTex(KEY_RES::TEX_TILE, L"texture\\tilemap.bmp");

	setFocus(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));

	m_hWnd = CreateDialog(hInst, MAKEINTRESOURCE(IDD_TILEBOX), hWnd, TileWinProc);

	ShowWindow(m_hWnd, SW_SHOW);
}

void CScene_Tool::exit()
{
	EndDialog(m_hWnd, IDOK);
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK TileWinProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}