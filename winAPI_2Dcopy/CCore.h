#pragma once

class CCore
{
	SINGLETON(CCore);	// 생성자 소멸자 포함

private:
	HDC		m_hDC;
	HDC		m_hMemDC;
	HBITMAP	m_hBitMap;

public:
	void update();
	void render();
	void init();

	HDC getMainDC();
};

