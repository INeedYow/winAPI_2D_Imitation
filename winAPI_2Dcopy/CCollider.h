#pragma once

class CObject;

class CCollider
{
	friend class CObject;

	static UINT		s_uiID;				// 

	CObject*		m_pOwner;			// ����
	fPoint			m_fpPos;
	fPoint			m_fpSize;
	fPoint			m_fpOffset;			// ����, ���� �̷� �����ε�
	
	SHAPE			m_eShape;			// ��Ʈ�ڽ� ��� (������ �簢������)
											// bool�� �Ϸ��ٰ� Ȥ�� Ÿ���̳� ��Ÿ �ٸ� ��찡 ���� �� ���� �� ���Ƽ�
	
	UINT			m_uiID;				// ���� Ű��(���̵�) // �浹���� ���� Ű������ �����ϰ� ã�� ����

public:
	CCollider();
	CCollider(const CCollider& other);	// ���� Ű�� �����ϱ� ���� �⺻ ���� ������ ������ (����ó��)
	virtual ~CCollider();

	void setPos(fPoint pos);
	void setSize(fPoint size);
	void setOffset(fPoint offset);
	void setShape(SHAPE shape);

	fPoint		getPos();
	fPoint		getSize();
	fPoint		getOffset();
	CObject*	getOwner();
	SHAPE		getShape();
	UINT		getID();

	CCollider& operator==(const CCollider& other) = delete;	// �� ����

	//void update();				// �� ģ���� ���̳� ������Ʈ��
	virtual void finalUpdate();
	void render(HDC hDC);


	// �浹 �Ŵ������� �浹 ���¿� ���� ȣ���� �� �Լ���
	void collisionKeep(CCollider* pOther);
	void collisionEnter(CCollider* pOther);
	void collisionExit(CCollider* pOther);


};

