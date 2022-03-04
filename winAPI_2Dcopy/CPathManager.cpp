#include "framework.h"
#include "CPathManager.h"

CPathManager::CPathManager()
{
	m_strContentPath[0] = {};
}

CPathManager::~CPathManager()
{

}

void CPathManager::init()
{
	GetCurrentDirectory(255, m_strContentPath);					// ���� ��� �޾ƿ�(���α׷� ���۵��� ��)

	int iLen = (int)wcslen(m_strContentPath);

	for (int i = iLen - 1; i >= 0; i--)
	{
		if ('\\' == m_strContentPath[i])
		{
			m_strContentPath[i] = '\0';
			break;
		}
	}

	wcscat_s(m_strContentPath, 255, L"\\Release\\content\\");	// wchar_t ���ڿ� �ڿ� ���ڿ� ���̱�
}

const wchar_t* CPathManager::GetContentPath()
{
	return m_strContentPath;
}
