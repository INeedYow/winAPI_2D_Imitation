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
// TODO �Լ������� �̷� ���� �� ���� ��� ���� �ŷ�

CEffect::~CEffect()
{
}

void CEffect::update()
{
}

void CEffect::render(HDC hDC)
{
}
