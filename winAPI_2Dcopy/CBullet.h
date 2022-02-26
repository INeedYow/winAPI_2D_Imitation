#pragma once
#include "CObject.h"
class CBullet : public CObject
{
	fVec2	m_fvDir;
	float	m_fSpeed;

	// TODO �ӽ� �׽�Ʈ�� ���߿� ���� ��
	// ���� ���� ����� �� ���ؼ� �Ѿ� ���߸� �� �׷����� �ϴ� �뵵
	// ����� �� �׳� �ش� ���ͷ����ͷ� ���� ����� �� �� ���� �ѵ�
	// ����� ���� ���͹迭 �� ĭ�� ����ְ�
	bool isColl;

public:
	CBullet();
	CBullet(fPoint pos, fVec2 vec, float spd = (float)B_SPEED);
	virtual ~CBullet();

	virtual void update();
	virtual void render(HDC hDC);
};