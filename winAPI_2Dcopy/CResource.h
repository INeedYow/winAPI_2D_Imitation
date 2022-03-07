#pragma once
class CResource
{

	KEY_RES	m_eKey;
	wstring	m_strRelativePath;

public:
	CResource();
	virtual ~CResource();

	void setKey(const KEY_RES& eKey);
	void setRelativePath(const wstring& strPath);

	KEY_RES getKey();
	const wstring& getRelativePath();
};
