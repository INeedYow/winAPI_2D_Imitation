// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#pragma comment(lib, "Msimg32.lib")		// TransparentBlt() 사용 (무거움)

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>
#include <math.h>
#include <string>

// # STL
#include <vector>
#include <map>

// # Util
#include "struct.h"
#include "SingleTon.h"
#include "Logger.h"

// # 전처리기
#define WINSTYLE		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU
#define WINPOSITIONX	100
#define WINPOSITIONY	100
#define WINSIZEX		1280
#define WINSIZEY		720

#define DT				CTimeManager::getInst()->getDT()
#define	KEY_HOLD(key)	CKeyManager::getInst()->getKeyPress(key)
#define KEY_ON(key)		CKeyManager::getInst()->getKeyOn(key)
#define KEY_OFF(key)	CKeyManager::getInst()->getKeyOff(key)


// # enum 열거형 
#define OBJ		GROUP_OBJECT
enum class GROUP_OBJECT
{
	DEFAULT,
	PLAYER,
	ENEMY,
	MISSILE,

	SIZE				// 마지막에 size 써주면 딱 맞아떨어져서 편하게 쓸 수 있음
};

#define SCENE	GROUP_SCENE
enum class GROUP_SCENE
{
	TITLE,
	STAGE_01,
	STAGE_02,
	
	SIZE
};

#define DIR		GROUP_DIRECTION
enum GROUP_DIRECTION
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	LEFTUP,		// 좌상	// 45도 각도
	RIGHTUP,	// 우상
	RIGHTDOWN,	// 우하
	LEFTDOWN,	// 좌하

	END
};


#define KEYTEX	KEY_TEXTURE
enum class KEY_TEXTURE
{
	DEFAULT,
	PLAYER,

	SIZE
};


// # 전역변수
extern HWND hWnd;
extern HINSTANCE hInstance;

using namespace std;


// # Core, Manager, Class
#include "CCore.h"
#include "CPathManager.h"
#include "CTimeManager.h"
#include "CKeyManager.h"
#include "CSceneManager.h"

#include "CObject.h"