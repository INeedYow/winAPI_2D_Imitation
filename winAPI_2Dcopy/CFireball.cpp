#include "framework.h"
#include "CFireball.h"

CFireball::CFireball()
{
	setPos(fPoint(0.f, 0.f));
	setSize(fPoint ((float)FB_SIZE, (float)FB_SIZE));
	setType(OBJ::FIREBALL);
	m_fSpeed	= (float)FB_SPD;
	m_fDuration = (float)FB_DUR;
	m_fvDir		= {};
	m_fGravity = 0.f;

	createCollider();
	getCollider()->setSize(fPoint((float)FB_SIZE, (float)FB_SIZE));
	getCollider()->setOffset(fPoint(0.f, 0.f));
	getCollider()->setShape(SHAPE::RECT);
}

CFireball::~CFireball()
{
}

void CFireball::setDir(fVec2 dir)
{
	m_fvDir = dir.normalize();
}

// 사라지는 조건은?
// 맵 밖으로 나가거나 (몬스터랑 충돌, 벽에 부딪히거나) 지속시간? //-> (충돌에서 처리)
void CFireball::update()
{
	m_fDuration -= fDT;

	if (m_fDuration <= 0.f)
		deleteObj(this);

	fPoint pos = getPos();
	
	if (m_fGravity < (float)FB_GRAVMAX)
		m_fGravity += FB_GRAV * fDT;

	pos.x += m_fSpeed * m_fvDir.x * fDT;
	pos.y += m_fSpeed * m_fvDir.y * fDT + m_fGravity * fDT;

	setPos(pos);
}

void CFireball::render(HDC hDC)
{
	componentRender(hDC);
}

void CFireball::collisionEnter(CCollider* pOther)
{
	
}