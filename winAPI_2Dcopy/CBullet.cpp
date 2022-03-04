#include "framework.h"
#include "CBullet.h"
#include "CScene.h"
#include "SelectGDI.h"

CBullet::CBullet()
{
	setPos(fPoint(0.f,0.f));
	setSize(fPoint((float)B_SIZE, (float)B_SIZE));
	m_fvDir = fVec2(0.f, 0.f);
	m_fSpeed = (float)B_SPEED;

	createCollider();
	getCollider()->setSize(fPoint((float)B_SIZE, (float)B_SIZE));
	getCollider()->setOffset(fPoint((float)0, (float)0));
	getCollider()->setShape(SHAPE::CIRCLE);
}

CBullet::CBullet(fPoint pos, fVec2 vec, float spd)
{
	setPos(pos);
	setSize(fPoint((float)B_SIZE, (float)B_SIZE));
	m_fvDir = vec;
	m_fSpeed = spd;

	createCollider();
	getCollider()->setSize(fPoint((float)B_SIZE, (float)B_SIZE));
	getCollider()->setOffset(fPoint((float)0, (float)0));
	getCollider()->setShape(SHAPE::CIRCLE);
}

CBullet::~CBullet()
{
}

void CBullet::update()
{
	fPoint bulletPos = getPos();
	fPoint enemyPos;

	CScene* pCurScene = CSceneManager::getInst()->getCurScene();

	bulletPos.x += m_fSpeed * m_fvDir.x * fDT;
	bulletPos.y += m_fSpeed * m_fvDir.y * fDT;

	setPos(bulletPos);
}

void CBullet::render(HDC hDC)
{
	int sight = ISMODE ? (int)P_SIGHTON : (int)P_SIGHTOFF;

	fPoint bulletPos = getPos();
	fPoint playerPos = GETPOS;

	if (ISCOLLPC(bulletPos, playerPos, sight))
	{	// 시야 범위 원 안에 총알이 위치하면 출력
		SelectGDI pen(hDC, PEN::GREEN);
		SelectGDI brush(hDC, BRUSH::HOLLOW);
		Ellipse(hDC,
			(int)(bulletPos.x - B_SIZE / 2),
			(int)(bulletPos.y - B_SIZE / 2),
			(int)(bulletPos.x + B_SIZE / 2),
			(int)(bulletPos.y + B_SIZE / 2));
	}

	componentRender(hDC);
}
