#pragma once

class CCollider;

class CObject
{
	fPoint		m_fptPos;
	fPoint		m_fptSize;
	
	CCollider*	m_pCollider;		// �浹ü, ��Ʈ�ڽ� // ������Ʈ, ��ǰ ����

public:
	CObject();
	virtual ~CObject();

	// ��������� private���� �����ϰ� ���� ���͵� �Լ��� ����� �����ϵ��� �ϴ� ���� �����, �������� ��� ���ϴ�.
	void setPos(fPoint pos);
	void setSize(fPoint size);

	fPoint getPos();
	fPoint getSize();

	virtual void update() = 0;
	virtual void finalUpdate() final;	// �������̵� ����
	virtual void render(HDC hDC);
	virtual void componentRender(HDC hDC);

	CCollider* getCollider();
	void createCollider();				// ���ͷ� �������ִ� �� �ƴ϶� ����

};

