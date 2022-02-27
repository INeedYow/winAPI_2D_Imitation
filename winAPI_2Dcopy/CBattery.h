#pragma once
#include "CObject.h"
class CBattery : public CObject
{
	float	m_fBattery;			// ���͸� (�����̽��� ����)
	float	m_fAccel;			// ���͸� ȸ�� ���� (���� �� ȸ���ϰ�)
	float	m_fDecel;			// ���͸� �Ҹ� ���� (���� �� �Ҹ��ϰ�)
	float	m_fBar;				// ���͸� ��¹�

public:
	CBattery();
	virtual ~CBattery();

	bool isEnough();
	
	float getBattery();

	void setBattery(float batt);

	virtual void update();
	virtual void render(HDC hDC);
};

