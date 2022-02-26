#pragma once
#include "CObject.h"
class CItem : public CObject
{
	float	fTimer;			// 1�� ī��Ʈ �ؼ� �ٸ� ���鿡 �����ַ���
	UINT	uiDuration;		// ������ ���ӽð� (float���� UINT�� ��� ���� �� ���Ƽ�)

public:
	CItem();
	virtual ~CItem();

	void setTimer(float time);
	void setDuration(UINT dura);

	float	getTimer();
	UINT	getDuration();

	void setRandPos();

	// 2�� ���� �����Լ� �ǳ�
	virtual void update() = 0;
	virtual void render(HDC hDC) = 0;
};

