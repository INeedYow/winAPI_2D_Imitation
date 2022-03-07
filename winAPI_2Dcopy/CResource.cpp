#include "framework.h"
#include "CResource.h"

CResource::CResource()
{
	m_eKey = KEY_RES::SIZE;
	m_strRelativePath = L"";

}

CResource::~CResource()
{
}

void CResource::setKey(const KEY_RES& eKey)
{
	m_eKey = eKey;
}

void CResource::setRelativePath(const wstring& strPath)
{
	m_strRelativePath = strPath;
}

KEY_RES CResource::getKey()
{
	return m_eKey;
}

const wstring& CResource::getRelativePath()
{
	return m_strRelativePath;
}
