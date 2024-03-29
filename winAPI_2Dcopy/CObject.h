#pragma once

class CCollider;
class CAnimator;

class CObject
{
	friend class CEventManager;
private:

	OBJNAME		m_eName;			// 충돌 대상의 종류를 알려면 필요함

	fPoint		m_fptPos;
	fPoint		m_fptSize;
	
	// 컴포넌트
	CCollider*	m_pCollider;
	CAnimator*	m_pAnimator;

	bool		m_bDead;			// 1프레임 유예
	void		setDead();			// 이벤트 매니저만 호출할 수 있도록 friend, private;

public:
	CObject();
	CObject(const CObject& other);
	virtual ~CObject();

	void setPos(fPoint pos);
	void setSize(fPoint size);
	void setName(OBJNAME name);

	fPoint	getPos();
	fPoint	getSize();
	OBJNAME	getName();

	bool isDead();

	virtual void update() = 0;
	virtual void finalUpdate() final;	// 오버라이딩 막음
	virtual void render(HDC hDC);
	virtual void componentRender(HDC hDC);

	CCollider* getCollider();
	void createCollider();				// 

	CAnimator* getAnimator();
	void createAnimator();


	// 충돌 매니저가 충돌체의 충돌상태 함수를 호출 해주는데 오브젝트의 종류에 따라 충돌에 대한 후처리가 달라져야 하니까
	// 충돌체의 Keep(),Enter(),Exit() 함수들이 각각 자신의 pOwner->Keep(),Enter(),Exit()을 호출하게 하는 방식으로 한다.
	// 자식이 반드시 구현해야 하는 경우는 아니므로 순수가상함수로는 안 쓰는듯
	virtual void collisionKeep(CCollider* pOther) {}	
	virtual void collisionEnter(CCollider* pOther) {}
	virtual void collisionExit(CCollider* pOther) {}

};

