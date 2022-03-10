#include "framework.h"
#include "CTile.h"
#include "CTexture.h"

CTile::CTile()
{
	m_pTex = nullptr;
	m_iIdx = 0;
	setSize(fPoint(SIZE_TILE, SIZE_TILE));
}

CTile::~CTile()
{
}

void CTile::update()
{
}

void CTile::render(HDC hDC)
{
	if (nullptr == m_pTex) return;

	// �ؽ��� ���� ���� ����
	UINT iWidth = m_pTex->getBmpWidth();
	UINT iHeight = m_pTex->getBmpHeight();

	// ���� ���� �ε��� ��
	UINT iMaxX = iWidth / SIZE_TILE;
	UINT iMaxY = iHeight / SIZE_TILE;

	// ���� x,y �ε��� ���� ������ ���� Ȱ�� (Ÿ���� lefttop ��ǥ)
		// ���� X = index�� �ִ� X������ŭ ���� �� �� ���Ҵ���
	UINT iCurX = m_iIdx % iMaxX;
		// ���� Y = index�� �ִ� x������ŭ�� �� �� ä������
	UINT iCurY = (m_iIdx / iMaxX) % iMaxY;

	fPoint rendPos = getRendPos(getPos());
	fPoint size = getSize();

	TransparentBlt(hDC,
		(int)(rendPos.x),
		(int)(rendPos.y),
		(int)(size.x),
		(int)(size.y),
		m_pTex->getDC(),
		(int)(iCurX * SIZE_TILE),
		(int)(iCurY * SIZE_TILE),
		(int)(size.x),
		(int)(size.y),
		RGB(255, 0, 255));
}

void CTile::setTexture(CTexture* pTex)
{
	m_pTex = pTex;
}
