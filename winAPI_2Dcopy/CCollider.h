#pragma once

class CObject;

class CCollider
{
	friend class CObject;

	CObject*		pOwner;			// 주인
	fPoint			fpPos;
	fPoint			fpSize;
	fPoint			fpOffset;		// 유격, 편차 이런 느낌인듯

public:
	CCollider();
	virtual ~CCollider();

	void setPos(fPoint pos);
	void setSize(fPoint size);
	void setOffset(fPoint offset);

	fPoint		 getPos();
	fPoint		 getSize();
	fPoint		 getOffset();
	CObject*	 getOwner();

	//void update();				// 이친구는 파이널 업데이트만
	virtual void finalUpdate();
	void render(HDC hDC);
};

