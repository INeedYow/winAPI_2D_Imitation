#include "framework.h"
#include "CTexture.h"

CTexture::CTexture()
{
	m_hDC = 0;
	m_hBMP = 0;
	m_bmpInfo = {};
}

CTexture::~CTexture()
{
	DeleteDC(m_hDC);
	DeleteObject(m_hBMP);
}

HDC CTexture::getDC()
{
	return m_hDC;
}

HBITMAP CTexture::getBmp()
{
	return m_hBMP;
}

BITMAP CTexture::getBmpInfo()
{
	return m_bmpInfo;
}

UINT CTexture::getBmpWidth()
{
	return (int)(m_bmpInfo.bmWidth);
}

UINT CTexture::getBmpHeight()
{
	return (int)(m_bmpInfo.bmHeight);
}

void CTexture::load(const wstring& strPath)
{
	m_hBMP = (HBITMAP)LoadImage(
		nullptr,								
		strPath.c_str(),
		IMAGE_BITMAP,	
		0, 0,	
		LR_CREATEDIBSECTION | LR_LOADFROMFILE );


	assert(m_hBMP);		// 이미지 불러오기 실패한 경우

	m_hDC = CreateCompatibleDC(CCore::getInst()->getMainDC());

	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hDC, m_hBMP);

	GetObject(m_hBMP, sizeof(BITMAP), &m_bmpInfo);

}
