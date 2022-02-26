#include "framework.h"
#include "CBullet.h"
#include "CScene.h"

CBullet::CBullet()
{
	setPos(fPoint(0.f,0.f));
	setSize(fPoint((float)B_SIZE, (float)B_SIZE));
	m_fvDir = fVec2(0.f, 0.f);
	m_fSpeed = (float)B_SPEED;

	// TODO 임시 테스트용 나중에 지울 것
	isColl = false;
}

CBullet::CBullet(fPoint pos, fVec2 vec, float spd)
{
	setPos(pos);
	setSize(fPoint((float)B_SIZE, (float)B_SIZE));
	m_fvDir = vec;
	m_fSpeed = spd;

	// TODO 임시 테스트용 나중에 지울 것
	isColl = false;
}

CBullet::~CBullet()
{
}

void CBullet::update()
{
	fPoint bulletPos = getPos();
	fPoint enemyPos;

	CScene* pCurScene = CSceneManager::getInst()->getCurScene();
	vector<CObject*>* pVecArr = pCurScene->getVecArr();

	// 씬이 가지고 있는 옵젝 배열 중 Enemy 인덱스에 있는 녀석들의 좌표를 받아서 충돌 여부 확인
	for (int i = 0; i < pVecArr[(int)OBJ::ENEMY].size(); i++)
	{	// 이게 되네;
		enemyPos = pVecArr[(int)OBJ::ENEMY][i]->getPos();
		
		if (bulletPos.COLL_PC(bulletPos, enemyPos, (int)O_HSIZE))
		{
			if(!isColl) g_resultKill++; // 임시로 총알 맞추기만 해도 kill count 증가하도록
			isColl = true;
			// TODO : 몬스터 총알에 맞았을 때 작업
		}
	}

	bulletPos.x += m_fSpeed * m_fvDir.x * DT;
	bulletPos.y += m_fSpeed * m_fvDir.y * DT;

	setPos(bulletPos);
}

void CBullet::render(HDC hDC)
{
	// TODO 임시 테스트용 나중에 지울 것 (충돌하면 안 그려지게 해놨음)
	if (isColl) return;

	int sight = ISMODE ? (int)P_SIGHTON : (int)P_SIGHTOFF;

	fPoint bulletPos = getPos();
	fPoint playerPos = GETPOS;

	if (bulletPos.COLL_PC(bulletPos, playerPos, sight))
	{	// 시야 범위 원 안에 총알이 위치하면 출력
		Ellipse(hDC,
			(int)(bulletPos.x - B_SIZE / 2),
			(int)(bulletPos.y - B_SIZE / 2),
			(int)(bulletPos.x + B_SIZE / 2),
			(int)(bulletPos.y + B_SIZE / 2));
	}
}
