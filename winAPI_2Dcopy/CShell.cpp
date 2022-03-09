#include "framework.h"
#include "CShell.h"

CShell::CShell()
{
	setName(OBJNAME::SHELL);
	setSize(fPoint(MT_SIZEX - 6, MT_SIZEY - 4));
	m_fSpeed = 0.f;
	m_fvDir = {};

	m_pTex = loadTex(KEY_RES::TEX_KOOPA, L"texture\\koopa.bmp");

	createCollider();
	getCollider()->setSize(fPoint(MT_SIZEX - 8, MT_SIZEY - 6));
	getCollider()->setOffset(fPoint(0.f, 4.f));
	getCollider()->setShape(SHAPE::RECT);

	createAnimator();
}

CShell::~CShell()
{
}

void CShell::setDir(fVec2 dir)
{
}

void CShell::update()
{
}

void CShell::render(HDC hDC)
{
}

void CShell::collisionEnter(CCollider* pOther)
{
}
