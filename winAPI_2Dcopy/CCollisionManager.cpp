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

// 충돌하는 OBJ그룹의 오브젝트들 모두를 비교해야 하기 때문에 오브젝트 배열 받아와야 한다.
// 현재 씬의 오브젝트들만 있으면 되고 현재 씬은 씬 매니저가 알고 있다.
void CCollisionManager::collisionGroupUpdate(OBJ obj1, OBJ obj2)
{
	CScene* pCurScene = CSceneManager::getInst()->getCurScene();

	vector<CObject*> vec1 = pCurScene->getGroupObject(obj1);
	vector<CObject*> vec2 = pCurScene->getGroupObject(obj2);

	for (int i = 0; i < vec1.size(); i++)
	{
		if (nullptr == vec1[i]->getCollider())	continue;			// 충돌체 없는 경우
		
		for (int j = 0; j < vec2.size(); j++)
		{
			if (nullptr == vec2[j]->getCollider()) continue;		// 충돌체 없는 경우

			if (vec1[i] == vec2[j]) continue;						// vec[]가 CObject*니까 주소가 같은 경우(같은 객체인 경우) 예외처리
		
			// ID로 키값
			COLLIDER_ID id;
			id.left_id = vec1[i]->getCollider()->getID();
			id.right_id = vec2[j]->getCollider()->getID();

			map<ULONGLONG, bool>::iterator iter = m_mapIsColl.find(id.ID);	// 해당 아이디로 맵 자료형에서 찾음

			if (m_mapIsColl.end() == iter)							// 못 찾았으면 만들어주고 찾기
			{	// map.insert(make_pair(ULONGLONG, bool);
				m_mapIsColl.insert(make_pair(id.ID, false));		// 기본은 false;
				iter = m_mapIsColl.find(id.ID);
			}	// iter->second에 이전 프레임 충돌 상태값 가지고 있음

			

			if (isCollision(vec1[i]->getCollider(), vec1[i]->getCollider()->getShape(),
				vec2[j]->getCollider(), vec2[j]->getCollider()->getShape()))
			{	// 현재 충돌 O
				if (iter->second)
				{	// 이전 충돌 O // 각 충돌체에게 충돌상태에 따라 다르게 알려줄 필요성 (collider에 함수 추가)
					if (vec1[i]->isDead() || vec2[j]->isDead())
					{	// 유예 O : 충돌 해제
						vec1[i]->getCollider()->collisionExit(vec2[j]->getCollider());
						vec2[j]->getCollider()->collisionExit(vec1[i]->getCollider());
						iter->second = false;
					}
					else
					{	// 유예 X : 충돌 진행 중
						vec1[i]->getCollider()->collisionKeep(vec2[j]->getCollider());
						vec2[j]->getCollider()->collisionKeep(vec1[i]->getCollider());
					}
					
				}
				else
				{	// 이전 충돌 X
					if (!vec1[i]->isDead() && !vec2[j]->isDead())
					{	// 유예 X : 충돌 진입
						vec1[i]->getCollider()->collisionEnter(vec2[j]->getCollider());
						vec2[j]->getCollider()->collisionEnter(vec1[i]->getCollider());
						iter->second = true;
					}	
					// 유예 O : 충돌 진입 안 함 (else는 아무 것도 할 필요없음)
				}
			}
			else
			{	// 현재 충돌 X
				if (iter->second)
				{	// 이전 충돌 O : 충돌 종료 (유예든 아니든 탈출하면 됨)
					vec1[i]->getCollider()->collisionExit(vec2[j]->getCollider());
					vec2[j]->getCollider()->collisionExit(vec1[i]->getCollider());
					iter->second = false;
				}
				// else 는 충돌한 적 없고 충돌하고 있지 않은 상태니까 아무것도 할 필요 없음
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

// 충돌 여부 체크된 그룹만 확인하도록 분류
void CCollisionManager::update()
{
	for (int i = 0; i < (UINT)OBJ::SIZE; i++)
	{	// 절반은 검사 안 해도 되니까 j = i부터 시작
		for (int j = i; j < (UINT)OBJ::SIZE; j++)
		{	// 충돌 여부 비트로 저장한 UINT m_arrCollChk[]가 1이면 판정 
			if (m_arrCollChk[i] & (0x1 << j))
			{	// 해당 비트가 1인지 (? & 1) 해보면 됨
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

	// 해당 비트만 1로 만들기
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

	// 해당 비트만 0으로 만들기
	m_arrCollChk[(UINT)groupLow] &= ~(0x1 << group);
}

void CCollisionManager::resetGroup()
{	// (void* Dst, int Val,  size_t Size) // 시작주소, 입력할 값, 사이즈
	memset(m_arrCollChk, 0, sizeof(UINT) * (UINT)OBJ::SIZE);			// 반복문 도는 것보다 매우 빠름
}
