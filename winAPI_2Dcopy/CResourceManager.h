#pragma once

class CTexture;

class CResourceManager
{
	SINGLETON(CResourceManager);

private:
	map<KEYTEX, CTexture*> m_mapTex;		// 탐색에 유리한 map
	// 키값이라 int, enum으로 대체해도 될듯
public:
	CTexture* findTexture(KEYTEX strKey);
	CTexture* loadTexture(const KEYTEX strKey, const wstring& strPath);
};

