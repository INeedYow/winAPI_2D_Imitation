#include "framework.h"
#include "CText.h"

class CTimeManager;

CText::CText()
{
	setPos(fPoint(0, 0));
	setSize(fPoint(0, 0));
	m_text = L"";
	m_textSize = 0;
	m_isMove = false;
}

CText::CText(fPoint pos, LPCWSTR text, unsigned int size, bool isMove)
{
	setPos(pos);
	setSize(fPoint(0, 0));
	m_text = text;
	m_textSize = size;
	m_isMove = isMove;
}

CText::~CText()
{
}

void CText::setText(LPCWSTR text)
{
	m_text = text;
}

void CText::setTextSize(unsigned int size)
{
	m_textSize = size;
}

LPCWSTR CText::getText()
{
	return m_text;
}

void CText::update()
{
	if (m_isMove)
	{
		fPoint textPos = getPos();

		if (KEY_HOLD(VK_UP)		&& textPos.y > -26)
			textPos.y -= P_SPEED * DT;

		if (KEY_HOLD(VK_DOWN)		&& textPos.y < WINSIZEY - 74)
			textPos.y += P_SPEED * DT;

		if (KEY_HOLD(VK_LEFT)		&& textPos.x > -76)
			textPos.x -= P_SPEED * DT;

		if (KEY_HOLD(VK_RIGHT)	&& textPos.x < WINSIZEX - 124)
			textPos.x += P_SPEED * DT;

		setPos(textPos);
	}
}

void CText::render(HDC hDC)
{
	SetTextColor(hDC, ISMODE ? BLACK : WHITE);
	
	SetBkMode(hDC, TRANSPARENT);	// 글자 배경 투명하게

	if (0 != m_textSize)
	{
		HFONT hFont = CreateFont(m_textSize, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Tahoma"));
		HFONT hOriginFont = (HFONT)SelectObject(hDC, hFont);

		TextOutW(hDC, getPos().x, getPos().y, m_text, wcslen(m_text));

		SelectObject(hDC, hOriginFont);
		DeleteObject(hFont);
	}
	else
	{
		TextOutW(hDC, getPos().x, getPos().y, m_text, wcslen(m_text));
	}

}
