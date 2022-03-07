#include "framework.h"
#include "CCollisionManager.h"
#include "CScene.h"

CCollisionManager::CCollisionManager()
{
	m_arrCollChk[0] = 0;
}

CCollisionManager::~CCollisionManager()
{

}

// �浹�ϴ� OBJ�׷��� ������Ʈ�� ��θ� ���ؾ� �ϱ� ������ ������Ʈ �迭 �޾ƿ;� �Ѵ�.
// ���� ���� ������Ʈ�鸸 ������ �ǰ� ���� ���� �� �Ŵ����� �˰� �ִ�.
void CCollisionManager::collisionGroupUpdate(OBJ obj1, OBJ obj2)
{
	CScene* pCurScene = CSceneManager::getInst()->getCurScene();

	vector<CObject*> vec1 = pCurScene->getGroupObject(obj1);
	vector<CObject*> vec2 = pCurScene->getGroupObject(obj2);

	for (int i = 0; i < vec1.size(); i++)
	{
		if (nullptr == vec1[i]->getCollider())	continue;			// �浹ü ���� ���
		
		for (int j = 0; j < vec2.size(); j++)
		{
			if (nullptr == vec2[j]->getCollider()) continue;		// �浹ü ���� ���

			if (vec1[i] == vec2[j]) continue;						// vec[]�� CObject*�ϱ� �ּҰ� ���� ���(���� ��ü�� ���) ����ó��
		
			// ID�� Ű��
			COLLIDER_ID id;
			id.left_id = vec1[i]->getCollider()->getID();
			id.right_id = vec2[j]->getCollider()->getID();

			map<ULONGLONG, bool>::iterator iter = m_mapIsColl.find(id.ID);	// �ش� ���̵�� �� �ڷ������� ã��

			if (m_mapIsColl.end() == iter)							// �� ã������ ������ְ� ã��
			{	// map.insert(make_pair(ULONGLONG, bool);
				m_mapIsColl.insert(make_pair(id.ID, false));		// �⺻�� false;
				iter = m_mapIsColl.find(id.ID);
			}	// iter->second�� ���� ������ �浹 ���°� ������ ����

			

			if (isCollision(vec1[i]->getCollider(), vec1[i]->getCollider()->getShape(),
				vec2[j]->getCollider(), vec2[j]->getCollider()->getShape()))
			{	// ���� �浹 O
				if (iter->second)
				{	// ���� �浹 O // �� �浹ü���� �浹���¿� ���� �ٸ��� �˷��� �ʿ伺 (collider�� �Լ� �߰�)
					if (vec1[i]->isDead() || vec2[j]->isDead())
					{	// ���� O : �浹 ����
						vec1[i]->getCollider()->collisionExit(vec2[j]->getCollider());
						vec2[j]->getCollider()->collisionExit(vec1[i]->getCollider());
						iter->second = false;
					}
					else
					{	// ���� X : �浹 ���� ��
						vec1[i]->getCollider()->collisionKeep(vec2[j]->getCollider());
						vec2[j]->getCollider()->collisionKeep(vec1[i]->getCollider());
					}
					
				}
				else
				{	// ���� �浹 X
					if (!vec1[i]->isDead() && !vec2[j]->isDead())
					{	// ���� X : �浹 ����
						vec1[i]->getCollider()->collisionEnter(vec2[j]->getCollider());
						vec2[j]->getCollider()->collisionEnter(vec1[i]->getCollider());
						iter->second = true;
					}	
					// ���� O : �浹 ���� �� �� (else�� �ƹ� �͵� �� �ʿ����)
				}
			}
			else
			{	// ���� �浹 X
				if (iter->second)
				{	// ���� �浹 O : �浹 ���� (������ �ƴϵ� Ż���ϸ� ��)
					vec1[i]->getCollider()->collisionExit(vec2[j]->getCollider());
					vec2[j]->getCollider()->collisionExit(vec1[i]->getCollider());
					iter->second = false;
				}
				// else �� �浹�� �� ���� �浹�ϰ� ���� ���� ���´ϱ� �ƹ��͵� �� �ʿ� ����
			}
		}
	}
}

bool CCollisionManager::isCollision(CCollider* pColl1, SHAPE shape1, CCollider* pColl2, SHAPE shape2)
{
	fPoint pos1		= pColl1->getPos();
	fPoint size1	= pColl1->getSize();
	fPoint pos2		= pColl2->getPos();
	fPoint size2	= pColl2->getSize();

	switch (shape1)
	{
	case SHAPE::CIRCLE:
		switch (shape2)
		{
		case SHAPE::CIRCLE:
		{
			return ISCOLLCC(pos1, (int)(size1.x / 2), pos2, (int)(size2.x / 2));
		}
		case SHAPE::RECT:
		{
			RECT rt = { (int)pos2.x - (int)size2.x / 2, (int)pos2.y - (int)size2.y,
						(int)pos2.x + (int)size2.x / 2, (int)pos2.y + (int)size2.y };
			return ISCOLLCR(pos1,(int)(size1.x / 2), rt);
		}
		case SHAPE::POINT:
		{
			return ISCOLLPC(pos2, pos1, (int)(size1.x / 2));
		}
		}
		break;
		//
	case SHAPE::RECT:
		switch (shape2)
		{
		case SHAPE::CIRCLE:
		{
			RECT rt = { (int)pos1.x - (int)size1.x / 2, (int)pos1.y - (int)size1.y,
						(int)pos1.x + (int)size1.x / 2, (int)pos1.y + (int)size1.y };
			return ISCOLLCR(pos2, (int)(size2.x / 2), rt);
		}
		break;
		case SHAPE::RECT:
		{
			return ISCOLLRR(pos1, size1, pos2, size2);
		}
		case SHAPE::POINT:
		{
			RECT rt = { (int)pos1.x - (int)size1.x / 2, (int)pos1.y - (int)size1.y,
						(int)pos1.x + (int)size1.x / 2, (int)pos1.y + (int)size1.y };
			return ISCOLLPR(pos2, rt);
		}
		}
		//
	case SHAPE::POINT:
		switch (shape2)
		{
		case SHAPE::CIRCLE:
		{
			return ISCOLLPC(pos1, pos2, (int)(size2.x / 2));
		}
		case SHAPE::RECT:
		{
			RECT rt = { (int)pos2.x - (int)size2.x / 2, (int)pos2.y - (int)size2.y,
						(int)pos2.x + (int)size2.x / 2, (int)pos2.y + (int)size2.y };
			return ISCOLLPR(pos1, rt);
		}
		case SHAPE::POINT:
		{
			return (pos1 == pos2);
		}
		}
	}
	return false;
}

DIR CCollisionManager::dirCollision(CCollider* pColl1, SHAPE shape1, CCollider* pColl2, SHAPE shape2)
{
	fPoint pos1 = pColl1->getPos();
	fPoint size1 = pColl1->getSize();
	fPoint pos2 = pColl2->getPos();
	fPoint size2 = pColl2->getSize();
	
	return COLLRR(pos1, size1, pos2, size2);
}

void CCollisionManager::init()
{
}

// �浹 ���� üũ�� �׷츸 Ȯ���ϵ��� �з�
void CCollisionManager::update()
{
	for (int i = 0; i < (UINT)OBJ::SIZE; i++)
	{	// ������ �˻� �� �ص� �Ǵϱ� j = i���� ����
		for (int j = i; j < (UINT)OBJ::SIZE; j++)
		{	// �浹 ���� ��Ʈ�� ������ UINT m_arrCollChk[]�� 1�̸� ���� 
			if (m_arrCollChk[i] & (0x1 << j))
			{	// �ش� ��Ʈ�� 1���� (? & 1) �غ��� ��
				collisionGroupUpdate((OBJ)i, (OBJ)j);
			}
		}
	}
}

void CCollisionManager::checkGroup(OBJ obj1, OBJ obj2)
{
	UINT groupLow, group;

	groupLow = (UINT)obj1;
	group = (UINT)obj2;

	if ((UINT)obj1 > (UINT)obj2)
	{
		groupLow = (UINT)obj2;
		group = (UINT)obj1;
	}

	// �ش� ��Ʈ�� 1�� �����
	m_arrCollChk[(UINT)groupLow] |= (0x1 << group);
}

void CCollisionManager::unCheckGroup(OBJ obj1, OBJ obj2)
{
	UINT groupLow, group;

	groupLow = (UINT)obj1;
	group = (UINT)obj2;

	if ((UINT)obj1 > (UINT)obj2)
	{
		groupLow = (UINT)obj2;
		group = (UINT)obj1;
	}

	// �ش� ��Ʈ�� 0���� �����
	m_arrCollChk[(UINT)groupLow] &= ~(0x1 << group);
}

void CCollisionManager::resetGroup()
{	// (void* Dst, int Val,  size_t Size) // �����ּ�, �Է��� ��, ������
	memset(m_arrCollChk, 0, sizeof(UINT) * (UINT)OBJ::SIZE);			// �ݺ��� ���� �ͺ��� �ſ� ����
}
