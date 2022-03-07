#include "framework.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CObject.h"
#include "CTexture.h"

CAnimation::CAnimation()
{
	m_strName	= L"";
	m_pAnimator = nullptr;
	m_pTex		= nullptr;
	m_uiCurFrm	= 0;
	m_fTimer	= 0.f;
}

CAnimation::~CAnimation()
{
}

void CAnimation::setName(const wstring& strName)
{
	m_strName = strName;
}

const wstring& CAnimation::getName()
{
	return m_strName;
}

void CAnimation::setFrame(UINT frmIndex)
{
	m_uiCurFrm = frmIndex;
}

tAniFrm& CAnimation::getFrame(UINT frmIndex)
{
	return m_vecFrm[frmIndex];
}

void CAnimation::update()
{
	m_fTimer += fDT;

	if (m_vecFrm[m_uiCurFrm].fDuration < m_fTimer)
	{
		m_uiCurFrm++;
		m_uiCurFrm %= m_vecFrm.size();		// 순환하도록 (나머지 연산활용)
		m_fTimer = 0.f;
	}
}

void CAnimation::render(HDC hDC)
{
	CObject* pObj = m_pAnimator->getOwner();
	fPoint pos = pObj->getPos();
	tAniFrm frm = m_vecFrm[m_uiCurFrm];

	pos = pos + frm.fpOffset;
	pos = getRendPos(pos);

	TransparentBlt(hDC,
		(int)(pos.x - frm.fpSlice.x / 2.f),
		(int)(pos.y - frm.fpSlice.y / 2.f),
		(int)(frm.fpSlice.x),
		(int)(frm.fpSlice.y),
		m_pTex->getDC(),
		(int)(frm.fpLeftTop.x),
		(int)(frm.fpLeftTop.y),
		(int)(frm.fpSlice.x),
		(int)(frm.fpSlice.y),
		RGB(255, 0, 255));
}

void CAnimation::create(CTexture* pTex, fPoint leftTop, fPoint slice, 
	fPoint step, float dura, UINT frmCnt)
{
	m_pTex = pTex;

	tAniFrm frm = {};
	for (UINT i = 0; i < frmCnt; i++)
	{
		frm.fDuration = dura;
		frm.fpSlice = slice;
		frm.fpLeftTop = leftTop + step * i;

		m_vecFrm.push_back(frm);
	}
}
