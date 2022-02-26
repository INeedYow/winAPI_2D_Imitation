#pragma once
#include "CObject.h"
class CBullet : public CObject
{
	fVec2	m_fvDir;
	float	m_fSpeed;

	// TODO 임시 테스트용 나중에 지울 것
	// 아직 옵젝 지우는 걸 못해서 총알 맞추면 안 그려지게 하는 용도
	// 지우는 거 그냥 해당 이터레이터로 옵젝 지우면 될 것 같긴 한데
	// 지우고 나서 벡터배열 한 칸씩 당겨주고
	bool isColl;

public:
	CBullet();
	CBullet(fPoint pos, fVec2 vec, float spd = (float)B_SPEED);
	virtual ~CBullet();

	virtual void update();
	virtual void render(HDC hDC);
};