#include "framework.h"
#include "CResourceManager.h"
#include "CTexture.h"

CResourceManager::CResourceManager()
{
	m_mapTex = {};
}

CResourceManager::~CResourceManager()
{
	for (map<KEY_RES, CTexture*>::iterator iter = m_mapTex.begin(); iter != m_mapTex.end(); iter++)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}

	m_mapTex.clear();
}

CTexture* CResourceManager::FindTexture(const KEY_RES& strKey)
{
	map<KEY_RES, CTexture*>::iterator iter = m_mapTex.find(strKey);

	if (m_mapTex.end() == iter)
		return nullptr;

	return iter->second;
}

CTexture* CResourceManager::LoadTextrue(const KEY_RES& eKey, const wstring& strRelativePath)
{
	CTexture* pTex = FindTexture(eKey);		// 이미 Texture가 있는지 확인
	if (nullptr == pTex)
	{
		// Texture 저장 경로 확인
		wstring strFilePath = CPathManager::getInst()->GetContentPath();
		strFilePath += strRelativePath;

		// Texture 생성 후 저장
		pTex = new CTexture;
		pTex->load(strFilePath);
		pTex->setKey(eKey);
		pTex->setRelativePath(strRelativePath);

		m_mapTex.insert(make_pair(eKey, pTex));
	}
	return pTex;
}
