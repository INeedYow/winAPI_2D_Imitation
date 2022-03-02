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
	UINT	m_arrCollChk[(UINT)OBJ::SIZE];				// ��Ʈ��������
			//m_arrCollChk[OBJ::PLAYER] ���� ��Ʈ���� �ش� ������Ʈenum class�� �浹 ���� 0,1 ����

	map<ULONGLONG, bool> m_mapIsColl;						// ���� �����ӿ� �浹�ߴ��� �����ϴ� �ڷᱸ��

	void collisionGroupUpdate(OBJ obj1, OBJ obj2);			// update ���� ���������θ� ȣ��Ǵ� �Լ��� private
	bool isCollision(CCollider* pColl1, SHAPE shape1, CCollider* pColl2, SHAPE shape2); // �浹���� ����

public:
	void init();
	void update();
	
	void checkGroup(OBJ obj1, OBJ obj2);
	void unCheckGroup(OBJ obj1, OBJ obj2);
	void resetGroup();
};

// �׷찣 �浹 ���� ������ �� �ְ� ���ְ� ���� �浹���� ���ִ� ���� �ο���

// �ݺ� �ð� ���̱� ���� ��Ʈ����,
// �׸����� ��Ī�̹Ƿ� �ݸ� Ȯ���ϸ� �� 
// �ش� ��Ʈ�� 1 : |
// �ش� ��Ʈ�� 0 : & ~

// Ű �Ŵ��� ��ó�� �浹 ����, �浹 ��, �浹 �� ���� ������ ó���ϰ� ������
// �׷� ���� �����ӿ����� �浹 ����?�� ������ �ʿ䰡 �ְ�
// �� ������� union�� static�� ���� ���� Ű�� �����ϴ� map�ڷ���(Ž�� ����)