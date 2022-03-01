#include "framework.h"
#include "CTexture.h"

CTexture::CTexture()
{
	m_hDC = 0;
	m_hBitmap = 0;
	m_bmpInfo = {};
}

CTexture::~CTexture()
{	// ����
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
{	// BITMAP �ڷ����� ���Ե� ���� �� width(LONGŸ�� -> ����ȯ) ��ȯ
	return (int)(m_bmpInfo.bmWidth);
}

int CTexture::getBmpHeight()
{
	return (int)(m_bmpInfo.bmHeight);
}

void CTexture::load(const wstring& strFilePath)
{	// �̹��� �ҷ����� �Լ� LoadImage
	m_hBitmap = (HBITMAP)LoadImage(
		nullptr,									// hInstance nullptr�� �ϸ� �ȴ�
		strFilePath.c_str(),						// ���ڷ� ���� ���ϰ��	// c_str()�� C style ���ڿ��� ��ȯ�ϴ� �Լ�
		IMAGE_BITMAP,								// �̹��� Ÿ��			// ��Ʈ���� ���� �ٷ�� ����
		0, 0,										// ���� ���� ����			// 0 : �̹��� ũ�� ��ü
		LR_CREATEDIBSECTION | LR_LOADFROMFILE);		// �̹��� �ε� Ÿ��		// �߰� ��ɵ� �Է��ϴ� ���ε�

	assert(m_hBitmap);								// �̹��� ������ ����

	// ��Ʈ�ʰ� ������ DC
	m_hDC = CreateCompatibleDC(CCore::getInst()->getMainDC());

	// ��Ʈ�ʰ� DC ����
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hDC, m_hBitmap);

	// ��Ʈ�� ����
	GetObject(m_hBitmap, sizeof(BITMAP), &m_bmpInfo);
}
