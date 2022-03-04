#pragma once

class CTexture;

class CResourceManager
{
	SINGLETON(CResourceManager);

private:
	map<UINT, CTexture*> m_mapTex;		

public:
	CTexture* FindTexture(const UINT& strKey);
	CTexture* LoadTextrue(const UINT& strKey, const wstring& strRelativePath);

};
