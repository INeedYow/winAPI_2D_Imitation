#pragma once
#include "CResource.h"
class CTexture :  public CResource
{
	HDC		m_hDC;			// 이미지니까 dc필요
	HBITMAP m_hBitmap;		// 그림 그릴 종이인가?
	BITMAP	m_bmpInfo;		// BITMAP 변수와 HBITMAP 변수의 차이는?
								// BITMAP은 f12해보면 정보들 들어있음
	// 얘네는 없음..?
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

