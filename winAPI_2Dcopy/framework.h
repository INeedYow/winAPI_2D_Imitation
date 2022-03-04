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

#include <time.h>
#include <math.h>


// # STL
#include <vector>
#include <string>
#include <map>

using namespace std;

// # 전역 변수
extern HWND			hWnd;
extern HINSTANCE	hInstance;


// # 전처리기
#define WINSTYLE			WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU
#define WINPOSITIONX		100
#define WINPOSITIONY		100
#define WINSIZEX			1280
#define WINSIZEY			720

	// 충돌관련 함수
#define ISCOLLPC			isCollisionPointToCircle
#define ISCOLLCR			isCollisionCircleToRect
#define ISCOLLCC			isCollisionCircleToCircle
#define ISCOLLPR			isCollisionPointToRect
#define ISCOLLRR			isCollisionRectToRect


// # enum 열거형
	// 위에 위치할수록 아래 오브젝트에 의해 덮어짐
#define OBJ		GROUP_OBJECT
enum class GROUP_OBJECT
{
	DEFAULT,

	SIZE
};

#define SCENE	GROUP_SCENE
enum class GROUP_SCENE
{
	TITLE,
	STAGE_01,
	
	SIZE
};

#define IKEY	KEY_ITEM
enum class KEY_ITEM
{
	NONE,

	SIZE
};


// GDI
#define BRUSH	TYPE_BRUSH
enum class TYPE_BRUSH
{
	HOLLOW,

	SIZE
};

#define PEN		TYPE_PEN
enum class TYPE_PEN
{
	RED,
	GREEN,
	BLUE,

	COLLIDER0,
	COLLIDER1,

	SIZE
};

#define FONT	TYPE_FONT
enum class TYPE_FONT
{
	COMIC24,
	COMIC18,
	COMIC48,

	SIZE
};

#define SHAPE	COLL_SHAPE
enum class COLL_SHAPE
{
	CIRCLE,
	RECT,
	POINT,

	END
};

#define EVENT	TYPE_EVENT
enum class TYPE_EVENT
{
	CREATEOBJ,
	DELETEOBJ,
	SCENECHANGE,

	END
};

// # Util
#include "struct.h"
#include "SingleTon.h"
#include "func.h"
//#include "SelectGDI.h"		// 사용하는 cpp 파일에서 참조하는 식으로


// # Core, Manager, Class
#include "CCore.h"
#include "CTimeManager.h"
#include "CKeyManager.h"
#include "CSceneManager.h"
#include "CResourceManager.h"
#include "CCollisionManager.h"
#include "CEventManager.h"
#include "CPathManager.h"

#include "CObject.h"
// # winAPI_2Dcopy.cpp에 static 멤버변수 초기화할 때 필요
#include "CCollider.h"


#define DT						CTimeManager::getInst()->getDT()
#define fDT						CTimeManager::getInst()->getfDT()

#define	KEY_HOLD(key)			CKeyManager::getInst()->getKeyPress(key)
#define KEY_ON(key)				CKeyManager::getInst()->getKeyOn(key)
#define KEY_OFF(key)			CKeyManager::getInst()->getKeyOff(key)

#define createObj(pObj, group)	CEventManager::getInst()->eventCreateObject(pObj, group)
#define deleteObj(pObj)			CEventManager::getInst()->eventDeleteObject(pObj)