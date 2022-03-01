#include "framework.h"
#include "CPathManager.h"

CPathManager::CPathManager()
{
	m_strContentPath[0] = {};
}

CPathManager::~CPathManager()
{

}

// debug, release ��� ���� ��θ� ����Ű���� �ؾ� �Ѵ�.
	// release���� ���� �ֵ��� �߱� ������
	// �� �� ���� ��α��� �ǵ��ư� ���� �ùٸ� ��ġ�� ��������� �Ѵ�.
		// ���������� �� ���� �̵��ϸ� ���� �ַ�� ����
void CPathManager::init()
{	
				// ���� nBufferLength, lpBuffer
					// (number of length, pointer)
	GetCurrentDirectory(255, m_strContentPath);

	Logger::info(m_strContentPath);

	// ���ڿ� ����(�迭 ������)��ȯ �Լ� wcslen();
	int size = (int)wcslen(m_strContentPath);

	// �ڿ������� Ȯ���ϸ� �Ǵϱ�
	for (int i = size - 1; i >= 0; i--)
	{	// ���� ���� ǥ���� \ ã�Ƽ� �ι���
		if ('\\' == m_strContentPath[i])
		{
			m_strContentPath[i] = '\0';
			break;
		}
		
	}
	Logger::info(m_strContentPath);
	// ���ڿ� ��ġ�� �Լ�(���� : destination, size, source)
	wcscat_s(m_strContentPath, 255, L"\\Release\\content\\");

	Logger::info(m_strContentPath);
}

const wchar_t* CPathManager::getContentPath()
{
	return m_strContentPath;
}
