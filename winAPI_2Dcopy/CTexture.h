#pragma once
#include "CResource.h"
class CTexture : public CResource
{
	HDC		m_hDC;
	HBITMAP	m_hBMP;
	BITMAP	m_bmpInfo;

public:
	CTexture();
	virtual ~CTexture();

	HDC		getDC();
	HBITMAP getBmp();
	BITMAP	getBmpInfo();

	UINT	getBmpWidth();
	UINT	getBmpHeight();

	void	load(const wstring& strPath);
};

