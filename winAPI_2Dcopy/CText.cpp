#include "framework.h"
#include "CText.h"

class CTimeManager;

CText::CText()
{
	setPos(fPoint(0, 0));
	setSize(fPoint(0, 0));
	m_text = L"";
	m_uiTextSize = 0;
}

CText::CText(fPoint pos, LPCWSTR text, UINT size)
{
	setPos(pos);
	setSize(fPoint(0, 0));
	m_text = text;
	m_uiTextSize = size;
}

CText::~CText()
{
}

void CText::setText(LPCWSTR text)
{
	m_text = text;
}

void CText::setTextSize(UINT size)
{
	m_uiTextSize = size;
}

LPCWSTR CText::getText()
{
	return m_text;
}

void CText::update()
{
}

void CText::render(HDC hDC)
{
	SetTextColor(hDC, ISMODE ? RGB(30, 30, 30) : RGB(15, 15, 15));
	
	SetBkMode(hDC, TRANSPARENT);	// 글자 배경 투명하게

	if (0 != m_uiTextSize)
	{
		HFONT hFont = CreateFont(m_uiTextSize, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Tahoma"));
		HFONT hOriginFont = (HFONT)SelectObject(hDC, hFont);

		TextOutW(hDC, (int)getPos().x, (int)getPos().y, m_text, (int)wcslen(m_text));

		SelectObject(hDC, hOriginFont);
		DeleteObject(hFont);
	}
	else
	{
		TextOutW(hDC, (int)getPos().x, (int)getPos().y, m_text, (int)wcslen(m_text));
	}

}
