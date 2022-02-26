// winAPI_2Dcopy.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "winAPI_2Dcopy.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE   hInst;                                    // 현재 인스턴스입니다.
HWND        hWnd;                                     // 윈도우 핸들
WCHAR       szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR       szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// static 멤버변수 초기화
bool CPlayer::isMode = false;
fPoint CPlayer::fpPos = { 0.f, 0.f };

// 전역변수 (결과창 출력)
float   g_resultTimer = 0.f;
USHORT  g_resultBullet = 0;
USHORT  g_resultKill = 0;


// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// _In_(SAL 주석) : 자주 사용되는 주석을 키워드로
// hInstance     : 프로세스 시작 주소, 인스턴스 핸들
// hPrevInstance : 이전에 실행된 인스턴스 핸들
// lpCmdLine     : 명령으로 입력된 프로그램 인수
// nCmdShow      : 프로그램이 시작될 형태

// wWinMain : 윈도우창 세팅 후 화면에 띄우고 메세지 루프
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
   // _CrtSetBreakAlloc(296);         // flag 키값을 인자로 

    srand((unsigned int)time(NULL));

    // 전역 문자열을 초기화합니다.
    // 위에 선언된 WCHAR 전역 문자열 변수들 리소스로 초기화
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPI2DCOPY, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    // 단축키 : 리소스뷰에서 단축키들 건들 수 있음
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI2DCOPY));

    MSG msg;

    // 기본 메시지 루프입니다:
    // 메시지 큐에서 메시지 확인될 때까지 대기하는 방식(cin처럼)

    // GetMessage  : 메시지 큐에 메시지 없으면 대기, 메시지 있다면 true 반환.단, WM_QUIT 메시지 있으면 false 반환
    // PeekMessage : 메시지 큐에 메시지 없으면 false, 메시지 있다면 true 반환.

    // 게임처리를 계속 진행하다가 메시지 큐에 메시지 들어오면 메시지를 처리하는 방식으로
    // PM_'키워드'를 5번째 인자로 넣어 메시지 가져오는 행동 입력가능
        //PM_REMOVE PM_NOREMOVE 등등

    // 코어 초기화 진행
    CCore::getInst()->init();

    while (TRUE)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message) break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) // 단축키 처리
            {
                TranslateMessage(&msg);     // 키보드 입력메시지 처리 담당 
                DispatchMessage(&msg);      // WndProc에서 전달된 메시지를 실제 윈도우에 전달
            }
        }
        else
        {
            CCore::getInst()->update();
            CCore::getInst()->render();
        }
        
    }


    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;                                  // 스타일
    wcex.lpfnWndProc    = WndProc;                                                  // 메시지 처리하는 함수 지정
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;                                                // 윈도우 클래스를 등록한 인스턴스의 핸들
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI2DCOPY));
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr;                                                  // 메뉴 (게임에선 필요 없으므로 nullptr했음)
    wcex.lpszClassName  = szWindowClass;                                            // 윈도우 클래스 이름

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   hWnd = CreateWindowW(szWindowClass,         // 클래스 이름
                        szTitle,               // 타이틀 이름
                        WINSTYLE,              // 윈도우 스타일 (비트연산 때 봤던 거)
                        WINPOSITIONX,          // 윈도우 화면 좌표
                        WINPOSITIONY,          // 
                        WINSIZEX,              // 윈도우 화면 크기
                        WINSIZEY,              // 
                        nullptr,               // 부모 윈도우(누군가가 호출한)
                        nullptr,               // 메뉴 핸들
                        hInstance,             // 인스턴스 지정
                        nullptr);              // 추가 매개변수

   if (!hWnd)
   {
      return FALSE;
   }

   // 현재 타이틀바 포함한 전체크기가 1280 720 이므로 실제 윈도우 내용 화면의 크기를 1280 720으로 맞추기 위해서
   RECT rect = { 0, 0, WINSIZEX, WINSIZEY};
   //rect.left = 0;
   //rect.top = 0;
   //rect.right = WINSIZEX;
   //rect.bottom = WINSIZEY;

   AdjustWindowRect(&rect, WINSTYLE, false); //(현재 윈도우 크기, 윈도우 스타일, 메뉴 여부)
   SetWindowPos(hWnd, NULL, WINPOSITIONX, WINPOSITIONY, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER | SWP_NOMOVE);
                                                                                        // Z-Order : 어떤 창이 다른 창들 위에 가려지는 것  // 0으로 둬도 됨


   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//

// 임시
POINT g_mousePos = {0, 0};
POINT g_keyPos = {0, 0};
int g_color = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            //Device Context 만들어서 ID 반환
            HDC hdc = BeginPaint(hWnd, &ps);

            //Rectangle(hdc, 0, 0, 200, 200);
            //Ellipse(hdc, 300, 300, 600, 600);

            //// 직접 펜과 브러쉬 만들어서 DC에 적용
            //HPEN hGreenPen = CreatePen(PS_DOT, 10, RGB(g_color, g_color, g_color)); // J, K 눌러서 색 변화 가능
            //HBRUSH hRedBrush = CreateSolidBrush(RGB(255, 255, 255));

            //// 기존 펜과 브러쉬 ID값 저장
            //HPEN hOldPen = (HPEN)SelectObject(hdc, hGreenPen);
            //HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hRedBrush);

            //Ellipse(hdc, g_mousePos.x - 50, g_mousePos.y - 50, g_mousePos.x + 50, g_mousePos.y + 50);
            //Rectangle(hdc, g_keyPos.x - 10, g_keyPos.y - 10, g_keyPos.x + 10, g_keyPos.y + 10);

            //// DC의 펜과 브러쉬를 원래 것으로 되돌림
            //SelectObject(hdc, hOldPen);
            //SelectObject(hdc, hOldBrush);

            //// 다 쓴 펜, 브러쉬 삭제
            //DeleteObject(hGreenPen);
            //DeleteObject(hRedBrush);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
