#pragma once

class CCore
{
	SINGLETON(CCore);	// ������ �Ҹ��� ����

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

