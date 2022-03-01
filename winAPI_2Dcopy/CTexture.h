#pragma once
#include "CResource.h"
class CTexture :  public CResource
{
	HDC		m_hDC;			// �̹����ϱ� dc�ʿ�
	HBITMAP m_hBitmap;		// �׸� �׸� �����ΰ�?
	BITMAP	m_bmpInfo;		// BITMAP ������ HBITMAP ������ ���̴�?
								// BITMAP�� f12�غ��� ������ �������
	// ��״� ����..?
	//PEN	m_pen;
	//BRUSH m_brush;
	//FONT m_font;

public:
	CTexture();
	virtual ~CTexture();

	HDC		getDC();
	HBITMAP getBitmap();
	BITMAP	getBitInfo();

	int getBmpWidth();
	int getBmpHeight();

	void load(const wstring& strFilePath);
};

