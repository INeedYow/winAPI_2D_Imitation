#include "framework.h"
#include "CResource.h"

CResource::CResource()
{
	m_uiKey = 0;
	m_strRelativePath = L"";

}

CResource::~CResource()
{
}

void CResource::setKey(const UINT& key)
{
	m_uiKey = key;
}

void CResource::setRelativePath(const wstring& strPath)
{
	m_strRelativePath = strPath;
}

UINT CResource::getKey()
{
	return m_uiKey;
}

const wstring& CResource::getRelativePath()
{
	return m_strRelativePath;
}
