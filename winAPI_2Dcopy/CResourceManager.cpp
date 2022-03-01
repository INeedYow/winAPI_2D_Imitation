#include "framework.h"
#include "CResourceManager.h"
#include "CTexture.h"

CResourceManager::CResourceManager()
{
	m_mapTex = {};
}

CResourceManager::~CResourceManager()
{	// second의 CTexture* delete
	for (map<KEYTEX, CTexture*>::iterator iter = m_mapTex.begin(); iter != m_mapTex.end(); iter++)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}
	m_mapTex.clear();	// clear
}

CTexture* CResourceManager::findTexture(KEYTEX strKey)
{	// 인자로 받은 키값으로 map자료구조에서 찾고 해당 이터레이터를 iter에 받음
	map<KEYTEX, CTexture*>::iterator iter = m_mapTex.find(strKey);
	
	if (m_mapTex.end() == iter) return nullptr;		// iter가 end면 없으니 null반환
	return iter->second;
}

// TODO 다시보기
CTexture* CResourceManager::loadTexture(KEYTEX strKey, const wstring& strPath)
{
	CTexture* pTex = findTexture(strKey);	// 일단 찾아봄
	if (nullptr != pTex) return pTex;		// 이미 있으면 그거 반환

	// pathMgr에 있는 경로에 인자로 받은 경로 합친 게 경로
	wstring strFilePath = CPathManager::getInst()->getContentPath();
	strFilePath += strPath;

	pTex = new CTexture;
	pTex->load(strFilePath);			// texture에 load()가 LoadImage()로 이미지 불러옴
	pTex->setKey(strKey);
	pTex->setRelativePath(strPath);

	m_mapTex.insert(make_pair(strKey, pTex));

	return pTex;

}
