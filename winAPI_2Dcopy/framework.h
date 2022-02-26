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

#define ISMODE			CPlayer::getMode()
#define GETPOS			CPlayer::getPlayerPos()
#define BLACK			RGB(0, 0, 0)
#define WHITE			RGB(255, 255, 255)

	// 설정,스탯 관련
		// obj
#define O_SIZE				48
#define O_HSIZE				(O_SIZE / 2)
		// player
#define P_PEN				6
#define P_SIZE				(O_SIZE - P_PEN)
#define P_SPEED				200
#define P_SIGHTON			240
#define P_SIGHTOFF			180
		// bullet
#define B_SIZE				10
#define B_SPEED				150
		// enemy
#define E_SPEED				50

// TODO : (교수님 질문)
// 중심 좌표(pos)에 대해서 scale / 2만큼 이동한 좌표로 그리는 작업이 많은데요
// 정수 나눗셈의 경우 처리 시간이나 작업량이 적어서 무시해도 되는 정도인가요?
// scale / 2가 자주 쓰일 값이라면 #define으로 결과값을 미리 정해놓고 계산시키면 유의미하게 차이가 날까요?


// # Util
#include "struct.h"
#include "SingleTon.h"


// # enum 열거형 
#define OBJ		GROUP_OBJECT
enum class GROUP_OBJECT
{
	DEFAULT,
	DUMMYPLAYER,
	DUMMYENEMY,
	PLAYER,
	ENEMY,
	BULLET,
	BLOCK,
	TEXT,

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


// # winAPI_2Dcopy.cpp에 static 멤버변수 초기화할 때 필요
#include "CPlayer.h"


// # 전역 변수
extern HWND hWnd;
extern HINSTANCE hInstance;

using namespace std;

