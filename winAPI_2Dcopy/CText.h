#pragma once
#include "CObject.h"
class CText : public CObject
{
	LPCWSTR		m_text;
	UINT		m_uiTextSize;
	//UINT 		m_uiRGB;				// 시간 남으면 비트연산으로 색상 도전

public:
	CText();
	CText(fPoint pos, LPCWSTR text, UINT size);
	virtual ~CText();
	
	// 필요하려나
	void setText(LPCWSTR text);
	void setTextSize(UINT size);

	LPCWSTR getText();

	virtual void update();
	virtual void render(HDC hDC);
};

