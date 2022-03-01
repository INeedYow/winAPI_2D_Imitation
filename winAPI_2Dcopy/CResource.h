#pragma once
class CResource
{
	KEYTEX		m_eKey;				// enum class·Î 
	wstring		m_strRelativePath;

public:
	CResource();
	virtual ~CResource();

	void setKey(const KEYTEX key);
	void setRelativePath(const wstring strPath);

	KEYTEX getKey();
	const wstring& getRelativePath();

};

