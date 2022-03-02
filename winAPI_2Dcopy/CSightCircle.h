#pragma once
#include "CObject.h"
class CSightCircle : public CObject
{
	//UINT	minRange;		// 시야범위
	//UINT	maxRange;

	// 다른 객체 정보 얻는 방법이 없어서 이렇게 만들어도 쓸 방법이 없음
		// scene통해서 해당 객체에 접근해야 get함수든 뭐든 쓸텐데
		// 아니면 static이 만능?

public:
	CSightCircle();
	virtual ~CSightCircle();

	virtual void update();
	virtual void render(HDC hDC);
	
	//UINT getRange(bool mode);
};

