#pragma once
#include "CObject.h"
class CText : public CObject
{
	LPCWSTR			m_text;
	unsigned int	m_textSize;
	bool			m_isMove;

public:
	CText();
	CText(fPoint pos, LPCWSTR text, unsigned int size, bool isMove);
	virtual ~CText();
	
	// 필요하려나
	void setText(LPCWSTR text);
	void setTextSize(unsigned int size);

	LPCWSTR getText();

	virtual void update();
	virtual void render(HDC hDC);
};

