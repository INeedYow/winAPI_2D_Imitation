#pragma once
#include "CObject.h"
class CItem : public CObject
{
	float	fTimer;			// 1초 카운트 해서 다른 값들에 영향주려고
	UINT	uiDuration;		// 아이템 지속시간 (float보다 UINT가 계산 빠를 것 같아서)
	bool	isFlick;		// 사라지기 전 깜빡임

	UCHAR	ucKey;			// 아이템 고유번호(구별용)
	
public:
	CItem();
	virtual ~CItem();

	void	setTimer(float time);
	void	setDuration(UINT dura);
	void	setIsFlick(bool flick);
	void	setKey(UCHAR key);

	float	getTimer();
	UINT	getDuration();
	bool	getIsFlick();
	UCHAR	getKey();

	void setRandPos();

	// 2단 순수 가상함수 되네
	virtual void update() = 0;
	virtual void render(HDC hDC) = 0;
};

