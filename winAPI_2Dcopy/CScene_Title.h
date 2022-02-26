#pragma once
#include "CScene.h"
class CScene_Title : public CScene
{
	float	m_fCount;			// 1초 누적 카운트용
	bool	m_isChange;			// text출력 여부 결정할 변수

	unsigned char	m_ucColorR;			// RGB에 넣을 변수
	unsigned char	m_ucColorG;
	unsigned char	m_ucColorB;	

public:
	CScene_Title();
	virtual ~CScene_Title();

	virtual void update();
	virtual void render(HDC hDC);

	virtual void enter();
	virtual void exit();

};

