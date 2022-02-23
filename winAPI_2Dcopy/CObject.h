#pragma once
class CObject
{
	fPoint m_fptPos;
	fPoint m_fptSize;
	
public:
	CObject();
	CObject(fPoint pos, fPoint size);
	virtual ~CObject();

	// ��������� private���� �����ϰ� ���� ���͵� �Լ��� ����� �����ϵ��� �ϴ� ���� �����, �������� ��� ���ϴ�.
	void setPos(fPoint pos);
	void setSize(fPoint size);

	fPoint getPos();
	fPoint getSize();

	virtual void update() = 0;
	virtual void render(HDC hDC) = 0;
};

