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
	// 게임 결과 출력용
extern float   g_resultTimer;
extern USHORT  g_resultBullet;
extern USHORT  g_resultKill;


// # 전처리기
#define WINSTYLE			WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU
#define WINPOSITIONX		100
#define WINPOSITIONY		100
#define WINSIZEX			1280
#define WINSIZEY			720

#define DT					CTimeManager::getInst()->getDT()
#define	KEY_HOLD(key)		CKeyManager::getInst()->getKeyPress(key)
#define KEY_ON(key)			CKeyManager::getInst()->getKeyOn(key)
#define KEY_OFF(key)		CKeyManager::getInst()->getKeyOff(key)

	// 충돌관련 함수
#define ISCOLLPC			isCollisionPointToCircle
#define ISCOLLCR			isCollisionCircleToRect
#define ISCOLLCC			isCollisionCircleToCircle
#define ISCOLLPR			isCollisionPointToRect
#define ISCOLLRR			isCollisionRectToRect

#define ISMODE				CPlayer::getMode()
#define ISSCAN				CPlayer::getScan()
#define GETPOS				CPlayer::getPlayerPos()
#define GETBULLET			CPlayer::getBullet()
#define GETSCANTIMER()		CPlayer::getScanTimer()
#define SETMODE(v)			CPlayer::setMode(v)
#define SETBULLET(v)		CPlayer::setBullet(v)
#define SETSCANTIMER(v)		CPlayer::setScanTimer(v)


#define C_BLACK				RGB(0, 0, 0)
#define C_WHITE				RGB(255, 255, 255)

#define SCORE_RANK			(UINT)75


	// 오브젝트 설정 관련
		// obj
#define O_SIZE				48
#define O_HSIZE				(O_SIZE / 2)
		// player
#define P_PEN				6
#define P_SIZE				(O_SIZE - P_PEN)
#define P_SPEED				135
#define P_SIGHTON			250
#define P_SIGHTOFF			190
		// enemy
			// zombie
#define EZ_SPEEDMAX			60
#define EZ_SPEEDMIN			40
#define EZ_SIZE				48
			// zombieDog
#define EZD_SIZE			30
#define EZD_SPEED			75
			// crawler
#define EC_SIZE				40
#define EC_SPEEDMAX			400
#define EC_SPEEDMIN			20
			// worms
#define EW_SIZE				40
#define EW_HSIZE			(EW_SIZE / 2)
#define EW_SPEED			180
#define EW_LENMAX			(EW_SIZE * 2)
		// bullet
#define B_SIZE				10
#define B_SPEED				200
		// item
#define I_SIZE				34
#define I_HSIZE				(I_SIZE / 2)
			// bullet
#define IB_DURA				12
#define IB_MAXEA			9
#define IB_MINEA			4
		// battery
#define BAT_MAX				40
#define BAT_ACCELMAX		7
#define BAT_DECELMAX		4
#define BAT_RECOVER			1
#define BAT_CONSUME			9
#define	BAT_INITCONSUME		4
#define BATBAR_MAX			25


// # enum 열거형
	// 위에 위치할수록 아래 오브젝트에 의해 덮어짐
#define OBJ		GROUP_OBJECT
enum class GROUP_OBJECT
{
	DEFAULT,
	SIGHTCIRCLE,
	PLAYER,
	DUMMYPLAYER,
	DUMMYENEMY,
	BATTERY,		
	ENEMY,
	TEXT,
	DROPITEM,
	BULLET,

	SIZE
};

#define SCENE	GROUP_SCENE
enum class GROUP_SCENE
{
	TITLE,
	TUTORIAL_01,
	TUTORIAL_02,
	STAGE_01,
	RESULT,
	
	SIZE
};

#define IKEY	KEY_ITEM
enum class KEY_ITEM
{
	NONE,
	BULLET,
	SCANNER,

	SIZE
};


// GDI
#define BRUSH	TYPE_BRUSH
enum class TYPE_BRUSH
{
	HOLLOW,

	BLACK30,
	BLACK15,
	WHITE200,

	// 적
	EZ_BRU,
	EZD_BRU,
	EC_BRU,
	EW_BRU,
	// 플레이어
	P_BRUON,
	P_BRUOFF,
	// 아이템
	I_BRUFLICK,
	I_BRUNORMAL,

	SIZE
};

#define PEN		TYPE_PEN
enum class TYPE_PEN
{
	RED,
	GREEN,
	BLUE,

	// 적
	E_EDGE,
	// 플레이어
	P_EDGEON,
	P_EDGEOFF,
	// 아이템
	I_EDGE,
	I_SCAN,

	SIZE
};

#define FONT	TYPE_FONT
enum class TYPE_FONT
{
	COMIC24,
	COMIC18,
	COMIC48,
	COMIC,

	
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

// # Util
#include "struct.h"
#include "SingleTon.h"
#include "func.h"
//#include "SelectGDI.h"		// 사용하는 cpp 파일에서 참조하는 식으로


// # Core, Manager, Class
#include "CCore.h"
#include "CObject.h"
#include "CTimeManager.h"
#include "CKeyManager.h"
#include "CSceneManager.h"
#include "CCollisionManager.h"


// # winAPI_2Dcopy.cpp에 static 멤버변수 초기화할 때 필요
#include "CPlayer.h"
#include "CCollider.h"