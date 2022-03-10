#include "framework.h"
#include "CEffect.h"

CEffect::CEffect()
{
	setName(OBJNAME::EFFECT);

	m_fGravity = O_GRAV;
	m_fvDir = {};

	m_pTex = nullptr;
	vFunc = nullptr;

}
// TODO 함수포인터 이럴 때는 못 쓰나 어떻게 쓰는 거래

CEffect::~CEffect()
{
}

void CEffect::update()
{
}

void CEffect::render(HDC hDC)
{
}
