#pragma once
#include "CObject.h"
class CPlayer : public CObject
{
	static bool isDarkMode;

protected:
	float fSpeed;

public:
	CPlayer();
	virtual ~CPlayer();

	virtual void update();
	virtual void render(HDC hDC);

	static bool getMode();
};

// ������Ģ ������ �� ���µ�
	// ���ӵ� ���� �����ұ�