﻿// header.h: 표준 시스템 포함 파일
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
#define COLL_PC				isCollisionPointToCircle
#define COLL_CR				isCollisionCircleToRect
#define COLL_CC				isCollisionCircleToCircle
#define COLL_PR				isCollisionPointToRect
#define COLL_RRS			isCollisionRectToRectSameSize

#define ISMODE				CPlayer::getMode()
#define ISSCAN				CPlayer::getScan()
#define GETPOS				CPlayer::getPlayerPos()
#define SETMODE(mode)		CPlayer::setMode(mode)
#define SETBULLET(v)		CPlayer::setBullet(v)
#define GETBULLET			CPlayer::getBullet()
#define SETSCAN(v)			CPlayer::setScan(v)
#define ADDTIMER(v)			CPlayer::addScanTimer(v)


#define BLACK				RGB(0, 0, 0)
#define WHITE				RGB(255, 255, 255)

#define SCORE_RANK			(UINT)75

// 비트연산 실패
//#define BIT_LOW(key)		(UINT)(key | 0xffff)
//#define BIT_HIGH(key)		(UINT)((key >> 16) | 0xffff)
//
//#define CNT_BULLET		BIT_LOW(resultCnt)
//#define CNT_KILL			BIT_HIGH(resultCnt)
//
//#define ADD_BULLET		resultCnt++
//#define ADD_KILL			resultCnt += (0x01 <<16)

	// 오브젝트 설정 관련
		// obj
#define O_SIZE				48
#define O_HSIZE				(O_SIZE / 2)
		// player
#define P_PEN				6
#define P_SIZE				(O_SIZE - P_PEN)
#define P_SPEED				150
#define P_SIGHTON			240
#define P_SIGHTOFF			180
		// enemy
#define E_SPEEDMAX			50
#define E_SPEEDMIN			30
		// bullet
#define B_SIZE				10
#define B_SPEED				175
		// item
#define I_SIZE				34
#define I_HSIZE				(I_SIZE / 2)
			// bullet
#define I_B_DURA			12
#define I_B_MAXEA			9
#define I_B_MINEA			4
		// battery
#define BAT_MAX				35
#define BAT_ACCELMAX		7
#define BAT_DECELMAX		3
#define BAT_RECOVER			0
#define BAT_CONSUME			9
#define	BAT_INITCONSUME		4
#define BATBAR_MAX			25



// # Util
#include "struct.h"
#include "SingleTon.h"


// # enum 열거형
	// 위에 위치할수록 아래 오브젝트에 의해 덮어짐
#define OBJ		GROUP_OBJECT
enum class GROUP_OBJECT
{
	DEFAULT,
	PLAYER,
	DUMMYPLAYER,
	DUMMYENEMY,
	BATTERY,		
	ENEMY,
	TEXT,
	DROPITEM,
	BULLET,

	SIZE				// 마지막에 size 써주면 딱 맞아떨어져서 편하게 쓸 수 있음
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

// # Core, Manager, Class
#include "CCore.h"
#include "CObject.h"
#include "CTimeManager.h"
#include "CKeyManager.h"
#include "CSceneManager.h"


// # winAPI_2Dcopy.cpp에 static 멤버변수 초기화할 때 필요
#include "CPlayer.h"


using namespace std;

