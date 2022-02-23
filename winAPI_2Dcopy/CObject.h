#pragma once
class CObject
{
	fPoint m_fptPos;
	fPoint m_fptSize;
	
public:
	CObject();
	CObject(fPoint pos, fPoint size);
	virtual ~CObject();

	// 멤버변수는 private으로 유지하고 세터 게터등 함수로 멤버에 접근하도록 하는 것이 디버그, 유지보수 등에서 편하다.
	void setPos(fPoint pos);
	void setSize(fPoint size);

	fPoint getPos();
	fPoint getSize();

	virtual void update() = 0;
	virtual void render(HDC hDC) = 0;
};

