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
#include <string>





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

#define COLL_PC			isCollisionPointToCircle
#define COLL_CR			isCollisionCircleToRect
#define COLL_CC			isCollisionCircleToCircle
#define COLL_PR			isCollisionPointToRect
#define COLL_RRS		isCollisionRectToRectSameSize

#define isMode			CPlayer::getMode()
#define BLACK			RGB(255, 255, 255)
#define WHITE			RGB(0, 0, 0)

	// 설정,스탯 관련
		// obj
#define O_SIZE		48
		// player
#define P_PEN		6
#define P_SIZE		(O_SIZE - P_PEN)

#define P_SPEED		200
		// enemy
#define E_SPEED		100


// # Util
#include "struct.h"
#include "SingleTon.h"


// # enum 열거형 
#define OBJ		GROUP_OBJECT
enum class GROUP_OBJECT
{
	DEFAULT,
	PLAYER,
	ENEMY,
	TARGET,
	BLOCK,
	TEXT,
	DUMMYPLAYER,

	SIZE				// 마지막에 size 써주면 딱 맞아떨어져서 편하게 쓸 수 있음
};

#define SCENE	GROUP_SCENE
enum class GROUP_SCENE
{
	TITLE,
	TUTORIAL_01,
	TUTORIAL_02,
	STAGE_01,
	ENDING,
	
	SIZE
};


// # Core, Manager, Class
#include "CCore.h"
#include "CObject.h"
#include "CTimeManager.h"
#include "CKeyManager.h"
#include "CSceneManager.h"


// #
#include "CPlayer.h"


// # 전역 변수
extern HWND hWnd;
extern HINSTANCE hInstance;

using namespace std;

