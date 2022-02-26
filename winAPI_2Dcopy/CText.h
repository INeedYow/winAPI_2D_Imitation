#pragma once
#include "CObject.h"
class CText : public CObject
{
	LPCWSTR		m_text;
	UINT		m_uiTextSize;
	//UINT 		m_uiRGB;				// �ð� ������ ��Ʈ�������� ���� ����

public:
	CText();
	CText(fPoint pos, LPCWSTR text, UINT size);
	virtual ~CText();
	
	// �ʿ��Ϸ���
	void setText(LPCWSTR text);
	void setTextSize(UINT size);

	LPCWSTR getText();

	virtual void update();
	virtual void render(HDC hDC);
};

