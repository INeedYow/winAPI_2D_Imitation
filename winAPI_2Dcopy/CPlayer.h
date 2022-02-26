#pragma once
#include "CObject.h"
class CPlayer : public CObject
{
protected:
	static bool isMode;			// 시야 모드
	static fPoint fpPos;		// 현재 좌표

	fPoint	m_fpPrevPos;		// 이전 좌표
	fVec2	m_fvDir;			// 총알 방향
	UINT	m_uiBullet;			// 총알 개수
	float	m_fSpeed;			// 이동 속도

public:
	CPlayer();
	virtual ~CPlayer();

	virtual void update();
	virtual void render(HDC hDC);
	
	void setDir(fVec2 vec);

	static bool getMode();
	static fPoint getPlayerPos();
	static void setPlayerPos(fPoint pos);

	void createBullet();

	void setBullet(UINT ea);
	void death();
};

// 하나 걸리는 게
// 다른 오브젝트들에서 플레이어 좌표로 렌더를 결정하기 때문에 부모의 pos를 안 쓰고
// static 멤버변수 pos를 새로 만들어서 씀
