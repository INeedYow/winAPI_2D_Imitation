#pragma once

class CCollider;

class CObject
{
	fPoint		m_fptPos;
	fPoint		m_fptSize;
	
	CCollider*	m_pCollider;		// 충돌체, 히트박스 // 컴포넌트, 부품 개념

public:
	CObject();
	virtual ~CObject();

	// 멤버변수는 private으로 유지하고 세터 게터등 함수로 멤버에 접근하도록 하는 것이 디버그, 유지보수 등에서 편하다.
	void setPos(fPoint pos);
	void setSize(fPoint size);

	fPoint getPos();
	fPoint getSize();

	virtual void update() = 0;
	virtual void finalUpdate() final;	// 오버라이딩 막음
	virtual void render(HDC hDC);
	virtual void componentRender(HDC hDC);

	CCollider* getCollider();
	void createCollider();				// 세터로 지정해주는 게 아니라 생성

};

