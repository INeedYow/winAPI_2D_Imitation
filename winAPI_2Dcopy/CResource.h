#pragma once
class CResource
{

	UINT	m_uiKey;
	wstring	m_strRelativePath;

public:
	CResource();
	virtual ~CResource();

	void setKey(const UINT& key);
	void setRelativePath(const wstring& strPath);

	UINT getKey();
	const wstring& getRelativePath();
};
