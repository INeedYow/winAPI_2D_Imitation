// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// # STL
#include <vector>

// # Util
#include "struct.h"
#include "SingleTon.h"

// # Core, Manager, Class
#include "CCore.h"
#include "CObject.h"
#include "CTimeManager.h"

// # 전처리기
#define WINSTYLE		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU
#define WINPOSITIONX	100
#define WINPOSITIONY	100
#define WINSIZEX		1280
#define WINSIZEY		720

#define DT				CTimeManager::getInst()->getDT()


// # 전역변수
extern HWND hWnd;