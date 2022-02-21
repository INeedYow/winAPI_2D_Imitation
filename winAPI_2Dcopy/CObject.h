#pragma once
class CObject
{
	fPoint m_fptPos;
	fPoint m_fptSize;
	
public:
	CObject();
	CObject(fPoint pos, fPoint size);
	~CObject();

	// 세터 게터
		// Q. 가상함수, 순수 가상함수 알아보기
	virtual void setPos(fPoint pos);
	virtual void setSize(fPoint size);

	fPoint getPos();
	fPoint getSize();
};

