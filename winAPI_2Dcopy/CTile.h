#pragma once
#include "CObject.h"
class CTile : public CObject
{
	CTexture*	m_pTex;
	int			m_iIdx;		// index

public:
	const static int SIZE_TILE = 32;		// #define�� ����� �뵵

	CTile();
	virtual ~CTile();

	virtual void update();
	virtual void render(HDC hDC);

	void setTexture(CTexture* pTex);
};

// Ÿ���� ���� 2^n ũ��� ���� ũ��� �����
// �׷��� index�� ��������