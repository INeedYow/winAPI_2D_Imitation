// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#pragma comment(lib, "msimg32.lib")

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
#include <assert.h>

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

#define COLLRR				collisionRectToRect

// # 비트연산
	// 상태값
#define S_JUMP				0x0001
#define S_DIR				0x0002
#define S_SUPER				0x0004
#define S_INVINCIBLE		0x0008

#define S_DEATH				0x4000
#define S_CAMERA			0x8000


// # 능력치
	// player
#define P_SPD				100
#define P_JUMPSPD			300
#define P_ACCEL 			250
#define P_DECEL				175
#define P_GRAV				400
#define P_GRAVMAX			(P_GRAV * 3)
		// smallMario
#define P_sizex				22
#define P_sizey				24
		// bigMario
#define P_SIZEX				30
#define P_SIZEY				55
	// tile
#define T_SIZE				50
	// fireball
#define FB_SIZE				10
#define FB_SPD				250
#define FB_DUR				8
#define FB_GRAV				1000
#define FB_GRAVMAX			(FB_GRAV * 3)
	// item
#define IT_SIZE				30
#define ITM_SPD				80


// # enum 열거형
	// 위에 위치할수록 아래 오브젝트에 의해 덮어짐
#define OBJ		GROUP_OBJECT
enum class GROUP_OBJECT
{
	DEFAULT,
	TILE,
	BLOCK,
	ITEM,
	PLAYER,
	MONSTER,
	FIREBALL,

	SIZE
};

#define OBJNAME	OBJECT_NAME
enum class OBJECT_NAME
{
	DEFAULT,
	MARIO,

	MONSTER,

	ITEM_COIN,
	ITEM_FLOWER,
	ITEM_MUSHROOM,
	ITEM_STAR,

	BLOCK,
	TILE,

	FIREBALL,


	SIZE
};

#define SCENE	GROUP_SCENE
enum class GROUP_SCENE
{
	TITLE,
	STAGE_01,
	RESULT,

	SIZE
};

enum class TYPE_MARIO
{
	smMARIO,
	bgMARIO,
	frMARIO,

	SIZE
};


// Obj::ITEM과 중복이슈
//#define ITEM	GROUP_ITEM
enum class GROUP_ITEM
{
	NONE,
	COIN,
	FLOWER,
	MUSHROOM,
	STAR,

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
	COMIC72,

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

#define DIR		COLL_DIR
enum class COLL_DIR
{
	NONE,
	TOP,
	BOTTOM,
	LEFT,
	RIGHT,

	END
};

#define KEY_RES	KEY_RESOURCE
enum class KEY_RESOURCE
{
	TEX_PLAYER,
	TEX_MONSTER,
	TEX_ITEM_FB,

	SIZE

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
#include "CCameraManager.h"

#include "CObject.h"
// # winAPI_2Dcopy.cpp에 static 멤버변수 초기화할 때 필요
#include "CCollider.h"
#include "CAnimator.h"

#define DT						CTimeManager::getInst()->getDT()
#define fDT						CTimeManager::getInst()->getfDT()

#define	KEY_HOLD(key)			CKeyManager::getInst()->getKeyHold(key)
#define KEY_ON(key)				CKeyManager::getInst()->getKeyOn(key)
#define KEY_OFF(key)			CKeyManager::getInst()->getKeyOff(key)
#define KEY_NONE(key)			CKeyManager::getInst()->getKeyNone(key)

#define createObj(pObj, eGroup)	CEventManager::getInst()->eventCreateObject(pObj, eGroup)
#define deleteObj(pObj)			CEventManager::getInst()->eventDeleteObject(pObj)
#define changeScn(eScn)			CEventManager::getInst()->eventChangeScene(eScn)

#define createAnim				getAnimator()->createAnimation
#define PLAY(name)				getAnimator()->play(name)

#define setFocus(fp)			CCameraManager::getInst()->setFocusOn(fp)
#define setTrace(pObj)			CCameraManager::getInst()->setTraceObj(pObj)
#define getRendPos(pos)			CCameraManager::getInst()->getRenderPos(pos)

#define loadTex					CResourceManager::getInst()->loadTextrue

