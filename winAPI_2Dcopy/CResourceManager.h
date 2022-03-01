#pragma once

class CTexture;

class CResourceManager
{
	SINGLETON(CResourceManager);

private:
	map<KEYTEX, CTexture*> m_mapTex;		// Ž���� ������ map
	// Ű���̶� int, enum���� ��ü�ص� �ɵ�
public:
	CTexture* findTexture(KEYTEX strKey);
	CTexture* loadTexture(const KEYTEX strKey, const wstring& strPath);
};

