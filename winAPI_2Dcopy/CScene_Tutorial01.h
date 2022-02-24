#pragma once
#include "CScene.h"
class CScene_Tutorial01 : public CScene
{
	//unsigned int m_uiPage;

public:
	CScene_Tutorial01();
	virtual ~CScene_Tutorial01();

	//virtual void update();

	virtual void enter();
	virtual void exit();
};

// 튜토리얼을 여러 단계로 나눠보고 싶었는데 이 경우
// 1) 페이지 변수를 두고 한 클래스 내에서 처리하는 게 나은지
// 2) 여러 튜토리얼 클래스를 만들고 씬 전환하게 만드는 게 나은지
// 고민인데 일단 2번으로 진행

// update()랑 render()는 virtual로 받아쓰면 
// 부모의 해당 씬 모든 옵젝 update, render 함수 돌려주는 기능 잃음