#pragma once
#include "CObject.h"
class CSightCircle : public CObject
{
	//UINT	minRange;		// �þ߹���
	//UINT	maxRange;

	// �ٸ� ��ü ���� ��� ����� ��� �̷��� ���� �� ����� ����
		// scene���ؼ� �ش� ��ü�� �����ؾ� get�Լ��� ���� ���ٵ�
		// �ƴϸ� static�� ����?

public:
	CSightCircle();
	virtual ~CSightCircle();

	virtual void update();
	virtual void render(HDC hDC);
	
	//UINT getRange(bool mode);
};

