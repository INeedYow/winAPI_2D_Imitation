#include "framework.h"
#include "CBullet.h"
#include "CScene.h"

CBullet::CBullet()
{
	setPos(fPoint(0.f,0.f));
	setSize(fPoint((float)B_SIZE, (float)B_SIZE));
	m_fvDir = fVec2(0.f, 0.f);
	m_fSpeed = (float)B_SPEED;

	// TODO �ӽ� �׽�Ʈ�� ���߿� ���� ��
	isColl = false;
}

CBullet::CBullet(fPoint pos, fVec2 vec, float spd)
{
	setPos(pos);
	setSize(fPoint((float)B_SIZE, (float)B_SIZE));
	m_fvDir = vec;
	m_fSpeed = spd;

	// TODO �ӽ� �׽�Ʈ�� ���߿� ���� ��
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

	// ���� ������ �ִ� ���� �迭 �� Enemy �ε����� �ִ� �༮���� ��ǥ�� �޾Ƽ� �浹 ���� Ȯ��
	for (int i = 0; i < pVecArr[(int)OBJ::ENEMY].size(); i++)
	{	// �̰� �ǳ�;
		enemyPos = pVecArr[(int)OBJ::ENEMY][i]->getPos();
		
		if (bulletPos.COLL_PC(bulletPos, enemyPos, (int)O_HSIZE))
		{
			if(!isColl) g_resultKill++; // �ӽ÷� �Ѿ� ���߱⸸ �ص� kill count �����ϵ���
			isColl = true;
			// TODO : ���� �Ѿ˿� �¾��� �� �۾�
		}
	}

	bulletPos.x += m_fSpeed * m_fvDir.x * DT;
	bulletPos.y += m_fSpeed * m_fvDir.y * DT;

	setPos(bulletPos);
}

void CBullet::render(HDC hDC)
{
	// TODO �ӽ� �׽�Ʈ�� ���߿� ���� �� (�浹�ϸ� �� �׷����� �س���)
	if (isColl) return;

	int sight = ISMODE ? (int)P_SIGHTON : (int)P_SIGHTOFF;

	fPoint bulletPos = getPos();
	fPoint playerPos = GETPOS;

	if (bulletPos.COLL_PC(bulletPos, playerPos, sight))
	{	// �þ� ���� �� �ȿ� �Ѿ��� ��ġ�ϸ� ���
		Ellipse(hDC,
			(int)(bulletPos.x - B_SIZE / 2),
			(int)(bulletPos.y - B_SIZE / 2),
			(int)(bulletPos.x + B_SIZE / 2),
			(int)(bulletPos.y + B_SIZE / 2));
	}
}
