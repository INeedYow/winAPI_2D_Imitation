#pragma once
#include "CScene.h"
class CScene_Result :  public CScene
{
	UINT		uiCount;		// 카운트
	float		fTimer;			// 시간
	LPCWSTR		szTextArr[5];	// 결과 출력할 텍스트들

public:
	CScene_Result();
	virtual ~CScene_Result();

	virtual void update();
	virtual void render(HDC hDC);

	virtual void enter();
	virtual void exit();
};