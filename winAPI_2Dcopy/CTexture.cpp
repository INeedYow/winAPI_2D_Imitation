#include "framework.h"
#include "CTexture.h"

CTexture::CTexture()
{
	m_hDC = 0;
	m_hBitmap = 0;
	m_bmpInfo = {};
}

CTexture::~CTexture()
{	// 해제
	DeleteDC(m_hDC);
	DeleteObject(m_hBitmap);
}

HDC CTexture::getDC()
{
	return m_hDC;
}

HBITMAP CTexture::getBitmap()
{
	return m_hBitmap;
}

BITMAP CTexture::getBitInfo()
{
	return m_bmpInfo;
}

int CTexture::getBmpWidth()
{	// BITMAP 자료형에 포함된 정보 중 width(LONG타입 -> 형변환) 반환
	return (int)(m_bmpInfo.bmWidth);
}

int CTexture::getBmpHeight()
{
	return (int)(m_bmpInfo.bmHeight);
}

void CTexture::load(const wstring& strFilePath)
{	// 이미지 불러오는 함수 LoadImage
	m_hBitmap = (HBITMAP)LoadImage(
		nullptr,									// hInstance nullptr로 하면 된다
		strFilePath.c_str(),						// 인자로 받은 파일경로	// c_str()은 C style 문자열로 변환하는 함수
		IMAGE_BITMAP,								// 이미지 타입			// 비트맵이 가장 다루기 쉬움
		0, 0,										// 가로 세로 길이			// 0 : 이미지 크기 전체
		LR_CREATEDIBSECTION | LR_LOADFROMFILE);		// 이미지 로딩 타입		// 추가 기능들 입력하는 곳인듯

	assert(m_hBitmap);								// 이미지 없으면 에러

	// 비트맵과 연결할 DC
	m_hDC = CreateCompatibleDC(CCore::getInst()->getMainDC());

	// 비트맵과 DC 연결
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hDC, m_hBitmap);

	// 비트맵 정보
	GetObject(m_hBitmap, sizeof(BITMAP), &m_bmpInfo);
}
