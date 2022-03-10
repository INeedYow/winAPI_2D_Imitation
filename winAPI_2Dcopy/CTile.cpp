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

	// 텍스쳐 가로 세로 길이
	UINT iWidth = m_pTex->getBmpWidth();
	UINT iHeight = m_pTex->getBmpHeight();

	// 가로 세로 인덱스 수
	UINT iMaxX = iWidth / SIZE_TILE;
	UINT iMaxY = iHeight / SIZE_TILE;

	// 현재 x,y 인덱스 값은 나머지 연산 활용 (타일의 lefttop 좌표)
		// 현재 X = index가 최대 X개수만큼 돌고 몇 개 남았는지
	UINT iCurX = m_iIdx % iMaxX;
		// 현재 Y = index가 최대 x개수만큼을 몇 번 채웠는지
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
