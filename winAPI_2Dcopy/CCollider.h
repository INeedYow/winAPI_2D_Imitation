#pragma once

class CObject;

class CCollider
{
	friend class CObject;

	static UINT		s_uiID;				// 고유 키값 생성을 위한 static변수

	CObject*		m_pOwner;			// 주인
	fPoint			m_fpPos;
	fPoint			m_fpSize;
	fPoint			m_fpOffset;			// 유격, 편차
	UINT			m_uiCollCnt;		// 충돌 카운트

	SHAPE			m_eShape;			// 히트박스 모양 (원,사각형,점)
	
	UINT			m_uiID;				// 고유 키값(아이디) // 충돌여부 고유 키값으로 저장하고 찾기 위함

public:
	CCollider();
	CCollider(const CCollider& other);	// 고유 키값 유지하기 위해 기본 복사 생성자 재정의 (예외처리)
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

	CCollider& operator==(const CCollider& other) = delete;	// 못 쓰게

	//void update();				// 이 친구는 파이널 업데이트만
	virtual void finalUpdate();
	void render(HDC hDC);


	// 충돌 매니저에서 충돌 상태에 따라 호출해 줄 함수임
	void collisionKeep(CCollider* pOther);
	void collisionEnter(CCollider* pOther);
	void collisionExit(CCollider* pOther);
};

