#pragma once

class CTexture;

class CResourceManager
{
	SINGLETON(CResourceManager);

private:
	map<KEY_RES, CTexture*> m_mapTex;

public:
	CTexture* FindTexture(const KEY_RES& eKey);
	CTexture* LoadTextrue(const KEY_RES& eKey, const wstring& strRelativePath);

};
