#pragma once

union COLLIDER_ID
{
	struct {
		UINT left_id;
		UINT right_id;
	};
	ULONGLONG ID;
};

class CCollisionManager
{
	SINGLETON(CCollisionManager);
	
private:
	UINT	m_arrCollChk[(UINT)OBJ::SIZE];				// 비트연산으로
			//m_arrCollChk[OBJ::PLAYER] 에는 비트마다 해당 오브젝트enum class와 충돌 여부 0,1 저장

	map<ULONGLONG, bool> m_mapIsColl;						// 이전 프레임에 충돌했는지 저장하는 자료구조

	void collisionGroupUpdate(OBJ obj1, OBJ obj2);			// update 통해 내부적으로만 호출되는 함수라서 private
	bool isCollision(CCollider* pColl1, SHAPE shape1, CCollider* pColl2, SHAPE shape2); // 충돌여부 판정

public:
	void init();
	void update();
	
	void checkGroup(OBJ obj1, OBJ obj2);
	void unCheckGroup(OBJ obj1, OBJ obj2);
	void resetGroup();
};

// 그룹간 충돌 여부 설정할 수 있게 해주고 실제 충돌판정 해주는 역할 부여함

// 반복 시간 줄이기 위해 비트연산,
// 그마저도 대칭이므로 반만 확인하면 됨 
// 해당 비트만 1 : |
// 해당 비트만 0 : & ~

// 키 매니저 때처럼 충돌 시작, 충돌 중, 충돌 끝 구간 나눠서 처리하고 싶은데
// 그럼 이전 프레임에서의 충돌 상태?를 저장할 필요가 있고
// 그 방법으로 union과 static을 통한 고유 키값 저장하는 map자료형(탐색 장점)