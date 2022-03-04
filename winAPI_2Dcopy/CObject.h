#pragma once

class CCollider;

class CObject
{
	friend class CEventManager;
private:
	bool		m_bDead;			// 1������ ����
	void		setDead();			// �̺�Ʈ �Ŵ����� ȣ���� �� �ֵ��� friend, private;

	OBJ			m_eType;			// �浹 ����� ������ �˷��� �ʿ���

	fPoint		m_fptPos;
	fPoint		m_fptSize;
	
	CCollider*	m_pCollider;		// ������Ʈ �浹ü

public:
	CObject();
	CObject(const CObject& other);
	virtual ~CObject();

	void setPos(fPoint pos);
	void setSize(fPoint size);
	void setType(OBJ type);

	fPoint	getPos();
	fPoint	getSize();
	OBJ		getType();

	bool isDead();

	virtual void update() = 0;
	virtual void finalUpdate() final;	// �������̵� ����
	virtual void render(HDC hDC);
	virtual void componentRender(HDC hDC);

	CCollider* getCollider();
	void createCollider();				// 

	// �浹 �Ŵ����� �浹ü�� �浹���� �Լ��� ȣ�� ���ִµ� ������Ʈ�� ������ ���� �浹�� ���� ��ó���� �޶����� �ϴϱ�
	// �浹ü�� Keep(),Enter(),Exit() �Լ����� ���� �ڽ��� pOwner->Keep(),Enter(),Exit()�� ȣ���ϰ� �ϴ� ������� �Ѵ�.
	virtual void collisionKeep(CCollider* pOther) {}	// ������ �뵵..
	virtual void collisionEnter(CCollider* pOther) {}
	virtual void collisionExit(CCollider* pOther) {}

};

