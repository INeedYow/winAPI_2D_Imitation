#pragma once

class CObject;

class CCollider
{
	friend class CObject;

	CObject*		pOwner;			// ����
	fPoint			fpPos;
	fPoint			fpSize;
	fPoint			fpOffset;		// ����, ���� �̷� �����ε�

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

	//void update();				// ��ģ���� ���̳� ������Ʈ��
	virtual void finalUpdate();
	void render(HDC hDC);
};

