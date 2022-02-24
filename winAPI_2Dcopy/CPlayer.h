#pragma once
#include "CObject.h"
class CPlayer : public CObject
{
	float fSpeed;
	
	//static bool isDarkMode;

public:
	CPlayer();
	~CPlayer();

	virtual void update();
	virtual void render(HDC hDC);

	//bool getIsMode();
};

// 물리법칙 쓸만한 게 없는데
// 가속도 적용 가능할까

// isDarkMode를 플레이어만 변경할 수 있으면서 
// 다른 오브젝트들이 bool 값에 따라 영향을 받게 하고 싶어서
// 정적 멤버 변수로 쓰려고 했는데 확인할 수 없는 외부기호라고 링크 에러가 뜸