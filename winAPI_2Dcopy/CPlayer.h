#pragma once
#include "CObject.h"

class CPlayer : public CObject
{
	static UINT s_uiCoin;

	float	m_fSpeed;
	float	m_fAccel;
	float	m_fTimer;

	UCHAR	m_ucState;		// 상태(SUPER,FIRE,BIG,DIR,JUMP)

public:
	CPlayer();
	virtual ~CPlayer();

	virtual void update();
	virtual void render(HDC hDC);

	static UINT getCoin();
	static void setCoin(UINT coin);

	void createFireball();
};

UINT    CPlayer::s_uiCoin = 0;

// TODO 버섯, 꽃, 별 먹었을 때 잠시 멈추면서 플레이어 모습 변하는 과정만 update()되도록 하기
// bool 변수로 true일 때 아예 업데이트 생략하도록 하면 될 것 같은 느낌
// static이나 전역변수로?