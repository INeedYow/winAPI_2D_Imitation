#pragma once
class SelectGDI
{
	HDC		m_hDC;
	HBRUSH	m_hDefaultBrush;
	HPEN	m_hDefaultPen;
	HFONT	m_hDefaultFont;

public:
	SelectGDI(HDC hDC, BRUSH type)
	{
		m_hDC = hDC;
		HBRUSH hBrush = CCore::getInst()->getBrush(type);
		m_hDefaultBrush = (HBRUSH)SelectObject(hDC, hBrush);
	}
	// 시야 모드에 따라서 brush나 pen 다르게 쓰는 경우에 쓰려고 만들어봄
	SelectGDI(HDC hDC, BRUSH typeTrue, BRUSH typeFalse, bool mode)
	{
		m_hDC = hDC;
		HBRUSH hBrush; 

		if(mode)
			hBrush = CCore::getInst()->getBrush(typeTrue);
		else
			hBrush = CCore::getInst()->getBrush(typeFalse);

		m_hDefaultBrush = (HBRUSH)SelectObject(hDC, hBrush);
	}

	SelectGDI(HDC hDC, PEN type)
	{
		m_hDC = hDC;
		HPEN hPen = CCore::getInst()->getPen(type);
		m_hDefaultPen = (HPEN)SelectObject(hDC, hPen);
	}

	SelectGDI(HDC hDC, PEN typeTrue, PEN typeFalse, bool mode)
	{
		m_hDC = hDC;
		HPEN hPen;

		if (mode)
			hPen = CCore::getInst()->getPen(typeTrue);
		else
			hPen = CCore::getInst()->getPen(typeFalse);

		m_hDefaultPen = (HPEN)SelectObject(hDC, hPen);
	}

	SelectGDI(HDC hDC, FONT type/*, UINT size = 24*/)
	{
		m_hDC = hDC;
		HFONT hFont;

		/*if (24 != size)
			hFont = CreateFont(size, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Comic Sans MS"));
		else
			hFont = CCore::getInst()->getFont(type);*/

		hFont = CCore::getInst()->getFont(type);
		m_hDefaultFont = (HFONT)SelectObject(hDC, hFont);
		
	}
	~SelectGDI()
	{
		SelectObject(m_hDC, m_hDefaultBrush);
		SelectObject(m_hDC, m_hDefaultPen);
		SelectObject(m_hDC, m_hDefaultFont);
	}
};

