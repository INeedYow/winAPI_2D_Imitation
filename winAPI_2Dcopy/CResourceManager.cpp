#include "framework.h"
#include "CResourceManager.h"
#include "CTexture.h"

CResourceManager::CResourceManager()
{
	m_mapTex = {};
}

CResourceManager::~CResourceManager()
{	// second�� CTexture* delete
	for (map<KEYTEX, CTexture*>::iterator iter = m_mapTex.begin(); iter != m_mapTex.end(); iter++)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}
	m_mapTex.clear();	// clear
}

CTexture* CResourceManager::findTexture(KEYTEX strKey)
{	// ���ڷ� ���� Ű������ map�ڷᱸ������ ã�� �ش� ���ͷ����͸� iter�� ����
	map<KEYTEX, CTexture*>::iterator iter = m_mapTex.find(strKey);
	
	if (m_mapTex.end() == iter) return nullptr;		// iter�� end�� ������ null��ȯ
	return iter->second;
}

// TODO �ٽú���
CTexture* CResourceManager::loadTexture(KEYTEX strKey, const wstring& strPath)
{
	CTexture* pTex = findTexture(strKey);	// �ϴ� ã�ƺ�
	if (nullptr != pTex) return pTex;		// �̹� ������ �װ� ��ȯ

	// pathMgr�� �ִ� ��ο� ���ڷ� ���� ��� ��ģ �� ���
	wstring strFilePath = CPathManager::getInst()->getContentPath();
	strFilePath += strPath;

	pTex = new CTexture;
	pTex->load(strFilePath);			// texture�� load()�� LoadImage()�� �̹��� �ҷ���
	pTex->setKey(strKey);
	pTex->setRelativePath(strPath);

	m_mapTex.insert(make_pair(strKey, pTex));

	return pTex;

}
