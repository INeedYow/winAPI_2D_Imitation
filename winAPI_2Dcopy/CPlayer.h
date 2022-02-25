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

// 물리법칙 쓸만한 게 없는데
	// 가속도 적용 가능할까