#pragma once
#include "CObject.h"
#include "CBattery.h"

class CPlayer : public CObject
{
protected:
	static bool		isMode;			// 시야 모드
	static bool		isScan;			// 스캐너 모드
	static float	scanTimer;		// 스캐너 지속시간
	static fPoint	fpPos;			// 현재 좌표
	static UINT		uiBullet;		// 총알 개수

	fPoint		m_fpPrevPos;		// 이전 좌표
	fVec2		m_fvDir;			// 총알 방향
	float		m_fSpeed;			// 이동 속도

	CBattery	m_battery;			// 배터리 (스페이스바)
	
public:
	CPlayer();
	virtual ~CPlayer();

	virtual void update();
	virtual void render(HDC hDC);
	
	void setDir(fVec2 vec);

	static bool getMode();
	static bool getScan();
	static float getScanTimer();
	static fPoint getPlayerPos();
	static UINT getBullet();

	static void setScanTimer(float time);
	static void setMode(bool mode);
	static void setPlayerPos(fPoint pos);
	static void setBullet(UINT bullet);


	void createBullet();

	void death();
};

// 다른 오브젝트들에서 플레이어 좌표로 렌더를 결정하기 때문에 부모의 pos를 안 쓰고
// static 멤버변수 pos를 새로 만들어서 씀
// 좋은 방법은 아닌 것 같음