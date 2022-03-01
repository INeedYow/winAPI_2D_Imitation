#include "framework.h"
#include "CPathManager.h"

CPathManager::CPathManager()
{
	m_strContentPath[0] = {};
}

CPathManager::~CPathManager()
{

}

// debug, release 모두 같은 경로를 가리키도록 해야 한다.
	// release에만 갖고 있도록 했기 때문에
	// 둘 다 같은 경로까지 되돌아간 다음 올바른 위치를 지정해줘야 한다.
		// 상위폴더로 한 번만 이동하면 같은 솔루션 폴더
void CPathManager::init()
{	
				// 인자 nBufferLength, lpBuffer
					// (number of length, pointer)
	GetCurrentDirectory(255, m_strContentPath);

	Logger::info(m_strContentPath);

	// 문자열 길이(배열 사이즈)반환 함수 wcslen();
	int size = (int)wcslen(m_strContentPath);

	// 뒤에서부터 확인하면 되니까
	for (int i = size - 1; i >= 0; i--)
	{	// 상위 폴더 표시인 \ 찾아서 널문자
		if ('\\' == m_strContentPath[i])
		{
			m_strContentPath[i] = '\0';
			break;
		}
		
	}
	Logger::info(m_strContentPath);
	// 문자열 합치는 함수(인자 : destination, size, source)
	wcscat_s(m_strContentPath, 255, L"\\Release\\content\\");

	Logger::info(m_strContentPath);
}

const wchar_t* CPathManager::getContentPath()
{
	return m_strContentPath;
}
