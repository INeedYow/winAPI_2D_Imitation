#include "framework.h"
#include "CResource.h"

CResource::CResource()
{
	m_strRelativePath = L"";
}

CResource::~CResource()
{
}

void CResource::setKey(const KEYTEX key)
{
	m_eKey = key;
}

void CResource::setRelativePath(const wstring strPath)
{
	m_strRelativePath = strPath;
}

KEYTEX CResource::getKey()
{
	return m_eKey;
}

const wstring& CResource::getRelativePath()
{
	return m_strRelativePath;
}
