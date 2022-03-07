#pragma once

class CTexture;

class CResourceManager
{
	SINGLETON(CResourceManager);

private:
	map<KEY_RES, CTexture*> m_mapTex;

public:
	CTexture* findTexture(const KEY_RES& eKey);
	CTexture* loadTextrue(const KEY_RES& eKey, const wstring& strRelativePath);

};
