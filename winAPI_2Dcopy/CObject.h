#pragma once
class CObject
{
	fPoint m_fptPos;
	fPoint m_fptSize;
	
public:
	CObject();
	CObject(fPoint pos, fPoint size);
	~CObject();

	// ���� ����
		// Q. �����Լ�, ���� �����Լ� �˾ƺ���
	virtual void setPos(fPoint pos);
	virtual void setSize(fPoint size);

	fPoint getPos();
	fPoint getSize();
};

