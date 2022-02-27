#pragma once
#include "CObject.h"
class CBattery : public CObject
{
	float	m_fBattery;			// 배터리 (스페이스바 지속)
	float	m_fAccel;			// 배터리 회복 가속도 (점점 더 회복하게)
	float	m_fDecel;			// 배터리 소모 가속도 (점점 덜 소모하게)
	float	m_fBar;				// 배터리 출력바

public:
	CBattery();
	virtual ~CBattery();

	bool isEnough();
	
	float getBattery();

	void setBattery(float batt);

	virtual void update();
	virtual void render(HDC hDC);
};

