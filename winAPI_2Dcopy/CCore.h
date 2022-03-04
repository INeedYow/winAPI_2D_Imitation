#pragma once

class CCore
{
	SINGLETON(CCore);	// 생성자 소멸자 포함

private:
	HDC		m_hDC;
	HDC		m_hMemDC;
	HBITMAP	m_hBitMap;

	// GDI
	HBRUSH	m_arrBrush[(UINT)TYPE_BRUSH::SIZE];
	HPEN	m_arrPen[(UINT)TYPE_PEN::SIZE];
	HFONT	m_arrFont[(UINT)TYPE_FONT::SIZE];

public:
	void update();
	void render();
	void init();

	void	CreateBrushPenFont();
	HBRUSH	getBrush(BRUSH type);
	HPEN	getPen(PEN type);
	HFONT	getFont(FONT type);

	HDC		getMainDC();
};

